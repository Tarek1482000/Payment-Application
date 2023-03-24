/* ****************************************************************************************************
 *  File name : application.c
 *
 *  Description : Source file of application module of payment application
 *  Author: Tarek Ahmed
 *******************************************************************************************************/

#include "../Application/app.h"

#include <stdio.h>

#include "../Server/server.h"
#include "../Terminal/terminal.h"


void appStart(void)
{
	ST_transaction trans;

	EN_transState_t state = recieveTransactionData(&trans);

	ST_accountsDB_t ref;

	if(isCardExpired(&trans.cardHolderData, &trans.terminalData) == TERMINAL_OK)
	{
		if(isBelowMaxAmount(&trans.terminalData) == TERMINAL_OK)
		{
			if(isValidAccount(&trans.cardHolderData, &ref) == SERVER_OK)
			{
				if(state == APPROVED)
				{
					if(saveTransaction(&trans) == SERVER_OK)
					{
						printf("Transaction saved\n");
					}
					else
					{
						printf("Transaction not saved\n");
					}

				}
				else if(state == DECLINED_INSUFFECIENT_FUND)
				{
					printf("DECLINED INSUFFECIENT FUND\n");
				}

				else if(state == DECLINED_STOLEN_CARD)
				{
					printf("DECLINED STOLEN CARD\n");
				}
				else if(state == FRAUD_CARD)
				{
					printf("FRAUD CARD\n");
				}

			}

			else if(isValidAccount(&trans.cardHolderData, &ref) == ACCOUNT_NOT_FOUND)
			{
				printf("ACCOUNT NOT FOUND\n");
			}
		}

		else if(isBelowMaxAmount(&trans.terminalData) == EXCEED_MAX_AMOUNT)
		{
			printf("Exceed max amount \n");
		}

	}
	else if(isCardExpired(&trans.cardHolderData, &trans.terminalData) == EXPIRED_CARD)
	{
		printf("Expired card\n");
	}
}
