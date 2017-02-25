# Kaleidoscope-Focus

![status][st:experimental] [![Build Status][travis:image]][travis:status]

 [travis:image]: https://travis-ci.org/keyboardio/Kaleidoscope-Focus.svg?branch=master
 [travis:status]: https://travis-ci.org/keyboardio/Kaleidoscope-Focus

 [st:stable]: https://img.shields.io/badge/stable-✔-black.png?style=flat&colorA=44cc11&colorB=494e52
 [st:broken]: https://img.shields.io/badge/broken-X-black.png?style=flat&colorA=e05d44&colorB=494e52
 [st:experimental]: https://img.shields.io/badge/experimental----black.png?style=flat&colorA=dfb317&colorB=494e52

TODO

## Using the plugin

TODO

```c++
#include <Kaleidoscope.h>
#include <Kaleidoscope-Focus.h>

void setup () {
  Kaleidoscope.setup ();
  
  USE_PLUGINS (&Focus);

  // TODO
}
```

## Plugin methods

The plugin provides the `Focus` object, which has the following method:

### `.addCommand(command)`

> TODO

## Further reading

Starting from the [example][plugin:example] is the recommended way of getting
started with the plugin.

  [plugin:example]: https://github.com/keyboardio/Kaleidoscope-Focus/blob/master/examples/Focus/Focus.ino
