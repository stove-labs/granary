type dockerode;
[@bs.module][@bs.new] external dockerode: unit => dockerode = "dockerode";


[@bs.deriving abstract]
type portBinding = {
    [@bs.as "HostPort"] hostPort: string,
};

[@bs.deriving abstract]
type hostConfiguration = {
    [@bs.as "Binds"] volumeBindings: option(array(string)),
    [@bs.as "PortBindings"] portBindings: option(Js.Dict.t(array(portBinding))),
    [@bs.as "NetworkMode"] networkMode: option(string)
};

[@bs.deriving abstract]
type createContainerOptions = {
    [@bs.as "Image"] image: option(string),
    [@bs.as "Cmd"] cmd: option(array(string)),
    [@bs.as "HostConfig"] hostConfig: option(hostConfiguration),
    [@bs.as "Tty"] tty: option(bool),
    [@bs.as "ExposedPorts"] exposedPorts: option(Js.Dict.t(Js.Dict.t(unit))),
    name: option(string)
};

type container;
[@bs.send] external start: (container, unit) => Js.Promise.t(container) = "";
[@bs.send] external stop: (container, unit) => Js.Promise.t(container) = "";
[@bs.send] external remove: (container, unit) => Js.Promise.t(container) = "";


[@bs.send] external createContainer: (dockerode, createContainerOptions) => Js.Promise.t(container) = "";
[@bs.send] external getContainer: (dockerode, string) => container = "";
type processInputStream;
[@bs.send] external run: (dockerode, string, array(string), processInputStream, createContainerOptions) => Js.Promise.t(container) = "";

[@bs.deriving abstract]
type containerInfo = {
    [@bs.as "Names"] names: array(string),
};
type containerList = array(containerInfo);
[@bs.send] external listContainers: (dockerode) => Js.Promise.t(containerList) = "";

type network;
[@bs.deriving abstract]
type networkConnectOptions = {
    [@bs.as "Container"] container: string,
    id: string
};
[@bs.send] external getNetwork: (dockerode, string) => network = "";
[@bs.send] external connect: (network, networkConnectOptions) => Js.Promise.t(unit) = ""



