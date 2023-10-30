#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtkmm.h>

#include <gtk-sfml/Window.hpp>

#include "font.hpp"


struct MyWindow :
    gtksfml::Window {

    sf::Font font;
    sf::Text text{"Window demo", font};


    MyWindow()
    {
        set_default_size(500, 300);
        font.loadFromMemory(FONT_DATA, FONT_SIZE);
        text.setPosition(100, 100);
    }


    void on_render() override
    {
        clear({64, 0, 0});
        draw(text);
        display();
    }

};


int main()
{
    auto app = Gtk::Application::create();
    MyWindow window;
    return app->run(window);
}
