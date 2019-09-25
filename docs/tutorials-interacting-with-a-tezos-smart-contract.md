---
id: tutorials-interacting-with-a-tezos-smart-contract
title: Interacting with a Tezos smart contract on Alphanet
---
Author: [Matej Šima](https://github.com/maht0rz/)

In [the previous tutorial](tutorials-deploying-a-tezos-smart-contract-to-alphanet.md) we've deployed a smart contract to Alphanet, it's address at the time of the writing of the tutorial was **KT1JfYDaNGwxVZB36SqeydVdBCVh6EVu93bP**

> Please note that the addresses and block explorer links are only valid until the next Alphanet restart

## Quick look at our existing contract

Our contract doesn't do much more than storing the parameter that we send, in it's storage. You can see the [deployed contract here](https://alphanet.tzscan.io/KT1JfYDaNGwxVZB36SqeydVdBCVh6EVu93bP).
Our goal is to invoke the contract and replace it's storage value with the value `7` - which is an int in the eyes of the contract.

### Addresses of the existing wallets / contracts

If you followed the previous tutorial, your Granary client already knows the addresses of our testing wallet `alice` and our contract `int_storage`. Let's take a quick look at how it looks like in our client:

```zsh
granary client - list known contracts
```

<img src="/granary/img/tutorials/deploy-a-tezos-smart-contract-to-alphanet/list-contracts.png" />
<div style="opacity: 0.7; text-align: center; font-size: 12px; margin-top:-24px;">
Listing existing contracts
</div>
<br/>

If you haven't followed the previous tutorial, you can load the `int_storage` contract to your client with the following command, however you will need to [obtain your own faucet wallet](tutorials-deploying-a-tezos-smart-contract-to-alphanet.md#obtaining-an-identity-wallet).

```zsh
granary client - remember contract int_storage KT1JfYDaNGwxVZB36SqeydVdBCVh6EVu93bP
```

> Wondering why you need a new faucet wallet? Well, if you haven't obtained one in the previous tutorial, you will need an on-chain identity to invoke the contract.

---

## Invoking the contract

Contracts on Tezos are invoked by a transaction sent to their respective address, where the transaction may or may not include additional arguments. There are gas costs, burns and fees associated with invoking a contract which are paid by the wallet that signed the transaction.

### Preparing a transaction

Easiest way to send a transaction with appropriate configuration (gas, burns and fees), is to run a dry-run simulation from the client. We want to transfer `0tz` from `alice` to `int_storage` with an integer argument of `7`.
```zsh
granary client - transfer 0 from alice to int_storage --dry-run --arg '7'
```

<img src="/granary/img/tutorials/deploy-a-tezos-smart-contract-to-alphanet/invocation-dry-run.png" />
<div style="opacity: 0.7; text-align: center; font-size: 12px; margin-top:-24px;">
Dry running a transaction
</div>
<br/>

Let's take a closer look at the dry-run output:

**Fee to the baker:** *ꜩ0.001417*

A minimal fee that's paid to the baker which includes our operation.

**Gas limit:** *11599*

Gas consumed by each instruction of our contract's code, gas consumed increases the fee to the baker according to a [predefined formula](http://tezos.gitlab.io/mainnet/protocols/004_Pt24m4xi.html#gas-and-fees).

**Balance updates**

This section outlines which wallets will be affected by our operation, we can see that the fees are paid by `alice` *(tz1...3W4i)*.

**Parameter & Updated storage:** *7*

We've sent our transaction with the argument of `7`, and our contract has update it's storage accordingly.

<br/>

### Sending a live Alphanet transaction

So far we've tried to dry-run our transaction and it went well, we're ready to inject it into the Alphanet. Let's run it again, this time without the `--dry-run`:

```zsh
granary client - transfer 0 from alice to int_storage --arg '7'
```

*Unfortunately, in my case the client reported the transaction as failed -  or at least it's simulation. This gives us an opportunity to explore additional means of figuring out if the transaction/operation has been included or not.*

<img src="/granary/img/tutorials/deploy-a-tezos-smart-contract-to-alphanet/transaction-error.png" />
<div style="opacity: 0.7; text-align: center; font-size: 12px; margin-top:-24px;">
Failed transfer simulation
</div>
<br/>

### Looking up our operation on the block explorer

> Please consider that this contract has no restraints on who can invoke it. The storage state might have changed since this tutorial was published.

We can see our operation included [here](https://alphanet.tzscan.io/BMLp7BDT5BxN5UnkSiGgfH8etKQyh79ZL3reTZ1a1yzaCdo36g4).

**Operation:** *opEBoZqbKNc2AyyQGkX2Y13f9BtwFnzByrrsZwrWTaJtPJh7BRV*

**Included in block:** *BMLp7BDT5BxN5UnkSiGgfH8etKQyh79ZL3reTZ1a1yzaCdo36g4*

**Fees paid:** *1.417 mꜩ*

To wrap things up, you can take a look at the contract's storage after the operation has been included:


<img src="/granary/img/tutorials/deploy-a-tezos-smart-contract-to-alphanet/new-storage.png" />
<br/>
<div style="opacity: 0.7; text-align: center; font-size: 12px; margin-top:-24px;">
Updated storage after the transaction
</div>

<br/>

**That's it, you've successfully invoked a contract and updated it's storage!**