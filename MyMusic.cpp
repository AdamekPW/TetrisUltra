#include "MyMusic.h"

MyMusic::MyMusic() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, SongNumber-1);
	CurrentSong = distribution(generator);
	for (int i = 1; i <= SongNumber; i++) {
		std::stringstream ss;
		ss << "Music/Music" << i << ".mp3";
		std::string fileName = ss.str();
		std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
		if (!music->openFromFile(fileName)) {
			std::cout << "Blad wczytania pliku: " << fileName << "\n";
		}
		else {
			SoundTrack.push_back(std::move(music));
		}
	}
	//PlayNextSong();
}


void MyMusic::PlayNextSong() {
	CurrentSong++;
	if (CurrentSong > SongNumber - 1) CurrentSong = 0;
	this->SoundTrack[CurrentSong]->play();
}

void MyMusic::IsSongFinished() {
	if (!(this->SoundTrack[CurrentSong]->getStatus() == sf::Music::Playing)) {
		PlayNextSong();
	}
}

void MyMusic::SetVolume(int Volume) {
	for (int i = 0; i < SoundTrack.size(); i++) {
		SoundTrack[i]->setVolume(Volume);
	}
}