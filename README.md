# GTK-SFML - A set of gtkmm widgets for integration with SFML.

GTK-SFML is a C++ library that integrates [SFML](https://www.sfml-dev.org/) with
[gtkmm](https://gtkmm.org).

On some systems, this approach allows for higher frame rates than using OpenGL directly
with GTK+ (e.g. GTK+ will cap the OpenGL rendering to 30 fps, while gtk-sfml will perform
the exact same rendering at 60 fps)

This is done through widgets that handle GTK+ events for SFML. The following widgets are
provided, inheriting from the gtkmm widget of the same name, and from
`sfml::RenderWindow`:

- `gtksfml::ApplicationWindow` (from [`<gtk-sfml/ApplicationWindow.hpp>`](include/gtk-sfml/ApplicationWindow.hpp))
- `gtksfml::DrawingArea` (from [`<gtk-sfml/DrawingArea.hpp>`](include/gtk-sfml/DrawingArea.hpp))
- `gtksfml::Window` (from [`<gtk-sfml/Window.hpp>`](include/gtk-sfml/Window.hpp))


## Example

Here's [an example](examples/window.cpp) from the examples directory:

```cpp
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtkmm.h>

#include <gtk-sfml/Window.hpp>

#include "font.hpp"

struct MyWindow :
    gtksfml::Window {

    sf::Font font;
    sf::Text text{"Window demo", font};

    MyWindow()
    {
        set_default_size(500, 300);
        font.loadFromMemory(FONT_DATA, FONT_SIZE);
        text.setPosition(100, 100);
    }

    void on_render() override
    {
        clear({64, 0, 0});
        draw(text);
        display();
    }
};

int main()
{
    auto app = Gtk::Application::create();
    MyWindow window;
    return app->run(window);
}
```


## Prerequisites

For this library to work you need:

- [gtkmm](https://gtkmm.org) (only gtkmm 3.x is supported at the moment)
- [SFML](https://www.sfml-dev.org/)


## Build instructions

0. When cloning from the repository, you need to first run `./bootstrap`. This step is not
   needed when obtaining a source tarball, as the resulting files are already included in
   the tarball.

1. `./configure --prefix=/usr`

2. `make`

3. `sudo make install`

For more installation options, use `./configure --help`. This is a standard Automake
package.


## Usage

A `pkg-config` script, `gtk-sfml.pc` will be installed, which provides the compilation and
linker flags to use gtk-sfml.

### With Makefiles
 In a Makefile, you would use:

```Makefile
CXXFLAGS := $(shell pkg-config --cflags gtk-sfml)
LIBS := $(shell pkg-config --libs gtk-sfml)
```


### With Autoconf/Automake

If using Autoconf/Automake, you can use the `PKG_CHECK_MODULES` macro in `configure.ac`:

```
PKG_CHECK_MODULES([GTK_SFML], [gtk-sfml])
```

Then the `Makefile.am` can use:

```Makefile
AM_CXXFLAGS = $(GTKSFML_CFLAGS)
LDADD = $(GTKSFML_LIBS)
# if linking into a library, use _LIBADD instead of LDADD
```


### With Cmake

The [FindPkgConfig](https://cmake.org/cmake/help/latest/module/FindPkgConfig.html) module can obtain the flags from a pkg-config module:

```
find_package(PkgConfig)

pkg_check_modules(GTKSFML gtk-sfml)

# now use GTKSFML_CFLAGS and GTKSFML_LDFLAGS in your target
```


### Invoking the compiler directly

Simply use [command
substitution](https://www.gnu.org/software/bash/manual/html_node/Command-Substitution.html)
to invoke `pkg-config`:

```
g++ -c my-code.cpp $(pkg-config gtk-sfml --cflags)
g++ my-code.o -o my-program $(pkg-config gtk-sfml --libs)
```

