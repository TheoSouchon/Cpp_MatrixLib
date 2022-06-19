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
	Constructeur par d�fault, initialise le nombre de lignes et de colonnes � 1 et le pointeur sur la liste de lignes
	Entree : /
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialis� OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e 
	*/
	CMatrice();


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
	CMatrice(unsigned int uiNbLignes, unsigned int uiNbColonnes);


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
	CMatrice(unsigned int uiNbLignes, unsigned int uiNbColonnes, CType** ppTYPElements);


	
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
	CMatrice(const CMatrice<CType> &MAT1);


	/*
	Constructeur utilisant un fichier pour initialiser la matrice
	Entree : /
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialis� et contient les m�mes valeurs que MAT1 OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e 
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
		- uiLigne : IN, index de la ligne � r�cup�rer
	Preconditions : /
	Sortie :
		- CType : Une copie de l'�l�ment voulu
	Postconditions :
		- Une copie de l'objet est retourn� OU
		- Erreur 1 : Index_Incorect : l'indice de la ligne ou de la colonne voulu est sup�rieur au nombre de lignes ou de colonnes
	*/
	CLigne<CType> MATLireLigne(unsigned int uiIndex) const;


private:

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
	void MATModifierLigne(unsigned int uiIndex, CLigne<CType> LIG1);

public:

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
	CType MATLireElement(unsigned int uiLigne, unsigned int uiColonne) const;


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
	void MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, CType TYPElement);



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
	void MATAjouterLigne(unsigned int uiIndex = uiMATNbLignes, CType* pTYPValeurs = nullptr, unsigned int uiIndiceMax = 0);


	/*
	Supprime une ligne � l'index sp�cifi�
	Entree :
		- uiIndex : IN, index de la ligne � supprimer
	Preconditions : /
	Sortie : /
	Postconditions :
		- La ligne a �t� retir�e de la matrice OU
		- Erreur 1 : Index_Incorect, l'index est sup�rieur au nombre de lignes de la matrice
	*/
	void MATSupprimerLigne(unsigned int uiIndex);



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
	void MATAjouterColonne(unsigned int uiIndex = uiMATNbColonnes, CType* pTYPValeurs = nullptr, unsigned int uiIndiceMax = 0);



	/*
	Supprime une colonne � l'index sp�cifi�
	Entree :
		- uiIndex : IN, indice de la colonne � supprimer
	Preconditions : /
	Sortie : /
	Postconditions :
		- La colonne a �t� retir�e de la matrice OU
		- Erreur 1 : Index_Incorect, l'index est sup�rieur au nombre de colonnes de la matrice
	*/
	void MATSupprimerColonne(unsigned int uiIndex);





	// OPERATEURS

	/* Operateur = entre 2 matrices du m�me type*/
	CMatrice<CType> operator=(CMatrice<CType> MAT1);

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
	template<class CType2>
	CMatrice<CType> operator+(CMatrice<CType2> MAT1) const;


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
	template<class CType2>
	CMatrice<CType> operator-(CMatrice<CType2> MAT1) const;



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
	template<class CType2>
	CMatrice<CType> operator*(CMatrice<CType2> MAT1) const;


	/* Operateur * entre une matrice et un nombre
	Entree :
		- dFacteur : IN, facteur
	Precondition :
		- L'objet CType contient une surcharge de l'op�rateur * pour un nombre
	Sortie :
		- CMatrice<CType> : La matrice contenant la multiplication de l'objet courant par dFacteur
	Postconditions :
		- La matrice revoy�e contient la multiplication de l'objet courant par dFacteur
	*/
	CMatrice<CType> operator*(double dFacteur) const;


	/* Operateur / entre une matrice et un nombre
	Entree :
		- dDiviseur : IN, diviseur
	Precondition :
		- L'objet CType contient une surcharge de l'op�rateur / pour un nombre
	Sortie :
		- CMatrice<CType> : La matrice contenant la division de l'objet courant par dDiviseur
	Postconditions :
		- La matrice revoy�e contient la multiplication de l'obet courant et dDiviseur OU
		- Erreur 4 : Division_Par_Zero, dDiviseur vaux 0
	*/
	CMatrice<CType> operator/(double dDiviseur) const;




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
	void MATAfficher() const;
	
};


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
CMatrice<CType> operator*(double dFacteur, const CMatrice<CType> &MAT1);




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
bool MATlireFichierTypeDouble(char* pcNomFichier);



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
int MATLireFichierNbLigne(char* pcNomFichier);



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
int MATLireFichierNbColonne(char* pcNomFichier);



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
bool MATLireFichierSyntaxMatrice(unsigned int uiNbLigne, char* pcNomFichier);



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
int* MATLireFichierAttribut(char* pcNomFichier);


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
double** MATLireFichierMatrice(unsigned int uiNbLigne, unsigned int uiNbCol, char* pcNomFichier);


#include "CMatrice.cpp"

