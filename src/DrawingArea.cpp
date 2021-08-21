/*
 *  SFMLWidget - a gtkmm3 widget for interfacing with SFML.
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

#include "DrawingArea.hpp"

#if defined(GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined(GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#else
#error "No implementation for this platform."
#endif


namespace gtksfml {

    DrawingArea::DrawingArea(bool auto_update)
    {
        set_auto_update(auto_update);
    }


    void
    DrawingArea::set_auto_update(bool enable)
    {
        if (enable == auto_update_state)
            return;
        auto_update_state = enable;
        if (enable)
            tick_id = add_tick_callback(sigc::mem_fun(*this, &DrawingArea::on_tick));
        else
            remove_tick_callback(tick_id);
    }


    bool
    DrawingArea::get_auto_update() const
    {
        return auto_update_state;
    }


    void
    DrawingArea::on_realize()
    {
        Gtk::DrawingArea::on_realize();
        auto win = get_window();
        //win->ensure_native();
#if defined(GDK_WINDOWING_X11)
        auto handle = gdk_x11_window_get_xid(win->gobj());
#elif defined(GDK_WINDOWING_WIN32)
        auto handle = gdk_win32_window_get_handle(win->gobj());
#endif
        create(handle);
    }


    void
    DrawingArea::on_unrealize()
    {
        close();
        Gtk::DrawingArea::on_unrealize();
    }


    void
    DrawingArea::on_size_allocate(Gtk::Allocation& alloc)
    {
        Gtk::DrawingArea::on_size_allocate(alloc);
        setSize(sf::Vector2u(alloc.get_width(), alloc.get_height()));
    }


    bool
    DrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>&)
    {
        setActive(true);
        on_render();
        return true;
    }


    bool
    DrawingArea::on_tick(const Glib::RefPtr<Gdk::FrameClock>& clock)
    {
        on_update(clock->get_frame_time());

        queue_draw();
        return G_SOURCE_CONTINUE;
    }


    void
    DrawingArea::on_update(gint64)
    {}

}
