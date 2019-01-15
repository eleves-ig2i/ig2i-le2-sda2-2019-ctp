/**
 * \file libElt.h
 * \author Nathan Salez
 * \brief déclaration des fonctions et du TAD utilisé pour les collections.
 * \note Le TAD peut être une collection de sous éléments (chaine de caractère, tableau d'entiers, tableau de réels )
 * \version 1.1
 * \date 18/09/2018
 */

#ifndef TP2_LIBELT_H
#define TP2_LIBELT_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Un elt_t est représenté par un "morceau" du corps du snake.
 */
typedef struct
{
    unsigned short x;       // abscisse
    unsigned short y;       // ordonnée
}elt_t;



/**
 * \enum bool
 * \brief Enumération permettant d'utiliser les variables booléennes (économie de mémoire)
 */
typedef enum
{
    false,
    true
}bool;

/**
 * \def EGAL(elt1,elt2)
 * \brief Opérateur de comparaison entre deux éléments. Retourne true si elt1 == elt2.
 * \author Nathan Salez
 * \version 1.0
 * \date 29/10/2018
 */
#define EGAL(elt1,elt2) ( comparerElt(elt1,elt2) == 0 )


/**
 * \def SUPERIEUR_STRICT(elt1,elt2)
 * \brief Opérateur de comparaison entre deux éléments. Retourne true si elt1 > elt2.
 * \note Peut être utilisée de la manière suivante : retourne true si elt1 <= elt2 avec !SUPERIEUR_STRICT(elt1,elt2).
 * \author Nathan Salez
 * \version 1.0
 * \date 29/10/2018
 */
#define SUPERIEUR_STRICT(elt1,elt2) ( comparerElt(elt1,elt2) == 1 )


/**
 * \def SUPERIEUR_EGAL(elt1,elt2)
 * \brief Opérateur de comparaison entre deux éléments. Retourne true si elt1 >= elt2.
 * \note Peut être utilisée de la manière suivante : retourne true si elt1 < elt2 avec !SUPERIEUR_EGAL(elt1,elt2).
 * \author Nathan Salez
 * \version 1.0
 * \date 29/10/2018
 */
#define SUPERIEUR_EGAL(elt1,elt2) ( comparerElt(elt1,elt2) == 1 || comparerElt(elt1,elt2) == 0)


/**
 * \fn void initialiserElt(elt_t *e)
 * \brief Initialise l'élément à utiliser.
 * \note Si l'élément est une collection de sous éléments, indiquer ce nombre de sous éléments.
 * \param e l'élément à initialiser (int, char *, pile_t etc..)
 */
void initialiserElt(elt_t *e);


/**
 * \fn void saisirElt(elt_t* e, const char * messageSaisie)
 * \param e pointeur sur un elt_t, qui ne vaut pas NULL
 * \param messageSaisie Le message affiché lors de la saisie de e.
 * \brief Saisie d'un élément (ici un int)
 * \attention e ne doit pas être égal à NULL
 */
void saisirElt(elt_t* e, const char * messageSaisie);


/**
 * \fn void copierElt(elt_t* d, const elt_t* s)
 * \param d pointeur sur un elt_t, valeur changée après affectation.
 * \param s un elt_t, sa valeur reste inchangée.
 * \brief Affectation de s vers d. Si s vaut NULL, *d prendra la valeur ELT_HB
 * \attention d ne doit pas être égal à NULL
 */
void copierElt(elt_t* d, const elt_t* s);


/**
 * \fn short comparerElt(elt_t elt1,elt_t elt2)
 * \param elt1 valeur de gauche.
 * \param elt2 valeur de droite.
 * \brief Renvoie 0 si elt1 == elt2, 1 si elt1 > elt2, -1 si elt1 < elt2
 * \attention elt1 et elt2 ne doivent pas être égaux à NULL
 */
short comparerElt(elt_t elt1,elt_t elt2);


/**
 * \fn void afficherElt(const elt_t* e, const char * messageAffichage)
 * \param e pointeur sur un elt_t, dont la valeur est affichée.
 * \param messagePreAffichage Le message affiché avant l'affichage de e.
 * \param messagePostAffichage Le message affiché après l'affichage de e.
 * \brief Affichage de *e sur la sortie standard.
 * \attention e ne doit pas être égal à NULL
 */
void afficherElt(const char * messagePreAffichage, const elt_t* e,  const char * messagePostAffichage);


/**
 * \fn void libererElt(elt_t *e)
 * \param e un pointeur sur une collection de sous éléments.
 * \brief Libère la mémoire allouée à la collection.
 * \attention N'utiliser cette fonction que lorsque elt_t est un pointeur sur un élément. e ne doit pas être égal à NULL.
 * \note Si l'élément est une collection non native du C (pile,liste), il faut modifier cette fonction.
 */
void libererElt(elt_t *e);


#endif //TP2_LIBELT_H