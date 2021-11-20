<script lang="ts">
  import instantiate_lifehash, { LifeHashModule } from './lifehash.js';
  import { LifeHashVersion } from './lifehash.types';

  let lifehash: LifeHashModule;

  const inputModeString = {
    sourceIsString: true,
    text: 'UTF-8 string',
  };

  const inputModeDigest = {
    sourceIsString: false,
    text: 'SHA-256 digest',
  };

  const inputModes = [inputModeString, inputModeDigest];

  const versions = [
    {
      version: LifeHashVersion.version1,
      text: 'Version 1',
      description:
        'DEPRECATED. Uses HSB gamut. Not CMYK-friendly. Has some minor gradient bugs.',
    },
    {
      version: LifeHashVersion.version2,
      text: 'Version 2',
      description: 'The official LifeHash. Recommended for most purposes. CMYK-friendly gamut.',
    },
    {
      version: LifeHashVersion.detailed,
      text: 'Detailed',
      description: 'Double resolution. CMYK-friendly gamut.',
    },
    {
      version: LifeHashVersion.fiducial,
      text: 'Fiducial',
      description:
        'Optimized for generating machine-vision fiducials. High-contrast. CMYK-friendly gamut.',
    },
    {
      version: LifeHashVersion.grayscaleFiducial,
      text: 'Grayscale Fiducial',
      description:
        'Optimized for generating machine-vision fiducials. High-contrast for low-light conditions.',
    },
  ];

  let selectedVersion = versions[1];
  let inputString = 'Hello, world!';
  let inputDigestHex = '';
  let sourceDigestHex = '';
  let sourceDigestBytes: Uint8Array | null;
  let inputMode = inputModeString;

  let inputStringChanged = (inputString: string): void => {};
  let inputDigestChanged = (inputDigest: string): void => {};
  let updateImage = (
    digestBytes: Uint8Array,
    version: LifeHashVersion
  ): void => {};
  let updateGallery = (version: LifeHashVersion, seeds: string[]): void => {};

  $: inputStringChanged(inputString);
  $: inputDigestChanged(inputDigestHex);
  $: updateImage(sourceDigestBytes, selectedVersion.version);
  $: updateGallery(selectedVersion.version, gallerySeeds);

  let gallerySeeds: string[] = [];
  reseed();

  const urlParams = new URLSearchParams(window.location.search);
  const queryString = urlParams.get('s');
  console.log(queryString);
  if (queryString !== null) {
    inputString = queryString;
    inputMode = inputModeString;
  } else {
    const queryString = urlParams.get('d');
    console.log(queryString);
    if (queryString !== null) {
      inputDigestHex = queryString;
      inputMode = inputModeDigest;
    }
  }

  (async () => {
    lifehash = await instantiate_lifehash();

    inputStringChanged = (inputString: string) => {
      if (inputMode === inputModeString) {
        const hex = lifehash.dataToHex(lifehash.sha256(inputString));
        inputDigestHex = hex;
      }
    };

    inputDigestChanged = (inputDigest: string) => {
      sourceDigestHex = inputDigest;
      const digest = lifehash.hexToData(sourceDigestHex);
      if (digest === null || digest.length !== 32) {
        sourceDigestBytes = null;
      } else {
        sourceDigestBytes = digest;
      }
    };

    updateImage = (digestBytes: Uint8Array, version: LifeHashVersion) => {
      const div = document.getElementById('image');
      div.innerHTML = '';

      if (digestBytes !== null) {
        let result = lifehash.makeFromDigest(digestBytes, version, 4);
        result.style.margin = '5px';
        div.appendChild(result);
      }
    };

    updateGallery = (version: LifeHashVersion, seeds: string[]) => {
      let result: HTMLElement[] = [];
      for (const seed of seeds) {
        let div = document.createElement('div');

        let upperDiv = document.createElement('div');
        upperDiv.appendChild(lifehash.makeFromUTF8(seed, version, 3));
        upperDiv.onclick = () => {
          inputMode = inputModeString;
          inputString = seed;
        };

        let lowerDiv = document.createElement('div');
        let lowerSpan = document.createElement('a');
        lowerDiv.appendChild(lowerSpan);
        lowerSpan.innerText = seed;
        lowerSpan.style.fontFamily = 'monospace';
        lowerSpan.style.fontSize = '12pt';
        lowerSpan.style.fontWeight = 'bold';
        lowerSpan.onclick = () => {
          inputMode = inputModeString;
          inputString = seed;
        };

        div.appendChild(upperDiv);
        div.appendChild(lowerDiv);
        div.style.display = 'inline-block';
        div.style.margin = '5px';
        div.style.textAlign = 'center';

        result.push(div);
      }
      const d = document.getElementById('gallery');
      d.textContent = '';
      for (const item of result) {
        d.appendChild(item);
      }
    };
  })();

  function randomItem<T>(items: ArrayLike<T>): T {
    return items[Math.floor(Math.random() * items.length)];
  }

  function randomLetter(): string {
    return randomItem('ABCDEFGHIJKLMNOPQRSTUVWXYZ');
  }

  function randomLetterCluster(): string {
    let result = '';
    for (let i = 0; i < 3; i++) {
      result += randomLetter();
    }
    return result;
  }

  function randomSeed(): string {
    return randomLetterCluster() + '-' + randomLetterCluster();
  }

  function reseed() {
    let result: string[] = [];
    for (let i = 0; i < 10; i++) {
      result.push(randomSeed());
    }
    gallerySeeds = result;
  }
