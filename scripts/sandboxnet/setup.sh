# Move our desired client config based on the current network, to the real client
cp /tezos-environment-manager/scripts/$NETWORK_TYPE/config /root/.tezos-client/
# Setup the init script
cp /tezos-environment-manager/scripts/$NETWORK_TYPE/init.sh /bin/init-client
chmod +x /bin/init-client
# Load our new tezos-client config
tezos-client config update
# Enabels liquidity to be used from the shell
eval $(opam env)

# Extract the current node address from config
export NODE_ADDR=$(cat /root/.tezos-client/config | jq -r .node_addr)
export NODE_PORT=$(cat /root/.tezos-client/config | jq -r .node_port)
export NODE_URL="http://$NODE_ADDR:$NODE_PORT"
