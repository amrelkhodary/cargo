#include "../../headers/validate/cargo_rules.h"

void cargo_compile(cargorule *rule) {}

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
  }

  return nrule;
}
