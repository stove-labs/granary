type commander;
[@bs.module] external commander: commander = "commander";

[@bs.send] external version: (commander, string, option(string)) => commander = "";

type argv = array(string);
[@bs.send] external parse: (commander, argv) => commander = "";

[@bs.send] external usage: (commander, string) => commander = "";

[@bs.send] external command: (commander, string) => commander = "";
[@bs.send] external forwardedCommand: (commander, string, string) => commander = "";

type commanderAction = unit => unit;
[@bs.send] external action: (commander, commanderAction) => commander = "";

[@bs.send] external description: (commander, string) => commander = "";