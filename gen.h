
/**szines megjeleniteshez szukseges sztringek*/
    #define EGY      "\x1b[1;34m"
    #define KETTO    "\x1b[0;32m"
    #define HAROM    "\x1b[1;31m"
    #define NEGY     "\x1b[0;34m"
    #define OT       "\x1b[0;31m"
    #define HAT      "\x1b[0;36m"
    #define HET      "\x1b[0;35m"
    #define NYOLC    "\x1b[0;37m"
    #define AKNASZIN "\x1b[1;33m"
    #define RESET    "\x1b[0m"

typedef struct Jatek{
    //egy jatek parameterei:
    int X; int Y;   //lathato meret
    int akna_db;    //aknak darabszama
    time_t t_kezd;  //megnyitas v. kezdes ideje
    int t;          //korabbi osszes jatekido
    int **rejtett;  //csak a szamitogep altal ismert
    int **latszik;  //ez a megjelenitett jatekter
} Jatek;

char jel(int id);

time_t most();

int random(int max);

void clear();

int stoi(char *numstr);

char *sor_be(int l);

void mso(char *mod, int *sor, int *oszlop, Jatek *s);
