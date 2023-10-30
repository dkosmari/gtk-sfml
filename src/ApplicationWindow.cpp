// SPDX-License-Identifier: GPL-3.0-or-later

/*
 *  gtk-sfml - a set of widgets for integrating SFML into gtkmm3.
 *  Copyright (C) 2023  Daniel K. O.
 */

#include <SFML/System/Vector2.hpp>
#include <gdkmm/frameclock.h>

#include "gtk-sfml/ApplicationWindow.hpp"

#include "priv-methods.hpp"


namespace gtksfml {


    ApplicationWindow::ApplicationWindow()
    {
        init();
    }


    ApplicationWindow::ApplicationWindow(const Glib::RefPtr<Gtk::Application>& application) :
        Gtk::ApplicationWindow{application}
    {
        init();
    }


    void
    ApplicationWindow::init()
    {
        set_app_paintable(true);
        set_double_buffered(false);
        set_auto_update(true);
        add_events(Gdk::EventMask::POINTER_MOTION_MASK);
        add_events(Gdk::EventMask::SCROLL_MASK);
    }


    IMPL_ALL_WINDOW(ApplicationWindow)

}
