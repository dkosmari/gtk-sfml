#include <ostream>
#include <sstream>
#include <iomanip>

#include "examples-utils.hpp"


using std::string;
using std::ostream;
using std::ostringstream;
using std::boolalpha;


string
to_string(const sf::Event& e)
{
    ostringstream out;
    out << e;
    return out.str();
}


string
to_string(const sf::Event::KeyEvent& ke)
{
    ostringstream out;
    out << ke;
    return out.str();
}



#define CASE(x) \
    case Key::x: return #x

string
to_string(sf::Keyboard::Key k)
{
    using Key = sf::Keyboard::Key;

    switch (k) {
        CASE(Unknown);
        CASE(A); CASE(B); CASE(C); CASE(D); CASE(E);
        CASE(F); CASE(G); CASE(H); CASE(I); CASE(J);
        CASE(K); CASE(L); CASE(M); CASE(N); CASE(O);
        CASE(P); CASE(Q); CASE(R); CASE(S); CASE(T);
        CASE(U); CASE(V); CASE(W); CASE(X); CASE(Y);
        CASE(Z);
        CASE(Num0); CASE(Num1); CASE(Num2);
        CASE(Num3); CASE(Num4); CASE(Num5);
        CASE(Num6); CASE(Num7); CASE(Num8);
        CASE(Num9);
        CASE(Escape);
        CASE(LControl); CASE(LShift); CASE(LAlt); CASE(LSystem);
        CASE(RControl); CASE(RShift); CASE(RAlt); CASE(RSystem);
        CASE(Menu);
        CASE(LBracket); CASE(RBracket);
        CASE(Semicolon); CASE(Comma); CASE(Period);
        CASE(Quote); CASE(Slash);
        CASE(Backslash);
        CASE(Tilde);
        CASE(Equal); CASE(Hyphen);
        CASE(Space);
        CASE(Enter);
        CASE(Backspace);
        CASE(Tab);
        CASE(PageUp); CASE(PageDown);
        CASE(End); CASE(Home);
        CASE(Insert); CASE(Delete);
        CASE(Add); CASE(Subtract); CASE(Multiply); CASE(Divide);
        CASE(Left); CASE(Right); CASE(Up); CASE(Down);
        CASE(Numpad0); CASE(Numpad1); CASE(Numpad2);
        CASE(Numpad3); CASE(Numpad4); CASE(Numpad5);
        CASE(Numpad6); CASE(Numpad7); CASE(Numpad8);
        CASE(Numpad9);
        CASE(F1); CASE(F2); CASE(F3); CASE(F4); CASE(F5);
        CASE(F6); CASE(F7); CASE(F8); CASE(F9); CASE(F10);
        CASE(F11); CASE(F12); CASE(F13); CASE(F14); CASE(F15);
        CASE(Pause);
        default:
            return "invalid key code";
    }
}

#undef CASE




#define CASE(x)                                 \
    case sf::Event::EventType::x:               \
    out << #x;                                  \
    break


ostream&
operator<<(ostream& out,
           const sf::Event& e)
{
    switch (e.type) {
        case sf::Event::EventType::KeyPressed:
            out << "KeyPressed[" << e.key << "]";
            break;
        case sf::Event::EventType::KeyReleased:
            out << "KeyReleased[" << e.key << "]";
            break;

        CASE(Closed);
        CASE(Resized);
        CASE(LostFocus);
        CASE(GainedFocus);
        CASE(TextEntered);
        CASE(MouseWheelMoved);
        CASE(MouseWheelScrolled);
        CASE(MouseButtonPressed);
        CASE(MouseButtonReleased);
        CASE(MouseMoved);
        CASE(MouseEntered);
        CASE(MouseLeft);
        CASE(JoystickButtonPressed);
        CASE(JoystickButtonReleased);
        CASE(JoystickMoved);
        CASE(JoystickConnected);
        CASE(JoystickDisconnected);
        CASE(TouchBegan);
        CASE(TouchMoved);
        CASE(TouchEnded);
        CASE(SensorChanged);
        default:
            out << "unknown event type";
    }
    return out;
}

#undef CASE


ostream&
operator<<(ostream& out,
           const sf::Event::KeyEvent& ke)
{
    out << "code=" << ke.code;
    if (ke.alt)
        out << " +Alt";
    if (ke.control)
        out << " +Ctrl";
    if (ke.shift)
        out << " +Shift";
    if (ke.system)
        out << " +Sys";
    return out;
}


ostream&
operator<<(ostream& out,
           sf::Keyboard::Key k)
{
    return out << to_string(k);
}
