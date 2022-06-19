#pragma once

//#include "CLigne.h"

// EXCEPTIONS

#define Index_Incorect 1
#define Pointeur_Null 2
#define Tailles_Differentes 3
#define Division_Par_Zero 4
#define Taille_Insufisante 5
#define Type_incorrect 6
#define Chemin_Incorrect 7
#define Syntaxe_Incorrecte 8


template <class CType>
class CMatrice {

private:
	unsigned int uiMATNbLignes;
	unsigned int uiMATNbColonnes;
	CLigne<CType>** ppLIGMATLignes;

public:

	// CONSTRUCTEURS ET DESTRUCTEUR

	/*
	Constructeur par défault, initialise le nombre de lignes et de colonnes à 1 et le pointeur sur la liste de lignes
	Entree : /
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialisé OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée 
	*/
	CMatrice();


	/*
	Constructeur de confort, initialise la matrice pour qu'elle puisse stocker uiNbLignes * uiNbColonnes éléments
	Entree : 
		- uiNbLignes : IN, nombre de lignes (au moins 1)
		- uiNbColonnes : IN, nombre de colonnes (au moins 1)
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialisé OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée OU
		- Erreur 5 : Taille_Insufisante, uiNbLignes ou uiNbColonnes vaux 0
	*/
	CMatrice(unsigned int uiNbLignes, unsigned int uiNbColonnes);


	/*
	Constructeur de confort, initialise la matrice avec les valeurs passées en paramètre (ou des valeurs par défault
		pour compléter si il manque des valeurs)
	Entree : 
		- uiNbLignes : IN, nombre de lignes (au moins 1)
		- uiNbColonnes : IN, nombre de colonnes (au moins 1)
		- ppTYPElements : IN, contient les valeurs à insérer dans la matrice
	Preconditions : 
		- ppTYPElements doit contenir uiNbLignes tableaux, chacun contenant uiNbColonnes éléments
	Sortie : /
	Postconditions :
		- L'objet est initialisé OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée OU
		- Erreur 5 : Taille_Insufisante, uiNbLignes ou uiNbColonnes vaux 0
	*/
	CMatrice(unsigned int uiNbLignes, unsigned int uiNbColonnes, CType** ppTYPElements);


	
	/*
	Constructeur de recopie pour une matrice stocant le même type d'objet
	Entree :
		- MAT1 : IN, matrice à copier
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialisé et contient les mêmes valeurs que MAT1 OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée 
	*/
	CMatrice(const CMatrice<CType> &MAT1);


	/*
	Constructeur utilisant un fichier pour initialiser la matrice
	Entree : /
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialisé et contient les mêmes valeurs que MAT1 OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée 
	*/
	CMatrice(char* chemin);


	/* Destructeur*/
	~CMatrice();


	// GETTEURS ET SETTEURS

	/* Getteur de uiMATNbLignes*/
	unsigned int MATLireNbLignes() const { return uiMATNbLignes; }


	/* Getteur de uiMATNbColonnes*/
	unsigned int MATLireNbColonnes() const { return uiMATNbColonnes; }



	/* 
	Getteur d'une ligne, renvoie une copie de la ligne
	Entree :
		- uiLigne : IN, index de la ligne à récupérer
	Preconditions : /
	Sortie :
		- CType : Une copie de l'élément voulu
	Postconditions :
		- Une copie de l'objet est retourné OU
		- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est supérieur au nombre de lignes ou de colonnes
	*/
	CLigne<CType> MATLireLigne(unsigned int uiIndex) const;


private:

	/*
	Setteur d'une ligne, privé
	Entree :
		- uiLigne : IN, index de la ligne à récupérer
		- LIG1 : IN, ligne à insérer
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'élément à l'index uiIndex est modifé dans la ligne OU
		- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est supérieur au nombre de lignes ou de colonnes OU
		- Erreur 3 : Tailles_Differentes, les matrices ne sont pas de même taille
	*/
	void MATModifierLigne(unsigned int uiIndex, CLigne<CType> LIG1);

public:

