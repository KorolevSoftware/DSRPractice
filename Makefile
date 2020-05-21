BUILD_ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))


SPL_PATH = $(BUILD_ROOT)/stm_spl/
COMMON_PATH = $(BUILD_ROOT)/common
LIB_PATH = $(BUILD_ROOT)/lib
MAIN_DIR = $(BUILD_ROOT)/DSRPractice

.PHONY: labs spl common lab1 clean

all: main

main: spl common lib
	make -C $(MAIN_DIR)

flash:
	make -C $(MAIN_DIR) flash

spl:
	make -C $(SPL_PATH)

common:
	make -C $(COMMON_PATH)

lib:
	make -C $(LIB_PATH)

clean:
	make -C $(SPL_PATH) clean	
	make -C $(COMMON_PATH) clean
	make -C $(LIB_PATH) clean
	make -C $(MAIN_DIR)/led_test clean
