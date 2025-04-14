#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
	assert((x>=0 && x<SIZE_X) && (y>=0 && y<SIZE_Y));
	Animal *animal = creer_animal(x,y,energie);
	while(*liste_animal){
		*liste_animal = (*liste_animal)->suivant;
	}
	(*liste_animal)->suivant = animal;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
	Animal *tmp = (Animal *)malloc(sizeof(Animal*));
	if(*liste == animal){
		tmp = (*liste)->suivant;
		free(liste);
		*liste = tmp;
	}
	else{
		while(*liste != animal){
			tmp = *liste;
			*liste = (*liste)->suivant;
		}
		tmp = (*liste)->suivant;
		free(liste);
		*liste = tmp;
	}
  return ;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
	Animal *tmp = (Animal *)malloc(sizeof(Animal*));
	while(liste){
		tmp = liste->suivant;
		free(liste);
		liste = tmp;
	}
  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie){
	FILE *f = fopen(nom_fichier,"w");
	if (f == NULL){
		printf("Impossible d'ouvrir le fichier");
		return 1;
	}
	
	fprintf(f,"<proies>\n");
	while(liste_proie){
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%f \n",liste_proie->x,liste_proie->y,liste_proie->dir[0],liste_proie->dir[1],liste_proie->energie);
		liste_proie = liste_proie->suivant;
	}
	fprintf(f,"</proies>\n");
	fprintf(f,"<predateurs>\n");
	while(liste_predateur){
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%f \n",liste_predateur->x,liste_predateur->y,liste_predateur->dir[0],liste_predateur->dir[1],liste_predateur->energie);
		liste_predateur = liste_predateur->suivant;
	}
	fprintf(f,"</predateurs>");
	fclose(f);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie){

	
}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    Animal *liste = la;
    while(liste){
    	if(rand()/RAND_MAX < p_ch_dir){
	    	liste->x += dir[x];
	    	liste->y += dir[y];
	    	
	    	if(liste->x > SIZE_X){
	    		liste->x -= SIZE_X;
	    	}
	    	if(liste->y > SIZE_Y){
	    		liste->y -= SIZE_Y;
	    	}
	    	if(liste->x < 0){
	    		liste->x += SIZE_X;
	    	}
	    	if(liste->y < 0){
	    		liste->y += SIZE_Y;
	    	}
	   }
	   liste = liste->suivant;
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
	Animal *la = *liste_animal;
	while(la){
		float p = (float)rand()/(float)RAND_MAX;
		if(p<p_reproduce){
			Animal *a = creer_animal(la->x,la->y,(la->energie)/2.0);
			ajouter_en_tete_animal(*liste_animal, a);
		}
		la = la->suivant;
	}
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/

}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/

  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){

   /*A Completer*/


}

