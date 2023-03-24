#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  FILE *fp = fopen(".config/lm/config", "r");
  if (fp == NULL) {
    perror(".config/lm/config");
    return 1;
  }
  char str[150];
  while (fgets(str, 150, fp) != NULL)
    if (strstr(str, *argv) != NULL) {
      fgets(str, 150, fp);
      system(str);
      fclose(fp);
      return 0;
    }
  printf("\"%s\" not found!\n", *argv);
  return 1;
}
