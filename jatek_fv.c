#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "gen.h"

enum { AKNA = 9, ISMERETLEN = 10, JELOLT = 11 };
enum { TOVABB = 0, VESZTETT = 1, NYERT = 2};

int **gen_jatekter(Jatek *s, int ertek) {
    //elkszit egy, az s-nek megfelelo meretezesu jatekteret
    //es feltolti a megadott ertekkel
    int **terep = (int **) malloc((s->Y + 2) * sizeof(int *));
    for (int y = 0; y <= s->Y + 1; y++) {
        terep[y] = (int *) malloc((s->X + 2) * sizeof(int));
        for (int x = 0; x <= s->X + 1; x++)
            terep[y][x] = ertek;
    }
    return terep;
}

Jatek start() {
    //uj jatek inditasahoz szukseges adatok begyujtese
    clear();
    Jatek s;
    printf("Aknakeresõ\n\n");
    printf("Játéktér szélessége: "); scanf("%d", &s.X);
    printf("Játéktér magassága:  "); scanf("%d", &s.Y);
    printf("Aknák száma:         "); scanf("%d", &s.akna_db);
    s.rejtett = gen_jatekter(&s, 0);
    s.latszik = gen_jatekter(&s, ISMERETLEN);
    s.t = 0;
    clear();
    return s;
}

void aknaz(Jatek *s) {
    //az s->rejtett -ben szor szet s->akna_db darab aknat
    int rx, ry;
    for (int db = 0; db < s->akna_db; db++) {
        do {
            rx = random(s->X) + 1;
            ry = random(s->Y) + 1;
        } while (s->rejtett[ry][rx] == AKNA);

        s->rejtett[ry][rx] = AKNA;
    }
}

int szomszed_akna(Jatek *s, int x, int y) {
    //visszatereti, hany akna van (s->rejtett -ben) az (x;y) kornyezeteben
    if (s->rejtett[y][x] == AKNA) return AKNA;

    int db = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (s->rejtett[y + i][x + j] == AKNA) db++;
    return db;
}

void szamol(Jatek *s) {
    //feltolti a rejtett nem-akna mezoit a megfelelo szamertekekkel
    for (int y = 1; y <= s->Y; y++)
        for (int x = 1; x <= s->X; x++)
            s->rejtett[y][x] = szomszed_akna(s, x, y);
}

void kirajzol(Jatek *s) {
    //kirajzolja a (felhasznalo altal lathato) jatekteret
    clear();
    //keret fejlece:
    printf("s\\o");
    for (int x = 0; x < s->X; x++) printf("|%2d", x+1);
    printf("\n   +");
    for (int x = 0; x < s->X; x++) printf("---");
    printf("+\n");
    for (int y = 1; y <= s->Y; y++) {
        //keret bal oldala:
        printf("%3d|", y);

        for (int x = 1; x <= s->X; x++) {
            //a mezok szines kiirasa miatt kell a switch:
            switch (s->latszik[y][x]) {
                case 1: { printf(EGY      " %c "RESET, jel(s->latszik[y][x])); break; }
                case 2: { printf(KETTO    " %c "RESET, jel(s->latszik[y][x])); break; }
                case 3: { printf(HAROM    " %c "RESET, jel(s->latszik[y][x])); break; }
                case 4: { printf(NEGY     " %c "RESET, jel(s->latszik[y][x])); break; }
                case 5: { printf(OT       " %c "RESET, jel(s->latszik[y][x])); break; }
                case 6: { printf(HAT      " %c "RESET, jel(s->latszik[y][x])); break; }
                case 7: { printf(HET      " %c "RESET, jel(s->latszik[y][x])); break; }
                case 8: { printf(NYOLC    " %c "RESET, jel(s->latszik[y][x])); break; }
                case AKNA:
                        { printf(AKNASZIN " %c "RESET, jel(s->latszik[y][x])); break; }
                default:
                        { printf(" %c ", jel(s->latszik[y][x])); }
            }
        }
        printf("|%3d\n", y);
    }
    printf("   +");
    for (int x = 0; x < s->X; x++) printf("---");
    printf("+\no/s");
    for (int x = 0; x < s->X; x++) printf("|%2d", x+1);
    printf("\n\n");
    printf("Menü: m\n\n");
}

