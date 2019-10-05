#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
#include <chrono>
#include <vector>
#include <thread>

#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod_studio.h>
#include <RoomProperties.h>

#include <Windows.h>
#include "goprint.h"
#define PI 3.141592653589793238463

const int INTERFACE_UPDATETIME = 50;
const float DISTANCEFACTOR = 1.0f;

using namespace std;
using namespace std::chrono_literals;
using namespace FMOD;
using namespace vraudio;

int main(int argc, char *argv[])
{

	RemoveCursor();
	print_boundary();
	FMOD_RESULT result;

	System *system = nullptr;
	// Create the main system object.
	result = System_Create(&system);

	// Initialize FMOD.
	//result = system->setOutput(FMOD_OUTPUTTYPE_WAVWRITER);	//audio output
	result = system->init(512, FMOD_INIT_NORMAL, nullptr);
	result = system->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);

	//The most traditional way to approach spatialization is by panning signal into virtual speakers, 
	//so with the introduction of 7.1.4 (7 horizontal plane speakers, 1 sub-woofer, 4 roof speakers)
	result = system->setSoftwareFormat(0, FMOD_SPEAKERMODE_7POINT1POINT4, 0);

	// Create the sound.
	Sound *sound = nullptr;
	result = system->createSound("mono.wav", FMOD_3D, nullptr, &sound);
	result = sound->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 30.0f*DISTANCEFACTOR);

	// Play the sound.
	Channel *channel = nullptr;
	result = system->playSound(sound, nullptr, false, &channel);
	channel->setVolume(20);

	//sound initial
	FMOD_VECTOR pos = { 0.0f, 0.0f, 5.0f };

	//3D effect
	FMOD::Reverb3D *reverb;
	result = system->createReverb3D(&reverb);
	FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_BATHROOM;
	reverb->setProperties(&prop2);
	float mindist = 0.5f;
	float maxdist = 30.0f;
	reverb->set3DAttributes(&pos, mindist, maxdist);


	// Position the listener at the origin
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };
	FMOD_VECTOR listenerpos = { 0.0f, 0.0f, -7.0f * DISTANCEFACTOR };
	result = system->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);

	float radius = 5.0f;
	float t = PI / 2.0;
	float angular_velocity = 2.5 * PI/ 4.0;

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	bool isPlaying = false;
	do {
		chrono::duration<float> dt = 1ms;
		t += dt.count() * angular_velocity;

		pos.x = radius * cos(t);
		pos.y = 1.0f;
		pos.z = radius * sin(t);
		channel->set3DAttributes(&pos, &vel);

		channel->isPlaying(&isPlaying);

		//오류: 꼭 위치를 출력해야 정상적으로 작동, 
		//UI 함수 따로 파서 좌표 위치값만 갱신되게끔 만들기.

		go_to_xy(3, 3);
		cout << "x_pos:" << pos.x << " " << "z_pos:" << pos.z << endl;

		system->update();

	} while (isPlaying);

	go_to_xy(7, 5);
	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	std::cout << sec.count() << " seconds" << std::endl;
	
	// Clean up.
	sound->release();
	system->release();

	return 0;
}