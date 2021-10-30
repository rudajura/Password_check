/**
 * Projekt 1 - Práce s textem
 * Rudolf Jurišica (xjuris02)
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN_FGETS 102           //konstanta s maximalni delkou hesla - heslo muze byt maximalne 100 znaku,
                                    //ale ve fgets se do retezce nacte na konci \0 a \n , proto musim pricist k delce +2

#define MAX_LEN_PSWR 101            //tato konstanta slouzi pro porovnavani delky hesla, do ktere se jiz nepocita \n

#define MAX_ASCII 94                //zde si vytvorim konstantu MAX_ASCII s hodnotou 94 (ASCII tabulka ma 128 znaku, ale ja
                                    //v tomto programu budu vyuzivat pouze znaky 32-126, coz dohromady dava 94 znaku)

#define ASCII_FIRST_CHARS 32        //vytvorim si konstantu, pomoci ktere budu v programu odecitat (pricitat) prvnich 32 znaku, ktere
                                    //nebudu vyuzivat

#define STATS_LEN_1 7               //konstanta pro kontrolu delky tretiho (spolu s nazvem programu ctvrteho) vstupniho argumentu

#define STATS_LEN_2 8               //konstanta pro ulozeni delky --stats (k delce, ktera je 7, se pricte 1, protoze na konci retezce je \0)

#define ARGC_MIN 3                  //definuje minimalni pocet vstupnich argumentu (nazev programu + LEVEL + PARAM (--stats je volitelne))

#define ARGC_MAX 4                  //ulozi maximalni pocet vstupnich argumentu (nazev programu + LEVEL + PARAM + --stats)

//tvorba funkci, ktere se po zavolani budto splni a vrati true, nebo nesplni a vrati false:

bool smalls_and_capitals (char arr[]) {    //funkce na overeni, jestli pole (heslo) obsahuje mala a velka pismena zaroven
    int j = 0;                             //zde si vytvorime promenne, ktere budou k dispozici pouze uvnitr teto funkce
    int sl = 0;
    int cl = 0;
    for(j = 0; arr[j] != '\0'; j++) {
        if(arr[j] >= 'a' && arr[j] <= 'z') {            //porovnavani pismen vychazi z pozic v ASCII tabulce, kde jsou postupne serazena
            sl++;                                       //od a do z a od A do Z - tim padem staci napsat, zda se hodnota arr[j] rovna
                                                        //necemu v intervalu v if
        } else if(arr[j] >= 'A' && arr[j] <= 'Z') {
            cl++;
        }
    }
    if(cl > 0 && sl > 0) {
        return true;
    } else {
        return false;
    }
}

bool small_let (char arr[]) {               //funkce na overeni, jestli pole (heslo) obsahuje mala pismena
    int p = 0;                              //tato funkce ma stejny princip, jako predchozi, avsak zde se pouze kontroluje,
    int sl = 0;                             //zda znak v zadanem poli (arr[]) je roven necemu v intervalu v if
    for(p = 0; arr[p] != '\0'; p++) {       //for cyklus opet skonci, jakmile se objevi posledni polozka v poli - \0
        if(arr[p] >= 'a' && arr[p] <= 'z') {
            sl++;
        }
    }
    if(sl > 0) {
        return true;
    } else {
        return false;
    }
}

bool capital_let (char arr[]) {               //funkce na overeni, jestli pole (heslo) obsahuje velka pismena
    int k = 0;                                //stejny princip, jako predchozi
    int cl = 0;
    for(k = 0; arr[k] != '\0'; k++) {
        if(arr[k] >= 'A' && arr[k] <= 'Z') {
            cl++;
        }
    }
    if(cl > 0) {
        return true;
    } else {
        return false;
    }
}

bool number (char arr[]) {                     //funkce na overeni, jestli pole (heslo) obsahuje cisla
    int l = 0;                                 //stejny princip, jako predchozi funkce
    int nm = 0;
    for(l = 0; arr[l] != '\0'; l++) {
        if(arr[l] >= '0' && arr[l] <= '9') {
            nm++;
        }
    }
    if(nm > 0) {
        return true;
    } else {
        return false;
    }
}

bool symbol (char arr[]) {                      //funkce na overeni, jestli pole (heslo) obsahuje specialni znaky
    int m = 0;
    int sb = 0;
    for(m = 0; arr[m] != '\0'; m++) {                   //zde uz nelze napsat if(arr[m] >= ' ' && arr[m] <= '~'),
        if((arr[m] >= ' ' && arr[m] <= '/')             //protoze opet vychazime z ASCII tabulky a overujeme pouze,
            || (arr[m] >= ':' && arr[m] <= '@')         //zda pole obsahuje polozky, ktere jsou specialni znaky,
            || (arr[m] >= '[' && arr[m] <= '`')         //a ty znaky, ktere overujeme, nejsou vsechny ulozeny po sobe
            || (arr[m] >= '{' && arr[m] <= '~')) {      //v ASCII, proto je zde nejdrive napsano (arr[m] >= ' ' && arr[m] <= '/')
            sb++;                                       //coz se da prelozit jako arr[m] >= polozce 32 a zaroven arr[m] <= polozce 47
        }                                               //z ASCII - v tabulce dale nasleduje posloupnost cislic a az na pozici 58
    }                                                   //zacinaji dalsi specialni znaky
    if(sb > 0) {
        return true;
    } else {
        return false;
    }
}


//__________________________________zacatek main a kontrola argumentu vlozenych pri spusteni programu______________________________________________//

int main(int argc, char* argv[])
{
    if(argc > ARGC_MAX || argc < ARGC_MIN) {      //zde se kontroluje, jestli vstupni argumenty jsou alespon 3 (nazev programu, LEVEL a PARAM)
        fprintf(stderr, "Spatne zadane vstupni parametry.");     //pokud vstupni argumenty LEVEL a PARAM nebudou pouze 2 (--stats je volitelny)
        return 1;                                                //nebo nebudou vubec zadany, program se ukonci s chybovym hlasenim
    }

    //kontrola, zda treti zadany argument je --stats
    //pokud ano, z se na konci bude rovnat 8 (zapocitan je znak \0) a po zavolani EOF se vypisou statistiky
    int z = 0;
    if(argc == ARGC_MAX) {
        int a = 0;
        char stats[] = "--stats";               //vytvorime si pole, do ktereho ulozime retezec "--stats", a s timto polem budeme nasledne
        for(a = 0; argv[3][a] != '\0'; a++);    //porovnavat treti uzivatelem zadany argument, zda je v nem obsazeno "--stats"
                                                //pokud by bylo povoleno pouzivani knihovny string.h, dalo by se zavolat jiz
        int b = 0;                              //predem vytvorenou funkci 'strcmp', ktere se pouze vlozi argumenty a ona je porovna
        if(a == STATS_LEN_1) {
            for(b = 0; b <= a; b++) {
                if(stats[b] == argv[3][b]) {
                    z = z + 1;
                } else {
                    fprintf(stderr, "Spatne zadane vstupni argumenty.");        //pokud argv[3] neobsahuje "--stats", program se ukonci s chybovym hlasenim"
                    return 1;
                }
            }
        } else {
        fprintf(stderr, "Spatne zadane vstupni argumenty.");        //pokud bylo zjisteno, ze retezec v argv[3] je delsi nebo kratsi jak 7 znaku,
        return 1;                                                   //program se ukonci s chybovym hlasenim
        }
    }

    long LEVEL = strtol(argv[1], NULL, 10);     //argv[1] (LEVEL) se pretypuje na long int, 10 znaci desitkovou soustavu
    long PARAM = strtol(argv[2], NULL, 10);     //argv[2] (PARAM) se pretypuje na long int, 10 znaci desitkovou soustavu


    //zde se kontroluje, jestli je cislo uvedene do LEVELu platne (v pripade chybne hodnoty se program ukonci s chybovym hlasenim)
    if(LEVEL > 4 || LEVEL < 1) {
        fprintf(stderr, "LEVEL muze byt pouze kladne cele cislo v rozmezi 1 - 4.");
        return 1;
    }
    //zde se kontroluje, jestli je cislo uvedene do PARAM platne (v pripade chybne hodnoty se program ukonci s chybovym hlasenim)
    if(PARAM < 1) {
        fprintf(stderr, "PARAM muze byt pouze kladne cele cislo vetsi jak 0.");
        return 1;
    }

 //____________________________samotna kontrola hesla___________________________//

    char pswr[MAX_LEN_FGETS];     //vytvoreni pole pro ulozeni hesla o predem nadefinovane delce

    while(!feof(stdin)) {       //while cyklus, ktery bude bezet do te doby, dokud uzivatel do terminalu nezada EOF, vse se odehrava uvnitr tohoto cyklu

        float length = 0;       //zde si vytvorim promenne, ktere budu pozdeji vyuzivat
        int min = 0;
        int hash[MAX_ASCII];    //vytvoreni pole o velikosti MAX_ASCII (94), do ktereho se postupne nactou hodnoty z ASCII tabulky (32 - 126)
        int g = 0;
        int i = 0;
        int v = 0;
        int c;
        int o;
        int q;
        int u;
        int w;

        for(o = 0; o < MAX_ASCII; o++) {        //for cyklus pro nacteni hodnot ASCII z pozic 32 - 126 a ulozeni do 94 pozic v hash[] poli
            hash[o] = o + ASCII_FIRST_CHARS;
        }
        while(fgets(pswr, MAX_LEN_FGETS, stdin) != NULL){     //nacitani hesel od uzivatele pomoci funkce fgets do pole pswr[MAX_LEN], max. pocet znaku 102 a vstup stdin

            //heslo se nacte a nasledne se musi zkontrolovat jeho delka, jestli neni moc dlouhe
            //nejdrive se jeho delka nainkrementuje do promenne i
            for(i = 0; pswr[i] != '\0'; i++);

            //a tady se jeho delka porovna, jestli je pocet znaku mensi jak 101 (100 je maximalni delka hesla), pokracuje se dal
            //pokud je pocet vetsi, heslo se zahodi a uzivatel musi zadat jine heslo
            if(i < MAX_LEN_PSWR) {
                g = g + 1;      //pokud heslo splnuje podminku, g se zvysi o 1 - g ukazuje pocet hesel, ktera jsou mensi jak 101
                length = length + i - 1;     //length slouzi k zapsani prumerne delky hesel
                if(g == 1) {                 //pri prvnim heslu se do min zapise delka prvniho hesla
                    min = i - 1;             //odecita se 1, protoze pole s heslem ma pocet zadanych znaku uzivatelem, ale posledni cast pole obsazuje
                }                            //znak konce pole /0

                if(g > 1) {                  //pri dalsich heslech se budto min prepise delkou kratsiho hesla, nebo ne
                    if(min > i) {
                        min = i - 1;
                    }
                }
            } else {                                            //pokud je heslo moc dlouhe, program se ukonci s chybovym hlasenim
                fprintf(stderr, "Heslo je moc dlouhe.");
                return 1;
            }

            for(w = 0; pswr[w] != '\0'; w++) {              //tyto cykly slouzi pro porovnani znaku hesla s hodnotami v hash poli, coz nasledne bude
                for(q = 0; hash[q] != '\0'; q++) {          //slouzit ve statistikach pro vytisteni poctu ruznych znaku
                    if(pswr[w] == hash[q]) {                //pokud se hodnoty v polich rovnaji, dana pozice 'q' v hash poli se prepise na 1
                        hash[q] = 1;                        //(z duvodu, aby se pri kontrole dalsiho hesla nepocital nejaky znak znovu)
                        break;                              //vsechny jednicky se nakonec sectou a dohromady daji pocet ruznych znaku
                    }
                }
            }

//_____________zde zacina overovani, zda hesla splnuji podminky pro zadane argumenty LEVEL a PARAM_____________//

            //overeni, jestli pro LEVEL 1 heslo splnuje podminku (pouzila se funkce smalls_and_capitals)
            if(LEVEL == 1 || LEVEL == 2 || LEVEL == 3 || LEVEL == 4) {
                if(smalls_and_capitals(pswr)) {
                    if(LEVEL == 1) {
                    printf("%s", pswr);     //pokud se podminka splni, heslo se vytiskne (pouze, pokud je zadan LEVEL = 1)
                    }
                }
            }

            //nyni pro LEVEL 2 (pouzily se funkce smalls_and_capitals, number a symbol)
            //diky funkci smalls_and_capitals je v LEVEL 2 zahrnut i LEVEL 1
            if(LEVEL == 2 || LEVEL == 3 || LEVEL == 4) {
                if(PARAM == 1 || PARAM == 2) {
                    if((smalls_and_capitals(pswr))
                    || (smalls_and_capitals(pswr) && number(pswr))
                    || (smalls_and_capitals(pswr) && symbol(pswr))
                    || (smalls_and_capitals(pswr) && number(pswr) && symbol(pswr))) {
                        if(LEVEL == 2) {
                            printf("%s", pswr);
                        }
                    } else {
                        continue;
                    }
                } else if(PARAM == 3) {
                    if((smalls_and_capitals(pswr) && number(pswr))
                    || (smalls_and_capitals(pswr) && symbol(pswr))
                    || (smalls_and_capitals(pswr) && number(pswr) && symbol(pswr))) {
                        if(LEVEL == 2) {
                            printf("%s", pswr);
                        }
                    } else {
                        continue;
                    }
                } else if(PARAM >= 4) {
                    if(smalls_and_capitals(pswr) && number(pswr) && symbol(pswr)) {
                        if(LEVEL == 2) {
                            printf("%s", pswr);                         //pokud se vyse uvedene podminky splni a pokud je LEVEL = 2, heslo se vytiskne
                        }                                               //pokud se podminky splni a LEVEL je 3 nebo 4, overovani pokracuje do dalsich
                    } else {                                            //overovacich podminek (viz nize)
                        continue;                                       //pokud heslo podminky nesplnilo, nevytiskne se a vracime se zpet do funkce fgets
                    }                                                   //a uzivatel muze zadat jine heslo
                }
            }

            //nyni pro LEVEL 3
            if(LEVEL == 3 || LEVEL == 4) {          //LEVEL 3 funguje tak, ze pokud je hodnota PARAM rovna 1, tak se pokracuje zpet k nacitani dalsiho hesla,
                if(PARAM == 1) {                    //protoze by to znamenalo, ze delka sekvence stejnych znaku delky 1 je vzdy, coz znamena jakykoliv znak
                    continue;
                }
                int count = 1;                      //v tomto kroku se do promenne count (ukazuje pocet stejnych znaku v sekvenci,
                                                    // v pripade rovnosti se inkrementuje) nacte 1
                for(int r = 0; pswr[r] != '\0'; r++) {      //tady zacinaji vnorene for cykly, postupne se overuji adresy znaku hesla v poli a tyto adresy
                    for(int s = r + 1; pswr[s] != '\0'; s++) {    //se po vyhotoveni vsech podminek uvnitr cyklu nasledne inkrementuji
                        if(pswr[r] == pswr[s]) {                   //pokud se napr. adresa 0 rovna adrese 1, znamena to, ze znaky na techto 2 pozicich
                            count++;                               //jsou shodne a count je inkrementuje (zvysi svoji hodnotu) o 1
                            break;
                        } else {
                            count = 1;              //pokud nejsou shodne, count se opet nastavi na hodnotu 1, aby nacitani shodnosti znaku mohlo zacit znovu
                            break;                  //u jine sekvence
                        }
                    } if(count == PARAM) {      //pokud je count roven hodnote PARAM, cely cyklus i podminka if(LEVEL == 3 || LEVEL == 4) se ukonci,
                        break;                  //heslo se nevypise a uzivatel muze zadat jine heslo
                    }
                } if(count < PARAM && LEVEL == 3) {           //pokud skonci 1. for cyklus a skoci se sem a count je mensi jak PARAM, znamena to, ze nebyla
                        printf("%s", pswr);                   //nalezena sekvence stejnych znaku delky PARAM a heslo se muze vypsat do terminalu
                } else if(count < PARAM & LEVEL == 4) {
                } else {
                    continue;
                }
            }

            //nyni pro LEVEL 4
            if(LEVEL == 4) {
                int count = 0;                      //vytvori se promenna count, ktera se bude v pripade shody znaku 2 retezcu inkrementovat
                for(int r = 0; pswr[r] != '\0'; r++) {      //cyklus pobezi tak dlouho, dokud nedojde na konec hesla
                    for(int s = r + PARAM; pswr[s] != '\0'; s++) {   //zde cyklus zacne o PARAM velikost vetsi, nez predchozi cyklus
                        if(pswr[r] == pswr[s]) {                  //pokud se znaky rovnaji, count se navysi o jedna a r taky
                            count++;                              //(aby se mohlo porovnavat stejne retezce - avsak na prvni for cyklus to vliv nema)
                            r++;
                            if(count == PARAM) {            //a pokud se count rovna hodnote PARAM, cela podminka se ukonci a heslo se nevypise
                                break;
                            }
                            continue;
                        } else {
                            count = 0;      //pokud se ale znaky nerovnaji, za count se dosadi opet nula a porovnavani muze zacit odznova
                            continue;
                        }
                    } if(count == PARAM) {      //druha podminka, pokud count = PARAM, aby se vyskocilo z posledniho cyklu a postoupilo k nacitani
                        break;                  //noveho hesla do fgets
                    }
                } if(count < PARAM) {           //avsak pokud for cykly se ukoncily a count je mensi nez PARAM (heslo nemelo dostatecne dlouhe
                    printf("%s", pswr);         //2 stejne podretezce), cela podminka pro LEVEL 4 se ukonci a muze se nacist dalsi heslo
                }
            }

        }                                       //nasledujici ukoly se zacnou vyhodnocovat po zavolani EOF uzivatelem
        for(c = 0; hash[c] != '\0'; c++) {      //zde se dopocita, kolik ruznych znaku bylo ve vsech heslech dohromady
            if(hash[c] == 1) {                  //tim, ze se spocita pocet jednicek v hash[] poli a jejich pocet se ulozi do promenne v
                v++;
            }
        }
        length = length/g;      //zde se vypocita prumerna delka vsech hesel vydelenim celkove delky poctem zadanych hesel
        if(z == STATS_LEN_2) {  //posledni podminka, ktera se splni, pokud byl zadan argument --stats, ktery byl overen vyse
            printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", v, min, length);  //vytisteni statistiky
        }
    }
    return 0;
}