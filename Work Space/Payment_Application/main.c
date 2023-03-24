/* ****************************************************************************************************
 *  File name : main.c
 *
 *  Description : Source file of main function of payment application
 *  Author: Tarek Ahmed
 *******************************************************************************************************/
#include <stdio.h>
#include "Server/server.h"
#include "Application/app.h"

int main(void)
{

	setbuf(stdout,NULL_PTR);

	for(;;)
	{
		appStart();
		printf("*****************************************\n");
	}
	return 0;
}

