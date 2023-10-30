// SPDX-License-Identifier: GPL-3.0-or-later

/*
 *  gtk-sfml - a set of widgets for integrating SFML into gtkmm3.
 *  Copyright (C) 2023  Daniel K. O.
 */

#ifndef GTKSFML_WINDOW_HPP
#define GTKSFML_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <gtkmm/builder.h>
#include <gtkmm/window.h>


namespace gtksfml {


    class Window : public Gtk::Window,
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
        bool on_motion_notify_event(GdkEventMotion* event) override;
        bool on_button_press_event(GdkEventButton* event) override;
        bool on_button_release_event(GdkEventButton* event) override;
        bool on_scroll_event(GdkEventScroll* event) override;
        void on_realize() override;
        void on_unrealize() override;

        bool on_tick(const Glib::RefPtr<Gdk::FrameClock>& clock);

        // user should override these
        virtual void on_event(const sf::Event& event);
        virtual void on_render() = 0;
        virtual void on_update();

    public:

        Window(Gtk::WindowType type = Gtk::WindowType::WINDOW_TOPLEVEL);
        Window(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

        // enable to call on_update() and on_render() periodically.
        void set_auto_update(bool enable);
        bool get_auto_update() const;


        using sf::RenderWindow::draw;
        using Gtk::Window::close;
    };


}

#endif
