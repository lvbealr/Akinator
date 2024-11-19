#include "binaryTree.h"

static int compareNodes(node<char *> *firstNode, node<char *> *secondNode){
  return strcmp(firstNode->data, secondNode->data);
}

static node<char *> *binaryTreeFindNode(node<char *> *currentNode, char *value) {
  customWarning(currentNode != NULL, NULL);

  static node<char *> *ptrToNode = NULL;

  if (strcmp(currentNode->data, value) == 0) {
    ptrToNode = currentNode;
    return ptrToNode;
  }

  if (currentNode->left) {
    binaryTreeFindNode(currentNode->left, value);
  }

  if (currentNode->right) {
    binaryTreeFindNode(currentNode->right, value);
  }

  return ptrToNode;
}

static void printTabs(int tabCount, FILE *dbOut) {
  for (int count = 0; count < tabCount; count++) {
    fprintf(dbOut, "\t");
  }
}

static binaryTreeError printDataBase(node<char *> *node, FILE *dbOut) {
  customWarning(node != NULL, NODE_BAD_POINTER);


  static int tabCount = 0;
  printTabs(tabCount, dbOut);

  fprintf(dbOut, "{");

  if ((node->parent) && (node == node->parent->right)) {
    fprintf(dbOut, "'%s'", node->data);
  }

  else if ((node->parent) && (node == node->parent->left)) {
    fprintf(dbOut, "'%s'", node->data);
  }

  else {
    fprintf(dbOut, "'%s'", node->data);
  }

  if (node->left) {
    tabCount++;
    fprintf(dbOut, "\n");
    printDataBase(node->left, dbOut);
  }

  if (node->right) {
    tabCount++;
    fprintf(dbOut, "\n");
    printDataBase(node->right, dbOut);
  }

  tabCount--;

  fprintf(dbOut, "}\n");

  printTabs(tabCount, dbOut);

  return NO_ERRORS;
}

static binaryTreeError printBinaryTree(node<char *> *node) {
  customWarning(node != NULL, NODE_BAD_POINTER);

  printf("(");

  if (node->left) {
    printBinaryTree(node->left);
  }

  printf(" %s ", node->data);

  if (node->right) {
    printBinaryTree(node->right);
  }

  printf(")");

  return NO_ERRORS;
}