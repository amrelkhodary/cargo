#ifndef H_CARGO_RULES
#define H_CARGO_RULES

#include "../cargo_errors.h"     //for cargostatus, cargo_errocde
#include "../cargo_structures.h" //for cargostr
#include <regex.h>               //for regex operations
#include <stdlib.h>              //for malloc inside func implementations

typedef struct {
  cargostr rulestr;
  regex_t *compiledrule;
  cargostatus *status;
} cargorule;

cargorule *cargo_newrule(cargostr rulestr, cargoflag defer_compilation);
cargo_errcode cargo_deleterule(cargorule *ruleptr);
void cargo_compile(cargorule *rule);
#endif
