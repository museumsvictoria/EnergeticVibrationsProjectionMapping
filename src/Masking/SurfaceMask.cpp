//
//  SurfaceMask.cpp
//  EnergeticVibrationsAV
//
//  Created by Joshua Batty on 8/3/18.
//
//

#include "SurfaceMask.h"


//--------------------------------------------------------------
void SurfaceMask::init_fbos(){
    
    /// Shader FBOs
    ///-------------------------
    ofFbo::Settings fboSettings;
    fboSettings.width = ofGetWidth();
    fboSettings.height = ofGetHeight();
    fboSettings.internalformat = GL_RGBA;
    fboSettings.numSamples = 8;//1
    fboSettings.useDepth = false;
    fboSettings.useStencil = false;
    fboSettings.textureTarget = GL_TEXTURE_2D;
    fboSettings.minFilter = GL_LINEAR;
    fboSettings.maxFilter = GL_LINEAR;
    fboSettings.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
    fboSettings.wrapModeVertical = GL_CLAMP_TO_EDGE;
    
    // create our FBOs
    m_fbos[ 0 ].allocate( fboSettings );
    
    // setup FBOs
    m_fbos[ 0 ].begin();
    ofClear( 0, 0, 0, 0 );
    m_fbos[ 0 ].end();
    m_fbos[ 0 ].getTexture().bind( 1 );
    
    //------------------------------
    
    /// Final Render FBO
    ///-------------------------
    ofFbo::Settings renderFboSettings;
    renderFboSettings.width = ofGetWidth();
    renderFboSettings.height = ofGetHeight();
    renderFboSettings.internalformat = GL_RGBA;
    renderFboSettings.numSamples = 4;
    renderFboSettings.useDepth = false;
    renderFboSettings.useStencil = false;
    renderFboSettings.textureTarget = GL_TEXTURE_2D;
    renderFboSettings.minFilter = GL_LINEAR;
    renderFboSettings.maxFilter = GL_LINEAR;
    renderFboSettings.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
    renderFboSettings.wrapModeVertical = GL_CLAMP_TO_EDGE;
    
    m_renderFbo.allocate( renderFboSettings );
    m_src_fbo.allocate( renderFboSettings );
}

//--------------------------------------------------------------
void SurfaceMask::setup(){
    // Use GL_TEXTURE_2D Textures (normalized texture coordinates 0..1)
    //ofDisableArbTex();
    
    shader_image.load("shaders/passthrough.vert","shaders/Masking/blend_mask.frag");
    mask_image.load("images/mask.png");

    shader_image.begin();
    shader_image.setUniform1i( "iChannel0", 1);
    shader_image.end();
    
    init_fbos();
    
}

//--------------------------------------------------------------
void SurfaceMask::set_source_texture(ofFbo& tex){
    m_fbos[ 0 ].begin();
    ofClear( 0, 0, 0, 0 );
    tex.draw(0,0,ofGetWidth(),ofGetHeight());
    m_fbos[ 0 ].end();
}

//--------------------------------------------------------------
void SurfaceMask::update(){
    // clear to green as grayScott runs in red and green channels
    ofClear( 0, 255, 0, 255 );
    ofDisableDepthTest();
    

    m_src_fbo.begin();
    ofClear(0,0,0,0);
    ofSetColor(255,255);
    mask_image.draw(0,0,ofGetWidth(),ofGetHeight());
    m_src_fbo.end();

    
    /// Final Render
    ////////////////
    m_renderFbo.begin();
    {
        ofClear(0,0,0,255);
        shader_image.begin();
        shader_image.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(),1);
        shader_image.setUniform1f("iTime", ofGetElapsedTimef());
        shader_image.setUniformTexture( "iChannel0", m_src_fbo.getTexture(), 1);
        shader_image.setUniformTexture( "iChannel1",  m_fbos[ 0 ].getTexture(), 2 );

        ofSetColor(255,255);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        shader_image.end();
    }
    m_renderFbo.end();
    
    glDisable( GL_CULL_FACE );
}

//--------------------------------------------------------------
void SurfaceMask::draw(){
    
    /// Draw To Screen
    ////////////////////
    ofSetColor(ofColor::white);
    m_renderFbo.draw(0,0,ofGetWidth(),ofGetHeight());
}

ofFbo& SurfaceMask::getFbo(){
    return m_renderFbo;
}
