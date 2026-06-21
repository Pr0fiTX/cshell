#include <malloc.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistdio.h>

// INFO: Struct with all user-input data from 'getline()'
typedef struct {
  char *get_buff;    // String from User
  size_t s_get_buff; // Size of the Buffer
  long get_str_len;  // Lenght of the String
} getLineStruct;

long in_get(getLineStruct *gls);
void show_greet(void);
char **tokenizer(getLineStruct *gls, int *tok_count);

int main(void) {
  // INFO: Some Vars
  _Bool is_exit = 0;
  getLineStruct in_buff = {.get_buff = NULL, .s_get_buff = 0, .get_str_len = 0};
  int tok_count = 0;
  char **tok_arr = NULL;

  // INFO: Main Loop (Entry Point of Exec)
  while (!is_exit) {
    tok_count = 0;

    // INFO: Show greet message
    show_greet();

    // INFO: Reading user input
    in_buff.get_str_len = in_get(&in_buff);
    if (in_buff.get_str_len == -1) {
      fprintf(stderr, "!> EOF. Exiting...\n");
      free(in_buff.get_buff);
      return 1;
    }

    // INFO: Parse user input to Arr of tokens
    tok_arr = tokenizer(&in_buff, &tok_count);
    if (tok_arr == NULL) {
      return 1;
    }

    // WARN: Debug Output
    for (int i = 0; i < tok_count; i++) {
      printf("%d> %s\n", i, tok_arr[i]);
    }

    free(tok_arr);
  }

  free(in_buff.get_buff);
  return 0;
}

char **tokenizer(getLineStruct *gls, int *tok_count) {
  char **tok_arr = NULL;
  int tok_arr_capacity = 2;
  char **tmp = NULL;

  for (int i = 0; i < gls->get_str_len; i++) {
    if (gls->get_buff[i] == ' ' || gls->get_buff[i] == '\n') {
      gls->get_buff[i] = '\0';
    }
  }

  tok_arr = malloc(tok_arr_capacity * sizeof(char *));
  if (tok_arr == NULL) {
    return NULL;
  }

  for (int i = 0; i < gls->get_str_len; i++) {
    if (*tok_count == tok_arr_capacity) {
      tok_arr_capacity *= 2;
      tmp = realloc(tok_arr, tok_arr_capacity * sizeof(char *));
      if (tmp == NULL) {
        return NULL;
      }
      tok_arr = tmp;
    }

    if (gls->get_buff[i] != '\0' && i == 0) {
      tok_arr[*tok_count] = &gls->get_buff[i];
      *tok_count += 1;
    } else if (gls->get_buff[i] != '\0' && gls->get_buff[i - 1] == '\0') {
      tok_arr[*tok_count] = &gls->get_buff[i];
      *tok_count += 1;
    }
  }

  if (*tok_count == tok_arr_capacity) {
    tok_arr_capacity++;
    tmp = realloc(tok_arr, tok_arr_capacity * sizeof(char *));
    if (tmp == NULL) {
      return NULL;
    }
    tok_arr = tmp;
  }
  tok_arr[*tok_count] = NULL;

  return tok_arr;
}

long in_get(getLineStruct *gls) {
  return getline(&gls->get_buff, &gls->s_get_buff, stdin);
}

void show_greet(void) { printf("> "); }
