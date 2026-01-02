#include "../headers/cargo_interface.h"

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
