#include "Message.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>

namespace render{

Message::Message(){
    if (!font.loadFromFile("res/arial/arial.ttf"))
        return;
    text.setFillColor(color.Black);
    text.setFont(font);
    text.setCharacterSize(25);
}

Message::~Message(){
    // std::string s = text.getString();
    // std::cout << s << std::endl;
}

Message::Message(int x, int y){
    if (!font.loadFromFile("res/arial/arial.ttf"))
        return;

    position.x = x;
    position.y = y;

    text.setFillColor(color.Black);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(x, y);
}

Message::Message(int x, int y, std::string string){
    if (!font.loadFromFile("res/arial/arial.ttf"))
        return;

    position.x = x;
    position.y = y;

    text.setFillColor(color.Black);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(x, y);
    text.setString(string);
    f_message = string;
}

Message::Message(int x, int y, std::string string, sf::Color color){
    if (!font.loadFromFile("res/arial/arial.ttf"))
        return;

    position.x = x;
    position.y = y;

    text.setFillColor(color);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(x, y);
    text.setString(string);
    f_message = string;
}


Message::Message (int x, int y, std::string string, bool m_display){
    if (!font.loadFromFile("res/arial/arial.ttf"))
        return;

    position.x = x;
    position.y = y;

    text.setFillColor(color.Black);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(x, y);
    if(m_display) {text.setString(string);}
    f_message = string;
}

void Message::setstrMessage (std::string message){
    std::ostringstream m_flux;

    m_flux << f_message;
    m_flux << message;

    text.setString(m_flux.str());
}

void Message::setintMessage (int message){
    std::ostringstream m_flux;

    m_flux << f_message;
    m_flux << message;

    text.setString(m_flux.str());
}

void Message::replaceMessage (std::string message){
    std::ostringstream m_flux;

    m_flux << message;

    text.setString(m_flux.str());
}

void Message::addMessage (std::string message) {
    std::ostringstream m_flux;

    std::string str = text.getString();

    m_flux << str;
    m_flux << message;

    text.setString(m_flux.str());
}

void Message::show (bool display) {
    if(display)
        text.setString(f_message);
    else    
        text.setString("");
}

}