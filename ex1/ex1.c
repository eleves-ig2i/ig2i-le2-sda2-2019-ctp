#include "libListe.h"
#include "libElt.h"


/**
 * Questions 1 à 3 effectuées.
 * Question 4 à moitié faite.
 */

/**
 * Les coordonnées de la matrice varient de (0,0) à (TAILLE_MATRICE-1,TAILLE_MATRICE-1)
 */
#define TAILLE_MATRICE 10

typedef enum{bas,droite,gauche,haut} T_Direction;

/**
 * QUESTION 1 : la structure de données a été modifié dans libListe.h et libElt.h
 */

/**
 *  Insère un morceau de corps dans le snake, si la coordonnee en paramètre est adjacente à la queue du snake.
 */
liste_t insererQueue(elt_t coordonnee,liste_t snake);

/**
 * Utilisé dans la fonction insererQueue, vérifie si la coordonnee en paramètre est adjacente à la queue du snake.
 */
bool estCompatible(elt_t coordonnee,liste_t snake);




/**
 * Affiche le snake dans une matrice de taille tailleMatrice.
 */
void afficherSnake(liste_t snake, unsigned int tailleMatrice);


/**
 * Utilisé dans la fonction afficherSnake, affiche la tête de snake.
 */
void afficherTeteSnake(liste_t snake);





/**
 * Fait bouger le snake dans une direction d, on suppose que snake existe.
 */
liste_t mouvement(T_Direction d, liste_t snake);

/**
 * Utilisé dans mouvement
 */
liste_t deplacerSnake(short x, short y, liste_t snake);

int main()
{
    liste_t snake = NULL;
    elt_t tableauCoordonnees[10] = {{2,2},{2,3},{3,3},{3,2},{3,1},{2,1}};
    for(size_t i = 0; i < 6;i++) {
        printf("Coordonnee insérée : (%u,%u)\n",tableauCoordonnees[i].x,tableauCoordonnees[i].y);
        snake = insererQueue(tableauCoordonnees[i], snake);
    }

    afficherSnake(snake,TAILLE_MATRICE);
    snake = mouvement(haut,snake);
    //afficherSnake(snake,TAILLE_MATRICE);
    return 0;
}



// question 2

bool estCompatible(elt_t coordonnee,liste_t snake)
{
    if( coordonnee.x >= TAILLE_MATRICE || coordonnee.y >= TAILLE_MATRICE )  // on vérifie d'abord si la coordonnée est correcte.
    {
        //printf("DEBUG - Coordonnée invalide ! => pas d'insertion\n");
        return false;
    }

    if( VIDE_LISTE(snake) ) // si on n'a pas toujours pas inséré snake !
    {
        //printf("DEBUG - Snake vide ! => insertion\n");
        return true;
    }

    if( estMembre(snake,coordonnee) ) // // on vérifie que la coordonnée actuelle n'est pas déjà occupé par le snake.
    {
        //printf("DEBUG - Coordonnée déjà occupée par le snake ! => pas d'insertion\n");
        return false;
    }

    if( VIDE_LISTE(RESTE(snake)) )  // on est à la queue du snake.
    {
        // 4 possibilités :
        if( TETE(snake).x + 1 == coordonnee.x &&  TETE(snake).y == coordonnee.y )   // en bas
        {
            //printf("DEBUG - On insère en bas du snake !\n");
            return true;
        }
        if( TETE(snake).x - 1 == coordonnee.x &&  TETE(snake).y == coordonnee.y )   // en haut
        {
            //printf("DEBUG - On insère en haut du snake !\n");
            return true;
        }
        if( TETE(snake).x == coordonnee.x && TETE(snake).y+1 == coordonnee.y )  // à droite
        {
            //printf("DEBUG - On insère à droite du snake !\n");
            return true;
        }
        if( TETE(snake).x == coordonnee.x && TETE(snake).y-1 == coordonnee.y )  // à gauche
        {
            //printf("DEBUG - On insère à gauche du snake !\n");
            return true;
        }

        return false;
    }

    return estCompatible(coordonnee,RESTE(snake));
}


liste_t insererQueue(elt_t coordonnee, liste_t snake)
{
    if( estCompatible(coordonnee,snake) )
    {
        snake = insererEltQueueListe(coordonnee,snake); // fonction créée lors du TP2
    }

    return snake;
}



void afficherTeteSnake(liste_t snake)
{
    assert(snake != NULL);
    if( VIDE_LISTE(RESTE(snake)) )
    {
        printf("^");    // par défaut, on affiche ^
    }
    else
    {
        if( TETE(RESTE(snake)).x + 1 == TETE(snake).x ) {
            // haut
            printf("^");
            return;
        }

        if( TETE(RESTE(snake)).x - 1 == TETE(snake).x ) {
            // bas
            printf("v");
            return;
        }

        if( TETE(RESTE(snake)).y - 1 == TETE(snake).y ) {
            // gauche
            printf("<");
            return;
        }

        if( TETE(RESTE(snake)).y + 1 == TETE(snake).y ) {
            // droite
            printf(">");
            return;
        }
    }

}


void afficherSnake(liste_t snake, unsigned int tailleMatrice)
{
    elt_t coordonneeActuelle = {0,0};
    elt_t teteSnake={TAILLE_MATRICE,TAILLE_MATRICE};
    if( !VIDE_LISTE(snake) )
        teteSnake = TETE(snake);

    for(unsigned int ligne =0; ligne < tailleMatrice; ligne++)
    {
        for(unsigned int colonne =0; colonne < tailleMatrice; colonne++)
        {
            printf("|");
            // 3 cas d'affichage possible :
            //printf("Coordonnée actuelle : (%u,%u)\n",coordonneeActuelle.x,coordonneeActuelle.y);
            if( estMembre(snake,coordonneeActuelle) == false)
            {
                // la case n'est pas occupée par le snake
                printf(" ");
            }
            else if( EGAL(teteSnake,coordonneeActuelle) )
            {
                // On affiche la tête du snake, il faut déterminer la direction !
                afficherTeteSnake(snake);
            }
            else
            {
                // on affiche un morceau du corps du snake.
                printf("*");
            }


            coordonneeActuelle.y++;
        }

        coordonneeActuelle.x++;
        coordonneeActuelle.y = 0;
        printf("\n");
    }
}



liste_t mouvement(T_Direction d, liste_t snake)
{
    switch(d)
    {
        case haut :
            snake = deplacerSnake(0,-1,snake);
        break;

        case bas :
            snake = deplacerSnake(0,1,snake);
        break;

        case droite :
            snake = deplacerSnake(1,0,snake);
            break;

        case gauche :
            snake = deplacerSnake(-1,0,snake);
            break;

        default : printf("Direction non prévue.\n");
    }

    return snake;
}


liste_t deplacerSnake(short x, short y, liste_t snake)
{
    if( VIDE_LISTE(snake) )
        return snake;

    // todo : prévoir le cas où le snake dépasse les limites de la matrice

    TETE(snake).x += x;
    TETE(snake).y += y;

    // todo : changer x et y
    // piste : retrouver les coordonnées du corps suivant, et adapter le déplacement en conséquence.
    return deplacerSnake(x,y,RESTE(snake));



}
