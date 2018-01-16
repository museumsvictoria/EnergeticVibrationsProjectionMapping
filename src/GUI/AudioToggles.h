//
//  AudioToggles.hpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 16/1/18.
//
//

#pragma once 

#include "ofMain.h"
#include "ofxImGui.h"

struct Toggle{
    bool b;
    GLuint buttonOnID;
    GLuint buttonOffID;
};


class AudioToggles{
public:
    
    void setup(ofxImGui::Gui &gui);
    void draw(ofxImGui::Gui &gui);
    
    vector<Toggle> toggles;

private:
    int selected;
};
