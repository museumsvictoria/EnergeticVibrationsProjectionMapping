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
        
        ofImage image_on;
        ofImage image_off;
        image_on.load("buttons/" + names[i] + "on.png");
        image_off.load("buttons/" + names[i] + "off.png");
        t.buttonOnID = gui.loadImage(image_on);
        t.buttonOffID = gui.loadImage(image_off);
        
        toggles.push_back(t);
    }
}

//------------------------------------
void AudioToggles::set_selected_toggle(int val){
    selected = val;
    for(int i = 0; i < toggles.size(); i++){
        if(i == selected) toggles[i].b = true;
        else toggles[i].b = false;
    }
}

//------------------------------------
int AudioToggles::get_selected_toggle(){
    return selected;
}

//------------------------------------
void AudioToggles::draw(string name, ofVec2f pos, ofVec2f size, ImGuiWindowFlags window_flags){

    auto mainSettings = ofxImGui::Settings();
    mainSettings.windowPos = ofVec2f(pos.x-15, pos.y-15);
    mainSettings.windowSize = ofVec2f(size.x, size.y);
    
    if (ofxImGui::BeginWindow(name, mainSettings, window_flags))
    {
        for(int i = 0; i < toggles.size(); i++){
            ImTextureID texID = (ImTextureID)(uintptr_t) (toggles[i].b ? toggles[i].buttonOnID : toggles[i].buttonOffID);
			
            if(ImGui::ImageButton(texID, ImVec2(60,44))){
                toggles[i].b = true;
                selected = i;
            }ImGui::SameLine(0,3); // squish the toggles closer togther
        }
    }
    ofxImGui::EndWindow(mainSettings);

    // Make sure only the selected shaders toggle is active.
    for(int i = 0; i < toggles.size(); i++){
        if(i != selected){
            toggles[i].b = false;
        }
    }
}
