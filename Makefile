# ----- PROJECT INFO -----

PROJ_NAME := libargvp
PROJ_DESC := "argument vector parsing"
PROJ_VER := 1.2

# ----- COMPILER CONFIGURATION -----

CC := gcc
CC_OPTS := \
	-Wall \
	-Werror \
	-fpic \
	-g

CC_LIBS := \
	-lerr

# ----- REAL TARGETS -----

build/lib/libargvp.so: build/obj/argvp.o
	@mkdir -p build/lib
	@${CC} -shared -o $@ $< ${CC_LIBS}
	@echo "Built target $@"

build/obj/argvp.o: argvp.c argvp.h Makefile
	@mkdir -p build/obj
	@${CC} ${CC_OPTS} -c -o $@ $<
	@echo "Built target $@"

# ----- PHONY TARGETS -----

.PHONY: \
	all \
	clean \
	install \
	uninstall \
	ver

all: build/lib/libargvp.so
	@ver -s -n ${PROJ_NAME} -d ${PROJ_DESC}
	@echo "Updated project metadata"
	@echo "Built ${PROJ_NAME} version ${PROJ_VER} (build $$(ver -b))"

clean:
	@rm -rf build
	@echo "All build artifacts deleted"

install: build/lib/libargvp.so
	@mkdir -p /usr/local/etc/libargvp
	@cp argvp.h /usr/local/include/argvp.h
	@echo "Copied argvp.h"
	@cp build/lib/libargvp.so /usr/local/lib/libargvp.so
	@echo "Copied libargvp.so"
	@cp .ver /usr/local/etc/libargvp/.ver
	@echo "Copied .ver"
	@echo "${PROJ_NAME} version ${PROJ_VER} successfully installed"

uninstall:
	@rm /usr/local/include/argvp.h
	@echo "Deleted argvp.h"
	@rm /usr/local/lib/libargvp.so
	@echo "Deleted libargvp.so"
	@rm -rf /usr/local/etc/libargvp
	@echo "Deleted etc files"
	@echo "${PROJ_NAME} successfully uninstalled"

ver:
	@ver -V ${PROJ_VER}
	@echo "Updated version number to ${PROJ_VER}"
