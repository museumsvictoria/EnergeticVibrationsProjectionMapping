//
//  SurfaceMask.h
//  EnergeticVibrationsAV
//
//  Created by Joshua Batty on 8/3/18.
//
//

#pragma once
#include "ofMain.h"
#include "Settings.h"

class SurfaceMask{
    
public:
    void setup();
    void init_fbos();
    void set_size(int w, int h);
    void set_dimensions(ofRectangle rect);
    void set_source_texture(ofFbo& tex);
    void update();
    void draw();
    
    ofShader shader_image;
    ofImage mask_image;

    ofRectangle rect_dim;

	/// FBOs
	ofFbo       m_mapper_fbo; 
	ofFbo       m_mask_fbo;
	ofFbo       m_renderFbo; // final render fbo
    
    int width;
    int height;
};
