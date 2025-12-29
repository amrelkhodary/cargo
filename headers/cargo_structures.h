#ifndef H_CARGO_STRUCTURES
#define H_CARGO_STRUCTURES

// define a simple string type
typedef char *cargostr;

// define a simple boolean type
typedef enum { cargofalse, cargotrue } cargobool;

enum {
    CARGO_DEFER_COMPILATION,
    CARGO_DO_NOT_DEFER_COMPILATION
};

// define a simple flag type
typedef unsigned int cargoflag;
typedef cargoflag cargo_binflags; //added for semantic code clarity
#endif
