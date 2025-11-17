/* Argument vector parsing */

#ifndef ARGVP_H
#define ARGVP_H

#include <core.h>
#include <err.h>

/* ----- TYPES ----- */

/* Stores data for parsing the command-line argument vector. */
typedef struct STRUCT_ARGVP {

    /* The number of total arguments given (including program name). */
    I16         arg_ct;

    /* The number of positional arguments given. */
    I16         pos_ct;

    /* The raw argument vector. */
    Ch          **arg_vec;

    /* The 'getopt' string used to define how the argument vector will be
    parsed. */
    Ch          *opt_str;
} Argvp;

/* ----- FUNCTIONS ----- */

/* Get the value of an argument option. */
Ch *get_argv_arg(Argvp *argvp, Ch opt);

/* Get the value of a flag option. */
Bool get_argv_flag(Argvp *argvp, Ch opt);

/* Get a positional argument. Throws BOUNDS. */
Ch *get_argv_pos(Argvp *argvp, U16 index, Err *err);

/* Initialize an 'Argvp'. */
Void init_argvp(Argvp *argvp);

/* Test if an option is present in the argument vector. Equivalent to 
'get_argv_pos'. */
Bool is_opt_in_argv(Argvp *argvp, Ch opt);

/* Load an 'Argvp'. Throws ARGV. */
Void ld_argvp(Argvp *argvp, I16 argc, Ch **argv, Ch *optstr, Err *err);

#endif
