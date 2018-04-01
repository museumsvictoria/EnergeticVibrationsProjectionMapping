//
//  PingPong.h
//  EnergeticVibrationsAV
//
//  Created by Joshua Batty on 4/10/17.
//
//

#pragma once
#include "ofMain.h"

class PingPong{
    
public:    
    //--------------------------------------------------------------
    virtual void init_fbos();
    void createFullScreenQuad();
    //--------------------------------------------------------------
    
    ofVboMesh   m_fsQuadVbo;
    
    /// FBOs
    ofFbo       m_fbos[2]; // ping pong fbos
    ofFbo       m_renderFbo; // final render fbo
    ofFbo       m_src_fbo;
};
