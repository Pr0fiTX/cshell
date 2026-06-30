#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// INFO: Struct with all user-input data from 'getline()'
typedef struct {
  char *get_buff;    // String from User
  size_t s_get_buff; // Size of the Buffer
  long get_str_len;  // Lenght of the String
} getLineStruct;

long in_get(getLineStruct *gls);
void show_greet(int code);
char **tokenizer(getLineStruct *gls, int *tok_count);
int cs_exec(char **args);
int parse_return_info(int ret_status);

int main(void) {
  // INFO: Some Vars
  _Bool is_exit = 0;
  getLineStruct in_buff = {.get_buff = NULL, .s_get_buff = 0, .get_str_len = 0};
  int tok_count = 0;
  char **tok_arr = NULL;
  int ret_value = 0;
  int i_count = 0;

  // INFO: Main Loop (Entry Point of Exec)
  while (!is_exit) {
    // INFO: Prep for next iteration
    tok_count = 0;

    // INFO: Show greet message
    if (i_count == 0) {
      printf("> ");
    } else {
      show_greet(parse_return_info(ret_value));
    }

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

    // INFO: Skip iteration if empty input
    if (tok_arr[0] == NULL) {
      free(tok_arr);
      continue;
    }

    // INFO: Exit handling
    if (strcmp("exit", tok_arr[0]) == 0) {
      printf("=> Exiting...");
      free(tok_arr);
      free(in_buff.get_buff);
      return 0;
    }

    // INFO: Exec if not CShell command
    ret_value = cs_exec(tok_arr);

    // INFO: Clear Tok array for the next cycle
    free(tok_arr);

    i_count++;
  }

  // INFO: Exit point
  free(in_buff.get_buff);
  return 0;
}

int parse_return_info(int ret_status) {
  if (WIFEXITED(ret_status)) {
    return WEXITSTATUS(ret_status);
  } else {
    return -1;
  }
}

int cs_exec(char **args) {
  int ret_status = 0;

  pid_t pid = fork();
  if (pid == 0) {
    execvp(args[0], args);

    fprintf(stderr, "!> Programm not found!\n");

    exit(127);
  } else {
    wait(&ret_status);
  }

  return ret_status;
}

char **tokenizer(getLineStruct *gls, int *tok_count) {
  char **tok_arr = NULL;    // Array of parsed tokens
  int tok_arr_capacity = 2; // Capacity of 'tok_arr'
  char **tmp = NULL;        // Temp pointer for 'realloc()'

  // INFO: Changing all '\n' & ' ' -> '\0'
  for (int i = 0; i < gls->get_str_len; i++) {
    if (gls->get_buff[i] == ' ' || gls->get_buff[i] == '\n') {
      gls->get_buff[i] = '\0';
    }
  }

  // INFO: Allocating mem for array of tokens
  tok_arr = malloc(tok_arr_capacity * sizeof(char *));
  if (tok_arr == NULL) {
    return NULL;
  }

  // INFO: Parse Loop
  for (int i = 0; i < gls->get_str_len; i++) {
    // INFO: Expanding 'tok_arr'
    if (*tok_count == tok_arr_capacity) {
      tok_arr_capacity *= 2;
      tmp = realloc(tok_arr, tok_arr_capacity * sizeof(char *));
      if (tmp == NULL) {
        free(tok_arr);
        return NULL;
      }
      tok_arr = tmp;
    }

    // INFO: Actual parse loop
    if (gls->get_buff[i] != '\0' && i == 0) {
      tok_arr[*tok_count] = &gls->get_buff[i];
      *tok_count += 1;
    } else if (gls->get_buff[i] != '\0' && gls->get_buff[i - 1] == '\0') {
      tok_arr[*tok_count] = &gls->get_buff[i];
      *tok_count += 1;
    }
  }

  // INFO: Expanding 'tok_arr' for NULL if needed
  if (*tok_count == tok_arr_capacity) {
    tok_arr_capacity++;
    tmp = realloc(tok_arr, tok_arr_capacity * sizeof(char *));
    if (tmp == NULL) {
      free(tok_arr);
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

void show_greet(int code) { printf("[%d]> ", code); }
