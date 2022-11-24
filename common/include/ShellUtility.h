
#ifndef SHELL_UTILITY_H
#define SHELL_UTILITY_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif

int fast_execute_cmd(const char* szCmd, char *szResult, u_int16_t size);
int getprop(const char* prop_name, char *szResult, u_int16_t size);
int safe_atoi(char *s);
int safecall_system(const char* cmd);

#ifdef __cplusplus
}
#endif


#endif //SHELL_UTILITY_H

