CONTIKI=../contiki/

TARGET = mikro-e
VERSION? = $(shell git describe --abbrev=4 --dirty --always --tags)
LWM2M_DIR=AwaLWM2M

CONTIKI_WITH_IPV6 = 1
CONTIKI_WITH_RPL = 0

USE_SERIAL_PADS = 1

CFLAGS += -DVERSION=$(VERSION)
CFLAGS += -Wall -Wno-pointer-sign
CFLAGS += -I $(CONTIKI)/platform/$(TARGET)
CFLAGS += -fno-short-double
CFLAGS += -I$(LWM2M_DIR)/api/include -DLWM2M_CLIENT
CFLAGS += -DUIP_CONF_BUFFER_SIZE=4096

LDFLAGS += -Wl,--defsym,_min_heap_size=32000

APPS += erbium

APPDIRS += $(LWM2M_DIR)/core/src
APPS += client
APPS += common

SMALL=0

all: main
	xc32-bin2hex main.$(TARGET)

include $(CONTIKI)/Makefile.include
