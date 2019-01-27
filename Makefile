ARGS = $(filter-out $@,$(MAKECMDGOALS))
$(eval $(ARGS):;@:)

build:
	docker image build -t tezos-environment-manager/sandbox-node -f ./docker/images/sandbox-node/Dockerfile . && \
	docker image build -t tezos-environment-manager/tezos-client-liquidity -f ./docker/images/tezos-client-liquidity/Dockerfile .

start:
	sh ./scripts/$(NETWORK_TYPE)/commands.sh start

stop:
	sh ./scripts/$(NETWORK_TYPE)/commands.sh stop

client:
	sh ./scripts/$(NETWORK_TYPE)/commands.sh client
