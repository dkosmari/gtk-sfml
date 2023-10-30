// SPDX-License-Identifier: GPL-3.0-or-later

/*
 *  gtk-sfml - a set of widgets for integrating SFML into gtkmm3.
 *  Copyright (C) 2023  Daniel K. O.
 */

#ifndef GTKSFML_PRIV_METHODS_HPP
#define GTKSFML_PRIV_METHODS_HPP


#include <SFML/OpenGL.hpp>
#include <gdkmm/general.h>

#include "priv-utils.hpp"


using gtksfml::priv::utils::translate;
using gtksfml::priv::utils::get_handle;


#define IMPL_BUILDER_CONSTRUCTOR(T)                                     \
    T::T(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>&) :  \
        Gtk::T{cobject}                                                 \
    {                                                                   \
        init();                                                         \
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
    T::on_tick(const Glib::RefPtr<Gdk::FrameClock>&)            \
    {                                                           \
        sf::Event event;                                        \
        while (pollEvent(event))                                \
            on_event(event);                                    \
        on_update();                                            \
        queue_draw();                                           \
        return G_SOURCE_CONTINUE;                               \
    }


#define IMPL_ON_UPDATE(T)                       \
    void                                        \
    T::on_update()                              \
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


#define IMPL_ON_MOTION_NOTIFY_EVENT(T)                          \
    bool                                                        \
    T::on_motion_notify_event(GdkEventMotion* motion_event)     \
    {                                                           \
        sf::Event event;                                        \
        event.type = sf::Event::EventType::MouseMoved;          \
        event.mouseMove.x = motion_event->x;                    \
        event.mouseMove.y = motion_event->y;                    \
        on_event(event);                                        \
        return true;                                            \
    }


#define IMPL_ON_BUTTON_PRESS_EVENT(T)                                   \
    bool                                                                \
    T::on_button_press_event(GdkEventButton* button_event)              \
    {                                                                   \
        if (button_event->type != GDK_BUTTON_PRESS)                     \
            return false;                                               \
        sf::Event event;                                                \
        event.type = sf::Event::EventType::MouseButtonPressed;          \
        event.mouseButton = translate(button_event);                    \
        if (event.mouseButton.button != sf::Mouse::Button::ButtonCount) \
            on_event(event);                                            \
        return true;                                                    \
    }


#define IMPL_ON_BUTTON_RELEASE_EVENT(T)                                 \
    bool                                                                \
    T::on_button_release_event(GdkEventButton* button_event)            \
    {                                                                   \
        sf::Event event;                                                \
        event.type = sf::Event::EventType::MouseButtonReleased;         \
        event.mouseButton = translate(button_event);                    \
        if (event.mouseButton.button != sf::Mouse::Button::ButtonCount) \
            on_event(event);                                            \
        return true;                                                    \
    }


#define IMPL_ON_SCROLL_EVENT(T)                                                 \
    bool                                                                        \
    T::on_scroll_event(GdkEventScroll* scroll_event)                            \
    {                                                                           \
        sf::Event event;                                                        \
        switch (scroll_event->direction) {                                      \
            case GDK_SCROLL_UP:                                                 \
            case GDK_SCROLL_DOWN:                                               \
                event.type = sf::Event::EventType::MouseWheelMoved;             \
                event.mouseWheel = priv::utils::translate_vert(scroll_event);   \
                if (event.mouseWheel.delta)                                     \
                    on_event(event);                                            \
                return true;                                                    \
            case GDK_SCROLL_SMOOTH:                                             \
                {                                                               \
                    event.type = sf::Event::EventType::MouseWheelScrolled;      \
                    auto [eh, ev] = priv::utils::translate_smooth(scroll_event); \
                    if (eh.delta) {                                             \
                        event.mouseWheelScroll = eh;                            \
                        on_event(event);                                        \
                    }                                                           \
                    if (ev.delta) {                                             \
                        event.mouseWheelScroll = ev;                            \
                        on_event(event);                                        \
                    }                                                           \
                    return true;                                                \
                }                                                               \
            default:                                                            \
                return false;                                                   \
        }                                                                       \
    }



#define IMPL_ALL_WINDOW(T)                      \
    IMPL_ALL(T)                                 \
    IMPL_ON_MOTION_NOTIFY_EVENT(T)              \
    IMPL_ON_BUTTON_PRESS_EVENT(T)               \
    IMPL_ON_BUTTON_RELEASE_EVENT(T)             \
    IMPL_ON_SCROLL_EVENT(T)


#endif
