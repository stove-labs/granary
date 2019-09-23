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