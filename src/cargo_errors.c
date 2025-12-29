#include "../headers/cargo_errors.h"

cargostr cargo_errmessages[CARGO_ERR_CODE_COUNT] = {
    "cargo: successful", "cargo: failed",
    "cargo: memory error",
    "cargo: NULL FILE* pointer",
    "cargo: NULL rule string."};

cargo_errcode cargo_printerr(cargo_errcode code, FILE* dest) {
    if(!dest) {
        return CARGO_NULL_FILE;
    }

    fprintf(dest, "%s\n", cargo_errmessages[code]);
    return CARGO_SUCCESSFUL;
}

cargo_errcode cargo_printstatus(cargostatus *status, FILE *dest) {
  if (!dest) {
    return CARGO_NULL_FILE;
  }

  fprintf(dest, "at line %u, in %s, in %s:\n\t\t%s\n", status->linenum,
          status->funcname, status->filename, cargo_errmessages[status->code]);
  return CARGO_SUCCESSFUL;
}
