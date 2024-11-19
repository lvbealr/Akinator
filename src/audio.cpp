#include "audio.h"

void playMusic(char *pathToSound)
{
    sf::Music music;
    music.openFromFile(pathToSound);
    music.play();
    sleep(2);
}