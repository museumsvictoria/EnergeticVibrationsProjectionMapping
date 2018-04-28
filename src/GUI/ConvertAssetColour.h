//
//  ConvertAssetColour.h
//  EnergeticVibrationsProjectionMapping
//
//  Created by Joshua Batty on 2/4/18.
//
//

#pragma once

#include "ofMain.h"

class ConvertAssetColour{
public:
    
    ofImage convert_asset_colour(int w, int h, ofImage image, ofVec4f theme_colour){
        ofFbo fbo;
        ofImage img;
        fbo.allocate(w, h, GL_RGBA);
        
        ofShader shader;
        shader.load("shaders/passthrough.vert","shaders/Interface/asset_colour_changer.frag");
        
        fbo.begin();
        ofClear(0,0,0,255);
        shader.begin();
        shader.setUniform3f("iResolution", w,h,1);
        shader.setUniform3f("base_colour", theme_colour.x / 255.0, theme_colour.y / 255.0,theme_colour.z / 255.0);
        shader.setUniformTexture( "iChannel0", image.getTexture(), 1);
        ofSetColor(255,255);
        ofDrawRectangle(0,0,w,h);
        shader.end();
        fbo.end();
        
        // Write the fbo contents into our ofPixels
        ofPixels pixels;
        fbo.readToPixels(pixels);
        
        unsigned char *p = pixels.begin();
        img.setFromPixels(p,fbo.getWidth(),fbo.getHeight(),OF_IMAGE_COLOR_ALPHA);
        img.update();
        
        return img;
    }
    
};
