//
//  VisualLayer.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 30/10/17.
//
//

#include "VisualLayer.h"



//--------------------------------------------------------------
VisualLayer::VisualLayer(){

}

//--------------------------------------------------------------
void VisualLayer::setup(string name, int scene_num){
    
    this->name = name; // Give our source a decent name
    scene_select = scene_num;

    allocate(LAYER_RENDER_SIZE_X, LAYER_RENDER_SIZE_Y); // Allocate our FBO source, decide how big it should be
    render_fbo.init(LAYER_RENDER_SIZE_X, LAYER_RENDER_SIZE_Y);
    
	use_shader = true;
}

//--------------------------------------------------------------
void VisualLayer::init_variables(vector<ShaderVariable> shader_variables){
    this->shader_variables = shader_variables;
}

//--------------------------------------------------------------
void VisualLayer::load_movie(string file){
    player.load(file);
	player.play();
}

//--------------------------------------------------------------
void VisualLayer::set_scene_shader(ofShader scene_shader){
    this->scene_shader = scene_shader;
}

//--------------------------------------------------------------
void VisualLayer::update(){

    render_fbo.fbo.begin();
        ofClear(0,0,0,0);
		if (use_shader) {
			scene_shader.begin();
			scene_shader.setUniform3f("resolution", LAYER_RENDER_SIZE_X, LAYER_RENDER_SIZE_Y, 1);
			scene_shader.setUniform1f("time", ofGetElapsedTimef());
			scene_shader.setUniform1i("iFrame", ofGetFrameNum());
			scene_shader.setUniform1i("scene_select", scene_select);
			scene_shader.setUniform1f("param1", shader_variables[0].value);
			scene_shader.setUniform1f("param2", shader_variables[1].value);
			scene_shader.setUniform1f("param3", shader_variables[2].value);
			scene_shader.setUniform1f("hue_offset", shader_variables[3].value * PI);
			ofDrawRectangle(0, 0, render_fbo.fbo.getWidth(), render_fbo.fbo.getHeight());
			scene_shader.end();
		} else {
			player.update();
			player.draw(0, 0);
		}
    render_fbo.fbo.end();
}

//--------------------------------------------------------------
void VisualLayer::draw(){
    ofClear(0,0,0,0);
    render_fbo.fbo.draw(0,0,fbo->getWidth(),fbo->getHeight());
}
