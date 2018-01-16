//
//  GuiInterface.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 11/1/18.
//
//

#include "GuiInterface.h"

//------------------------------------
void GuiInterface::setup(ofxImGui::Gui &gui){
    img.load("BP_PROJECTION_INTERFACE.png");
    
    font_large.load("fonts/Ruda-Bold.ttf", 15);
    font_mid.load("fonts/Ruda-Bold.ttf", 12);
    
    padding.x = 10;
    padding.y = 26;
    
    add_shape_rect = ofRectangle(50,13,360,175);
    selected_layer_rect = ofRectangle(50,200,360,683);
    audio_analysis_rect = ofRectangle(50,892,360,175);
    shader_toggles_rect = ofRectangle(50,200,360,680);
    mapping_panel_rect = ofRectangle(422,13,1450,870);
    
    setup_selected_layer(gui);
    setup_mapping_panel();
}

//------------------------------------
void GuiInterface::setup_selected_layer(ofxImGui::Gui &gui){
    slider.setup(selected_layer_rect.x + padding.x + 10, selected_layer_rect.y + 80,
                 selected_layer_rect.width - (padding.x*2) - 20, 40,0.0,1.0,20,false, false);

    toggles.setup(gui);
}

//------------------------------------
void GuiInterface::setup_mapping_panel(){
    mp_grid.load("shaders/passthrough.vert","shaders/Interface/grid.frag");
    mp_fbo.allocate(mapping_panel_rect.width, mapping_panel_rect.height,GL_RGBA);
}

//------------------------------------
void GuiInterface::draw(ofxImGui::Gui &gui){
    if(ofGetMousePressed()){
        //img.draw(0,0);
    }

    draw_add_shape(add_shape_rect);
    draw_selected_layer(selected_layer_rect);
    draw_audio_analysis(audio_analysis_rect);
    draw_shader_toggles(shader_toggles_rect);
    draw_mapping_panel(mapping_panel_rect);
    
}

//------------------------------------
void GuiInterface::draw_border(ofRectangle rect){
    ofNoFill();
    ofSetColor(255);
    ofDrawRectangle(rect);
}


//------------------------------------
void GuiInterface::draw_add_shape(ofRectangle rect){
    draw_border(rect);
    font_large.drawString("ADD SHAPE", rect.x + padding.x, rect.y + padding.y);
}

void GuiInterface::draw_selected_layer(ofRectangle rect){
    draw_border(rect);
    font_large.drawString("SELECTED LAYER", rect.x + padding.x, rect.y + padding.y);
}
void GuiInterface::draw_audio_analysis(ofRectangle rect){
    draw_border(rect);
    
    red_gradient.draw(1, get_bass_vol(),rect.x + 10, rect.y + 10, 100, rect.height - 20);
    red_gradient.draw(1, get_mid_vol(),rect.x + 130, rect.y + 10, 100, rect.height - 20);
    red_gradient.draw(1, get_high_vol(),rect.x + 250, rect.y + 10, 100, rect.height - 20);
    
    font_large.drawString("BASS", rect.x + 10, rect.y + padding.y);
    font_large.drawString("MID", rect.x + 130, rect.y + padding.y);
    font_large.drawString("HIGH", rect.x + 250, rect.y + padding.y);

}
void GuiInterface::draw_shader_toggles(ofRectangle rect){
    
}
void GuiInterface::draw_mapping_panel(ofRectangle rect){
    draw_border(rect);
    
    ofFill();
    ofSetColor(255,125);
    mp_fbo.begin();
    ofClear(0,0,0,0);
        mp_grid.begin();
        mp_grid.setUniform3f("resolution", mapping_panel_rect.width, mapping_panel_rect.height, 1);
        ofDrawRectangle(0, 0, mapping_panel_rect.width, mapping_panel_rect.height);
        mp_grid.end();
    
    mp_fbo.end();
    
    mp_fbo.draw(rect);
}

//------------------------------------
float GuiInterface::get_bass_vol() {
    return ofNoise(ofGetElapsedTimef() * 5.0);
}
float GuiInterface::get_mid_vol() {
    return ofNoise(10000+ofGetElapsedTimef() * 5.0);
}
float GuiInterface::get_high_vol() {
    return ofNoise(200000+ofGetElapsedTimef() * 5.0);
}
