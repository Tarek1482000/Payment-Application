/* ****************************************************************************************************
 *  File name : terminal.c
 *
 *  Description : Source file of terminal module of payment application
 *  Author: Tarek Ahmed
 *******************************************************************************************************/

#include <stdio.h>
#include "terminal.h"



EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	uint8 counter=0 , date[11]={0};

	scanf(" %[^\n]s",date);

	if((date == NULL_PTR)

			||((date[0]=='3') && (date[1]>'1')) /* Check if days correct */

			||(date[2] !='/') /* Check if not / */

			||(date[3] > '1') /* Check if month correct */

			||(date[5] !='/') /* Check if not / */

			||(date[6] !='2') /* Check if year correct */

			||(date[7] !='0'))/* Check if year correct */
	{

//		printf("WRONG DATE\n");
		/*If the date is not correct */
		return WRONG_DATE;
	}

	while((date[counter]) != '\0')
	{
		termData->transactionDate[counter] = date[counter];
		counter++;
	}

	termData->transactionDate[counter] = '\0';


	if(counter != T_EXPIRE_DATE_NUM)
	{
//		printf("WRONG DATE\n");
		return WRONG_DATE;
	}
//	printf("TERMINAL OK\n");
	return TERMINAL_OK;
}


EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{

	if(cardData->cardExpirationDate[3] > termData->transactionDate[8])
	{
		/*
		 * MM/YY           01/34      cardExpirationDate
		 * DD/MM/YYYY   12/12/2023    transactionDate
		 */
//		printf("TERMINAL OK\n");
		return TERMINAL_OK;
	}


	else if(cardData->cardExpirationDate[3] == termData->transactionDate[8])
	{


		if (cardData->cardExpirationDate[4] > termData->transactionDate[9])
		{
			/*
			 * MM/YY           01/24     cardExpirationDate
			 * DD/MM/YYYY   12/12/2023   transactionDate
			 */
//			printf("TERMINAL OK\n");
			return TERMINAL_OK;
		}



		else if (cardData->cardExpirationDate[4] == termData->transactionDate[9])
		{




			if (cardData->cardExpirationDate[0] > termData->transactionDate[3])
			{
				/*
				 * MM/YY           12/23     cardExpirationDate
				 * DD/MM/YYYY   12/09/2023   transactionDate
				 */
//				printf("TERMINAL OK\n");
				return TERMINAL_OK;
			}



			else if(cardData->cardExpirationDate[0] == termData->transactionDate[3])
			{



				if (cardData->cardExpirationDate[1] > termData->transactionDate[4])
				{
					/*
					 * MM/YY           04/23     cardExpirationDate
					 * DD/MM/YYYY   12/02/2023   transactionDate
					 */
//					printf("TERMINAL OK\n");
					return TERMINAL_OK;
				}


				else
				{
//					printf("EXPIRED CARD\n");
					return EXPIRED_CARD;
				}
			}


			else
			{
//				printf("EXPIRED CARD\n");
				return EXPIRED_CARD;
			}

		}



		else
		{
//			printf("EXPIRED CARD\n");
			return EXPIRED_CARD;
		}

	}


	else
	{
//		printf("EXPIRED CARD\n");
		return EXPIRED_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	scanf("%f",&termData->transAmount);

	if(termData->transAmount <= 0)
	{
//		printf("INVALID AMOUNT\n");
		return INVALID_AMOUNT;
	}

//	printf("TERMINAL OK\n");
	return TERMINAL_OK;
}



EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
	if(maxAmount <= 0)
	{
//		printf("INVALID MAX AMOUNT\n");
		return INVALID_MAX_AMOUNT;
	}

	termData->maxTransAmount = maxAmount;
//	printf("TERMINAL OK\n");
	return TERMINAL_OK;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{

	if((termData->transAmount) > (termData->maxTransAmount))
	{
//		printf("EXCEED MAX AMOUNT\n");
		return EXCEED_MAX_AMOUNT;
	}

//	printf("TERMINAL OK\n");
	return TERMINAL_OK;
}




EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{

//	printf("INVALID CARD\n");
	return INVALID_CARD;

//	printf("TERMINAL OK\n");
	return TERMINAL_OK;
}






void getTransactionDateTest(void)
{
	uint8 result=0;
	ST_terminalData_t termData;
	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: getTransactionDateTest\n");
	printf("Test Case 1:\n");
	printf("Input Data: 10/09/2022\n");
	result=getTransactionDate(&termData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data: 10-09-2022\n");
	result=getTransactionDate(&termData);
	printf("Expected Result: 1\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data: 10/09/2029 \n");
	result=getTransactionDate(&termData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data: 01/9/2022 \n");
	result=getTransactionDate(&termData);
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 5:\n");
	printf("Input Data: 1/09/2022 \n");
	result=getTransactionDate(&termData);
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 6:\n");
	printf("Input Data: 10/09/22 \n");
	result=getTransactionDate(&termData);
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");

}


void isCardExpriedTest(void)
{
	uint8 result=0;

	ST_cardData_t cardData;
	ST_terminalData_t termData;

	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: isCardExpriedTest\n");
	printf("Test Case 1:\n");
	printf("Input Data1: 09/24\n");
	getCardExpiryDate(&cardData);
	printf("Input Data2: 10/09/2023\n");
	getTransactionDate(&termData);
	result=isCardExpired(&cardData,&termData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data1: 04/23\n");
	getCardExpiryDate(&cardData);
	printf("Input Data2: 01/12/2022\n");
	getTransactionDate(&termData);
	result=isCardExpired(&cardData,&termData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data1: 01/23\n");
	getCardExpiryDate(&cardData);
	printf("Input Data2: 10/02/2023\n");
	getTransactionDate(&termData);
	result=isCardExpired(&cardData,&termData);
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data1: 05/22\n");
	getCardExpiryDate(&cardData);
	printf("Input Data2: 10/01/2023\n");
	getTransactionDate(&termData);
	result=isCardExpired(&cardData,&termData);
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 5:\n");
	printf("Input Data1: 09/22\n");
	getCardExpiryDate(&cardData);
	printf("Input Data2: 10/09/2030\n");
	getTransactionDate(&termData);
	result=isCardExpired(&cardData,&termData);
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 6:\n");
	printf("Input Data1: 09/32\n");
	getCardExpiryDate(&cardData);
	printf("Input Data2: 10/09/2023\n");
	getTransactionDate(&termData);
	result=isCardExpired(&cardData,&termData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
}



void getTransactionAmountTest(void)
{
	uint8 result=0;
	ST_terminalData_t termData;
	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: getTransactionAmountTest\n");
	printf("Test Case 1:\n");
	printf("Input Data: 10\n");
	result=getTransactionAmount(&termData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data: 0\n");
	result=getTransactionAmount(&termData);
	printf("Expected Result: 4\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data: -10 \n");
	result=getTransactionAmount(&termData);
	printf("Expected Result: 4 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data: 91020 \n");
	result=getTransactionAmount(&termData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
}



void setMaxAmountTest(void)
{
	uint8 result=0;
	ST_terminalData_t termData;
	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: setMaxAmountTest\n");
	printf("Test Case 1:\n");
	printf("Input Data: 10\n");
	result=setMaxAmount(&termData,10);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data: 0\n");
	result=setMaxAmount(&termData,0);
	printf("Expected Result: 6\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data: -10 \n");
	result=setMaxAmount(&termData,-10);
	printf("Expected Result: 6 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data: 91020 \n");
	result=setMaxAmount(&termData,91020);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 5:\n");
	printf("Input Data: 91.20 \n");
	result=setMaxAmount(&termData,91.20);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");

}

void isBelowMaxAmountTest(void)
{
	uint8 result=0;
	ST_terminalData_t termData;
	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: isBelowMaxAmountTest\n");
	printf("Test Case 1:\n");
	printf("MaxAmount:  10000\n");
	setMaxAmount(&termData,10000);
	printf("Input Data: 10000\n");
	getTransactionAmount(&termData);
	result=isBelowMaxAmount(&termData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data: 5000\n");
	getTransactionAmount(&termData);
	result=isBelowMaxAmount(&termData);
	printf("Expected Result: 0\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data: 10001 \n");
	getTransactionAmount(&termData);
	result=isBelowMaxAmount(&termData);
	printf("Expected Result: 5 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data: 15000 \n");
	getTransactionAmount(&termData);
	result=isBelowMaxAmount(&termData);
	printf("Expected Result: 5 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
}



void isValidCardPANTest(void)
{


}
