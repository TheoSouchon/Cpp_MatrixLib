#include <iostream>
#include "CException.h"
#include "CLigne.h"
#include "CMatrice.h"
using std::cout;
using std::endl;
#include <fstream>
#include <string>
using namespace std;



// CONSTRUCTEURS ET DESTRUCTEUR

/*
Constructeur par d�fault, initialise le nombre de lignes et de colonnes � 1 et le pointeur sur la liste de lignes
Entree : /
Preconditions : /
Sortie : /
Postconditions :
	- L'objet est initialis� OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e 
*/
template<class CType>
CMatrice<CType>::CMatrice() {
	uiMATNbLignes = 1;
	uiMATNbColonnes = 1;
	ppLIGMATLignes = (CLigne<CType>**) malloc(uiMATNbLignes * sizeof(CLigne<CType>*));
	if (ppLIGMATLignes == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	ppLIGMATLignes[0] = new CLigne<CType>(1);
}



/*
Constructeur de confort, initialise la matrice pour qu'elle puisse stocker uiNbLignes * uiNbColonnes �l�ments
Entree :
	- uiNbLignes : IN, nombre de lignes (au moins 1)
	- uiNbColonnes : IN, nombre de colonnes (au moins 1)
Preconditions : /
Sortie : /
Postconditions :
	- L'objet est initialis� OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e OU
	- Erreur 5 : Taille_Insufisante, uiNbLignes ou uiNbColonnes vaux 0
*/
template<class CType>
CMatrice<CType>::CMatrice(unsigned int uiNbLignes, unsigned int uiNbColonnes) {
	if (uiNbLignes == 0 || uiNbColonnes == 0) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Taille_Insufisante);
		throw EXCErreur;
	}
	uiMATNbLignes = uiNbLignes;
	uiMATNbColonnes = uiNbColonnes;
	ppLIGMATLignes = (CLigne<CType>**) malloc(uiMATNbLignes * sizeof(CLigne<CType>*));
	if (ppLIGMATLignes == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++) {
		ppLIGMATLignes[uiBoucle] = new CLigne<CType>(uiMATNbColonnes);
	}
}

/*
Constructeur de confort, initialise la matrice avec les valeurs pass�es en param�tre (ou des valeurs par d�fault
	pour compl�ter si il manque des valeurs)
Entree :
	- uiNbLignes : IN, nombre de lignes (au moins 1)
	- uiNbColonnes : IN, nombre de colonnes (au moins 1)
	- ppTYPElements : IN, contient les valeurs � ins�rer dans la matrice
Preconditions :
	- ppTYPElements doit contenir uiNbLignes tableaux, chacun contenant uiNbColonnes �l�ments
Sortie : /
Postconditions :
	- L'objet est initialis� OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e OU
	- Erreur 5 : Taille_Insufisante, uiNbLignes ou uiNbColonnes vaux 0
*/
template<class CType>
CMatrice<CType>::CMatrice(unsigned int uiNbLignes, unsigned int uiNbColonnes, CType** ppTYPElements) {
	if (uiNbLignes == 0 || uiNbColonnes == 0) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Taille_Insufisante);
		throw EXCErreur;
	}
	uiMATNbLignes = uiNbLignes;
	uiMATNbColonnes = uiNbColonnes;
	ppLIGMATLignes = (CLigne<CType>**) malloc(uiMATNbLignes * sizeof(CLigne<CType>*));
	if (ppLIGMATLignes == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++) {
		ppLIGMATLignes[uiBoucle] = new CLigne<CType>(uiMATNbColonnes, ppTYPElements[uiBoucle]);
	}
}


