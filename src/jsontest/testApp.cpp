#include "testApp.h"

static string readfile(string path) {
	string str,strTotal;
	ifstream in;
	in.open(ofToDataPath(path, true).c_str());
	getline(in,str);
	while ( in ) {
		strTotal += str;
		getline(in, str);
	}
	in.close();
	return strTotal;
}

//--------------------------------------------------------------
void testApp::setup(){
	bool success;
	
	// http://dev.twitter.com/console
    success = twitter.openLocal("/Users/luisbrandao/Documents/metaLAB/code/revere-small/zeega_project.json");
	if (success)
	{
        /*
        Json::ValueIterator it;
        Json::Value layers = twitter["layers"];
        
        for(it = layers.begin(); it != layers.end(); ++it)
        {
            //Json::Value item = (*it)["attr"];
            cout << (*it)[0u]["type"].asString() << endl;
        }
        */
 /*
        for(int i = 0u; i != twitter["layers"].size(); ++i)
        {
            Json::Value currLayer = twitter["layers"][i];
            string text = twitter["layers"][i]["text"].asString();
            int zindex = twitter["layers"][i]["zindex"].asInt();
            
            string localURL = twitter["layers"][i]["args"]["localurl"].asString();
            string originalURL = twitter["layers"][i]["args"]["url"].asString();
            string mediaType = twitter["layers"][i]["type"].asString();
            
            item it = item(1, originalURL, localURL, mediaType);
        }
        string type = twitter["layers"][0u]["type"].asString();
        int id = twitter["layers"][1u]["attr"]["item_id"].asInt();
		cout << id << endl;
        
        //cout << twitter["layers"]. << endl;
        //cout << typeid(twitter["layers"]).name() << endl;
          */  
	}
}

//--------------------------------------------------------------
void testApp::update(){

	
	
}

//--------------------------------------------------------------
void testApp::draw(){

	}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
	}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

    