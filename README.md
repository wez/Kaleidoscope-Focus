# Kaleidoscope-Focus

![status][st:experimental] [![Build Status][travis:image]][travis:status]

 [travis:image]: https://travis-ci.org/keyboardio/Kaleidoscope-Focus.svg?branch=master
 [travis:status]: https://travis-ci.org/keyboardio/Kaleidoscope-Focus

 [st:stable]: https://img.shields.io/badge/stable-✔-black.png?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.png?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.png?style=flat&colorA=dfb317&colorB=494e52

Bidirectional communication for Kaleidoscope. With this plugin, one can expose a
set of commands via the Serial port, and allow the host to talk with the
keyboard - and vice versa. This plugin implements only the basic building
blocks, a framework other plugins can opt-in to.

## Using the plugin

This plugin is **not** meant to be used by the end-user (apart from setting it
up to use plugin-provided hooks), but by plugin authors instead. As an end user,
please see the documentation of the plugins you use, for instructions on how to
hook them up with `Focus`!

Nevertheless, the basic commands we implement with this plugin alone, are usable
like this:

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-Focus.h>

void setup () {
  Serial.begin (9600);
  Kaleidoscope.setup ();

  USE_PLUGINS (&Focus);

  Focus.addHook (FOCUS_HOOK_HELP);
  Focus.addHook (FOCUS_HOOK_VERSION);
}
```

## Plugin methods

The plugin provides the `Focus` object, which has the following method:

### `.addHook(FOCUS_HOOK (function, documentation))`

> Adds a new hook to `Focus`. Hooks are called in order of registration, and
> they get the parsed command name as argument. If they handle the command, they
> shall return `true`, otherwise `false`. Once a command has been handled, it
> will not be given to other hooks.
>
> The hook function is responsible for reading the rest of the command, in
> whatever way it sees fit.
>
> The `documentation` argument is a string, used by the `help` command, and can
> be left empty, if no documentation is desired for the `function`.

## Focus commands

The plugin ships with two (optional) commands:

### `FOCUS_HOOK_VERSION`

> A hook, that when called via the `version` command, prints the version of the
> firmware, the keyboard vendor & product, compile date, and Arduino version.

### `FOCUS_HOOK_HELP`

> A hook, that when called via the `help` command, walks through the registered
> hooks, and prints their documentation.

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

  [plugin:example]: https://github.com/keyboardio/Kaleidoscope-Focus/blob/master/examples/Focus/Focus.ino