</script>

<main>
  <div style="margin-bottom: 20px;">
    <label>
      <strong>Create Lifehash using a:</strong>
      <select bind:value={inputMode}>
        {#each inputModes as inputMode}
          <option value={inputMode}>
            {inputMode.text}
          </option>
        {/each}
      </select>
    </label>
  </div>
  {#if inputMode.sourceIsString}
    <div>
      <label>
        <strong>Input string:</strong>
        <input bind:value={inputString} spellcheck="false" />
      </label>
      <p class="caption">
        Edit this field to update the LifeHash image below. When using the
        library, the input can be a binary object of any size.
      </p>
    </div>
    <div>
      <strong>SHA-256 Digest:</strong>
      <span class="data">{sourceDigestHex}</span>
      <p class="caption">
        This is the unique “fingerprint” of the input that is used as the seed
        for the LifeHash algorithm. Making even a tiny change to the input
        string above results in a complete change of the digest.
      </p>
    </div>
  {:else}
    <div>
      <label style="width: 100%;">
        <strong>Input SHA-256 Digest:</strong><br />
        <textarea
          bind:value={inputDigestHex}
          class="data"
          spellcheck="false"
          rows="1"
          style="width: 100%;"
        />
      </label>
      {#if sourceDigestBytes === null}
        <div class="error">Invalid digest.</div>
      {/if}
      <p class="caption">
        This is the unique “fingerprint” of the input that is used as the seed
        for the LifeHash algorithm. It must be exactly 64 hexadecimal digits
        produced by the SHA-256 algorithm.
      </p>
    </div>
  {/if}
  <div>
    <label>
      <strong>LifeHash Version:</strong>
      <select bind:value={selectedVersion}>
        {#each versions as version}
          <option value={version}>
            {version.text}
          </option>
        {/each}
      </select>
    </label>
    <p class="caption">
      About {selectedVersion.text}: {selectedVersion.description}
    </p>
  </div>
  <strong>LifeHash:</strong>
  <div id="image" style="margin-bottom: 20px;" />
  {#if sourceDigestBytes === null}
    <div class="error">Invalid digest.</div>
  {/if}

  <div><strong>Gallery:</strong><button class="reload" on:click={reseed}>↻ More</button></div>
  <p class="caption">
    Click on the icons below to set the input string,
    reproducing the exact same LifeHash.
  </p>
  <div id="gallery" />
</main>

<style>
  main {
    text-align: left;
    background: lightGray;
    width: 100%;
    padding: 10px;
  }

  .caption {
    margin-top: 5px;
    font-size: 10pt;
  }

  .data {
    font-family: monospace;
    font-size: 12pt;
    word-wrap: break-word;
    display: block;
  }

  .error {
    color: red;
    font-weight: bold;
  }

  button.reload {
    border: none;
    background-color: transparent;
    font-weight: bold;
  }

  button.reload:active {
    background-color: gray;
  }
</style>
