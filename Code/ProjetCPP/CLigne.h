#ifndef LIGNE_H_
#define LIGNE_H_

// EXCEPTIONS

#define Index_Incorect 1
#define Pointeur_Null 2
#define Tailles_Differentes 3
#define Division_Par_Zero 4


template <class CType>
class CLigne
{

private:
	unsigned int uiLIGTaille;
	CType** ppTYPLIGListeElement;

public:

	//CONSTRUCTEURS ET DESTRUCTEUR :

	/*
	Constructeur par défault, initialise la taille à 0 et le pointeur sur la liste d'éléments à NULL
	Entree : /
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialisé
	*/
	CLigne();


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
	CLigne(unsigned int uiTaille);


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
	CLigne(unsigned int uiTaille, CType* pTYPElements);


	/*
	Constructeur de recopie
	Entree : /
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialisé et contient les mêmes valeurs que LIG1 OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée 
	*/
	CLigne<CType>(const CLigne<CType>& LIG1);


	/* Destructeur*/
	~CLigne();





	//GETTEURS ET SETTEURS :

	/* Getteur de uiLIGTaille*/
	int LIGLireTaile() const { return uiLIGTaille; };


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
	CType LIGLireElement(unsigned int uiIndex) const;

	
	
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
	void LIGAjouterElement(unsigned int uiIndex = uiLIGTaille, CType TYPElement = CType());


	
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
	void LIGSupprimerElement(unsigned int uiIndex);


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
	void LIGModifierElement(unsigned int uiIndex, CType TYPElement);





	// OPERATEURS :

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
	CLigne<CType> operator=(CLigne<CType> LIG1);



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
	template<class CType2>
	CLigne<CType> operator+(CLigne<CType2> LIG1) const;


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
	template<class CType2>
	CLigne<CType> operator-(CLigne<CType2> LIG1) const;


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
	CLigne<CType> operator*(double dFacteur) const;


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
	CLigne<CType> operator/(double dDiviseur) const;


	// AUTRE METHODES

	/*
	Affiche les éléments d'une ligne dans la console
	Entree : /
	Precondition :
		- L'objet CType contient une surcharge de l'opérateur <<
	Sortie : /
	Postconditions :
		- La ligne est affichée dans la console
	*/
	void LIGAfficherLigne();


};


#include "CLigne.cpp"

#endif // !LIGNE_H