/*
Constructeur utilisant un fichier pour initialiser la matrice
Entree : 
	- pcChemin : IN, chemin du fichier contenant la matrice
Preconditions : 
	- pcChemin n'est pas nullptr
Sortie : /
Postconditions :
	- L'objet est initialis� et contient les m�mes valeurs que celles du fichier OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e OU
	- Erreur 7 : Chemin_Incorrect, le chemin sp�cifi� est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
template<class CType>
CMatrice<CType>::CMatrice(char* pcChemin) {
	try {
		//on lit les attributs du fichiers
		int* piTabAttributMatrice = MATLireFichierAttribut(pcChemin);
		double** ppdTab = nullptr;
		if (piTabAttributMatrice != nullptr) {
			//on lit les �l�ments de la matrice du fichier
			ppdTab = MATLireFichierMatrice(piTabAttributMatrice[0], piTabAttributMatrice[1], pcChemin);
			if (ppdTab != nullptr) {
				//on cr�� la matrice et on la copie dans this
				*this = CMatrice<CType>(piTabAttributMatrice[0], piTabAttributMatrice[1], ppdTab);
			}
		}
	}
	catch (CException EXCCatchedEXC) {
		throw EXCCatchedEXC;
	}
}


/*
Constructeur de recopie pour une matrice stocant le m�me type d'objet
Entree :
	- MAT1 : IN, matrice � copier
Preconditions : /
Sortie : /
Postconditions :
	- L'objet est initialis� et contient les m�mes valeurs que MAT1 OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e
*/
template<class CType>
CMatrice<CType>::CMatrice(const CMatrice<CType>& MAT1) {
	uiMATNbLignes = MAT1.MATLireNbLignes();
	uiMATNbColonnes = MAT1.MATLireNbColonnes();
	ppLIGMATLignes = (CLigne<CType>**) malloc(uiMATNbLignes * sizeof(CLigne<CType>*));
	if (ppLIGMATLignes == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++) {
		ppLIGMATLignes[uiBoucle] = new CLigne<CType>(MAT1.MATLireLigne(uiBoucle));
	}
}


/*
Destructeur
Entree : /
Preconditions : /
Sortie : /
Postconditions :
	- Les CLignes de CMatrice sont d�sallou�
	- La CMatrice est lib�r�
*/
template<class CType>
CMatrice<CType>::~CMatrice() {
	//delete les �lements dans la liste
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++)
	{
		if (ppLIGMATLignes[uiBoucle] != nullptr) {
			delete ppLIGMATLignes[uiBoucle];
		}
	}
	//free la liste
	free(ppLIGMATLignes);
}


// GETTEURS ET SETTEURS



/*
Getteur d'une ligne, renvoie une copie de la ligne
Entree :
	- uiLigne : IN, index de la ligne � r�cup�rer
Preconditions : /
Sortie :
	- CType : Une copie de l'�l�ment voulu
Postconditions :
	- Une copie de l'objet est retourn� OU
	- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est sup�rieur au nombre de lignes ou de colonnes
*/
template<class CType>
CLigne<CType> CMatrice<CType>::MATLireLigne(unsigned int uiIndex) const {
	if (uiIndex > uiMATNbLignes) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	return *ppLIGMATLignes[uiIndex];
}

/*
Setteur d'une ligne, priv�
Entree :
	- uiLigne : IN, index de la ligne � r�cup�rer
	- LIG1 : IN, ligne � ins�rer
Preconditions : /
Sortie : /
Postconditions :
	- L'�l�ment � l'index uiIndex est modif� dans la ligne OU
	- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est sup�rieur au nombre de lignes ou de colonnes OU 
	- Erreur 3 : Tailles_Differentes, les matrices ne sont pas de m�me taille
*/
template<class CType>
void CMatrice<CType>::MATModifierLigne(unsigned int uiIndex, CLigne<CType> LIG1) {
	if (uiIndex > uiMATNbLignes) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	else if (LIG1.LIGLireTaile() != uiMATNbColonnes) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Tailles_Differentes);
		throw EXCErreur;
	}
	ppLIGMATLignes[uiIndex] = new CLigne<CType>(LIG1);
}


/*
Getteur d'un �l�ment de la matrice
Entree :
	- uiLigne : IN, index de la ligne de l'�l�ment � r�cup�rer
	- uiColonne : IN, index de la colonne de l'�l�ment � r�cup�rer
Preconditions : /
Sortie :
	- CType : Une copie de l'�l�ment voulu
Postconditions :
	- Une copie de l'objet est retourn� OU
	- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est sup�rieur au nombre de lignes ou de colonnes
*/
template<class CType>
CType CMatrice<CType>::MATLireElement(unsigned int uiLigne, unsigned int uiColonne) const {
	if (uiLigne > uiMATNbLignes || uiColonne > uiMATNbColonnes) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	return ppLIGMATLignes[uiLigne]->LIGLireElement(uiColonne);
}


