/*
 *  CustomSlider.h
 *  Created by Golan Levin on 2/24/12.
 *
 */


#pragma once

#include "ofMain.h"
#include "Gradient.h"

class CustomSlider {

	public:
			
		CustomSlider();
		~CustomSlider();

		void	setup (float inx, float iny, float inw, float inh, float loVal, float hiVal, float initialPercent, bool bVert, bool bDrawNum);
		void	clear();

		void	draw();
        void    set_is_active(bool val);
		void	mouseMoved(ofMouseEventArgs& event);
		void	mouseDragged(ofMouseEventArgs& event);
		void	mousePressed(ofMouseEventArgs& event);
		void	mouseReleased(ofMouseEventArgs& event);
	
		float	getValue();
		float	getLowValue();
		float	getHighValue();
		float	getPercent();
		
		void	setLowValue(float lv);
		void	setHighValue(float hv);
		void	setPercent(float p);
		void	setNumberDisplayPrecision(int prec);
		void	setLabelString (string str);
		void	updatePercentFromMouse(int mx, int my); 
		
        //Red Gradient Shader
        Gradient red_gradient;
        void update_gradient_percent(float perc);
        float gradient_perc;
    
		//Touch Events
		int active_touch_idx;

		ofRectangle box;
		bool get_is_active();

	protected:
		
        float   thumb_radius;
		float	x;
		float	y; 
		float	width; 
		float	height;
		int		numberDisplayPrecision;
	
		bool	bVertical;
		bool	bDrawNumber;
		bool	bHasFocus; 
        bool    isActive;
	
		float	lowValue;
		float	highValue;
		float	percent;
	
		string	labelString; 
	
	private:
	
		bool	bWasSetup;
};
