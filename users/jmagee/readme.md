Overview
========

This is my personal user space area.  Most of the code here consists of utility helpers
that are useful across keyboards.

Layers
------
layers.c and layers.h define different layers, keycodes, and routines to work with them.
Keymaps do not have to implement all the layers defined here.

The way I use layers may be a tad unorthodox, but fits the modal model I have
in mind.  In particularly,

 * There is only one persistent layer, which is qwerty.
 * All other layers are considered transient.
 * Transient layers should not redefine any of the layer switching keys.
 * Only one transient layer can be enabled at a time.

In practice, leveraging the layers here can be done by:

1. #define the layer macro for each desired layer in your config.h.
2. Define keymaps for desired layers found in the `Layers` enum.
3. Use keycodes from the `Custom_keycodes` enum in your layers, ensuring that
   you do not use any keycodes that correspond to layers that you don't plan to
   implement. (Meaning if you use the `ALBHED` keycode, you better define an
   `_ALBHED` keymap.
4. Add the following to `process_record_user`:
```
if (is_layer_keycode(keycode)) {
    if (record->event.pressed) {
      activate_layer(keycode_to_layer(keycode));
      return false;
    }
  }
```

The following table summarizes the available layers:


| Layer enum   | Keycode         | Required macro            | Note                                   |
|--------------|-----------------|---------------------------|----------------------------------------|
| `_BASE`      | `BASE`          | None - always enabled     | Base layer - probably qwerty           |
| `_ALBHED`    | `ALBHED`        | `USE_ALBHED_LAYER`        | Layer for Al Bhed 'language' (cipher)  |
| `_NUMPAD`    | `NUMPAD`        | `USE_NUMPAD_LAYER`        | Layer for numpad overlays              |
| `_SYMBOLS`   | `SYMBOLS`       | `USE_SYMBOLS_LAYER`       | Layer for symbols (!@#$, etc.)         |
| `_NAVI`      | `NAVI`          | `USE_NAVI_LAYER`          | Layer for navigation (arrows, etc)     |
| `_MOUSER`    | `MOUSER`        | `USE_MOUSER_LAYER`        | Layer for MOUSEKEY                     |
| `_FUNC`      | `FUNC`          | `USE_FUNC_LAYER`          | Layer for function keys (F-keys, etc)  |
| `_GOD`       | `GOD`           | `USE_GOD_LAYER`           | Layer for almighty power               |


The motivation for the extra complication of requiring opting-in via a macro is
to allow these layers (and the code to work with them) to be reused between
keyboards, but without wasting any space for potentially unused layers.
For example, on a 40% the NUMPAD, SYMBOLS, and NAVI layers are very useful but
on a 60% they may not be useful.

For each layer, a "smart toggle" is provided (roughly of the form `T_LAYER`).
These yield toggle on tap and momentarily activate on hold.  I.e.
`LT(LAYER, LAYER_KEYCODE)`.

Custom Keycodes
---------------
A few custom keycodes are provided, including ones for each layer described above.

Non-layer custom key codes:

| Keycode      | Use                                           |
|--------------|-----------------------------------------------|
| `SQUEEK`     | Toggles through mouse acceleration speed.     |
| `KC_HEX`     | Emit `0x`.                                    |

A function is provided to handle these custom keycodes:

```
#include "keycodes.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_custom_keycodes(keycode, record);
}
```

`process_custom_keycodes` returns `false` if further processing should stop,
and `true` if further processing should continue.  This function handles layer
activation as well, so if it is used then the code sample in the layer section
is not needed.

Leaders
-------
I make heavy use of leaders.

| Leader Key   | Traditional Key | Enabled by function       | Note                                   |
|--------------|-----------------|---------------------------|----------------------------------------|
|Leader f N N  | F<N>            | `leader_fkeys`            | N are numpad digits on a qwerty layer. |
|Leader c a d  | ctrl+alt+delete | `leader_ctrl_alt_del`     |                                        |
|Leader v N N  | ctrl+alt+F<N>   | `leader_virtual_consoles` | N are numpad digits on a qwerty layer. |
|Leader x enter| alt+shift+enter | `leader_xmonad`           | Launch new term.                       |
|Leader x p    | alt+p           | `leader_xmonad`           | Launch dmenu.                          |
|Leader x x    | alt+x           | `leader_xmonad`           | Lock the screen.                       |
|Leader x c    | alt+c           | `leader_xmonad`           | Close current window.                  |
|Leader x space| alt+space       | `leader_xmonad`           | Cycle layout.                          |
|Leader x d    | alt+d           | `leader_xmonad`           | Start a pomodoro session.              |
|Leader x q    | alt+shift+ctrl+q| `leader_xmonad`           | Quit xmonad.                           |
|Leader x r    | alt+shift+q     | `leader_xmonad`           | Restart xmonad.                        |
|Leader x N    | alt+N           | `leader_xmonad`           | N are numpad digits on a qwerty layer. |
|Leader flash  | N/A             | `leader_utility`          | Rest the board into flash mode.        |
|Leader n      | N/A             | `leader_nkro`             | Toggle NKRO on and off.                |
|Leader spc spc| N/A             | `leader_music`            | Toggle music mode on/off.              |
|Leader tab tab| N/A             | `leader_music`            | Toggle music mode mode.                |

Mouser
------
The function `squeek` is provided when working with Mouse Keys.  `squeek`
simply cycles through the available acceleration speeds.

Pseudo assertions
-----------------
Assertions are a nice debugging and code sanity technique.  If you ever think to yourself "[some scenario] is impossible", then that is a sign that you should add an assertion to that effect.
Of course, asserting in your keyboard firmware is not very friendly.  To help with that, I added psuedo assertions - asserts without the bite.  In other words, they just print the debug message but don't actually abort the program.

Two functions are provided:

  -  `passert(condition)` - Pseudo assert.  Print a debug message if the condition fails.
  -  `unreachable(void)` - Print a debug message if execution reaches this point.

If the `NO_DEBUG` macro is set, then `passert(condition)` will result in void and `unreachable` will result in `__builtin_unreachable()` (which is a nice optimization hint.)


NKRO
----
The function `enable_nkro(NK_Control mode)` is provided to easily change NKRO mode.
Usage:

```
#include "nkro.h"

void foo() {
  enable_nkro(NK_DISABLE); /* Disable NKRO */
  enable_nkro(NK_ENABLE);  /* Enable NKRO */
  enable_nkro(NK_TOGGLE);  /* Toggle NKRO */
}
```

Tapdances
---------
The "lock tapdance" is a dance that allows you to lock (and potentially unlock)
your screen.  Here's how it works:

 * A single tap on the `TD_LOCK` key will initiate a "short lock".
 * A long (held) tap on the `TD_LOCK` key will initiate a "long lock".
 * A double tap on the `TD_LOCK` key will unlock the screen in the "short lock"
   state, but do nothing in the "long lock" state.
 * After a configurable period of time (60 minutes by default, can be
   overridden via the `AUTO_LOCK_TIME` macro), "short locks" are automatically
   upgraded to "long locks".

The motivation behind this is that there are two scenarios where I locked my screen:
 1. When I momentarily leave my desk.  For example, I may go fetch a printout
    or coffee.  In this case I lock the screen just to be sure someone walking
    by my desk doesn't see something they shouldn't see.  I'm not however
    particularly worried that someone is going to try to break into the system
    at my desk, therefore I like a quick and convenient way to unlock my
    screen.
 2. When I leave my desk for an extended length of time - a meeting or
    overnight, then I don't want my screen to be so easy to unlock.  In that
    case, I want to have to manually unlock it.

To use this, first define a tap dance dance action:

```
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LCK]  = ACTION_TAP_DANCE_FN(lock_dance)
};
```

Second, in `matrix_scan_user` add a call to `expire_short_lock()`.  This *must*
be called regularly for "short locks" to be upgraded to "long locks".

Third, you'll likely want to define `AUTO_LOCK_TIME` to a preferred value in
your "config.h" file or rules.mk.  The value is specified in milliseconds.

Finally, define an implementation for the following function in your "secrets.h" file:
`static void secret_unlock(void)`

Providing a function `secret_unlock` rather than just an array value gives you
more control over how you want to perform your unlock - it can be something
more elaborate than simply sending a string.

Caveat - Depending on how the lock/unlock process is implemented, it can
range from mildly insecure to terribly insecure.  What I do is modify my
my screen lock program (xlockmore) to accept a special string, which will
unlock the screen, before authenticating the user account.  The catch
is that this special check is only allowed if the screen has been locked
less than `AUTO_LOCK_TIME`.  This avoids having to place a user credential
in keyboard firmware, at the cost of having to modify the screen lock program.
The end result is a slightly stronger version of the common "screen blank"
that upgrades to a full lock after a certain time.

Secrets
-------
Shhhh.  Its a secret.
