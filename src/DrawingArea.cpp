// SPDX-License-Identifier: GPL-3.0-or-later

/*
 *  gtk-sfml - a set of widgets for integrating SFML into gtkmm3.
 *  Copyright (C) 2023  Daniel K. O.
 */

#include <SFML/System/Vector2.hpp>
#include <gdkmm/frameclock.h>

#include "gtk-sfml/DrawingArea.hpp"

#include "priv-methods.hpp"


namespace gtksfml {


    DrawingArea::DrawingArea()
    {
        init();
    }


    void
    DrawingArea::init()
    {
        set_auto_update(true);
    }


    IMPL_ALL(DrawingArea)
}
