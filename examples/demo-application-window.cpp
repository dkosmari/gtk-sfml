#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtkmm.h>


#ifdef NOT_INSTALLED
# include "ApplicationWindow.hpp"
#else
# include <gtk-sfml/ApplicationWindow.hpp>
#endif


struct MyApplicationWindow :
    gtksfml::ApplicationWindow {

    sf::Font font;
    sf::Text text{"ApplicationWindow demo", font};


    MyApplicationWindow()
    {
        set_default_size(500, 300);
        font.loadFromFile(DEMO_FONT);
        text.setPosition(100, 100);
    }


    void on_render() override
    {
        clear({0, 64, 0});
        draw(text);
        display();
    }

};


int main()
{
    auto app = Gtk::Application::create();
    MyApplicationWindow window;
    return app->run(window);
}
