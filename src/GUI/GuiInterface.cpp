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
    
    ofRemoveListener(map_helper.get_surface_manager()->surfaceSelectedEvent, this, &GuiInterface::onSurfaceSelected);
}

//------------------------------------
GuiInterface::GuiInterface(){
    selected_shader = 0;
    mouse_over_remove_toggle = false;
    mouse_over_duplicate_toggle = false;
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
void GuiInterface::setup(ofxImGui::Gui &gui, ofxPiMapper& mapper, int num_layers, ofVec4f theme_colour){
    this->num_layers = num_layers;
    this->theme_colour = theme_colour;
    
    map_helper.setup(mapper);
    
    img.load("BP_PROJECTION_INTERFACE.png");
    img_background.load("images/background.png");
    
//    font_large.load("fonts/ArialRoundedBold.ttf", 15);
//    font_mid.load("fonts/ArialRoundedBold.ttf", 12);
    font_large.load("fonts/DINOffc-CondMedi.ttf", 18);
    font_mid.load("fonts/DINOffc-CondMedi.ttf", 16);
  
    padding.x = 10;
    padding.y = 25;
    
    param_gui_offset = 150;

    
    

    map_helper.set_theme_colour(theme_colour);
    
    add_shape_rect = ofRectangle(118,95,306,149);
    selected_layer_rect = ofRectangle(118,252,306,580);
    audio_analysis_rect = ofRectangle(118,843,306,151);
    shader_toggles_rect = ofRectangle(1442,164,350,830);
//    mapping_panel_rect = ofRectangle(422,13,1450,870);
    mapping_panel_rect = ofRectangle(434,95,998,899);
    duplicate_remove_rect = ofRectangle(1442,95,228,46);
    
    init_window_flags();
    
    setup_add_shape(gui);
    setup_selected_layer(gui);
    setup_mapping_panel(gui);
    
    // init volume vector
    volumes = {0.0, 0.0, 0.0};
    
    // Receive events from ofxPiMapper when a new surface is selected
    ofAddListener(map_helper.get_surface_manager()->surfaceSelectedEvent, this, &GuiInterface::onSurfaceSelected);
}

//----------------------------------------
void GuiInterface::onSurfaceSelected(int & surfaceIndex){
    update_active_shader(map_helper.get_selected_source());
}

//------------------------------------
void GuiInterface::init_shader_variables(vector<VisualLayer*> &layers){
    for(int i = 0; i < num_layers; i++){
        // Init the slider positions to the shader param defaluts
        for(int x = 0; x < layers[i]->shader_variables.size(); x++){
            shader_states[i].sliders[x]->setPercent(layers[i]->shader_variables[x].value);
        }
    }
}

//------------------------------------
void GuiInterface::push_back_shader_toggle(ofxImGui::Gui &gui, vector<VisualLayer*> &layers){
    ShaderState state;
    shader_states.push_back(state);
    
    for(int x = 0; x < 3; x++){
        AudioToggles toggle;
        toggle.setup(gui, theme_colour);
        shader_states.back().toggles.push_back(toggle);
    }
    for(int y = 0; y < 4; y++){
        CustomSlider* slider = new CustomSlider();
        slider->setup(selected_layer_rect.x + padding.x + 10, (param_gui_offset * y) + (selected_layer_rect.y + 63),
                      selected_layer_rect.width - (padding.x*2) - 16, 40,0.0,1.0,20,false, true, false);
        shader_states.back().sliders.push_back(slider);
    }
    
    ShaderToggle t;
    t.b = false;
    t.buttonID = (ImTextureID)layers.back()->render_fbo.fbo.getTexture().texData.textureID;
    shader_toggles.push_back(t);
    
    // Init the slider positions to the shader param defaluts
    for(int x = 0; x < layers.back()->shader_variables.size(); x++){
        shader_states.back().sliders[x]->setPercent(layers.back()->shader_variables[x].value);
    }
}

//------------------------------------
void GuiInterface::setup_shader_toggles(vector<VisualLayer*> &layers){
    for(int i = 0; i < num_layers; i++){
        ShaderToggle t;
        t.b = false;
        if(i==0) t.b = true;
        t.buttonID = (ImTextureID)layers[i]->render_fbo.fbo.getTexture().texData.textureID;
        shader_toggles.push_back(t);
        
        // Init the slider positions to the shader param defaluts
        for(int x = 0; x < layers[i]->shader_variables.size(); x++){
            shader_states[i].sliders[x]->setPercent(layers[i]->shader_variables[x].value);
        }
    }
    
    sb_slider.setup(shader_toggles_rect.x + shader_toggles_rect.width + 20, shader_toggles_rect.y + 2, 40, shader_toggles_rect.height - 8, 0.0, 1.0, 20, true, true, false);
    sb_slider.set_is_active(true);
}

//------------------------------------
void GuiInterface::setup_selected_layer(ofxImGui::Gui &gui){
    
    for(int i = 0; i < num_layers; i++){
        ShaderState state;
        shader_states.push_back(state);
    }
    
    for(int i = 0; i < shader_states.size(); i++){
        for(int x = 0; x < 3; x++){
            AudioToggles toggle;
            toggle.setup(gui, theme_colour);
            shader_states[i].toggles.push_back(toggle);
        }
        for(int y = 0; y < 4; y++){
            CustomSlider* slider = new CustomSlider();
            slider->setup(selected_layer_rect.x + padding.x + 10, (param_gui_offset * y) + (selected_layer_rect.y + 63),
                          selected_layer_rect.width - (padding.x*2) - 16, 40,0.0,1.0,20,false, true, false);
            shader_states[i].sliders.push_back(slider);
        }
    }
    update_active_sliders();

}

//------------------------------------
void GuiInterface::setup_mapping_panel(ofxImGui::Gui &gui){

    ofImage remove_image;
    ofImage duplicate_image;
    remove_image.load("buttons/remove_off.png");
    duplicate_image.load("buttons/duplicate_off.png");
    remove_button_ID = gui.loadImage(remove_image);
    duplicate_button_ID = gui.loadImage(duplicate_image);
}

//------------------------------------
void GuiInterface::setup_add_shape(ofxImGui::Gui &gui){
    ofImage quad_image;
    ofImage triangle_image;
    quad_image.load("buttons/rectangle.png");
    triangle_image.load("buttons/triangle.png");
    
    quad_image = asset_colour.convert_asset_colour(quad_image.getWidth(), quad_image.getHeight(), quad_image, theme_colour);
    
    triangle_image = asset_colour.convert_asset_colour(triangle_image.getWidth(), triangle_image.getHeight(), triangle_image, theme_colour);
    
    quad_buttonID = gui.loadImage(quad_image);
    triangle_buttonID = gui.loadImage(triangle_image);
}

//------------------------------------
void GuiInterface::update_active_shader(int selected){
    selected_shader = selected;
    shader_toggles[selected_shader].b = true;
    map_helper.update_layer_source(selected_shader);
    
    for(int x = 0; x < shader_states[selected_shader].sliders.size(); x++){
        float value = shader_states[selected_shader].sliders[x]->getValue();
        shader_states[selected_shader].sliders[x]->setPercent(value);
    }
    
    update_active_sliders();
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
    
    volumes[0] = ofMap(volumes[0],0.3,1.3,0.0,1.0);
    volumes[1] = ofMap(volumes[1],0.5,1.5,0.0,1.0);
    volumes[2] = ofMap(volumes[2],0.5,2.0,0.0,1.0);
}

//------------------------------------
void GuiInterface::update_audio_reactivity(vector<VisualLayer *> &layers){
    for(int x = 0; x < shader_states.size(); x++){

        for(int i = 0; i < shader_states[x].toggles.size(); i++){
            ShaderVariable& variable = layers[x]->shader_variables[i];
            float slider_val = shader_states[x].sliders[i]->getValue();
            
            if(shader_states[x].toggles[i].get_selected_toggle() != 0){
				float audio_val = volumes[shader_states[x].toggles[i].get_selected_toggle() - 1];
				shader_states[x].sliders[i]->update_gradient_percent(audio_val * slider_val);
                variable.value = audio_val * slider_val;
            }
        }
    }
}

//------------------------------------
void GuiInterface::set_theme_colour(ofVec4f theme_colour){
    this->theme_colour = theme_colour;
}

//------------------------------------
void GuiInterface::draw(vector<ShaderVariable> &shader_variables){
    map_helper.set_theme_colour(theme_colour);

    ofSetColor(255);
    img_background.draw(0,0,ofGetWidth(),ofGetHeight());

//    if(ofGetMousePressed()){
//        img.draw(0,0,ofGetWidth(), ofGetHeight());
//    }
    
    draw_add_shape(add_shape_rect);
	draw_selected_layer(selected_layer_rect, shader_variables);
	draw_audio_analysis(audio_analysis_rect);
    draw_duplicate_and_remove(duplicate_remove_rect);
    draw_shader_toggles(shader_toggles_rect);
    draw_mapping_panel(mapping_panel_rect);
}

//------------------------------------
void GuiInterface::draw_border(ofRectangle rect){
    ofPushStyle();
    ofNoFill();
    ofSetColor(255,255);
    ofSetLineWidth(2);
    ofDrawRectangle(rect);
    ofPopStyle();
}

//------------------------------------
void GuiInterface::draw_border_background(ofRectangle rect){
    ofPushStyle();
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(rect);
    ofPopStyle();
}

//------------------------------------
void GuiInterface::draw_add_shape(ofRectangle rect){
    draw_border_background(rect);
    draw_border(rect);
    
    font_large.drawString("ADD SHAPE", rect.x + padding.x, rect.y + padding.y);
    
    auto mainSettings = ofxImGui::Settings();
    mainSettings.windowPos = ofVec2f(rect.x+18, rect.y+20);
    mainSettings.windowSize = ofVec2f(rect.width+30, rect.height+30);
    
    if (ofxImGui::BeginWindow("add shape", mainSettings, window_flags))
    {
        ImTextureID quadID = (ImTextureID)(uintptr_t)quad_buttonID;
        ImTextureID triangleID = (ImTextureID)(uintptr_t)triangle_buttonID;

        if(ImGui::ImageButton(quadID, ImVec2(122,90))){
			if (BaseSurface::count < SurfaceManager::getMaxSurfaces()) {
				map_helper.add_quad_surface();
			}
        }
        ImGui::SameLine(0,5);
        if(ImGui::ImageButton(triangleID, ImVec2(105,95))){
			if (BaseSurface::count < SurfaceManager::getMaxSurfaces()) {
				map_helper.add_triangle_surface();
			}
        }
    }
    ofxImGui::EndWindow(mainSettings);
}

//------------------------------------
void GuiInterface::draw_selected_layer(ofRectangle rect, vector<ShaderVariable> &shader_variables){
    draw_border_background(rect);
    draw_border(rect);
    
    font_large.drawString("SELECTED LAYER", rect.x + padding.x, rect.y + padding.y);

    //--- PARAMS
    for(int i = 0; i < shader_states[selected_shader].sliders.size(); i++){

        ofSetColor(theme_colour.x,theme_colour.y,theme_colour.z);
        font_mid.drawString(shader_variables[i].name, rect.x + padding.x, (param_gui_offset * i) + (rect.y+52));
        
        float slider_val = shader_states[selected_shader].sliders[i]->getValue();
        shader_states[selected_shader].sliders[i]->set_theme_colour(theme_colour);

        if(i < shader_states[selected_shader].toggles.size()){
            
            shader_states[selected_shader].toggles[i].draw(shader_variables[i].name + ofToString(i), ofVec2f(rect.x + padding.x, (param_gui_offset * i) + (rect.y+120)), ofVec2f(rect.width+10, 80), window_flags);
            
            if(shader_states[selected_shader].toggles[i].get_selected_toggle() == 0){
                shader_states[selected_shader].sliders[i]->update_gradient_percent(slider_val);
                shader_variables[i].value = slider_val;
            } else {
				float audio_val = volumes[shader_states[selected_shader].toggles[i].get_selected_toggle() - 1];
				//shader_states[selected_shader].sliders[i]->update_gradient_percent(audio_val * slider_val);
                shader_variables[i].value = audio_val * slider_val;
            }
        } else {
            shader_states[selected_shader].sliders[i]->update_gradient_percent(slider_val);
            shader_variables[i].value = slider_val;
        }
    }
    
    for(int i = 0; i < shader_states[selected_shader].sliders.size(); i++){
        shader_states[selected_shader].sliders[i]->draw();
    }
}

//------------------------------------
void GuiInterface::draw_audio_analysis(ofRectangle rect){
    draw_border_background(rect);
    draw_border(rect);
    
    slider_gradient.set_colour(theme_colour.x, theme_colour.y, theme_colour.z);
    
    int width = 85;
    slider_gradient.draw(0,1, volumes[0],rect.x + 10, rect.y + 10, width, rect.height - 20);
    slider_gradient.draw(0,1, volumes[1],rect.x + 110, rect.y + 10, width, rect.height - 20);
    slider_gradient.draw(0,1, volumes[2],rect.x + 210, rect.y + 10, width, rect.height - 20);
    
    font_large.drawString("BASS", rect.x + 10, rect.y + padding.y);
    font_large.drawString("MID", rect.x + 110, rect.y + padding.y);
    font_large.drawString("HIGH", rect.x + 210, rect.y + padding.y);

}

//------------------------------------
void GuiInterface::draw_mapping_panel(ofRectangle rect){
    //draw_border(rect);
}

//------------------------------------
void GuiInterface::draw_shader_toggles(ofRectangle rect){
    auto mainSettings = ofxImGui::Settings();
    mainSettings.windowPos = ofVec2f(rect.x, rect.y-2);
    mainSettings.windowSize = ofVec2f(rect.width, rect.height+2);
//    ImVec4 c1 = ImColor(1.f, 0.1f, 0.13f, 1.00f);
    ImVec4 c1 = ImColor(theme_colour.x / 255.0f, theme_colour.y / 255.0f, theme_colour.z / 255.0f, theme_colour.w / 255.0f);
    
    ImVec4 c2 = ImColor(1.0f, 1.0f, 1.0f, 1.00f);
    
    int y_padding = 22;
    int toggle_height = 147;
    int sb_multiplier = (toggle_height + y_padding);
    int excess_rows = 0;
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    if (ofxImGui::BeginWindow("shader_toggles", mainSettings, window_flags))
    {
        for(int i = 0; i < shader_toggles.size(); i++){
            ImTextureID texID = (ImTextureID)(uintptr_t) shader_toggles[i].buttonID;
            
            // Active Shader is highlighted
            if (selected_shader == i) ImGui::PushStyleColor(ImGuiCol_Button, c1);
            else ImGui::PushStyleColor(ImGuiCol_Button, c2);
            
            if(ImGui::ImageButton(shader_toggles[i].buttonID, ImVec2(161, 147))){
                update_active_shader(i);
            }
            ImGui::PopStyleColor();
            if( i % 2 == 0) {
                ImGui::SameLine(0,20);
            } else if( i % 2 == 1){
                ImGui::Dummy(ImVec2(0.0,3.0));
            }

            if(i > 7 && i % 2 == 1){
                excess_rows++;
            }
        }
    }

    float slider_val = sb_slider.getValue();
    ImGui::SetScrollY((1.0-slider_val) * (sb_multiplier * excess_rows));

    ofxImGui::EndWindow(mainSettings);
    ImGui::PopStyleVar();
    
    // Make sure only the selected shaders toggle is active.
    for(int i = 0; i < shader_toggles.size(); i++){
        if(i != selected_shader){
            shader_toggles[i].b = false;
        }
    }
    
    sb_slider.update_gradient_percent(slider_val);
    sb_slider.set_theme_colour(theme_colour);
    sb_slider.draw();
}

//------------------------------------
void GuiInterface::draw_duplicate_and_remove(ofRectangle rect){
    
    auto mainSettings = ofxImGui::Settings();
    mainSettings.windowPos = ofVec2f(rect.x - IMGUI_PADDING, rect.y - IMGUI_PADDING);
    mainSettings.windowSize = ofVec2f(TOGGLE_WIDTH,TOGGLE_HEIGHT + 25);
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(18,18));
    
    if (ofxImGui::BeginWindow("duplicate panel", mainSettings, window_flags))
    {
        mouse_over_duplicate_toggle = ImGui::IsMouseHoveringWindow();
        ImTextureID duplicate_texID = (ImTextureID)(uintptr_t)(duplicate_button_ID);
        if(ImGui::ImageButton(duplicate_texID, ImVec2(TOGGLE_WIDTH, TOGGLE_HEIGHT))){
			if (BaseSurface::count < SurfaceManager::getMaxSurfaces() ) {
				map_helper.duplicate_surface();
			}
        }
    }
    ofxImGui::EndWindow(mainSettings);
    
    mainSettings.windowPos = ofVec2f((rect.x + TOGGLE_WIDTH) - 10, rect.y - IMGUI_PADDING);
    if (ofxImGui::BeginWindow("remove panel", mainSettings, window_flags))
    {
        mouse_over_remove_toggle = ImGui::IsMouseHoveringWindow();
        ImTextureID remove_texID = (ImTextureID)(uintptr_t)(remove_button_ID);
        if(ImGui::ImageButton(remove_texID, ImVec2(TOGGLE_WIDTH, TOGGLE_HEIGHT))){
            map_helper.remove_surface();
        }
    }
    ofxImGui::EndWindow(mainSettings);
    ImGui::PopStyleVar();

}

