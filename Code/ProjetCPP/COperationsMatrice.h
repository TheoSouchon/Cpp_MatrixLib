#pragma once


class COperationsMatrice
{

public:

	/*
	Calacul la transposée d'une matrice
	Entree :
		- MAT1 : IN, matrice à transposer
	Precondition : /
	Sortie :
		- CMatrice<CType> : la transposée de MAT1
	Postconditions :
		- La transposée est retournée
	*/
	template<class CType>
	CMatrice<CType> OPMTransposer(CMatrice<CType> MAT1);

	/*
	Calacul le vecteur MATVect dans la dernière base de la liste des pMATMatPassage
	Entree :
		- MATVect : IN, Vecteur à changer de base, doit être de taille 1 ligne * n colonnes OU n lignes * 1 colonne
		- pMATMatPassage : IN, matrices de changement de base, doit contenir au moins uiNbMatPassage matrices chacune de taille n*n
		- uiNbMatPassage : IN, nombre de matrices à utiliser dans pMATMatPassage
	Precondition :
		- le nombre de matrices dans pMATMatPassage doit être supérieur ou égal à uiNbMatPassage
	Sortie :
		- CMatrice<CType> : le vecteur calculé dans la dernière base de pMATMatPassage
	Postconditions :
		- Le nouveau vecteur est retourné OU
		- Erreur 3 : Tailles_Differentes, le vecteur ou les matrices de passages n'ont pas une taille correcte
	*/
	template<class CType>
	CMatrice<CType> OPMChangerBase(CMatrice<CType> MATVect, CMatrice<CType>* pMATMatPassage, unsigned int uiNbMatPassage);

};


#include "COperationsMatrice.cpp"