/* ****************************************************************************************************
 *  File name : card.c
 *
 *  Description : Source file of card module of payment application
 *  Author: Tarek Ahmed
 *******************************************************************************************************/
#include <stdio.h>
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{

	uint8  counter=0 , name[25]={0} ;

	/* Get user name
	 * Check if the name is alphabet
	 * Check user name length
	 */
	scanf(" %[^\n]s",name);

	if(name == NULL_PTR)
	{
//		printf("WRONG NAME\n");
		return WRONG_NAME;
	}

	while(name[counter] != '\0')
	{

		if(!(('z'>= name[counter] && name[counter] >= 'a') || ('Z'>= name[counter] && name[counter] >= 'A') || (name[counter] == ' ')))
		{
//			printf("WRONG NAME\n");
			return WRONG_NAME;
		}


		cardData->cardHolderName [counter] = name[counter];

		counter++;
	}

	cardData->cardHolderName [counter] = '\0';

	if(counter>NAME_MAX || counter<NAME_MIN)
	{
//		printf("WRONG NAME\n");
		return WRONG_NAME;
	}
//	printf("CARD OK\n");
	return CARD_OK;
}




EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	uint8 counter=0 , date[6]={0} ;

	/*
	 * Get Expire date and check if the date is correct
	 */
	scanf(" %[^\n]s",date);


	if((date == NULL_PTR) || (date[0]>'1') || (date[2] !='/')|| ((date[0]=='1') && (date[1]>'2')))
	{
//		printf("WRONG EXP DATE\n");
		return WRONG_EXP_DATE;
	}

	while((date[counter]) != '\0')
	{
		cardData->cardExpirationDate[counter] = date[counter];
		counter++;
	}

	cardData->cardExpirationDate[counter] = '\0';


	if(counter != EXPIRE_DATE_NUM)
	{
//		printf("WRONG EXP DATE\n");
		return WRONG_EXP_DATE;
	}
//	printf("CARD OK\n");
	return CARD_OK;
}



EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	uint8 counter=0 , pan[20]={0};

	/*
	 * Get PAN and check if it is correct
	 */

	scanf(" %[^\n]s",pan);

	if(pan == NULL)
	{
//		printf("WRONG PAN\n");
		return WRONG_PAN;
	}

	while(pan[counter] != '\0')
	{
		if(pan[counter]>'9' || pan[counter]<'0')
		{
//			printf("WRONG PAN\n");
			return WRONG_PAN;
		}

		cardData->primaryAccountNumber[counter] = pan[counter];
		counter++;
	}
	cardData->primaryAccountNumber[counter] = '\0';


	if(counter>PAN_MAX || counter<PAN_MIN)
	{
//		printf("WRONG PAN\n");
		return WRONG_PAN;
	}
//	printf("CARD OK\n");
	return CARD_OK;
}





void getCardHolderNameTest(void)
{
	uint8 result=0;

	ST_cardData_t *cardData;

	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 1:\n");
	printf("Input Data: Tarek Ahmed Abd El Wahab\n"); //24
	result=getCardHolderName(&cardData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data: Tarek Ahmed Abd El Wah\n"); //22
	result=getCardHolderName(&cardData);
	printf("Expected Result: 0\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data: Tarek Ahmed Abd El Wahab Ali \n"); //28
	result=getCardHolderName(&cardData);
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data: Tarek Ahmed \n"); //11
	result=getCardHolderName(&cardData);
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
}




void getCardExpiryDateTest(void)
{

	uint8 result=0;

	ST_cardData_t *cardData;

	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: getCardExpiryDateTest\n");
	printf("Test Case 1:\n");
	printf("Input Data: 10/25\n");
	result=getCardExpiryDate(&cardData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data: 08/22\n");
	result=getCardExpiryDate(&cardData);
	printf("Expected Result: 0\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data: 20/1 \n");
	result=getCardExpiryDate(&cardData);
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data: 1/30 \n");
	result=getCardExpiryDate(&cardData);
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 5:\n");
	printf("Input Data: 1027 \n");
	result=getCardExpiryDate(&cardData);
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 6:\n");
	printf("Input Data: 10-23 \n");
	result=getCardExpiryDate(&cardData);
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
}


void getCardPANTest(void)
{
	uint8 result=0;

	ST_cardData_t *cardData;

	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: getCardPANTest\n");
	printf("Test Case 1:\n");
	printf("Input Data: 0123456789987643\n"); //16
	result=getCardPAN(&cardData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data: 0123456789987996543\n"); //19
	result=getCardPAN(&cardData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data: 012345678998764\n"); //15
	result=getCardPAN(&cardData);
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data: Tarek 01234567899879965431 \n");//20
	result=getCardPAN(&cardData);
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 5:\n");
	printf("Input Data: Tarek 0123456789 \n");
	result=getCardPAN(&cardData);
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 6:\n");
	printf("Input Data: 012345678_7996543 \n");
	result=getCardPAN(&cardData);
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
}
