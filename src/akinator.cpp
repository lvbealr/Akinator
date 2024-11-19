#include <cstring>
#include <cassert>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "binaryTree.h"
#include "consoleParser.h"
#include "akinator.h"
#include "colorPrint.h"
#include "stack.h"

akinatorError akinatorInitialize(Akinator *akinator, char *treeRootValue, int argc, char *argv[]) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  akinator->tree = (binaryTree<char *> *)calloc(1, sizeof(binaryTree<char *>));
  customWarning(akinator->tree != NULL, BAD_CALLOC_POINTER);

  akinator->userAnswer = (char *)calloc(MAX_ANSWER_LENGTH, sizeof(char));
  customWarning(akinator->userAnswer != NULL, BAD_CALLOC_POINTER);

  akinator->audioMode  = (char *)calloc(MAX_ANSWER_LENGTH, sizeof(char));
  customWarning(akinator->audioMode  != NULL, BAD_CALLOC_POINTER);

  INIT_BINARY_TREE(akinator->tree, treeRootValue);

  return AKINATOR_NO_ERRORS;
}

akinatorError akinatorDestruct(Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  binaryTreeDestruct(akinator->tree);
  FREE_(akinator->tree);

  return AKINATOR_NO_ERRORS;
}

akinatorError runAkinator(Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  userGreeting(akinator);
  chooseMode(akinator);

  return AKINATOR_NO_ERRORS;
}

node<char *> *akinatorInitNode(char *value) {
  if (value == NULL) {
    return NULL;
  }

  node<char *> *initNode = (node<char *> *)calloc(1, sizeof(node<char *>));
  if (!initNode) {
    return NULL;
  }

  initNode->data         = (char *)calloc(MAX_ANSWER_LENGTH, sizeof(char));
  if (!initNode->data) {
    return NULL;
  }

  if (!strcpy(initNode->data, value)) {
    return NULL;
  }

  return initNode;
}

binaryTreeError akinatorLinkNode(Akinator *akinator, node<char *> **parentNode, node <char *> **newNode, linkType nodeType) {
  assert       (akinator    != NULL);
  customWarning(*parentNode != NULL, NODE_BAD_POINTER);
  customWarning(*newNode    != NULL, NODE_BAD_POINTER);

  switch (nodeType) {
    case FEATURE_NODE:
      {
        if ((*parentNode)->parent) {
          if ((*parentNode) == (*parentNode)->parent->right) {
            (*parentNode)->parent->right = *newNode;
          }

          else {
            (*parentNode)->parent->left = *newNode;
          }
        }

        (*newNode)->parent    = (*parentNode)->parent;
        (*newNode)->left      =           *parentNode;
        (*newNode)->right     =                  NULL;

        (*parentNode)->parent = *newNode;
        (*parentNode)->left   =     NULL;
        (*parentNode)->right  =     NULL;

        if ((*parentNode) == akinator->tree->root) {
          akinator->tree->root = *newNode;
        }

        break;
      }

    case CHARACTER_NODE: {
      (*parentNode)->right = *newNode;

      (*newNode)->parent   = *parentNode;
      (*newNode)->left     =        NULL;
      (*newNode)->right    =        NULL;

      break;
    }
  }

  return NO_ERRORS;
}

binaryTreeError switchNode(Akinator *akinator, node<char *> *currentNode) {
  assert       (akinator    != NULL);
  customWarning(currentNode != NULL, NODE_BAD_POINTER);

  customPrint(white, bold, bgDefault, "It ");
  customPrint(lightblue, bold, bgDefault, "%s? ", currentNode->data);
  printf("Your answer [Y(y)/N(n)]: ");

  scanf("%s", akinator->userAnswer);

  if (currentNode->right && currentNode->left) {
    switch (*akinator->userAnswer) {
      case 'Y':
      case 'y':
        {
          currentNode = currentNode->right;
          switchNode(akinator, currentNode);
          break;
        }

      case 'N':
      case 'n':
        {
          currentNode = currentNode->left;
          switchNode(akinator, currentNode);
          break;
        }
    }
  }

  else {
    switch(*akinator->userAnswer) {
      case 'Y':
      case 'y':
        {
          customPrint(green, bold, bgDefault, "[SUCCESS]!\n");
          break;
        }

      case 'N':
      case 'n':
        {
          customPrint(white, bold, bgDefault, "I can't guess. What did you wish for?\n");
          scanf("%s", akinator->userAnswer);
          size_t len = 0;
          node<char *> *character = akinatorInitNode(akinator->userAnswer);

          customPrint(white, bold, bgDefault, "What's the difference between %s and %s?\n", character->data, currentNode->data);
          scanf("%s", akinator->userAnswer);

          node<char *> *feature = akinatorInitNode(akinator->userAnswer);

          akinatorLinkNode(akinator, &currentNode, &feature,   FEATURE_NODE  );
          akinatorLinkNode(akinator, &feature,     &character, CHARACTER_NODE);

          DUMP_(akinator->tree);

          break;
        }
    }
  }

  return NO_ERRORS;
}

