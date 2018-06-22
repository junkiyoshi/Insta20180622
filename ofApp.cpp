#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	ofNoFill();
	ofSetColor(39);
	ofSetLineWidth(2);

	this->font_size = 100;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(20, this->font_size + 20);

	vector<char> charactors = { 'A', 'B', 'C', 'D', 'E', 'F',
								'G', 'H', 'I', 'J', 'K', 'L',
								'M', 'N', 'O', 'P', 'Q', 'R',
								'S', 'T', 'U', 'V', 'W', 'X',
								'Y', 'Z', '!'};
	int sample_count = 180;
	for (int charactor_index = 0; charactor_index < charactors.size(); charactor_index++) {

		ofPath path = this->font.getCharacterAsPoints(charactors[charactor_index], true, false);
		vector<ofPolyline> outline = path.getOutline();

		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
			vector<glm::vec3> vertices = outline[outline_index].getVertices();

			ofBeginShape();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				ofPoint point(vertices[vertices_index].x, vertices[vertices_index].y, vertices[vertices_index].z);

				if (ofGetFrameNum() % (sample_count * 2) < sample_count) {

					if (vertices_index < ofGetFrameNum() % sample_count) { 
						
						ofVertex(point); 
					}
				}
				else {

					if (vertices_index > ofGetFrameNum() % sample_count) { 
						
						ofVertex(point); 
					}
				}

				if (vertices_index == ofGetFrameNum() % sample_count) { 
					
					ofDrawCircle(point, 3); 
				}

			}
			ofEndShape();
		}

		if ((charactor_index + 1) % 6 == 0) {

			ofTranslate(this->font_size * -6, this->font_size * 1.4);
		}
		else {

			ofTranslate(this->font_size * 1.2, 0);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}