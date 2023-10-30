// SPDX-License-Identifier: GPL-3.0-or-later

/*
 *  gtk-sfml - a set of widgets for integrating SFML into gtkmm3.
 *  Copyright (C) 2023  Daniel K. O.
 */

#ifndef GTKSFML_DRAWING_AREA_HPP
#define GTKSFML_DRAWING_AREA_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>


namespace gtksfml {

    class DrawingArea : public Gtk::DrawingArea,
                        public sf::RenderWindow {

        bool auto_update_state = false;
        guint tick_id;

        // hide this method, use on_event() instead
        using sf::RenderWindow::pollEvent;

        void init();

    protected:

        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        bool on_focus_in_event(GdkEventFocus* event) override;
        bool on_focus_out_event(GdkEventFocus* event) override;
        bool on_key_press_event(GdkEventKey* event) override;
        bool on_key_release_event(GdkEventKey* event) override;
        bool on_tick(const Glib::RefPtr<Gdk::FrameClock>& clock);
        void on_realize() override;
        void on_unrealize() override;

        // user should override these
        virtual void on_event(const sf::Event& event);
        virtual void on_render() = 0;
        virtual void on_update();

    public:

        DrawingArea();
        DrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

        // enable to call on_update() and on_render() periodically.
        void set_auto_update(bool enable);
        bool get_auto_update() const;


        using sf::RenderWindow::draw;
    };

}


#endif
