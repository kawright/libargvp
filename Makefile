# ----- PROJECT INFO -----

PROJ_NAME := libargvp
VER := 1.0

# ----- COMPILER CONFIGURATION -----

CC := gcc
CC_OPTS := \
	-Wall \
	-Werror \
	-fpic

# ----- REAL TARGETS -----

build/lib/libargvp.so: build/obj/argvp.o
	@mkdir -p build/lib
	@${CC} -shared -o $@ $<
	@echo "Built target $@"

build/obj/argvp.o: argvp.c argvp.h
	@mkdir -p build/obj
	@${CC} ${CC_OPTS} -c -o $@ $<
	@echo "Built target $@"

# ----- PHONY TARGETS -----

.PHONY: \
	all \
	clean \
	install \
	uninstall

all: build/lib/libargvp.so
	@echo "Built ${PROJ_NAME} version ${VER}"

clean:
	@rm -rf build
	@echo "Deleted build"
	@echo "All build artifacts deleted"

install: build/lib/libargvp.so
	@cp argvp.h /usr/local/include/argvp.h
	@echo "Copied argvp.h"
	@cp build/lib/libargvp.so /usr/local/lib/libargvp.so
	@echo "Copied libargvp.so"
	@echo "${PROJ_NAME} version ${VER} successfully installed"

uninstall:
	@rm /usr/local/include/argvp.h
	@echo "Deleted argvp.h"
	@rm /usr/local/lib/libargvp.so
	@echo "Deleted libargvp.so"
	@echo "${PROJ_NAME} successfully uninstalled"
