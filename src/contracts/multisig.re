[%%version 0.4];

type proposition = {
    destination: key_hash,
    amount: tez
};

type storage = {
    owners: set(address),
    owners_signed: set(address),
    last_proposition: option(proposition),
};

/* 
    Initialized storage with two accounts, bootstrap1 & bootstrap2
*/
[%%init let storage = {
    owners: Set([tz1KqTpEZ7Yob7QbPE4Hy4Wo8fHG8LhKxZSx: address, tz1gjaF81ZRRvdzjobyfVNsAeSC6PScjfQwN: address]),
    last_proposition: None,
    owners_signed: Set
}];

/* 
    If current transaction author is also an owner of this contract,
    let him move forward
*/
let can_call = (storage) => {
    let sender = Current.sender();
    Set.mem(sender, storage.owners)
};

/* 
    In case that someone tries calling the contract when he's not an owner,
    product an error message
*/
let fail_with_wrong_ownership = () => {
    Current.failwith("Only contract owners can propose new trasactions")
};

/* 
    Resets the storage state
*/
let delete_proposition = (storage, transactions) => {
    (transactions, {
        owners: storage.owners,
        last_proposition: None,
        owners_signed: Set
    })
};

/* 
    If you're an owner, you can remove the existing proposition
*/
[%%entry let delete_proposition = (parameter: unit, storage) => {
    if (can_call(storage)) {
        delete_proposition(storage, [])
    } else {
        Current.failwith("Only contract owners can sign transation proposals")
    }
}];

/* 
    If you're an owner, and all the required signatures are present,
    execute the proposal = send the transaction
*/
[%%entry let execute_proposition = (parameter: unit, storage) => {
    if (can_call(storage)) {
        /*
            Just checking a size of the set can be pretty risky,
            we leverage the fact that when a proposition is signed, the signature
            is not appended to the set if it is not unique
        */
        if (Set.size(storage.owners_signed) == Set.size(storage.owners)) {
            switch(storage.last_proposition) {
                | Some(proposition) => {
                    let transfer = Account.transfer(
                        ~dest = proposition.destination, 
                        ~amount = proposition.amount
                    );
                    delete_proposition(storage, [transfer]);
                }
                | None => Current.failwith("There is no proposition to execute")
            }
        } else {
            Current.failwith("More signatures required to execute the proposition")
        }
    } else {
        Current.failwith("Only contract owners can sign transation proposals")
    }
}];

/*
    As an owner of the account, you can add your signature to the proposal
*/
[%%entry let sign_proposition = (parameter: unit, storage) => {
    if (can_call(storage)) {
        let sender = Current.sender();
        ([], {
            last_proposition: storage.last_proposition,
            owners: storage.owners,
            owners_signed: Set.add(sender, storage.owners_signed)
        });
    } else {
        Current.failwith("Only contract owners can sign transation proposals")
    }
}];

/*
    Owners of the contract can create new transaction proposals
*/
[%%entry let create_proposition = (new_proposition: proposition, storage) => {
    if (can_call(storage)) {
        switch(storage.last_proposition) {
            | Some(proposition) => Current.failwith("Transaction proposal is already pending, please delete it before creating a new one")
            | None => ([], {
                last_proposition: Some(new_proposition),
                owners: storage.owners,
                owners_signed: Set
            })
        }
    } else {
        fail_with_wrong_ownership()
    }
}];

