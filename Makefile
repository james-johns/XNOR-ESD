
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

###
# General build targets
###
.PHONY: default all clean clean-* rebuild-*

all: install-configs
	make -C buildroot/ all
	make -C rpu/ all CROSS_COMPILE=arm-buildroot-linux-uclibcgnueabi- GST_LIBRARY_PATH=-L$(shell pwd)/buildroot/output/target/usr/lib PATH=$(PATH):$(shell pwd)/buildroot/output/host/usr/bin/

clean:

# Any unhandled target can be passed through to buildroot
%:
	make -C buildroot/ $@




