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
void VisualLayer::init_params(){
    shader_params.clear();
    
    for(int i = 0; i < 9; i++){
        shader_params.push_back(ShaderParams());
    }
   
    shader_params[PATTERN_MESH_2D].params = {0.0f,0.0f,0.0f,0.0f};
    shader_params[PATTERN_MESH_2D].names = {"SPEED","SHAPE_ITER","GRID_ITER", "HUESHIFT"};
    
    shader_params[COLOUR_GRADIENT].params = {0.1f,0.02f,0.0f,0.0f};
    shader_params[COLOUR_GRADIENT].names = {"COL_ITER_X", "COL_ITER_Y", "SPEED", "HUESHIFT"};
    
    shader_params[ESCHER_LIKE].params = {0.5f,0.0f,1.0f,0.0f};
    shader_params[ESCHER_LIKE].names = {"circle_offset", "circle_iter", "grid_iter", "HUESHIFT"};
 
    shader_params[FLOWER_OF_LIFE].params = {1.0f,0.0f,0.3f,0.0f};
    shader_params[FLOWER_OF_LIFE].names = {"brightness","time_scale","grid_size", "HUESHIFT"};

    shader_params[TRI_LATTICE].params = {1.0f,0.0f,1.0f,0.0f};
    shader_params[TRI_LATTICE].names = {"num_triangles","ROTATION","colour mix", "HUESHIFT"};
    
    shader_params[RADIAL_HEXAGON].params = {0.0f,1.0f,0.0f,0.0f};
    shader_params[RADIAL_HEXAGON].names = {"circle_iter","grid_size","time_skip", "HUESHIFT"};

    shader_params[OP_ART_TWISTER].params = {1.0f,1.0f,0.0f,0.0f};
    shader_params[OP_ART_TWISTER].names = {"iter_size","grid_size","speed", "HUESHIFT"};

    shader_params[HEXAGON_GRADIENT].params = {0.5,0.2,0.0};
    shader_params[HEXAGON_GRADIENT].names = {"speed","circle_iter","iter", "HUESHIFT"};
    
    shader_params[POLYGON_PATTERNS].params = {0.5,0.2,0.0};
    shader_params[POLYGON_PATTERNS].names = {"speed","circle_iter","iter", "HUESHIFT"};
}

//--------------------------------------------------------------
void VisualLayer::setup(string name, int scene_num){
    
    this->name = name; // Give our source a decent name
    scene_select = scene_num;
    allocate(LAYER_RENDER_SIZE_X, LAYER_RENDER_SIZE_Y); // Allocate our FBO source, decide how big it should be
    
    render_fbo.init(LAYER_RENDER_SIZE_X, LAYER_RENDER_SIZE_Y);
    
    scene_shader.load("shaders/passthrough.vert","shaders/shader_selector.frag");

	use_shader = true;
    
    init_params();
}

//--------------------------------------------------------------
void VisualLayer::load_movie(string file){
    player.load(file);
	player.play();
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
			scene_shader.setUniform1f("param1", shader_params[scene_select].params[0]);
			scene_shader.setUniform1f("param2", shader_params[scene_select].params[1]);
			scene_shader.setUniform1f("param3", shader_params[scene_select].params[2]);
			scene_shader.setUniform1f("hue_offset", shader_params[scene_select].params[3] * PI);
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
