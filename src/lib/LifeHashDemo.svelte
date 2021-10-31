<script lang="ts">
  import instantiate_lifehash, { LifeHashModule } from "./lifehash.js";
  import { LifeHashVersion } from "./lifehash.types";

  let lifehash: LifeHashModule;

  function randomItem<T>(items: ArrayLike<T>): T {
    return items[Math.floor(Math.random() * items.length)];
  }

  function randomLetter(): string {
    return randomItem("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  }

  function randomLetterCluster(): string {
    let result = '';
    for(let i = 0; i < 3; i++) {
      result += randomLetter();
    }
    return result;
  }

  function randomSeed(): string {
    return randomLetterCluster() + '-' + randomLetterCluster();
  }

  let updateDigestHex = (input: string) => {
    return "";
  };
  let updateImage = (
    input: string,
    version: LifeHashVersion
  ): HTMLImageElement | null => {
    return null;
  };
  let updateGallery = (version: LifeHashVersion, seeds: string[]) => {};
  let gallerySeeds: string[] = [];

  function reseed() {
    let result: string[] = [];
    for (let i = 0; i < 10; i++) {
      result.push(randomSeed());
    }
    gallerySeeds = result;
  }
  reseed();

  const versions = [
    {
      version: LifeHashVersion.version1,
      text: "Version 1",
      description:
        "DEPRECATED. Uses HSB gamut. Not CMYK-friendly. Has some minor gradient bugs.",
    },
    {
      version: LifeHashVersion.version2,
      text: "Version 2",
      description: "CMYK-friendly gamut. Recommended for most purposes.",
    },
    {
      version: LifeHashVersion.detailed,
      text: "Detailed",
      description: "Double resolution. CMYK-friendly gamut.",
    },
    {
      version: LifeHashVersion.fiducial,
      text: "Fiducial",
      description:
        "Optimized for generating machine-vision fiducials. High-contrast. CMYK-friendly gamut.",
    },
    {
      version: LifeHashVersion.grayscaleFiducial,
      text: "Grayscale Fiducial",
      description:
        "Optimized for generating machine-vision fiducials. High-contrast for low-light conditions.",
    },
  ];

  let selectedVersion = versions[1];


  let inputString = "Hello, world!";

  const urlParams = new URLSearchParams(window.location.search);
  const queryString = urlParams.get('s');
  if(queryString !== null) {
    inputString = queryString;
  }

  $: digestHex = updateDigestHex(inputString);
  $: image = updateImage(inputString, selectedVersion.version);
  $: gallery = updateGallery(selectedVersion.version, gallerySeeds);

  (async () => {
    lifehash = await instantiate_lifehash();

    updateDigestHex = (input: string) => {
      return lifehash.dataToHex(lifehash.sha256(inputString));
    };
    updateImage = (
      input: string,
      version: LifeHashVersion
    ): HTMLImageElement | null => {
      let result = lifehash.makeFromUTF8(input, version, 4);
      result.style.margin = "5px";
      const d = document.getElementById("image");
      const old = d.firstChild;
      if (old !== null) {
        d.removeChild(old);
      }
      d.appendChild(result);
      return result;
    };
    updateGallery = (version: LifeHashVersion, seeds: string[]) => {
      let result: HTMLElement[] = [];
      for (const seed of seeds) {
        let div = document.createElement('div');

        let upperDiv = document.createElement('div');
        upperDiv.appendChild(lifehash.makeFromUTF8(seed, version, 3));

        let lowerDiv = document.createElement('div');
        let lowerSpan = document.createElement('a');
        lowerDiv.appendChild(lowerSpan);
        lowerSpan.innerText = seed;
        lowerSpan.style.fontFamily = 'monospace';
        lowerSpan.style.fontSize = '12pt';
        lowerSpan.style.fontWeight = 'bold';
        lowerSpan.onclick = () => { inputString = seed; };

        div.appendChild(upperDiv);
        div.appendChild(lowerDiv);
        div.style.display = 'inline-block';
        div.style.margin = '5px';
        div.style.textAlign = 'center';

        result.push(div);
      }
      const d = document.getElementById("gallery");
      d.textContent = "";
      for (const item of result) {
        d.appendChild(item);
      }
    };
  })();
</script>

<main>
  <div>
    <label>
      <strong>Input string:</strong>
      <input bind:value={inputString} />
    </label>
    <p class="caption">
      Edit this field to update the LifeHash image below. When using the
      library, the input can be a binary object of any size.
    </p>
  </div>
  <div>
    <strong>SHA-256 Digest:</strong> <span class="data">{digestHex}</span>
    <p class="caption">
      This is the unique “fingerprint” of the input that is used as the seed for
      the LifeHash algorithm. Making even a tiny change to the input object
      above results in a complete change of the digest.
    </p>
  </div>
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
  <div id="image" />
  <strong>Gallery:</strong> <button class="reload" on:click={reseed}>↻ More</button>
  <div id="gallery" />
  <p class="caption">You can click on the strings beneath each icon to set the input field above, reproducing the exact same LifeHash.</p>
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

  button.reload {
    border: none;
    background-color: transparent;
    font-weight: bold;
  }

  button.reload:active {
    background-color: gray;
  }
</style>
