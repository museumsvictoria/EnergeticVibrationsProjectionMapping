#include "MaskApp.hpp"

void MaskApp::setup() {
	ofBackground(0);
	masker.setup(DO_NOT_STRETCH);
	mask_pattern = masker.newPattern(1045, 870);
}

void MaskApp::update() {
}

void MaskApp::draw() {
	ofBackground(0);
   masker.update(mouseX, mouseY);
   masker.draw();
}

void MaskApp::keyReleased(int key){
	masker.keyReleased(key);
}

void MaskApp::mouseDragged(int x, int y, int button){
	masker.mouseDragged();
}

void MaskApp::mousePressed(int x, int y, int button) {
	masker.mousePressed();
}

void MaskApp::mouseReleased(int x, int y, int button) {
	masker.mouseReleased();
}