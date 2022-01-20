#pragma once

#define USB_POLLING_INTERVAL_MS 5
#define DEBOUNCE 5
#define PERMISSIVE_HOLD
#define TAPPING_TERM 180
#define IGNORE_MOD_TAP_INTERRUPT
#define FORCE_NKRO
#ifdef COMBO_ENABLE
#    define COMBO_COUNT 5
#    define COMBO_TERM 50
#define TAPPING_FORCE_HOLD
#endif

