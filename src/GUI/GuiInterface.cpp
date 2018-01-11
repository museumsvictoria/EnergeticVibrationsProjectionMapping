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
    setup_gradient_shader();
}

//------------------------------------
void GuiInterface::setup_mapping_panel(){
    mp_grid.load("shaders/passthrough.vert","shaders/Interface/grid.frag");
    
    mp_fbo.allocate(mapping_panel_rect.width, mapping_panel_rect.height,GL_RGBA);
}

//------------------------------------
void GuiInterface::setup_gradient_shader(){
    gradient.load("shaders/passthrough.vert","shaders/Interface/gradient.frag");
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
void GuiInterface::draw_red_gradient(int verticle_or_horizontal, float perc, int x, int y, int w, int h){
    ofFill();
    ofSetColor(255);
    
    gradient.begin();
    gradient.setUniform3f("resolution",w,h,1);
    gradient.setUniform1f("perc",perc);
    gradient.setUniform1i("verticle_or_horizontal", verticle_or_horizontal);
    ofDrawRectangle(x, y, w, h);
    gradient.end();
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
    
    float speed = ofGetElapsedTimef() * 5.0;
    float bass = ofNoise(speed);
    float mid = ofNoise(300000+speed);
    float high = ofNoise(10000+speed);
    
    draw_red_gradient(1, bass,rect.x + 10, rect.y + 10, 100, rect.height - 20);
    draw_red_gradient(1, mid,rect.x + 130, rect.y + 10, 100, rect.height - 20);
    draw_red_gradient(1, high,rect.x + 250, rect.y + 10, 100, rect.height - 20);
    
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
