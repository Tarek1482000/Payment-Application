/* ****************************************************************************************************
 *  File name : terminal.h
 *
 *  Description : Header file of terminal module of payment application
 *  Author: Tarek Ahmed
 *******************************************************************************************************/


#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "../std_types.h"
#include "../Card/card.h"

/********************************************************************************************************
 *                                          Definitions
 ********************************************************************************************************/

#define T_EXPIRE_DATE_NUM 10


typedef enum
{
	TERMINAL_OK,
	WRONG_DATE,
	EXPIRED_CARD,
	INVALID_CARD,
	INVALID_AMOUNT,
	EXCEED_MAX_AMOUNT,
	INVALID_MAX_AMOUNT
}EN_terminalError_t ;




typedef struct
{
	float32 transAmount;
	float32 maxTransAmount;
	uint8 transactionDate[11];
}ST_terminalData_t;



/********************************************************************************************************
 *                                        Functions Prototype
 ********************************************************************************************************/


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);


EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);


EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);


EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional



void getTransactionDateTest(void);



void isCardExpriedTest(void);



void getTransactionAmountTest(void);



void setMaxAmountTest(void);



void isBelowMaxAmountTest(void);



void isValidCardPANTest(void);

#endif /* TERMINAL_H_ */
