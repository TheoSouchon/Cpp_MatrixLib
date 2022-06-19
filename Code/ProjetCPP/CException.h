#pragma once

class CException {

private:
	int iEXCValeur;

public:

	// Constructeurs :

	/*
	Constructeur par défault
	*/
	CException();

	/*
	Constructeur de confort
	*/
	CException(unsigned int uiValeur);
public:

	//Accesseurs :

	/*
	Getter de l'atribut iEXCValeur
	*/
	const int EXCGetValeur() {
		return iEXCValeur;
	}

	/*
	Setter de l'atribut iEXCValeur
	*/
	void EXCSetValeur(int iValeur) {
		iEXCValeur = iValeur;
	}
};
