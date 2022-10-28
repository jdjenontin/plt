#include "Message.h"

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

void Message::setstrMessage (std::string message){
    std::string str;

    str.append(f_message);
    str.append(message);
    text.setString(str);
}

void Message::setintMessage (int message){
    std::string str;
    flux << message;

    str.append(f_message);
    str.append(flux.str());
    text.setString(str);

    flux.clear();
}

}