void ellenorzes(Jatek *s, int *allap) {
    //eldonti, hogyan folytatodik a jatek (nyer/veszit/tovabb)
    *allap = NYERT;
    for (int y = 1; y <= s->Y; y++) {
        for (int x = 1; x <= s->X; x++) {
            //ha latszik akna:
            if (s->latszik[y][x] == AKNA) { *allap = VESZTETT; return; }
            //ha nem csak az aknak fedettek:
            if ((s->latszik[y][x] == ISMERETLEN ||
                 s->latszik[y][x] == JELOLT) &&
                 s->rejtett[y][x] != AKNA)
               { *allap = TOVABB; }
        }
    }
}

void felderit(Jatek *s, int x, int y) {
    //feltár egy mezőt
    //ha 0 volt, akkor automatikusan a szomszédokat is
    if (s->latszik[y][x] == ISMERETLEN)
        s->latszik[y][x] = s->rejtett[y][x];
    if (x > 0 && x <= s->X &&
        y > 0 && y <= s->Y &&
        s->latszik[y][x] == 0) {

        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)

                if (i == 0 && j == 0)
                    continue;
                else if (s->latszik[y+j][x+i] == ISMERETLEN) {
                    felderit(s, x+i, y+j);
                }
    }
}

void gameover(Jatek *s, int allap) {
    //játékmenet végét intézi
    for (int y = 1; y <= s->Y; y++) {
        for (int x = 1; x <= s->X; x++) {
            s->latszik[y][x] = s->rejtett[y][x];
        }
    }
    kirajzol(s);
    if (allap == VESZTETT)
        { printf("\n-----VESZTETT-----\n"); }
        else
        { printf("\n*-*--*-*-NYERT-*-*--*-*\n"); }
    time_t t_vege = most();
    s->t += t_vege - s->t_kezd;
    printf(RESET"\n\nJáték hossza: %d", s->t);
    char nemkell;
    scanf("%c", &nemkell);
}

void javitando(char *mod, int *sor, int *oszlop, Jatek *s) {
    //egy biztosan értelmes sort szerez meg
    while (*mod == '!' || *oszlop == -1) {
        printf("Nem értelmezhető; kérlek, próbáld újra!\n");
        mso(mod, sor, oszlop, s);
    }
    return;
}

void felszabadit(Jatek *s) {
    //felszabaditja a malloc-ok altal foglalt teruleteket
    for (int i = 0; i < s->Y; i++) {
        free(s->rejtett[i]);
        free(s->latszik[i]);
    }
    free(s->rejtett);
    free(s->latszik);
}

void jatekmenet() {

    Jatek s = start();
    aknaz(&s);
    szamol(&s);
    //ez csak teljesen új játékot tud indítani

    int allapot = TOVABB;
    s.t_kezd = most();
    kirajzol(&s);
    s.t_kezd = most();
    int x, y;
    char mod = '\0';
    scanf("%c", &mod);

    while (allapot == TOVABB) {
        mso(&mod, &y, &x, &s);
        javitando(&mod, &y, &x, &s);
        switch (mod) {
            case 'm': {
                    jatekmenu(&s);
                    /// /!!!!!!44!4!44!! játék állását eltárolni, vissza a main()be, jatekmenut OTT megnyitni!!!
                    break;
                }
            case 'j': {
                    if (s.latszik[y][x] == JELOLT)
                        s.latszik[y][x] = ISMERETLEN;
                    else if (s.latszik[y][x] == ISMERETLEN)
                        s.latszik[y][x] = JELOLT;
                    break;
                }
            case 'f':
            default: {
                    felderit(&s, x, y);
                    break;
            }
        }
        ellenorzes(&s, &allapot);
        kirajzol(&s);
    }
    gameover(&s, allapot);

    felszabadit(&s);
}
