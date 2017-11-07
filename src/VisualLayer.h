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

class VisualLayer : public ofx::piMapper::FboSource {
public:
    
    VisualLayer();
    void setup(string name);
    
    void load_shader(string file);
    void load_movie(string file);
    
    void update();
    void draw();
    
private:
    ofShader scene_shader;
    ofVideoPlayer player;
    RenderFbo render_fbo;
    FullscreenQuad quad;
    
    float shader_param1, shader_param2, shader_param3;
    float hue_offset;
};
