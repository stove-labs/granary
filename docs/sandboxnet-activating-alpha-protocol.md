---
id: sandboxnet-activating-alpha-protocol
title: Activating the Alpha protocol
---

Sandboxed node comes with exactly one block on the chain - *the genesis block*. You can check it out using the `tezos-client`:

```zsh
granary client - rpc get "/chains/main/blocks/head"
```

At this moment, our chain runs a *dummy economic protocol*, called genesis. What we actually want, is to activate the latest protocol that's available on the live zeronet/alphanet/mainnet, otherwise basic features such as transfers between accounts, would not be possible.

## Quick start (relatively *quick*)

> ⚠️ In the upcoming release the following process will be automated

```zsh
# Import the activator secret key
granary client - import secret key "activator" "unencrypted:edsk31vznjHSSpGExDMHYASz45VZqXN4DPxvsa4hAyY8dHM28cZzp6"

# Create protocol_parameters.json in your project
{ 
    "bootstrap_accounts": [
        [ "edpkuBknW28nW72KG6RoHtYW7p12T6GKc7nAbwYX5m8Wd9sDVC9yav", "4000000000000" ]
    ],
    "time_between_blocks" : [ "1", "0" ],
    "blocks_per_roll_snapshot" : 4,
    "blocks_per_cycle" : 8,
    "preserved_cycles" : 2,
    "proof_of_work_threshold": "-1"
}

# Activate the alpha protocol using the activator key
granary client - "--block genesis activate protocol ProtoALphaALphaALphaALphaALphaALphaALphaALphaDdp3zK with fitness 1 and key activator and parameters $PWD/protocol_parameters.json --timestamp $(TZ='AAA+1' date +%FT%TZ)"

# Import a secret key for the account 
# specified in protocol_parameters.json's bootstrap_accounts
granary client - import secret key "bootstrap1" "unencrypted:edsk3gUfUPyBSfrS9CCgmCiQsTCHGkviBDusMxDJstF
tojtc1zcpsh"

# Our bootstrapped account also has baking rights right away,
# so we bake a new block with the protocol activation
granary client - bake for "bootstrap1"

# Confirm that we have a new block with the alpha protocol
granary client - rpc get "/chains/main/blocks/head"
```
---
## Who can activate protocols?

Activations on top of the *genesis* block/protocol, have to be signed by a private key, that belongs to the public key specified in `.granary/node/sandbox.json` as `genesis_pubkey`:

```js
{
    "genesis_pubkey": "edpkuSLWfVU1Vq7Jg9FucPyKmma6otcMHac9zG4oU1KMHSTBpJuGQ2"
}
```

### Importing an activator account

#### Activator private key
> This may change according to your `sandbox.json`'s `genesis_pubkey`.

`encrypted:edsk31vznjHSSpGExDMHYASz45VZqXN4DPxvsa4hAyY8dHM28cZzp6`

#### Import the activator account
```zsh
granary client - import secret key "activator" "unencrypted:edsk31vznjHSSpGExDMHYASz45VZqXN4DPxvsa4hAyY8dHM28cZzp6"
```

#### Verifying the account import
`Public Key` should match the `genesis_pubkey` from `sandbox.json`.
```zsh
granary client - show address "activator" -S
Hash: tz1TGu6TN5GSez2ndXXeDX6LgUDvLzPLqgYV
Public Key: edpkuSLWfVU1Vq7Jg9FucPyKmma6otcMHac9zG4oU1KMHSTBpJuGQ2
Secret Key: unencrypted:edsk31vznjHSSpGExDMHYASz45VZqXN4DPxvsa4hAyY8dHM28cZzp6
```

---
## Alpha protocol parameters

Alpha protocol can be customized by a `protocol_parameters.json` file.

### Notable configuration options

<div class="configuration-table">

|Key |Description |Example |
|:---|:---|:---|
|`bootstrap_accounts`| Public key and an amount of XTZ available |`["edpkuBknW28nW72KG6RoHtYW7p12T6GKc7nAbwYX5m8Wd9sDVC9yav", "4000000000000"]`

</div>

### Example `protocol_parameters.json`

```js
{ 
    "bootstrap_accounts": [
        [ "edpkuBknW28nW72KG6RoHtYW7p12T6GKc7nAbwYX5m8Wd9sDVC9yav", "4000000000000" ]
    ],
    "time_between_blocks" : [ "1", "0" ],
    "blocks_per_roll_snapshot" : 4,
    "blocks_per_cycle" : 8,
    "preserved_cycles" : 2,
    "proof_of_work_threshold": "-1"
}
```

## Faucet

Once you've injected the alpha protocol with a set of *protocol parameters*, you can simulate a faucet by transferring XTZ from one of the rich bootstrap accounts, to any account that you import to your client after activating the protocol.

> ⚠️ You **will not** be able to import accounts from the [Alphanet faucet](https://faucet.tzalpha.net/)

```zsh
# Import the bootstrapped account, if we haven't dont that yet
granary client - import secret key "bootstrap1" "unencrypted:edsk3gUfUPyBSfrS9CCgmCiQsTCHGkviBDusMxDJstF
tojtc1zcpsh"

# Import a new account called 'alice'
granary client - import secret key "alice" "unencrypted:edsk39qAm1fiMjgmPkw1EgQYkMzkJezLNewd7PLNHTkr6w9XA2zdfo"

# Client will wait for the operation to be included into the chain, so we start it in the background with '&'
granary client - transfer 1000 from bootstrap1 to alice --burn-cap 0.257 &

# Bake a new block to include the transfer operation from above
granary client - bake for bootstrap1

# Outputs 1000 XTZ
granary client - get balance for alice
```