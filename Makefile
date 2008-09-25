##
## This file is part of Lemona.
## Copyright (C) 2008 Kenfe-Mickaël Laventure
##
## The contents of this file are subject to the terms of either the
## GNU General Public License Version 2 ("GPL") or the MIT License
## (collectively, the "License"). You may not use this file except in
## compliance with the License. You can obtain a copy of the License
## at http://www.opensource.org/licenses/gpl-2.0.php and
## http://www.opensource.org/licenses/mit-license.php or GPL.LICENSE
## and MIT.LICENSE. See the License for the specific language
## governing permissions and limitations under the License.
##

# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)

lemona-objs 		:= init.o mixers.o logging.o
obj-$(CONFIG_LEMONA)	+= lemona.o

#if relay support is needed add the relevant files
	ifneq ($(CONFIG_LEMONA_RELAY),)
		lemona-objs	+= relay.o
	endif

# originated from command line, force CONFIG_LEMONA_RELAY declaration
	ifneq ($(LEMONA_RELAY),)
		EXTRA_CFLAGS		+= -DCONFIG_LEMONA_RELAY=1
	endif

# Otherwise we were called from the command
# line; invoke the kernel build system
else

	ifneq ($(LEMONA_TARGET),)
		UNAME	:= $(LEMONA_TARGET)
	else
		UNAME	:= $(shell uname -r)
	endif

	KERNELDIR	?= /lib/modules/$(UNAME)/build
	PWD		:= $(shell pwd)

	CONFIG_LEMONA	:= m
	export CONFIG_LEMONA

	ifneq ($(LEMONA_RELAY),)
		CONFIG_LEMONA_RELAY	:= 1
		export CONFIG_LEMONA_RELAY
	endif

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	@echo 'Cleaning up...'
	@find -name '*.o' -o -name '*.ko*' -o -name '*.mod.c' 	\
	-o -name '*.symvers' -o -name '*~' -o -name '*.order'	\
	-o -name '*.cmd' -type f | xargs rm -f
	@rm -rf .tmp_versions
endif
