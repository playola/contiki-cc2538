all: example-coap-server

CONTIKI = ../..

CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"

# Automatically build RESTful resources
REST_RESOURCES_DIR = ./resources
REST_RESOURCES_FILES = $(notdir $(shell find $(REST_RESOURCES_DIR) -name '*.c'))
# Automatically build libraries resources
LIBRARIES_DIR = ./libraries
LIBRARIES_FILES = $(notdir $(shell find $(LIBRARIES_DIR) -name '*.c'))

PROJECTDIRS += $(REST_RESOURCES_DIR) $(LIBRARIES_DIR)
PROJECT_SOURCEFILES += $(REST_RESOURCES_FILES) $(LIBRARIES_FILES)

# Linker optimizations
SMALL=1

# REST Engine shall use Erbium CoAP implementation
APPS += er-coap
APPS += rest-engine

CONTIKI_WITH_IPV6 = 1
include $(CONTIKI)/Makefile.include

# Minimal-net target is currently broken in Contiki
ifeq ($(TARGET), minimal-net)
CFLAGS += -DHARD_CODED_ADDRESS=\"fdfd::10\"
${info INFO: er-example compiling with large buffers}
CFLAGS += -DUIP_CONF_BUFFER_SIZE=1300
CFLAGS += -DREST_MAX_CHUNK_SIZE=1024
CFLAGS += -DCOAP_MAX_HEADER_SIZE=176
CONTIKI_WITH_RPL=0
endif

# Border Router rules
$(CONTIKI)/tools/tunslip6:	$(CONTIKI)/tools/tunslip6.c
	(cd $(CONTIKI)/tools && $(MAKE) tunslip6)

connect-router:	$(CONTIKI)/tools/tunslip6
	sudo $(CONTIKI)/tools/tunslip6 fd00::1/64