/*
Setteur d'un �l�ment de la matrice
Entree :
	- uiLigne : IN, index de la ligne de l'�l�ment � modifier
	- uiColonne : IN, index de la colonne de l'�l�ment � modifier
	- TYPElement : IN, �l�ment � mettre dans la matrice
Preconditions : /
Sortie : /
Postconditions :
	- Une copie de l'objet est retourn� OU
	- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est sup�rieur au nombre de lignes ou de colonnes
*/
template<class CType>
void CMatrice<CType>::MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, CType TYPElement) {
	if (uiLigne > uiMATNbLignes || uiColonne > uiMATNbColonnes) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	ppLIGMATLignes[uiLigne]->LIGModifierElement(uiColonne, TYPElement);
}



/*
Ajoute une ligne � l'index sp�cifi� (ou � la fin par d�fault ou si l'index est sup�rieur au nombre de lignes de la matrice)
	contenant les valeurs pass�es en param�tre (ou des objets construits avec le contructeur par d�fault si
	aucun tableau n'est pass� en param�tre ou si celui-ci ne contient pas assez de valeurs pour la remplir enti�rement)
Entree :
	- uiIndex : IN, index o� ins�rer la ligne
	- pTYPValeurs : IN, tableau des valeurs � ins�rer
	- uiIndiceMax : IN, indice de la derni�re valeur du tableau � ins�rer dans la matrice
Preconditions : 
	- uiIndiceMax doit �tre inf�rieur au nombre d'�l�ments contenu dans le tableau
Sortie : /
Postconditions :
	- La ligne a �t� ins�r�e dans la matrice OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e
*/
template<class CType>
void CMatrice<CType>::MATAjouterLigne(unsigned int uiIndex, CType* pTYPValeurs, unsigned int uiIndiceMax) {
	if (uiIndex > uiMATNbLignes) {
		uiIndex = uiMATNbLignes;
	}
	//Ajout d'une ligne vide dans la Matrice
	CLigne<CType>** ppTYPTmp = nullptr;
	ppTYPTmp = (CLigne<CType>**)realloc(ppLIGMATLignes, (uiMATNbLignes + 1) * sizeof(CLigne<CType>*));
	if (ppTYPTmp == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	//d�calage
	unsigned int uiBoucle;
	for (uiBoucle = uiMATNbLignes; uiBoucle > uiIndex; uiBoucle--) {
		ppTYPTmp[uiBoucle] = ppTYPTmp[uiBoucle - 1];
	}
	// Insertion de la nouvelle ligne et de ses valeurs
	uiMATNbLignes++;
	ppTYPTmp[uiIndex] = new CLigne<CType>(uiMATNbColonnes);
	ppLIGMATLignes = ppTYPTmp;
	for (uiBoucle = 0; uiBoucle <= uiIndiceMax && uiBoucle < uiMATNbColonnes; uiBoucle++) {
		ppLIGMATLignes[uiIndex]->LIGModifierElement(uiBoucle, pTYPValeurs[uiBoucle]);
	}
}


/*
Supprime une ligne � l'index sp�cifi�
Entree :
	- uiIndex : IN, index de la ligne � supprimer
Preconditions : /
Sortie : /
Postconditions :
	- La ligne a �t� retir�e de la matrice OU
	- Erreur 1 : Index_Incorect, l'index est sup�rieur au nombre de lignes de la matrice OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e
*/
template<class CType>
void CMatrice<CType>::MATSupprimerLigne(unsigned int uiIndex) {
	if (uiIndex > uiMATNbLignes) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	//D�placement des �l�ments
	delete ppLIGMATLignes[uiIndex];
	for (unsigned int uiBoucle = uiIndex; uiBoucle < uiMATNbLignes - 1; uiBoucle++) {
		ppLIGMATLignes[uiBoucle] = ppLIGMATLignes[uiBoucle + 1];
	}

	// R�alocation
	CLigne<CType>** ppTYPTmp = nullptr;
	ppTYPTmp = (CLigne<CType>**)realloc(ppLIGMATLignes, (uiMATNbLignes - 1) * sizeof(CLigne<CType>*));
	if (ppTYPTmp == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	uiMATNbLignes--;
	ppLIGMATLignes = ppTYPTmp;
}



/*
Ajoute une colonne � l'index sp�cifi� (ou � la fin par d�fault ou si l'index est sup�rieur au nombre de colonnes de la matrice)
	contenant les valeurs pass�es en param�tre (ou des objets construits avec le contructeur par d�fault si
	aucun tableau n'est pass� en param�tre ou si celui-ci ne contient pas assez de valeurs pour la remplir enti�rement)
Entree :
	- uiIndex : IN, index o� ins�rer la colonne
	- pTYPValeurs : IN, tableau des valeurs � ins�rer
	- uiIndiceMax : IN, indice de la derni�re valeur du tableau � ins�rer dans la matrice
Preconditions :
	- uiIndiceMax doit �tre inf�rieur au nombre d'�l�ments contenu dans le tableau
Sortie : /
Postconditions :
	- La colonne a �t� ins�r�e dans la matrice OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e
*/
template<class CType>
void CMatrice<CType>::MATAjouterColonne(unsigned int uiIndex, CType* pTYPValeurs, unsigned int uiIndiceMax) {
	if (uiIndex > uiMATNbLignes) {
		uiIndex = uiMATNbLignes;
	}
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLignes; uiLigne++) {
		if (uiLigne <= uiIndiceMax) {
			ppLIGMATLignes[uiLigne]->LIGAjouterElement(uiIndex, pTYPValeurs[uiLigne]);
		}
		else {
			ppLIGMATLignes[uiLigne]->LIGAjouterElement(uiIndex);
		}
	}
}


/*
Supprime une colonne � l'index sp�cifi�
Entree :
	- uiIndex : IN, indice de la colonne � supprimer
Preconditions : /
Sortie : /
Postconditions :
	- La ligne a �t� retir�e de la matrice OU
	- Erreur 1 : Index_Incorect, l'index est sup�rieur au nombre de lignes de la matrice OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e
*/
template<class CType>
void CMatrice<CType>::MATSupprimerColonne(unsigned int uiIndex) {
	if (uiIndex > uiMATNbLignes) {
		uiIndex = uiMATNbLignes;
	}
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLignes; uiLigne++) {
		ppLIGMATLignes[uiLigne]->LIGSupprimerElement(uiIndex);
	}
}



