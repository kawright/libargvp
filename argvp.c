#include "argvp.h"

#include <core.h>
#include <err.h>

#include <getopt.h>


Ch *get_argv_arg(Argvp *argvp, Ch opt) {
    I16 curr_opt    = 0;
    opterr          = 0;
    optind          = 1;
    while ((curr_opt = 
            getopt(argvp->arg_ct, argvp->arg_vec, argvp->opt_str)) != -1) {
        if (curr_opt == opt) {
            if (optarg == 0)
                return NIL;
            return optarg;
        }
    }
    return optarg;
}

Bool get_argv_flag(Argvp *argvp, Ch opt) {
    I16 curr_opt    = 0;
    opterr          = 0;
    optind          = 1;
    while ((curr_opt = 
            getopt(argvp->arg_ct, argvp->arg_vec, argvp->opt_str)) != -1) {
        if (curr_opt == opt)
            return TRUE;
    }
    return FALSE;
}

Ch *get_argv_pos(Argvp *argvp, U16 index, Err *err) {
    if (index >= argvp->pos_ct) {
        THROW(err, ErrCode_BOUNDS, 
            "Out of bounds positional argv access at index %d", index)
        return FALSE;
    }
    opterr          = 0;
    optind          = 1;
    while (getopt(argvp->arg_ct, argvp->arg_vec, argvp->opt_str) != -1) {}
    return argvp->arg_vec[optind + index]; 
}

Void init_argvp(Argvp *argvp) {
    argvp->arg_ct       = 0;
    argvp->pos_ct       = 0;
    argvp->arg_vec      = NIL;
    argvp->opt_str      = NIL;    
}

Bool is_opt_in_argv(Argvp *argvp, Ch opt) {
    return get_argv_flag(argvp, opt);
}

Void ld_argvp(Argvp *argvp, I16 argc, Ch **argv, Ch *optstr, Err *err) {
    I16 curr_opt        = 0;
    opterr              = 0;
    optind              = 1;
    argvp->arg_vec      = argv;
    argvp->arg_ct       = argc;
    argvp->opt_str      = optstr;
    while ((curr_opt = 
            getopt(argvp->arg_ct, argvp->arg_vec, argvp->opt_str)) != -1) {
        if (curr_opt == '?') {
            THROW(err, ErrCode_ARGV, "Invalid option found: %c", curr_opt)
            return;
        }
    }
    argvp->pos_ct       = argc - optind;
}
