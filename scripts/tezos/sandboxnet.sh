command=$1

case "$command" in
    start)
        docker-compose -f ./docker/compose/docker-compose-local.yml up -d
        ;;
    stop)
        docker-compose -f ./docker/compose/docker-compose-local.yml down
        ;;
    shell)
        docker exec -it compose_node_1 /bin/bash
esac