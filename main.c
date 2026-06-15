#include <malloc.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistdio.h>

typedef struct {
  char *get_buff;
  size_t s_get_buff;
} getLineStruct;

getLineStruct *in_get(void);
void show_greet(void);

int main(void) {

  // First Inits
  _Bool is_exit = 0;
  getLineStruct *in_buff;

  // INFO: Main Cycle (Entry Point of Exec)
  while (!is_exit) {
    show_greet();
    in_buff = in_get();
  }
}

getLineStruct *in_get(void) {
  getLineStruct *in_buff = malloc(sizeof(getLineStruct));

  getline(&in_buff->get_buff, &in_buff->s_get_buff, stdin);

  return in_buff;
}

char **tokenize_line(getLineStruct *gls) { // TODO:
  char c = 'a';
  char **arr;
  int a = 0;
  int b = 0;

  // while (c != '\n' && c != '\0') {
  //   if (c == ' ') {
  //     a++;
  //   }
  // }

  for (;;) {
  }

  return arr; // Ret: addr of array of tokens
}

void show_greet(void) { printf("> "); }
