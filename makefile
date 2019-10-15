# https://stackoverflow.com/a/6273809/1826109
%:
	@:

.PHONY: submodules_update
submodules_update:
	@git submodule foreach git pull origin master
	@make copy_helpers

.PHONY: copy_helpers
copy_helpers:
	@cp -arf "./arduino-helpers/lib" ./node-gps-rx/
	@cp -arf "./arduino-helpers/src" ./node-gps-rx/
	@cp -arf "./arduino-helpers/include" ./node-gps-rx/
	@cp -arf "./arduino-helpers/.editorconfig" ./node-gps-rx/

	@cp -arf "./arduino-helpers/lib" ./node-gps-tx/
	@cp -arf "./arduino-helpers/src" ./node-gps-tx/
	@cp -arf "./arduino-helpers/include" ./node-gps-tx/
	@cp -arf "./arduino-helpers/.editorconfig" ./node-gps-tx/