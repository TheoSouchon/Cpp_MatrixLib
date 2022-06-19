// ProjetCPP.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include "CLigne.h"
#include "CMatrice.h"
#include "COperationsMatrice.h"
#include <iostream>
#include <stdio.h>


/*
Main réalisé pour le rendu de la question individuelle du projet matrice
*/
int main(int argc, char* argv [])
{

	CMatrice<double>** ppMATListeMatrice;
	unsigned int uiBoucle;
	CException EXCErreur;

	if (argc < 5) {
		printf("Il manque des chemins de fichier en paramètre (il en faut 5), fin du programme\n\n");
		return 0;
	}
	int nbArg = 5;

	try {
		ppMATListeMatrice = (CMatrice<double>**) malloc((nbArg -1) * sizeof(CMatrice<double>*));
		if (ppMATListeMatrice == nullptr) {
			EXCErreur.EXCSetValeur(Pointeur_Null);
			throw EXCErreur;
		}
		//Pour chaque nom de fichier
		for (uiBoucle = 1; uiBoucle < nbArg; uiBoucle++)
		{
			//on créé et stock la matrice
			ppMATListeMatrice[uiBoucle-1] = new CMatrice<double>(argv[uiBoucle]);
		}
	}
	catch (CException EXCe) {
		//gestion exception
		switch (EXCe.EXCGetValeur()) {
		case 1:
			printf("Exception : Index_Incorect\n\n");
			break;
		case 2:
			printf("Exception : Pointeur_Null\n\n");
			break;
		case 3:
			printf("Exception : Tailles_Differentes\n\n");
			break;
		case 4:
			printf("Exception : Division_Par_Zero\n\n");
			break;
		case 5:
			printf("Exception : Taille_Insufisante\n\n");
			break;
		case 6:
			printf("Exception : Erreur type matrice (pas double)\n\n");
			break;
		}

		printf("Erreur lors de la lecture des fichiers, fin du programme\n");
		return 0;
	}

	std::cout << "Vecteur avant changement de base : ";
	ppMATListeMatrice[0]->MATAfficher();
	COperationsMatrice OPM1;
	CMatrice<double> pMATMatricesPassage[3] = { *ppMATListeMatrice[1], *ppMATListeMatrice[2], *ppMATListeMatrice[3] };
	std::cout << "Vecteur après changement de base : ";
	OPM1.OPMChangerBase(*ppMATListeMatrice[0], pMATMatricesPassage, 3).MATAfficher();

	// Libération de la mémoire
	if (ppMATListeMatrice != nullptr) {
		for (uiBoucle = 1; uiBoucle < nbArg; uiBoucle++)
		{
			//on créé et stock la matrice
			ppMATListeMatrice[uiBoucle - 1] = new CMatrice<double>(argv[uiBoucle]);
		}
		free(ppMATListeMatrice);
	}
}




