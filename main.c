#include "tools.h"


int main (){
  int n=-1;
  initialiser_ecran ();

  while (1)
    {
      n++;
      generer_labyrinth ();
      dessiner_labyrinth ();
      if(n>0){
        mvprintw (23, 7, "   Vous avez gagne %d fois!! ", n);}
      else{
        mvprintw (23, 7, "Vous n'avez pas encore gagne");
      }
      refresh ();
      while ((objectif.x != position.x) || (objectif.y != position.y)){
	  int c = wgetch (stdscr);
	  switch (c)
	    {
	    case KEY_UP:
	      se_deplacer (haut);
	      break;
	    case KEY_DOWN:
	      se_deplacer (bas);
	      break;
	    case KEY_RIGHT:
	      se_deplacer (droite);
	      break;
	    case KEY_LEFT:
	      se_deplacer (gauche);
	      break;
	    }
      }
    }
  refresh();
  return 0;
}

