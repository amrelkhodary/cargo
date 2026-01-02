#include "../headers/cargo_interface.h"
#include <cdyar_macros.h>

static
cargo_errcode
cargo_checkrule(const cargorule* rule) {
   if(!rule) {
       return CARGO_NULL_RULE;
   }

   if(!rule->rulestr) {
       return CARGO_NULL_RULESTR;
   }

   if(!rule->status) {
       return CARGO_NULL_STATUS;
   }

   if(!rule->compiledrule) {
       return CARGO_UNCOMPILED_RULE;
   }

   return CARGO_SUCCESSFUL;
}

static
size_t cargo_calcsize_argv(const int argc, const char** argv) {
    if(argc <= 0) {
        return CARGO_NONPOSITIVE_ARGC;
    }

    if(!argv) {
        return CARGO_NULL_INPUT;
    }

    size_t total_strsize = 0;
    for(int i = 0; i<argc; i++) {
        if(!argv[i]) {
            return CARGO_NULL_INPUT;
        }

        total_strsize += strlen(argv[i]) + 1; //+1 for null terminator for each string
    }

    return total_strsize;
}


static
cargo_errcode
cargo_makeargstr(const int argc, const char** argv) {

}

cargo_errcode
validate(const int argc, const char** argv, const cargorule* rule) {
  if(argc <= 0) {
     return CARGO_NONPOSITIVE_ARGC;
  }

  if(!(argv && rule)) {
      return CARGO_NULL_INPUT;
  }

  const int checkrule_result = cargo_checkrule(rule);
  if(checkrule_result != CARGO_SUCCESSFUL) {
      return checkrule_result;
  }


}
