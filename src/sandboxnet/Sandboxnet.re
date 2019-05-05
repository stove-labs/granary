open Data;

let dirname: string = [%bs.raw {|__dirname|}];
let nodeBaseInitFilePath: string = dirname ++ "/node/init";
let nodeInitDestinationPath = Config.getExn("data.networks.<network>.nodeFolder");

let nodeInitFiles = [
    "config.json",
    "identity.json",
    "sandbox.json",
    "version.json"
];

let clientInitFiles = [];
let clientBaseInitFilePath = "";
let clientInitDestinationPath = Config.getExn("data.networks.<network>.clientFolder");

let init = () => {
    Data.init(nodeBaseInitFilePath, nodeInitDestinationPath, nodeInitFiles);
    Data.init(clientBaseInitFilePath, clientInitDestinationPath, clientInitFiles);
}