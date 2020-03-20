#include <stdio.h>
void main()
{
	printf("======code 002=====\n");
	int iValue;
	float fValue;
	char strValue[20];
	char cValue1, cvalue2;
	printf("\n 정수 혹은 실수를 2개 입력하시오");
	scanf_s("%d %f", &iValue, &fValue);

	printf("\n 문자열을 입력하십시오 : ");
	scanf_s("%s", strValue);

	printf("\n iValue = %d", iValue);
	printf("\n fValue = %f", fValue);
	printf("\n strValue = %s", strValue);

	//char c;
	//while ((c == getchar()) != '\n' && c != EOF);

	printf("\n 문자 1을 입력하십시오 : ");
	scanf_s("%c", &cValue1);
	printf("\n strvalue = %s, %c ", strValue, cValue1);
}