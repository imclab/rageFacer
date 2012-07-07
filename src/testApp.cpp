#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    

	rager[0].loadImage("happy-big-smile-l.png");
    rager[1].loadImage("happy-smile-l.png");
    rager[2].loadImage("laughing-lol-crazy-clean-l.png");
    rager[3].loadImage("misc-herp-derp-l.png");
    rager[4].loadImage("misc-me-gusta-l.png");
    rager[5].loadImage("neutral-suspicious-l.png");
    rager[6].loadImage("okay-okay-clean-l copy.png");
    rager[7].loadImage("rage-rage-l.png");
    rager[8].loadImage("sad-forever-alone-face-only-l.png");
    rager[9].loadImage("troll-troll-face-l.png");
    
    for(int i=0;i<10;i++){
        randomFace[i]=ofRandom(10);
    }
    
	finder.setup("haarcascade_frontalface_default.xml");
	//finder.findHaarObjects(img);
    
    camWidth = 640;
    camHeight = 480;
    
    
    vidGrabber.initGrabber(camWidth,camHeight);
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
    
    saveImage=false;
    

    
}

//--------------------------------------------------------------
void testApp::update(){
    bool bNewFrame = false;
    
    vidGrabber.grabFrame();
    bNewFrame = vidGrabber.isFrameNew();
    
    if (bNewFrame){
        colorImg.setFromPixels(vidGrabber.getPixels(), camWidth, camHeight);
        colorImg.resize(320, 240);
        grayImage=colorImg;
        finder.findHaarObjects(grayImage);
    }


}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackgroundGradient(ofColor::black,ofColor::white);
    ofDrawBitmapString("Initializing Camera", (ofGetWidth()/2)-70, ofGetHeight()/2);
    if (vidGrabber.isFrameNew()) { //Only draw if there is a new frame..keeps it from looking weird on startup
        vidGrabber.draw(0,0,ofGetWidth(),.75*ofGetWidth());
    }
	
    ofEnableAlphaBlending();
	ofNoFill();
	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
        rager[randomFace[i%10]].draw(
                                     ofMap(finder.blobs[i].boundingRect.x,0,320,0,ofGetWidth())-40,
                                     ofMap(finder.blobs[i].boundingRect.y,0,240,0,.75*ofGetWidth())-40,
                                     1.5*ofMap(finder.blobs[i].boundingRect.width,0,320,0,ofGetWidth()),
                                     1.5*ofMap(finder.blobs[i].boundingRect.height,0,240,0,.75*ofGetWidth()));
	}
    
    if (saveImage) {
        ofImage picture;
        int randomCounter = ofRandom(4000);
        picture.grabScreen(0,0,ofGetWidth(),ofGetHeight());
        picture.saveImage("ragePic_" + ofToString(randomCounter)+".jpg");
        cout<<"Saved Image: " << "ragePic_" << ofToString(randomCounter)+".jpg" <<endl;
        saveImage=false;
    }
    ofDisableAlphaBlending();
    
    ofDrawBitmapString("Number of faces: " + ofToString(finder.blobs.size()), 30,ofGetHeight()-100);
    ofDrawBitmapString("Click for random faces", 30,ofGetHeight()-80);
    ofDrawBitmapString("Press any key to save Image", 30,ofGetHeight()-60);
    ofDrawBitmapString("Current FPS: " +ofToString(ofGetFrameRate()),30,ofGetHeight()-40);
    

}
//--------------------------------------------------------------
void testApp::newRandomFace(){
    //This just randomizes all of the faces in the array
    for(int i=0;i<10;i++){
        randomFace[i]=ofRandom(10);
    }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    newRandomFace();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    saveImage=true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}