//------------------------------------
bool GuiInterface::is_mouse_over_mapping_toggles(){
    if(mouse_over_remove_toggle | mouse_over_duplicate_toggle){
        return true;
    } else {
        return false;
    }
}

bool GuiInterface::is_touch_over_mapping_toggles(ofVec2f t_pos) {
	ofRectangle duplicate_area(
		duplicate_remove_rect.x - IMGUI_PADDING, duplicate_remove_rect.y - IMGUI_PADDING,
		TOGGLE_WIDTH, TOGGLE_HEIGHT);
	ofRectangle remove_area(
		(duplicate_remove_rect.x + TOGGLE_WIDTH) - 10, duplicate_remove_rect.y - IMGUI_PADDING,
		TOGGLE_WIDTH, TOGGLE_HEIGHT
	);
	
	if (duplicate_area.inside(t_pos) || remove_area.inside(t_pos)) {
		return true;
	}
	else {
		return false;
	}
}

//------------------------------------
bool GuiInterface::is_mouse_inside_mapping_rect(){
    return mapping_panel_rect.inside(ofGetMouseX(), ofGetMouseY());
}

//------------------------------------
int GuiInterface::get_selected_shader(){
    return selected_shader;
}


//----------------WINDOWS ONLY
//--------------------------------------------------------------
void GuiInterface::touchDown(map<int, ofTouchEventArgs> touchMap) {

	vector<CustomSlider*> sliders = shader_states[get_selected_shader()].sliders;
	for (int i = 0; i < sliders.size(); i++) {
		for (auto &t : touchMap) {
			auto &touch = t.second;
			if (sliders[i]->box.inside(touch.x, touch.y)) {
				sliders[i]->active_touch_idx = touch.id;
				sliders[i]->updatePercentFromMouse(touch.x, touch.y);
			}
		}
	}

    for (auto &t : touchMap) {
        auto &touch = t.second;
        if (sb_slider.box.inside(touch.x, touch.y)) {
            sb_slider.active_touch_idx = touch.id;
            sb_slider.updatePercentFromMouse(touch.x, touch.y);
        }
    }


}

//--------------------------------------------------------------
void GuiInterface::touchMoved(map<int, ofTouchEventArgs> touchMap) {

	vector<CustomSlider*> sliders = shader_states[get_selected_shader()].sliders;
	for (int i = 0; i < sliders.size(); i++) {
		for (auto &t : touchMap) {
			auto &touch = t.second;
			if (sliders[i]->active_touch_idx == touch.id) {
				if (sliders[i]->get_is_active()) {
					sliders[i]->updatePercentFromMouse(touch.x, touch.y);
				}
			}
		}
	}
    
    for (auto &t : touchMap) {
        auto &touch = t.second;
        if (sb_slider.active_touch_idx == touch.id) {
            if (sb_slider.get_is_active()) {
                sb_slider.updatePercentFromMouse(touch.x, touch.y);
            }
        }
    }
}

//--------------------------------------------------------------
void GuiInterface::touchUp(map<int, ofTouchEventArgs> touchMap) {

}
