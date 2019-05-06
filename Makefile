contributors-build-image:
	docker build -t stovelabs/granary-contributors ./docker/contributors

contributors-push-image:
	docker push stovelabs/granary-contributors

contributors-shell:
	# 3000 for the docs server and 35729 for it's the live-reload 
	docker run -it -p 3000:3000 -p 35729:35729 -v $(PWD):$(PWD):delegated -w $(PWD) stovelabs/granary-contributors /bin/bash

contributors-shell-no-ports:
	docker run -it -v $(PWD):$(PWD):delegated -w $(PWD) stovelabs/granary-contributors /bin/bash

contributors-build-user-images:
	# node
	docker build -t stovelabs/granary-tezos-node-sandboxnet ./docker/tezos-node/sandboxnet
	# client
	docker build -t stovelabs/granary-tezos-client-sandboxnet -f ./docker/tezos-client/sandboxnet/Dockerfile ./docker/tezos-client
	docker build -t stovelabs/granary-tezos-client-alphanet -f ./docker/tezos-client/alphanet/Dockerfile ./docker/tezos-client



contributors-push-user-images:
	docker push stovelabs/granary-tezos-node-sandboxnet
	docker push stovelabs/granary-tezos-client

activate:
	docker run -v $(PWD):$(PWD):delegated --network=granary stovelabs/granary-tezos-client-sandboxnet --base-dir $(PWD)/.granary/sandboxnet/client --addr granary-tezos-node-sandbox activate protocol ProtoALphaALphaALphaALphaALphaALphaALphaALphaDdp3zK with fitness 1 and key activator and parameters "$(PWD)/protocol_parameters.json" --timestamp 2019-05-05T19:18:34Z