type config;
type configStore = Js.t({
    .
    [@bs.set] all: config,
    get: (string) => string
});

type configOptions = Js.t({
    .
    globalConfigPath: option(bool),
    configPath: option(string)
});
[@bs.module][@bs.new] external configStore: (string, config, configOptions) => configStore = "configstore";
[@bs.send] external get: (configStore, string) => option(string) = "";
[@bs.send] external set: (configStore, string, string) => unit = "";
[@bs.send] external delete: (configStore, string) => unit = "";