contributors-build-image:
	docker build -t stovelabs/granary-contributors ./docker/contributors

contributors-push-image:
	docker push stovelabs/granary-contributors

contributors-shell:
	docker run -it -p 3000:3000 -p 35729:35729 -v $(PWD):$(PWD):delegated -w $(PWD) stovelabs/granary-contributors /bin/bash

contributors-shell-no-ports:
	docker run -it -v $(PWD):$(PWD):delegated -w $(PWD) stovelabs/granary-contributors /bin/bash