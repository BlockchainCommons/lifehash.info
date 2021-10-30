<script lang="ts">
  import instantiate_lifehash, { LifeHashModule } from "./lifehash.js";
  import { LifeHashVersion } from "./lifehash.types";

  let lifehash: LifeHashModule;

  let updateDigestHex = (input: string) => {
    return "";
  };
  let updateImage = (
    input: string,
    version: LifeHashVersion
  ): HTMLImageElement | null => {
    return null;
  };

  const versions = [
    { version: LifeHashVersion.version1, text: "Version 1", description: "DEPRECATED. Uses HSB gamut. Not CMYK-friendly. Has some minor gradient bugs." },
    { version: LifeHashVersion.version2, text: "Version 2", description: "CMYK-friendly gamut. Recommended for most purposes." },
    { version: LifeHashVersion.detailed, text: "Detailed", description: "Double resolution. CMYK-friendly gamut." },
    { version: LifeHashVersion.fiducial, text: "Fiducial", description: "Optimized for generating machine-vision fiducials. High-contrast. CMYK-friendly gamut." },
    { version: LifeHashVersion.grayscaleFiducial, text: "Grayscale Fiducial", description: "Optimized for generating machine-vision fiducials. High-contrast." },
  ];

  let selectedVersion = versions[1];

  let inputString = "Hello, world!";
  $: digestHex = updateDigestHex(inputString);
  $: image = updateImage(inputString, selectedVersion.version);

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
  })();
</script>

<main>
  <label>
    <strong>Input string:</strong>
    <input bind:value={inputString} />
  </label>
  <p><strong>Digest:</strong> <span class="data">{digestHex}</span></p>
  <div>
    <label>
      <strong>Version:</strong>
      <select bind:value={selectedVersion}>
        {#each versions as version}
          <option value={version}>
            {version.text}
          </option>
        {/each}
      </select>
    </label>
    <p style="margin-top: 5px;">{selectedVersion.description}</p>
  </div>
  <strong>LifeHash:</strong>
  <div id="image" />
</main>

<style>
  main {
    text-align: left;
    background: lightGray;
    width: 100%;
    padding: 10px;
  }

  .data {
    font-family: monospace;
    font-size: 12pt;
    word-wrap: break-word;
    display: block;
  }
</style>