	/*
	Getteur d'un élément de la matrice
	Entree :
		- uiLigne : IN, index de la ligne de l'élément à récupérer
		- uiColonne : IN, index de la colonne de l'élément à récupérer
	Preconditions : /
	Sortie :
		- CType : Une copie de l'élément voulu
	Postconditions :
		- Une copie de l'objet est retourné OU
		- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est supérieur au nombre de lignes ou de colonnes
	*/
	CType MATLireElement(unsigned int uiLigne, unsigned int uiColonne) const;


	/*
	Setteur d'un élément de la matrice
	Entree :
		- uiLigne : IN, index de la ligne de l'élément à modifier
		- uiColonne : IN, index de la colonne de l'élément à modifier
		- TYPElement : IN, élément à mettre dans la matrice
	Preconditions : /
	Sortie : /
	Postconditions :
		- Une copie de l'objet est retourné OU
		- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est supérieur au nombre de lignes ou de colonnes
	*/
	void MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, CType TYPElement);



	/*
	Ajoute une ligne à l'index spécifié (ou à la fin par défault ou si l'index est supérieur au nombre de lignes de la matrice)
		contenant les valeurs passées en paramètre (ou des objets construits avec le contructeur par défault si
		aucun tableau n'est passé en paramètre ou si celui-ci ne contient pas assez de valeurs pour la remplir entièrement)
	Entree :
		- uiIndex : IN, index où insérer la ligne
		- pTYPValeurs : IN, tableau des valeurs à insérer
		- uiIndiceMax : IN, indice de la dernière valeur du tableau à insérer dans la matrice
	Preconditions :
		- uiIndiceMax doit être inférieur au nombre d'éléments contenu dans le tableau
	Sortie : /
	Postconditions :
		- La ligne a été insérée dans la matrice OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée
	*/
	void MATAjouterLigne(unsigned int uiIndex = uiMATNbLignes, CType* pTYPValeurs = nullptr, unsigned int uiIndiceMax = 0);


	/*
	Supprime une ligne à l'index spécifié
	Entree :
		- uiIndex : IN, index de la ligne à supprimer
	Preconditions : /
	Sortie : /
	Postconditions :
		- La ligne a été retirée de la matrice OU
		- Erreur 1 : Index_Incorect, l'index est supérieur au nombre de lignes de la matrice
	*/
	void MATSupprimerLigne(unsigned int uiIndex);



	/*
	Ajoute une colonne à l'index spécifié (ou à la fin par défault ou si l'index est supérieur au nombre de colonnes de la matrice)
		contenant les valeurs passées en paramètre (ou des objets construits avec le contructeur par défault si
		aucun tableau n'est passé en paramètre ou si celui-ci ne contient pas assez de valeurs pour la remplir entièrement)
	Entree :
		- uiIndex : IN, index où insérer la colonne
		- pTYPValeurs : IN, tableau des valeurs à insérer
		- uiIndiceMax : IN, indice de la dernière valeur du tableau à insérer dans la matrice
	Preconditions :
		- uiIndiceMax doit être inférieur au nombre d'éléments contenu dans le tableau
	Sortie : /
	Postconditions :
		- La colonne a été insérée dans la matrice OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a échouée
	*/
	void MATAjouterColonne(unsigned int uiIndex = uiMATNbColonnes, CType* pTYPValeurs = nullptr, unsigned int uiIndiceMax = 0);



	/*
	Supprime une colonne à l'index spécifié
	Entree :
		- uiIndex : IN, indice de la colonne à supprimer
	Preconditions : /
	Sortie : /
	Postconditions :
		- La colonne a été retirée de la matrice OU
		- Erreur 1 : Index_Incorect, l'index est supérieur au nombre de colonnes de la matrice
	*/
	void MATSupprimerColonne(unsigned int uiIndex);





	// OPERATEURS

	/* Operateur = entre 2 matrices du même type*/
	CMatrice<CType> operator=(CMatrice<CType> MAT1);

	/*
	Opérateur + entre 2 matrices de mêmes tailles
	Entree :
		- MAT1 : IN, Matrice contenant les valeurs à additionner
	Precondition :
		- L'objet CType contient une surcharge de l'opérateur + pour un objet de type CType2
	Sortie :
		- CMatrice<CType> : La matrice contenant l'addition de l'objet courant et de MAT1
	Postconditions :
		- La matrice revoyée contient la somme de l'objet courant et de MAT1 OU
		- Erreur 3 : Tailles_Differentes, les matrices ne sont pas de même taille
	*/
	template<class CType2>
	CMatrice<CType> operator+(CMatrice<CType2> MAT1) const;


	/*
	Opérateur - entre 2 matrices de mêmes tailles
	Entree :
		- MAT1 : IN, Matrice contenant les valeurs à soustraire
	Precondition :
		- L'objet CType contient une surcharge de l'opérateur - pour un objet de type CType2
	Sortie :
		- CMatrice<CType> : La matrice contenant la différence de l'objet courant et de MAT1
	Postconditions :
		- La matrice revoyée contient la différence de l'objet courant et de MAT1 OU
		- Erreur 3 : Tailles_Differentes, les matrices ne sont pas de même taille
	*/
	template<class CType2>
	CMatrice<CType> operator-(CMatrice<CType2> MAT1) const;



	/*
	Opérateur * entre 2 matrices avec MAT1 possédant autant de lignes que
		l'objet courrant possède de colonnes
	Entree :
		- MAT1 : IN, Matrice contenant les valeurs à multiplier à l'objet courant
	Precondition :
		- L'objet CType contient une surcharge de l'opérateur * pour un objet de type CType2
	Sortie :
		- CMatrice<CType> : La matrice contenant la multiplication de l'objet courant et de MAT1
	Postconditions :
		- La ligne revoyée contient la multiplication de l'obet courant et MAT1 OU
		- Erreur 3 : Tailles_Differentes, l'objet courant n'a pas autant de colonnes que MAT1 a de lignes
	*/
	template<class CType2>
	CMatrice<CType> operator*(CMatrice<CType2> MAT1) const;


	/* Operateur * entre une matrice et un nombre
	Entree :
		- dFacteur : IN, facteur
	Precondition :
		- L'objet CType contient une surcharge de l'opérateur * pour un nombre
	Sortie :
		- CMatrice<CType> : La matrice contenant la multiplication de l'objet courant par dFacteur
	Postconditions :
		- La matrice revoyée contient la multiplication de l'objet courant par dFacteur
	*/
	CMatrice<CType> operator*(double dFacteur) const;


	/* Operateur / entre une matrice et un nombre
	Entree :
		- dDiviseur : IN, diviseur
	Precondition :
		- L'objet CType contient une surcharge de l'opérateur / pour un nombre
	Sortie :
		- CMatrice<CType> : La matrice contenant la division de l'objet courant par dDiviseur
	Postconditions :
		- La matrice revoyée contient la multiplication de l'obet courant et dDiviseur OU
		- Erreur 4 : Division_Par_Zero, dDiviseur vaux 0
	*/
	CMatrice<CType> operator/(double dDiviseur) const;




	// AUTRES METHODES

	/* 
	Affiche les éléments d'une matrice dans la console
	Entree : /
	Precondition :
		- L'objet CType contient une surcharge de l'opérateur <<
	Sortie : /
	Postconditions :
		- La matrice est affichée dans la console
	*/
	void MATAfficher() const;
	
};


