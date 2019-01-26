# Tezos Environment Manager 🏖

#### This project is a WIP, contact [t.me/maht0rz](t.me/maht0rz) for any questions

Tezos environment manager provides a seamless way to develop apps locally for mainstream networks such as `alphanet`, while enabling **sandboxed private network** in form of `sandboxnet`

## Setup

1. Choose an environment (network), pick just one

        # Alphanet
        source ./env/tezos/alphanet.sh

        # Sandboxnet
        source ./env/tezos/sandboxnet.sh

2. Build the docker image
    > ⏱ This might take a while, be patient! ⏱ 

        make build

3. Start the node (baker/endorser/...) 

        make start

4. Open the interactive shell

    > ⚠️ All Tezos related commands will be ran inside this shell⚠️
        
        make shell

    🏖 In case you're running `sandboxnet`, run additional commands inside the shell, to initialize a sandbox version of `tezos-client`, and to activate the same protocol as `alphanet`:
    
        # Run this each time after `make shell` if you're using sandboxnet
        eval `./tezos/src/bin_client/tezos-init-sandboxed-client.sh 1` 
        tezos-activate-alpha

## Example with [sotez](https://www.npmjs.com/package/sotez)

You can find an attached example of `sotez.node.query` in the `examples/` folder. 

#### Running the example

> You will need a recent version of NodeJS installed locally

1. Install dependencies
        
        npm install

2. Run the example

        npm run start

## Using Sandboxnet

1. List all available sandbox addresses

        tezos-client list known addresses

2. Create a transfer using tezos-client

        tezos-client transfer 1000 from bootstrap1 to bootstrap2 &

3. Bake a new block in the sanbox environment, for the transaction to be included in the chain

        tezos-client bake for bootstrap1

4. Check your balance

        tezos-client get balance for bootstrap2



## Using Alphanet

1. Get an account from https://faucet.tzalpha.net/, you'll get a json file, that you need to move to your shell. You can use vim inside `make shell`.

        // e.g. tz1ZsLVBG....
        vim my_public_tz_address_goes_here.json 

2. Activate your account

        tezos-client activate account <your-name> with json-created-in-step-1.json

3. Run commands as you wish, e.g. check your balance:

        tezos-client get balance for <your-name>

