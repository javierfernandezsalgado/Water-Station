SHELL := /bin/bash



build:
	-source /opt/esp/esp/esp/esp-idf/export.sh && idf.py build
flash:
	-source /opt/esp/esp/esp/esp-idf/export.sh && idf.py flash monitor
monitor:
	-source /opt/esp/esp/esp/esp-idf/export.sh && idf.py  monitor
test:
	-source /opt/esp/esp/esp/esp-idf/export.sh && cd test &&  idf.py build flash monitor
clean:
	-source /opt/esp/esp/esp/esp-idf/export.sh && idf.py fullclean
test_clean:
	-source /opt/esp/esp/esp/esp-idf/export.sh && cd test &&  idf.py fullclean
