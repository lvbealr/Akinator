#ifndef AKINATOR_H_
#define AKINATOR_H_

#include "binaryTreeExtensions.h"

// static const char *akinatorLogo =   " _____   ______  _____   _____  _   _      _    _______    ____   _____ \n"
//                                     "|  __ / |  ____||  __ / |_   _|| / | |    / /  |__   __| / __ / |  __ / \n"
//                                     "| |  | || |__   | |  | |  | |  |  /| |   / _ /    | |    | |  | || |__) | \n"
//                                     "| |  | ||  __|  | |  | |  | |  | . ` |  / /_/ /   | |    | |  | ||  _  / \n"
//                                     "| |__| || |____ | |__| | _| |_ | |/  | / ____ /   | |    | |__| || | / / \n"
//                                     "|_____/ |______||_____/ |_____||_| /_|/_/    /_/  |_|     /____/ |_|  /_/ \n";

static const char *akinatorLogo =
" _____   ______  _______   ____   _   _           _______   ____   _____ \n"
"|  __ / |  ____||__   __| / __ / | / | |    //   |__   __| / __ / |  __ / \n"
"| |  | || |__      | |   | |  | ||  /| |   /  /     | |   | |  | || |__) | \n"
"| |  | ||  __|     | |   | |  | || . ` |  / // /    | |   | |  | ||  _  / \n"
"| |__| || |____    | |   | |__| || |/  | / ____ /   | |   | |__| || | / / \n"
"|_____/ |______|   |_|    /____/ |_| /_|/_/    /_/  |_|    /____/ |_|  /_/ \n";

const size_t MAX_ANSWER_LENGTH          = 50;
const size_t MAX_DATABASE_BUFFER_LENGTH = 1000;

enum akinatorError {
  AKINATOR_NO_ERRORS        = 0,
  AKINATOR_BAD_POINTER      = 1,
  AKINATOR_TREE_BAD_POINTER = 2,
  BAD_CALLOC_POINTER        = 3,
  BAD_STACK_POINTER         = 4,
  NO_OBJECT_FOUND           = 5,
  AKINATOR_BAD_BUFFER       = 6,
  NO_DB_FILE_FOUND          = 7
};

enum linkType {
  CHARACTER_NODE = 0,
  FEATURE_NODE   = 1
};

struct Akinator {
  binaryTree<char *> *tree                 = {};
  char               *userAnswer           = {};
  char               *audioMode            = {};
};

// FUNCTION PROTOTYPES //
void userGreeting(Akinator *akinator);
void chooseMode  (Akinator *akinator);
void putDed      ();
// FUNCTION PROTOTYPES //

// FUNCTION PROTOTYPES //
akinatorError akinatorInitialize(Akinator *akinator, char *treeRootValue, int argc, char *argv[]);
akinatorError akinatorDestruct  (Akinator *akinator);
akinatorError runAkinator       (Akinator *akinator);

akinatorError guessCharacter    (Akinator *akinator);
akinatorError describeCharacter (Akinator *akinator);
akinatorError compareCharacters (Akinator *akinator);
akinatorError showBase          (Akinator *akinator);
akinatorError quitWithSave      (Akinator *akinator);
akinatorError quitWithoutSave   (Akinator *akinator);
// FUNCTION PROTOTYPES //

#endif // AKINATOR_H_