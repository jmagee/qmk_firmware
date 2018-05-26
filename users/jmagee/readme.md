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
1. Define keymaps for any desired layers found in the `Layers` enum.
2. Use keycodes from the `Custom_keycodes` enum in your layers, ensuring that
   you do not use any keycodes that correspond to layers that you don't plan to
   implement. (Meaning if you use the `ALBHED` keycode, you better define an
   `_ALBHED` kymap.
3. Add the following to `process_record_user`:
```
if (is_layer_keycode(keycode)) {
    if (record->event.pressed) {
      activate_layer(keycode_to_layer(keycode));
      return false;
    }
  }
```

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

Secrets
-------
Shhhh.  Its a secret.
