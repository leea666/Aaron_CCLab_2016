#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0) ;
    mGravity = ofVec2f(0.f, 0.02f) ;
    
    gui.setup() ;
    gui.add(sliderForceX.setup("ForceX", 0, -2.f, 2.f)) ;
    gui.add(sliderForceY.setup("ForceY", 0, -2.f, 2.f)) ;
    gui.add(mRed.setup("Red", 255, 0, 255)) ;
    gui.add(mGreen.setup("Green", 255, 0, 255)) ;
    gui.add(mBlue.setup("Blue", 255, 0, 255)) ;
//    gui.add(addRotation.setup("Rotation", false)) ;
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0 ; i < mSystems.size() ; i++) {
        mSystems[i].update() ;
    }
//    sliderForce = ofMap(sliderForce, 1, 300, 0.f, 0.02f) ;
    force = ofVec2f(sliderForceX, sliderForceY) ;
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0 ; i < mSystems.size() ; i++) {
        mSystems[i].draw() ;
    }
    
    
    gui.draw() ;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a') {
        ParticleSystem system(ofVec2f(ofGetWindowWidth()/2,ofGetWindowHeight()/2), force, mRed, mGreen, mBlue) ;
        mSystems.push_back(system) ;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
