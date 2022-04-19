#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen.h"

void menu_kiir(char *menu_id){
    char fn[31];
    strcpy(fn, "menuk\\");
    strcat(fn, menu_id);
    strcat(fn, ".txt");
    FILE *f = fopen(fn, "r");
    char c;
    while (fscanf(f, "%c", &c) != EOF) {
        printf("%c", c);
    }
    fclose(f);
}

/// ///////////////////////////legyen char!!!
void jatekmenu(Jatek *s) {
    clear();
    s->t += most() - s->t_kezd;
    menu_kiir("Segitseg");
    /*printf("Mentés másként (új mentés): u\n");
    printf("Mentés:                     m\n\n");
    printf("Játék menete:\n");
    printf("Próbáld megtalálni az összes aknát! Az feltárt mezõk a szomszédos aknák számát tartalmazzák.\n");
    printf("Ha egy mezõt aknának gondolsz, ne tárd fel, hanem jelöld meg (különben elveszted a játékot).\n\n");
    printf("jelölés:                    \"j [sor száma] [oszlop száma]\"\n");
    printf("feltárás:                   \"[sor száma] [oszlop száma]\"\n");
    printf("\nVisszalépéshez nyomj entert!\n");*/
    char c;
    scanf("%c", &c);
   /** if (c == 'v')
        s->t_kezd = most();
    return 'j';
    return c;   */
}

char fomenu() {
    //FILE *fm = fopen("menuk\\Fomenu.txt", "r");
    clear();
    menu_kiir("Fomenu");
    //fclose(fm);
    char c;
    scanf("%c", &c);
    return c;
}
