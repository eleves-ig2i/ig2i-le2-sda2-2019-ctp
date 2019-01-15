/* ------------------------------------------------------------------------ */
/**
 *  \file       abr.c
 *  \brief      Implémentation d'un module de gestion d'arbres binaires
 *              de recherche
 *
 *  \date       25 Septembre 2018
 *  \author     S. El Khattabi
 *  \version    1.0
 *
 */
/* ------------------------------------------------------------------------ */
/*					I N C L U D E (s)   S T A N D A R D (s)					*/
/* ------------------------------------------------------------------------ */

#include <string.h>     // pour la fonction genererDotPng()
#include <sys/stat.h>   // idem

/* ------------------------------------------------------------------------ */
/*					I N C L U D E (s)   S P É C F I Q U E (s)				*/
/* ------------------------------------------------------------------------ */
#include "libArbre.h"

/* ------------------------------------------------------------------------ */
/*		P R O T O T Y P E S   D E S   F O N C T I O N S   L O C A L E S		*/
/* ------------------------------------------------------------------------ */
static void displayABR(const noeudABR_t * a);
static void displayInverseABR(const noeudABR_t * a);
static void genererDotPng(const noeudABR_t * a, FILE *fp);
/**
 *  \fn         noeudABR_t * supprimerRacineABR(elt_t e, noeudABR_t * a)
 *  \brief      Utilisé dans supprimerRacineABR, supprime la racine de l'arbre, et renvoie l'arbre initial.
 *  \param      e       l'élément à supprimer
 *  \param      a   le pointeur sur la racine de l'arbre
 *  \return     le pointeur sur l'arbre après suppression
 */
static noeudABR_t * supprimerRacineABR(elt_t e, noeudABR_t * a);

/* ------------------------------------------------------------------------ */
static void displayABR(const noeudABR_t * a)
{
    // Affichage GRD
    if( PASVIDE(a) )
    {
        displayABR(GAUCHE(a));      // G pour gauche
        afficherElt(NULL,&RACINE(a),NULL);
        displayABR(DROITE(a));       // D pour droit
    }
}

/* ------------------------------------------------------------------------ */
static void displayInverseABR(const noeudABR_t * a)
{
    // Affichage DRG
    if( PASVIDE(a) )
    {
        displayInverseABR(DROITE(a));      // D pour droit
        afficherElt(NULL,&RACINE(a),NULL);
        displayInverseABR(GAUCHE(a));     // G pour gauche
    }
}

/* ------------------------------------------------------------------------ */
static noeudABR_t * supprimerRacineABR(elt_t e, noeudABR_t * a)
{
    assert( PASVIDE(a) && EGAL(a->elt,e) );

    if( EST_FEUILLE(a) )
    {
        //printf("DEBUG - a est une feuille.\n");
        free(a);
        return NULL;
    }

    if( VIDE(GAUCHE(a)))
    {
        noeudABR_t* aux = copierABR(DROITE(a));
        //printf("DEBUG - VIDE(GAUCHE()) - aux :\n"); afficherABR(aux);
        free(a);
        //a = NULL;
        return aux;
    }

    if( VIDE(DROITE(a)) )
    {
        noeudABR_t* aux = copierABR(GAUCHE(a));
        //printf("DEBUG - VIDE(DROIT()) - aux :\n"); afficherABR(aux);
        free(a);
        //a = NULL;
        return aux;
    }

    //printf("DEBUG - a contient deux descendants, on va chercher le plus petit élément du sous arbre droit.\n");
    elt_t minArbreDroit;
    chercherMinABR(DROITE(a),&minArbreDroit);
    DROITE(a) = supprimer1EltABR(minArbreDroit,DROITE(a));
    copierElt(&RACINE(a),&minArbreDroit);

    return a;
}


/* ------------------------------------------------------------------------ */
noeudABR_t * insererABR(elt_t e, noeudABR_t * a)
{
    if( VIDE(a) )   // On crée une feuille (cas trivial de la récursivité)
        return creer1Noeud(e,NULL,NULL);

    if( SUPERIEUR_STRICT(a->elt,e) )
        GAUCHE(a) = insererABR(e,GAUCHE(a));
    else if( SUPERIEUR_STRICT(e,a->elt) )                    // On évite les doublons.
        DROITE(a) = insererABR(e,DROITE(a));

    return a;
}


