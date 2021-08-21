#include <iomanip>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <gtkmm.h>


#include "DrawingArea.hpp"


#include "examples-utils.hpp"


using std::cout;
using std::endl;
using std::string;

using Glib::ustring;




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
    sf::Text time_text;
    unsigned frame_counter = 0;
    bool has_event = false;


    MyWidget()
    {
        set_can_focus(true);

        font.loadFromFile(SRCDIR "/LiberationSans-Regular.ttf");

        time_text.setFont(font);
        time_text.setPosition(40, 20);

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
        draw(time_text);
        draw(fps_text);
        display();
        ++frame_counter;
    }


    // called before on_render()
    void on_update(gint64 us)
    {
        // this will dispatch events to on_event()
        gtksfml::DrawingArea::on_update(us);

        string msg = ustring::format("time: ",
                                     std::fixed,
                                     std::setprecision(2),
                                     us/1000000.);
        time_text.setString(msg);

        if (has_event) {
            has_event = false;
            cout << endl;
        }
    }


    // Override this instead of calling pollEvent(), because some
    // events are translated from GTK+, and SFML never gets to see
    // them.
    void on_event(const sf::Event& event) override
    {
        if (event.type == sf::Event::EventType::KeyPressed ||
            event.type == sf::Event::EventType::KeyReleased) {

            if (has_event)
                cout << " ";
            has_event = true;
            cout << event;
        }

        // grab focus on click
        if (event.type == sf::Event::EventType::MouseButtonPressed)
                grab_focus();
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
