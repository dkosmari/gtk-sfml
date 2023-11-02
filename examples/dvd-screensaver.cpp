#include <algorithm>
#include <vector>
#include <random>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtkmm.h>

#include <gtk-sfml/Window.hpp>

#include "font.hpp"


std::default_random_engine rnd_eng{std::random_device{}()};


struct AABB {

    sf::Vector2f min, max;

    AABB(const sf::FloatRect& rect) :
        min{rect.left, rect.top},
        max{rect.left+rect.width, rect.top+rect.height}
    {}

    AABB(const sf::Vector2f& center, const sf::Vector2f& size) :
        min{center - size/2.0f},
        max{center + size/2.0f}
    {}

};


sf::Vector2f
random_dir(float radius)
{
    std::uniform_real_distribution<float> dist{-M_PI, M_PI};
    float angle = dist(rnd_eng);
    return {radius * std::cos(angle), radius * std::sin(angle)};
}



struct MyWindow : gtksfml::Window {

    sf::Clock frame_interval;
    sf::Vector2f speed{random_dir(100)};
    sf::Font font;
    sf::Text text{"DVD", font, 80};
    sf::RectangleShape click_marker{{16, 16}};
    bool click_visible = false;

    std::vector<sf::Color> colors {
        sf::Color::White,
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Cyan,
        // one dominant color, one secondary color
        {0xff, 0x80, 0x40},
        {0xff, 0x40, 0x80},
        {0x80, 0xff, 0x40},
        {0x40, 0xff, 0x80},
        {0x80, 0x40, 0xff},
        {0x40, 0x80, 0xff}
    };
    std::size_t current_color = 0;


    MyWindow()
    {
        set_default_size(800, 600);

        font.loadFromMemory(FONT_DATA, FONT_SIZE);

        text.setStyle(sf::Text::Bold | sf::Text::Italic);
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width/2.0f,
                       bounds.top + bounds.height/2.0f);
        text.setPosition(400, 300);

        std::shuffle(colors.begin(), colors.end(), rnd_eng);
        text.setFillColor(colors[current_color]);

        click_marker.setOrigin(click_marker.getSize() / 2.0f);
    }


    void on_update() override
    {
        float t = frame_interval.restart().asSeconds();

        auto pos = text.getPosition();
        pos += t * speed;
        text.setPosition(pos);

        // check if collided with boundary of the camera
        bool bounced = false;
        auto camera = getView();
        AABB cbox{camera.getCenter(), camera.getSize()};
        AABB tbox{text.getGlobalBounds()};
        if ((speed.x < 0 && tbox.min.x < cbox.min.x)
            || (speed.x > 0 && tbox.max.x > cbox.max.x)) {
            speed.x = -speed.x;
            bounced = true;
        }

        if ((speed.y < 0 && tbox.min.y < cbox.min.y)
            || (speed.y > 0 && tbox.max.y > cbox.max.y)) {
            speed.y = -speed.y;
            bounced = true;
        }
        if (bounced)
            change_color();
    }


    void
    change_color()
    {
        if (++current_color >= colors.size())
            current_color = 0;
        text.setFillColor(colors[current_color]);
    }


    void
    on_render() override
    {
        clear();
        draw(text);
        if (click_visible)
            draw(click_marker);
        display();
    }


    void
    onResize() override
    {
        auto [w, h] = getSize();
        auto view = getView();
        view.setCenter(w/2.0f, h/2.0f);
        view.setSize(w, h);
        setView(view);
    }


#if 0

    // Here we handle the mouse through SFML events as if they came from
    // sf::Window::pollEvent().

    void
    on_event(const sf::Event& event) override
    {
        switch (event.type) {
        case sf::Event::EventType::MouseButtonPressed:
            handle_mouse_click(event.mouseButton.x, event.mouseButton.y);
            break;
        case sf::Event::EventType::MouseButtonReleased:
            click_visible = false;
            break;
        default:
            ;
        }
    }

#else

    // Same thing, but use the gtkmm event handling instead.

    bool
    on_button_press_event(GdkEventButton* event)
        override
    {
        handle_mouse_click(event->x, event->y);
        return false; // allow the event to propagate to GTK+
    }

    bool
    on_button_release_event(GdkEventButton*)
        override
    {
        click_visible = false;
        return false; // allow the event to propagate to GTK+
    }

#endif


    void
    handle_mouse_click(float x, float y)
    {
        auto tpos = text.getPosition();
        sf::Vector2i mpixel(x, y);
        auto mpos = mapPixelToCoords(mpixel);
        speed = mpos - tpos;
        change_color();

        click_marker.setPosition(mpos);
        click_visible = true;
    }


};


int main()
{
    auto app = Gtk::Application::create();
    MyWindow window;
    return app->run(window);
}
