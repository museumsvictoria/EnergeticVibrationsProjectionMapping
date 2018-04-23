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
    fboSettings.width = width;
    fboSettings.height = height;
    fboSettings.internalformat = GL_RGBA;
    fboSettings.numSamples = 8;
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
    
    m_renderFbo.allocate( renderFboSettings );
    m_src_fbo.allocate( renderFboSettings );
    
    cout << "w = " << width << " -h = " << height << endl;
}

//--------------------------------------------------------------
void SurfaceMask::setup(){
    shader_image.load("shaders/passthrough.vert","shaders/Masking/blend_mask.frag");
#ifdef PORTRAIT_MODE
    mask_image.load("images/mask_portrait.png");
#else
    mask_image.load("images/mask_landscape.png");
#endif
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
void SurfaceMask::set_size(int w, int h){
    width = w;
    height = h;
}

//--------------------------------------------------------------
void SurfaceMask::set_dimensions(ofRectangle rect){
    rect_dim.x = rect.x;
    rect_dim.y = rect.y;
    rect_dim.width = rect.width;
    rect_dim.height = rect.height;
}

//--------------------------------------------------------------
void SurfaceMask::update(){
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
}

//--------------------------------------------------------------
void SurfaceMask::draw(){
    
    /// Draw To Screen
    ////////////////////
    ofSetColor(ofColor::white);

#ifdef PORTRAIT_MODE
    m_renderFbo.draw(rect_dim.x, rect_dim.y, rect_dim.width, rect_dim.height);
    
    //ofSetColor(255,abs(cos(ofGetFrameNum()*0.06))*255);
    //m_src_fbo.draw(0,0,ofGetWidth(),ofGetHeight());
    
//    ofSetColor(255,abs(sin(ofGetFrameNum()*0.1))*255);
//    mask_image.draw(0,0,ofGetWidth(),ofGetHeight());

#else
    m_renderFbo.draw(0,0,ofGetWidth(),ofGetHeight());
#endif

}

ofFbo& SurfaceMask::getFbo(){
    return m_renderFbo;
}
