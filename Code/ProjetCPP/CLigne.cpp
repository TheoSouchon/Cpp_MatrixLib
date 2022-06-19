#include <iostream>
#include "CLigne.h"
#include "CException.h"


// CONSTRUCTEURS ET DESTRUCTEUR

/*
Constructeur par d�fault, initialise la taille � 0 et le pointeur sur la liste d'�l�ments � NULL
Entree : /
Preconditions : /
Sortie : /
Postconditions :
	- L'objet est initialis�
*/
template<class CType>
CLigne<CType>::CLigne() 
{
	uiLIGTaille = 0;
	ppTYPLIGListeElement = nullptr;
}

/*
Constructeur de confort, initialise la ligne pour qu'elle puisse stocker uiTaille �l�ments
Entree :
	- uiTaille : IN, taille de la ligne
Preconditions : /
Sortie : /
Postconditions :
	- L'objet est initialis� OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e
*/
template<class CType>
CLigne<CType>::CLigne(unsigned int uiTaille)
{
	uiLIGTaille = uiTaille;
	ppTYPLIGListeElement = (CType**) malloc(uiLIGTaille * sizeof(CType*));
	if (ppTYPLIGListeElement == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++) {
		ppTYPLIGListeElement[uiBoucle] = new CType();
	}
}


/*
Constructeur de confort, initialise la ligne avec la liste d'�l�ments pass�e en param�tre
Entree :
	- uiTaille : IN, taille de la ligne
	- pTYPElements : IN, liste des �l�ments � ins�rer dans la ligne
Preconditions :
	- Il y a au moins uiTaille �l�ments dans pTYPElements
Sortie : /
Postconditions :
	- L'objet est initialis� OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e
*/
template<class CType>
CLigne<CType>::CLigne(unsigned int uiTaille, CType* pTYPElements) {
	uiLIGTaille = uiTaille;
	ppTYPLIGListeElement = (CType**)malloc(uiLIGTaille * sizeof(CType*));
	if (ppTYPLIGListeElement == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++) {
		ppTYPLIGListeElement[uiBoucle] = new CType(pTYPElements[uiBoucle]);
	}
}


/*
Constructeur de recopie
Entree : /
Preconditions : /
Sortie : /
Postconditions :
	- L'objet est initialis� et contient les m�mes valeurs que LIG1 OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e
*/
template<class CType>
CLigne<CType>::CLigne(const CLigne<CType>& LIG1)
{
	uiLIGTaille = LIG1.uiLIGTaille;
	ppTYPLIGListeElement = (CType**) malloc(uiLIGTaille * sizeof(CType*));
	if (ppTYPLIGListeElement == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++) {
		ppTYPLIGListeElement[uiBoucle] = new CType(LIG1.LIGLireElement(uiBoucle));
	}
}



/* Destructeur*/
template<class CType>
CLigne<CType>::~CLigne()
{
	//delete les �lements dans la liste
	for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++)
	{
		if (ppTYPLIGListeElement[uiBoucle] != nullptr) {
			delete ppTYPLIGListeElement[uiBoucle];
		}
	}
	//free la liste
	free(ppTYPLIGListeElement);
	
}



// GETTEURS ET SETTEURS


