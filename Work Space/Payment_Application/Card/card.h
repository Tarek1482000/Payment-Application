/* ****************************************************************************************************
 *
 *  File Name : card.h
 *
 *  Description : Header file of card module of payment application
 *
 *  Author: Tarek Ahmed
 *
 *******************************************************************************************************/

#ifndef CARD_H_
#define CARD_H_

#include "../std_types.h"

/********************************************************************************************************
 *                                          Definitions
 ********************************************************************************************************/

#define NAME_MAX           24
#define NAME_MIN           20

#define EXPIRE_DATE_NUM    5

#define PAN_MAX            19
#define PAN_MIN            16



typedef enum
{
	CARD_OK,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN
}EN_cardError_t;;


typedef struct
{
	uint8  cardHolderName[25];
	uint8  primaryAccountNumber[20];
	uint8  cardExpirationDate[6];
}ST_cardData_t;


/********************************************************************************************************
 *                                        Functions Prototype
 ********************************************************************************************************/


EN_cardError_t getCardHolderName(ST_cardData_t *cardData);




EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);




EN_cardError_t getCardPAN(ST_cardData_t *cardData);




void getCardHolderNameTest(void);


void getCardExpiryDateTest(void);


void getCardPANTest(void);


#endif /* CARD_H_ */
