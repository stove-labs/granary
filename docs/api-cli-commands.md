---
id: api-cli-commands
title: CLI Commands
---

List of all available CLI commands for granary, including their required & optional arguments.

> ⚠️ Arguments for the cli are either &lt;required&gt; or [optional]



## Version

Displays the currently installed CLI version.

```shell
granary --version
```

## Help
Displays help & useful links.

```shell
granary --help
```

### Help for sub-commands

Displays detailed help for the given sub-command, e.g. `config`.

```shell
granary [command] --help
```
---
## Config
---
Provides a way to manipulate the Granary config for your project, and adds an option to set a config path when executing CLI commands.

### Show all

```shell
granary config show
```

### Show property

```shell
granary config show [property]
```

### Set property

> ⚠️ You can omit the value when setting a property to delete it instead.

> ⚠️ All config values are currently being handled as strings, this may change in future releases.

```shell
granary config set <property> [value]
```

### Setting a custom config path

```shell
export GRANARY_CONFIG=custom-config.json 
granary config show
```

## Init

Scaffolds both Node & Client's data directories and setups Docker for use with Granary

```shell
granary init
```

---
## Node
---

Manipulate the sandboxed Tezos node.

### Init
```shell
granary node init
```

### Start
```shell
granary node start
```

### Stop
```shell
granary node stop
```

### Clean
```shell
granary node clean
```

---
## Client
---
Pass-through commands to a pre-configured tezos-client.

### Init
```shell
granary client init
```

### Forwards commands
```shell
granary client - list known addresses
```

### Clean
```shell
granary client clean
```
