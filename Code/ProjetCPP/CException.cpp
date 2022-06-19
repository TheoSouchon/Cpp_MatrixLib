#include "CException.h"

/*
Constructeur par défault
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
