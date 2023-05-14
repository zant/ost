.PHONY: build test

build:
	sh ./scripts/build.sh

test:
	sh ./scripts/test.sh && ./build/test/tests

build-test:
	sh ./scripts/test.sh