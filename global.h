#ifndef GLOBAL_H
#define GLOBAL_H

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

struct Field spieler1[10][10];
struct Field spieler2[10][10];

#endif