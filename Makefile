WORKING_DIR			?= . # $(shell pwd)

.DEFAULT_GOAL := help

# cmake .. -G "MinGW Makefiles"

down: ## clean project
	@rm -rf build

generate: ## generate project
	@cmake -B build -G "MinGW Makefiles" . -DCMAKE_BUILD_TYPE=Release
	
build: ## build project
	@cd build && make --no-print-directory

rebuild: ## rebuild project
	@cd build && make rebuild_cache --no-print-directory

run: ## run
	@./out/bin/data-structure.exe

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: down build rebuild help