#include <iostream>
#include <SFML/Audio.hpp>
#include <cmath>
const float PI = 3.141592653589793238463;

using namespace sf;
using namespace std;

//기능 구현: 소리 위치 시각적으로/최소 거리 및 Attenuation 조절
//보완: 소리가 평면적임, 추가적인 library 확인해서 더 만들 것

int main()
{
	Listener::setPosition(0.0f, 0.0f, 0.0f);
	Listener::setDirection(0.f, 0.0f, -1.0f);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("mono.wav");

	sf::Sound sound;
	sound.setBuffer(buffer);
	//sound.setLoop(true);
	sound.setMinDistance(8.0f);		//최소거리 조절
	sound.setAttenuation(1.0f);		//Attenuation 조사
	sound.play();

	sf::Vector3f pos;
	float radius = 10.0f;
	float t = 0;
	float angular_velocity = 2 * PI / 4.0f;	//각속도 조절할 것

	sf::Clock clock;

	while (true)
	{
		sf::Time dt = clock.restart();

		t += dt.asSeconds() * angular_velocity;

		pos.x = radius * std::cos(t);
		pos.y = 0.f;
		pos.z = radius * std::sin(t);
		
		sound.setPosition(pos);
	}

	sound.stop();
}