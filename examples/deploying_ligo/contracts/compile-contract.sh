DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

ligo compile-contract $DIR/taco-shop.ligo buy_taco > $DIR/taco-shop_tmp.tz

# please note that OS X introduces a line break incompatiblity when saving a file
# hence the following correction for UNIX systems
tr -d '\r' < $DIR/taco-shop_tmp.tz > $DIR/taco-shop.tz
rm $DIR/taco-shop_tmp.tz