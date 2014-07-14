#ifndef __ANARCH_X64_STDDEF_H__
#define __ANARCH_X64_STDDEF_H__

#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif

typedef unsigned long int size_t;
typedef long int ssize_t;

#endif
