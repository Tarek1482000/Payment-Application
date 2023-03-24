/* ****************************************************************************************************
 *  File name : server.c
 *
 *  Description : Source file of server module of payment application
 *  Author: Tarek Ahmed
 *******************************************************************************************************/

#include "server.h"
#include <stdio.h>

ST_accountsDB_t accountsDB[255] =
{
		{2000.0 , RUNNING, "8989374615436851"},
		{1000.0 , BLOCKED, "5807007076043875"},
		{500.0  , RUNNING, "6011627201989743"},
		{7500.0 , BLOCKED, "3566002027889576"},
		{2450.0 , RUNNING, "2283248777889576"},
		{12000.0, BLOCKED, "5019717010103742"}
};


ST_transaction  g_transaction[255]={0};


uint32 g_transaction_id=0;

EN_transState_t recieveTransactionData(ST_transaction *transData)
{

	ST_accountsDB_t account;

	uint8 state = APPROVED;

	printf("Enter your name please\n");
	if(getCardHolderName(&transData->cardHolderData) == WRONG_NAME)
	{
		state = FRAUD_CARD;
	}

	printf("Enter your Card Expiry Date please\n");
	getCardExpiryDate(&transData->cardHolderData);

	printf("Enter your Card PAN please\n");
	getCardPAN(&transData->cardHolderData);


	printf("Enter The Date\n");
	getTransactionDate(&transData->terminalData);

	printf("Enter Transaction amount\n");
	getTransactionAmount(&transData->terminalData);

	setMaxAmount(&transData->terminalData, 30000.0);


	if(isValidAccount(&transData->cardHolderData, &account) == ACCOUNT_NOT_FOUND)
	{
		//		printf("FRAUD CARD\n");
		state =  FRAUD_CARD;
	}

	if(isAmountAvailable(&transData->terminalData, &account) == LOW_BALANCE)
	{
		//		printf("DECLINED INSUFFECIENT FUND\n");
		state =  DECLINED_INSUFFECIENT_FUND;
	}

	if(isBlockedAccount(&account) == BLOCKED_ACCOUNT)
	{
		//		printf("DECLINED STOLEN CARD\n");
		state =  DECLINED_STOLEN_CARD;
	}

	if(saveTransaction(transData) == SAVING_FAILED)
	{
		//		printf("INTERNAL SERVER ERROR\n");
		state =  INTERNAL_SERVER_ERROR;
	}


	//	printf("APPROVED\n");
	return state;
}


EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
	uint8 index=0;
	uint8 count=0;

	if(accountRefrence == NULL_PTR)
	{
		//		printf("ACCOUNT NOT FOUND\n");
		return ACCOUNT_NOT_FOUND;
	}

	for(index=0;index<255;index++)
	{
		if(check_string((cardData->primaryAccountNumber),(accountsDB[index].primaryAccountNumber)))
		{

			accountRefrence->balance = accountsDB[index].balance;
			accountRefrence->state = accountsDB[index].state;

			while((accountsDB[index].primaryAccountNumber[count]) != '\0')
			{
				accountRefrence->primaryAccountNumber[count] = accountsDB[index].primaryAccountNumber[count];
				count++;
			}

			//			printf("SERVER OK\n");
			return SERVER_OK;
		}
	}

	accountRefrence=NULL_PTR;
	//	printf("ACCOUNT NOT FOUND\n");
	return ACCOUNT_NOT_FOUND;
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	if(accountRefrence->state == RUNNING)
	{
		//		printf("SERVER OK\n");
		return SERVER_OK;
	}

	//	printf("BLOCKED ACCOUNT\n");
	return BLOCKED_ACCOUNT;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
	if(termData->transAmount < accountRefrence->balance)
	{
		//		printf("SERVER OK\n");
		return SERVER_OK;
	}
	//	printf("LOW BALANCE\n");
	return LOW_BALANCE;
}


EN_serverError_t saveTransaction(ST_transaction *transData)
{

	uint8 counter = 0;

	if(g_transaction_id>=255)
	{
		return SAVING_FAILED;
	}

	/*
	 * Set a sequence number transaction account
	 */
	transData->transactionSequenceNumber=g_transaction_id;

	/*
	 * Copy Card Name into transaction account
	 */
	while((transData->cardHolderData.cardHolderName[counter]) != '\0')
	{
		g_transaction[g_transaction_id].cardHolderData.cardHolderName [counter] = transData->cardHolderData.cardHolderName[counter] ;

		counter++;
	}
	counter = 0;

	/*
	 * Copy Card expire date into transaction account
	 */
	while((transData->cardHolderData.cardExpirationDate[counter]) != '\0')
	{
		g_transaction[g_transaction_id].cardHolderData.cardExpirationDate [counter] = transData->cardHolderData.cardExpirationDate[counter] ;

		counter++;
	}
	counter = 0;


	/*
	 * Copy Card PAN into transaction account
	 */
	while((transData->cardHolderData.primaryAccountNumber[counter]) != '\0')
	{
		g_transaction[g_transaction_id].cardHolderData.primaryAccountNumber [counter] = transData->cardHolderData.primaryAccountNumber[counter] ;

		counter++;
	}
	counter = 0;



	/*
	 * Copy terminal transaction Date into transaction account
	 */
	while((transData->terminalData.transactionDate[counter]) != '\0')
	{
		g_transaction[g_transaction_id].terminalData.transactionDate [counter] = transData->terminalData.transactionDate[counter] ;

		counter++;
	}
	counter = 0;

	/*
	 * Copy terminal max transaction Amount  into transaction account
	 */
	g_transaction[g_transaction_id].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;


	/*
	 * Copy terminal transaction Amount  into transaction account
	 */
	g_transaction[g_transaction_id].terminalData.transAmount = transData->terminalData.transAmount;




	/*
	 * Copy  transaction state into transaction account
	 */
	g_transaction[g_transaction_id].transState = transData->transState;



	g_transaction_id++;
	//	printf("SERVER OK\n");
	return SERVER_OK;
}



