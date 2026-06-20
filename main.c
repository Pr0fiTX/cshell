#include <malloc.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistdio.h>

typedef struct {
  char *get_buff;
  size_t s_get_buff;
} getLineStruct;

void in_get(getLineStruct *gls);
void show_greet(void);

int main(void) {

  // First Inits
  _Bool is_exit = 0;
  getLineStruct in_buff = {.get_buff = NULL, .s_get_buff = 0};
  char *tokens[128];

  // INFO: Main Cycle (Entry Point of Exec)
  while (!is_exit) {
    show_greet();
    in_get(&in_buff);

    free(in_buff.get_buff);
  }

  return 0;
}

void tokenizer(getLineStruct *gls, char **tok) {
  int i = 0;

  for (int a = 0;; a++) {
  }
}

void in_get(getLineStruct *gls) {
  getline(&gls->get_buff, &gls->s_get_buff, stdin);
}

void show_greet(void) { printf("> "); }
