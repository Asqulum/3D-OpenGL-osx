//
//  chat.hpp
//  3D
//
//  Created by Daan Vijfvinkel on 28-08-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#ifndef chat_h
#define chat_h

#include <string>
#include <vector>
#include "textdisplay.h"

class chatbox {
public:
    chatbox();
    int sendchat();
    void appendchat(char input);
    void displaychat(int windowwidth, int windowheight, GLboolean zPressed);
    void typing(int windowwidth, int windowheight);
    
    std::vector<std::string> chatlog;
    std::vector<int> chatduration;
    std::string newmessage;
};


#endif /* chat_h */
