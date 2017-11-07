//
//  FullscreenQuad.h
//  EnergeticVibrationsAV
//
//  Created by Joshua Batty on 4/10/17.
//
//

#pragma once
#include "ofMain.h"

class FullscreenQuad{
    
public:
    ofVboMesh   m_fsQuadVbo;

    //--------------------------------------------------------------
    void createFullScreenQuad(){
        // -1.0 to +1.0 is the full viewport (screen) if you use these as vertices in your vertex shader
        // (without multiplying by model, view, and projection matrices)
        
        ofVec3f vertices[4] =
        {
            ofVec3f(  1.0f,  1.0f, 0.0f ),
            ofVec3f( -1.0f,  1.0f, 0.0f ),
            ofVec3f(  1.0f, -1.0f, 0.0f ),
            ofVec3f( -1.0f, -1.0f, 0.0f )
        };
        
        ofIndexType indices[6] =
        {
            0, 1, 2,
            2, 1, 3
        };
        
        // Texture coordinates vary from 0.0 to 1.0 when they are in normalized format
        // ofDisableArbTex() was called earlier set that we're using normalized texture coordinates
        ofVec2f texCoords[4] =
        {
            ofVec2f( 1.0f, 0.0f ),
            ofVec2f( 0.0f, 0.0f ),
            ofVec2f( 1.0f, 1.0f ),
            ofVec2f( 0.0f, 1.0f )
        };
        
        m_fsQuadVbo.addVertices( vertices, 4 );
        m_fsQuadVbo.addTexCoords( texCoords, 4 );
        m_fsQuadVbo.addIndices( indices, 6 );
    }
    
    void draw_gl2_quad(int width, int height){
        ofSetColor(255,255,255);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(0,0,0);
        glTexCoord2f(1,0); glVertex3f(width,0,0);
        glTexCoord2f(1,1); glVertex3f(width,height,0);
        glTexCoord2f(0,1); glVertex3f(0,height,0);
        glEnd();
    }
};
