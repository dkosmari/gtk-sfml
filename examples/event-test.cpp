#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <gtkmm.h>


#include "DrawingArea.hpp"


using std::cout;
using std::endl;
using std::string;

using Glib::ustring;


#define CASE(x) \
    case sf::Event::EventType::x: \
    return #x

string
to_string(const sf::Event& e)
{
    switch (e.type) {
        CASE(Closed);
        CASE(Resized);
        CASE(LostFocus);
        CASE(GainedFocus);
        CASE(TextEntered);
        CASE(KeyPressed);
        CASE(KeyReleased);
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
            return "unknown event type";
    }
}

#undef CASE


#define TEST(x) \
    if (m & Gdk::EventMask::x) cout << "  " << #x << "\n"

void
print_event_mask(Gdk::EventMask m)
{
    cout << "Gdk::EventMask: {\n";
    TEST(EXPOSURE_MASK);
    TEST(POINTER_MOTION_MASK);
    TEST(POINTER_MOTION_HINT_MASK);
    TEST(BUTTON_MOTION_MASK);
    TEST(BUTTON1_MOTION_MASK);
    TEST(BUTTON2_MOTION_MASK);
    TEST(BUTTON3_MOTION_MASK);
    TEST(BUTTON_PRESS_MASK);
    TEST(BUTTON_RELEASE_MASK);
    TEST(KEY_PRESS_MASK);
    TEST(KEY_RELEASE_MASK);
    TEST(ENTER_NOTIFY_MASK);
    TEST(LEAVE_NOTIFY_MASK);
    TEST(FOCUS_CHANGE_MASK);
    TEST(STRUCTURE_MASK);
    TEST(PROPERTY_CHANGE_MASK);
    TEST(VISIBILITY_NOTIFY_MASK);
    TEST(PROXIMITY_IN_MASK);
    TEST(PROXIMITY_OUT_MASK);
    TEST(SUBSTRUCTURE_MASK);
    TEST(SCROLL_MASK);
    TEST(TOUCH_MASK);
    TEST(SMOOTH_SCROLL_MASK);
    TEST(TOUCHPAD_GESTURE_MASK);
    TEST(TABLET_PAD_MASK);
    cout << "}\n";
    cout.flush();
}


struct MyWidget : gtksfml::DrawingArea {

    using Parent = gtksfml::DrawingArea;

    sf::Font font;

    sf::Text fps_text;
    sf::Text update_time_text;
    unsigned frame_counter = 0;


    MyWidget()
    {
        set_can_focus(true);

        font.loadFromFile(SRCDIR "/LiberationSans-Regular.ttf");

        update_time_text.setFont(font);
        update_time_text.setPosition(40, 20);

        fps_text.setFont(font);
        fps_text.setString("FPS: n/a");
        fps_text.setFillColor(sf::Color::Yellow);
        fps_text.setPosition(40, 80);

        Glib::signal_timeout()
            .connect_seconds(sigc::mem_fun(*this, &MyWidget::update_fps), 1);
    }


    bool update_fps()
    {
        string msg = ustring::format("FPS: ", frame_counter);
        fps_text.setString(msg);
        frame_counter = 0;
        return G_SOURCE_CONTINUE;
    }


    void on_render() override
    {
        if (has_focus())
            clear({0, 16, 64});
        else
            clear({0, 0, 64});
        draw(update_time_text);
        draw(fps_text);
        display();
        ++frame_counter;
    }


    void on_update(gint64 us)
    {
        string msg = ustring::format("update time: ", us/1000000.);
        update_time_text.setString(msg);

        sf::Event event;
        bool has_event = false;
        while (pollEvent(event)) {
            if (has_event)
                cout << " ";
            has_event = true;
            cout << to_string(event);

            // grab focus on click
            if (event.type == sf::Event::EventType::MouseButtonPressed)
                grab_focus();

        }
        if (has_event)
            cout << endl;
    }


    bool on_key_press_event(GdkEventKey* event) override
    {
        // Key press events are always handled by GTK+, not by SFML.
        cout << "on_key_press_event(): "
             << event->keyval << endl;
        return Parent::on_key_press_event(event);
    }


    /*
     * Because there are multiple widgets, prevent the widget from
     * losing focus from GUI navigation.  Focus can still be lost by
     * mouse clicks or shortcuts.
     */
    bool on_focus(Gtk::DirectionType dir) override
    {
        if (is_focus())
            return true;
        return Parent::on_focus(dir);
    }


    /*
     * Because there are multiple widgets, let's make sure it starts
     * with focus.
     */
    void on_realize() override
    {
        Parent::on_realize();
        grab_focus(); // start with focus
    }

};



/*
 * GTK+ handles the gained/lost focus events, on the toplevel window.
 * So this must be used instead of sf::Event::LostFocus and
 * sf::Event::GainedFocus.
 */

struct MyWindow : public Gtk::ApplicationWindow {

    bool on_focus_in_event(GdkEventFocus* event) override
    {
        cout << "MyWindow::on_focus_in_event()" << endl;
        return Gtk::ApplicationWindow::on_focus_in_event(event);
    }


    bool on_focus_out_event(GdkEventFocus* event) override
    {
        cout << "MyWindow::on_focus_out_event()" << endl;
        return Gtk::ApplicationWindow::on_focus_out_event(event);
    }

};



int main()
{
    auto app = Gtk::Application::create();
    MyWindow window;
    window.set_default_size(640, 480);
    window.set_border_width(18);

    Gtk::Box vbox{Gtk::Orientation::ORIENTATION_VERTICAL, 6};
    window.add(vbox);

    MyWidget widget;
    vbox.pack_start(widget);

    Gtk::Box hbox{Gtk::Orientation::ORIENTATION_HORIZONTAL, 12};
    vbox.pack_start(hbox, Gtk::PackOptions::PACK_SHRINK);
    hbox.set_homogeneous(true);

    Gtk::Button do_nothing{"_Do nothing", true};
    hbox.pack_start(do_nothing);

    Gtk::Button close{"_Close", true};
    hbox.pack_start(close);
    close.signal_clicked().connect([&window]{ window.close(); });

    window.show_all();
    return app->run(window);
}
