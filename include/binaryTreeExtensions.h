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

static binaryTreeError printBinaryTree(node<const char *> *node) {
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