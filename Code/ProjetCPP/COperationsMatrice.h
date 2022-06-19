#pragma once


class COperationsMatrice
{

public:

	/*
	Calacul la transpos�e d'une matrice
	Entree :
		- MAT1 : IN, matrice � transposer
	Precondition : /
	Sortie :
		- CMatrice<CType> : la transpos�e de MAT1
	Postconditions :
		- La transpos�e est retourn�e
	*/
	template<class CType>
	CMatrice<CType> OPMTransposer(CMatrice<CType> MAT1);

	/*
	Calacul le vecteur MATVect dans la derni�re base de la liste des pMATMatPassage
	Entree :
		- MATVect : IN, Vecteur � changer de base, doit �tre de taille 1 ligne * n colonnes OU n lignes * 1 colonne
		- pMATMatPassage : IN, matrices de changement de base, doit contenir au moins uiNbMatPassage matrices chacune de taille n*n
		- uiNbMatPassage : IN, nombre de matrices � utiliser dans pMATMatPassage
	Precondition :
		- le nombre de matrices dans pMATMatPassage doit �tre sup�rieur ou �gal � uiNbMatPassage
	Sortie :
		- CMatrice<CType> : le vecteur calcul� dans la derni�re base de pMATMatPassage
	Postconditions :
		- Le nouveau vecteur est retourn� OU
		- Erreur 3 : Tailles_Differentes, le vecteur ou les matrices de passages n'ont pas une taille correcte
	*/
	template<class CType>
	CMatrice<CType> OPMChangerBase(CMatrice<CType> MATVect, CMatrice<CType>* pMATMatPassage, unsigned int uiNbMatPassage);

};


#include "COperationsMatrice.cpp"