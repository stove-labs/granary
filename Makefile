ARGS = $(filter-out $@,$(MAKECMDGOALS))
$(eval $(ARGS):;@:)

build:
	docker image build -t tezos-app-stack-local -f ./docker/images/Dockerfile-local .

start:
	sh ./scripts/tezos/$(TEZOS_NETWORK).sh start --rpc-port 18731

stop:
	sh ./scripts/tezos/$(TEZOS_NETWORK).sh stop

shell:
	sh ./scripts/tezos/$(TEZOS_NETWORK).sh shell