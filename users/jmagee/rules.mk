SRC += leader.c nkro.c layers.c passert.c mouse.c

EXTRAFLAGS += -flto

ifeq ($(strip $(NO_SECRETS)), yes)
	OPT_DEFS += -DNO_SECRETS
endif

ifeq ($(strip $(NO_DEBUG)), yes)
	OPT_DEFS += -DNO_DEBUG
endif
