#include "getopt.h"

#include "consoleParser.h"
#include "binaryTree.h"

int main(int argc, char *argv[]) {
  binaryTree<int> intTree = {};
  INIT_BINARY_TREE(&intTree, 100);

  binaryTreeNodeCreate(&intTree, 200);
  binaryTreeNodeCreate(&intTree, 12);
  binaryTreeNodeCreate(&intTree, 1488);
  binaryTreeNodeCreate(&intTree, 228);
  binaryTreeNodeCreate(&intTree, 50);
  binaryTreeNodeCreate(&intTree, 37);
  binaryTreeNodeCreate(&intTree, 98);
  binaryTreeNodeCreate(&intTree, 1002);
  binaryTreeNodeCreate(&intTree, 1323);
  binaryTreeNodeCreate(&intTree, 11);
  binaryTreeNodeCreate(&intTree, 2);

  binaryTreeDestruct(&intTree);
}