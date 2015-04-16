
###
# Makefile Environment Definitions
###
Q:=-@

default: all

###
# Specific build targets
###


# Make sure buildroot submodule has been checked out
# If buildroot/Makefile does not exist, submodule can be
# assumed to have not been checked out yet.
buildroot/Makefile:
	$(Q)echo "Initialising submodules..."
	$(Q)git submodule init
	$(Q)git submodule update

# copy configs to appropriate places in build tree.
install-configs: buildroot/Makefile
	cp configs/buildroot.config buildroot/.config

# copy configs out of build tree, into configs/ 
save-configs:
	cp buildroot/.config configs/buildroot.config

buildroot: install-configs
	make -C buildroot/ all

rpu-build: buildroot
	make -C rpu/ all CROSS_COMPILE=arm-buildroot-linux-uclibcgnueabi- PKG_CONFIG_SYSROOT_PATH=$(shell pwd)/output/staging/ PATH=$(PATH):$(shell pwd)/buildroot/output/host/usr/bin/

rpu-clean:
	make -C rpu/ clean

###
# General build targets
###
.PHONY: default all clean clean-* rebuild-* rpu buildroot FORCE

all: buildroot rpu-build

clean:

docs:
	$(Q)mkdir docs/
	$(Q)doxygen doxyfile

# Any unhandled target can be passed through to buildroot
%:
	make -C buildroot/ $@




