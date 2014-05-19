#include "testApp.h"

ofEasyCam cam;
bool hideedit;

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetLogLevel("ofxGLEditor", OF_LOG_VERBOSE);
	editor.setup("fonts/DroidSansMono.ttf");
	editor.loadFile("hello.xml");
	ofAddListener(editor.runScriptEvent, this, &testApp::runScriptEvent);
	ofAddListener(editor.saveFileEvent, this, &testApp::saveFileEvent);
        radius =80;

	ofSetSmoothLighting(true);
        pointLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));
        pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
        pointLight.setPointLight();

        spotLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));
        spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
        spotLight.setSpotlight();
        spotLight.setSpotlightCutOff( 50 );
        spotLight.setSpotConcentration( 45 );

        directionalLight.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
        directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
        directionalLight.setDirectional();
        directionalLight.setOrientation( ofVec3f(0, 90, 0) );
        material.setShininess( 120 );
        material.setSpecularColor(ofColor(255, 255, 255, 255));
        ofDisableArbTex();
}

//--------------------------------------------------------------
void testApp::update(){
	pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
                sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
                -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
        spotLight.setOrientation( ofVec3f( 0, cos(ofGetElapsedTimef()) * RAD_TO_DEG, 0) );
        spotLight.setPosition( mouseX, mouseY, 200);
	rules.step();
	editor.reShape();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackgroundGradient(ofColor(144,144,144),ofColor(2,143,255),OF_GRADIENT_CIRCULAR);
	cam.begin();
	ofEnableDepthTest();
	ofEnableLighting();
        material.begin();
        pointLight.enable();
        spotLight.enable();
        directionalLight.enable();
	rules.draw();
        material.end();
        ofDisableLighting();
	ofDisableDepthTest();
	cam.end();
	if(hideedit) editor.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	editor.keyPressed(key);
	bool alt = editor.isAltPressed();
	if(alt && key == 'f'){
		ofToggleFullscreen();
		editor.reShape();
	}
	if(alt && key == 'h'){
		hideedit=!hideedit;
	}
	if(alt && key == 's'){
		editor.saveFile("hello.xml");
		cout<< "* file save *"<<endl;
	}
	if(alt && key == 'd'){
                rules.watchFile("hello.xml");
	}

}
//--------------------------------------------------------------
void testApp::keyReleased(int key){}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	editor.reShape();
}
//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){}

//--------------------------------------------------------------
void testApp::runScriptEvent(int & whichEditor){
	cout << "run script in editor " << whichEditor << endl;
}

//--------------------------------------------------------------
void testApp::saveFileEvent(int & whichEditor){
	cout << "save file from editor " << whichEditor << endl;
	editor.saveFile(ofToString(whichEditor)+".txt", whichEditor, false);
}