int   estDansABR (elt_t e, const noeudABR_t * a)
{
    if( VIDE(a) )   //1er cas trivial
        return false;

    if ( EGAL(a->elt,e))   // 2e cas trivial
        return true;       // true retourne -1

    // On effectue le parcours GAUCHE -> DROITE
    if ( estDansABR(e,GAUCHE(a)) )
        return true;
    else
        return estDansABR(e,DROITE(a));
}

/* ------------------------------------------------------------------------ */
int hauteurABR(const noeudABR_t * a)
{
    if( VIDE(a) )       // Cas trivial : ABR vide == niveau -1
        return -1;

    return 1+ MAX( hauteurABR(GAUCHE(a)),hauteurABR(DROITE(a)) );
}

unsigned int nbNoeudsABR(const noeudABR_t * a)
{
    if( VIDE(a) )       // Cas trivial : ABR vide <=> 0 élément
        return 0;

    /*if( EST_FEUILLE(a) )    // Cas trivial : on a une feuille <=> 1 élément
        return 1;*/

    return 1 + nbNoeudsABR(GAUCHE(a)) + nbNoeudsABR(DROITE(a));


}

/* ------------------------------------------------------------------------ */
noeudABR_t * supprimerABR(noeudABR_t * a)
{
    if( VIDE(a) )
        return NULL;

    if( EST_FEUILLE(a))
    {
        free(a);
        return NULL;
    }

    GAUCHE(a) = supprimerABR(GAUCHE(a));
    DROITE(a) = supprimerABR(DROITE(a));
    free(a);
    return NULL;
}

/* ------------------------------------------------------------------------ */
noeudABR_t * copierABR (const noeudABR_t * a)
{
    if( VIDE(a) )
        return NULL;

    /*if( EST_FEUILLE(a))
        return creer1Noeud(a->elt,NULL,NULL);*/

    noeudABR_t * aux = creer1Noeud(a->elt,NULL,NULL);
    GAUCHE(aux) = copierABR(GAUCHE(a));
    DROITE(aux) = copierABR(DROITE(a));

    return aux;
}

/* ------------------------------------------------------------------------ */
int egalABR (const noeudABR_t * a1, const noeudABR_t * a2)
{
    if( VIDE(a1) || VIDE(a2) )
        return VIDE(a1) && VIDE(a2);


    if( EST_FEUILLE(a1) || EST_FEUILLE(a2) )
    {
        if( EST_FEUILLE(a1) && EST_FEUILLE(a2) )
            return EGAL(a1->elt,a2->elt);
        else
            return false;
    }

    return egalABR(GAUCHE(a1),GAUCHE(a2)) && egalABR(DROITE(a1),DROITE(a2));
}

/* ------------------------------------------------------------------------ */
static void  genererDotPng(const noeudABR_t * a, FILE *fp)
{
    if( VIDE(a) )
        return;

    fprintf(fp,"%c [label = \"{<c> %c | { <g> | <d>}}\"];\n",a->elt,a->elt);        // on écrit la ligne commune à tous les arbres non vides.

    if( VIDE(DROITE(a)) || VIDE(GAUCHE(a))) {            // Si a ne possède pas 2 descendants directs.
        fprintf(fp, "%c [label = \"{<c> %c | { <g>", a->elt, a->elt);              // on écrit une ligne où il y a aura AU MOINS une inscription NULL.

        if (VIDE(GAUCHE(a)))
            fprintf(fp, " NULL");

        fprintf(fp, " | <d>");

        if (VIDE(DROITE(a)))
            fprintf(fp, " NULL");

        fprintf(fp, "}}\"];\n");
    }

    if( !EST_FEUILLE(a) )           // si a possède au moins un descendant
    {
        if( PASVIDE(GAUCHE(a)) )
            fprintf(fp,"%c:g -> %c;\n",a->elt,GAUCHE(a)->elt);
        genererDotPng(GAUCHE(a),fp);
        if( PASVIDE(DROITE(a)) )
            fprintf(fp,"%c:d -> %c;\n",a->elt,DROITE(a)->elt);
        genererDotPng(DROITE(a),fp);
    }


}

/* ------------------------------------------------------------------------ */

void chercherMinABR(noeudABR_t * a,elt_t *min)
{
    elt_t elt_hb = 1024;
    if( VIDE(a) )       // Cas particulier : arbre vide, on renvoie une valeur d'erreur.
    {
        copierElt(min, &elt_hb);
        return;
    }

    if( VIDE(GAUCHE(a)) || EST_FEUILLE(a) )
    {
        copierElt(min,&RACINE(a));  // Cas trivial de la récursivité : on renvoie l'élément si l'arbre est une feuille
                        // Mais aussi lorsqu'on ne peut plus aller à gauche !
        return;
    }

    chercherMinABR(GAUCHE(a),min);   // Cas général de la récursivité : on va chercher l'élément le plus à gauche de l'arbre.
}

