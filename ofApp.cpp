#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);

	for (int i = 0; i < 3; i++) {

		this->noise_seed_list.push_back(glm::vec2(ofRandom(1000), ofRandom(1000)));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	int index = 0;
	for (auto& noise_seed : this->noise_seed_list) {

		auto deg = ofGetFrameNum() * 2 + index * 120;
		auto next_deg = deg + 2;

		auto location = glm::vec2(250 * cos(deg * DEG_TO_RAD), 250 * sin(deg * DEG_TO_RAD));
		auto next = glm::vec2(250 * cos(next_deg * DEG_TO_RAD), 250 * sin(next_deg * DEG_TO_RAD));

		auto distance = location - next;
		distance *= 1;

		for (int i = 0; i < 2; i++) {

			auto future = location + distance * 8;
			auto random_deg = ofRandom(360);
			future += glm::vec2(30 * cos(random_deg * DEG_TO_RAD), 30 * sin(random_deg * DEG_TO_RAD));
			auto future_distance = future - location;

			this->location_list.push_back(location);
			this->velocity_list.push_back(glm::normalize(future_distance) * glm::length(distance));
		}

		index++;
	}

	for (int i = this->location_list.size() - 1; i > -1; i--) {

		this->location_list[i] += this->velocity_list[i];
		this->velocity_list[i] *= 1.01;

		if (glm::distance(glm::vec2(), this->location_list[i]) > 720) {

			this->location_list.erase(this->location_list.begin() + i);
			this->velocity_list.erase(this->velocity_list.begin() + i);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (auto& location : this->location_list) {

	
		for (auto& other : this->location_list) {

			if (location == other) continue;

			if (glm::distance(location, other) < 50) {

				ofDrawLine(location, other);
			}
		}
	}

	for (auto& location : this->location_list) {

		ofFill();
		ofSetColor(0);
		ofDrawCircle(location, 5);

		ofNoFill();
		ofSetColor(255);
		ofDrawCircle(location, 5);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}