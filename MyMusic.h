#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>
#include <random>

class MyMusic
{
private:
	int SongNumber = 6;
	int Volume = 100;
public:
	int CurrentSong;
	std::vector<std::unique_ptr<sf::Music>> SoundTrack;
	MyMusic();
	void PlayNextSong();
	void IsSongFinished();
	void SetVolume(int Volume);
};

