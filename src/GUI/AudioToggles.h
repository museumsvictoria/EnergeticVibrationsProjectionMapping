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
#include "ConvertAssetColour.h"

struct Toggle{
    bool b;
    GLuint buttonOnID;
    GLuint buttonOffID;
};


class AudioToggles{
public:
    
    void setup(ofxImGui::Gui &gui, ofVec4f theme_colour);
    void draw(string name, ofVec2f pos, ofVec2f size, ImGuiWindowFlags window_flags);
    
    ofImage convert_asset_colour(int w, int h, ofImage img, ofVec4f theme_colour);
    vector<Toggle> toggles;

    ConvertAssetColour asset_colour;
    
    void set_selected_toggle(int val);
    int get_selected_toggle();
    
private:
    int selected;
};
