#include "../headers/cargo_interface.h"
#include <cdyar_macros.h>

static cargo_errcode cargo_checkrule(const cargorule *rule) {
  if (!rule) {
    return CARGO_NULL_RULE;
  }

  if (!rule->rulestr) {
    return CARGO_NULL_RULESTR;
  }

  if (!rule->status) {
    return CARGO_NULL_STATUS;
  }

  if (!rule->compiledrule) {
    return CARGO_UNCOMPILED_RULE;
  }

  return CARGO_SUCCESSFUL;
}

static size_t cargo_calcsize_argv(const int argc, const char **argv) {
  size_t total_strsize = 0;
  for (int i = 0; i < argc; i++) {
    total_strsize +=
        strlen(argv[i]); //+1 for null terminator for each string
  }

  return total_strsize + 1;
}

static cargostr cargo_makeargstr(const int argc, const char **argv) {
  const size_t argvarr_size = cargo_calcsize_argv(argc, argv);
  cargostr arr = malloc(sizeof(char) * argvarr_size);
  if (!arr) {
    return NULL;
  }
  arr[argvarr_size - 1] = '\0';

  char* arrptr = arr;
  for(int i = 0; i<argc; i++) {
      //check for null enteries
      if(!argv[i]) {
          free(arr);
          return NULL;
      }

      //cpy str into arr
      //update arr ptr position
      strcpy(arrptr, argv[i]);
      arrptr += strlen(argv[i]);
  }

  return arr;
}

cargo_errcode validate(const int argc, const char **argv,
                       const cargorule *rule) {
  if (argc <= 0) {
    return CARGO_NONPOSITIVE_ARGC;
  }

  if (!(argv && rule)) {
    return CARGO_NULL_INPUT;
  }

  const int checkrule_result = cargo_checkrule(rule);
  if (checkrule_result != CARGO_SUCCESSFUL) {
    return checkrule_result;
  }
}
