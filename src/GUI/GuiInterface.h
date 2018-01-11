//
//  GuiInterface.hpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 11/1/18.
//
//

#pragma once 

#include "ofMain.h"

class GuiInterface{
    public:
    void setup();
    void setup_mapping_panel();
    
    void draw();
    
    void draw_border(ofRectangle rect);
    
    void draw_add_shape(ofRectangle rect);
    void draw_selected_layer(ofRectangle rect);
    void draw_audio_analysis(ofRectangle rect);
    void draw_shader_toggles(ofRectangle rect);
    void draw_mapping_panel(ofRectangle rect);
    
    ofImage img; // background template ref
private:
    ofRectangle add_shape_rect;
    ofRectangle selected_layer_rect;
    ofRectangle audio_analysis_rect;
    ofRectangle shader_toggles_rect;
    ofRectangle mapping_panel_rect;
  
    ofTrueTypeFont font_large;
    ofTrueTypeFont font_mid;
    
    ofVec2f padding; // used to offset the titles from their containing rectangle pos
    
    
    /// Mapping Panel
    ofFbo mp_fbo;
    ofShader mp_grid;
};
