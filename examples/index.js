const sotez = require('sotez');
const account = "tz1Y65Dac2K9FNxY4R9HAt4Jo8JFvRZedYan";
const provider = "http://localhost:18731";

sotez.node.setProvider(provider);

sotez.node.query('/chains/main/blocks/head')
  .then(response => console.log(response));