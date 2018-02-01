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
void CustomSlider::setup(float inx, float iny, float inw, float inh, float loVal, float hiVal, float initialValue, bool bVert, bool bDrawNum){
	x = inx;
	y = iny; 
	width = inw; 
	height = inh;
	box.set(x,y, width, height); 
	numberDisplayPrecision = 2;
	
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
    
	if(!bWasSetup){
		ofAddListener(ofEvents().mouseMoved, this, &CustomSlider::mouseMoved);
		ofAddListener(ofEvents().mousePressed, this, &CustomSlider::mousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &CustomSlider::mouseReleased);
		ofAddListener(ofEvents().mouseDragged, this, &CustomSlider::mouseDragged);
        
        //----------------WINDOWS ONLY
#ifdef WINDOWS_TOUCH
        /* Essential setup */
        ofxWin8TouchSetup();
        ofRegisterTouchEvents(this);
        ofAddListener(ofEvents().touchDown, this, &CustomSlider::touchDown);
        ofAddListener(ofEvents().touchMoved, this, &CustomSlider::touchMoved);
        ofAddListener(ofEvents().touchUp, this, &CustomSlider::touchUp);
        ofAddListener(ofEvents().touchDoubleTap, this, &CustomSlider::touchDoubleTap);
        ofAddListener(ofEvents().touchCancelled, this, &CustomSlider::touchCancelled);
#endif
        
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
        
        //----------------WINDOWS ONLY
#ifdef WINDOWS_TOUCH
        ofRemoveListener(ofEvents().touchDown, this, &CustomSlider::touchDown);
        ofRemoveListener(ofEvents().touchMoved, this, &CustomSlider::touchMoved);
        ofRemoveListener(ofEvents().touchUp, this, &CustomSlider::touchUp);
        ofRemoveListener(ofEvents().touchDoubleTap, this, &CustomSlider::touchDoubleTap);
        ofRemoveListener(ofEvents().touchCancelled, this, &CustomSlider::touchCancelled);
#endif
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

//----------------------------------------------------
void CustomSlider::draw(){
	
	ofPushStyle();
	ofEnableAlphaBlending();
	ofDisableSmoothing();
	ofPushMatrix();
	ofTranslate(x,y,0);
	
	// Use different alphas if we're actively maniupulating me. 
	float spineAlpha  = (bHasFocus) ? 192:128;
	
	// draw box outline
	ofNoFill();
	ofSetLineWidth(18.0);
	ofSetColor(25,25,25, 255);
    ofDrawLine(-10, 0, width+10, 0);
	ofDrawLine(-10,height, width+10,height);
    ofSetLineWidth(10.0);
    ofDrawLine(-5, 0, -5, height);
    ofDrawLine(width+5, 0, width+5, height);
	
    red_gradient.draw(0, gradient_perc, 0, 9, width, height - 18);

	// draw thumb
    ofSetCircleResolution(160);
    float thumbX = ofMap(percent, 0,1, 0 + thumb_radius,width - thumb_radius, true);
	ofSetLineWidth(3.0);
	ofSetColor(25, 25, 25, 255);
    ofDrawCircle(thumbX, height/2, 22);
    ofSetColor(255, 26, 34, 255);
    ofFill();
    ofDrawCircle(thumbX, height/2, thumb_radius);
	
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
    percent = ofMap(mx, x + thumb_radius, (x+width) - thumb_radius,  0,1, true);
}

#ifdef WINDOWS_TOUCH
//----------------WINDOWS ONLY
//--------------------------------------------------------------
void CustomSlider::touchDown(ofTouchEventArgs & touch){
    touchMap[touch.id] = touch;
    
    bHasFocus = false;
    if (box.inside(touch.x, touch.y)){
        bHasFocus = true;
        if(isActive){
            updatePercentFromMouse (touch.x, touch.y);
        }
    }
}

//--------------------------------------------------------------
void CustomSlider::touchMoved(ofTouchEventArgs & touch){
    touchMap[touch.id] = touch;
    
    if (bHasFocus){
        if(isActive){
            updatePercentFromMouse (touch.x, touch.y);
        }
    }
}

//--------------------------------------------------------------
void CustomSlider::touchUp(ofTouchEventArgs & touch){
    touchMap.erase(touch.id);
    
    if (bHasFocus){
        if (box.inside(touch.x, touch.y)){
            if(isActive){
                updatePercentFromMouse (touch.x, touch.y);
            }
        }
    }
    bHasFocus = false;
}

//--------------------------------------------------------------
void CustomSlider::touchDoubleTap(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void CustomSlider::touchCancelled(ofTouchEventArgs & touch){
    touchMap.erase(touch.id);
}
#endif
		

