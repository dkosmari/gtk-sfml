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


#ifndef GTKSFML_PRIV_UTILS_HPP
#define GTKSFML_PRIV_UTILS_HPP


#include <SFML/Window/Event.hpp>
#include <gdk/gdk.h>


#if defined(GDK_WINDOWING_X11)
# include <gdk/gdkx.h>
#elif defined(GDK_WINDOWING_WIN32)
# include <gdk/gdkwin32.h>
#else
# error "No implementation for this platform."
#endif



namespace gtksfml::priv::utils {

    sf::Event::KeyEvent
    translate(GdkEventKey* gkey);


#if defined(GDK_WINDOWING_X11)
    using WinHandle = ::Window;
#elif defined(GDK_WINDOWING_WIN32)
    using WinHandle = HANDLE;
#endif

    WinHandle get_handle(GdkWindow* w);


}


#endif
