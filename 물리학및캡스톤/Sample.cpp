#define _CRT_SECURE_NO_WARNINGS
#define CPLUSPLUS
//#undef CPLUSPLUS

#ifndef CPLUSPLUS	
	#include <stdio.h>	// printf
	#include <stdlib.h> // malloc, free
	#include <conio.h>	//_getche();	
	void main()
	{
		// 포인터 변수 할당, 기본 void* 에서 int*로 형변환				//malloc : 동적메모리 할당 - 메모리 어디선가 malloc(n) n만큼의 메모리가 연속으로 존재한다면 해당 시작 메모리를 pointer에 저장
		printf("\n=====================\n");
		int *pPoint = (int*)malloc(sizeof(int));						//pointer 다른 주소값을 저장하기보다는, "
		*pPoint = 100;
		printf("%0x번지 : %d\n", pPoint + 0, *(pPoint + 0));
		free(pPoint);
		// 포인터 변수 배열 할당
		printf("\n=====================\n");
		int *pPointArray = (int*)malloc(sizeof(int) * 10);
		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			pPointArray[iCnt] = iCnt * 10;
			printf("\n0x%08x번지 : %d", &pPointArray[iCnt], *(pPointArray + iCnt));
		}
		free(pPointArray);
		// 문자형 포인터 변수 배열 할당
		printf("\n=====================\n");
		char* pCharPoint = 0;
		int iCount = 0;
		pCharPoint = (char*)malloc(sizeof(char) * 100);
		// 멀티바이트에서 _getche()==0이라는 것은 확장키가 입력되었다는 것이다. 
		// 방향키 또는 home, end,insert등은 0x00E0을 반환한다.
		do {
			int ivalue = _getch(); //_getche();
			if (ivalue != 0 && ivalue != 0x00E0)
			{
				pCharPoint[iCount++] = ivalue;
				printf("*"); // password
			}

		} while (pCharPoint[iCount - 1] != '\r');

		// 알파벳 또는 숫자키를 입력시 확장키코드(널문자 추가)로 반환하는 
		// 문제가 시스템에 따라 발생한다.
		/*do {
				pCharPoint[iCount++] = _getche();
		} while (pCharPoint[iCount - 1] != '\r');*/

		// \n, \r  
		pCharPoint[iCount - 1] = 0;
		printf("\n0x%08x번지 : %s", pCharPoint, pCharPoint);
		for (int iCnt = 0; iCnt < iCount; iCnt++)
		{
			printf("\n0x%08X번지 : %c", pCharPoint + iCnt, *(pCharPoint + iCnt));
		}
		free(pCharPoint);


		// 포인터 배열 변수 할당
		printf("\n=====================\n");
		int *lpPoint[10];
		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			lpPoint[iCnt] = (int*)malloc(sizeof(int));
			*lpPoint[iCnt] = iCnt * 10;
			printf("\n0x%08X번지 : %d", lpPoint + iCnt, *lpPoint[iCnt]);
		}
		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			free(lpPoint[iCnt]);
		}
		printf("\n=====================\n");

		// 2차원 배열 초기화 및 접근
		int iValue[3][2] = { { 10,20 },{ 30,40 },{ 50,60 } };
		for (int iCnt = 0; iCnt < 3; iCnt++)
		{
			printf("\n*(iValue+%d): %p", iCnt, *(iValue + iCnt));
			printf("\t\tiValue[%d]: %p", iCnt, iValue[iCnt]);
		}
		printf("\n");
		for (int iCnt = 0; iCnt < 3; iCnt++)
		{
			for (int jCnt = 0; jCnt < 2; jCnt++)
			{
				printf("\n*(*(iValue+%d)+%d)  : %d", iCnt, jCnt, *(*(iValue + iCnt) + jCnt));
				printf("\t\t *(iValue[%d]+%d) : %d", iCnt, jCnt, *(iValue[iCnt] + jCnt));
			}
		}


		// 이중 포인터 할당 
		printf("\n=====================\n");
		printf("\n====== 이중포인터 =========\n");
		system("cls");				// cls : 도스명령어 (Clear Screen)
		int *pPtr;
		int **ppPtr;
		int num = 10;
		pPtr = &num;
		//포인터의 메모리 주소는 일반포인트에 저장 불가하며 
		//반드시 이중포인터에 저장해야 한다.
		ppPtr = &pPtr;//pPtr의 주소 저장
		printf("%d\n", **ppPtr);//ppPtr의 메모리 주소에 접근

		/////////////////////////////////////////////////////
		// 이중포인트의 할당은 시스템 비트를 고려해야 한다.
		unsigned char *array[50];
		unsigned char size = sizeof(array);
		//32 - bit  : sizeof(array) = 200
		//64 - bit  : sizeof(array) = 400
#ifdef _WIN64		
		printf("\n64 - bit Size=%d", sizeof(array));
#else
		printf("\n32 - bit Size=%d", sizeof(array));