/*
Main réalisé pour le rendu de la première version du projet matrice
*/
int ancienMain(int argc, char* argv[]) {
	CMatrice<double>** ppMATListeMatrice;
	unsigned int uiBoucle;
	CException EXCErreur;

	if (argc < 2) {
		printf("Aucun chemin de fichier passe en paramètre, fin du programme\n\n");
		return 0;
	}

	try {
		ppMATListeMatrice = (CMatrice<double>**) malloc((argc - 1) * sizeof(CMatrice<double>*));
		if (ppMATListeMatrice == nullptr) {
			EXCErreur.EXCSetValeur(Pointeur_Null);
			throw EXCErreur;
		}
		//Pour chaque nom de fichier
		for (uiBoucle = 1; uiBoucle < argc; uiBoucle++)
		{
			//on créé et stock la matrice
			ppMATListeMatrice[uiBoucle - 1] = new CMatrice<double>(argv[uiBoucle]);
		}
	}
	catch (CException EXCe) {
		//gestion exception
		switch (EXCe.EXCGetValeur()) {
		case 1:
			printf("Exception : Index_Incorect\n\n");
			break;
		case 2:
			printf("Exception : Pointeur_Null\n\n");
			break;
		case 3:
			printf("Exception : Tailles_Differentes\n\n");
			break;
		case 4:
			printf("Exception : Division_Par_Zero\n\n");
			break;
		case 5:
			printf("Exception : Taille_Insufisante\n\n");
			break;
		case 6:
			printf("Exception : Erreur type matrice (pas double)\n\n");
			break;
		}

		printf("Erreur lors de la lecture des fichiers, fin du programme\n");
		return 0;
	}



	double dFacteur = NULL;
	printf("\nSaisir une valeur c \n(Interpretable en tant que double par promotion numerique ou correspondance exacte)\n\n");
	fflush(stdout);
	int iCode = scanf_s("%lf", &dFacteur);
	if (iCode != 1) {
		printf("Erreur, la valeur c n est pas convertible en double.\n Saut de la multiplication et de la division des matrices par c\n\n");
	}
	else {
		/*Multiplication*/
		try {
			printf("\n\nMultiplication par %.2lf :\n\n", dFacteur);
			for (uiBoucle = 0; uiBoucle < (argc - 1); uiBoucle++)
			{
				CMatrice<double> MATTest = *ppMATListeMatrice[uiBoucle];
				(MATTest * dFacteur).MATAfficher();
				printf("---------------------------------");
			}
		}
		catch (CException EXCe) {
			switch (EXCe.EXCGetValeur()) {
			case 1:
				printf("Exception : Index_Incorect\n\n");
				break;
			case 2:
				printf("Exception : Pointeur_Null\n\n");
				break;
			case 3:
				printf("Exception : Tailles_Differentes\n\n");
				break;
			case 4:
				printf("Exception : Division_Par_Zero\n\n");
				break;
			case 5:
				printf("Exception : Taille_Insufisante\n\n");
				break;
			}
			printf("Erreur lors de la multiplication des matrices par c, le programme va continuer son exécution\n\n");
		}

		/*Division*/
		try {
			printf("\nDivision par %.2lf :\n\n", dFacteur);
			for (uiBoucle = 0; uiBoucle < (argc - 1); uiBoucle++)
			{
				CMatrice<double> MATTest = *ppMATListeMatrice[uiBoucle];
				(MATTest / dFacteur).MATAfficher();
				printf("---------------------------------");
			}
		}
		catch (CException EXCe) {
			switch (EXCe.EXCGetValeur()) {
			case 1:
				printf("Exception : Index_Incorect\n\n");
				break;
			case 2:
				printf("Exception : Pointeur_Null\n\n");
				break;
			case 3:
				printf("Exception : Tailles_Differentes\n\n");
				break;
			case 4:
				printf("Exception : Division_Par_Zero\n\n");
				break;
			case 5:
				printf("Exception : Taille_Insufisante\n\n");
				break;
			}
			printf("Erreur lors de la division des matrices par c, le programme va continuer son exécution\n\n");
		}
	}

	/*Somme*/
	try {
		printf("\nSomme des matrices :\n\n");
		CMatrice<double> MATSomme = *ppMATListeMatrice[0];
		for (uiBoucle = 1; uiBoucle < (argc - 1); uiBoucle++)
		{
			MATSomme = MATSomme + *ppMATListeMatrice[uiBoucle];
		}
		MATSomme.MATAfficher();
		printf("---------------------------------");
	}
	catch (CException EXCe) {
		switch (EXCe.EXCGetValeur()) {
		case 1:
			printf("Exception : Index_Incorect\n\n");
			break;
		case 2:
			printf("Exception : Pointeur_Null\n\n");
			break;
		case 3:
			printf("Exception : Tailles_Differentes\n\n");
			break;
		case 4:
			printf("Exception : Division_Par_Zero\n\n");
			break;
		case 5:
			printf("Exception : Taille_Insufisante\n\n");
			break;
		}
		printf("Erreur lors du calcul de la somme des matrices, le programme va continuer son exécution\n\n");
	}

	/*Somme selon les indices*/
	try {
		printf("\nDifference entre les matrices d'indices paires et impair :\n\n");
		CMatrice<double> MATSomme2 = *ppMATListeMatrice[0];
		for (uiBoucle = 1; uiBoucle < (argc - 1); uiBoucle++)
		{
			//Si l'indice de la matrice est pair
			if (uiBoucle % 2 == 0) {
				MATSomme2 = MATSomme2 + *ppMATListeMatrice[uiBoucle];
			}
			else {
				MATSomme2 = MATSomme2 - *ppMATListeMatrice[uiBoucle];
			}
		}
		MATSomme2.MATAfficher();
		printf("---------------------------------");
	}
	catch (CException EXCe) {
		switch (EXCe.EXCGetValeur()) {
		case 1:
			printf("Exception : Index_Incorect\n\n");
			break;
		case 2:
			printf("Exception : Pointeur_Null\n\n");
			break;
		case 3:
			printf("Exception : Tailles_Differentes\n\n");
			break;
		case 4:
			printf("Exception : Division_Par_Zero\n\n");
			break;
		case 5:
			printf("Exception : Taille_Insufisante\n\n");
			break;
		}
		printf("Erreur lors de l'addition et soustraction des matrices paires / impaires, le programme va continuer son exécution\n\n");
	}

	/*Produit*/
	try {
		printf("\nProduit des matrices :\n\n");
		CMatrice<double> MATProduit = *ppMATListeMatrice[0];
		for (uiBoucle = 1; uiBoucle < (argc - 1); uiBoucle++)
		{
			MATProduit = MATProduit * (*ppMATListeMatrice[uiBoucle]);
		}
		MATProduit.MATAfficher();
	}
	catch (CException EXCe) {
		switch (EXCe.EXCGetValeur()) {
		case 1:
			printf("Exception : Index_Incorect\n\n");
			break;
		case 2:
			printf("Exception : Pointeur_Null\n\n");
			break;
		case 3:
			printf("Exception : Tailles_Differentes\n\n");
			break;
		case 4:
			printf("Exception : Division_Par_Zero\n\n");
			break;
		case 5:
			printf("Exception : Taille_Insufisante\n\n");
			break;
		}
		printf("Erreur lors de la multiplication des matrices, le programme va continuer son exécution\n\n");
	}

	// Libération de la mémoire
	if (ppMATListeMatrice != nullptr) {
		for (uiBoucle = 1; uiBoucle < argc; uiBoucle++)
		{
			//on créé et stock la matrice
			ppMATListeMatrice[uiBoucle - 1] = new CMatrice<double>(argv[uiBoucle]);
		}
		free(ppMATListeMatrice);
	}
	return 0;
}