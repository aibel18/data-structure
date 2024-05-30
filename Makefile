WORKING_DIR			?= $(shell pwd)

.DEFAULT_GOAL := help

down: ## clean project
	@rm -rf build

generate: ## generate project
	@cmake -B build . -DCMAKE_BUILD_TYPE=Release
	
build: ## build project
	@cd $(WORKING_DIR)/build && make --no-print-directory

rebuild: ## rebuild project
	@cd $(WORKING_DIR)/build && make rebuild_cache --no-print-directory

run: ## run
	@$(WORKING_DIR)/sdk/bin/xsim_launcher

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: down build rebuild help