#endif	
		// 8바이트 포인터 배열 ? 4바이트 포인터 배열 ?
		// intptr_t 사용하면 시스템 비트수에 따라 변환됨.
		/*
		intptr_t : 포인터의 주소를 저장하는데 사용. 
		다른 환경으로 이식이 가능하고 안전한 포인터 선언 방법을 제공한다.
		시스템 내부에서 사용하는 포인터와 같은 크기
		포인터를 정수 표현으로 변환할 때 유용하게 사용할 수 있다.

		uinptr_t :부호 없는 버전. type casting(uintprt_t) 사용 필수적
		*/


		int  **ppPoint = 0;
		ppPoint = (int **)malloc(sizeof(intptr_t) * 10);
		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			ppPoint[iCnt] = (int *)malloc(sizeof(intptr_t) * 10);
		}

		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			for (int jCnt = 0; jCnt < 10; jCnt++)
			{
				ppPoint[iCnt][jCnt] = iCnt * 10 + jCnt;
			}
		}

		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			printf("\n");
			for (int jCnt = 0; jCnt < 10; jCnt++)
			{
				printf("[%d,%d]=%d", iCnt, jCnt, ppPoint[iCnt][jCnt]);
				printf("[%d,%d]=%d", iCnt, jCnt, *(ppPoint[iCnt] + jCnt));
			}
		}

		for (int iCnt = 0; iCnt < 10; iCnt++)
		{
			free(ppPoint[iCnt]);
		}

		free(ppPoint);

		printf("\n====== 포인터 배열=========\n");
		system("cls");

		char *pArray[6];
		for (int iCnt = 0; iCnt < 6; iCnt++)
		{
			pArray[iCnt] = (char*)malloc(sizeof(char) * 4);
		}

		for (int iCnt = 0; iCnt < 6; iCnt++)
		{
			for (int jCnt = 0; jCnt < 3; jCnt++)
			{
				pArray[iCnt][jCnt] = 65 + iCnt * 3 + jCnt;
			}
			pArray[iCnt][3] = 0;
		}

		for (int iCnt = 0; iCnt < 6; iCnt++)
		{
			printf("\n");
			printf("[%d]=%s", iCnt, pArray[iCnt]);
		}

		for (int iCnt = 0; iCnt < 6; iCnt++)
		{
			free(pArray[iCnt]);
		}
		_getch();
	}	
#else
	#include <cstdio>
	#include <cstdlib>
	#include <conio.h>
	#include <iostream>

	void main()
	{													//동적 할당하기
		// 기본 void* 에서 int*로 형변환
		printf("\n=====================\n");	
		int *pPoint = new int;			// new 했는데 메모리 공간이 없으면 null반환하므로 항상 체크
		*pPoint = 100;
		printf("%0x번지 : %d\n", pPoint+0, *(pPoint+0) );
		delete( pPoint );							//		

		printf("\n=====================\n");		
		int *pPointArray = new int[10];
		for( int iCnt = 0; iCnt < 10; iCnt++ )
		{		
			pPointArray[iCnt] = iCnt*10;
			//printf("%d:%d\n", 
			//	pPointArray[iCnt],
			//	*(pPointArray + iCnt));
			std::cout << pPointArray[iCnt] <<"   "<< *(pPointArray+iCnt) <<std::endl;
		}

		delete [] pPointArray;

		std::cout << "\n=====================\n";
		char* pCharPoint = 0;
		int iCount = 0;
		pCharPoint = new char[100];
		do{
			pCharPoint[iCount++] = _getche();						
		}while(pCharPoint[iCount-1] != '\r');
	
		pCharPoint[iCount+1] = 0;
		printf("\n0x%08x번지 : %s", pCharPoint, pCharPoint );	
		for( int iCnt = 0; iCnt < iCount; iCnt++ )
		{
			printf("\n0x%08X번지 : %c", pCharPoint+iCnt, *(pCharPoint+iCnt) );	
		}
		delete[] pCharPoint;
		//////////////////////////////////////////////////
		printf("\n=====================\n");	
		int *lpPoint[10];
		for( int iCnt = 0; iCnt < 10; iCnt++ )
		{
			lpPoint[iCnt] = new int;
			*lpPoint[iCnt] = iCnt*10;
			printf("\n0x%08X번지 : %d", lpPoint+iCnt, *lpPoint[iCnt] );	
		}
		for( int iCnt = 0; iCnt < 10; iCnt++ )
		{
			delete lpPoint[iCnt];
		}
		printf("\n=====================\n");	
		int iValue[3][2] = {{10,20}, {30,40}, {50,60}};
		for( int iCnt = 0; iCnt < 3; iCnt++ )
		{
			printf("\n*(iValue+%d): %p", iCnt, *(iValue+iCnt));
			printf("\t\tiValue[%d]: %p", iCnt, iValue[iCnt]);
		}
		printf("\n");
		for( int iCnt = 0; iCnt < 3; iCnt++ )
		{
			for( int jCnt = 0; jCnt < 2; jCnt++ )
			{
				printf("\n*(*(iValue+%d)+%d)  : %d", iCnt,jCnt, *(*(iValue+iCnt)+jCnt) );
				printf("\t\t *(iValue[%d]+%d) : %d", iCnt,jCnt, *(iValue[iCnt]+jCnt ) );
			}
		}
		printf("\n=====================\n");
		_getch();	
	}
#endif

