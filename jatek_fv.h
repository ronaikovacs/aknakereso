//#include "gen.h"


int **gen_jatekter(Jatek *s, int ertek);

Jatek start();

void aknaz(Jatek *s);

int szomszed_akna(Jatek *s, int x, int y);

void szamol(Jatek *s);

void kirajzol(Jatek *s);

void ellenorzes(Jatek *s, int *allap);

void felderit(Jatek *s, int x, int y);

void gameover(Jatek *s, int allap);

void javitando(char *mod, int *sor, int *oszlop, Jatek *s);

void felszabadit(Jatek *s);

void jatekmenet();
