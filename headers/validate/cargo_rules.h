#ifndef H_CARGO_RULES
    #define H_CARGO_RULES

    #include <regex.h> //for regex operations
    #include <stdlib.h> //for malloc inside func implementations
    #include "../cargo_structures.h" //for cargostr
    #include "../cargo_errors.h" //for cargostatus, cargo_errocde

    typedef struct {
        cargostr rulestr;
        regex_t compiledrule;
        cargostatus* status;
    } cargorule;

    cargorule* cargo_newrule(cargostr rulestr, cargo_binflags flags);
    cargo_errcode cargo_deleterule(cargorule* ruleptr, cargoflag isOnHeap);
    void cargo_compile(cargorule* rule);
#endif
