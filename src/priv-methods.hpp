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


#ifndef GTKSFML_PRIV_METHODS_HPP
#define GTKSFML_PRIV_METHODS_HPP


#include <SFML/OpenGL.hpp>
#include <gdkmm/general.h>


#define IMPL_BUILDER_CONSTRUCTOR(T)                                     \
    T::T(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>&) :  \
        Gtk::T{cobject}                                                 \
    {                                                                   \
        set_auto_update(true);                                          \
    }


#define IMPL_SET_AUTO_UPDATE(T)                                                 \
    void                                                                        \
    T::set_auto_update(bool enable)                                             \
    {                                                                           \
        if (enable == auto_update_state)                                        \
            return;                                                             \
        auto_update_state = enable;                                             \
        if (enable)                                                             \
            tick_id = add_tick_callback(sigc::mem_fun(*this, &T::on_tick));     \
        else                                                                    \
            remove_tick_callback(tick_id);                                      \
    }


#define IMPL_GET_AUTO_UPDATE(T)                 \
    bool                                        \
    T::get_auto_update() const                  \
    {                                           \
        return auto_update_state;               \
    }


#define IMPL_ON_REALIZE(T)                              \
    void                                                \
    T::on_realize()                                     \
    {                                                   \
        Gtk::T::on_realize();                           \
        auto handle = get_handle(get_window()->gobj()); \
        create(handle);                                 \
    }


#define IMPL_ON_UNREALIZE(T)                    \
    void                                        \
    T::on_unrealize()                           \
    {                                           \
        sf::RenderWindow::close();              \
        Gtk::T::on_unrealize();                 \
    }


#define IMPL_ON_DRAW(T)                                 \
    bool                                                \
    T::on_draw(const Cairo::RefPtr<Cairo::Context>&)    \
    {                                                   \
        setActive(true);                                \
        on_render();                                    \
        return true;                                    \
    }


#define IMPL_ON_DRAW_BROKEN(T)                                  \
    bool                                                        \
    T::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)         \
    {                                                           \
        on_render();                                            \
        Gdk::Cairo::draw_from_gl(cr,                            \
                                 get_window(),                  \
                                 0,                             \
                                 GL_RENDERBUFFER,               \
                                 get_scale_factor(),            \
                                 0,                             \
                                 0,                             \
                                 get_allocated_width(),         \
                                 get_allocated_height());       \
        return true;                                            \
    }




#define IMPL_ON_TICK(T)                                         \
    bool                                                        \
    T::on_tick(const Glib::RefPtr<Gdk::FrameClock>& clock)      \
    {                                                           \
        sf::Event event;                                        \
        while (pollEvent(event))                                \
            on_event(event);                                    \
        on_update(clock->get_frame_time());                     \
        queue_draw();                                           \
        return G_SOURCE_CONTINUE;                               \
    }


#define IMPL_ON_UPDATE(T)                       \
    void                                        \
    T::on_update(gint64)                        \
    {}


#define IMPL_ON_EVENT(T)                        \
    void                                        \
    T::on_event(const sf::Event&)               \
    {}


#define IMPL_ON_KEY_PRESS_EVENT(T)                                      \
    bool                                                                \
    T::on_key_press_event(GdkEventKey* key_event)                       \
    {                                                                   \
        sf::Event event;                                                \
        event.type = sf::Event::EventType::KeyPressed;                  \
        event.key = translate(key_event);                               \
        on_event(event);                                                \
        if (guint32 u = gdk_keyval_to_unicode(key_event->keyval)) {     \
            sf::Event tevent;                                           \
            tevent.type = sf::Event::EventType::TextEntered;            \
            tevent.text.unicode = u;                                    \
            on_event(tevent);                                           \
        }                                                               \
        return Gtk::T::on_key_press_event(key_event);                   \
    }


#define IMPL_ON_KEY_RELEASE_EVENT(T)                    \
    bool                                                \
    T::on_key_release_event(GdkEventKey* key_event)     \
    {                                                   \
        sf::Event event;                                \
        event.type = sf::Event::EventType::KeyReleased; \
        event.key = translate(key_event);               \
        on_event(event);                                \
        return Gtk::T::on_key_release_event(key_event); \
    }



#define IMPL_ON_FOCUS_IN_EVENT(T)                       \
    bool                                                \
    T::on_focus_in_event(GdkEventFocus* focus_event)    \
    {                                                   \
        sf::Event event;                                \
        event.type = sf::Event::EventType::GainedFocus; \
        on_event(event);                                \
        return Gtk::T::on_focus_in_event(focus_event);  \
    }


#define IMPL_ON_FOCUS_OUT_EVENT(T)                      \
    bool                                                \
    T::on_focus_out_event(GdkEventFocus* focus_event)   \
    {                                                   \
        sf::Event event;                                \
        event.type = sf::Event::EventType::LostFocus;   \
        on_event(event);                                \
        return Gtk::T::on_focus_out_event(focus_event); \
    }


#define IMPL_ALL(T)                             \
    IMPL_BUILDER_CONSTRUCTOR(T)                 \
    IMPL_SET_AUTO_UPDATE(T)                     \
    IMPL_GET_AUTO_UPDATE(T)                     \
    IMPL_ON_REALIZE(T)                          \
    IMPL_ON_UNREALIZE(T)                        \
    IMPL_ON_DRAW(T)                             \
    IMPL_ON_TICK(T)                             \
    IMPL_ON_UPDATE(T)                           \
    IMPL_ON_EVENT(T)                            \
    IMPL_ON_KEY_PRESS_EVENT(T)                  \
    IMPL_ON_KEY_RELEASE_EVENT(T)                \
    IMPL_ON_FOCUS_IN_EVENT(T)                   \
    IMPL_ON_FOCUS_OUT_EVENT(T)


#endif
