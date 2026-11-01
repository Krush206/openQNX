/*
 * dl_stubs.c - dlopen/dlsym/dlclose placeholders.
 *
 * The dynamic-loader interface implementation is not part of the
 * openQNX sources (it lives in the proprietary ldqnx.so.2).  These
 * stubs keep libc.so.3 loadable: the symbols resolve at load time and
 * the functions fail gracefully (dlopen/dlsym -> NULL, dlclose -> -1)
 * instead of leaving unresolved imports.
 */

#include <stddef.h>

/* Head of the loaded-objects list; the real loader maintains it. */
void *_dll_list;

void *dlopen(const char *pathname, int mode)
{
    (void) pathname;
    (void) mode;
    return 0;
}

void *dlsym(void *handle, const char *name)
{
    (void) handle;
    (void) name;
    return 0;
}

int dlclose(void *handle)
{
    (void) handle;
    return -1;
}
