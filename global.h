#ifndef GLOBAL_H
#define GLOBAL_H

#define WIDTH_MIN 3
#define WIDTH_MAX 26
#define WIDTH_DEFAULT 10
#define HEIGHT_MIN 3
#define HEIGHT_MAX 99
#define HEIGHT_DEFAULT 10

/*structs*/
struct Field {
        short content;
        short length; /*0 if no ship*/
        short number; /*0 if no ship*/
        short position; /*enum left, horizontal, ... (0 if no ship)*/
};

/*enums*/
enum { water, hit_water, ship, hit_ship, destroyed_ship };
enum { none, left, horizontal, right, top, vertical, bottom };

/*Globale Variablen*/
int height;
int width;

struct Field **spieler1;
struct Field **spieler2;

int difficulty;

#endif