#ifndef H_CARGO_INTERFACE
    #define H_CARGO_INTERFACE

    #include <string.h>
    #include "./validate/cargo_rules.h"
    #include "./cargo_errors.h"

    cargo_errcode
    validate(const int argc, const char **argv, const cargorule* rule);
#endif
