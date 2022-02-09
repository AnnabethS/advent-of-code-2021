#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>

char isFirst5Zero(char* str);

int main()
{
	unsigned char* test = "abcdef609043";
	unsigned char* ptr = MD5(&test[0], 12, NULL);
	printf("%c\n", ptr);
	/* printf("%d\n", ptr[0]); */
	/* int count = 1; */
	/* unsigned char bufStr[50] = {0}; */
	/* do */
	/* { */
	/* 	printf("\n"); */
	/* 	strcpy(bufStr, ptr); */
	/* 	char cat[20]; */
	/* 	sprintf(cat, "%d", count); */
	/* 	strcat(bufStr, cat); */
	/* 	ptr = MD5(&bufStr[0], strlen(bufStr), NULL); */
	/* } while (!isFirst5Zero(ptr)); */
	/* printf("%d\n", count); */
}

char isFirst5Zero(char* str)
{
	for(int i=0; i < 5; i++)
	{
		printf("%d ", (str[i]));
		if(str[i] != 0)
			return 0;
	}
	return 1;
}
