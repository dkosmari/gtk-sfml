#ifndef EXAMPLES_UTILS_HPP
#define EXAMPLES_UTILS_HPP

#include <string>
#include <iosfwd>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>


std::string
to_string(const sf::Event& e);

std::string
to_string(const sf::Event::KeyEvent& ke);


std::string
to_string(sf::Keyboard::Key k);


std::ostream&
operator<<(std::ostream& out,
           const sf::Event& e);


std::ostream&
operator<<(std::ostream& out,
           const sf::Event::KeyEvent& ke);


std::ostream&
operator<<(std::ostream& out,
           sf::Keyboard::Key k);


#endif
