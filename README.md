# GTK-SFML - A set of gtkmm widgets for integration with SFML.

GTK-SFML is a C++ library that integrates [SFML](https://www.sfml-dev.org/) with
[gtkmm](https://gtkmm.org). Currently only gtkmm-3 is supported.

On some systems, this approach allows for higher frame rates than using OpenGL directly
with GTK+ (e.g. GTK+ will cap the OpenGL rendering to 30 fps, while gtk-sfml will perform
the exact same rendering at 60 fps)

This is done through widgets that handle GTK+ events for SFML. The following widgets are
provided, inheriting from the gtkmm widget of the same name, and from
`sfml::RenderWindow`:

- `gtksfml::ApplicationWindow` (from `<gtksfml/ApplicationWindow.hpp>`)
- `gtksfml::DrawingArea` (from `<gtksfml/DrawingArea.hpp>`)
- `gtksfml::Window` (from `<gtksfml/Window.hpp>`)


## Example

examples/hello-world.cpp


## Prerequisites

For this library to work you need:

- [gtkmm](https://gtkmm.org)
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


## Building a RPM package

Use `make rpm`.


