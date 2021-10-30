<script lang="ts">
  import HelloTest from "./lib/HelloTest.svelte";

  let message: string;
</script>

<main>
  <h1>LifeHash: Beautiful Visual Hashes</h1>
  <h2>
    from <a href="https://www.blockchaincommons.com/" target="_blank"
      >Blockchain Commons</a
    >
  </h2>
  <h2>
    created by <a href="https://wolfmcnally.com" target="_blank">Wolf McNally</a
    >
  </h2>
  <div class="explanation">
    <p>
      This page is a live, running example of the LifeHash visual hash
      algorithm. It uses the reference C++ implementation compiled to
      WebAssembly.
    </p>
  </div>

  <HelloTest />

  <h2 class="section">About <strong>LifeHash</strong></h2>

  <p>LifeHash is a method of hash visualization based on Conway’s Game of Life that creates beautiful icons that are deterministic, yet distinct and unique given the input data.</p>

  <p>The basic concept is to take a SHA-256 hash of the input data (which can be any data including another hash) and then use the 256-bit digest as a 16x16 pixel "seed" for running the cellular automata known as Conway’s Game of Life.</p>

  <p>After the pattern becomes stable (or begins repeating) the resulting history is used to compile a grayscale image of all the states from the first to last generation. Using Game of Life provides visual structure to the resulting image, even though it was seeded with entropy.</p>

  <p>Some bits of the initial hash are then used to deterministically apply symmetry and color to the icon to add beauty and quick recognizability.</p>

  <p>Watch the explainer video below!</p>

  <div class="video-container">
    <iframe
      title="video"
      class="video"
      src="https://www.youtube.com/embed/cu0K__KLxKo"
      allowfullscreen
    />
  </div>

  <div class="explanation">
      <h2 class="section">We Care about Your Privacy</h2>
      <p>This page is self-contained, sets no cookies, and sends no data to the cloud. The embedded YouTube video access Google's APIs.</p>
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
    color: #555;
  }

  main h2 {
    font-family: Urbanist, sans-serif;
    font-weight: 300;
  }

  main h2 a {
    font-weight: 600;
  }

  main h2 strong {
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

  .video-container {
    position: relative;
    width: 100%;
    padding-bottom: 56.25%;
  }

  .video {
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    border: 0;
  }
</style>
