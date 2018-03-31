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

const int PATTERN_MESH_2D = 0;
const int COLOUR_GRADIENT = 1;
const int ESCHER_LIKE = 2;
const int FLOWER_OF_LIFE = 3;
const int TRI_LATTICE = 4;
const int RADIAL_HEXAGON = 5;
const int OP_ART_TWISTER = 6;
const int HEXAGON_GRADIENT = 7;
const int POLYGON_PATTERNS = 8;
const int SNUB_QUADRILLE = 9;
const int PENTAGON_TESSELLATIONS = 10;

struct ShaderParams{
    vector<float> params = {0.0,0.0,0.0,0.0};
    vector<string> names = {"","","",""};
};

class VisualLayer : public ofx::piMapper::FboSource {
public:
    
    VisualLayer();
    void init_params();
    void setup(string name, int scene_num);
    
    void load_movie(string file);
    
    void update();
    void draw();
    
	void toggle_shader() { use_shader = !use_shader; }
	bool is_shader() { return use_shader; }

    vector<ShaderParams> shader_params;

    RenderFbo render_fbo;

private:
    ofShader scene_shader;
    ofVideoPlayer player;
    FullscreenQuad quad;
	bool use_shader;
    
    int scene_select;
    
};