void listSavedTransactions(void)
{
	ST_transaction account;

	printf("#########################\n");
	printf("Transaction Sequence Number: %d\n", account.transactionSequenceNumber);
	printf("Transaction Date: %s\n",account.terminalData.transactionDate);
	printf("Transaction Amount: %f\n",account.terminalData.transAmount);
	printf("Transaction State: %d\n",account.transState);
	printf("Terminal Max Amount: %f\n",account.terminalData.maxTransAmount);
	printf("Card holder Name: %s\n",account.cardHolderData.cardHolderName);
	printf("PAN: %s\n",account.cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s\n",account.cardHolderData.cardExpirationDate);
	printf("#########################\n");
}





void recieveTransactionDataTest(void)
{
	uint8 result=0;
	ST_transaction transData;
	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: recieveTransactionDataTest\n");
	printf("Test Case 1:\n");
	printf("Input Data:\n"
			"Name:Tarek Ahmed Abd El Wahab\n"
			"Expire date:10/25\n"
			"PAN:2283248777889576\n"
			"Trans date:10/09/2022\n"
			"Trans amount:2000\n");
	result=recieveTransactionData(&transData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data:\n"
			"Name:Tarek Ahmed\n"
			"Expire date:10/25\n"
			"PAN:2283248777889576\n"
			"Trans date:10/09/2022\n"
			"Trans amount:2000\n");
	result=recieveTransactionData(&transData);
	printf("Expected Result: 3\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data:\n"
			"Name:Tarek Ahmed Abd El Wahab\n"
			"Expire date:10/25\n"
			"PAN:5019717010103742\n"
			"Trans date:10/09/2022\n"
			"Trans amount:2000\n");
	result=recieveTransactionData(&transData);
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 4:\n");
	printf("Input Data:\n"
			"Name:Tarek Ahmed Abd El Wahab\n"
			"Expire date:10/25\n"
			"PAN:2283248777889576\n"
			"Trans date:10/09/2022\n"
			"Trans amount:6000\n");
	result=recieveTransactionData(&transData);
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
}





void isValidAccountTest(void)
{
	uint8 result=0;
	ST_cardData_t cardData;
	ST_accountsDB_t accountRefrenc;

	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: isValidAccountTest\n");
	printf("Input Data:6011627201989743\n");
	getCardPAN(&cardData);
	result=isValidAccount(&cardData, &accountRefrenc);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data:3566002027889576\n");
	getCardPAN(&cardData);
	result=isValidAccount(&cardData, &accountRefrenc);
	printf("Expected Result: 0\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 3:\n");
	printf("Input Data:5807007076046666\n");
	getCardPAN(&cardData);
	result=isValidAccount(&cardData, &accountRefrenc);
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
}


void isBlockedAccountTest(void)
{
	uint8 result=0;
	uint8 i=0;

	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: isBlockedAccountTest\n");
	printf("Input Data:0 \n");
	scanf("%d",&i);
	result = isBlockedAccount(&accountsDB[i]);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data:3\n");
	scanf("%d",&i);
	result = isBlockedAccount(&accountsDB[i]);
	printf("Expected Result: 5\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");

}


void isAmountAvailableTest(void)
{
	ST_terminalData_t termData;
	uint8 result=0;

	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: isAmountAvailableTest\n");
	printf("Input Data:2000 \n");
	scanf("%f",&termData.transAmount);
	result = isAmountAvailable(&termData, &accountsDB[4]);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data:3000\n");
	scanf("%f",&termData.transAmount);
	result = isAmountAvailable(&termData, &accountsDB[4]);
	printf("Expected Result: 4\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");

}


void saveTransactionTest(void)
{
	ST_transaction transData;
	uint8 result=0;

	printf("*****************************************************************************************************\n");
	printf("Tester Name: Tarek Ahmed\n");
	printf("Function Name: saveTransactionTest\n");
	printf("Input Data:sequence = 0 \n");
	result = saveTransaction(&transData);
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");
	printf("Test Case 2:\n");
	printf("Input Data:sequence = 255 \n");
	g_transaction_id = 255;
	result = saveTransaction(&transData);
	printf("Expected Result: 1\n");
	printf("Actual Result: %d \n",result);
	printf("*****************************************************************************************************\n");

}





uint8 check_string(uint8 *str1 , uint8 *str2)
{
	uint8 counter=0;

	while(str1[counter] != '\0' || str2[counter] != '\0')
	{
		if(str1[counter] != str2[counter])
		{
			return 0;
		}
		counter++;
	}

	return 1;
}
