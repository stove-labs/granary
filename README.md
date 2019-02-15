# Tezos Environment Manager 🏖

#### This project is a WIP, contact [t.me/maht0rz](t.me/maht0rz) for any questions

Tezos environment manager provides a seamless way to **develop smart contracts and dapps locally** for public networks such as `alphanet`, and private networks such as `sandboxnet` 

> `alphanet` environment is currently **WIP**

> Sections of readme with '🏖 ' are only applicable to the `sandboxnet` environment

## 👀  Quick overview

### Block explorer for `sandboxnet`
![](https://gateway.pinata.cloud/ipfs/QmX931XSq9KVmPD9y5C7Fqmjfa5uU99rYZvguCXGC33rbw)

### Sending a transaction using `sandboxnet`
![](https://gateway.pinata.cloud/ipfs/QmTTwU6vZDBbreuuHd4e1LiAEXL2V455785cLvEnMnJ1i7)

### Deploying a ReasonML smart contract at `sandboxnet`
![](https://gateway.pinata.cloud/ipfs/QmS11bjtHwS7ynZztXw1uaCJgTLs8kBJLFU9sx77HsAKsC)

## 🛠 Setup

**1. Choose an environment / network**

```bash
source ./env/sandboxnet.sh
```

**2. Start the apropriate tezos node**
```bash
make start
```

**3. Open the interactive shell with `tezos-client` and `liquidity` preconfigured**
> ⚠️ &nbsp; All Tezos related commands will be ran inside this shell
```bash
make client
```

Inside the newly started shell, initialize the `tezos-client` by running:

```bash
# Run this inside the shell created by make client
init-client
```

> ⚠️ `tezos-client` needs to be initialised only once, unless you delete/restart your bootstrapped network.

**4. Confirm the setup by navigating to local TzScan**

TzScan is available at [http://localhost:8000/](http://localhost:8000/). 

You should see your sandboxed network with *no transactions at block 1*, baked by *God*.


        
## 🕹 Useful commands

### Miscelanious

#### Initializing the sandbox client
When  you start your `sandboxnet` node for the first time, make sure to initialize your client in order to get a handful of testing accounts to play with.
```
init-client
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

You can find an example smart contract, in all three supported syntaxes: `.liq` `.reliq` `.tz`, under [`src/contracts/`](https://github.com/maht0rz/tezos-environment-manager/tree/master/src/contracts)

> ⚠️ Prievously we've encouraged the use of `refmt` to convert `.re` files into `.liq` files, but liquidity now supports ReasonML syntax out of the box, you can learn more [here](https://github.com/lefessan/liquidity/blob/2a408f23efadcecf64274539d540a08c0ac9cb58/docs/sphinx/src/reference/liquidity.rst#reasonml-syntax).


#### Simulating a smart contract execution
```bash
liquidity \
    --tezos-node $NODE_URL \
    --amount 2tz \
    tezos-environment-manager/src/contracts/simple.liq \
    --run main '5' '1'
```

> The command above, will test our `simple.liq` smart contract, by calling it's entry point `main`, with it's single argument as `1`, while setting it's initial storage value to `5`.

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

#### Display private key for an account
```bash
tezos-client show address  bootstrap1 -S
```

#### Using ReasonML for Liquidity contracts

Liquidity supports syntax of ReasonML in the form of `.reliq` files, instead of the traditional `.liq` files.

If your file has a `.reliq` extension, it'll be automatically parsed as ReasonML.

```bash
liquidity \
    --tezos-node $NODE_URL \
    --amount 2tz \
    tezos-environment-manager/src/contracts/simple.reliq \
    --run main '5' '1'
```

## 🔍 Block explorer 

Once your local environment is up & running, you can 
visit the block explorer *(tzscan)* at [`http://localhost:8000`](http://localhost:8000)

Don't forget to bake a new block after you inject any operations using the client.

> 👷‍ Listing of all existing blocks does not seem to work at the moment, however dashboard displays blocks as it should

## 📚 Examples

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
# Get storage of a deployed smart contract
# Make sure your contract is deployed and the example address is up-to-date
npm run contract
```

## 🚗 Roadmap

- Automated contract deployment & testing in ReasonML / OCaml & bs-jest
- Alphanet support
