#include <cstdlib>

#include "audio.h"

#include "akinator.h"
#include "colorPrint.h"

static const char *images[]    = {"1.jpg", "2.jpg", "3.jpg", "4.jpg"};
static const size_t imagesSize = sizeof(images) / sizeof(images[0]);

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

void userGreeting(Akinator *akinator) {
  system("ascii-image-converter images/4.jpg -C --braille -d 73,30");
  customPrint(red, bold, bgDefault, "\n%s\n", akinatorLogo);
  customPrint(lightblue, bold, bgDefault, "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
  customPrint(purple, bold, bgDefault, "  I am DED32 - an AI developed by the great Python Senior Dev @lvbealr\n");
  customPrint(lightblue, bold, bgDefault, "▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
  printf("\033[0m");
  customPrint(lightblue, bold, bgDefault, "\n► DO YOU WANNA PLAY? LET'S GO!\n");

  for (size_t iter = 0; iter < 72; iter++) {
    printf(".");
    fflush(stdout);

    if ((iter == 28) || (iter == 47) || (iter == 65)) {
      usleep(250000);
    }

    usleep(10000);
  }

  printf("\n");

  customPrint(green, bold, bgDefault, "Would you play in audio mode? [Y(N)/y(n)]: ");
  scanf("%1s", akinator->audioMode);

  switch (*akinator->audioMode) {
    case 'Y':
    case 'y':
      {
        PLAY_SOUND("audio/ded.wav");
        break;
      }

    default:
      {
        *akinator->userAnswer = 'n';
        break;
      }
  }

  printf("\n");
}

void chooseMode(Akinator *akinator) {
  customPrint(white, bold, bgDefault, "\nChoose gamemode: \n\n");
  customPrint(green, bold, bgDefault, "[G/g] ");
  customPrint(white, bold, bgDefault, "I'll try to guess the character you wished for!\n");
  customPrint(green, bold, bgDefault, "[D/d] ");
  customPrint(white, bold, bgDefault, "I will describe the character you want!\n");
  customPrint(green, bold, bgDefault, "[C/c] ");
  customPrint(white, bold, bgDefault, "You can compare two characters!\n");
  customPrint(green, bold, bgDefault, "[B/b] ");
  customPrint(white, bold, bgDefault, "Show Akinator database!\n");
  customPrint(yellow, bold, bgDefault, "[S/s] ");
  customPrint(white, bold, bgDefault, "Quit the game WITH saving database.\n");
  customPrint(red, bold, bgDefault, "[Q/q] ");
  customPrint(white, bold, bgDefault, "Quit the game WITHOUT saving :(\n\n");

  customPrint(white, underlined, bgDefault, "ENTER:\t");

  scanf("%s", akinator->userAnswer);

  switch (*akinator->userAnswer) {
    case 'G':
    case 'g':
      {
      guessCharacter(akinator);
      chooseMode(akinator);
      break;
      }

    case 'D':
    case 'd':
      {
        describeCharacter(akinator);
        chooseMode(akinator);
        break;
      }

    case 'C':
    case 'c':
      {
        compareCharacters(akinator);
        chooseMode(akinator);
        break;
      }

    case 'B':
    case 'b':
      {
        showBase(akinator);
        chooseMode(akinator);
        break;
      }

    case 'S':
    case 's':
      {
        quitWithSave(akinator);
        chooseMode(akinator);
        break;
      }

    case 'Q':
    case 'q':
      {
        quitWithoutSave(akinator);
        break;
      }

    default:
      {
        customPrint(red, bold, bgDefault, "[ERROR] ");
        customPrint(white, bold, bgDefault, "No such gamemode!\n\n");
        chooseMode(akinator);
        break;
      }
  }
}

void putDed() {
  char *buffer = (char *)calloc(MAX_CMD_BUFFER_SIZE, sizeof(char));
  customWarning(buffer != NULL, (void) 1);

  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "ascii-image-converter images/%s -C --braille -H 20", images[rand() % imagesSize]);
  system(buffer);

  FREE_(buffer);
}