---
id: client-usage
title: Using the client
---

Granary provides a way to run a pre-configured `tezos-client` to interact with either the *sandboxed tezos node*, or with a *publicly hosted alphanet node*.

## Example commands
```zsh
granary client - get balance for "alice"
```

## Usage with alphanet

To use the `alphanet` version of tezos-client, you have to switch Granary's network mode first. It's fairly straightforward:

```zsh
# Switch to the alphanet network mode
granary config set network "alphanet"

# Initialize a network specific data directory for the client
granary client init
```

> ⚠️ Notice how the command is encapuslated in quotes, this is used to prevent mixed behavior when passing additional flags/options to the client.

```zsh
granary client - "--tls rpc get /protocols"
# Outputs
[ "ProtoDemoDemoDemoDemoDemoDemoDemoDemoDemoDemoD3c8k9",
  "PsddFKi32cMJ2qPjf43Qv5GDWLDPZb3T3bF6fLKiF5HtvHNU7aP",
  "Ps6mwMrF2ER2s51cp9yYpjDcuzQjsc2yAz8bQsRgdaRxw4Fk95H" ]
```

### Changing the alphanet node URL

By default, Granary will connect to `alphanet.tezrpc.me`, which is an alphanet node hosted / provided by [Tezbox](https://tezbox.com/). You can update the alphanet node's URL used by the client with:

> ⚠️ More information about TzScan can be found [here](https://tzscan.io/).
> Before using TzScan's public nodes, please see their [terms & conditions](https://tzscan.io/terms-of-services).

```zsh
# Update the client's nodeAddr
granary config set tezosClient.networks.alphanet.nodeAddr "alphanet-node.tzscan.io"
```

## Usage with mainnet (soon™)

> ⚠️ Please consider the fact that this is a `pre-alpha` software and should be used with extreme caution when handling production-ready credentials. Production *(mainnet)* usage is discouraged until the CLI becomes more stable.

Using the client with mainnet requires additional configuration in `granary.json`, which defines a new network setup in the same way as *sandboxnet* and *alphanet* is defined. 



