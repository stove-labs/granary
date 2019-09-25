---
id: tutorials-deploying-ligo-taco-to-sandbox
title: Deploying the Ligo Taco Shop Smart Contract to a local Sandbox
---
Author: [István Deák](http://github.com/dexterslabor)

In this tutorial we'll learn how to compile a Ligo smart contract to Michelson code and to deploy it to a local Sandbox, utilizing Granary's built in tezos-client.

> 🆒 You can find an example project [here](https://github.com/stove-labs/granary/tree/features/examples/examples/deploying_ligo) and fast forward in less than 2 minutes. 

> In order to run example commands in this tutorial, you will have to **install** [ Granary](getting-started-install.md) and [ Ligo](https://ligolang.org/docs/next/setup/installation/). 


# Setting up the local environment

First we need to initalise Granary in our project folder.

```zsh
# Initialise Granary
granary init
# Start the node
granary node start &
```
> For troubleshooting, visit
[docs-common-issues](https://stove-labs.github.io/granary/docs/getting-started-install#troubleshooting-common-issues).


## Activating the protocol
> ℹ️ There is no need to set the network to *Sandbox*, because that is the default setting.

The *Sandboxed node* is in its current state not very useful to us, because it runs a dummy economic protocol, called genesis. What we'll do next is to activate the latest protocol that is used on mainnet. Read [this](https://stove-labs.github.io/granary/docs/sandboxnet-activating-a-protocol) to learn more about activation.

We retrieve the list of availabe protocols with:
```zsh
granary client - rpc get /protocols
```


<img src="/granary/img/tutorials/deploy-a-ligo-smart-contract-in-local-sandbox/available-protocols.png" />
<div style="opacity: 0.7; text-align: center; font-size: 12px; margin-top:-24px;">
Available protocols in our local Sandboxed node.
</div>

<br/>

We want to activate **Athens protocol** with the hash **Pt24m4xiPbLDhVgVfABUjirbmda3yohdN82Sp9FeuAXJ4eV9otd**, but before doing so, save the following to `protocol_parameters.json`.

```json
{
    "bootstrap_accounts": [
        [
            "edpkuBknW28nW72KG6RoHtYW7p12T6GKc7nAbwYX5m8Wd9sDVC9yav",
            "4000000000000"
        ]
    ],
    "time_between_blocks": [
        "1",
        "0"
    ],
    "blocks_per_roll_snapshot": 4,
    "blocks_per_cycle": 8,
    "preserved_cycles": 2,
    "proof_of_work_threshold": "-1"
}
```

```zsh
# Import the activator secret key
granary client - import secret key activator unencrypted:edsk31vznjHSSpGExDMHYASz45VZqXN4DPxvsa4hAyY8dHM28cZzp6 --force
# Activate Athens protocol
granary client - activate protocol Pt24m4xiPbLDhVgVfABUjirbmda3yohdN82Sp9FeuAXJ4eV9otd with fitness 1 and key activator and parameters $PWD/protocol_parameters.json --timestamp $(TZ='AAA+1' date +%FT%TZ)
# Import key for bootstrapped account
granary client - import secret key "bootstrap1" "unencrypted:edsk3gUfUPyBSfrS9CCgmCiQsTCHGkviBDusMxDJstFtojtc1zcpsh"
# We bake a new block with the bootstrapped account
granary client - bake for bootstrap1
```

Congratulations, you have a local sandboxed node running with the Athens protocol! We need to prepare the Taco Shop smart contract for the network, because it is written in a high-level language called [Ligo](https://www.ligolang.org) and the Tezos node accepts [Michelson](https://www.michelson-lang.com/) code.

# Compiling Ligo to Michelson
The story of Pedro, *artisan taco chef*, who has decided to utilize Tezos blockchain to  manage supply, pricing & sales of his delicious tacos to his customers can be read [here](https://ligolang.org/docs/tutorials/get-started/tezos-taco-shop-smart-contract/).


## Contract Code
We will use the [finalized contract](https://ligolang.org/docs/tutorials/get-started/tezos-taco-shop-payout/#finalizing-the-contract) from the Ligo tutorial. In your project folder, copy the following to `taco-shop.ligo`

```
type taco_supply is record
    current_stock : nat;
    max_price : tez;
end
type taco_shop_storage is map(nat, taco_supply);

const ownerAddress: address = "tz1TGu6TN5GSez2ndXXeDX6LgUDvLzPLqgYV";

function buy_taco (const taco_kind_index: nat ; var taco_shop_storage : taco_shop_storage) : (list(operation) * taco_shop_storage) is
  begin
    // Retrieve the taco_kind from the contract's storage
    const taco_kind : taco_supply = get_force(taco_kind_index, taco_shop_storage);
    
    const current_purchase_price : tez = taco_kind.max_price / taco_kind.current_stock;

    if amount =/= current_purchase_price then
      // we won't sell tacos if the amount isn't correct
      fail("Sorry, the taco you're trying to purchase has a different price");
    else
      // Decrease the stock by 1n, because we've just sold one
      taco_kind.current_stock := abs(taco_kind.current_stock - 1n);

    // Update the storage with the refreshed taco_kind
    taco_shop_storage[taco_kind_index] := taco_kind;

    const receiver : contract(unit) = get_contract(ownerAddress);
    const payoutOperation : operation = transaction(unit, amount, receiver);
    const operations : list(operation) = list
      payoutOperation
    end;

  end with (operations, taco_shop_storage)
```

Use Ligo CLI to compile the contract. Learn more [here](https://ligolang.org/docs/next/api-cli-commands/#compiling-a-contract).

```zsh 
ligo compile-contract taco-shop.ligo buy_taco
```

> Notice that **buy_taco** is the entry point for this smart contract.

Copy the CLI output from your terminal to `taco-shop.tz`

<img src="/granary/img/tutorials/deploy-a-ligo-smart-contract-in-local-sandbox/michelson-smart-contract.png" />
<div style="opacity: 0.7; text-align: center; font-size: 12px; margin-top:-24px;">
This is the Michelson code of the Taco Shop.
</div>
<br/>

> ℹ️ **\*.tz** is used for Michelson code.

> ⚠️ If you are saving the output through your terminal on **OS X**, make sure to remove the additional '\r' line-breaks. This is a nasty bug and makes the ouput incompatible with Linux systems. Find a work-around script [here](https://github.com/stove-labs/granary/blob/features/examples/examples/deploying_ligo/contracts/compile-contract.sh#L7).

>🎓Why do we need to compile more than the contract code? 

Let's examine the first 3 rows of the Michelson code.
```
{ parameter nat ;
  storage (map nat (pair nat mutez)) ;
  code { {} ;
```  
We can see that the *parameter* is quite simple and it is not necessary to run `ligo compile-parameter ...`, however the types expected for *storage* is more complex and we will compile that in the next section.
 
## Initial Storage
From the [tutorial](https://ligolang.org/docs/tutorials/get-started/tezos-taco-shop-payout/#finalizing-the-contract) we take the initial storage of `50`x `el clásico` tacos.

```sh
# Compile initiale storage
ligo compile-storage taco-shop.ligo buy_taco "map 1n -> record current_stock = 50n; max_price = 50000000mtz; end; end"
# { Elt 1 (Pair 50 50000000) }
```

<img src="/granary/img/tutorials/deploy-a-ligo-smart-contract-in-local-sandbox/compile-storage.png" />
<div style="opacity: 0.7; text-align: center; font-size: 12px; margin-top:-24px;">
The storage types can look quite different between Ligo and Michelson.
</div>
<br/>

We will use this output when originating the smart contract.


## Originating the smart contract
Originating the smart contract in a local sandbox is basically a 2-step-process. First we inject the *operation* and then we *manually bake* the next block.
```zsh
# Inject operation
granary client - originate contract taco-shop for bootstrap1 transferring 0 from bootstrap1 running $PWD/contracts/taco-shop.tz --init '"{ Elt 1 (Pair 50 50000000) }"' --burn-cap 2.356 --force &
# Manually bake new block
granary client - bake for bootstrap1
```

> ⚠️ Make sure to use the whitespace preserving '""' double quotes. For more complex types, such as strings and addresses, you will need to escape the quotes like [here](https://github.com/stove-labs/nft.stove-labs.com/blob/master/docs/index.html#L141).

Let's summarize the current state in the sandbox. We have deployed Pedro's digital Taco Shop and initialized his stock with 50 pieces of the *el clásico* type culinary. 

> 🤓 Bonus: Can you help Pedro to expand his offering, by adding the *especial del chef* type taco?

# Interacting with Pedro's store

Finally, Pedro's store is up and running and we can already smell the fresh tacos. We are getting quite hungry and want to buy our first taco by *invoking* the smart contract. This is just a fancy word for sending a transaction to the contract. This transaction *can* contain `tez` and/or `parameters`. The client uses the `--arg` flag.

Using the formula of the tutorial, we know that the minimum price depends on the available stock. Currently that should be at least `1 tez`. 
Luckily, we don't have to memorize the smart contract's address, because the client saved it for us under the name `taco-shop`.

```zsh
# Call the contract by transferring 1tez 
# and the parameter/arugment 1 for the taco type
granary client - transfer 1 from bootstrap1 to taco-shop --arg '1' --burn-cap 0.257 &
# Manually bake new block
granary client - bake for bootstrap1
```

Fantastic, enjoy your well deserved taco. We have set-up a local development environment, compiled an advanced smart contract from Ligo to Michelson and even deployed & interacted with it - everything in record time!

Please leave a comment on Twitter @stove_labs,because this is the best motivation for us. Stay tuned for more.