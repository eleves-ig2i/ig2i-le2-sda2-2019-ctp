/**
 * \file libElt.c
 * \include "libElt.h"
 * \author Nathan Salez
 * \brief code source des fonctions du TAD utilisé pour les listes chaînées.
 * \note le type utilisé actuellement est : int
 * \version 1.1
 * \date 18/09/2018
 */
#include "libElt.h"


void initialiserElt(elt_t *e, size_t nbSousElts)
{
    assert(nbSousElts != 0);
    e = (elt_t *)malloc(sizeof(elt_t)*nbSousElts);
    assert( e != NULL );
}

void saisirElt(elt_t *e, const char * messageSaisie)
{
    assert( e != NULL && messageSaisie != NULL );
    printf("%s\n",messageSaisie);
    scanf("%c",e);
}


void copierElt(elt_t* d, const elt_t* s)
{
    assert( d != NULL);
    if( s != NULL)
        *d = *s;
    else
       *d = ELT_HB;
}


short comparerElt(elt_t elt1,elt_t elt2)
{
    if( elt1 == elt2)
        return 0;
    if( elt1 > elt2)
        return 1;

    return -1;
}


void afficherElt(const char * messagePreAffichage, const elt_t* e,  const char * messagePostAffichage)
{
    assert( e != NULL);

    if( messagePreAffichage != NULL)
        printf("%s",messagePreAffichage);

    printf("%c",*e);

    if( messagePostAffichage != NULL)
        printf("%s",messagePostAffichage);
}


void libererElt(elt_t *e)
{
    if( e != NULL)
    {
        free(e);
        e = NULL;
    }
}