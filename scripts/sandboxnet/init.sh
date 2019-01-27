# Replace localhost with the current node address
sed -i "s/127.0.0.1/$NODE_ADDR/g" ./tezos/src/bin_client/tezos-init-sandboxed-client.sh
# Additionally, activate tezos alpha protocol straight away
echo "activate_alpha" >> ./tezos/src/bin_client/tezos-init-sandboxed-client.sh
eval `./tezos/src/bin_client/tezos-init-sandboxed-client.sh 1`
# Move the generated sandboxed client configuration to our real client
mv -v /tmp/tezos-tmp-client.*/* /root/.tezos-client/