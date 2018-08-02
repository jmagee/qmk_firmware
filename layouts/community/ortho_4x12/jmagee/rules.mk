CONSOLE_ENABLE = yes
DEBUG_ENABLE = yes
MOUSEKEY_ENABLE = yes
NKRO_ENABLE = yes
#KEY_LOCK_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), vitamins_included/rev1)
	AUDIO_ENABLE = no
	RGBLIGHT_ENABLE = no
endif