// OPERATEURS

/* Operateur = entre 2 matrices du m�me type*/
template<class CType>
CMatrice<CType> CMatrice<CType>::operator=(CMatrice<CType> MAT1) {
	// Destruction de la matrice actuelle
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++)
	{
		if (ppLIGMATLignes[uiBoucle] != nullptr) {
			delete ppLIGMATLignes[uiBoucle];
		}
	}
	free(ppLIGMATLignes);
	// Recopie de la matrice
	uiMATNbLignes = MAT1.MATLireNbLignes();
	uiMATNbColonnes = MAT1.MATLireNbColonnes();
	ppLIGMATLignes = (CLigne<CType>**) malloc(uiMATNbLignes * sizeof(CLigne<CType>*));
	if (ppLIGMATLignes == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++) {
		ppLIGMATLignes[uiBoucle] = new CLigne<CType>(*MAT1.ppLIGMATLignes[uiBoucle]);
	}
	return *this;
}


/*
Op�rateur + entre 2 matrices de m�mes tailles
Entree :
	- MAT1 : IN, Matrice contenant les valeurs � additionner
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur + pour un objet de type CType2
Sortie :
	- CMatrice<CType> : La matrice contenant l'addition de l'objet courant et de MAT1
Postconditions :
	- La matrice revoy�e contient la somme de l'objet courant et de MAT1 OU
	- Erreur 3 : Tailles_Differentes, les matrices ne sont pas de m�me taille
*/
template<class CType>
template<class CType2>
CMatrice<CType> CMatrice<CType>::operator+(CMatrice<CType2> MAT1) const{
	if (uiMATNbLignes != MAT1.MATLireNbLignes() || uiMATNbColonnes != MAT1.MATLireNbColonnes()) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Tailles_Differentes);
		throw EXCErreur;
	}
	CMatrice<CType> MATSomme(uiMATNbLignes, uiMATNbColonnes);
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++) {
		delete (MATSomme.ppLIGMATLignes[uiBoucle]);
		MATSomme.ppLIGMATLignes[uiBoucle] = new CLigne<CType>(*(ppLIGMATLignes[uiBoucle]) + MAT1.MATLireLigne(uiBoucle));
	}
	return MATSomme;
}



