/**
 * \file libListe.h
 * \author Nathan Salez
 * \brief déclaration des fonctions et types de la bibliothèque de TAD de gestion de listes chaînées.
 * \note Toutes les fonctions marchent correctement, bibliothèque utilisable pour un CTP.
 * \version 1.0
 * \date 21/09/2018
 */

#ifndef TP1_LIBPILE_H
#define TP1_LIBPILE_H

#include <stdlib.h>
#include "libElt.h"

/**
 * Une maille est représenté par un morceau du corps de snake, relié à un autre morceau de ce corps.
 * La tete de liste est la tête du snake.
 */
typedef struct maille
{
    elt_t e;    /**< l'élément présent dans la maille */
    struct maille *next;    /**< Pointeur sur la maille suivante. Si l'instance actuelle est la queue de la liste, alors next vaut NULL. */
}maille_t, *liste_t;

/**
 * \brief Macrofonction vérifiant si une liste est vide ou non.
 * \param liste La liste concernée.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
#define VIDE_LISTE(liste) (liste==NULL)


/**
 * \brief Macrofonction retournant l'élément de la maille en tête de liste.
 * \param liste La liste concernée.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
#define TETE(liste) (liste->e)


/**
 * \brief Macrofonction retournant le reste de la liste l.
 * \param l La liste concernée.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
#define RESTE(l) (l->next)


/**
 * \fn elt_t eltTeteListe(liste_t l)
 * \param l La liste concernée.
 * \return La tête de liste si l n'est pas vide, ELT_HB sinon.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
elt_t eltTeteListe(liste_t l);


/**
 * \fn unsigned int nbrEltsListe(liste_t l)
 * \brief Renvoie le nombre d'éléments de la liste, à l'aide de la récursivité.
 * \param l la liste concernée.
 * \return Le nombre d'éléments de la liste.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
unsigned int nbrEltsListe(liste_t l);


/**
 * \fn void afficherListe(liste_t l)
 * \brief Affiche la liste, de la tête jusqu'à la queue.
 * \param l La liste concernée.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
void afficherListe(liste_t l);


/**
 * \fn void afficherListeInverse(liste_t l)
 * \brief Affiche la liste, de la queue jusqu'à la tête.
 * \param l La liste concernée.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
void afficherListeInverse(liste_t l);


/**
 * \fn liste_t creerMaille(elt_t e, liste_t suivant)
 * \brief Crée une maille de la liste chaînée.
 * \param e L'élément constituant la maille.
 * \param suivant Pointeur sur la maille suivante (ancienne tête de liste) dans la liste chaînée
 * \return la liste créée.
 * \attention Si l'allocation de la maille a échouée, le programme s'arrête.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
liste_t creerMaille(elt_t e, liste_t suivant);


/**
 * \fn liste_t insererEltTeteListe(elt_t e, liste_t liste)
 * \brief Insère un élément  en tête de la liste.
 * \param e L'élément concerné.
 * \param liste la liste initiale
 * \return la liste créée
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
liste_t insererEltTeteListe(elt_t e, liste_t liste);


/**
 * \fn liste_t insererEltListeOrdonnee(elt_t e, liste_t liste)
 * \brief Insère un élément dans une liste déjà triée par ordre croissant. La liste reste triée après cette fonction.
 * \param e L'élément concerné.
 * \param liste la liste initiale.
 * \return la liste créée
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
liste_t insererEltListeOrdonnee(elt_t e, liste_t liste);


/**
 * \fn liste_t insererEltQueueListe(elt_t e, liste_t liste)
 * \brief Insère un élément  en queue de la liste, à l'aide de la récursivité.
 * \param e L'élément concerné.
 * \param liste la liste initiale
 * \return la liste créée
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
liste_t insererEltQueueListe(elt_t e, liste_t liste);


/**
 * \fn liste_t supprimerDernierElementListe(liste_t liste)
 * \brief Supprime l'élément en queue de liste.
 * \param liste La liste concernée.
 * \return La liste si elle n'est pas vide, NULL sinon.
 * \attention Mettre l'argument en paramètre UNIQUEMENT lorsque la liste contient 1 seul ou aucun élément.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
liste_t supprimerDernierElementListe(liste_t liste);


/**
 * \fn liste_t supprimerPremierElementListe(liste_t liste)
 * \brief Supprime l'élément en tête de liste
 * \param liste La liste concernée.
 * \return La liste si elle n'est pas vide, NULL sinon.
 * \attention Mettre l'argument en valeur de retour.
 * \author Nathan Salez
 * \version 1.0
 * \date 20/09/2018
 */
liste_t supprimerPremierElementListe(liste_t liste);


/**
 * \fn liste_t supprimerElementListe(elt_t e, liste_t liste)
 * \brief Supprime toutes les occurences de l'élément e, dans la liste liste
 * \param e L'élément à supprimer.
 * \param liste La liste concernée.
 * \return La liste si elle n'est pas vide, NULL sinon.
 * \attention Mettre l'argument en valeur de retour.
 * \author Nathan Salez
 * \version 1.0
 * \date 20/09/2018
 */
liste_t supprimerElementListe(elt_t e, liste_t liste);


/**
 * \fn liste_t libererListe(liste_t liste)
 * \brief Libère la mémoire allouée pour la liste.
 * \param liste La liste concernée.
 * \return NULL
 * \attention Mettre l'argument en valeur de retour.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
liste_t  libererListe(liste_t liste);


/**
 * \fn liste_t copierListe(liste_t src)
 * \brief Copie la liste src dans une autre liste.
 * \param src La liste à copier.
 * \remark Mettre l'argument en valeur de retour.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
liste_t copierListe(liste_t src);


/**
 * \fn bool estMembre(liste_t liste, elt_t e)
 * \brief Permet de savoir si une valeur de type elt_t est présente dans la liste
 * \param e L'élément concerné.
 * \param liste La liste à parcourir.
 * \return Retourne true si l'élément est membre, false sinon.
 * \author Nathan Salez
 * \version 1.0
 * \date 20/09/2018
 */
bool estMembre(liste_t l, elt_t e);


/**
 * \fn unsigned int occurenceValeur(liste_t liste, elt_t e)
 * \brief Permet de connaître le nombre d'occurences d'une valeur dans la liste.
 * \param e L'élément concerné.
 * \param liste La liste à parcourir.
 * \return Retourne le nombre d'occurences de e.
 * \author Nathan Salez
 * \version 1.0
 * \date 20/09/2018
 */
unsigned int occurenceValeur(liste_t liste, elt_t e);


/**
 * \fn elt_t trouverMinListe(liste_t liste)
 * \brief Permet de trouver la valeur minimale de la liste.
 * \param liste Liste non vide dans laquelle on cherche le plus petit élément.
 * \return le plus petit élément de la liste si elle n'est pas vide, ELT_HB sinon.
 * \author Nathan Salez
 * \version 1.0
 * \date 24/09/2018
 */
elt_t trouverMinListe(liste_t liste);


#endif //TP2_LIBLISTE_H
