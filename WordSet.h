#ifndef WORDSET_H
#define WORDSET_H

#include <stdlib.h>
#include "Word.h"

typedef struct WordSet
{
  Word *array;
  int _size;
  int _cap;
} WordSet;

void init(WordSet *arr, int cap);
int size(WordSet *arr);
void push(WordSet *arr, Word word);
char *get(WordSet *arr, int index);

#endif