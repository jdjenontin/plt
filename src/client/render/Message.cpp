#include "Message.h"

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>

#define FONT_PATH "res/arial.ttf"

namespace render{

Message::Message(){
    if (!font.loadFromFile(FONT_PATH))
        return;
    text.setFillColor(color.Black);
    text.setFont(font);
    text.setCharacterSize(25);
}

Message::~Message(){
    
}

Message::Message(int x, int y){
    if (!font.loadFromFile(FONT_PATH))
        return;

    position.x = x;
    position.y = y;

    text.setFillColor(color.Black);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(x, y);
}

Message::Message(int x, int y, std::string string){
    if (!font.loadFromFile(FONT_PATH))
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
    if (!font.loadFromFile(FONT_PATH))
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
    if (!font.loadFromFile(FONT_PATH))
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

void Message::setSize(int size){
    text.setCharacterSize(size);
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

void Message::cutMessage (){
    std::string str(text.getString());
    std::string str2;

    for(unsigned int i = 0; i < str.size(); i++){
        str2.push_back(str[i]);
        if(str[i] == ' '){
            break;
        }
    }

    text.setString(str2);
}

void Message::setColor (sf::Color color){
    text.setFillColor(color);
}

void Message::show (bool display) {
    if(display)
        text.setString(f_message);
    else    
        text.setString("");
}

}