/*
Op�rateur - entre 2 matrices de m�mes tailles
Entree :
	- MAT1 : IN, Matrice contenant les valeurs � soustraire
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur - pour un objet de type CType2
Sortie :
	- CMatrice<CType> : La matrice contenant la diff�rence de l'objet courant et de MAT1
Postconditions :
	- La matrice revoy�e contient la diff�rence de l'objet courant et de MAT1 OU
	- Erreur 3 : Tailles_Differentes, les matrices ne sont pas de m�me taille
*/
template<class CType>
template<class CType2>
CMatrice<CType> CMatrice<CType>::operator-(CMatrice<CType2> MAT1) const {
	if (uiMATNbLignes != MAT1.MATLireNbLignes() || uiMATNbColonnes != MAT1.MATLireNbColonnes()) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Tailles_Differentes);
		throw EXCErreur;
	}
	CMatrice<CType> MATDifference(uiMATNbLignes, uiMATNbColonnes);
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++) {
		MATDifference.ppLIGMATLignes[uiBoucle] = new CLigne<CType>(*(ppLIGMATLignes[uiBoucle]) - MAT1.MATLireLigne(uiBoucle));
	}
	return MATDifference;
}


/*
Op�rateur * entre 2 matrices avec MAT1 poss�dant autant de lignes que
	l'objet courrant poss�de de colonnes
Entree :
	- MAT1 : IN, Matrice contenant les valeurs � multiplier � l'objet courant
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur * pour un objet de type CType2
Sortie :
	- CMatrice<CType> : La matrice contenant la multiplication de l'objet courant et de MAT1
Postconditions :
	- La ligne revoy�e contient la multiplication de l'obet courant et MAT1 OU
	- Erreur 3 : Tailles_Differentes, l'objet courant n'a pas autant de colonnes que MAT1 a de lignes
*/
template<class CType>
template<class CType2>
CMatrice<CType> CMatrice<CType>::operator*(CMatrice<CType2> MAT1) const {
	if (uiMATNbColonnes != MAT1.MATLireNbLignes()) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Tailles_Differentes);
		throw EXCErreur;
	}
	CMatrice<CType> MATProduit(uiMATNbLignes, MAT1.MATLireNbColonnes());
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLignes; uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MAT1.MATLireNbColonnes(); uiColonne++) {
			CType* TYPSomme = new CType();
			for (unsigned int uiIndex = 0; uiIndex < uiMATNbColonnes; uiIndex++) {
				*TYPSomme = *TYPSomme + (MATLireElement(uiLigne, uiIndex) * MAT1.MATLireElement(uiIndex, uiColonne));
			}
			MATProduit.MATModifierElement(uiLigne, uiColonne, *TYPSomme);
		}
	}
	return MATProduit;
}


/* Operateur * entre une matrice et un nombre
Entree :
	- dFacteur : IN, facteur
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur * pour un nombre
Sortie :
	- CMatrice<CType> : La matrice contenant la multiplication de l'objet courant par dFacteur
Postconditions :
	- La mtrice revoy�e contient la multiplication de l'objet courant par dFacteur
*/
template<class CType>
CMatrice<CType> CMatrice<CType>::operator*(double dFacteur) const {
	CMatrice<CType> MATProduit(*this);
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLignes; uiLigne++) {
		MATProduit.MATModifierLigne(uiLigne, MATProduit.MATLireLigne(uiLigne) * dFacteur);
	}
	return MATProduit;
}


/* Operateur / entre une matrice et un nombre
Entree :
	- dDiviseur : IN, diviseur
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur / pour un nombre
Sortie :
	- CMatrice<CType> : La matrice contenant la division de l'objet courant par dDiviseur
Postconditions :
	- La matrice revoy�e contient la division de l'objet courant et dDiviseur OU
	- Erreur 4 : Division_Par_Zero, dDiviseur vaux 0
*/
template<class CType>
CMatrice<CType> CMatrice<CType>::operator/(double dDiviseur) const {
	if (dDiviseur == 0) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Division_Par_Zero);
		throw EXCErreur;
	}
	CMatrice<CType> MATQuotient(*this);
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLignes; uiLigne++) {
		MATQuotient.MATModifierLigne(uiLigne, MATQuotient.MATLireLigne(uiLigne) / dDiviseur);
	}
	return MATQuotient;
}



// AUTRES METHODES


/* 
Affiche les �l�ments d'une matrice dans la console
Entree : /
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur <<
Sortie : /
Postconditions :
	- La matrice est affich�e dans la console
*/
template<class CType>
void CMatrice<CType>::MATAfficher() const
{

	printf("[\n");
	for (unsigned int uiBoucle = 0; uiBoucle < uiMATNbLignes; uiBoucle++)
	{
		ppLIGMATLignes[uiBoucle]->LIGAfficherLigne();
	}
	printf("]\n");
}





