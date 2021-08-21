#include <iomanip>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "examples-utils.hpp"


using std::cout;
using std::endl;
using std::ostringstream;


int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Raw SFML event test");

    window.setVerticalSyncEnabled(true);

    sf::Font font;
    font.loadFromFile(SRCDIR "/LiberationSans-Regular.ttf");

    sf::Text time_text;
    time_text.setFont(font);
    time_text.setPosition(40, 20);

    sf::Text fps_text;
    fps_text.setFont(font);
    fps_text.setPosition(40, 80);
    fps_text.setFillColor(sf::Color::Yellow);

    unsigned frame_counter = 0;
    bool has_event = false;


    sf::Clock time_clock;
    sf::Clock fps_clock;


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::EventType::KeyPressed ||
                event.type == sf::Event::EventType::KeyReleased) {


                if (has_event)
                    cout << " ";
                cout << event;
                has_event = true;
            }
        }
        if (has_event)
            cout << endl;
        has_event = false;


        if (fps_clock.getElapsedTime() >= sf::seconds(1)) {
            fps_clock.restart();
            ostringstream out;
            out << "FPS: " << frame_counter;
            fps_text.setString(out.str());
            frame_counter = 0;
        }

        {
            ostringstream out;
            out << "time: "
                << std::fixed
                << std::setprecision(2)
                << time_clock.getElapsedTime().asSeconds();
            time_text.setString(out.str());
        }


        if (window.hasFocus())
            window.clear({0, 16, 64});
        else
            window.clear({0, 0, 64});
        window.draw(time_text);
        window.draw(fps_text);
        window.display();
        ++frame_counter;
    }
}
