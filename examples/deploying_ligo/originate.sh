# compile storage in contracts folder with
# ligo compile-storage taco-shop.ligo buy_taco 'map 1n -> record current_stock = 50n; max_price = 50000000mtz; end; end'
# { Elt 1 (Pair 50 50000000) }

# compile parameter in contracts folder with
# ligo compile-parameter taco-shop.ligo buy_taco 1n
# 1

granary client - originate contract taco-shop for bootstrap1 transferring 0 from bootstrap1 running $PWD/contracts/taco-shop.tz --init '"{ Elt 1 (Pair 50 50000000) }"' --burn-cap 2.356 --force & 
sleep 10
granary client - bake for bootstrap1