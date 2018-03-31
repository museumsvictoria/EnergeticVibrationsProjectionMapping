//
//  Gradient.cpp
//  EnergeticVibrations_ProjectionMapping
//
//  Created by Joshua Batty on 16/1/18.
//
//

#include "Gradient.h"


//------------------------------------
Gradient::Gradient(){
    gradient.load("shaders/passthrough.vert","shaders/Interface/gradient.frag");
}

//------------------------------------
void Gradient::draw(int is_slider, int verticle_or_horizontal, float perc, int x, int y, int w, int h){
    ofFill();
    ofSetColor(255);

    gradient.begin();
    gradient.setUniform3f("resolution",w,h,1);
    gradient.setUniform1f("perc",perc);
    gradient.setUniform1i("is_slider", is_slider);
    gradient.setUniform1i("verticle_or_horizontal", verticle_or_horizontal);
    ofDrawRectangle(x, y, w, h);
    gradient.end();
}
