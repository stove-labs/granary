---
id: sandboxnet-introduction
title: Introduction
---

Development, no matter if blockchain or not, usually requires a fine-tuned control over your development environment. For Tezos, this is where the *private sandbox* comes into play. It's no rocket science, a bare `tezos-node` with a few options on top - don't worry, Granary lifts all the heavy weights for you.

## Getting started

Starting a sandboxed tezos-node is a no-brainer, but first you have to make sure to *install & initialize granary*, so let's do that. In an empty directory, or an existing project, run the following:

> Installation instructions can be found [here](getting-started-install.md)

```zsh
granary init
```

After initializing, you should now see a `.granary` folder and a `granary.json` config file in your project. One serves as a data storage for everything Granary related, and the other is a configuration file for your project.

To start a sandboxnet node, all you have to do is run the following command, and then check if it's up and running by calling the `/protocols` RPC endpoint via cURL.

```zsh
granary node start
```

```zsh
curl "http://localhost:8732/protocols"
# Outputs
["ProtoALphaALphaALphaALphaALphaALphaALphaALphaDdp3zK","ProtoDemoDemoDemoDemoDemoDemoDemoDemoDemoDemoD3c8k9","ProtoGenesisGenesisGenesisGenesisGenesisGenesk612im"]
```