/* Operateur * entre un nombre et une matrice
Entree :
	- dFacteur : IN, nombre facteur
	- MAT1 : IN, matrice facteur
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur * pour un nombre
Sortie :
	- CMatrice<CType> : La matrice contenant la multiplication de l'objet courant par dFacteur
Postconditions :
	- La mtrice revoy�e contient la multiplication de l'objet courant par dFacteur
*/
template<class CType>
CMatrice<CType> operator*(double dFacteur, const CMatrice<CType>& MAT1) {
	return MAT1 * dFacteur;
}





// FONCTIONS DU PARSEUR



/*
Sous-m�thode du parseur pour la ligne du type d'une matrice
Entree :
	- pcNomFichier : IN, nom du fichier � ouvrir et tester
Preconditions : 
	- pcNomFichier n'est pas null
Sortie :
	- True si la ligne est de la bonne syntaxe
Postconditions :
	- True est renvoy� OU
	- Erreur 6 : Type_Incorrect, le type sp�cifi� dans le fichier n'est pas double OU
	- Erreur 7 : Chemin_Incorrect, le chemin sp�cifi� est incorrect
*/
bool MATlireFichierTypeDouble(char* pcNomFichier)
{
	CException EXCErreur;
	std::ifstream MonFichier(pcNomFichier);
	char cLigne[255];
	if (!MonFichier.is_open()) {
		EXCErreur.EXCSetValeur(Chemin_Incorrect);
		throw EXCErreur;
	}
	MonFichier.getline(cLigne, sizeof(cLigne));
	for (unsigned int uiBoucle = 0; uiBoucle < 255; uiBoucle++) {
		if (cLigne[uiBoucle] == 32) {
			cLigne[uiBoucle] = 0;
		}
	}
	if (strcmp(cLigne, "TypeMatrice=double") == 0) {
		return true;
	}
	else {
		EXCErreur.EXCSetValeur(Type_incorrect);
		throw EXCErreur;
	}
}


