#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <chrono>
#include <vector>
#include<Windows.h>
#include<conio.h>
#include "goprint.h"
#include <SFML/Audio.hpp>


#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod_studio.h>
#include <RoomProperties.h>

#define PI 3.141592653589793238463
#define DISTANCE 5.0f

const int INTERFACE_UPDATETIME = 50;
const float DISTANCEFACTOR = 1.0f;
using namespace sf;
using namespace std;
using namespace std::chrono_literals;
using namespace FMOD;
using namespace vraudio;

int main(int argc, char *argv[])
{
	RemoveCursor();
	print_boundary();
	print_effect();

	char input[200] = "";
	FMOD_RESULT result;
	go_to_xy(5, 1);
	printf("파일 명을 입력해주세요");
	Sleep(1500);
	go_to_xy(5, 1);
	printf("                      ");
	go_to_xy(5, 1);
	System *system = nullptr;


	//파일이름 및 필터 입력 
	scanf("%s", input);
	go_to_xy(5, 1);
	printf("재생 모드를 입력해주세요");
	int nKey = _getch();
	printf("                         ");

	go_to_xy(5, 1);
	printf("음원파일을 재생중입니다..");

	//시스템 생성
	// Create the main system object.
	result = System_Create(&system);

	// Initialize FMOD.
	result = system->setOutput(FMOD_OUTPUTTYPE_WAVWRITER);	//audio output
	//result 변수에 시스템 초기화 및 3D 세팅
	result = system->init(512, FMOD_INIT_NORMAL, nullptr);
	result = system->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);

	//The most traditional way to approach spatialization is by panning signal into virtual speakers, 
	//so with the introduction of 7.1.4 (7 horizontal plane speakers, 1 sub-woofer, 4 roof speakers)
	result = system->setSoftwareFormat(16000, FMOD_SPEAKERMODE_7POINT1POINT4, 0);


	// Create the sound.
	FMOD::Sound *sound = nullptr;

	result = system->createSound(input, FMOD_3D, nullptr, &sound);
	//일정 거리 이상 되는 소리 X 
	result = sound->set3DMinMaxDistance(0.0f * DISTANCEFACTOR, DISTANCE * DISTANCEFACTOR + 5.0f);	// 멀어지는 데 영향이 있음
	//result = sound->setMode(FMOD_LOOP_NORMAL);
	sound->setMode(FMOD_3D_LINEARROLLOFF);

	// Play the sound.
	Channel *channel = nullptr;
	result = system->playSound(sound, nullptr, false, &channel);
	channel->setVolume(5);	// (5) 볼륨을 높이면 ouput.wav에서 소리가 이상해짐

	//sound initial
	FMOD_VECTOR pos = { 0.0f, 0.0f, DISTANCE };

	//3D effect
	FMOD::Reverb3D *reverb;
	result = system->createReverb3D(&reverb);

	FMOD_REVERB_PROPERTIES prop1 = FMOD_PRESET_ROOM;
	FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_CAVE;
	FMOD_REVERB_PROPERTIES prop3 = FMOD_PRESET_BATHROOM;
	FMOD_REVERB_PROPERTIES prop4 = FMOD_PRESET_CONCERTHALL;
	FMOD_REVERB_PROPERTIES prop5 = FMOD_PRESET_OFF;

	switch (nKey) {
	case '1':
		reverb->setProperties(&prop1);
		break;
	case '2':
		reverb->setProperties(&prop2);
		break;
	case '3':
		reverb->setProperties(&prop3);
		break;
	case '4':
		reverb->setProperties(&prop4);
		break;
	case '5':
		reverb->setProperties(&prop5);
		break;
	}

	float mindist = 0.01f;
	float maxdist = DISTANCE * 2.0f;
	reverb->set3DAttributes(&pos, mindist, maxdist);


	// Position the listener at the origin
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	//forward -> 소리 방향 (z가 양의 방향) 
	FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };
	FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };
	FMOD_VECTOR listenerpos = { 0.0f, 0.0f, -DISTANCE * DISTANCEFACTOR };
	result = system->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);

	float radius = DISTANCE;
	//t 초기값 -> 오차 보정 
	float t = PI / 2.0;
	//각속도 > 오류 누적 > 임의로 보정 
	//원래 t와 동일한데 느리게 재생돼서 일부러 딜레이 맞추려고 조절함. 
	//float angular_velocity = 2.5 * PI/ 4.0;
	float angular_velocity = 2.0 *PI / 4.0;
	sf::Clock clock;
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	bool isPlaying = false;
	do {
		sf::Time dt = clock.restart();
		//chrono::duration<float> dt = 1ms;
		//dt- > 1ms 
		//t += dt.count() * angular_velocity;
		t += dt.asSeconds() * angular_velocity;

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