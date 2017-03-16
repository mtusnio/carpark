CONTIKI?=../contiki/

TARGET = mikro-e
VERSION? = $(shell git describe --abbrev=4 --dirty --always --tags)
LWM2M_DIR=AwaLWM2M
TINYDTLS_DIR=tinydtls
WITH_CONTIKI = 1
CONTIKI_WITH_IPV6 = 1
CONTIKI_WITH_RPL = 0
TINYDTLS = 1
USE_SERIAL_PADS = 0
USE_CA8210 = 1

CLIENT_NAME?="Carpark1"

CFLAGS += -DCLIENT_NAME=$(CLIENT_NAME)
CFLAGS += -DVERSION=$(VERSION) -DPROJECT_CONF_H=\"project-conf.h\"
CFLAGS += -Wall -Wno-pointer-sign
CFLAGS += -I $(CONTIKI)/platform/$(TARGET)
CFLAGS += -fno-short-double
CFLAGS += -I$(LWM2M_DIR)/api/include -DLWM2M_CLIENT -DDTLS_PEERS_NOHASH=1
CFLAGS += -DUIP_CONF_BUFFER_SIZE=4096

LDFLAGS += -Wl,--defsym,_min_heap_size=32000

APPDIRS += $(TINYDTLS_DIR)
APPDIRS += $(LWM2M_DIR)/core/src

APPS += letmecreateiot
APPS += erbium
APPS += client
APPS += common
APPS += tinydtls/aes tinydtls/sha2 tinydtls/ecc tinydtls

SMALL=0

all: main
	xc32-bin2hex main.$(TARGET)

include $(CONTIKI)/Makefile.include
