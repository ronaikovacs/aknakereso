#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "menu_fv.h"
#include "jatek_fv.h"

#ifdef _WIN32
    #include <windows.h>
#endif

int main()
{
    #ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif

    /**minden menu egy char-ral tér vissza,
      *ez alapján a switch eldönti, melyik
      *a legközelebbi megnyitandó menü*/
    char be = 'v'; //'?' <=> fomenu() kell
    while (be != 'x') {
        switch (be) {
            case 'u': { jatekmenet();  be = 'v'; break; }
            default:  { be = fomenu(); break; }
        }
    }
    //jatekmenet();

    return 0;
}
//switch(c) a menu()-ben /.../
//menu.txt, segitseg.txt, ranglista.txt hasznalata
//ranglista fájl
//mentés(ek) hozzáadása
//mentés(ek) betöltése

