
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "printing.h"
#include "global.h"
#include "input.h"
#include "bot.h"


/*Methoden für den Spielablauf*/
int shoot(void);
int shoot_ki(void);
int get_status(void);
int get_status1(void);
int get_status2(void);
void free_all(void);

/*---------------------------------------- Methoden ----------------------------------------*/
int main(void)
{
        int i;

        width = WIDTH_DEFAULT;
        height = HEIGHT_DEFAULT;
        if (get_size()) {
                return -1;
        }

        spieler1 = (struct Field **)malloc(width * sizeof(struct Field *));
        spieler2 = (struct Field **)malloc(width * sizeof(struct Field *));
        if (spieler1 == NULL) {
                printf("FATAL ERROR: could not allocate memory");
                free_all();
                return -1;
        }
        if (spieler2 == NULL) {
                printf("FATAL ERROR: could not allocate memory");
                free(spieler1);
                return -1;
        }
        for (i = 0; i < width; ++i) {
                spieler1[i] = (struct Field *) malloc(height * sizeof(struct Field));
                spieler2[i] = (struct Field *) malloc(height * sizeof(struct Field));
                if (spieler1[i] == NULL || spieler2[i] == NULL) {
                        printf("FATAL ERROR: could not allocate memory");
                        free_all();
                        return -1;
                }
        }

        set_start_values();
        SetStartBot();

        while (!shoot())
        {
            shoot_ki();
        };

        printf("\n----------------------------------------\n");
        printf("The game is over! Someone won!\n");
        printf("----------------------------------------\n\n");

        free_all();
        return 0;
}

void free_all()
{
        int i;
        for (i = 0; i < width; ++i) {
                if (spieler1[i] != NULL) {
                        free(spieler1[i]);
                }
                if (spieler2[i] != NULL) {
                        free(spieler2[i]);
                }
        }
        free(spieler1);
        free(spieler2);
}

int shoot()
{
        int row;
        char column;
        printf("Choose a field to shoot at: ");
        if (get_field(&row, &column)) {
                return -1;
        }

        switch (spieler2[column - 'A'][row].content) {
                case water:
                        printf("\n%s\n", "Oh no, you missed!");
                        spieler2[column - 'A'][row].content = hit_water;
                        print();
                        return 0;
                        break;
                case hit_water:
                        printf("%s\n", "You have already tried to kill that water!");
                        shoot();
                        return 0;
                        break;
                case ship:
                        printf("%s\n", "Yeah, you have hit a ship!");
                        spieler2[column - 'A'][row].content = hit_ship;
                        if (!get_status()) {
                                print();
                                return 1;
                        }
                        print();
                        shoot();
                        return 0;
                        break;
                case hit_ship:
                        printf("%s\n", "You have already destroyed this Part of the ship!");
                        shoot();
                        return 0;
                        break;
                case destroyed_ship:
                        printf("%s\n", "You have already destroyed this ship!");
                        shoot();
                        return 0;
                        break;
                default:
                        printf("%s\n", "Oh, it seems that aliens have claimed this field. I think this is an ERROR\n"); /*Should never be reached!*/
                        printf("content: %i, column: (%c|%i), row: %i", spieler2[column - 'A'][row].content, column, column, row);
                        return -2;
        }
}

int shoot_ki()
{
    int row;
    char column;
    int hit = 0;
    int done;

    do {
        done = 1;
        if(hit && difficulty==2)
        {
            GetField_onHit(&row, &column);
            hit = 0;
        } else {
                GetFieldBot(&row, &column);
        }


        switch (spieler1[column - 'A'][row].content) {
                case water:
                        printf("\n%s\n", "Oh no, Bot missed!");
                        spieler1[column - 'A'][row].content = hit_water;
                        break;
                case hit_water:
                        printf("%s\n", "Bot has already tried to kill that water!");
                        done = 0;
                        break;
                case ship:
                        printf("%s\n", "Yeah, bot has hit a ship!");
                        spieler1[column - 'A'][row].content = hit_ship;
                        if (!get_status()) {
                                print();
                                return 1;
                        }
                        hit = 1;
                        break;
                case hit_ship:
                        printf("%s\n", "Bot has already destroyed this Part of the ship!");
                        done = 0;
                        break;
                case destroyed_ship:
                        printf("%s\n", "Bot has already destroyed this ship!");
                        done = 0;
                        break;
                default:
                        printf("%s\n", "Oh, it seems that aliens have claimed this field. I think this is an ERROR\n"); /*Should never be reached!*/
                        printf("content: %i, column: (%c|%i), row: %i", spieler1
                               [column - 'A'][row].content, column, column, row);
                        return -2;
        }
}while( hit==1 | done == 0);
        print();
        return 0;
}

int get_status()
{
        return get_status1() * get_status2();
}

int get_status1() /*Return 0 to end game*/
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

int get_status2() /*Return 0 to end game*/
{
        int status = 0;
        int i;
        for (i = 0; i < width; ++i) {
                int j;
                for (j = 0; j < height; ++j) {
                        struct Field field = spieler2[i][j];
                        status += field.content == ship;
                        if (field.position == left) {
                                if (field.content == hit_ship) {
                                        int k;
                                        int ship_ok = 0; /*Anzahl an noch nicht getroffenen Teilen dieses Schiffes*/
                                        for (k = 0; k < field.length; ++k) {
                                                ship_ok += spieler2[i+k][j].content == ship;
                                        }
                                        if (!ship_ok) { /*Schiff versenkt*/
                                                for (k = 0; k < field.length; ++k) {
                                                        spieler2[i+k][j].content = destroyed_ship;
                                                }
                                                printf("One of your ships with length %i was destroyed!", field.length);
                                        }
                                }
                        } else if (field.position == top) {
                                if (field.content == hit_ship) {
                                        int k;
                                        int ship_ok = 0; /*Anzahl an noch nicht getroffenen Teilen dieses Schiffes*/
                                        for (k = 0; k < field.length; ++k) {
                                                ship_ok += spieler2[i][j+k].content == ship;
                                        }
                                        if (!ship_ok) { /*Schiff versenkt*/
                                                for (k = 0; k < field.length; ++k) {
                                                        spieler2[i][j+k].content = destroyed_ship;
                                                }
                                                printf("One of your ships with length %i was destroyed!", field.length);
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
