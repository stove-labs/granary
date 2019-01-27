command=$1

case "$command" in
    start)
        ./scripts/original/alphanet.sh node start --rpc-port 18731
        ;;
    stop)
        ./scripts/original/alphanet.sh node stop
        ;;
    shell)
        docker run -e NETWORK_TYPE=$NETWORK_TYPE --network compose_default  -v $PWD:/tezos-environment-manager -it tezos-environment-manager/tezos-client-liquidity:latest /bin/bash
        ;;
esac