#include "../../headers/validate/cargo_rules.h"
#include <regex.h>

void cargo_compile(cargorule *rule) {
  rule->compiledrule = malloc(sizeof(regex_t));
  if (!rule->compiledrule) {
    cargo_assignstatus(rule->status, CARGO_MEMORY_ERROR, __FILE__, __func__,
                       __LINE__);
    return;
  }


  int result = regcomp(rule->compiledrule, rule->rulestr, REG_EXTENDED);
  if (result != 0) {
    free(rule->compiledrule);
    rule->compiledrule = NULL;
  }
}

cargorule *cargo_newrule(cargostr rulestr, cargoflag defer_compilation) {
  if (!rulestr) {
    return NULL;
  }

  cargorule *nrule = malloc(sizeof(cargorule));
  if (!nrule) {
    return NULL;
  }

  cargostatus *nstatus = malloc(sizeof(cargostatus));
  if (!nstatus) {
    free(nrule);
    return NULL;
  }

  nrule->rulestr = rulestr;
  nrule->status = nstatus;
  if (defer_compilation == CARGO_DO_NOT_DEFER_COMPILATION) {
    cargo_compile(nrule);
    if (nrule->status->code != CARGO_SUCCESSFUL) {
      free(nstatus);
      free(nrule);
      return NULL;
    }
  } else {
    nrule->compiledrule = NULL;
  }

  return nrule;
}

cargo_errcode
cargo_deleterule(cargorule* ruleptr) {
   if(!ruleptr) {
       return CARGO_NULL_RULE;
   }

   free(ruleptr -> status);
   if(ruleptr -> compiledrule) {
       regfree(ruleptr->compiledrule);
       free(ruleptr->compiledrule);
   }

   free(ruleptr);
   return CARGO_SUCCESSFUL;
}
