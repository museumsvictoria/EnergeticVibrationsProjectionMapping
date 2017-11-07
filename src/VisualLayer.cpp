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
    hue_offset = 0.0;
    shader_param1 = 0.0;
    shader_param2 = 0.0;
    shader_param3 = 0.0;
}

//--------------------------------------------------------------
void VisualLayer::setup(string name){
    
    this->name = name; // Give our source a decent name
    allocate(LAYER_RENDER_SIZE_X, LAYER_RENDER_SIZE_Y); // Allocate our FBO source, decide how big it should be
    
    render_fbo.init(LAYER_RENDER_SIZE_X, LAYER_RENDER_SIZE_Y);
}

//--------------------------------------------------------------
void VisualLayer::load_shader(string file){
    scene_shader.load("shaders/passthrough.vert",file);
}

//--------------------------------------------------------------
void VisualLayer::load_movie(string file){
    player.load(file);
}

//--------------------------------------------------------------
void VisualLayer::update(){
    hue_offset = ofGetElapsedTimef() * 10.;
    
    render_fbo.fbo.begin();
        ofClear(0,0,0,0);
        scene_shader.begin();
        scene_shader.setUniform3f("iResolution", LAYER_RENDER_SIZE_X, LAYER_RENDER_SIZE_Y, 1);
        scene_shader.setUniform1f("iTime", ofGetElapsedTimef());
        scene_shader.setUniform1i("iFrame", ofGetFrameNum());
        scene_shader.setUniform1f("param1", shader_param1);
        scene_shader.setUniform1f("param2", shader_param2);
        scene_shader.setUniform1f("param3", shader_param3);
        scene_shader.setUniform1f("hue_offset", hue_offset);
        ofDrawRectangle(0, 0, render_fbo.fbo.getWidth(), render_fbo.fbo.getHeight());

        scene_shader.end();
    render_fbo.fbo.end();
}

//--------------------------------------------------------------
void VisualLayer::draw(){
    ofClear(0,0,0,0);
    render_fbo.fbo.draw(0,0,fbo->getWidth(),fbo->getHeight());
}
