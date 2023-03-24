/* ****************************************************************************************************
 *  File name : server.h
 *
 *  Description : Header file of server module of payment application
 *  Author: Tarek Ahmed
 *******************************************************************************************************/

#ifndef SERVER_H_
#define SERVER_H_

#include "../std_types.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"

/********************************************************************************************************
 *                                          Definitions
 ********************************************************************************************************/


typedef enum
{
	APPROVED,
	DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,
	FRAUD_CARD,
	INTERNAL_SERVER_ERROR
}EN_transState_t;




typedef enum
{
	SERVER_OK,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	ACCOUNT_NOT_FOUND,
	LOW_BALANCE,
	BLOCKED_ACCOUNT
}EN_serverError_t;


typedef enum
{
	RUNNING,
	BLOCKED
}EN_accountState_t;


typedef struct
{
	float32 balance;
	EN_accountState_t state;
	uint8 primaryAccountNumber[20];
}ST_accountsDB_t;





typedef struct
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32 transactionSequenceNumber;
}ST_transaction;



/********************************************************************************************************
 *                                        Functions Prototype
 ********************************************************************************************************/


EN_transState_t recieveTransactionData(ST_transaction *transData);


EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);



EN_serverError_t saveTransaction(ST_transaction *transData);



void listSavedTransactions(void);


void recieveTransactionDataTest(void);


void isValidAccountTest(void);


void isBlockedAccountTest(void);


void isAmountAvailableTest(void);


void saveTransactionTest(void);



uint8 check_string(uint8 *str1 , uint8 *str2);

#endif /* SERVER_H_ */
