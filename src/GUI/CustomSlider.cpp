/*
 *  CustomSlider.cpp
 *  Created by Golan Levin on 2/24/12.
 *
 */

#include "CustomSlider.h"

//----------------------------------------------------
CustomSlider::CustomSlider(){
	bWasSetup = false;
}

//----------------------------------------------------
CustomSlider::~CustomSlider(){
	clear();
}

//-----------------------------------------------------------------------------------------------------------------------
void CustomSlider::setup(float inx, float iny, float inw, float inh, float loVal, float hiVal, float initialValue, bool bVert, bool bIsSlider, bool bDrawNum){
	x = inx;
	y = iny; 
	width = inw; 
	height = inh;
	box.set(x,y, width, height); 
	numberDisplayPrecision = 2;
	
    this->bIsSlider = bIsSlider;
	bVertical = bVert;
	bDrawNumber = bDrawNum;
	bHasFocus = false;
    isActive = false;
    
	lowValue = loVal;
	highValue = hiVal;
	percent = ofMap(initialValue, lowValue,highValue, 0,1); 
	percent = ofClamp(percent, 0,1);
	
	labelString = ""; 
	
    thumb_radius = 20;
    gradient_perc = getValue();

	active_touch_idx = 0;
    
	if(!bWasSetup){
		ofAddListener(ofEvents().mouseMoved, this, &CustomSlider::mouseMoved);
		ofAddListener(ofEvents().mousePressed, this, &CustomSlider::mousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &CustomSlider::mouseReleased);
		ofAddListener(ofEvents().mouseDragged, this, &CustomSlider::mouseDragged);
		bWasSetup = true;
	}
}

//----------------------------------------------------
void CustomSlider::clear(){
	if(bWasSetup){
		ofRemoveListener(ofEvents().mouseMoved, this, &CustomSlider::mouseMoved);
		ofRemoveListener(ofEvents().mousePressed, this, &CustomSlider::mousePressed);
		ofRemoveListener(ofEvents().mouseReleased, this, &CustomSlider::mouseReleased);
		ofRemoveListener(ofEvents().mouseDragged, this, &CustomSlider::mouseDragged);
	}
	bWasSetup = false;
}

//----------------------------------------------------
void CustomSlider::setLabelString (string str){
	labelString = str;
}

//----------------------------------------------------
void CustomSlider::update_gradient_percent(float perc){
    gradient_perc = perc;
}

//------------------------------------
void CustomSlider::set_theme_colour(ofVec4f theme_colour){
    this->theme_colour = theme_colour;
    colour_gradient.set_colour(theme_colour.x, theme_colour.y, theme_colour.z);
}

//----------------------------------------------------
void CustomSlider::draw(){
	
	ofPushStyle();
	ofEnableAlphaBlending();
	ofDisableSmoothing();
	ofPushMatrix();
	ofTranslate(x,y,0);
	
	// Use different alphas if we're actively maniupulating me. 
	float spineAlpha  = (bHasFocus) ? 192:128;
	

	// draw thumb
    ofSetCircleResolution(160);
    if (bVertical){
        if(bIsSlider){
            colour_gradient.draw(1, 1, gradient_perc, 0, 0, width, height );
        } else {
            colour_gradient.draw(0, 1, gradient_perc, 0, 0, width, height );
        }
        // draw box outline
        ofNoFill();
        ofSetLineWidth(10.0);
        ofSetColor(25,25,25, 255);
        ofDrawLine(-10, 0, width+10, 0);
        ofDrawLine(-10,height, width+10,height);
        ofSetLineWidth(18.0);
        ofDrawLine(0, 0, 0, height);
        ofDrawLine(width, 0, width, height);
        
        float thumbY = ofMap(percent, 0,1, height - thumb_radius, 0 + thumb_radius, true);
        ofSetLineWidth(3.0);
        ofSetColor(25, 25, 25, 255);
        ofDrawCircle(width/2, thumbY, 22);
        //ofSetColor(255, 26, 34, 255);
        ofSetColor(theme_colour.x,theme_colour.y,theme_colour.z,theme_colour.w);
        ofFill();
        ofDrawCircle(width/2, thumbY, thumb_radius);
    } else {
        colour_gradient.draw(1, 0, gradient_perc, 0, 9, width, height - 18);

        // draw box outline
        ofNoFill();
        ofSetLineWidth(18.0);
        ofSetColor(25,25,25, 255);
        ofDrawLine(-10, 0, width+10, 0);
        ofDrawLine(-10,height, width+10,height);
        ofSetLineWidth(10.0);
        ofDrawLine(-5, 0, -5, height);
        ofDrawLine(width+5, 0, width+5, height);
        
        float thumbX = ofMap(percent, 0,1, 0 + thumb_radius,width - thumb_radius, true);
        ofSetLineWidth(3.0);
        ofSetColor(25, 25, 25, 255);
        ofDrawCircle(thumbX, height/2, 22);
        //ofSetColor(255, 26, 34, 255);
        ofSetColor(theme_colour.x,theme_colour.y,theme_colour.z,theme_colour.w);
        ofFill();
        ofDrawCircle(thumbX, height/2, thumb_radius);
    }
    
	ofPopMatrix();
	ofPopStyle();
}

//----------------------------------------------------
float CustomSlider::getValue(){
	// THIS IS THE MAIN WAY YOU GET THE VALUE FROM THE SLIDER!
	float out = ofMap(percent, 0,1, lowValue,highValue, true); 
	return out;
}


//----------------------------------------------------
// Probably not used very much. 
float CustomSlider::getLowValue(){
	return lowValue;
}
float CustomSlider::getHighValue(){
	return highValue;
}
float CustomSlider::getPercent(){
	return percent;
}

//----------------------------------------------------
// Probably not used very much. 
void CustomSlider::setLowValue(float lv){
	lowValue = lv;
}
void CustomSlider::setHighValue(float hv){
	highValue = hv; 
}
void CustomSlider::setPercent (float p){
	// Set the slider's percentage from the outside. 
	p = ofClamp(p, 0,1);
	percent	= p;
}
void CustomSlider::setNumberDisplayPrecision(int prec){
	numberDisplayPrecision = prec;
}

//----------------------------------------------------
void CustomSlider::set_is_active(bool val){
    isActive = val;
}
bool CustomSlider::get_is_active() {
	return isActive;
}
		
//----------------------------------------------------
void CustomSlider::mouseMoved(ofMouseEventArgs& event){
	bHasFocus = false;
}
void CustomSlider::mouseDragged(ofMouseEventArgs& event){
	if (bHasFocus){
        if(isActive){
            updatePercentFromMouse (event.x, event.y);
        }
    }
}
void CustomSlider::mousePressed(ofMouseEventArgs& event){
	bHasFocus = false;
	if (box.inside(event.x, event.y)){
		bHasFocus = true;
        if(isActive){
            updatePercentFromMouse (event.x, event.y);
        }
    }
}
void CustomSlider::mouseReleased(ofMouseEventArgs& event){
	if (bHasFocus){
		if (box.inside(event.x, event.y)){
            if(isActive){
                updatePercentFromMouse (event.x, event.y);
            }
		}
	}
	bHasFocus = false;
}

//----------------------------------------------------
void CustomSlider::updatePercentFromMouse (int mx, int my){
    if (bVertical){
        percent = ofMap(my, y + thumb_radius, (y+height) - thumb_radius,  1,0, true);
    }
    else {
        percent = ofMap(mx, x + thumb_radius, (x+width) - thumb_radius,  0,1, true);
    }
}


		

