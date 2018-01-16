//
//  ShaderSelector.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 16/1/18.
//
//

#include "ShaderSelector.h"

//------------------------------------
void ShaderSelector::setup(ofxImGui::Gui &gui, vector<VisualLayer*> &layers){
    selected = 0;
    
    for(int i = 0; i < 7; i++){
        Toggle t;
        t.b = false;
        if(i==0) t.b = true;
        
        t.buttonID = (ImTextureID)layers[i]->FboSource::fbo->getTexture().texData.textureID;
        
        toggles.push_back(t);
    }
}

//------------------------------------
void ShaderSelector::draw(ofxImGui::Gui &gui){
    
    
}
