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
	Constructeur par d�fault, initialise la taille � 0 et le pointeur sur la liste d'�l�ments � NULL
	Entree : /
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialis�
	*/
	CLigne();


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
	CLigne(unsigned int uiTaille);


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
	CLigne(unsigned int uiTaille, CType* pTYPElements);


	/*
	Constructeur de recopie
	Entree : /
	Preconditions : /
	Sortie : /
	Postconditions :
		- L'objet est initialis� et contient les m�mes valeurs que LIG1 OU
		- Erreur 2 : Pointeur_Null, l'allocation d'un pointeur a �chou�e 
	*/
	CLigne<CType>(const CLigne<CType>& LIG1);


	/* Destructeur*/
	~CLigne();





	//GETTEURS ET SETTEURS :

	/* Getteur de uiLIGTaille*/
	int LIGLireTaile() const { return uiLIGTaille; };


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
	CType LIGLireElement(unsigned int uiIndex) const;

	
	
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
	void LIGAjouterElement(unsigned int uiIndex = uiLIGTaille, CType TYPElement = CType());


	
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
	void LIGSupprimerElement(unsigned int uiIndex);


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
	void LIGModifierElement(unsigned int uiIndex, CType TYPElement);





	// OPERATEURS :

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
	CLigne<CType> operator=(CLigne<CType> LIG1);



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
	template<class CType2>
	CLigne<CType> operator+(CLigne<CType2> LIG1) const;


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
	template<class CType2>
	CLigne<CType> operator-(CLigne<CType2> LIG1) const;


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
	CLigne<CType> operator*(double dFacteur) const;


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
	CLigne<CType> operator/(double dDiviseur) const;


	// AUTRE METHODES

	/*
	Affiche les �l�ments d'une ligne dans la console
	Entree : /
	Precondition :
		- L'objet CType contient une surcharge de l'op�rateur <<
	Sortie : /
	Postconditions :
		- La ligne est affich�e dans la console
	*/
	void LIGAfficherLigne();


};


#include "CLigne.cpp"

#endif // !LIGNE_H


