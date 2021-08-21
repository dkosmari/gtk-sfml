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

#ifndef GTKSFML_DRAWING_AREA_HPP
#define GTKSFML_DRAWINGAREA_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <gtkmm/drawingarea.h>


namespace gtksfml {

    class DrawingArea : public Gtk::DrawingArea, public sf::RenderWindow {

        bool auto_update_state = false;
        guint tick_id;

    protected:

        void on_realize() override;
        void on_unrealize() override;
        void on_size_allocate(Gtk::Allocation& alloc) override;
        bool on_draw(const Cairo::RefPtr<Cairo::Context >& cr) override;
        bool on_tick(const Glib::RefPtr<Gdk::FrameClock>& clock);

        // do any per-frame logic here
        virtual void on_update(gint64 us);

        virtual void on_render() = 0;

    public:

        DrawingArea(bool auto_redraw = true);

        // enable to call on_update() and on_render() periodically.
        void set_auto_update(bool enable);
        bool get_auto_update() const;


        using sf::RenderWindow::draw;
    };

}


#endif
