<script lang="ts">
  import LifeHashDemo from "./lib/LifeHashDemo.svelte";

  let message: string;
</script>

<main>
  <h1>LifeHash</h1>
  <h2>Beautiful Visual Hashes</h2>
  <h3>
    from <a href="https://www.blockchaincommons.com/" target="_blank"
      >Blockchain Commons</a
    >
  </h3>
  <h3>
    created by <a href="https://wolfmcnally.com" target="_blank">Wolf McNally</a
    >
  </h3>
  <div class="explanation">
    <p>
      This page is a live demonstration of the <a href="https://github.com/BlockchainCommons/bc-lifehash" target="_blank">LifeHash</a> visual hash algorithm running in the web browser.
      It uses the reference C++ implementation compiled to <a href="https://webassembly.org/" target="_blank">WebAssembly</a>.
    </p>
  </div>

  <LifeHashDemo />

  <h3 class="section">About <strong>LifeHash</strong></h3>

  <p>
    LifeHash is a method of <a
      href="https://en.wikipedia.org/wiki/Identicon"
      target="_blank">hash visualization</a
    >
    based on
    <a
      href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life"
      target="_blank">Conway’s Game of Life</a
    > that creates beautiful icons that are deterministic, yet distinct and unique
    given the input data.
  </p>

  <p>
    The basic concept is to take a <a
      href="https://en.wikipedia.org/wiki/SHA-2"
      target="_blank">SHA-256</a
    > hash of the input data (which can be any data including another hash) and then
    use the 256-bit digest as a 16x16 pixel "seed" for running the cellular automata
    known as Conway’s Game of Life.
  </p>

  <p>
    After the pattern becomes stable (or begins repeating) the resulting history
    is used to compile a grayscale image of all the states from the first to
    last generation. Using Game of Life provides visual structure to the
    resulting image, even though it was seeded with entropy.
  </p>

  <p>
    Some bits of the initial hash are then used to deterministically apply
    symmetry and color to the icon to add beauty and quick recognizability.
  </p>

  <h3 class="section">Watch the explainer video</h3>

  <a href="https://www.youtube.com/watch?v=cu0K__KLxKo" target="_blank"
    ><img src="title-card.jpg" alt="Explainer Video" style="width:100%; max-width: 600px" /></a
  >

  <div class="explanation">
    <h3 class="section">We care about your privacy</h3>
    <p>
      This page is self-contained, sets no cookies, and sends no data to the
      cloud.
    </p>
  </div>
</main>

<style>
  main {
    text-align: left;
    padding: 1em;
    margin: 0 auto;
  }

  main a {
    text-decoration: none;
  }

  main h1 {
    font-family: Urbanist, sans-serif;
    font-weight: 800;
    color: #333;
  }

  main h2 {
    font-family: Urbanist, sans-serif;
    font-weight: 600;
  }

  main h3 {
    font-family: Urbanist, sans-serif;
    font-weight: 300;
  }

  main h3 a {
    font-weight: 600;
  }

  main h3 strong {
    font-weight: 600;
  }

  .section {
    margin-top: 30px;
    margin-bottom: 10px;
  }

  .explanation {
    margin-top: 20px;
    margin-bottom: 20px;
  }
</style>
