---
id: getting-started-install
title: Installation
---

To install Granary, you need [NodeJS](https://nodejs.org/en/) installed on your machine, we recommend using at least `v11.4+`. NodeJS comes standard with a package manager called [NPM](https://www.npmjs.com/) which can be used to install Granary - just run the command below to install the latest `pre-alpha` version cli, or scroll further down for the **starter kit setup**.

## CLI installation

Using NPM:
```zsh
npm install --global --unsafe-perm @stove-labs/granary@pre-alpha
```

Using Yarn:
```zsh
yarn global add @stove-labs/granary@pre-alpha
```

> ⚠️ `--global` flag installs Granary globaly on your system, it might require `sudo` permissions depending on your installation of NodeJS.

Confirm that your installation was successfull by checking for the `--version` of Granary:

```zsh
granary --version
> 1.0.0-pre-alpha.12 #example version
```

## Docker setup

The only additional dependency is [Docker 🐳](https://www.docker.com/get-started), which Granary uses to encapsulate all of the tools you might need for development. We personally run `Docker Desktop v2.x.x.x`

> ⚠️ Don't forget to start Docker before trying any other commands.

After installing, you can confirm that your Docker socket is available by running:
```zsh
curl --unix-socket /var/run/docker.sock http://localhost/v1.37/ve
rsion
```

## Starter kit

If you're starting a new project, and you already have NPM & Docker installed, you can get up & running quiclky using the [Granary's starter kit](https://github.com/stove-labs/granary-starter-kit)

## Troubleshooting common issues

Certain issues might appear while using the pre-alpha version of Granary, don't worry, those will be fixed down the line. For now, if you encounter any of the following errors, here's how you can get rid of them.

#### Container name is already in use
*Error:*
```zsh
(node:66975) UnhandledPromiseRejectionWarning: Error: (HTTP code 409) unexpected - Conflict. The container name "/granary-tezos-node-s
andbox" is already in use by container "61381b485d074175856f741adeebaa0e60fde9876fdabca909467d2068c9fe01". You have to remove (or rena
me) that container to be able to reuse that name.
```

*Solution:*
```zsh
# Remove the container all together, and try again
docker rm --force granary-tezos-node-sandbox
```

#### Network name already exists
*Error:*
```zsh
Updating image: stovelabs/granary-tezos-node-sandboxnet
(node:67151) UnhandledPromiseRejectionWarning: Error: (HTTP code 409) unexpected - network with name granary already exists 
```

*Solution:*

This can happen if you run `granary init` multiple times, as it tries to create a new docker network for you to use. Don't worry, it's harmless and will be patched in the upcoming releases.
