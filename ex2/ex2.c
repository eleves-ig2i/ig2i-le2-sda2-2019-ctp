#include "libArbre.h"
#include <string.h>

/**
 * Ce programme est incomplet, il ne prend pas en compte les mots contenant 2 fois le même caractère.
 */
#define TAILLE_MAX 5

/**
 * Rentre une chaine saisie dans un arbre.
 */
noeudABR_t * saisirChaineDansArbre();

void vider_buffer();

/**
 * retourne 1 si a1 et a2 contiennent les mêmes éléments.
 * On suppose que ces 2 arbres ont le même nombre d'éléments.
 */
int memesElements(noeudABR_t * a1,noeudABR_t * a2);

/**
 * retourne 1 si a1 et a2 contiennent des anagrammes.
 * On utilise la première méthode pour effectuer cette fonction.
 */
int anagrammes(noeudABR_t * a1,noeudABR_t * a2);


void question1(noeudABR_t ** A1, noeudABR_t ** A2);
void question2(noeudABR_t * A1, noeudABR_t * A2);

int main()
{
    noeudABR_t * A1 = NULL;
    noeudABR_t * A2 = NULL;
    question1(&A1,&A2);
    question2(A1,A2);
    return 0;
}

noeudABR_t * saisirChaineDansArbre()
{
    char chaine[TAILLE_MAX+1];
    noeudABR_t * a = NULL;

    printf("Veuillez saisir une chaine de %d caractères\n",TAILLE_MAX);
    fgets(chaine,TAILLE_MAX+1,stdin);
    //printf("Chaine tapée ( taille %d : %s\n",strlen(chaine), chaine);

    for(size_t i = 0; i < strlen(chaine); i++)
    {
        a = insererABR(chaine[i],a);
    }


    return a;
}

void vider_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void question1(noeudABR_t ** A1, noeudABR_t ** A2)
{
    *A1 = saisirChaineDansArbre();
    vider_buffer();
    *A2 = saisirChaineDansArbre();
    creerDotABR(*A1,"testA1");
    creerDotABR(*A2,"testA2");
}


int memesElements(noeudABR_t * a1,noeudABR_t * a2)
{
    if( VIDE(a1) )      // on a le droit de retourner 1 car on suppose que a1 et a2 ont le même nombre d'éléments.
        return 1;

    //printf("DEBUG - estDansABR(%c,a2) == %d\n",RACINE(a1),estDansABR(RACINE(a1),a2));

    if( estDansABR(RACINE(a1),a2) == true )
    {
        return memesElements(GAUCHE(a1),a2) && memesElements(DROITE(a1),a2);
    }
    else
    {
        return 0;
    }

}



int anagrammes(noeudABR_t * a1,noeudABR_t * a2)
{
    // On vérifie d'abord si a1 et a2 ont le même nombre d'éléments.
    if( nbNoeudsABR(a1) == nbNoeudsABR(a2) )
    {
        printf("Les deux arbres ont le même nombre d'éléments.\n");
        if( memesElements(a1,a2) )
        {
            printf("Les deux arbres sont des anagrammes !\n");
            return 1;
        }
        else
        {
            printf("Mais ces 2 arbres n'ont pas les mêmes éléments !\n");
            return 0;
        }
    }
    else
    {
        printf("Les deux arbres n'ont pas le même nombre d'éléments.\n");
        return 0;
    }
}


void question2(noeudABR_t * A1, noeudABR_t * A2)
{
    anagrammes(A1,A2);
}