#ifndef __PLUGIN_H_INCLUDED__
#define __PLUGIN_H_INCLUDED__


#include <sys/stat.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include "conf.h"


__BEGIN_DECLS


#define FILMOND_DECLINED    0
#define FILMOND_DONE        -1
#define FILMOND_ERROR       -2


#define ACTION_ADD_OR_MOD   'a'
#define ACTION_DEL          'd'


extern __attribute__((weak)) char *g_hostname; /* defined in filmond.c */


/*
 * All hooks are optional, and only return value listed above.
 *
 *  FILMOND_DECLINED:   continue process following plugin.
 *  FILMOND_DONE:       stop process following plugin.
 *  FILMOND_ERROR:      directly return, stop processing following plugin.
 * 
 */
int plugin_init(conf_t *conf);
int plugin_file_ftw(char *filepath, const struct stat *st);
int plugin_file_event(int action, char *filepath, const struct stat *st);
int plugin_deinit(conf_t *conf);
int plugin_ftw_post();


/* Add interp section just for geek.
 * This partion of code can be remove to Makefile 
 * to determine RTLD(runtime loader). */
#if __WORDSIZE == 64
#define RUNTIME_LINKER  "/lib64/ld-linux-x86-64.so.2"
#else
#define RUNTIME_LINKER  "/lib/ld-linux.so.2"
#endif

#ifndef __SO_INTERP__
#define __SO_INTERP__
const char __invoke_dynamic_linker__[] __attribute__ ((section (".interp")))
    = RUNTIME_LINKER;
#endif /* __SO_INTERP__ */


__END_DECLS


#endif /* __PLUGIN_H_INCLUDED__ */