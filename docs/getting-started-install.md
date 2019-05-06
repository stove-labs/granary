---
id: getting-started-install
title: Installation
---

To install Granary, you need [NodeJS](https://nodejs.org/en/) installed on your machine, we recommend using at least `v11.4+`. NodeJS comes standard with a package manager called [NPM](https://www.npmjs.com/) which can be used to install Granary - just run the command below to install the latest `pre-alpha` version cli:

## CLI installation

```shell
npm install --global @stove-labs/granary@pre-alpha
```

> ⚠️ `--global` flag installs Granary globaly on your system, it might require `sudo` permissions depending on your installation of NodeJS.

Confirm that your installation was successfull by checking for the `--version` of Granary:

```shell
granary --version
> 1.0.0-pre-alpha.12 #example version
```

## Docker setup

The only additional dependency is [Docker 🐳](https://www.docker.com/get-started), which Granary uses to encapsulate all of the tools you might need for development. We personally run `Docker Desktop v2.x.x.x`

> ⚠️ Don't forget to start Docker before trying any other commands.

After installing, you can confirm that your Docker socket is available by running:
```shell
curl --unix-socket /var/run/docker.sock http://localhost/v1.37/ve
rsion
```