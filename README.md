# Tezos Environment Manager 🏖

#### This project is a WIP, contact [t.me/maht0rz](t.me/maht0rz) for any questions

Tezos environment manager provides a seamless way to **develop smart contracts and dapps locally** for public networks such as `alphanet`, and private networks such as `sandboxnet` 

> `alphanet` environment is currently **WIP**

> Sections of readme with '🏖 ' are only applicable to the `sandboxnet` environment

## 👀  Quick overview

### Sending a transaction using `sandboxnet`
![](https://gateway.pinata.cloud/ipfs/QmTTwU6vZDBbreuuHd4e1LiAEXL2V455785cLvEnMnJ1i7)

### Deploying a ReasonML smart contract at `sandboxnet`
![](https://gateway.pinata.cloud/ipfs/QmNqQAnU4Y41jg4xquGje2cfKVEHjrnDtdvkND3zsGP5Mw)

## 🛠 Setup

**1. Choose an environment / network**

```bash
source ./env/tezos/sandboxnet.sh
```

**2. Build the docker images**
> ⏱ This might take a while, be patient! ⏱ 

```bash
make build
```

**3. Start the apropriate node**
        
```bash
make start
```

**4. Open the interactive shell with `tezos-client` and `liquidity` preconfigured**
> ⚠️ &nbsp; All Tezos related commands will be ran inside this shell
```bash
make client
```
        

## 🕹 Useful commands

### Miscelanious

#### Initializing the sandbox client
When  you start your `sandboxnet` node for the first time, make sure to initialize your client in order to get a handful of testing accounts to play with.
```
init-client
```

#### Converting a ReasonML smart contract into Liquidity [Experimental 🚨] 
> Liquidity smart contracts are implemented using a subset of OCaml syntax. We can use `refmt` to convert ReasonML code to OCaml code, 
but not every valid ReasonML code is a valid Liquidity contract.
```bash
refmt --parse re --print ml tezos-environment-manager/src/contracts/simple.re > tezos-environment-manager/src/contracts/simple.liq
```

### Client


#### List all available addresses
```bash
tezos-client list known addresses
```

#### Create a transfer using tezos-client
```bash
tezos-client transfer 1000 from bootstrap1 to bootstrap2 &
```

#### 🏖  &nbsp; Bake a new block
```bash
tezos-client bake for bootstrap1
```
#### Check your balance
```bash
tezos-client get balance for bootstrap2
```

### Contracts

> `simple.re` example has to be converted into liquidity first, see above.

#### Forging a contract deployment

> ⚠️&nbsp;`$NODE_URL` is set based on your environment automatically

``` bash
liquidity \
        --tezos-node $NODE_URL \
        --amount 2tz \
        --fee 1tz \
        --delegatable \
        --source tz1KqTpEZ7Yob7QbPE4Hy4Wo8fHG8LhKxZSx \
        tezos-environment-manager/src/contracts/simple.liq \
        --forge-deploy > contract_deployment_op.bytes
```

#### Signing a forged operation
```bash
tezos-client sign bytes 0x03$(cat ./contract_deployment_op.bytes) for bootstrap1
```

#### Injecting a signed operation
```bash
liquidity \
   --tezos-node $NODE_URL \
   --signature signature_goes_here \
   --inject contract_deployment_op.bytes
```

> 🏖 &nbsp;Don't forget to bake a new block after injecting an operation

#### Getting a receipt for an injected operation
You can use the following command, to get the originated address of your contract. (e.g. *KT1GtgAL2VV2R9McZmhPxTp5syB4ysyG2XL1*)
```bash
tezos-client get receipt for operation_hash_goes_here
```


## 🔍 Examples

### RPC with [Sotez](https://www.npmjs.com/package/sotez)

You can find an attached example of `sotez.node.query` in the `examples/` folder. 

#### Running the examples

> You will need a recent version of NodeJS installed locally

1. Install dependencies
```bash
npm install
```
2. Run the example
```bash
# Get current block/head
npm run head
# Get storage of a deployed smart contract (simple.re)
# Make sure your contract is deployed and the example address is up-to-date
npm run contract
```

## 🚗 Roadmap

- Automated contract deployment & testing in ReasonML / OCaml & bs-jest
- Alphanet support
