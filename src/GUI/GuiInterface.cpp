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
    for(int i = 0; i < shader_states.size(); i++){
        for(int x = 0; x < shader_states[i].sliders.size(); x++){
            delete shader_states[i].sliders[x];
        }
    }
}

//------------------------------------
GuiInterface::GuiInterface(){
    selected_shader = 0;
}

//------------------------------------
void GuiInterface::init_window_flags(){
    static bool no_titlebar = true;
    static bool no_border = true;
    static bool no_resize = true;
    static bool no_move = true;
    static bool no_scrollbar = true;
    static bool no_collapse = true;
    static bool no_menu = true;
    
    // Demonstrate the various window flags. Typically you would just use the default.
    window_flags = 0;
    if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
    if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
    if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
    if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
    if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
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
    
    init_window_flags();
    
    setup_selected_layer(gui);
    setup_mapping_panel(gui);
    
    // init volume vector
    volumes = {0.0, 0.0, 0.0};
}

//------------------------------------
void GuiInterface::setup_shader_toggles(vector<VisualLayer*> &layers){
    for(int i = 0; i < 7; i++){
        ShaderToggle t;
        t.b = false;
        if(i==0) t.b = true;
        t.buttonID = (ImTextureID)layers[i]->render_fbo.fbo.getTexture().texData.textureID;
        shader_toggles.push_back(t);
        
        // Init the slider positions to the shader param defaluts
        for(int x = 0; x < layers[i]->shader_params[i].params.size(); x++){
            shader_states[i].sliders[x]->setPercent(layers[i]->shader_params[i].params[x]);
        }
    }
}

//------------------------------------
void GuiInterface::setup_selected_layer(ofxImGui::Gui &gui){
    
    for(int i = 0; i < 7; i++){
        ShaderState state;
        shader_states.push_back(state);
    }

    for(int i = 0; i < shader_states.size(); i++){
        for(int x = 0; x < 3; x++){
            AudioToggles toggle;
            toggle.setup(gui);
            shader_states[i].toggles.push_back(toggle);
        }
        for(int y = 0; y < 4; y++){
            CustomSlider* slider = new CustomSlider();
            slider->setup(selected_layer_rect.x + padding.x + 10, (param_gui_offset * y) + (selected_layer_rect.y + 80),
                          selected_layer_rect.width - (padding.x*2) - 20, 40,0.0,1.0,20,false, false);
            
            shader_states[i].sliders.push_back(slider);
        }
    }
    update_active_sliders();

}

//------------------------------------
void GuiInterface::setup_mapping_panel(ofxImGui::Gui &gui){
    mp_grid.load("shaders/passthrough.vert","shaders/Interface/grid.frag");
    mp_fbo.allocate(mapping_panel_rect.width, mapping_panel_rect.height,GL_RGBA);
    
    ofImage remove_image;
    ofImage duplicate_image;
    remove_image.load("buttons/remove.png");
    duplicate_image.load("buttons/duplicate.png");
    remove_button_ID = gui.loadImage(remove_image);
    duplicate_button_ID = gui.loadImage(duplicate_image);
}

//------------------------------------
void GuiInterface::update_active_sliders(){
    for(int i = 0; i < shader_states.size(); i++){
        for(int y = 0; y < 4; y++){
            if(i == selected_shader) shader_states[i].sliders[y]->set_is_active(true);
            else shader_states[i].sliders[y]->set_is_active(false);
        }
    }
}

//------------------------------------
void GuiInterface::update_volumes(vector<float> volumes){
    this->volumes = volumes;
}

//------------------------------------
void GuiInterface::update_audio_reactivity(vector<VisualLayer *> &layers){
    for(int x = 0; x < shader_states.size(); x++){
        ShaderParams& params = layers[x]->shader_params[x];
        for(int i = 0; i < shader_states[x].toggles.size(); i++){
            float slider_val = shader_states[x].sliders[i]->getValue();
            float audio_val = volumes[shader_states[x].toggles[i].get_selected_toggle()-1];
            
            if(shader_states[x].toggles[i].get_selected_toggle() != 0){
                shader_states[x].sliders[i]->update_gradient_percent(audio_val * slider_val);
                params.params[i] = audio_val * slider_val;
            }
        }
    }
}

//------------------------------------
void GuiInterface::draw(ShaderParams &params){
    if(ofGetMousePressed()){
        img.draw(0,0);
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
    for(int i = 0; i < shader_states[selected_shader].sliders.size(); i++){
        ofSetColor(236, 60, 53);
        font_mid.drawString(params.names[i], rect.x + padding.x, (param_gui_offset * i) + (rect.y+62));
        
        float slider_val = shader_states[selected_shader].sliders[i]->getValue();
        
        if(i < shader_states[selected_shader].toggles.size()){
            
            float audio_val = volumes[shader_states[selected_shader].toggles[i].get_selected_toggle()-1];
            
            shader_states[selected_shader].toggles[i].draw(params.names[i] + ofToString(i), ofVec2f(rect.x + padding.x, (param_gui_offset * i) + (rect.y+140)), ofVec2f(rect.width+10, 80), window_flags);
            
            if(shader_states[selected_shader].toggles[i].get_selected_toggle() == 0){
                shader_states[selected_shader].sliders[i]->update_gradient_percent(slider_val);
                params.params[i] = slider_val;
            } else {
                shader_states[selected_shader].sliders[i]->update_gradient_percent(audio_val * slider_val);
                params.params[i] = audio_val * slider_val;
            }
        } else {
            shader_states[selected_shader].sliders[i]->update_gradient_percent(slider_val);
            params.params[i] = slider_val;
        }
    }
    
    for(int i = 0; i < shader_states[selected_shader].sliders.size(); i++){
        shader_states[selected_shader].sliders[i]->draw();
    }
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
                
                for(int x = 0; x < shader_states[selected_shader].sliders.size(); x++){
                    float value = shader_states[selected_shader].sliders[x]->getValue();
                    shader_states[selected_shader].sliders[x]->setPercent(value);
                }
                
                update_active_sliders();
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
    
    
    auto mainSettings = ofxImGui::Settings();
    mainSettings.windowPos = ofVec2f((rect.x + rect.width) - 165, rect.y + 10);
    mainSettings.windowSize = ofVec2f(120,80);
    
    if (ofxImGui::BeginWindow("duplicate panel", mainSettings, window_flags))
    {
        ImTextureID duplicate_texID = (ImTextureID)(uintptr_t)(duplicate_button_ID);
        if(ImGui::ImageButton(duplicate_texID, ImVec2(111,51))){
            
        }
    }
    ofxImGui::EndWindow(mainSettings);
    
    mainSettings.windowPos = ofVec2f((rect.x + rect.width) - 165, rect.y + 70);
    if (ofxImGui::BeginWindow("remove panel", mainSettings, window_flags))
    {
        ImTextureID remove_texID = (ImTextureID)(uintptr_t)(remove_button_ID);
        if(ImGui::ImageButton(remove_texID, ImVec2(111,51))){
            
        }
    }
    ofxImGui::EndWindow(mainSettings);
    

}

//------------------------------------
int GuiInterface::get_selected_shader(){
    return selected_shader;
}

