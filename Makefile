contributors-build-image:
	docker build -t stovelabs/granary-contributors ./docker/contributors

contributors-push-image:
	docker push stovelabs/granary-contributors

contributors-build-website:
	docker run -v $(PWD):$(PWD) -w $(PWD)/website stovelabs/granary-contributors npm run build
	