akinatorError guessCharacter(Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  switchNode(akinator, akinator->tree->root);

  return AKINATOR_NO_ERRORS;
}

Stack *fillCharacterStack (Akinator *akinator) {
  assert(akinator != NULL);

  Stack *personality = (Stack *)calloc(1, sizeof(Stack));
  assert(personality != NULL);

  stackInitialize(personality, 10);

  node<char *> *foundNode     = binaryTreeFindNode(akinator->tree->root, akinator->userAnswer);

  if (foundNode == NULL) {
    return NULL;
  }

  node<char *> *foundNodeCopy = foundNode;

  node<char *> *movePtr       = foundNode->parent;

  stackPush(personality, foundNode);

  while (movePtr) {
    stackPush(personality, movePtr);

    foundNode = movePtr;
    movePtr   = movePtr->parent;
  }

  return personality;
}

akinatorError describeCharacter(Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  customPrint(white, bold, bgDefault, "Whose description do you want to receive? ");
  scanf("%s", akinator->userAnswer);

  Stack *descriptionStack = fillCharacterStack(akinator);
  customWarning(descriptionStack != NULL, NO_OBJECT_FOUND);

  node<char *> *popNode     = {};
  stackPop(descriptionStack, &popNode);
  node<char *> *popNodeCopy = popNode;

  if (!(descriptionStack->data[0])) {
    customPrint(red, bold, bgDefault, "This object has no description!\n");
    return BAD_STACK_POINTER;
  }

  customPrint(lightblue, bold, bgDefault, "%s - ", (descriptionStack->data[0])->data);

  while (descriptionStack->size) {
    stackPop(descriptionStack, &popNode);

    if (popNode == popNodeCopy->right) {
      printf("%s ", popNodeCopy->data);
    }

    else {
      printf("not %s ", popNodeCopy->data);
    }

    popNodeCopy = popNode;
  }

  printf("\n");

  stackDestruct(descriptionStack);
  FREE_(descriptionStack);

  return AKINATOR_NO_ERRORS;
}

akinatorError compareCharacters(Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  customPrint(white, bold, bgDefault, "Enter the names of the objects you want to compare!\n");

  printf("First object: ");
  scanf("%s", akinator->userAnswer);
  Stack *firstCharacter  = fillCharacterStack(akinator);
  customWarning(firstCharacter != NULL, NO_OBJECT_FOUND);

  printf("Second object: ");
  scanf("%s", akinator->userAnswer);
  Stack *secondCharacter = fillCharacterStack(akinator);
  customWarning(secondCharacter != NULL, NO_OBJECT_FOUND);

  char *firstName  = firstCharacter->data[0]->data;
  char *secondName = secondCharacter->data[0]->data;

  node<char *> *firstNode  = {};
  node<char *> *secondNode = {};

  // TODO

  return AKINATOR_NO_ERRORS;
}

akinatorError showBase          (Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  SAVE_DUMP_IMAGE(akinator->tree);
  char *buffer = (char *)calloc(MAX_CMD_BUFFER_SIZE, sizeof(char));
  customWarning(buffer != NULL, AKINATOR_BAD_BUFFER);

  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "xdg-open %s", akinator->tree->infoData->htmlDumpPath);
  system(buffer);

  FREE_(buffer);

  return AKINATOR_NO_ERRORS;
}

akinatorError saveDataBase (Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  FILE *dbOut = fopen(akinator->tree->infoData->dataBasePath, "w");
  customWarning(dbOut != NULL, NO_DB_FILE_FOUND);

  printDataBase(akinator->tree->root, dbOut);

  customPrint(white, bold, bgDefault, "Saving database... OK! (%s)", akinator->tree->infoData->dataBasePath);

  fclose(dbOut);

  return AKINATOR_NO_ERRORS;
}

akinatorError quitWithSave      (Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  saveDataBase(akinator);

  return AKINATOR_NO_ERRORS;
}

akinatorError quitWithoutSave   (Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  customPrint(purple, bold, bgDefault, "\nByye! 👋\n");

  return AKINATOR_NO_ERRORS;
}