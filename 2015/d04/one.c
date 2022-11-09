#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>

char isFirst5Zero(unsigned char* str);
void generateHash(unsigned char* str, int num, unsigned char* output);

int main()
{
	unsigned char* test = "ckczppom";
	unsigned char outputString[64] = {0};
	int num = 0;
	char found = 0;
	while(!found)
	{
		num++;
		memset(&outputString[0], 0, sizeof(unsigned char)*64);
		generateHash(test, num, &outputString[0]);
		found = isFirst5Zero(outputString);
		if(num == 609043)
		{
			printf("---\n");
			for(int i=0; i < 64; i++)
			{
				char str[2] = {0};
				sprintf(str, "%c", outputString[i]);
			}
			printf("\n");
		}
	}
	/* generateHash(test, num, &outputString[0]); */
	printf("required_num: %d\n", num);
}

void generateHash(unsigned char* str, int num, unsigned char* output)
{
	char numString[10] = {0};
	sprintf(numString, "%d", num);
	unsigned char inputString[20] = {0};
	strcpy((char*)inputString, (char*)str);
	strcat((char*)inputString, numString);
	unsigned char outputString[17] = {0};
	MD5(&inputString[0], strlen((char*)inputString), &outputString[0]);
	unsigned char hexString[33] = {0};
	for(int i=0; i < 16; i++)
	{
		unsigned char value = outputString[i];
		char hex[3] = {0};
		sprintf(hex, "%02x", value);
		strcat((char*) hexString, hex);
	}
	strcpy((char*)output, (char*)hexString);
	return;
}
	
char isFirst5Zero(unsigned char* str)
{
	for(int i=0; i < 5; i++)
	{
		if((str[i] - '0') != 0)
		{
			return 0;
		}
	}
	return 1;
}
