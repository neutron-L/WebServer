/* signal_functions.h

   Header file for signal_functions.c.
*/
#ifndef SIGNAL_FUNCTIONS_H
#define SIGNAL_FUNCTIONS_H

#include <signal.h>

#ifdef _cplusplus
extern "C"
{
#endif
#include "tlsp_hdr.h"

    int printSigMask(FILE *of, const char *msg);

    int printPendingSigs(FILE *of, const char *msg);

    void printSigset(FILE *of, const char *ldr, const sigset_t *mask);

#ifdef _cplusplus
}
#endif
#endif