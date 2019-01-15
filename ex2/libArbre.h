/**
 *  \file       abr.h
 *  \brief      Spécification d'un module de gestion d'arbres binaires
 *              de recherche
 *
 *  \date       25 Septembre 2018
 *  \author     S. El Khattabi
 *  \version    1.0
 *
 */

#ifndef _ABR_H_
#define _ABR_H_


#include "libElt.h"

/**
 *  \def        DOSSIER_PNG
 *  \brief		Constante symbolique désignant le nom du dossier destiné
 *				à contenir les fichiers .png générés par le programme
 *
 */
#define	DOSSIER_PNG	"./Png/"

/**
 *  \def        DOSSIER_DOT
 *  \brief		Constante symbolique désignant le nom du dossier destiné
 *				à contenir les fichiers .dot générés par le programme
 *
 */
#define	DOSSIER_DOT	"./Dot/"


/**
 *  \def        DOT_CMD
 *  \brief		Constante symbolique désignant le nom de la commande
 *				permettant de produire le fichier .png à partir du
 *				fichier .dot
 *
 */
#define	DOT_CMD		"dot"

/* ------------------------------------------------------------------------ */

/**
 *  \typedef    T_Noeud
 *  \brief      Définition du type des noeuds qui composent les ABRs
 */
typedef struct noeudABR noeudABR_t;
/* ------------------------------------------------------------------------ */


/**
 *  \struct     noeudABR
 *  \brief      Définition de la structure d'un noeud
 */
struct noeudABR
{
    /**         L'information enregistrée dans le noeudABR         */
    elt_t elt ;
    /**         Le pointeur sur le sous arbre gauche            */
    struct noeudABR * gauche ;
    /**         Le pointeur sur le sous arbre droit            */
    struct noeudABR * droit ;
}*ABR_t;
/* ------------------------------------------------------------------------ */

/**
 * \def MAX(a,b)
 * \brief Permet d'obtenir la valeur maximale entre a et b.
 * \param a Opérande de gauche, doit être comparable à b.
 * \param b Opérande de droite, doit être comparable à a.
 * \return a si a est supérieur ou égal à b, b sinon.
 */
#define	MAX(a,b)	(((a) >= (b)) ? (a) : (b))


/**
 * \def VIDE(noeud)
 * \brief Permet de savoir si un noeud de l'arbre est vide ou non.
 * \param noeud Le noeud de l'arbre
 * \return 1 si le noeud est vide, 0 sinon.
 */
#define VIDE(noeud) (noeud==NULL)


/**
 * \def PASVIDE(noeud)
 * \brief Permet de savoir si un noeud de l'arbre est vide ou non.
 * \param noeud Le noeud de l'arbre
 * \return 1 si le noeud n'est pas vide, 0 sinon.
 */
#define PASVIDE(noeud) (noeud != NULL)


/**
 * \def GAUCHE(noeud)
 * \brief Permet d'obtenir le sous arbre gauche du noeud.
 * \param noeud Le noeud de l'arbre
 * \return le sous arbre gauche du paramètre noeud.
 */
#define GAUCHE(noeud) (noeud->gauche)


/**
 * \def DROITE(noeud)
 * \brief Permet d'obtenir le sous arbre droit du noeud.
 * \param noeud Le noeud de l'arbre
 * \return le sous arbre droit du paramètre noeud.
 */
#define DROITE(noeud) (noeud->droit)


/**
 * \def RACINE(noeud)
 * \brief Permet d'obtenir l'élément situé dans la racine de l'arbre.
 * \param noeud Le noeud de l'arbre
 * \return l'élément en question.
 */
#define RACINE(noeud) (noeud->elt)


/**
 * \def EST_FEUILLE(noeud)
 * \brief Permet de savoir si le noeud actuel est une feuille de l'arbre.
 * \param noeud Le noeud de l'arbre
 * \return 1 si le noeud ne contient pas de sous arbre, 0 sinon.
 */
#define EST_FEUILLE(noeud) ( noeud->droit == NULL && noeud->gauche == NULL)


/* ------------------------------------------------------------------------ */

/****************************************************************************
 *      F O N C T I O N S    D' A C C E S                                   *
 ****************************************************************************/

/**
 *  \fn         void afficherABR( const noeudABR_t * arbre)
 *  \brief      Permet d'afficher le contenu d'un ABR.
 *              Le parcours effectué est de type GRD (infixé)
 *  \param      arbre   le pointeur sur l'ABR
 *  \return		néant
 *  \note       Un saut de ligne est effectué à la fin de l'affichage
 */
void afficherABR (const noeudABR_t * arbre);
/* ------------------------------------------------------------------------ */

/**
 *  \fn         unsigned int afficherInverseABR( const noeudABR_t * arbre)
 *  \brief      Permet d'afficher le contenu d'un ABR.
 *              Le parcours effectué est de type GDR (postfixé)
 *  \param      arbre   le pointeur sur l'ABR
 *  \return     néant
 *  \note       Un saut de ligne est effectué à la fin de l'affichage
 */
void afficherInverseABR (const noeudABR_t * arbre);
/* ------------------------------------------------------------------------ */

/**
 *  \fn         unsigned int nbNoeudsABR( const noeudABR_t * arbre)
 *  \brief      Calcule le nombre de noeuds d'un ABR.
 *  \param      arbre   le pointeur sur l'ABR
 *  \return    le nombre d'éléments de l'ABR
 */
unsigned int nbNoeudsABR (const noeudABR_t * arbre);
/* ------------------------------------------------------------------------ */

/**
 *  \fn         int   estDansABR (elt_t e, const noeudABR_t * arbre);
 *  \brief      Détermine si l'élément e est dans l'arbre
 *  \param      e       l'élément recherché
 *  \param      arbre   le pointeur sur la racine de l'ABR
 *  \return     0 si e n'est pas dans l'arbre ou 1 s'il est présent
 */
