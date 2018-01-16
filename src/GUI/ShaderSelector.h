//
//  ShaderSelector.hpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 16/1/18.
//
//

#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "VisualLayer.h"

struct Toggle{
    bool b;
    ImTextureID buttonID;
};


class ShaderSelector{
public:
    
    void setup(ofxImGui::Gui &gui, vector<VisualLayer*> &layers);
    void draw(ofxImGui::Gui &gui);
    
    vector<Toggle> toggles;
    
private:
    int selected;
};
