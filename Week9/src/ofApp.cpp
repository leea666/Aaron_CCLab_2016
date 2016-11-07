#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0,0,0) ;
    ofSetBackgroundAuto(false) ;
    ofSetCircleResolution(50) ;
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)) ;
    ofFill() ;
    ofDrawBitmapStringHighlight("Press 'a' to draw circles! and Mouse Press to clear the background!", ofGetWindowWidth()/2 - 250, ofGetWindowHeight()/2) ;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a') {
       ofDrawCircle(ofRandom(0, ofGetWindowWidth()), ofRandom(0, ofGetWindowHeight()), ofRandom(0, 50));
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
    ofBackground(0,0,0) ;
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
