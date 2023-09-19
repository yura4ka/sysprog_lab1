#include <stdio.h>
#include <ctype.h>
#include "WordSet.h"
#include "Word.h"
#include <string.h>

const char VOWELS[] = "euioa";
const int MAX_SIZE = 30;

int parseFile(FILE *file, WordSet *arr)
{
  char word[MAX_SIZE + 1];
  int wordLen = 0;
  int vowelsCount = 0;

  while (1)
  {
    char c = fgetc(file);
    if (!isalpha(c) && wordLen != 0)
    {
      Word w = {malloc(wordLen + 1), wordLen, vowelsCount};
      memset(w.word, '\0', wordLen + 1);
      memcpy(w.word, word, wordLen);
      push(arr, w);
      wordLen = 0;
      vowelsCount = 0;
    }

    if (feof(file))
      break;

    if (!isalpha(c))
      continue;

    if (wordLen == MAX_SIZE)
      return 1;

    word[wordLen++] = c;
    if (strchr(VOWELS, tolower(c)) != NULL)
      vowelsCount++;
  }

  return 0;
}

int comparator(const void *a, const void *b)
{
  Word *wa = (Word *)a;
  Word *wb = (Word *)b;

  float ca = 1.0 * wa->vowels / wa->size;
  float cb = 1.0 * wb->vowels / wb->size;

  if (ca < cb)
    return -1;
  if (ca > cb)
    return 1;
  return 0;
}

int main()
{
  FILE *file = fopen("text.txt", "r");
  WordSet arr;
  init(&arr, 0);

  if (file == NULL)
  {
    printf("File not found!\n");
    return 0;
  }

  int err = parseFile(file, &arr);
  fclose(file);

  if (err)
  {
    printf("Error! Word more than %d symbols!", MAX_SIZE);
    return 0;
  }

  qsort(arr.array, size(&arr), sizeof(Word), comparator);
  for (int i = 0; i < size(&arr); i++)
    printf("%s\n", get(&arr, i));

  return 0;
}