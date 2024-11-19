#include <SFML/Audio.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PLAY_SOUND(pathToSound) { \
  pid_t pid;                      \
  int rv;                         \
  switch(pid = fork()) {          \
    case 0:                       \
      {                           \
        playMusic(pathToSound);   \
        exit(rv);                 \
        break;                    \
      }                           \
                                  \
    default:                      \
      {                           \
        break;                    \
      }                           \
  }                               \
}

void playMusic(char *pathToSound);