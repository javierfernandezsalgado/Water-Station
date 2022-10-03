SHELL := /bin/bash
ESP-IDF:=/opt/eps-idf/esp-idf

build: FORCE
	-source $(ESP-IDF)/export.sh && idf.py build
flash: FORCE
	-source $(ESP-IDF)/export.sh && idf.py flash monitor
monitor: FORCE
	-source $(ESP-IDF)/export.sh && idf.py  monitor
test: FORCE
	-source $(ESP-IDF)/export.sh && cd test &&  idf.py build flash monitor
flash_parameters: FORCE
	-source $(ESP-IDF)/export.sh && cd flash_parameters && idf.py build flash monitor
clean: FORCE
	-source $(ESP-IDF)/export.sh && idf.py fullclean
test_clean: FORCE
	-source $(ESP-IDF)/export.sh && cd test &&  idf.py fullclean
menu_config: FORCE
	-source $(ESP-IDF)/export.sh && cd test &&  idf.py menuconfig
version: FORCE
	-source $(ESP-IDF)/export.sh && idf.py --version

.PHONY: FORCE
