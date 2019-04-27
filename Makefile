contributors-build-image:
	docker build -t stovelabs/granary-contributors ./docker/contributors

contributors-push-image:
	docker push stovelabs/granary-contributors

contributors-test:
	./__tests__/cli.sh