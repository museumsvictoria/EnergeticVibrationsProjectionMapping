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
    m_mapper_fbo.allocate( fboSettings );
	m_renderFbo.allocate(fboSettings);
	m_mask_fbo.allocate(fboSettings);

    // setup FBOs
	m_mapper_fbo.begin();
    ofClear( 0, 0, 0, 0 );
	m_mapper_fbo.end();
	m_mapper_fbo.getTexture().bind( 1 );

	m_renderFbo.begin();
	ofClear(0, 0, 0, 0);
	m_renderFbo.end();

	m_mask_fbo.begin();
	ofClear(0, 0, 0, 0);
	m_mask_fbo.end();

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
void SurfaceMask::set_source_texture(ofFbo& tex) {
	m_mapper_fbo.begin();
	ofClear(0, 0, 0, 0);
	ofSetColor(255, 255);
	tex.draw(0, 0, m_mapper_fbo.getWidth(), ofGetHeight());
	m_mapper_fbo.end();
}

//--------------------------------------------------------------
void SurfaceMask::update(){
	m_mask_fbo.begin();
	ofClear(0, 0, 0, 0);
	ofSetColor(255, 255);
	mask_image.draw(0, 0, m_mask_fbo.getWidth(), ofGetHeight());
	m_mask_fbo.end();
	
	
    /// Final Render
    ////////////////
    m_renderFbo.begin();

        ofClear(0,0,0,255);
        shader_image.begin();
        shader_image.setUniform3f("iResolution", ofGetWidth() / 2, ofGetHeight(),1);
		shader_image.setUniform1f("iTime", ofGetElapsedTimef());
		shader_image.setUniformTexture("iChannel0", m_mask_fbo.getTexture(), 1);
		shader_image.setUniformTexture("iChannel1", m_mapper_fbo.getTexture(), 2);

        ofSetColor(255,255);
        ofDrawRectangle(0,0,ofGetWidth()/2,ofGetHeight());
		shader_image.end();
    m_renderFbo.end();
}

//--------------------------------------------------------------
void SurfaceMask::draw(){
    
    /// Draw To Screen
    ////////////////////
    //ofSetColor(ofColor::white);
	ofSetColor(255, 255);

#ifdef PORTRAIT_MODE
	int start_x = ofGetWidth() / 2;
	int center_x = start_x + ofGetWidth() / 4;
	int center_y = ofGetHeight() / 2;
	int fbo_w = m_renderFbo.getWidth();
	int fbo_h = m_renderFbo.getHeight();

	ofPushMatrix();
		ofTranslate(center_x, center_y, 0);//move pivot to centre
		ofRotate(270, 0, 0, 1);//rotate from centre
		ofPushMatrix();
			ofTranslate(-center_x, -center_y, 0);
			int x = start_x;
			int y = 0;
			int new_fbo_h = fbo_w;
			float scale = (float)new_fbo_h / (float)fbo_h;
			int new_fbo_w = scale * (float)fbo_w;
			float ratio = (float)fbo_w / (float)fbo_h;
			float new_fbo_x = x - (((float)new_fbo_w - (float)fbo_w) / 2.0f);
			float new_fbo_y = y - (new_fbo_w / 8);
			m_renderFbo.draw(new_fbo_x, new_fbo_y, new_fbo_w, new_fbo_h);
		ofPopMatrix();
	ofPopMatrix();
#else
	m_renderFbo.draw(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
#endif

}

