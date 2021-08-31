#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iosfwd>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Sensor.hpp>
#include <SFML/Window/Touch.hpp>


std::string to_string(const sf::Event& e);

std::string to_string(const sf::Event::KeyEvent& ke);


std::string to_string(sf::Joystick::Axis a);
std::string to_string(sf::Keyboard::Key k);
std::string to_string(sf::Mouse::Button b);
std::string to_string(sf::Mouse::Wheel w);
std::string to_string(sf::Sensor::Type t);


std::ostream& operator<<(std::ostream& out, const sf::Event& e);

std::ostream& operator<<(std::ostream& out, const sf::Event::JoystickButtonEvent& button);
std::ostream& operator<<(std::ostream& out, const sf::Event::JoystickConnectEvent& connect);
std::ostream& operator<<(std::ostream& out, const sf::Event::JoystickMoveEvent& move);
std::ostream& operator<<(std::ostream& out, const sf::Event::KeyEvent& key);
std::ostream& operator<<(std::ostream& out, const sf::Event::MouseButtonEvent& button);
std::ostream& operator<<(std::ostream& out, const sf::Event::MouseMoveEvent& move);
std::ostream& operator<<(std::ostream& out, const sf::Event::MouseWheelEvent& wheel);
std::ostream& operator<<(std::ostream& out, const sf::Event::MouseWheelScrollEvent& scroll);
std::ostream& operator<<(std::ostream& out, const sf::Event::SensorEvent& sensor);
std::ostream& operator<<(std::ostream& out, const sf::Event::SizeEvent& size);
std::ostream& operator<<(std::ostream& out, const sf::Event::TextEvent& text);
std::ostream& operator<<(std::ostream& out, const sf::Event::TouchEvent& touch);


std::ostream& operator<<(std::ostream& out, sf::Joystick::Axis axis);
std::ostream& operator<<(std::ostream& out, sf::Keyboard::Key key);
std::ostream& operator<<(std::ostream& out, sf::Mouse::Button button);
std::ostream& operator<<(std::ostream& out, sf::Mouse::Wheel wheel);
std::ostream& operator<<(std::ostream& out, sf::Sensor::Type type);

#endif
