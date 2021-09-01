#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtkmm.h>


#ifdef NOT_INSTALLED
# include "DrawingArea.hpp"
#else
# include <gtk-sfml/DrawingArea.hpp>
#endif



struct MyDrawingArea :
    gtksfml::DrawingArea {

    sf::Font font;
    sf::Text text{"DrawingArea demo", font};


    MyDrawingArea()
    {
        set_size_request(512, 300);
        font.loadFromFile(DEMO_FONT);
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
