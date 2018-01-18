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
        
        t.buttonOnID = gui.loadImage("buttons/" + names[i] + "on.jpg");
        t.buttonOffID = gui.loadImage("buttons/" + names[i] + "off.jpg");
        
        toggles.push_back(t);
    }
}

//------------------------------------
void AudioToggles::draw(ofxImGui::Gui &gui){

    /*
    auto mainSettings = ofxImGui::Settings();
    int gui_width = 350;
    int scroll_bar = 17;
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
    
    // Look at this https://github.com/ocornut/imgui/issues/1537
    
    if (ofxImGui::BeginWindow("", mainSettings, window_flags))
    {
        for(int i = 0; i < toggles.size(); i++){
            
            ImTextureID texID = (ImTextureID)(uintptr_t) (pressed ? toggles[i].buttonOnID : toggles[i].buttonOffID);

            ImTextureID texID = (ImTextureID)(uintptr_t) shader_toggles[i].buttonID;
            
            if(ImGui::ImageButton(texID, ImVec2(196,167))){
                shader_toggles[i].b = true;
                selected_shader = i;
            }ImGui::SameLine(0,2); // squish the toggles closer togther
        }
    }
    ofxImGui::EndWindow(mainSettings);
    
    // Make sure only the selected shaders toggle is active.
    for(int i = 0; i < shader_toggles.size(); i++){
        if(i != selected_shader){
            shader_toggles[i].b = false;
        }
    }
    */
}
