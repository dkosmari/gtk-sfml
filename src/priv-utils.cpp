// SPDX-License-Identifier: GPL-3.0-or-later

/*
 *  gtk-sfml - a set of widgets for integrating SFML into gtkmm3.
 *  Copyright (C) 2023  Daniel K. O.
 */

#include "priv-utils.hpp"


using std::pair;


namespace gtksfml::priv::utils {


    sf::Keyboard::Key
    translate_key(guint val)
    {
        using Key = sf::Keyboard::Key;

        switch (val) {
            case GDK_KEY_A: case GDK_KEY_a:
                return Key::A;
            case GDK_KEY_B: case GDK_KEY_b:
                return Key::B;
            case GDK_KEY_C: case GDK_KEY_c:
                return Key::C;
            case GDK_KEY_D: case GDK_KEY_d:
                return Key::D;
            case GDK_KEY_E: case GDK_KEY_e:
                return Key::E;
            case GDK_KEY_F: case GDK_KEY_f:
                return Key::F;
            case GDK_KEY_G: case GDK_KEY_g:
                return Key::G;
            case GDK_KEY_H: case GDK_KEY_h:
                return Key::H;
            case GDK_KEY_I: case GDK_KEY_i:
                return Key::I;
            case GDK_KEY_J: case GDK_KEY_j:
                return Key::J;
            case GDK_KEY_K: case GDK_KEY_k:
                return Key::K;
            case GDK_KEY_L: case GDK_KEY_l:
                return Key::L;
            case GDK_KEY_M: case GDK_KEY_m:
                return Key::M;
            case GDK_KEY_N: case GDK_KEY_n:
                return Key::N;
            case GDK_KEY_O: case GDK_KEY_o:
                return Key::O;
            case GDK_KEY_P: case GDK_KEY_p:
                return Key::P;
            case GDK_KEY_Q: case GDK_KEY_q:
                return Key::Q;
            case GDK_KEY_R: case GDK_KEY_r:
                return Key::R;
            case GDK_KEY_S: case GDK_KEY_s:
                return Key::S;
            case GDK_KEY_T: case GDK_KEY_t:
                return Key::T;
            case GDK_KEY_U: case GDK_KEY_u:
                return Key::U;
            case GDK_KEY_V: case GDK_KEY_v:
                return Key::V;
            case GDK_KEY_W: case GDK_KEY_w:
                return Key::W;
            case GDK_KEY_X: case GDK_KEY_x:
                return Key::X;
            case GDK_KEY_Y: case GDK_KEY_y:
                return Key::Y;
            case GDK_KEY_Z: case GDK_KEY_z:
                return Key::Z;

            case GDK_KEY_0: case GDK_KEY_parenright:
                return Key::Num0;
            case GDK_KEY_1: case GDK_KEY_exclam:
                return Key::Num1;
            case GDK_KEY_2: case GDK_KEY_at:
                return Key::Num2;
            case GDK_KEY_3: case GDK_KEY_numbersign:
                return Key::Num3;
            case GDK_KEY_4: case GDK_KEY_dollar:
                return Key::Num4;
            case GDK_KEY_5: case GDK_KEY_percent:
                return Key::Num5;
            case GDK_KEY_6: case GDK_KEY_asciicircum:
                return Key::Num6;
            case GDK_KEY_7: case GDK_KEY_ampersand:
                return Key::Num7;
            case GDK_KEY_8: case GDK_KEY_asterisk:
                return Key::Num8;
            case GDK_KEY_9: case GDK_KEY_parenleft:
                return Key::Num9;

            case GDK_KEY_Escape:
                return Key::Escape;

            case GDK_KEY_Control_L:
                return Key::LControl;

            case GDK_KEY_Control_R:
                return Key::RControl;

            case GDK_KEY_Shift_L:
                return Key::LShift;

            case GDK_KEY_Shift_R:
                return Key::RShift;

            case GDK_KEY_Alt_L: case GDK_KEY_Meta_L:
                return Key::LAlt;
            case GDK_KEY_Alt_R: case GDK_KEY_Meta_R:
                return Key::RAlt;

            case GDK_KEY_Super_L:
                return Key::LSystem;

            case GDK_KEY_Super_R:
                return Key::RSystem;

            case GDK_KEY_Menu:
                return Key::Menu;

            case GDK_KEY_bracketleft: case GDK_KEY_braceleft:
                return Key::LBracket;
            case GDK_KEY_bracketright: case GDK_KEY_braceright:
                return Key::RBracket;
            case GDK_KEY_semicolon: case GDK_KEY_colon:
                return Key::Semicolon;
            case GDK_KEY_comma: case GDK_KEY_less:
                return Key::Comma;
            case GDK_KEY_period: case GDK_KEY_greater:
                return Key::Period;
            case GDK_KEY_apostrophe: case GDK_KEY_quotedbl:
                return Key::Quote;
            case GDK_KEY_slash: case GDK_KEY_question:
                return Key::Slash;
            case GDK_KEY_backslash: case GDK_KEY_bar:
                return Key::Backslash;
            case GDK_KEY_grave: case GDK_KEY_asciitilde:
                return Key::Tilde;
            case GDK_KEY_equal: case GDK_KEY_plus:
                return Key::Equal;
            case GDK_KEY_minus: case GDK_KEY_underscore:
                return Key::Hyphen;

            case GDK_KEY_space:
                return Key::Space;

            case GDK_KEY_Return: case GDK_KEY_KP_Enter:
                return Key::Enter;

            case GDK_KEY_BackSpace:
                return Key::Backspace;

            case GDK_KEY_Tab:
                return Key::Tab;

            case GDK_KEY_Page_Up:
                return Key::PageUp;

            case GDK_KEY_Page_Down:
                return Key::PageDown;

            case GDK_KEY_End:
                return Key::End;

            case GDK_KEY_Home:
                return Key::Home;

            case GDK_KEY_Insert:
                return Key::Insert;

            case GDK_KEY_Delete:
                return Key::Delete;

            case GDK_KEY_KP_Add:
                return Key::Add;

            case GDK_KEY_KP_Subtract:
                return Key::Subtract;

            case GDK_KEY_KP_Multiply:
                return Key::Multiply;

            case GDK_KEY_KP_Divide:
                return Key::Divide;

            case GDK_KEY_Left:
                return Key::Left;
            case GDK_KEY_Right:
                return Key::Right;
            case GDK_KEY_Up:
                return Key::Up;
            case GDK_KEY_Down:
                return Key::Down;

            case GDK_KEY_KP_0: case GDK_KEY_KP_Insert:
                return Key::Numpad0;
            case GDK_KEY_KP_1: case GDK_KEY_KP_End:
                return Key::Numpad1;
            case GDK_KEY_KP_2: case GDK_KEY_KP_Down:
                return Key::Numpad2;
            case GDK_KEY_KP_3: case GDK_KEY_KP_Page_Down:
                return Key::Numpad3;
            case GDK_KEY_KP_4: case GDK_KEY_KP_Left:
                return Key::Numpad4;
            case GDK_KEY_KP_5: case GDK_KEY_KP_Begin:
                return Key::Numpad5;
            case GDK_KEY_KP_6: case GDK_KEY_KP_Right:
                return Key::Numpad6;
            case GDK_KEY_KP_7: case GDK_KEY_KP_Home:
                return Key::Numpad7;
            case GDK_KEY_KP_8: case GDK_KEY_KP_Up:
                return Key::Numpad8;
            case GDK_KEY_KP_9: case GDK_KEY_KP_Page_Up:
                return Key::Numpad9;

            case GDK_KEY_F1:
                return Key::F1;
            case GDK_KEY_F2:
                return Key::F2;
            case GDK_KEY_F3:
                return Key::F3;
            case GDK_KEY_F4:
                return Key::F4;
            case GDK_KEY_F5:
                return Key::F5;
            case GDK_KEY_F6:
                return Key::F6;
            case GDK_KEY_F7:
                return Key::F7;
            case GDK_KEY_F8:
                return Key::F8;
            case GDK_KEY_F9:
                return Key::F9;
            case GDK_KEY_F10:
                return Key::F10;
            case GDK_KEY_F11:
                return Key::F11;
            case GDK_KEY_F12:
                return Key::F12;
            case GDK_KEY_F13:
                return Key::F13;
            case GDK_KEY_F14:
                return Key::F14;
            case GDK_KEY_F15:
                return Key::F15;

            case GDK_KEY_Pause:
                return Key::Pause;

            default:
                return Key::Unknown;
        }
    }


