/**
 * \file libListe.c
 * \author Nathan Salez
 * \brief code source des fonctions de la bibliothèque de TAD de gestion de listes chaînées.
 * \version 1.0
 * \date 19/09/2018
 */
#include "libListe.h"


elt_t eltTeteListe(liste_t l)
{
    elt_t elt_hb ={11,11} ;
    if ( VIDE_LISTE(l) )
        return elt_hb;

    return TETE(l);
}



unsigned int nbrEltsListe(liste_t l)
{
    if( VIDE_LISTE(l) ) return 0;     // Cas trivial

    return nbrEltsListe(RESTE(l)) +1;    // Cas général de la récursivité
}


void afficherListe(liste_t l)
{
    if ( VIDE_LISTE(l) ) return;  // Cas trivial

    afficherElt("---> ",&TETE(l),NULL );        // Cas général
    afficherListe( RESTE(l) );      // de la récursivité
}


void afficherListeInverse(liste_t l)
{
    if ( VIDE_LISTE(l) ) return; // Cas trivial

    afficherListeInverse( RESTE(l) );   // Cas général
    afficherElt("---> ",&TETE(l),NULL );            // de la récursivité
}


liste_t creerMaille(elt_t e,liste_t l)
{
    liste_t aux = (liste_t) malloc( sizeof(maille_t) );
    assert( aux != NULL);
    copierElt(&TETE(aux),&e);
    RESTE(aux) = l;

    return aux;
}


liste_t insererEltTeteListe(elt_t e, liste_t liste)
{
    return creerMaille(e,liste);
}



liste_t insererEltQueueListe(elt_t e, liste_t liste)
{
    if( VIDE_LISTE(liste) )
        return creerMaille(e,NULL);

    else    // Récursivité
    {
        if( VIDE_LISTE(RESTE(liste)) )    // Cas trivial
        {
            RESTE(liste) = creerMaille(e, NULL);
            return liste;
        }
        else
        {
            insererEltQueueListe(e,RESTE(liste));   // Cas général de la récursivité.
            return liste;
        }
    }
}


liste_t supprimerDernierElementListe(liste_t liste)
{

    if( !VIDE_LISTE(liste) && !VIDE_LISTE(RESTE(liste)) )
    {
        if( VIDE_LISTE(RESTE(RESTE(liste))) ) {   // Cas trivial.
            free(RESTE(liste));             // On libère la mémoire associée à l'élément. *(RESTE(liste)) = 0
            RESTE(liste)=NULL;              // On coupe la liaison entre l'avant dernier et le dernier élément.
            return liste;
        }
        else
            return supprimerDernierElementListe(RESTE(liste)); // Cas général
    }
    else    // La liste contient qu'un seul élément ou 0 élément.
    {
        if ( !(VIDE_LISTE(liste)))    // La liste contient un élément.
        {
            free(liste);
        }

        return NULL;
    }
}


liste_t supprimerPremierElementListe(liste_t liste)
{
    if( VIDE_LISTE(liste) )
        return NULL;
    else
    {
        if( VIDE_LISTE(RESTE(liste)) )
        {
            free(liste);
            return NULL;
        }
        else
        {
            liste=RESTE(liste);
            return liste;
        }
    }
}


liste_t libererListe(liste_t liste)
{
    if( !VIDE_LISTE(liste) )  // Cas général de la récursivité
    {
        liste = libererListe(RESTE(liste));
        free(liste);
    }
    return liste;      // Cas trivial, on retourne NULL

}



liste_t insererEltListeOrdonnee(elt_t e, liste_t liste) {

    if (VIDE_LISTE(liste))        // Cas 1 : liste vide
        return creerMaille(e, NULL);

    if ( VIDE_LISTE(RESTE(liste)) || SUPERIEUR_STRICT(TETE(liste),e) )// Cas 2 : liste à un élément OU l'élément à insérer est strictement inférieur à la tête de liste
    {
        if ( SUPERIEUR_STRICT(e,TETE(liste)) )      // TETE(liste) < e
            return insererEltQueueListe(e, liste);   // e est plus grand => on l'insère en fin de liste.
        else
            return insererEltTeteListe(e, liste);
    }



    // Cas 3 : cas trivial 2 de la récursivité = on insère e dans une liste à 2 éléments
    if ( SUPERIEUR_STRICT(TETE(RESTE(liste)), e) )      // TETE(RESTE(liste)) > e
    {
        liste_t aux = creerMaille(e, RESTE(liste));      // aux pointe sur le reste de la liste.
        // Mais la tête de liste pointe aussi sur le reste de la liste.
        RESTE(liste) = aux;             // la tête de liste pointe désormais sur aux
        return liste;
    }
    else    // Cas 4 : cas général de la récursivité.
    {
        // ATTENTION, on ne doit pas mettre liste = insererEltListeOrdonnee(e,RESTE(liste))
        // Dans ce cas, on perd automatiquement la 1er élément de la liste chaînée. (même chose avec inserer en fin de liste)
        RESTE(liste) = insererEltListeOrdonnee(e, RESTE(liste));
        return liste;
    }
}



liste_t copierListe(liste_t src)
{
    if(VIDE_LISTE(src))
        return NULL;

    return creerMaille(TETE(src),copierListe(RESTE(src)));
}


bool estMembre(liste_t liste, elt_t e)
{
    if( VIDE_LISTE(liste) )
        return false;
    else if( EGAL(TETE(liste),e) )
        return true;
    else
        return estMembre(RESTE(liste),e);
}


unsigned int occurenceValeur(liste_t liste, elt_t e)
{
    if( VIDE_LISTE(liste) )
        return 0;
    if( EGAL(eltTeteListe(liste),e) )
        return 1 + occurenceValeur(RESTE(liste),e);
    else
        return occurenceValeur(RESTE(liste),e);
}


liste_t supprimerElementListe(elt_t e, liste_t liste)
{
    // On veut supprimer toutes les occurences d'un élément.
    if( VIDE_LISTE(liste) )   // Cas 1 : liste vide.
        return liste;

    if( estMembre(liste,e) == true )
    {
        RESTE(liste) = supprimerElementListe(e,RESTE(liste));   // Cas général de la récursivité => on supprime d'abord les <e> en fin de liste.

        if( EGAL(e,TETE(liste)) )      // Cas trivial de la récursivité
            return supprimerPremierElementListe(liste);

    }
    return liste;
}


elt_t trouverMinListe(liste_t liste)
// On effectue le parcours de la liste dans le sens inverse (on commence par la fin de la liste pour arriver au début.
// Remarque : l'implémentation de la recherche de la valeur max est quasi identique à cette fonction.
// Il faut juste changer la comparaison.
{
    elt_t elt_hb = {11,11};
    if( VIDE_LISTE(liste) )       // Cas particulier : liste vide.
        return elt_hb;

    if ( !VIDE_LISTE(RESTE(liste)) )      // Cas général de la récursivité, on va plus loin dans la liste d'abord.
    {
        elt_t min = trouverMinListe(RESTE(liste));  // On obtient l'élément minimum du reste de la liste
        // on effectue la comparaison avec la tête de liste.
        if( !SUPERIEUR_EGAL(TETE(liste),min) )   // TETE(liste) < min
        {
            return TETE(liste);
        }
        else
        {
            return min;
        }
    }
    else
    {
        // Cas particulier de la récursivité, liste à un membre => on renvoie à fortiori la tête
        return TETE(liste);
    }
}