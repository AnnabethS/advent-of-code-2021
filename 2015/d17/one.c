#include <stdio.h>

int input[] = {11, 30, 47, 31, 32, 36, 3, 1, 5, 3, 32, 36,
	15, 11, 46, 26, 28, 1, 19, 3};

int main()
{
	return 0;
}

int getCombos(char remainingMap[20], int currentTotal)
{
	if(currentTotal > 150)
		return 0;
	else if (currentTotal == 150)
		return 1;
	
}
