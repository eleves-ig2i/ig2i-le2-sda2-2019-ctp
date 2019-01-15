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


void initialiserElt(elt_t *e)
{
    e = (elt_t *)malloc(sizeof(elt_t));
    assert( e != NULL );
}

void saisirElt(elt_t *e, const char * messageSaisie)    // non utilisé
{
    assert( e != NULL && messageSaisie != NULL );
    printf("%s\n",messageSaisie);
    //scanf("%d",e);
}


void copierElt(elt_t* d, const elt_t* s)
{
    elt_t elt_hb = {10,10};
    assert( d != NULL);
    if( s != NULL)
        *d = *s;
    else
        *d = elt_hb;
}


short comparerElt(elt_t elt1,elt_t elt2)    // utilisé dans la question 2
{
    if( elt1.x == elt2.x && elt1.y == elt2.y)
        return 0;
    else
        return 1;
}


void afficherElt(const char * messagePreAffichage, const elt_t* e,  const char * messagePostAffichage)  // non utilisé
{
    assert( e != NULL);

    if( messagePreAffichage != NULL)
        printf("%s",messagePreAffichage);

    //printf(".",*e);

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