int   estDansABR (elt_t e, const noeudABR_t * arbre);
/* ------------------------------------------------------------------------ */


/****************************************************************************
 *      F O N C T I O N S    D E    M O D F I C A T I O N  D' U N           *
 *         A R B R E   B I N A I R E   D E   R E C H E R C H E              *
 ****************************************************************************/


/**
 *  \fn         noeudABR_t * creer1Noeud(elt_t e, noeudABR_t * g, noeudABR_t * d)
 *  \brief      Permet de créer un nouveau noeudABR d'ABR, et
 *              d'intialiser ses 3 composantes
 *  \param      e   la valeur d'initialisation de l'élément
 *  \param      g   la valeur d'initialisation du pointeur gauche du noeud
 *  \param      d   la valeur d'initialisation du pointeur droite du noeud
 *  \return    La pointeur sur le nouveau noeudABR ou NULL si l'allocation
 *              mémoire échoue.
 */
noeudABR_t * creer1Noeud (elt_t e, noeudABR_t * g, noeudABR_t * d);


/**
 *  \brief      Permet d'insérer un élément dans un ABR
 *  \param      arbre       le pointeur sur la racine de l'ABR
 *  \param      e           l'élément à insérer
 *  \return    La pointeur sur la (nlle) racine après insertion
 *  \note       arbre peut désigner un arbre vide.
 *  \note       Utilise <b>creer1Noeud</b>
 *	\note		l'insertion n'est pas réalisée si la valeur est déjà
 *				présente dans l'arbre.
 */
noeudABR_t * insererABR (elt_t e, noeudABR_t * a);
/* ------------------------------------------------------------------------ */

/**
 *  \fn         noeudABR_t * copierABR (const noeudABR_t * arbre)
 *  \brief      Crée une copie d'un ABR
 *  \param      arbre    le pointeur sur la racine de l'arbre
 *  \return     le pointeur sur la racine de la copie
 *  \note       arbre peut désigner un arbre vide. Dans ce cas
 *              elle retourne simplement NULL
 *  \note       Utilise <b>insererABR</b>
 */
noeudABR_t * copierABR (const noeudABR_t * arbre);
/* ------------------------------------------------------------------------ */

/**
 *  \fn         noeudABR_t * supprimerABR (noeudABR_t * arbre)
 *  \brief      Permet de supprimer un ABR et de
 *              récupérer tout l'espace mémoire qu'il occupait
 *  \param      arbre    le pointeur sur la racine de l'arbre
 *  \return    NULL
 *  \note       arbre peut désigner un arbre vide. Dans ce cas
 *              elle retourne simplement NULL
 */
noeudABR_t * supprimerABR (noeudABR_t * arbre);
/* ------------------------------------------------------------------------ */


/**
 *  \fn         void chercherMinABR(noeudABR_t * pRac,elt_t * min)
 *  \brief      Utilisé dans supprimer1EltTrouveABR, renvoie la plus petite valeur de l'arbre passé en paramètre.
 *  \param      arbre   le pointeur sur la racine de l'arbre
 */
void chercherMinABR(noeudABR_t * pRac,elt_t * min);


/**
 *  \fn         noeudABR_t * supprimer1EltABR(elt_t e, noeudABR_t * pRac)
 *  \brief      Permet de supprimer un élément d'un ABR et de
 *              récupérer tout l'espace mémoire qu'il occupait
 *  \param      e       l'élément à supprimer
 *  \param      arbre   le pointeur sur la racine de l'arbre
 *  \return     le pointeur sur l'arbre après suppression
 *  \note       si e n'est pas dans l'arbre alors elle retourne
 *              le pointeur sur sa racine.
 */
noeudABR_t * supprimer1EltABR(elt_t e, noeudABR_t * pRac);


/****************************************************************************
 *      F O N C T I O N S    U T I L E S   S U R   A R B R E S              *
 *           B I N A I R E S   D E   R E C H E R C H E                      *
 ****************************************************************************/

/**
 *  \fn         unsigned int hauteurABR(const noeudABR_t * arbre)
 *  \brief      Détermine la hauteur d'un ABR
 *  \param      arbre   l'ABR dont on détermine la hauteur
 *  \return    la hauteur de l'arbre
 *  \note       Un arbre vide a une hauteur égale à -1
 */
int hauteurABR (const noeudABR_t * arbre);
/* ------------------------------------------------------------------------ */

/**
 *  \fn         int egalABR(const noeudABR_t * arbre1, const noeudABR_t * arbre2)
 *  \brief      Détermine si deux arbres sont identiques
 *  \param      arbre1  le 1er arbre binaire
 *  \param      arbre2  le second arbre binaire
 *  \return		true s'ils sont égaux, false sinon.
 */
int egalABR (const noeudABR_t * arbre1, const noeudABR_t * arbre2);
/* ------------------------------------------------------------------------ */

/**
 *  \fn         int isomorpheABR(const noeudABR_t * arbre1, const noeudABR_t * arbre2)
 *  \brief      Détermine si deux arbres sont de même forme
 *  \param      arbre1  le 1er arbre binaire
 *  \param      arbre2  le second arbre binaire
 *  \return    1 s'ils ont même forme, 0 sinon.
 */
int isomorpheABR (const noeudABR_t * arbre1, const noeudABR_t * arbre2);
/* ------------------------------------------------------------------------ */

/**
 * \brief Génère un fichier dot et png, permettant d'afficher un arbre binaire de recherche en 2D.
 * \param arbre L'arbre à afficher.
 * \param basename Le nom des fichiers créés.
 */
void creerDotABR(const noeudABR_t * arbre, const char *basename);

#endif

