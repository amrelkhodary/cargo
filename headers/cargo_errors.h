#ifndef H_CARGO_ERRORS
#define H_CARGO_ERRORS
#define CARGO_ERR_CODE_COUNT 8 // number of recognized err codes

#include "./cargo_structures.h" //for cargostr
#include <stdio.h>              //for FILE*

typedef enum {
  CARGO_SUCCESSFUL,
  CARGO_FAILED, // generic failed code, use only when abs. necessary
  CARGO_MEMORY_ERROR,
  CARGO_NULL_FILE, // passed null to a func not expecting null
  CARGO_NULL_RULESTR,
  CARGO_NULL_STATUS,
  CARGO_NULL_STR,
  CARGO_NULL_RULE,
} cargo_errcode;

typedef struct {
  cargo_errcode code;
  cargostr filename;    // file where error occured
  cargostr funcname;    // function where error occured
  unsigned int linenum; // line where error occured
} cargostatus;

extern cargostr cargo_errmessages[CARGO_ERR_CODE_COUNT];

cargo_errcode cargo_printerr(cargo_errcode code, FILE *dest);
cargo_errcode cargo_printstatus(cargostatus *status, FILE *dest);
cargo_errcode cargo_assignstatus(cargostatus *status, const cargo_errcode code,
                                 const cargostr filename,
                                 const char funcname[14],
                                 const unsigned int linenum);
#endif
