#include <stdio.h>
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>

//on commence par d�finir une nouvelle structure: coordonn�es de points

struct coordonnees{int x;int y;};

const struct coordonnees haut = { 0, -1 };
const struct coordonnees bas = { 0, 1 };
const struct coordonnees droite = { 1, 0 };
const struct coordonnees gauche = { -1, 0 };

struct coordonnees voisins[4] = {droite,gauche,haut,bas};

struct coordonnees position;
struct coordonnees objectif;

#define largeur 41  //largeur de la table du jeu
#define longueur 23  //longueur de celle-ci


int blocs_visites[largeur][longueur]={0}; //Au d�but toute la labyrinth est sous forme de blocs et il n'y a aucun passage
int matrice_de_labyrinth[largeur][longueur]={1};



//La fonction suivante sert � initialiser l'�cran (ncurses)

void initialiser_ecran (void){
  initscr ();
  noecho ();
  keypad (stdscr, TRUE);
  refresh ();
}


//La fonction suivante est pour g�n�rer un labyrinth en utilisant l'algorithme de depth first search

void depth_first_search (int x, int y){
  if (blocs_visites[x][y]==1)
    return;
  blocs_visites[x][y] = 1;
  matrice_de_labyrinth[x][y] = 0;
  int voisins_non_visites;
  do
    {
      voisins_non_visites = 0;
      int i;
      for (i = 0; i < 4; i++)
	  {
	     int _x = x + (2 * voisins[i].x);
	     int _y = y + (2 * voisins[i].y);
	     if (longueur > _y && _y > 0 && largeur > _x && _x > 0 && blocs_visites[_x][_y] == 0)
	       {
	        voisins_non_visites++;
	       }
	}
      if (voisins_non_visites > 0)
	  {
	      int internal_counter = -1;
	      int j = 0;
	      int choix = rand() % (voisins_non_visites + 1);
	      do
	      {
	          int _x = x + (2 * voisins[j-1].x);
	          int _y = y + (2 * voisins[j-1].y);
	          if (longueur > _y && _y > 0 && largeur > _x && _x > 0 && blocs_visites[_x][_y] == 0)
		         internal_counter++;
              j++;
	      }
	      while (internal_counter != choix - 1);
	      j--;
          matrice_de_labyrinth[x + voisins[j-1].x][y + voisins[j-1].y] = 0;
	      depth_first_search (x + (2 * voisins[j-1].x), y + (2 * voisins[j-1].y));
	  }
    }
  while (voisins_non_visites > 0);
}  /*Si cette case (x,y) a plus d'un seul voisin de voisins non visit� (cases qu'on peut trouver en se d�pla�ant de 2 cases
     vers le haut, le bas, la droite ou la gauche), l'algorithme de depth first search va rester sur cette case et
     en m�me temps, il va s'�x�cuter pour ces cases mentionn�es*/


//La fonction suivante est pour dessiner le labyrinth

void dessiner_labyrinth (){
  int i, j;
  for (i = 0; i < largeur; i++)
    {
      for (j = 0; j < longueur; j++)
	{
	  move (j , i );
	  if (matrice_de_labyrinth[i][j] == 1){
        addch('|');}

      else
	    addch (' ');
	}
    }
  move (1, 1);
  addch (ACS_CKBOARD);
  move (position.y, position.x);
  addch (ACS_DIAMOND);
}


void generer_labyrinth (){
  int i, j;
  for (i = 0; i < largeur; i++)
    {
      for (j = 0; j < longueur; j++)
	{
	  matrice_de_labyrinth[i][j] = 1;
	  blocs_visites[i][j] = 0;
	}
    }

  position.x = largeur - 2;
  position.y = longueur - 2;
  objectif.x = 1;
  objectif.y = 1;
  dessiner_labyrinth ();

  depth_first_search (1,1);
}



void se_deplacer (struct coordonnees mouvement){
  if (matrice_de_labyrinth[position.x + mouvement.x][position.y + mouvement.y] ==0)
    {
      mvprintw (position.y, position.x, " ");
      position.x += mouvement.x;
      position.y += mouvement.y;
      move (position.y, position.x);
      if (mouvement.x==0 && mouvement.y==1)
        addch (ACS_DARROW);
      if (mouvement.x==1 && mouvement.y==0)
        addch (ACS_RARROW);
      if (mouvement.x==0 && mouvement.y==-1)
        addch (ACS_UARROW);
      if (mouvement.x==-1 && mouvement.y==0)
        addch (ACS_LARROW);
    }
  else{beep();}
  move (0, 0);
}


