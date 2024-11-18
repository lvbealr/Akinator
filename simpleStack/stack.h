#include "customWarning.h"
#include "binaryTree.h"

#define FREE_(field) { \
  free(field);         \
  field = NULL;        \
}

struct Stack {
  int    capacity        = {};
  int    size            = {};
  node<char*> **data     = {};
};

enum stackError {
  STACK_NO_ERROR     = 0,
  BAD_CAPACITY       = 1,
  BAD_SIZE           = 2,
  BAD_DATA_POINTER   = 3,
  BAD_POP_POINTER    = 4,
  STACK_NULL_POINTER = 5
};

enum changeMemory {
  DUMP_MEMORY = -1,
  ADD_MEMORY  =  1
};

stackError stackInitialize (Stack *stack, int            capacity   );
stackError stackDestruct   (Stack *stack                            );
stackError stackPush       (Stack *stack, node<char *>  *data       );
stackError stackPop        (Stack *stack, node<char *> **dataPointer);
stackError stackResize     (Stack *stack, changeMemory   mode       );
