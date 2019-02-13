ARGS = $(filter-out $@,$(MAKECMDGOALS))
$(eval $(ARGS):;@:)

build:
	docker image build -t maht0rz/tezos-environment-manager-sandbox-node -f ./docker/images/sandbox-node/Dockerfile . && \
	docker image build -t maht0rz/tezos-environment-manager-tezos-client-liquidity -f ./docker/images/tezos-client-liquidity/Dockerfile .
	docker image build -t maht0rz/tezos-environment-manager-tzscan -f ./docker/images/tzscan/Dockerfile .

publish-docker-images:
	docker push maht0rz/tezos-environment-manager-sandbox-node
	docker push maht0rz/tezos-environment-manager-tezos-client-liquidity
	docker push maht0rz/tezos-environment-manager-tzscan
	
start:
	sh ./scripts/$(NETWORK_TYPE)/commands.sh start

stop:
	sh ./scripts/$(NETWORK_TYPE)/commands.sh stop

client:
	sh ./scripts/$(NETWORK_TYPE)/commands.sh client
