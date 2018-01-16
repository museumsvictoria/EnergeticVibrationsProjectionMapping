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
    shader_toggles_rect = ofRectangle(422,892,1450,175);
    mapping_panel_rect = ofRectangle(422,13,1450,870);
    
    setup_selected_layer(gui);
    setup_mapping_panel();
    
}

//------------------------------------
void GuiInterface::setup_shader_toggles(vector<VisualLayer*> &layers){
    for(int i = 0; i < 7; i++){
        ShaderToggle t;
        t.b = false;
        if(i==0) t.b = true;
        t.buttonID = (ImTextureID)layers[i]->render_fbo.fbo.getTexture().texData.textureID;
        shader_toggles.push_back(t);
    }
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
    draw_shader_toggles(shader_toggles_rect, gui);
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

//------------------------------------
void GuiInterface::draw_shader_toggles(ofRectangle rect, ofxImGui::Gui &gui){
    auto mainSettings = ofxImGui::Settings();
    int gui_width = 350;
    int scroll_bar = 17;
    mainSettings.windowPos = ofVec2f(rect.x, rect.y);
    mainSettings.windowSize = ofVec2f(rect.width, rect.height);
    
    static bool no_titlebar = true;
    static bool no_border = true;
    static bool no_resize = true;
    static bool no_move = true;
    static bool no_scrollbar = true;
    static bool no_collapse = true;
    static bool no_menu = true;
    
    // Demonstrate the various window flags. Typically you would just use the default.
    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
    if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
    if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
    if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
    if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
    

    int size = 180;
    

    if (ofxImGui::BeginWindow("", mainSettings, window_flags))
    {
        for(int i = 0; i < shader_toggles.size(); i++){
            ShaderToggle* toggle;
            
            //if(x==names.size()-1) toggle = &layer_assignments[i].disabled;
            //else toggle = &layer_assignments[i].outputs[x];
            
            //ImTextureID texID = (ImTextureID)(uintptr_t) (toggle->b ? toggle->buttonID : toggle->buttonOffID);
            ImTextureID texID = (ImTextureID)(uintptr_t) shader_toggles[i].buttonID;
            
            if(ImGui::ImageButton(shader_toggles[i].buttonID, ImVec2(size,size))){
                //toggle->b = !toggle->b;
                //if(x < names.size()-1) layer_assignments[i].disabled.b = false;
                
                //if(layer_assignments[i].disabled.b == true){
                //    for(int y = 0; y < names.size()-1; y++){
                //        layer_assignments[i].outputs[y].b = false;
                //    }
                //}
            }ImGui::SameLine();
        }
    }
    ofxImGui::EndWindow(mainSettings);
}

//------------------------------------
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
