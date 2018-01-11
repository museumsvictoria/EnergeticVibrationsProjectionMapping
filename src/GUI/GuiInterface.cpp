//
//  GuiInterface.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 11/1/18.
//
//

#include "GuiInterface.h"

//------------------------------------
void GuiInterface::setup(){
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
    
    setup_mapping_panel();
}

//------------------------------------
void GuiInterface::setup_mapping_panel(){
    mp_grid.load("shaders/passthrough.vert","shaders/Interface/grid.frag");
    
    mp_fbo.allocate(mapping_panel_rect.width, mapping_panel_rect.height,GL_RGBA);
}

//------------------------------------
void GuiInterface::draw(){
    if(ofGetMousePressed()){
        img.draw(0,0);
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
}
void GuiInterface::draw_shader_toggles(ofRectangle rect){
    
}
void GuiInterface::draw_mapping_panel(ofRectangle rect){
    draw_border(rect);
    
    mp_grid.load("shaders/passthrough.vert","shaders/Interface/grid.frag");

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
