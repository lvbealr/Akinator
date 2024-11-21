#include "consoleParser.h"
#include "akinator.h"

int main(int argc, char *argv[]) {
  Akinator akinator = {};
  akinatorInitialize(&akinator, (char *)"Bebra228", argc, argv);

  runAkinator(&akinator);

  akinatorDestruct(&akinator);

  return 0;
}