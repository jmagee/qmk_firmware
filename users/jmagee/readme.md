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

 * There is only one persistant layer, which is qwerty.
 * All other layers are considered transient.
 * Transient layers should not redefine any of the layer switching keys.
 * Only one transient layer can be enabled at a time.

In practice, leveraging the layers here can be done by:
1. Define keymaps for the desired layers in the `Layers` enum.
2. Use keycodes from the `Custom_keycodes` enum in your layers, ensuring that
   you do not use any keycodes that corrospond to layers that you don't plan to
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

Mouser
------

Pseudo assertions
-----------------

NKRO
----

Secrets
-------
