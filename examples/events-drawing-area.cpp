#include <iomanip>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <gtkmm.h>

#include <gtk-sfml/DrawingArea.hpp>

#include "font.hpp"
#include "utils.hpp"


using std::cout;
using std::endl;
using std::string;

using Glib::ustring;



struct MyWidget : gtksfml::DrawingArea {


    using Parent = gtksfml::DrawingArea;

    sf::Font font;

    sf::Text fps_text;
    sf::Text time_text;
    unsigned frame_counter = 0;
    bool has_event = false;
    sf::Clock time_clock;


    MyWidget()
    {
        set_can_focus(true);

        font.loadFromMemory(FONT_DATA, FONT_SIZE);

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
            clear({0, 16, 96});
        else
            clear({32, 32, 64});
        draw(time_text);
        draw(fps_text);
        display();
        ++frame_counter;
    }


    // called before on_render()
    void on_update() override
    {
        float t = time_clock.getElapsedTime().asSeconds();
        string msg = ustring::format("time: ",
                                     std::fixed,
                                     std::setprecision(2),
                                     t);
        time_text.setString(msg);

        if (has_event) {
            has_event = false;
            cout << endl;
        }
    }


    /*
     * Override this instead of calling pollEvent(), because some
     * events are handled by GTK+, and SFML never gets to see
     * them directly. But gtk-sfml translates them into SFML
     * for this method.
     */
    void on_event(const sf::Event& event) override
    {
        if (has_event)
            cout << " ";
        has_event = true;
        cout << event;

        // grab focus on click
        if (event.type == sf::Event::EventType::MouseButtonPressed)
            grab_focus();
    }


    /*
     * Because there are multiple widgets, prevent the widget from
     * losing focus from GUI navigation. Focus can still be lost by
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



int main()
{
    auto app = Gtk::Application::create();
    Gtk::Window window;
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
