const sotez = require('sotez');
const provider = "http://localhost:18731";

sotez.node.setProvider(provider);

sotez.contract.load('KT1EqomJQCJCwjiq2XzWqqBwNntQXJBoCgRJ')
  .then(console.log);
