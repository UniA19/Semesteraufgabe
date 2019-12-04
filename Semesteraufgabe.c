#include "printing.h"
#include "global.h"
#include "input.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


/*Methoden für den Spielablauf*/
void shoot();
int get_status();


/*---------------------------------------- Methoden ----------------------------------------*/
int main(void)
{
        height = 10;
        width = 10;
        print();
        set_start_values();
        do {
                shoot();
        } while (get_status());
        
        printf("\n----------------------------------------\n");
        printf("The game is over! Someone won!\n");
        printf("----------------------------------------\n\n");
        
        return 0;
}

void shoot()
{
        char field[2];
        printf("Choose a field to shoot at: ");
        get_field(field);
        
        switch (spieler2[field[0] - 'A'][field[1] - '0'].content) {
                case water:
                        printf("\n%s\n", "Oh no, you missed!");
                        spieler2[field[0] - 'A'][field[1] - '0'].content = hit_water;
                        print();
                        break;
                case hit_water:
                        printf("%s\n", "You have already tried to kill that water!");
                        shoot();
                        break;
                case ship:
                        printf("%s\n", "Yeah, you have hit a ship!");
                        spieler2[field[0] - 'A'][field[1] - '0'].content = hit_ship;
                        if (!get_status()) {
                                print();
                                return;
                        }
                        print();
                        shoot();
                        break;
                case hit_ship:
                        printf("%s\n", "You have already destroyed this Part of the ship!");
                        shoot();
                        break;
                case destroyed_ship:
                        printf("%s\n", "You have already destroyed this ship!");
                        shoot();
                        break;
                default:
                        printf("%s\n", "Oh, it seems that aliens have claimed this field. I think this is an ERROR"); /*Should never be reached!*/
        }
}

int get_status() /*Return 0 to end game*/
{
        int status = 0;
        int i;
        for (i = 0; i < width; ++i) {
                int j;
                for (j = 0; j < height; ++j) {
                        struct Field field = spieler1[i][j];
                        status += field.content == ship;
                        if (field.position == left) {
                                if (field.content == hit_ship) {
                                        int k;
                                        int ship_ok = 0; /*Anzahl an noch nicht getroffenen Teilen dieses Schiffes*/
                                        for (k = 0; k < field.length; ++k) {
                                                ship_ok += spieler1[i+k][j].content == ship;
                                        }
                                        if (!ship_ok) { /*Schiff versenkt*/
                                                for (k = 0; k < field.length; ++k) {
                                                        spieler1[i+k][j].content = destroyed_ship;
                                                }
                                                printf("You have destroyed a ship with length %i!", field.length);
                                        }
                                }
                        } else if (field.position == top) {
                                if (field.content == hit_ship) {
                                        int k;
                                        int ship_ok = 0; /*Anzahl an noch nicht getroffenen Teilen dieses Schiffes*/
                                        for (k = 0; k < field.length; ++k) {
                                                ship_ok += spieler1[i][j+k].content == ship;
                                        }
                                        if (!ship_ok) { /*Schiff versenkt*/
                                                for (k = 0; k < field.length; ++k) {
                                                        spieler1[i][j+k].content = destroyed_ship;
                                                }
                                                printf("You have destroyed a ship with length %i!", field.length);
                                        }
                                }
                        }
                }
        }
        return status;
}

/* 
Schiffe:
1x 5
2x 4
2x 3
2x 2
 */