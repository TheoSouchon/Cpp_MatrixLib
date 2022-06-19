#include <iostream>
#include "CLigne.h"
#include "CException.h"


// CONSTRUCTEURS ET DESTRUCTEUR

/*
Constructeur par défault, initialise la taille à 0 et le pointeur sur la liste d'éléments à NULL
Entree : /
Preconditions : /
Sortie : /
Postconditions :
	- L'objet est initialisé
*/
template<class CType>
CLigne<CType>::CLigne() 
{
	uiLIGTaille = 0;
	ppTYPLIGListeElement = nullptr;
}

/*
Constructeur de confort, initialise la ligne pour qu'elle puisse stocker uiTaille éléments
Entree :
	- uiTaille : IN, taille de la ligne
Preconditions : /
Sortie : /
Postconditions :
	- L'objet est initialisé OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée
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
Constructeur de confort, initialise la ligne avec la liste d'éléments passée en paramètre
Entree :
	- uiTaille : IN, taille de la ligne
	- pTYPElements : IN, liste des éléments à insérer dans la ligne
Preconditions :
	- Il y a au moins uiTaille éléments dans pTYPElements
Sortie : /
Postconditions :
	- L'objet est initialisé OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée
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
	- L'objet est initialisé et contient les mêmes valeurs que LIG1 OU
	- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée
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
	//delete les élements dans la liste
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
Getteur d'élément dans la ligne
Entree :
	- uiIndex : IN, index de l'élément à récupérer
Precondition : /
Sortie :
	- CType : Copie de l'élément à l'index uiIndex
Postconditions :
	- Une copie de l'élément à l'index uiIndex est retourné OU
	- Erreur 1 : Index_Incorect : L'index passé en paramètre est plus grand que la taille de la ligne OU
	- Erreur 2 : Pointeur_Null : Le pointeur sur lequel on veut effectuer des opérations est nullptr
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
Ajoute un élément dans la ligne à l'index spécifié (ou à la fin de la ligne par défaut ou si l'index est plus grand que la taille de la ligne)
Entree :
	- uiIndex : IN, index de l'élément à récupérer (défaut = uiLIGTaille
	- TYPElement : IN, élément à ajouter (défaut = nouvel ojet construit avec le contructeur par défaut)
Precondition : /
Sortie : /
Postconditions :
	- L'élément est ajouté à l'index spécifié OU
	- Erreur 2 : Pointeur_Null : Le pointeur sur lequel on veut effectuer des opérations est nullptr (erreur d'allocation)
*/
template<class CType>
void CLigne<CType>::LIGAjouterElement(unsigned int uiIndex, CType TYPElement)
{
	if (uiIndex > uiLIGTaille) {
		uiIndex = uiLIGTaille;
	}
	// Réalocation
	CType** ppTYPTmp = nullptr;
	ppTYPTmp = (CType**) realloc(ppTYPLIGListeElement, (uiLIGTaille + 1) * sizeof(CType*));
	if (ppTYPTmp == nullptr) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Pointeur_Null);
		throw EXCErreur;
	}
	//Déplacement des éléments
	for (unsigned int uiBoucle = uiLIGTaille; uiBoucle > uiIndex; uiBoucle--) {
		ppTYPTmp[uiBoucle] = ppTYPTmp[uiBoucle-1];
	}
	ppTYPTmp[uiIndex] = new CType(TYPElement);
	uiLIGTaille++;
	ppTYPLIGListeElement = ppTYPTmp;
}


/*
Supprime un élément dans la ligne à l'index spécifié
Entree :
	- uiIndex : IN, index de l'élément à suprimer
Precondition : /
Sortie : /
Postconditions :
	- L'élément à l'index spécifié est suprimé OU
	- Erreur 1 : Index_Incorect : L'index passé en paramètre est plus grand que la taille de la ligne OU
	- Erreur 2 : Pointeur_Null : Le pointeur sur lequel on veut effectuer des opérations est nullptr (erreur d'allocation)
*/
template<class CType>
void CLigne<CType>::LIGSupprimerElement(unsigned int uiIndex)
{
	if (uiIndex > uiLIGTaille) {
		CException EXCErreur;
		EXCErreur.EXCSetValeur(Index_Incorect);
		throw EXCErreur;
	}
	//Déplacement des éléments
	delete ppTYPLIGListeElement[uiIndex];
	for (unsigned int uiBoucle = uiIndex; uiBoucle < uiLIGTaille - 1; uiBoucle++) {
		ppTYPLIGListeElement[uiBoucle] = ppTYPLIGListeElement[uiBoucle + 1];
	}
	// Réalocation
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
Modifie un élément dans la ligne à l'index spécifié
Entree :
	- uiIndex : IN, index de l'élément à récupérer
	- TYPElement : IN, élément à ajouter
Precondition : /
Sortie : /
Postconditions :
	- L'élément est ajouté à l'index spécifié OU
	- Erreur 1 : Index_Incorect : L'index passé en paramètre est plus grand que la taille de la ligne
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
Opérateur = entre 2 lignes stockant le même type d'objets
Entree :
	- LIG1 : IN, ligne à copier
Precondition : /
Sortie :
	- CLigne<CType> : l'objet courrant, qui contient les mêmes valeurs que LIG1
Postconditions :
	- L'objet courrant contient les mêmes valeurs que LIG1 et est renvoyé OU
	- Erreur 2 : Pointeur_Null : Le pointeur sur lequel on veut effectuer des opérations est nullptr (erreur d'allocation)
*/
template<class CType>
CLigne<CType> CLigne<CType>::operator=(CLigne<CType> LIG1)
{
	// Destruction des objets actuellement dans la ligne et désallocation du tableau d'éléments
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
Opérateur + entre 2 lignes de même taille
Entree :
	- LIG1 : IN, Ligne contenant les valeurs à additionner à celles de l'objet courant
Precondition :
	- L'objet CType contient une surcharge de l'opérateur + pour un objet de même type
Sortie :
	- CLigne<CType> : La ligne contenant l'addition de l'objet courant et de LIG1
Postconditions :
	- La ligne revoyée contient l'addition de l'objet courant et de LIG1 OU
	- Erreur 3 : Tailles_Differentes, les lignes ne sont pas de même taille
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
Opérateur - entre 2 lignes de même taille
Entree :
	- LIG1 : IN, Ligne contenant les valeurs à soustraire à l'objet courant
Precondition :
	- L'objet CType contient une surcharge de l'opérateur - pour un objet de type CType2
Sortie :
	- CLigne<CType> : La ligne contenant la différence de l'objet courant et de LIG1
Postconditions :
	- La ligne revoyée contient la différence de l'objet courant et LIG1 OU
	- Erreur 3 : Tailles_Differentes, les lignes ne sont pas de même taille
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
	- L'objet CType contient une surcharge de l'opérateur * pour un nombre
Sortie :
	- CLigne<CType> : La ligne contenant la multiplication de l'objet courant par dFacteur
Postconditions :
	- La ligne revoyée contient la multiplication de l'objet courant par dFacteur
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
	- L'objet CType contient une surcharge de l'opérateur / pour un nombre
Sortie :
	- CLigne<CType> : La ligne contenant la division de l'objet courant par dDiviseur
Postconditions :
	- La ligne revoyée contient la multiplication de l'obet courant et dDiviseur OU
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
Affiche les éléments d'une ligne dans la console
Entree : /
Precondition :
	- L'objet CType contient une surcharge de l'opérateur <<
Sortie : /
Postconditions :
	- La ligne est affichée dans la console
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