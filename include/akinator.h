#ifndef AKINATOR_H_
#define AKINATOR_H_

#include <cstdlib>

#include "binaryTreeExtensions.h"

const size_t MAX_TRASH_BUFFER_SIZE = 100;

#define SCAN_ANSWER(pointer) {                                      \
  char *answer = (char *)calloc(MAX_ANSWER_LENGTH, sizeof(char));   \
                                                                    \
  scanf("%[^\n]", answer);                                          \
  strncpy(pointer, answer, MAX_ANSWER_LENGTH);                      \
                                                                    \
  FREE_(answer);                                                    \
                                                                    \
  CLEAN_BUFFER();                                                   \
}

#define CLEAN_BUFFER() {                           \
  char ch = {};                                    \
  while ((ch = getchar()) != '\n' && ch != EOF) {} \
}

static const char *akinatorLogo =   " _____   ______  _____   _____  _   _      _    _______    ____   _____ \n"
                                    "|  __ / |  ____||  __ / |_   _|| / | |    / /  |__   __| / __ / |  __ / \n"
                                    "| |  | || |__   | |  | |  | |  |  /| |   / _ /    | |    | |  | || |__) | \n"
                                    "| |  | ||  __|  | |  | |  | |  | . ` |  / /_/ /   | |    | |  | ||  _  / \n"
                                    "| |__| || |____ | |__| | _| |_ | |/  | / ____ /   | |    | |__| || | / / \n"
                                    "|_____/ |______||_____/ |_____||_| /_|/_/    /_/  |_|     /____/ |_|  /_/ \n";

const size_t MAX_ANSWER_LENGTH          = 50;
const size_t MAX_DATABASE_BUFFER_LENGTH = 1000;

enum akinatorError {
  AKINATOR_NO_ERRORS        =  0,
  AKINATOR_BAD_POINTER      =  1,
  AKINATOR_TREE_BAD_POINTER =  2,
  BAD_CALLOC_POINTER        =  3,
  BAD_STACK_POINTER         =  4,
  NO_OBJECT_FOUND           =  5,
  AKINATOR_BAD_BUFFER       =  6,
  NO_DB_FILE_FOUND          =  7,
  BAD_DATABASE_POINTER      =  8,
  NO_DATA_MORE              =  9,
  DOUBLE_ROOT_INITIALIZE    = 10,
  BAD_NODE_INITIALIZE       = 11
};

enum linkType {
  CHARACTER_NODE = 0,
  FEATURE_NODE   = 1
};

enum linkDirection {
  LEFT  = 'n',
  RIGHT = 'y'
};

struct DB {
  char  *dataBaseBuffer = {};
};

struct Akinator {
  binaryTree<char *> *tree                 = {};
  char               *userAnswer           = {};
  char               *audioMode            = {};
  DB                 *dataBase             = {};
  const char        **phrases              = {};
};

// FUNCTION PROTOTYPES //
void userGreeting(Akinator *akinator);
void chooseMode  (Akinator *akinator);
void putDed      ();
// FUNCTION PROTOTYPES //

// FUNCTION PROTOTYPES //
akinatorError   akinatorInitialize(Akinator *akinator, char *treeRootValue, int argc, char *argv[]);
akinatorError   akinatorDestruct  (Akinator *akinator);
akinatorError   runAkinator       (Akinator *akinator);

akinatorError   guessCharacter    (Akinator *akinator);
akinatorError   describeCharacter (Akinator *akinator);
akinatorError   compareCharacters (Akinator *akinator);
akinatorError   showBase          (Akinator *akinator);
akinatorError   quitWithSave      (Akinator *akinator);
akinatorError   quitWithoutSave   (Akinator *akinator);

akinatorError   readDataBaseInfo  (Akinator *akinator);
akinatorError   readDataBase      (Akinator *akinator);

binaryTreeError printDataBase     (node<char *> *node, FILE *dbOut);
void            printTabs         (int tabCount,       FILE *dbOut);
// FUNCTION PROTOTYPES //

#endif // AKINATOR_H_