SHELL := /bin/bash


build: FORCE
	-source /opt/esp/esp/esp/esp-idf/export.sh && idf.py build
flash: FORCE
	-source /opt/esp/esp/esp/esp-idf/export.sh && idf.py flash monitor
monitor: FORCE
	-source /opt/esp/esp/esp/esp-idf/export.sh && idf.py  monitor
test: FORCE
	-source /opt/esp/esp/esp/esp-idf/export.sh && cd test &&  idf.py build flash monitor
clean: FORCE
	-source /opt/esp/esp/esp/esp-idf/export.sh && idf.py fullclean
test_clean: FORCE
	-source /opt/esp/esp/esp/esp-idf/export.sh && cd test &&  idf.py fullclean

menu_config: FORCE
	-source /opt/esp/esp/esp/esp-idf/export.sh && cd test &&  idf.py menuconfig


.PHONY: FORCE
