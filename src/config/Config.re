open Log;
open ConfigStore;
open Lodash;

let defaultConfigPath = "./granary.json";

/* @TODO: Define a proper configDefaults type instead of abusing %bs.raw */
/* Those defaults get saved in the used JSON config if it's empty */
let configDefaults = [%bs.raw {|
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
|}];


let getConfigStore = () => {
    
    /* Allow override of the default config path via --config */
    let configPath = switch(Js.Dict.get(Cli.program, "config")) {
        | Some(configPath) => {
            log(
                ~message = ":warning:  Using custom config path: " ++ configPath
            )
            configPath
        }
        | None => defaultConfigPath
    };

    /* %bs.obj to turn this record into a plain JS object */
    let configOptions: ConfigStore.configOptions = [%bs.obj {
        globalConfigPath: None,
        configPath: Some(configPath)
    }];

    ConfigStore.configStore(Package.name, configDefaults, configOptions);
};


/**
 * This allows config values, to reference other config properties
 * e.g.:
 * 
 * "val1": 1,
 * "val2": "<val1>"
 */
let replaceValues = (value, config) => {
    replace(value, [%bs.raw {|/(<[^>]+>)/g|}], (match) => {
        let match = Js.String.replace("<", "", match)
            |> Js.String.replace(">", "");
        Belt.Option.getExn(
            config->get(match)
        );
    })
};

let replaceValuesInDepth = (value, config) => {
    let value = ref(value);
    while (value.contents !== replaceValues(value.contents, config)) {
        value := replaceValues(value.contents, config);
    }
    value.contents;
};


let getOptional = (property) => {
    let config = getConfigStore();
    let property = replaceValuesInDepth(property, config);
    let value = config->get(property);
    switch (value) {
        | Some(value) => {
            let value = replaceValuesInDepth(value, config);
            Some(value)
        }
        | None => None
    }
};

let getExn = (property) => {
    let value = getOptional(property);
    Belt.Option.getExn(value);
}