/* ------------------------------------------------------------------------ */
noeudABR_t * supprimer1EltABR(elt_t e, noeudABR_t * a)
{
    if( VIDE(a) )
        return NULL;

    if( EGAL(a->elt,e) )
    {
        //printf("DEBUG - Elément trouvé !\n");
        return supprimerRacineABR(e,a);
    }

    if( SUPERIEUR_STRICT(a->elt,e))
        GAUCHE(a) = supprimer1EltABR(e,GAUCHE(a));
    else
        DROITE(a) = supprimer1EltABR(e,DROITE(a));

    return a;
}
/* ------------------------------------------------------------------------ */


/* ------------------------------------------------------------------------ */
/*			F O N C T I O N S   M I S E S   À   D I S P O S I T I O N		*/
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
noeudABR_t * creer1Noeud(elt_t e, noeudABR_t * g, noeudABR_t * d)
{
    noeudABR_t * p;
    p = (noeudABR_t *)malloc(sizeof(noeudABR_t));
    if (p != NULL)
    {
        copierElt(&RACINE(p),&e);
        p->gauche = g;
        p->droit = d;
    }
    return p;
}

/* ------------------------------------------------------------------------ */
void afficherABR(const noeudABR_t * a)
{
    displayABR(a);
    printf("\n");
}

/* ------------------------------------------------------------------------ */
void afficherInverseABR(const noeudABR_t * a)
{
    displayInverseABR(a);
    printf("\n");
}

/* ------------------------------------------------------------------------ */
/**
 *  \fn         void creerDotABR(const T_ABR arbre, const char *basename)
 *  \brief      Créer le fichier .dot représentant l'arbre binaire de
 *				rechercher
 *  \param      arbre  l'arbre binaire
 *  \param      basename le nom du fichier à créer, sans son extension qui
 *				sera ajoutée (.dot) ainsi qu'un numéro de version
 *  \return    	néant
 *	\note		Le fichier est refermé en fin d'exécution de la fonction
 *	\remark		Ne convient (dans l'état) que pour des ABR dont
 *				les noeuds contiennent des valeurs entières toutes distinctes
 */
void creerDotABR(const noeudABR_t * arbre, const char *basename)
{
    static char oldBasename[FILENAME_MAX + 1] = "";
    char fnameDot [FILENAME_MAX + 1];
    char fnamePng [FILENAME_MAX + 1];
    static unsigned int noVersion = 0;
    char	cmdLine [2 * FILENAME_MAX + 20];
    FILE *fp;
    
    /*
     *	Au premier appel, création (si nécessaire) des répertoires
     *	où seront rangés les fichiers .dot et .png générés par cette
     *	fonction
     */
    if (oldBasename[0] == '\0')
    {
        mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
        mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    }
    /*
     *	S'il y a changement de nom de base alors recommencer
     *	à zéro, la numérotation des fichiers
     */
    if (strcmp(oldBasename, basename) != 0)
    {
        noVersion = 0;
        strcpy(oldBasename, basename);
    }
    sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
    sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);
    if ( (fp = fopen(fnameDot, "w")) == NULL)
    {
        fprintf(stderr, "Impossible de creer le fichier \"%s\"\n", fnameDot);
        exit(EXIT_FAILURE);
    }
    
    noVersion ++;
    fprintf(fp, "digraph %s {\n", basename);
    fprintf(fp,
            "\tnode [\n"
            "\t\tfontname  = \"Arial bold\" \n"
            "\t\tfontsize  = \"14\"\n"
            "\t\tfontcolor = \"red\"\n"
            "\t\tstyle     = \"rounded, filled\"\n"
            "\t\tshape     = \"record\"\n"
            "\t\tfillcolor = \"grey90\"\n"
            "\t\tcolor     = \"blue\"\n"
            "\t\twidth     = \"2\"\n"
            "\t]\n"
            "\n"
            "\tedge [\n"
            "\t\tcolor     = \"blue\"\n"
            "\t]\n\n"
            );
    
    if (arbre == NULL)
        fprintf(fp, "\n");
    else
        genererDotPng(arbre, fp);
    
    fprintf(fp, "}\n");	
    fclose(fp);
    
    sprintf(cmdLine, "%s -Tpng  %s -o %s", DOT_CMD, fnameDot, fnamePng);
    system(cmdLine);
    
    printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}
/* ------------------------------------------------------------------------ */
