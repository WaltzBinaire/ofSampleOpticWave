#include "testApp.h"

using namespace ofxCv;
using namespace cv;

const int numElements=200;

void testApp::setup() {
	camera.initGrabber(320, 240);	
	ofSetBackgroundAuto(false);
	curFlow = &farneback;
}

void testApp::update(){
	camera.update();

	if(camera.isFrameNew()) {
		curFlow->calcOpticalFlow(camera);
	}
}

void testApp::draw(){
	ofBackground(100);

	ofSetColor(255);


	camera.draw(ofGetWidth()/2-320,ofGetHeight()/2 -240,640,480);
	ofSetColor(255,150);

	curFlow->draw(ofGetWidth()/2-320,ofGetHeight()/2 -240,640,480);

	flowStats.emplace(flowStats.begin(),farneback.getAverageFlow() );
	flowStats.resize(numElements);

	vector<ofVec2f>::iterator it = flowStats.begin();  // create an iterator that points to the first element

	ofPushStyle();
	ofSetLineWidth(4);
	int mult = 5;


	for( int i = 0; i < flowStats.size(); i++){
		int x = i*10;
		ofSetColor(240,130,100);
		ofLine(x,ofGetHeight()-100+flowStats.at(i).y * mult,x,ofGetHeight() -100-flowStats.at(i).y * mult);
		ofSetColor(100,200,100);
		ofLine(x,ofGetHeight()-50+flowStats.at(i).x * mult,x,ofGetHeight() -50-flowStats.at(i).x * mult);

	}

	ofPopStyle();


}