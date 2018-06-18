SRC += leader.c nkro.c layers.c passert.c mouse.c chord.c keycodes.c

EXTRAFLAGS += -flto

ifneq ($(strip $(SECRETS)), yes)
	OPT_DEFS += -DNO_SECRETS
endif

ifeq ($(strip $(NO_DEBUG)), yes)
	OPT_DEFS += -DNO_DEBUG
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tapdance.c
endif