    sf::Event::KeyEvent
    translate(GdkEventKey* gkey)
    {
        sf::Event::KeyEvent result;

        auto state = gkey->state;
        result.alt = state & GDK_META_MASK;
        result.control = state & GDK_CONTROL_MASK;
        result.shift = state & GDK_SHIFT_MASK;
        result.system = state & GDK_SUPER_MASK;

        result.code = translate_key(gkey->keyval);

        return result;
    }


    WinHandle
    get_handle(GdkWindow* w)
    {
#if defined(GDK_WINDOWING_X11)
        return gdk_x11_window_get_xid(w);
#elif defined(GDK_WINDOWING_WIN32)
        return gdk_win32_window_get_handle(w);
#endif
    }


    sf::Mouse::Button
    translate_button(guint b)
    {
        switch (b) {
            case 1:
                return sf::Mouse::Button::Left;
            case 2:
                return sf::Mouse::Button::Middle;
            case 3:
                return sf::Mouse::Button::Right;
            case 4:
                return sf::Mouse::Button::XButton1;
            case 5:
                return sf::Mouse::Button::XButton2;
            default:
                return sf::Mouse::Button::ButtonCount;
        }
    }


    sf::Event::MouseButtonEvent
    translate(GdkEventButton* motion_event)
    {
        sf::Event::MouseButtonEvent result;
        result.x = motion_event->x;
        result.y = motion_event->y;
        result.button = translate_button(motion_event->button);
        return result;
    }




    sf::Event::MouseWheelEvent
    translate_vert(GdkEventScroll* scroll_event)
    {
        sf::Event::MouseWheelEvent e;
        e.x = scroll_event->x;
        e.y = scroll_event->y;
        switch (scroll_event->direction) {
            case GDK_SCROLL_UP:
                e.delta = 1;
                break;
            case GDK_SCROLL_DOWN:
                e.delta = -1;
                break;
            default:
                e.delta = 0;
        }
        return e;
    }


    pair<sf::Event::MouseWheelScrollEvent,
         sf::Event::MouseWheelScrollEvent>
    translate_smooth(GdkEventScroll* scroll_event)
    {
        sf::Event::MouseWheelScrollEvent h, v;

        h.wheel = sf::Mouse::Wheel::HorizontalWheel;
        v.wheel = sf::Mouse::Wheel::VerticalWheel;

        h.x = v.x = scroll_event->x;
        h.y = v.y = scroll_event->y;

        if (scroll_event->direction == GDK_SCROLL_SMOOTH) {
            // TODO: check if horizontal sign matches SFML
            h.delta = -scroll_event->delta_x;
            v.delta = -scroll_event->delta_y;
        } else
            h.delta = v.delta = 0;

        return {h, v};
    }

}