/*
Sous-m�thode du parseur pour lire le nombre de ligne
Entree :
	- pcNomFichier : IN, nom du fichier � ouvrir et tester
Preconditions : 
	- pcNomFichier n'est pas null
Sortie :
	- iNum : le nombre de ligne indiqu� dans le fichier
Postconditions :
	- iNum est renvoy� et correspond au nombre au nombre lu et test� de la ligne OU
	- Erreur 7 : Chemin_Incorrect, le chemin sp�cifi� est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
int MATLireFichierNbLigne(char* pcNomFichier)
{
	CException EXCErreur;
	std::ifstream MonFichier(pcNomFichier);
	char cLigne[255];
	if (!MonFichier.is_open()) {
		EXCErreur.EXCSetValeur(Chemin_Incorrect);
		throw EXCErreur;
	}

	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.getline(cLigne, sizeof(cLigne), '=');
	if (strcmp(cLigne, "NBLignes") != 0) {
		EXCErreur.EXCSetValeur(Syntaxe_Incorrecte);
		throw EXCErreur;
	}
	MonFichier.getline(cLigne, sizeof(cLigne), '\n');
	for (unsigned int uiBoucle = 0; uiBoucle < 255; uiBoucle++) {
		if (cLigne[uiBoucle] == 32) {
			cLigne[uiBoucle] = 0;
		}
	}
	int iNum = 0;
	try {
		iNum = stoi(cLigne);
	}
	catch (...) {
		EXCErreur.EXCSetValeur(Syntaxe_Incorrecte);
		throw EXCErreur;
	}
	return iNum;
}

/*
Sous-m�thode du parseur pour lire le nombre de colonne
Entree :
	- pcNomFichier : IN, nom du fichier � ouvrir et tester
Preconditions : 
	- pcNomFichier n'est pas null
Sortie :
	- iNum : le nombre de colonne indiqu� dans le fichier
Postconditions :
	- iNum est renvoy� et correspond au nombre de colonnes lu et test� de la ligne OU
	- Erreur 7 : Chemin_Incorrect, le chemin sp�cifi� est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
int MATLireFichierNbColonne(char* pcNomFichier)
{
	CException EXCErreur;
	std::ifstream MonFichier(pcNomFichier);
	char cLigne[255];
	if (!MonFichier.is_open()) {
		EXCErreur.EXCSetValeur(Chemin_Incorrect);
		throw EXCErreur;
	}

	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.getline(cLigne, sizeof(cLigne), '=');
	if (strcmp(cLigne, "NBColonnes") != 0) {
		EXCErreur.EXCSetValeur(Syntaxe_Incorrecte);
		throw EXCErreur;
	}

	MonFichier.getline(cLigne, sizeof(cLigne), '\n');
	for (unsigned int uiBoucle = 0; uiBoucle < 255; uiBoucle++) {
		if (cLigne[uiBoucle] == 32) {
			cLigne[uiBoucle] = 0;
		}
	}

	int iNum = 0;
	try {
		iNum = stoi(cLigne);
	}
	catch (...) {
		EXCErreur.EXCSetValeur(Syntaxe_Incorrecte);
		throw EXCErreur;
	}
	return iNum;
}

/*
Sous-m�thode du parseur pour lire la syntaxe de l'encapsualtion de la matrice
Entree :
	- pcNomFichier : IN, nom du fichier � ouvrir et tester
	- uiNbLigne : IN, nombre de ligne lu auparavant
Preconditions : 
	- pcNomFichier n'est pas null
Sortie :
	- true : la syntaxe est correcte
Postconditions :
	- True est renvoy� OU
	- Erreur 7 : Chemin_Incorrect, le chemin sp�cifi� est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
bool MATLireFichierSyntaxMatrice(unsigned int uiNbLigne, char* pcNomFichier) {
	std::ifstream MonFichier(pcNomFichier);
	char cLigne[255];
	CException EXCErreur;

	if (!MonFichier.is_open()) {
		EXCErreur.EXCSetValeur(Chemin_Incorrect);
		throw EXCErreur;
	}
	
	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.getline(cLigne, sizeof(cLigne));
	for (unsigned int uiBoucle = 0; uiBoucle < 255; uiBoucle++) {
		if (cLigne[uiBoucle] == 32) {
			cLigne[uiBoucle] = 0;
		}
	}
	if (strcmp(cLigne, "Matrice=[") != 0) {
		EXCErreur.EXCSetValeur(Syntaxe_Incorrecte);
		throw EXCErreur;
	}

	for (unsigned int uiBoucle2 = 0; uiBoucle2 < uiNbLigne; uiBoucle2++) {
		MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	MonFichier.getline(cLigne, sizeof(cLigne));
	for (unsigned int uiBoucle = 0; uiBoucle < 255; uiBoucle++) {
		if (cLigne[uiBoucle] == 32) {
			cLigne[uiBoucle] = 0;
		}
	}

	if (strcmp(cLigne, "]") != 0) {
		EXCErreur.EXCSetValeur(Syntaxe_Incorrecte);
		throw EXCErreur;
	}
	return true;
}


/*
M�thode du parseur pour lire et v�rifier les lignes autres que le contenu de la matrice
Entree :
	- pcNomFichier : nom du fichier � ouvrir et tester
Preconditions :
	- pcNomFichier n'est pas null
Sortie :
	- piTabAttributMatrice : tableau dynamique d'entier
Postconditions :
	- piTabAttributMatrice[0] et [1} correspondent respectivements au nombre de lignes et de colonnes de la matrice OU
	- Erreur 2 : Pointeur_Null, une allocation de m�moire a �chou�e OU
	- Erreur 7 : Chemin_Incorrect, le chemin sp�cifi� est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
int* MATLireFichierAttribut(char* pcNomFichier)
{
	CException EXCErreur;
	int* piTabAttributMatrice;
	piTabAttributMatrice = (int*) malloc(2 * sizeof(int));
	if (piTabAttributMatrice == nullptr) {
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	try {
		//check syntax en-t�te
		MATlireFichierTypeDouble(pcNomFichier);
		piTabAttributMatrice[0] = MATLireFichierNbLigne(pcNomFichier);
		piTabAttributMatrice[1] = MATLireFichierNbColonne(pcNomFichier);
		MATLireFichierSyntaxMatrice(piTabAttributMatrice[0], pcNomFichier);
	}
	catch (CException EXCCatchedExc) {
		throw EXCCatchedExc;
	}
	return piTabAttributMatrice;

}


//Tronque la plage d'�l�ments de la matrice selon le nombre de ligne (m�me si il y a d'autres �l�ments dans le fichier)
/*
M�thode du parseur pour lire le contenu de la matrice
Entree :
	- uiNbLigne : IN, nombre de ligne lu auparavant
	- uiNbCol : IN, nombre de colonne lu auparavant
	- pcNomFichier : IN, nom du fichier � ouvrir et tester
Preconditions :
	- pcNomFichier n'est pas null
Sortie :
	- double** : tableau � 2 dimensions contenant les valeurs de la matrice contenues dans le fichier
Postconditions :
	- le tableau � 2 dimensions est retourn� avec les valeurs de la matrice OU
	- Erreur 2 : Pointeur_Null, une allocation de m�moire a �chou�e OU
	- Erreur 7 : Chemin_Incorrect, le chemin sp�cifi� est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture ou il manque des �l�ments dans le fichier pour cr�er la matrice
*/
double** MATLireFichierMatrice(unsigned int uiNbLigne, unsigned int uiNbCol, char* pcNomFichier)
{
	CException EXCErreur;
	std::ifstream MonFichier(pcNomFichier);
	char cLigne[255];

	if (!MonFichier.is_open()) {
		EXCErreur.EXCSetValeur(Chemin_Incorrect);
		throw EXCErreur;
	}

	//init variable m�moire
	double** ppdTabVal = (double**)malloc(1 * sizeof(double*)); //1 ligne
	if (ppdTabVal == nullptr) {
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	ppdTabVal[0] = (double*)malloc(1 * sizeof(double)); //1 colonne � la ligne 1
	if (ppdTabVal[0] == nullptr) {
		free(ppdTabVal);
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	


	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	MonFichier.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//pour chaque ligne
	for (unsigned int uiBoucle = 0; uiBoucle < uiNbLigne; uiBoucle++)
	{
		//augmente la taille en ligne de notre matrice de double en cons�quence
		if (uiBoucle != 0) {
			ppdTabVal = (double**)realloc(ppdTabVal, (uiBoucle + 1) * sizeof(double*));
			if (ppdTabVal == nullptr) {
				EXCErreur.EXCSetValeur(Pointeur_Null);
				throw EXCErreur;
			}
			//init colonne
			ppdTabVal[uiBoucle] = (double*)malloc(1 * sizeof(double));
			if (ppdTabVal[uiBoucle] == nullptr) {
				for (unsigned int uiBoucle3 = 0; uiBoucle3 < uiBoucle; uiBoucle3++) {
					free(ppdTabVal[uiBoucle]);
				}
				free(ppdTabVal);
				EXCErreur.EXCSetValeur(Pointeur_Null);
				throw EXCErreur;
			}
		}


		//pour chaque colonne
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < uiNbCol; uiBoucle2++)
		{
			//augmente la taille en colonne de notre matrice de double en cons�quence
			if (uiBoucle2 != 0) {
				ppdTabVal[uiBoucle] = (double*)realloc(ppdTabVal[uiBoucle], (uiBoucle2 + 1) * sizeof(double));
				if (ppdTabVal[uiBoucle] == nullptr) {
					for (unsigned int uiBoucle3 = 0; uiBoucle3 < uiBoucle; uiBoucle3++) {
						free(ppdTabVal[uiBoucle]);
					}
					free(ppdTabVal);
					EXCErreur.EXCSetValeur(Pointeur_Null);
					throw EXCErreur;
				}
			}

			//on lit le premier �l�ment
			if (uiBoucle2 < (uiNbCol - 1)) {
				MonFichier.getline(cLigne, sizeof(cLigne), ' ');
			}
			else {
				MonFichier.getline(cLigne, sizeof(cLigne), '\n');
				for (unsigned int uiBoucle3 = 0; uiBoucle3 < 200; uiBoucle3++)
				{
					if (cLigne[uiBoucle3] == 32) cLigne[uiBoucle3] = 0;
				}

			}
			double dTemp = 0;
			try {
				dTemp = stod(cLigne);
			}
			catch (...) {
				printf("Erreur syntax sur les lignes des elements la matrice\n");

				for (unsigned int uiBoucle3 = 0; uiBoucle3 < uiBoucle; uiBoucle3++)
				{
					free(ppdTabVal[uiBoucle3]);
				}
				free(ppdTabVal);
				EXCErreur.EXCSetValeur(Syntaxe_Incorrecte);
				throw EXCErreur;
			}
			ppdTabVal[uiBoucle][uiBoucle2] = dTemp;

		}

	}

	return ppdTabVal;
}
