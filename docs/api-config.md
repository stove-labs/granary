---
id: api-config
title: Configuration
---

This page explains different configuration options for the Granary CLI.

## API

Documentation available [here](api-cli-commands.md#config).

## Relevant configuration

> ⚠️ Granary uses a config refference mechanism where you can point to other parts of the config by using the following syntax: `<path.to.property>`

Lot of the default configuration you get when you start a project with Granary, probably doesn't concern you that much. So that's why here's a list of things that you're most likely to change:

<div class="configuration-table">

|Key |Default |Available |Description|
|:---|:---|:---|:---|
|`network`   | `"sandboxnet"`   |`"sandboxnet"` `"alphanet"`   | Network name used for the node, client, config options etc., update this based on which network you're trying to work with.|
|`tezosNode.networks.sandboxnet.rpcPort`|`"8732"` | Whatever HTTP port your machine allows | Port number used to serve RPC services from the sandboxnet node|
|`tezosClient.networks.alphanet.nodeAddr` |`"alphanet.tezrpc.me"` | Any HTTP/HTTPS URL of an alphanet Tezos node | URL representing an alphanet Tezos node that the client will connect to|

</div>

### Setting an alphanet node's URL & port

Example configuration workflow for setting an URL of a 3rd party alphanet node:

```sh-session
granary config set network alphanet
granary config set tezosClient.networks.alphanet.nodeAddr alphanet.tezrpc.me
granary config set tezosClient.networks.alphanet.nodeRpcPort 443
granary client - "--tls rpc get /protocols" 
```

## Overriding the default configuration file

Default config path for the Granary CLI is `./granary.json`, which means that a configuration file from your current working directory will always be used - unless you override it with the option documented [here](api-cli-commands.md#setting-a-custom-config-path).


---


## granary.json

The file below is an up-to-date version of the default `granary.json` configuration file. Beware that it contains all the different options that are also used internally for Granary. You can see the most often used configuration options explained in the section below.

> ⚠️ Currently the default config is over-bloated, this will likely change when we hit `alpha`.


```js
{
    network: "sandboxnet",
    dockerNetworkName: "granary",
    data: {
        basePath: ".granary",
        networks: {
            sandboxnet: {
                "name": "sandboxnet",
                subFolderName: "<data.networks.sandboxnet.name>",
                nodeFolder: "<data.basePath>/<data.networks.sandboxnet.subFolderName>/node",
                clientFolder: "<data.basePath>/<data.networks.sandboxnet.subFolderName>/client"
            },
            alphanet: {
                "name": "alphanet",
                subFolderName: "<data.networks.alphanet.name>",
                nodeFolder: "",
                clientFolder: "<data.basePath>/<data.networks.alphanet.subFolderName>/client"
            }
        }
    },
    tezosClient: {
        networks: {
            sandboxnet: {
                dockerImage: "stovelabs/granary-tezos-client-sandboxnet",
                nodeAddr: "<tezosNode.networks.sandboxnet.containerName>",
                nodeRpcPort: "<tezosNode.networks.sandboxnet.rpcPort>",
                baseDir: "<data.networks.sandboxnet.clientFolder>"
            },
            alphanet: {
                dockerImage: "stovelabs/granary-tezos-client-alphanet",
                nodeAddr: "alphanet.tezrpc.me",
                nodeRpcPort: "443",
                baseDir: "<data.networks.alphanet.clientFolder>"
            }
        }
    },
    tezosNode: {
        networks: {
            sandboxnet: {
                dockerImage: "stovelabs/granary-tezos-node-sandboxnet",
                containerName: "granary-tezos-node-sandbox",
                rpcPort: "8732",
                dataDir: "<data.networks.sandboxnet.nodeFolder>"
            },
            alphanet: {
                dockerImage: "",
                containerName: "",
                rpcPort: "",
                dataDir: ""
            }
        }
    }
}
```