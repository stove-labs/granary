command=$1

case "$command" in
    start)
        docker-compose -f ./docker/compose/docker-compose-local.yml up -d
        ;;
    stop)
        docker-compose -f ./docker/compose/docker-compose-local.yml down
        ;;
    client)
        docker run -e NETWORK_TYPE=$NETWORK_TYPE --network compose_default -v $PWD/docker/volumes/$NETWORK_TYPE/.tezos-client:/root/.tezos-client/ -v $PWD:/tezos-environment-manager -it maht0rz/tezos-environment-manager-tezos-client-liquidity:latest /bin/bash
        ;;
esac