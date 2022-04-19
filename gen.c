#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

/**Jatek tipus*/
typedef struct Jatek{
    //egy jatek parameterei:
    int X; int Y;   //lathato meret
    int akna_db;    //aknak darabszama
    time_t t_kezd;  //megnyitas v. kezdes ideje
    int t;          //korabbi osszes jatekido
    int **rejtett;  //csak a szamitogep altal ismert
    int **latszik;  //ez a megjelenitett jatekter
} Jatek;

char jel(int id) {
    char jelolok[13] = { '.', '1', '2', '3', '4', '5', '6', '7', '8', '!', '#', 'X'};
    ///Cellak allapota:   0    1    2    3    4    5    6    7    8   akna !ism jel
    return jelolok[id];
}

void clear() {
    //console torlese
    system("@cls||clear");
}

int stoi(char *numstr) {
    //egy sztringből számot csinál
    int szam = 0;
    int exp = 0;
    for (int i = strlen(numstr)-1; i >= 0; i--) {
        if (numstr[i] < '0' || numstr[i] > '9') return -1;
        szam += (numstr[i] - '0') * pow(10, exp++);
    }
    return szam;
}

time_t most(){
    //jelenlegi ido (mp pontossaggal)
    time_t t;
    time(&t);
    return t;
}

int random(int max) {
    //random szam 0-tol (max-1)-ig
    static bool elso = true;
    if (elso) {
        elso = false;
        srand(time(NULL));
    }
    return rand() % max;
}

char *sor_be(int l) {
    //bemenet megszerzése
    char c;
    scanf("%c", &c);
    char *sor = NULL;

    if (c == '\n' && l > 0) {
        c = '\0';
        sor = (char *) malloc((l+1) * sizeof(char));
    }
    else { sor = sor_be(l + 1); }

    if (sor == NULL) return NULL;
    sor[l] = c;
    return sor;
}

void mso(char *mod, int *sor, int *oszlop, Jatek *s) {
    //betöltött játéknál ez felel egyetlen bemenet megszerzéséért
    char *be = sor_be(0);
    if (be == NULL)
        { *mod = '!'; *sor = -1; *oszlop = -1; return; }

    if (isalpha(be[0]))
        { *mod = be[0]; be = (char*) (be + 1);}
    else
        { *mod = 'f'; }

    if (*mod == 'm')
        { *sor = 1; *oszlop = 1; return; }

    int i = strlen(be) - 1;
    while (i > 0 && be[i] != ' ')
        i--;

    if (i <= 0)
        { *sor = -1; *oszlop = -1; return; }

    be[i] = '\0';
    *oszlop = stoi(be + i + 1);
    *sor = stoi(be);

    if ((*oszlop > s->X || *oszlop < 1) || (*sor > s->Y || *sor < 1))
        { *sor = -1; *oszlop = -1; return; }

    free(--be);
}
