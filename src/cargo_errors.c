#include "../headers/cargo_errors.h"

cargostr cargo_errmessages[CARGO_ERR_CODE_COUNT] = {
    "cargo: successful",       "cargo: failed",
    "cargo: memory error",     "cargo: NULL FILE* pointer",
    "cargo: NULL rule string", "cargo: NULL status",
    "cargo: NULL string", "cargo: NULL rule", "cargo: argc is smaller than or equal to zero",
    "cargo: NULL input", "cargo: uncompiled rule"};

cargo_errcode cargo_printerr(cargo_errcode code, FILE *dest) {
  if (!dest) {
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

cargo_errcode cargo_assignstatus(cargostatus *status, const cargo_errcode code,
                                 const cargostr filename,
                                 const char funcname[14],
                                 const unsigned int linenum) {
  if (!status) {
    return CARGO_NULL_STATUS;
  }

  if (!(filename && funcname)) {
    return CARGO_NULL_STR;
  }

  status->code = code;
  status->filename = filename;
  status->funcname = funcname;
  status->linenum = linenum;
  return CARGO_SUCCESSFUL;
}
