//
//  GuiInterface.hpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 11/1/18.
//
//

#pragma once 

#include "ofMain.h"
#include "Gradient.h"
#include "CustomSlider.h"
#include "AudioToggles.h"
#include "ofxImGui.h"
#include "VisualLayer.h"

struct ShaderToggle{
    bool b;
    ImTextureID buttonID;
};

struct ShaderState{
    //Shader Sliders
    vector<CustomSlider*> sliders;
    
    //Audio Select Toggles
    vector<AudioToggles> toggles;
};

class GuiInterface{
    public:
    GuiInterface();
    ~GuiInterface();
    void setup(ofxImGui::Gui &gui);
    void setup_shader_toggles(vector<VisualLayer*> &layers);
    void setup_mapping_panel();
    void setup_selected_layer(ofxImGui::Gui &gui);
    
    void update_audio_reactivity(vector<VisualLayer*> &layers);
    void update_active_sliders();
    
    void draw(ShaderParams &params);
    
    void draw_border(ofRectangle rect);
    
    void draw_add_shape(ofRectangle rect);
    void draw_selected_layer(ofRectangle rect, ShaderParams &params);
    void draw_audio_analysis(ofRectangle rect);
    void draw_shader_toggles(ofRectangle rect);
    void draw_mapping_panel(ofRectangle rect);
    
    void update_volumes(vector<float> volumes);
    vector<float> volumes;

    
    int get_selected_shader();
    
private:
    ofRectangle add_shape_rect;
    ofRectangle selected_layer_rect;
    ofRectangle audio_analysis_rect;
    ofRectangle shader_toggles_rect;
    ofRectangle mapping_panel_rect;
  
    ofTrueTypeFont font_large;
    ofTrueTypeFont font_mid;
    
    int param_gui_offset;
    ofVec2f padding; // used to offset the titles from their containing rectangle pos
    
    
    /// Mapping Panel
    ofFbo mp_fbo;
    ofShader mp_grid;
    
    ofImage img; // background template ref

    //Red Gradient Shader
    Gradient red_gradient;
    
    vector<ShaderState> shader_states;
    
    //Shader Selection Buttons
    vector<ShaderToggle> shader_toggles;
    int selected_shader;
};
