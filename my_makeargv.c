#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//~ #define DEBUG

int my_makeargv(const char *s, const char *delimiter, char ***argvp)
{
	const char *snew;
	char *t;
	int numtokens;
	int i;
	int error;
	 
	#ifdef DEBUG
		printf("enter makearg\n");
	#endif
	
	//判断输入是否合法
	if(s == NULL || delimiter == NULL || **argvp == NULL)
	{
		errno = EINVAL;   //invalid argument
		return -1;
	}
	
	*argvp = NULL;  
	snew = s + strspn(s, delimiter);
	
	#ifdef DEBUG
		printf("snew:%s\n", snew);
	#endif
	
	//因为t不是snew指向一个字符串串中的地址，t是指向一个新数据的地址，所以需要为t分配空间
	if((t = malloc(strlen(snew) + 1)) == NULL)
	{
		return -1;
	}
	
	numtokens = 0;
	strcpy(t, snew);
	
	#ifdef DEBUG
		printf("t:%s\n", t);
	#endif
	
	if(strtok(t, delimiter) != NULL)
		for(numtokens = 1;strtok(NULL, delimiter) != NULL;numtokens++);
	
	#ifdef DEBUG	
		printf("numtokens:%d\n", numtokens);
	#endif
	
	if((*argvp = malloc((numtokens + 1) * sizeof(char *) )) == NULL)
	{
		error = errno;
		free(t);
		errno = error;
		return -1;
	}

	strcpy(t, snew);
	**argvp = strtok(t, delimiter);
	for(i = 1; i < numtokens; i++)
	{
		//~ *(*argvp + i) = strtok(NULL, delimiter);
		(*argvp)[i] = strtok(NULL, delimiter);
	}
	
	 *((*argvp) + numtokens) = NULL;
	return numtokens;		
}
  
