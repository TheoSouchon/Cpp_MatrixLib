#include "COperationsMatrice.h"
#include "CMatrice.h"


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
CMatrice<CType> COperationsMatrice::OPMTransposer(CMatrice<CType> MAT1) {
	CMatrice<CType> MATTransposee(MAT1.MATLireNbColonnes(), MAT1.MATLireNbLignes());
	for (unsigned int uiLigne = 0; uiLigne < MAT1.MATLireNbLignes(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MAT1.MATLireNbColonnes(); uiColonne++) {
			MATTransposee.MATModifierElement(uiColonne, uiLigne, MAT1.MATLireElement(uiLigne, uiColonne));
		}
	}
	return MATTransposee;
}



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
CMatrice<CType> COperationsMatrice::OPMChangerBase(CMatrice<CType> MATVect, CMatrice<CType>* pMATMatPassage, unsigned int uiNbMatPassage) {
	bool bTanspose = false;
	// On vérifie si c'est bien un vecteur
	if (MATVect.MATLireNbLignes() != 1 && MATVect.MATLireNbColonnes() != 1) {
		throw CException(Tailles_Differentes);
	}
	// On vérifie le sens du vecteur
	else if (MATVect.MATLireNbLignes() != 1 && MATVect.MATLireNbColonnes() == 1) {
		MATVect = OPMTransposer(MATVect);
		bTanspose = true;
	}
	// On calcule le nouveau vecteur
	unsigned int uiNbElemVect = MATVect.MATLireNbColonnes();
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbMatPassage; uiBoucle++) {
		if (pMATMatPassage[uiBoucle].MATLireNbLignes() != uiNbElemVect || pMATMatPassage[uiBoucle].MATLireNbColonnes() != uiNbElemVect) {
			throw CException(Tailles_Differentes);
		}
		MATVect = MATVect * pMATMatPassage[uiBoucle];
	}
	// On return le vecteur
	if (bTanspose) {
		return OPMTransposer(MATVect);
	}
	return MATVect;
}


