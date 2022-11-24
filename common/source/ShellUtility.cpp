#include "popen_noshell.h"
#include <string.h>
#include <err.h>
#include <stdlib.h>
#include <ctype.h>
#include "ShellUtility.h"


int fast_execute_cmd(const char* szCmd, char *szResult, u_int16_t size)
{
	int status;
	FILE *fp;
	struct popen_noshell_pass_to_pclose pclose_arg;

	if (szCmd==NULL || szResult==NULL || size==0) {
		return -1;
	}

	// the command arguments used by popen_noshell()
	const char *exec_file = "/bin/bash";
	const char *arg1 = "-c";
	const char *endarg = (char *) NULL; // last element, must have
	const char *argv[] = {exec_file, arg1, szCmd, endarg}; // NOTE! The first argv[] must be the executed *exec_file itself

	fp = popen_noshell(exec_file, (const char * const *)argv, "r", &pclose_arg, 0);
	if (!fp) {
		err(EXIT_FAILURE, "popen_noshell_compat()");
	}

	fread(szResult, sizeof(char), size-1, fp);

	status = pclose_noshell(&pclose_arg);
	if (status == -1) {
		err(EXIT_FAILURE, "pclose_noshell()");
	}
	return status;
}

int getprop(const char *prop_name, char *szResult, u_int16_t size)
{
    int result=0;
	const int cmd_size=128;
	char cmd[cmd_size] = {0};

	memset(szResult, 0, size);
    snprintf(cmd,cmd_size,"getprop %s | tr -d '\n'", prop_name);
	result=fast_execute_cmd(cmd,szResult,size);
	//printf("prop[%s]=[%s]\n", prop_name, szResult);
	return result;
}

int safe_atoi(char *s)
{
	int i;

	if (strlen(s) == 0) {
		errx(EXIT_FAILURE, "safe_atoi(): String is empty");
	}

	for (i = 0; i < strlen(s); ++i) {
		if (!isdigit((unsigned char)s[i])) {
			errx(EXIT_FAILURE, "safe_atoi(): Non-numeric characters found in string '%s'", s);
		}
	}

	return atoi(s);
}

int safecall_system(const char* cmd)
{
    int status = system(cmd);
    
    if (status == -1) {
        printf("system(%s): child process fork fail !\n", cmd);
        return -1;
    }
    if (!WIFEXITED(status)) {
        printf("system(%s): child process terminated abnormally !\n", cmd);
        return -1;
    }
    if (WEXITSTATUS(status)) {
        printf("system(%s): child process exit code = %d.\n", cmd, WEXITSTATUS(status));
        return -1;
    }

    return 0;
}
