#include "WordSet.h"
#include "Word.h"
#include <string.h>

void init(WordSet *arr, int cap)
{
  if (cap <= 0)
    cap = 1;
  arr->_cap = cap;
  arr->_size = 0;
  arr->array = (Word *)malloc(cap * sizeof(Word));
}

int size(WordSet *arr)
{
  return arr->_size;
}

void push(WordSet *arr, Word element)
{
  for (int i = 0; i < arr->_size; i++)
  {
    Word w = arr->array[i];
    if (w.size != element.size)
      continue;

    if (strcmp(w.word, element.word) == 0)
      return;
  }

  if (arr->_size == arr->_cap)
  {
    arr->_cap *= 2;
    arr->array = realloc(arr->array, arr->_cap * sizeof(Word));
  }
  arr->array[arr->_size++] = element;
}

char *get(WordSet *arr, int index)
{
  return arr->array[index].word;
}
