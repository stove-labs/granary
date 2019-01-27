const sotez = require('sotez');
const provider = "http://localhost:18731";

sotez.node.setProvider(provider);

sotez.contract.load('KT1WBCA1YLiuUazqVbYiRNfuQeaq8SPmh2r1')
  .then(console.log);