/*
Getteur d'�l�ment dans la ligne
Entree :
	- uiIndex : IN, index de l'�l�ment � r�cup�rer
Precondition : /
Sortie :
	- CType : Copie de l'�l�ment � l'index uiIndex
Postconditions :
	- Une copie de l'�l�ment � l'index uiIndex est retourn� OU
	- Erreur 1 : Index_Incorect : L'index pass� en param�tre est plus grand que la taille de la ligne OU
	- Erreur 2 : Pointeur_Null : Le pointeur sur lequel on veut effectuer des op�rations est nullptr
*/
template<class CType>
CType CLigne<CType>::LIGLireElement(unsigned int uiIndex) const {
	if (uiIndex >= uiLIGTaille) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	else if (ppTYPLIGListeElement == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	return *ppTYPLIGListeElement[uiIndex];
}



/*
Ajoute un �l�ment dans la ligne � l'index sp�cifi� (ou � la fin de la ligne par d�faut ou si l'index est plus grand que la taille de la ligne)
Entree :
	- uiIndex : IN, index de l'�l�ment � r�cup�rer (d�faut = uiLIGTaille
	- TYPElement : IN, �l�ment � ajouter (d�faut = nouvel ojet construit avec le contructeur par d�faut)
Precondition : /
Sortie : /
Postconditions :
	- L'�l�ment est ajout� � l'index sp�cifi� OU
	- Erreur 2 : Pointeur_Null : Le pointeur sur lequel on veut effectuer des op�rations est nullptr (erreur d'allocation)
*/
template<class CType>
void CLigne<CType>::LIGAjouterElement(unsigned int uiIndex, CType TYPElement)
{
	if (uiIndex > uiLIGTaille) {
		uiIndex = uiLIGTaille;
	}
	// R�alocation
	CType** ppTYPTmp = nullptr;
	ppTYPTmp = (CType**) realloc(ppTYPLIGListeElement, (uiLIGTaille + 1) * sizeof(CType*));
	if (ppTYPTmp == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	//D�placement des �l�ments
	for (unsigned int uiBoucle = uiLIGTaille; uiBoucle > uiIndex; uiBoucle--) {
		ppTYPTmp[uiBoucle] = ppTYPTmp[uiBoucle-1];
	}
	ppTYPTmp[uiIndex] = new CType(TYPElement);
	uiLIGTaille++;
	ppTYPLIGListeElement = ppTYPTmp;
}


/*
Supprime un �l�ment dans la ligne � l'index sp�cifi�
Entree :
	- uiIndex : IN, index de l'�l�ment � suprimer
Precondition : /
Sortie : /
Postconditions :
	- L'�l�ment � l'index sp�cifi� est suprim� OU
	- Erreur 1 : Index_Incorect : L'index pass� en param�tre est plus grand que la taille de la ligne OU
	- Erreur 2 : Pointeur_Null : Le pointeur sur lequel on veut effectuer des op�rations est nullptr (erreur d'allocation)
*/
template<class CType>
void CLigne<CType>::LIGSupprimerElement(unsigned int uiIndex)
{
	if (uiIndex > uiLIGTaille) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	//D�placement des �l�ments
	delete ppTYPLIGListeElement[uiIndex];
	for (unsigned int uiBoucle = uiIndex; uiBoucle < uiLIGTaille - 1; uiBoucle++) {
		ppTYPLIGListeElement[uiBoucle] = ppTYPLIGListeElement[uiBoucle + 1];
	}
	// R�alocation
	CType** ppTYPTmp = nullptr;
	ppTYPTmp = (CType**)realloc(ppTYPLIGListeElement, (uiLIGTaille - 1) * sizeof(CType*));
	if (ppTYPTmp == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	uiLIGTaille--;
	ppTYPLIGListeElement = ppTYPTmp;
}


/*
Modifie un �l�ment dans la ligne � l'index sp�cifi�
Entree :
	- uiIndex : IN, index de l'�l�ment � r�cup�rer
	- TYPElement : IN, �l�ment � ajouter
Precondition : /
Sortie : /
Postconditions :
	- L'�l�ment est ajout� � l'index sp�cifi� OU
	- Erreur 1 : Index_Incorect : L'index pass� en param�tre est plus grand que la taille de la ligne
*/
template<class CType>
void CLigne<CType>::LIGModifierElement(unsigned int uiIndex, CType TYPElement)
{
	if (uiIndex > uiLIGTaille) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	ppTYPLIGListeElement[uiIndex] = new CType(TYPElement);
}



/*
Op�rateur = entre 2 lignes stockant le m�me type d'objets
Entree :
	- LIG1 : IN, ligne � copier
Precondition : /
Sortie :
	- CLigne<CType> : l'objet courrant, qui contient les m�mes valeurs que LIG1
Postconditions :
	- L'objet courrant contient les m�mes valeurs que LIG1 et est renvoy� OU
	- Erreur 2 : Pointeur_Null : Le pointeur sur lequel on veut effectuer des op�rations est nullptr (erreur d'allocation)
*/
template<class CType>
CLigne<CType> CLigne<CType>::operator=(CLigne<CType> LIG1)
{
	// Destruction des objets actuellement dans la ligne et d�sallocation du tableau d'�l�ments
	if (ppTYPLIGListeElement != nullptr) {
		for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++)
		{
			delete ppTYPLIGListeElement[uiBoucle];
		}
		free(ppTYPLIGListeElement);
	}
	//Initialisation de la ligne
	uiLIGTaille = LIG1.uiLIGTaille;
	ppTYPLIGListeElement = (CType**) malloc(uiLIGTaille * sizeof(CType*));
	if (ppTYPLIGListeElement == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++) {
		ppTYPLIGListeElement[uiBoucle] = new CType(LIG1.LIGLireElement(uiBoucle));
	}
	return *this;
}



/*
Op�rateur + entre 2 lignes de m�me taille
Entree :
	- LIG1 : IN, Ligne contenant les valeurs � additionner � celles de l'objet courant
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur + pour un objet de m�me type
Sortie :
	- CLigne<CType> : La ligne contenant l'addition de l'objet courant et de LIG1
Postconditions :
	- La ligne revoy�e contient l'addition de l'objet courant et de LIG1 OU
	- Erreur 3 : Tailles_Differentes, les lignes ne sont pas de m�me taille
*/
template<class CType>
template<class CType2>
CLigne<CType> CLigne<CType>::operator+(CLigne<CType2> LIG1) const {
	if (uiLIGTaille != LIG1.LIGLireTaile()) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Tailles_Differentes);
		throw EXCErreur;
	}
	CLigne<CType> LIGSomme(uiLIGTaille);
	for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++) {
		LIGSomme.LIGModifierElement(uiBoucle, LIGLireElement(uiBoucle) + LIG1.LIGLireElement(uiBoucle));
	}
	return LIGSomme;
}


