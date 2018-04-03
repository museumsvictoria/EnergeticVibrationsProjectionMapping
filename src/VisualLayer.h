//
//  VisualLayer.hpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 30/10/17.
//
//

#pragma once 

#include "ofMain.h"
#include "Settings.h"
#include "FboSource.h"
#include "FullscreenQuad.h"
#include "RenderFbo.h"
#include "ShaderVariable.h"

class VisualLayer : public ofx::piMapper::FboSource {
public:
    
    VisualLayer();
    void setup(string name, int scene_num);
    void init_variables(vector<ShaderVariable> shader_variables);
    
    void load_movie(string file);
    void set_scene_shader(ofShader scene_shader);
    void update();
    void draw();
    
	void toggle_shader() { use_shader = !use_shader; }
	bool is_shader() { return use_shader; }

    vector<ShaderVariable> shader_variables;

    RenderFbo render_fbo;

private:
    ofShader scene_shader;
    ofVideoPlayer player;
    FullscreenQuad quad;
	bool use_shader;
    
    int scene_select;
    
};
