//
//  AudioToggles.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 16/1/18.
//
//

#include "AudioToggles.h"

//------------------------------------
void AudioToggles::setup(ofxImGui::Gui &gui){
    selected = 0;
    
    vector<string> names = {"off_", "bass_", "mid_", "high_"};
    
    for(int i = 0; i < 4; i++){
        Toggle t;
        t.b = false;
        if(i==0) t.b = true;
        
        t.buttonOnID = gui.loadImage("buttons/" + names[i] + "on.jpg");
        t.buttonOffID = gui.loadImage("buttons/" + names[i] + "off.jpg");
        
        toggles.push_back(t);
    }
}

//------------------------------------
void AudioToggles::draw(ofxImGui::Gui &gui){


}
