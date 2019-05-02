---
id: contributors-development-environment
title: Development environment
---

Setting up the development environment for contributing to Granary is easy. First you'll clone the repo, which is an obvious step. The fun part is having the same environment as every other developers, and the same as the CI. This is easily achievable thanks to Docker.

## Starting a dockerized shell

You can spin up a dockerized shell environment, with ports exposed and the local `$PWD` mounted, using:

```shell
make contributors-shell
```

## Building the docker image

> `stovelabs/granary-contributors` is available at [Docker Hub](https://hub.docker.com/r/stovelabs/granary-contributors) as well, which means you don't need to build it yourself before using it, feel free to **skip this part, unless you know what you're doing**

Granary CI setup & dev setup uses the same docker image for consistency purposes. You can build it using:

```shell
make contributors-build-image
```

## Useful commands

#### Build the CLI

```shell
npm run build
```

```shell
npm run build:watch
```

#### Run tests
```shell
npm run test
```

```shell
npm run test:watch
```

#### Link the CLI executable for development

> ⚠️ Run this outside of the docker container, on your own machine. Might require sudo permissions for linking.

```shell
npm link 
granary --version
```