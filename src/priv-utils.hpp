// SPDX-License-Identifier: GPL-3.0-or-later

/*
 *  gtk-sfml - a set of widgets for integrating SFML into gtkmm3.
 *  Copyright (C) 2023  Daniel K. O.
 */

#ifndef GTKSFML_PRIV_UTILS_HPP
#define GTKSFML_PRIV_UTILS_HPP

#include <utility>

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


    sf::Event::MouseButtonEvent
    translate(GdkEventButton* motion_event);


    sf::Event::MouseWheelEvent
    translate_vert(GdkEventScroll* scroll_event);


    std::pair<sf::Event::MouseWheelScrollEvent,
              sf::Event::MouseWheelScrollEvent>
    translate_smooth(GdkEventScroll* scroll_event);

}


#endif
