#include "CException.h"

/*
Constructeur par d�fault
*/
CException::CException() {
	iEXCValeur = 0;
}

/*
Constructeur de confort
*/
CException::CException(unsigned int uiValeur)
{
	iEXCValeur = uiValeur;
}
