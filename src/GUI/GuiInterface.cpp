//
//  GuiInterface.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 11/1/18.
//
//

#include "GuiInterface.h"

//------------------------------------
GuiInterface::~GuiInterface(){
    for(int i = 0; i < sliders.size(); i++){
        delete sliders[i];
    }
}

//------------------------------------
void GuiInterface::setup(ofxImGui::Gui &gui){
    img.load("BP_PROJECTION_INTERFACE.png");
    
    font_large.load("fonts/ArialRoundedBold.ttf", 15);
    font_mid.load("fonts/ArialRoundedBold.ttf", 12);
    
    padding.x = 10;
    padding.y = 26;
    
    param_gui_offset = 177;
    
    add_shape_rect = ofRectangle(50,13,360,175);
    selected_layer_rect = ofRectangle(50,200,360,683);
    audio_analysis_rect = ofRectangle(50,892,360,175);
    shader_toggles_rect = ofRectangle(422,892,1450,175);
    mapping_panel_rect = ofRectangle(422,13,1450,870);
    
    setup_selected_layer(gui);
    setup_mapping_panel();
    
    // init volume vector
    volumes = {0.0, 0.0, 0.0};
}

//------------------------------------
void GuiInterface::setup_shader_toggles(vector<VisualLayer*> &layers){
    selected_shader = 0;
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
    for(int i = 0; i < 4; i++){
        CustomSlider* slider = new CustomSlider();
        slider->setup(selected_layer_rect.x + padding.x + 10, (param_gui_offset * i) + (selected_layer_rect.y + 80),
                         selected_layer_rect.width - (padding.x*2) - 20, 40,0.0,1.0,20,false, false);
        sliders.push_back(slider);
    }
    
    for(int i = 0; i < 3; i++){
        AudioToggles toggle;
        toggle.setup(gui);
        toggles.push_back(toggle);
    }
}

//------------------------------------
void GuiInterface::setup_mapping_panel(){
    mp_grid.load("shaders/passthrough.vert","shaders/Interface/grid.frag");
    mp_fbo.allocate(mapping_panel_rect.width, mapping_panel_rect.height,GL_RGBA);
}

//------------------------------------
void GuiInterface::update_volumes(vector<float> volumes){
    this->volumes = volumes;
}

//------------------------------------
void GuiInterface::draw(ShaderParams &params){
    if(ofGetMousePressed()){
        //img.draw(0,0);
    }

    draw_add_shape(add_shape_rect);
    draw_selected_layer(selected_layer_rect, params);
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

//------------------------------------
void GuiInterface::draw_selected_layer(ofRectangle rect, ShaderParams &params){
    draw_border(rect);
    font_large.drawString("SELECTED LAYER", rect.x + padding.x, rect.y + padding.y);
    
    //--- PARAMS
    for(int i = 0; i < toggles.size(); i++){
        ofSetColor(236, 60, 53);
        font_mid.drawString(params.names[i], rect.x + padding.x, (param_gui_offset * i) + (rect.y+62));
        toggles[i].draw(params.names[i] + ofToString(i), ofVec2f(rect.x + padding.x, (param_gui_offset * i) + (rect.y+140)), ofVec2f(rect.width+10, 80));
        
        if(toggles[i].get_selected_toggle() == 0){
            sliders[i]->update_gradient_percent(sliders[i]->getValue());
        } else {
            sliders[i]->update_gradient_percent(volumes[toggles[i].get_selected_toggle()-1]);
        }
        sliders[i]->setPercent(params.params[i]);
        
        //params.params[i] = sliders[i]->getValue();
    }
    
    ofSetColor(236, 60, 53);
    font_mid.drawString("HUESHIFT", rect.x + padding.x, (param_gui_offset * 3) + (rect.y+62));

}

//------------------------------------
void GuiInterface::draw_audio_analysis(ofRectangle rect){
    draw_border(rect);
    
    red_gradient.draw(1, volumes[0],rect.x + 10, rect.y + 10, 100, rect.height - 20);
    red_gradient.draw(1, volumes[1],rect.x + 130, rect.y + 10, 100, rect.height - 20);
    red_gradient.draw(1, volumes[2],rect.x + 250, rect.y + 10, 100, rect.height - 20);
    
    font_large.drawString("BASS", rect.x + 10, rect.y + padding.y);
    font_large.drawString("MID", rect.x + 130, rect.y + padding.y);
    font_large.drawString("HIGH", rect.x + 250, rect.y + padding.y);

}

//------------------------------------
void GuiInterface::draw_shader_toggles(ofRectangle rect){
    auto mainSettings = ofxImGui::Settings();
    mainSettings.windowPos = ofVec2f(rect.x-15, rect.y-15);
    mainSettings.windowSize = ofVec2f(rect.width+30, rect.height+30);
    
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

    ImVec4 c1 = ImColor(1.f, 0.1f, 0.13f, 1.00f);
    ImVec4 c2 = ImColor(0.10f, 0.09f, 0.12f, 1.00f);
    
    if (ofxImGui::BeginWindow("shader_toggles", mainSettings, window_flags))
    {
        for(int i = 0; i < shader_toggles.size(); i++){
            ImTextureID texID = (ImTextureID)(uintptr_t) shader_toggles[i].buttonID;
            
            // Active Shader is highlighted
            if (selected_shader == i) ImGui::PushStyleColor(ImGuiCol_Button, c1);
            else ImGui::PushStyleColor(ImGuiCol_Button, c2);
            
            if(ImGui::ImageButton(shader_toggles[i].buttonID, ImVec2(196,167))){
                shader_toggles[i].b = true;
                selected_shader = i;
            }
            ImGui::PopStyleColor();
            ImGui::SameLine(0,2); // squish the toggles closer togther
        }
    }
    ofxImGui::EndWindow(mainSettings);
    
    // Make sure only the selected shaders toggle is active.
    for(int i = 0; i < shader_toggles.size(); i++){
        if(i != selected_shader){
            shader_toggles[i].b = false;
        }
    }
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
int GuiInterface::get_selected_shader(){
    return selected_shader;
}

