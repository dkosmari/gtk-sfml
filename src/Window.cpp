/*
 *  libgtk-sfml - a set of widgets for integrating SFML into gtkmm3.
 *  Copyright (C) 2021  Daniel K. O.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <SFML/System/Vector2.hpp>
#include <gdkmm/frameclock.h>

#include "gtk-sfml/Window.hpp"

#include "priv-methods.hpp"


namespace gtksfml {

    Window::Window(Gtk::WindowType type) :
        Gtk::Window{type}
    {
        init();
    }


    void
    Window::init()
    {
        set_app_paintable(true);
        set_double_buffered(false);
        set_auto_update(true);
        add_events(Gdk::EventMask::POINTER_MOTION_MASK);
        add_events(Gdk::EventMask::SCROLL_MASK);
    }


    IMPL_ALL_WINDOW(Window)

}
