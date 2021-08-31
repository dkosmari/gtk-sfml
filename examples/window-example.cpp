#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtkmm.h>


#include "Window.hpp"

float radius = 40;


struct MyWindow : gtksfml::Window {

    sf::Vector2f speed{70, 40};
    sf::CircleShape ball{radius};
    sf::Clock frame_interval;


    MyWindow()
    {
        set_default_size(512, 512);

        ball.setOrigin(radius, radius);
        ball.setPosition(100, 100);
        ball.setFillColor(sf::Color::Yellow);
    }


    void on_update(gint64) override
    {
        float t = frame_interval.restart().asSeconds();
        //std::clog << "t=" << t << "\n";
        auto pos = ball.getPosition();
        pos += t * speed;
        ball.setPosition(pos);

        // check if collided with boundary of the camera
        auto cam = getView();
        auto hsize = cam.getSize() / 2.0f;
        auto center = cam.getCenter();
        float left = center.x - hsize.x;
        float right = center.x + hsize.x;
        float top = center.y - hsize.x;
        float bottom = center.y + hsize.y;
        if ((speed.x < 0 && pos.x < left)
            || (speed.x > 0 && pos.x > right))
            speed.x = -speed.x;
        if ((speed.y < 0 && pos.y < top)
            || (speed.y > 0 && pos.y > bottom))
            speed.y = -speed.y;
    }


    void on_render() override
    {
        clear(sf::Color::Blue);
        draw(ball);
        display();
    }

};



int main()
{
    auto app = Gtk::Application::create();
    MyWindow window;
    return app->run(window);
}
