//
//  RenderFbo.h
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 1/11/17.
//
//

#pragma once
#include "ofMain.h"

class RenderFbo{
    
public:
    ofFbo  fbo; // final render fbo

    //--------------------------------------------------------------
    void init(int width = ofGetWidth(), int height = ofGetHeight()){
        /// Final Render FBO
        ///-------------------------
        ofFbo::Settings renderFboSettings;
        renderFboSettings.width = width;
        renderFboSettings.height = height;
        renderFboSettings.internalformat = GL_RGBA;
        renderFboSettings.numSamples = 8;
        renderFboSettings.useDepth = false;
        renderFboSettings.useStencil = false;
        renderFboSettings.textureTarget = GL_TEXTURE_2D;
        renderFboSettings.minFilter = GL_LINEAR;
        renderFboSettings.maxFilter = GL_LINEAR;
        renderFboSettings.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
        renderFboSettings.wrapModeVertical = GL_CLAMP_TO_EDGE;
        
        fbo.allocate( renderFboSettings );
    }
};
