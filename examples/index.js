const sotez = require('sotez');
const account = "tz1gjaF81ZRRvdzjobyfVNsAeSC6PScjfQwN";
const provider = "http://localhost:18731";

sotez.node.setProvider(provider);

sotez.rpc.getBalance(account)
    .then(console.log);