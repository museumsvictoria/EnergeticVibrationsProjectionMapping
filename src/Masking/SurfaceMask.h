//
//  SurfaceMask.h
//  EnergeticVibrationsAV
//
//  Created by Joshua Batty on 8/3/18.
//
//

#pragma once
#include "ofMain.h"
#include "PingPong.h"
#include "Settings.h"

class SurfaceMask : public PingPong{
    
public:
    void setup();
    void init_fbos();
    void set_size(int w, int h);
    void set_dimensions(ofRectangle rect);
    void set_source_texture(ofFbo& tex);
    void update();
    void draw();
    
    ofFbo& getFbo();

    ofShader shader_image;
    ofImage mask_image;

    ofRectangle rect_dim;
    
    int width;
    int height;
};