/*
Op�rateur - entre 2 lignes de m�me taille
Entree :
	- LIG1 : IN, Ligne contenant les valeurs � soustraire � l'objet courant
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur - pour un objet de type CType2
Sortie :
	- CLigne<CType> : La ligne contenant la diff�rence de l'objet courant et de LIG1
Postconditions :
	- La ligne revoy�e contient la diff�rence de l'objet courant et LIG1 OU
	- Erreur 3 : Tailles_Differentes, les lignes ne sont pas de m�me taille
*/
template<class CType>
template<class CType2>
CLigne<CType> CLigne<CType>::operator-(CLigne<CType2> LIG1) const {
	if (uiLIGTaille != LIG1.LIGLireTaile()) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Tailles_Differentes);
		throw EXCErreur;
	}
	CLigne<CType> LIGDifference(uiLIGTaille);
	for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++) {
		LIGDifference.LIGModifierElement(uiBoucle, LIGLireElement(uiBoucle) - LIG1.LIGLireElement(uiBoucle));
	}
	return LIGDifference;
}


/* Operateur * entre une ligne et un nombre
Entree :
	- dFacteur : IN, facteur
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur * pour un nombre
Sortie :
	- CLigne<CType> : La ligne contenant la multiplication de l'objet courant par dFacteur
Postconditions :
	- La ligne revoy�e contient la multiplication de l'objet courant par dFacteur
*/
template<class CType>
CLigne<CType> CLigne<CType>::operator*(double dFacteur) const {
	CLigne<CType> LIGProduit(*this);
	for (unsigned int uiIndex = 0; uiIndex < uiLIGTaille; uiIndex++) {
		LIGProduit.LIGModifierElement(uiIndex, LIGProduit.LIGLireElement(uiIndex) * dFacteur);
	}
	return LIGProduit;
}


/* Operateur / entre une ligne et un nombre
Entree :
	- dDiviseur : IN, diviseur
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur / pour un nombre
Sortie :
	- CLigne<CType> : La ligne contenant la division de l'objet courant par dDiviseur
Postconditions :
	- La ligne revoy�e contient la multiplication de l'obet courant et dDiviseur OU
	- Erreur 4 : Division_Par_Zero, dDiviseur vaux 0
*/
template<class CType>
CLigne<CType> CLigne<CType>::operator/(double dDiviseur) const {
	if (dDiviseur == 0) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Division_Par_Zero);
		throw EXCErreur;
	}
	CLigne<CType> LIGQuotient(*this);
	for (unsigned int uiIndex = 0; uiIndex < uiLIGTaille; uiIndex++) {
		LIGQuotient.LIGModifierElement(uiIndex, LIGQuotient.LIGLireElement(uiIndex) / dDiviseur);
	}
	return LIGQuotient;
}


// AUTRES METHODES


/*
Affiche les �l�ments d'une ligne dans la console
Entree : /
Precondition :
	- L'objet CType contient une surcharge de l'op�rateur <<
Sortie : /
Postconditions :
	- La ligne est affich�e dans la console
*/
template<class CType>
void CLigne<CType>::LIGAfficherLigne()
{
	for (unsigned int uiBoucle = 0; uiBoucle < uiLIGTaille; uiBoucle++)
	{
		std::cout << *ppTYPLIGListeElement[uiBoucle] << "\t";
	}
	std::cout << "\n";
}