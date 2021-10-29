<script lang="ts">
  import instantiate_lifehash, { LifeHashModule } from "./lifehash.js"
  import LifeHashVersion from "./lifehash.js"

  let lifehash: LifeHashModule;

  let updateDigestHex = (input: string) => { return ''; }
  let updateImage = (input: string): HTMLImageElement|null => { return null; }

  let inputString = "Hello, world!";
  $: digestHex = updateDigestHex(inputString);
  $: image = updateImage(inputString);

  (async () => {
    lifehash = await instantiate_lifehash();

    updateDigestHex = (input: string) => {
      return lifehash.dataToHex(lifehash.sha256(inputString));
    };
    updateImage = (input: string): HTMLImageElement|null => {
      let result = lifehash.makeFromUTF8(input, 1, 3);
      result.style = "margin: 5px;"
      const d = document.getElementById("image");
      d.appendChild(result);
      return result;
    };
  })();
</script>

<main>
  <label>
    <strong>Input string:</strong>
    <input bind:value={inputString}>
  </label>
  <p><strong>Digest:</strong> <span class="data">{digestHex}</span></p>
  <strong>LifeHash:</strong>
  <div id="image"></div>
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
