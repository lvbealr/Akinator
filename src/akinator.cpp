#include "binaryTree.h"
#include "consoleParser.h"
#include "akinator.h"
#include "colorPrint.h"

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
  // TODO check
  node<char *> *initNode = (node<char *> *)calloc(1, sizeof(node<char *>));
  initNode->data         = (char *)calloc(MAX_ANSWER_LENGTH, sizeof(char));

  strcpy(initNode->data, value);
  // TODO check

  return initNode;
}

binaryTreeError akinatorLinkNode(Akinator *akinator, node<char *> **parentNode, node <char *> **newNode, linkType nodeType) {
  // TODO check
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
  // TODO check
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

akinatorError describeCharacter(Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  customPrint(white, bold, bgDefault, "Whose description do you want to receive? ");
  scanf("%s", akinator->userAnswer);

  node<char *> *foundNode = binaryTreeFindNode(akinator->tree->root, akinator->userAnswer);

  customPrint(lightblue, bold, bgDefault, "%s - ", foundNode->data);

  node<char *> *movePtr    = foundNode->parent;

  while (movePtr) {
    if (foundNode == movePtr->right) {
      printf("%s ", movePtr->data);
    }

    else {
      printf("not %s ", movePtr->data);
    }

    movePtr = movePtr->parent;
  }

  printf("\n\n");

  return AKINATOR_NO_ERRORS;
}

akinatorError compareCharacters(Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  return AKINATOR_NO_ERRORS;
}

akinatorError showBase          (Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  SAVE_DUMP_IMAGE(akinator->tree);
  char *buffer = (char *)calloc(MAX_CMD_BUFFER_SIZE, sizeof(char)); // TODO CHECK
  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "xdg-open %s", akinator->tree->infoData->htmlDumpPath);
  system(buffer);

  FREE_(buffer);

  return AKINATOR_NO_ERRORS;
}

akinatorError quitWithSave      (Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  return AKINATOR_NO_ERRORS;
}

akinatorError quitWithoutSave   (Akinator *akinator) {
  customWarning(akinator != NULL, AKINATOR_BAD_POINTER);

  customPrint(purple, bold, bgDefault, "\nByye! 👋\n");

  return AKINATOR_NO_ERRORS;
}