/* Operateur * entre un nombre et une matrice
Entree :
	- dFacteur : IN, nombre facteur
	- MAT1 : IN, matrice facteur
Precondition :
	- L'objet CType contient une surcharge de l'opérateur * pour un nombre
Sortie :
	- CMatrice<CType> : La matrice contenant la multiplication de l'objet courant par dFacteur
Postconditions :
	- La mtrice revoyée contient la multiplication de l'objet courant par dFacteur
*/
template<class CType>
CMatrice<CType> operator*(double dFacteur, const CMatrice<CType> &MAT1);




// FONCTIONS DU PARSEUR


/*
Sous-méthode du parseur pour la ligne du type d'une matrice
Entree :
	- pcNomFichier : IN, nom du fichier à ouvrir et tester
Preconditions :
	- pcNomFichier n'est pas null
Sortie :
	- True si la ligne est de la bonne syntaxe
Postconditions :
	- True est renvoyé OU
	- Erreur 6 : Type_Incorrect, le type spécifié dans le fichier n'est pas double OU
	- Erreur 7 : Chemin_Incorrect, le chemin spécifié est incorrect
*/
bool MATlireFichierTypeDouble(char* pcNomFichier);



/*
Sous-méthode du parseur pour lire le nombre de ligne
Entree :
	- pcNomFichier : IN, nom du fichier à ouvrir et tester
Preconditions :
	- pcNomFichier n'est pas null
Sortie :
	- iNum : le nombre de ligne indiqué dans le fichier
Postconditions :
	- iNum est renvoyé et correspond au nombre au nombre lu et testé de la ligne OU
	- Erreur 7 : Chemin_Incorrect, le chemin spécifié est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
int MATLireFichierNbLigne(char* pcNomFichier);



/*
Sous-méthode du parseur pour lire le nombre de colonne
Entree :
	- pcNomFichier : IN, nom du fichier à ouvrir et tester
Preconditions :
	- pcNomFichier n'est pas null
Sortie :
	- iNum : le nombre de colonne indiqué dans le fichier
Postconditions :
	- iNum est renvoyé et correspond au nombre de colonnes lu et testé de la ligne OU
	- Erreur 7 : Chemin_Incorrect, le chemin spécifié est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
int MATLireFichierNbColonne(char* pcNomFichier);



/*
Sous-méthode du parseur pour lire la syntaxe de l'encapsualtion de la matrice
Entree :
	- pcNomFichier : IN, nom du fichier à ouvrir et tester
	- uiNbLigne : IN, nombre de ligne lu auparavant
Preconditions :
	- pcNomFichier n'est pas null
Sortie :
	- true : la syntaxe est correcte
Postconditions :
	- True est renvoyé OU
	- Erreur 7 : Chemin_Incorrect, le chemin spécifié est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
bool MATLireFichierSyntaxMatrice(unsigned int uiNbLigne, char* pcNomFichier);



/*
Méthode du parseur pour lire et vérifier les lignes autres que le contenu de la matrice
Entree :
	- pcNomFichier : nom du fichier à ouvrir et tester
Preconditions :
	- pcNomFichier n'est pas null
Sortie :
	- piTabAttributMatrice : tableau dynamique d'entier
Postconditions :
	- piTabAttributMatrice[0] et [1} correspondent respectivements au nombre de lignes et de colonnes de la matrice OU
	- Erreur 2 : Pointeur_Null, une allocation de mémoire a échouée OU
	- Erreur 7 : Chemin_Incorrect, le chemin spécifié est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture
*/
int* MATLireFichierAttribut(char* pcNomFichier);


//Tronque la plage d'éléments de la matrice selon le nombre de ligne (même si il y a d'autres éléments dans le fichier)
/*
Méthode du parseur pour lire le contenu de la matrice
Entree :
	- uiNbLigne : IN, nombre de ligne lu auparavant
	- uiNbCol : IN, nombre de colonne lu auparavant
	- pcNomFichier : IN, nom du fichier à ouvrir et tester
Preconditions :
	- pcNomFichier n'est pas null
Sortie :
	- double** : tableau à 2 dimensions contenant les valeurs de la matrice contenues dans le fichier
Postconditions :
	- le tableau à 2 dimensions est retourné avec les valeurs de la matrice OU
	- Erreur 2 : Pointeur_Null, une allocation de mémoire a échouée OU
	- Erreur 7 : Chemin_Incorrect, le chemin spécifié est incorrect OU
	- Erreur 8 : Syntaxe_Inorrecte, la syntaxe du fichier ne permet pas sa lecture ou il manque des éléments dans le fichier pour créer la matrice
*/
double** MATLireFichierMatrice(unsigned int uiNbLigne, unsigned int uiNbCol, char* pcNomFichier);


#include "CMatrice.cpp"

