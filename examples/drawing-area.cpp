#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtkmm.h>

#include <gtk-sfml/DrawingArea.hpp>

#include "font.hpp"


struct MyDrawingArea :
    gtksfml::DrawingArea {

    sf::Font font;
    sf::Text text{"DrawingArea demo", font};


    MyDrawingArea()
    {
        set_size_request(512, 300);
        font.loadFromMemory(FONT_DATA, FONT_SIZE);
        text.setPosition(100, 100);
    }


    void on_render() override
    {
        clear({0, 0, 255});
        draw(text);
        display();
    }

};


int main()
{
    auto app = Gtk::Application::create();
    Gtk::ApplicationWindow window;
    MyDrawingArea area;
    area.show();
    window.add(area);
    return app->run(window);
}
