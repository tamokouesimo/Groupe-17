#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
/*-----------------struct etudiant-------------------*/
struct produit
{
	char code[15];
	char libele [30];
	int prix;
};
typedef struct produit PRODUIT;
/*------------------liste etudiant------------------*/
struct cellule
{
	PRODUIT p;
	struct cellule *suivant;
};
typedef struct cellule *LISTE;
/*---------------creation d'une liste----------------*/
LISTE new_list(void)
{
	return NULL;
}
/*-----------------lit etudiant-----------------------*/
PRODUIT *lire_produit()
{
	PRODUIT *pt;
	pt=(PRODUIT*)malloc(sizeof(PRODUIT)*1);
	printf("entrez le code du produit: ");
	scanf("%s",pt->code);
	printf("entrez le libele du produit: " );
	scanf("%s",pt->libele);
    printf("entrez le prix du produit: ");
    scanf("%d", &pt->prix);
     return pt;
}
/*--------------------afficher d'un etudiant----------------*/
void afficher_produit(PRODUIT *pt)
{
	int i;
	printf("%s\t %s\t",pt->code, pt->libele );
	printf("%d\n", pt->prix);
}
/*------------------liste vide-----------------------------*/
int liste_vide(LISTE l)
{
	if(l==NULL)
		return TRUE;
	return FALSE;
}
/*--------------ajout en queue de la liste-----------------*/
LISTE ajout_en_queue(LISTE l , PRODUIT p)
{
	struct cellule *pt ;
	pt=(struct cellule*)malloc(sizeof(struct cellule));
	pt->p=p;
	pt->suivant = NULL;
       if(liste_vide(l))
		return pt;
	struct cellule *pt_1;
	pt_1= l;
	while (pt_1->suivant!=NULL)
		pt_1 = pt_1->suivant;
	pt_1->suivant = pt;
	return l;
}
/*-------------afficher liste etudiant-------------------------*/
void afficher_liste(LISTE l)
{
	if (liste_vide(l))
		printf("la liste est vide\n" );
	else
	{
		printf("CODE     LIBELE    PRIX \n");
		while(!liste_vide(l))
		{
	     afficher_produit(l);
		   l = l ->suivant;
		}
	}
}
/*---------------------------rechercher de l'etudiant-----------*/
PRODUIT search(LISTE l)
{
    struct cellule *t=l;
    char code[10];
	printf("entrez le code du produit a rechercher: ");
	scanf("%s", code);
	if(liste_vide(l))
        printf("    la liste est vide    ");
     while(!liste_vide(t))
     {
     	if(!strcmp(t->p.code, code))
     	{
     		printf("\n**** Voici les informations sur le produit rechercher.****\n\n");
     		printf("CODE     LIBELE  PRIX \n");
     		afficher_produit(t);
            return l->p;
     	}
     	t=t->suivant;
     }
     printf("le produit rechercher n'existe pas.\n");
     return  ;
}
/*-----------------------suprimer un etudiant------------------*/
LISTE suprimer(LISTE l)
{
	char code[10];
	printf("entrez le code du produit a superimer: ");
	scanf("%s", code);
	struct cellule *t1,*t2,*t=l;
	if(liste_vide(l))
        printf("    la liste est vide    ");
	if(!strcmp(t->p.code, code))
    {
        t1=t->suivant;
        l=t1;
        free(t);
        printf("\n le produit a ete suprimer avec succe et la liste restante est la suvante.\n\n");
    	afficher_liste(l);
         return l;
    }
	while(t->suivant!=NULL)
	{
        t1=t->suivant;

        if(!strcmp(t1->p.code, code))
        {
        	t->suivant=t1->suivant;
             free(t1);

    	printf("\n le produit a ete suprimer avec succes et la liste restante est la suvante.\n\n");
    	afficher_liste(l);
        	return l;
        }
        t=t->suivant;
	}
	printf("\nle produit dont le code  entrez n'existe pas.\n");
	 return l;
}
/*------------------------ajoute un etudiant dans la liste----------*/
LISTE ajoute_produit(LISTE l)
{
	PRODUIT *e =lire_produit();
	l=ajout_en_queue(l,*e);
	printf("\n      le produit a ete bien  ajouter     ");
	return l;
}
/*-------------trier les etudiant pas leur moyenne------------------*/
LISTE trie_bulle(LISTE l)
{
	struct cellule *t, *t1;
	int trier = FALSE;
	float a;
	char code[15], libele[10];
	int prix;
	t1 = (struct cellule*)malloc(sizeof(struct cellule)*1);
	while(trier==FALSE)
	{
        t=l;
		trier = TRUE;
		while(t->suivant != NULL)
		{
 			t1 = t->suivant;
			if(t->p.prix >t1->p.prix)
			{
			    strcpy(code,t->p.code);
                strcpy(libele,t->p.libele);
                strcpy(t->p.code,t1->p.code);
                strcpy(t->p.libele,t1->p.libele);
                strcpy(t1->p.code,code);
                strcpy(t1->p.libele, libele);
				a = t->p.prix;
				t->p.prix = t1->p.prix;
				t1->p.prix = a;
				trier = FALSE;
			}
            t = t->suivant;
		}
	}
	printf("     Voici la liste trier par ordre croisante de prix   \n\n");
	afficher_liste(l);
	return l;
}
/*----------enregistrer la liste etudiant dans un ficher------------*/
void list_to_file(LISTE l)
{
	FILE *fich;
	fich = fopen("produit.txt", "a");
	if(liste_vide(l))
    {
        printf("\non ne peut pas enregistrer dans les ficher car la liste est vide");
        return;
    }
	while(!liste_vide(l))
	{
		fprintf(fich, "%s\t %s\t", l->p.code, l->p.libele );
	    fprintf(fich, "%d\n",l->p.prix );
	    l = l->suivant;
	}
	fclose(fich);
	  printf("\n\nles produit ont ete enregistrer danns le ficher avec succe");
}
/*------------enregistrer les etudiant du ficher en memoire-----------*/
LISTE file_to_list(LISTE l)
{
	PRODUIT *p;
	p = (PRODUIT*)malloc(sizeof(PRODUIT));
    l= new_list();
	FILE *fich;
	fich = fopen("produit.txt","r");

	do
	{
		fscanf(fich,"%s %s %d",p->code, p->libele, &p->prix);

		l=ajout_en_queue(l , *p);
	} while(!feof(fich));
	 printf("voici les produit copie du ficher produit.\n\n");
     afficher_liste(l);
	 return l;
}
/*----------------nombre etudiant de la liste------------------*/
int taille(LISTE l)
{
	int i=0;
	while(!liste_vide(l))
	{
		i++;
		l=l->suivant;
	}
	return i;
}
/*--------------------menu ameliore----------------------------------*/

   void main(void)
{
    LISTE pt=new_list();
	int choix;
	int rep;
	do
	{
        printf("               MENU                           \n");
		printf("    1-Ajouter un produit.                     \n");
		printf("    2-Suprimer un produit.                    \n");
		printf("    3-Trier etudiant par le prix.              \n");
		printf("    4-Afficher les produits.                   \n");
		printf("    5-Rechercher un produit pas sont code.    \n");
		printf("    6-Ouvrir le ficher des produits.          \n");
		printf("    7-Enregistrer dans un ficher.             \n");
		printf("    8-Quitter.                                \n");
        do
          {
            printf("entrez votre choix: ");
			scanf("%d",&choix);
           } while( choix < 1 || choix > 8);
           switch(choix)
	     {

	      case 1: pt=ajoute_produit(pt);
	      break;
	      case 2: pt=suprimer(pt);
	      break;
	      case 3: pt=trie_bulle(pt);
	      break;
	      case 4:afficher_liste(pt);
	      printf("  \n\nOn a au total %d produit dans la liste des produit.",taille(pt));
	      break;
          case 5: search(pt);
          break;
          case 6: pt=file_to_list(pt);
          break;
          case 7: list_to_file(pt);
          break;
	      case 8: return;
          break;
        }

        do
           {
        	   printf("\n entrez 0 pour revenir au menu principale.\n");
	           scanf("%d",&rep);
	       } while(rep!=0);

    } while(rep==0);
}
