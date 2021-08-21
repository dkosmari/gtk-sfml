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

#include <iostream>

#include "utils.hpp"


using std::clog;
using std::endl;


namespace gtksfml::utils {


#define TR1(x, y)                            \
    case GDK_KEY_ ## x:                         \
    case GDK_KEY_ ## y:                         \
        return Key::x


#define NUM(x, y)                               \
    case GDK_KEY_ ## x:                         \
    case GDK_KEY_ ## y:                         \
        return Key::Num ## x


#define KP(x, y, z)                             \
    case GDK_KEY_KP_ ## x:                      \
    case GDK_KEY_KP_ ## y:                      \
        return Key::z


#define FK(x)                                   \
    case GDK_KEY_F ## x:                        \
        return Key::F ## x


#define DIR(x)                                  \
    case GDK_KEY_ ## x:                         \
        return Key::x


#define TR2(x, y, z)                            \
    case GDK_KEY_ ## x:                         \
    case GDK_KEY_ ## y:                         \
        return Key::z



    sf::Keyboard::Key
    translate(guint val)
    {
        using Key = sf::Keyboard::Key;

        //clog << "--- translating: " << val << endl;

        switch (val) {
            TR1(A, a);
            TR1(B, b);
            TR1(C, c);
            TR1(D, d);
            TR1(E, e);
            TR1(F, f);
            TR1(G, g);
            TR1(H, h);
            TR1(I, i);
            TR1(J, j);
            TR1(K, k);
            TR1(L, l);
            TR1(M, m);
            TR1(N, n);
            TR1(O, o);
            TR1(P, p);
            TR1(Q, q);
            TR1(R, r);
            TR1(S, s);
            TR1(T, t);
            TR1(U, u);
            TR1(V, v);
            TR1(W, w);
            TR1(X, x);
            TR1(Y, y);
            TR1(Z, z);

            NUM(0, parenright);
            NUM(1, exclam);
            NUM(2, at);
            NUM(3, numbersign);
            NUM(4, dollar);
            NUM(5, percent);
            NUM(6, asciicircum);
            NUM(7, ampersand);
            NUM(8, asterisk);
            NUM(9, parenleft);

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

            TR2(Alt_L, Meta_L, LAlt);
            TR2(Alt_R, Meta_R, RAlt);

            case GDK_KEY_Super_L:
                return Key::LSystem;

            case GDK_KEY_Super_R:
                return Key::RSystem;

            case GDK_KEY_Menu:
                return Key::Menu;

            TR2(bracketleft, braceleft, LBracket);
            TR2(bracketright, braceright, RBracket);
            TR2(semicolon, colon, Semicolon);
            TR2(comma, less, Comma);
            TR2(period, greater, Period);
            TR2(apostrophe, quotedbl, Quote);
            TR2(slash, question, Slash);
            TR2(backslash, bar, Backslash);
            TR2(grave, asciitilde, Tilde);
            TR2(equal, plus, Equal);
            TR2(minus, underscore, Hyphen);

            case GDK_KEY_space:
                return Key::Space;

            TR2(Return, KP_Enter, Enter);

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

            DIR(Left);
            DIR(Right);
            DIR(Up);
            DIR(Down);

            KP(0, Insert,    Numpad0);
            KP(1, End,       Numpad1);
            KP(2, Down,      Numpad2);
            KP(3, Page_Down, Numpad3);
            KP(4, Left,      Numpad4);
            KP(5, Begin,     Numpad5);
            KP(6, Right,     Numpad6);
            KP(7, Home,      Numpad7);
            KP(8, Up,        Numpad8);
            KP(9, Page_Up,   Numpad9);

            FK(1);
            FK(2);
            FK(3);
            FK(4);
            FK(5);
            FK(6);
            FK(7);
            FK(8);
            FK(9);
            FK(10);
            FK(11);
            FK(12);
            FK(13);
            FK(14);
            FK(15);

            case GDK_KEY_Pause:
                return Key::Pause;

            default:
                clog << "ERROR: not handled: " << gdk_keyval_name(val) << endl;
                return Key::Unknown;
        }
    }

#undef TR1
#undef NUM
#undef KP
#undef FK
#undef DIR
#undef TR2


    sf::Event::KeyEvent
    gtk_to_sfml(GdkEventKey* gkey)
    {
        sf::Event::KeyEvent result;

        // TODO: use gdk_keymap_add_virtual_modifiers()?
        auto state = gkey->state;
        result.alt = state & GDK_META_MASK;
        result.control = state & GDK_CONTROL_MASK;
        result.shift = state & GDK_SHIFT_MASK;
        result.system = state & GDK_SUPER_MASK;

        //clog << "::: hardware keycode: " << gkey->hardware_keycode << endl;
        result.code = translate(gkey->keyval);

        return result;
    }

}
