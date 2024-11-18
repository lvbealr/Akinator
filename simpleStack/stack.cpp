#include <cstdlib>

#include "stack.h"

stackError stackInitialize (Stack *stack, int capacity) {
  customWarning(stack    != NULL, STACK_NULL_POINTER);
  customWarning(capacity >= 0,    BAD_CAPACITY      );

  stack->size     = 0;
  stack->capacity = capacity;
  stack->data     = (node<char *> **)calloc(capacity, sizeof(node<char *> *));

  customWarning(stack->data != NULL, BAD_DATA_POINTER);

  return STACK_NO_ERROR;
}

stackError stackDestruct   (Stack *stack) {
  customWarning(stack != NULL, STACK_NULL_POINTER);

  stack->size     = -1;
  stack->capacity = -1;

  FREE_(stack->data);

  return STACK_NO_ERROR;
}

stackError stackPush       (Stack *stack, node<char *> *data) {
  customWarning(stack != NULL, STACK_NULL_POINTER);
  customWarning(data  != NULL, BAD_DATA_POINTER  );

  if (stack->size >= stack->capacity) {
    stackResize(stack, ADD_MEMORY);
  }

  stack->data[stack->size++] = data;
  return STACK_NO_ERROR;
}

stackError stackPop        (Stack *stack, node<char *> **dataPointer) {
  customWarning(stack          != NULL, STACK_NULL_POINTER);
  customWarning(dataPointer    != NULL, BAD_DATA_POINTER  );
  customWarning(stack->size    >     0, BAD_SIZE          );

  if (stack->size <= stack->capacity / 4) {
    stackResize(stack, DUMP_MEMORY);
  }

  (*dataPointer)           = stack->data[--stack->size];
  stack->data[stack->size] = NULL;

  return STACK_NO_ERROR;
}

stackError stackResize(Stack *stack, changeMemory mode) {
  customWarning(stack != NULL, STACK_NULL_POINTER);

  switch (mode) {
    case ADD_MEMORY:
      {
        int newCapacity = stack->capacity * 2;

        stack->data = (node<char *> **)realloc(stack->data, sizeof(node<char *> *) * (size_t)newCapacity);
        customWarning(stack->data != NULL, BAD_DATA_POINTER);

        stack->capacity *= 2;
      }

    case DUMP_MEMORY:
      {
        int newCapacity = stack->capacity / 2;

        stack->data = (node<char *> **)realloc(stack->data, sizeof(node<char *> *) * (size_t)newCapacity);
        customWarning(stack->data != NULL, BAD_DATA_POINTER);

        stack->capacity /= 2;
      }
  }

  return STACK_NO_ERROR;
}