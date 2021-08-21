#include <string>

#include <SFML/Graphics.hpp>
#include <gtkmm.h>

#include "DrawingArea.hpp"


struct MyWidget : gtksfml::DrawingArea {

    sf::Font font;
    sf::Text hello_text;
    sf::Text fps_text;
    unsigned frame_counter = 0;


    MyWidget()
    {
        font.loadFromFile(SRCDIR "/LiberationSans-Regular.ttf");

        hello_text.setFont(font);
        hello_text.setString("Hello World!");
        hello_text.setPosition(40, 20);

        fps_text.setFont(font);
        fps_text.setString("FPS: n/a");
        fps_text.setFillColor(sf::Color::Yellow);
        fps_text.setPosition(40, 80);

        Glib::signal_timeout().
            connect_seconds(sigc::mem_fun(*this, &MyWidget::update_fps),
                            1);
    }


    bool update_fps()
    {
        std::string msg = Glib::ustring::format("FPS: ", frame_counter);
        fps_text.setString(msg);
        frame_counter = 0;
        return G_SOURCE_CONTINUE;
    }


    void on_render() override
    {
        clear({0, 64, 128});
        draw(hello_text);
        draw(fps_text);
        display();
        ++frame_counter;
    }

};


int main()
{
    auto app = Gtk::Application::create();
    Gtk::ApplicationWindow window;
    window.set_default_size(640, 480);
    MyWidget widget;
    widget.show();
    window.add(widget);
    return app->run(window);
}
