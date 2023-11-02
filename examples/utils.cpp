#include <ostream>
#include <sstream>
#include <iomanip>

#include "utils.hpp"


using std::string;
using std::ostream;
using std::ostringstream;
using std::boolalpha;
using std::setw;
using std::hex;
using std::setfill;
using std::uppercase;

using sf::Event;


string
to_hex(sf::Uint32 val, unsigned digits = 0)
{
    ostringstream out;

    out << setfill('0')
        << hex
        << uppercase
        << setw(digits)
        << val;

    return out.str();
}


string
to_string(const Event& e)
{
    ostringstream out;
    out << e;
    return out.str();
}


string
to_string(const Event::KeyEvent& ke)
{
    ostringstream out;
    out << ke;
    return out.str();
}



#define CASE(x) case sf::Joystick::Axis::x: return #x

string
to_string(sf::Joystick::Axis a)
{
    switch (a) {
        CASE(X);
        CASE(Y);
        CASE(Z);
        CASE(R);
        CASE(U);
        CASE(V);
        CASE(PovX);
        CASE(PovY);
        default:
            return "invalid axis code";
    }
}

#undef CASE




#define CASE(x) case sf::Keyboard::Key::x: return #x

string
to_string(sf::Keyboard::Key k)
{
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



#define CASE(x) case sf::Mouse::Button::x: return #x

string
to_string(sf::Mouse::Button b)
{
    switch (b) {
        CASE(Left);
        CASE(Right);
        CASE(Middle);
        CASE(XButton1);
        CASE(XButton2);
        default:
            return "invalid button code";
    }
}

#undef CASE


string
to_string(sf::Mouse::Wheel w)
{
    switch (w) {
        case sf::Mouse::Wheel::VerticalWheel:
            return "VerticalWheel";
        case sf::Mouse::Wheel::HorizontalWheel:
            return "HorizontalWheel";
        default:
            return "invalid wheel code";
    }
}


#define CASE(x) case sf::Sensor::Type::x: return #x

string to_string(sf::Sensor::Type t)
{
    switch (t) {
        CASE(Accelerometer);
        CASE(Gyroscope);
        CASE(Magnetometer);
        CASE(Gravity);
        CASE(UserAcceleration);
        CASE(Orientation);
        default:
            return "invalid sensor type";
    }
}

#undef CASE



ostream&
operator<<(ostream& out,
           const Event& e)
{
    using ET = Event::EventType;

    switch (e.type) {
        case ET::Closed:
            out << "Closed";
            break;
        case ET::GainedFocus:
            out << "GainedFocus";
            break;

        case ET::JoystickButtonPressed:
            out << "JoystickButtonPressed[" << e.joystickButton << "]";
            break;
        case ET::JoystickButtonReleased:
            out << "JoystickButtonReleased[" << e.joystickButton << "]";
            break;
        case ET::JoystickMoved:
            out << "JoystickMoved[" << e.joystickMove << "]";
            break;
        case ET::JoystickConnected:
            out << "JoystickConnected[" << e.joystickConnect << "]";
            break;
        case ET::JoystickDisconnected:
            out << "JoystickDisconnected[" << e.joystickConnect << "]";
            break;
        case ET::KeyPressed:
            out << "KeyPressed[" << e.key << "]";
            break;
        case ET::KeyReleased:
            out << "KeyReleased[" << e.key << "]";
            break;
        case ET::LostFocus:
            out << "LostFocus";
            break;
        case ET::MouseMoved:
            out << "MouseMoved[" << e.mouseMove << "]";
            break;
        case ET::MouseButtonPressed:
            out << "MouseButtonPressed[" << e.mouseButton << "]";
            break;
        case ET::MouseButtonReleased:
            out << "MouseButtonReleased[" << e.mouseButton << "]";
            break;
        case ET::MouseEntered:
            out << "MouseEntered";
            break;
        case ET::MouseLeft:
            out << "MouseLeft";
            break;
        case ET::MouseWheelMoved:
            out << "MouseWheelMoved[" << e.mouseWheel << "]";
            break;
        case ET::MouseWheelScrolled:
            out << "MouseWheelScrolled[" << e.mouseWheelScroll << "]";
            break;
        case ET::Resized:
            out << "Resized[" << e.size << "]";
            break;
        case ET::SensorChanged:
            out << "SensorChanged[" << e.sensor << "]";
            break;
        case ET::TextEntered:
            out << "TextEntered[" << e.text << "]";
            break;
        case ET::TouchBegan:
            out << "TouchBegan[" << e.touch << "]";
            break;
        case ET::TouchEnded:
            out << "TouchEnded[" << e.touch << "]";
            break;
        case ET::TouchMoved:
            out << "TouchMoved[" << e.touch << "]";
            break;

        default:
            out << "unknown event type";
    }
    return out;
}

#undef CASE


ostream&
operator<<(ostream& out, const Event::JoystickButtonEvent& button)
{
    return out << "joystick=" << button.joystickId
               << ", button=" << button.button;
}


ostream&
operator<<(ostream& out, const Event::JoystickConnectEvent& connect)
{
    return out << "joystick=" << connect.joystickId;
}


ostream&
operator<<(ostream& out, const Event::JoystickMoveEvent& move)
{
    return out << "joystick=" << move.joystickId
               << ", axis=" << move.axis
               << ", position=" << move.position;
}


ostream&
operator<<(ostream& out,
           const Event::KeyEvent& ke)
{
    out << "code=" << ke.code;
    if (ke.alt)
        out << ", Alt";
    if (ke.control)
        out << ", Ctrl";
    if (ke.shift)
        out << ", Shift";
    if (ke.system)
        out << ", Sys";
    return out;
}


ostream&
operator<<(ostream& out, const Event::MouseButtonEvent& button)
{
    return out << "button=" << button.button
               << ", x=" << button.x
               << ", y=" << button.y;

}


ostream&
operator<<(ostream& out, const Event::MouseMoveEvent& move)
{
    return out << "x=" << move.x
               << ", y=" << move.y;
}


ostream&
operator<<(ostream& out, const Event::MouseWheelEvent& wheel)
{
    return out << "delta=" << wheel.delta
               << ", x=" << wheel.x
               << ", y=" << wheel.y;
}


ostream&
operator<<(ostream& out, const Event::MouseWheelScrollEvent& scroll)
{
    return out << "wheel=" << scroll.wheel
               << ", delta=" << scroll.delta
               << ", x=" << scroll.x
               << ", y=" << scroll.y;
}


ostream&
operator<<(ostream& out, const Event::SensorEvent& sensor)
{
    return out << "type=" << sensor.type
               << ", x=" << sensor.x
               << ", y=" << sensor.y
               << ", z=" << sensor.z;
}


ostream&
operator<<(ostream& out, const Event::SizeEvent& size)
{
    return out << "width=" << size.width
               << ", height=" << size.height;
}


ostream&
operator<<(ostream& out, const Event::TextEvent& te)
{
    return out << "unicode=U+" << to_hex(te.unicode, 4);
}


ostream&
operator<<(ostream& out, const Event::TouchEvent& touch)
{
    return out << "finger=" << touch.finger
               << ", x=" << touch.x
               << ", y=" << touch.y;
}




ostream&
operator<<(ostream& out, sf::Joystick::Axis a)
{
    return out << to_string(a);
}


ostream&
operator<<(ostream& out, sf::Keyboard::Key k)
{
    return out << to_string(k);
}


ostream&
operator<<(ostream& out, sf::Mouse::Button button)
{
    return out << to_string(button);
}


ostream&
operator<<(ostream& out, sf::Mouse::Wheel wheel)
{
    return out << to_string(wheel);
}


ostream&
operator<<(ostream& out, sf::Sensor::Type type)
{
    return out << to_string(type);
}
