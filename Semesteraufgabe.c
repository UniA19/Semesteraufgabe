#include <stdio.h>
#include <ctype.h>

/*Methode zum setzen der Startpositionen*/
void set_start_values();
void get_start();
void get_orientation();
void ship_not_fit();

/*Methoden für den graphischen Output*/
void print();
void line_1();
void line_2();

/*Globale Variablen*/
/*
00 -> Wasser "    "
01 -> getroffenes Wasser " () "
1x -> Schiff Nr. x "===="
2x -> getroffenes Schiff Nr. x " >< " 
3x -> versenktes Schiff Nr. x "(><)"
*/
int height = 10;
int width = 10;

int spieler1[width][height];
int spieler2[width][height];



int main(void)
{
        print();
        set_start_values();
        return 0;
}

void set_start_values()
{       
        int i;
        int j;
        for (i = 0; i < width; ++i) {
                for (j = 0; j < height; ++j) {
                        spieler1[i][j] = 0;
                        spieler2[i][j] = 0;
                }
        }
        get_start(5, 0);
        get_start(4, 1);
        get_start(4, 2);
        get_start(3, 3);
        get_start(3, 4);
        get_start(2, 5);
        get_start(2, 6);
        
}

void get_start(int length, int number)
{
        char input[2];
        int end = 0;
        int ic = 0;     /*z.B. 0A*/
        int ci = 0;     /*z.B. A0*/
        while (!end) {
                printf("Please enter the starting field of ship with length '%i': ", length);
                scanf("%s", input);
                input[0] = toupper(input[0]);
                input[1] = toupper(input[1]);
                ic = (input[0] - '0' >= 0 && input[0] - '0' <= height) && (input[1] - 'A' >= 0 && input[1] - 'A' <= width);
                ci = (input[0] - 'A' >= 0 && input[0] - 'A' <= width) && (input[1] - '0' >= 0 && input[1] - '0' <= height);
                end = ic || ci;
                if (ic) {
                        char temp = input[0];
                        input[0] = input[1];
                        input[1] = temp;
                }
                if (end) {
                        char orientation = get_orientation(length);
                        if (orientation == 'h') {
                                if (((input[0] - 'A') + length) <= width) {
                                        int i;
                                        for (i = 0; i < length; ++i) {
                                                spieler1[][] = ;
                                        }
                                } else {
                                        /*Das Schiff passt horizontal nicht in das Feld!*/
                                        ship_not_fit(length, number);
                                }
                        } else {
                                if (((input[1] - '0') + length) <= height) {
                                        
                                } else {
                                        /*Das Schiff passt vertikal nicht in das Feld!*/
                                        ship_not_fit(length, number);
                                }
                        }
                } else {
                        printf("'%s' is no legal input!\n", input);
                }
        }       
}

void ship_not_fit(int length, int number)
{
        printf("%s", "The ship doesn't fit like this");
        get_start(length, number);
}

char get_orientation(int length)
{
        char input[1];
        int end = 0;
        while (!end) {
                printf("Please enter the orientation of ship with length '%i'\n 'h' for horizontal or 'v' for vertical: ", length);
                scanf("%s", input);
                input[0] = toupper(input[0]);
                end = (input[0] == 'h') || (input[0] == 'v');
                if (end) {
                        return input[0];
                } else {
                        printf("'%s' is no legal input!\n", input);
                }
        }
}

void print()
{
        int i;
        for (i = 'A'; i <= 'A' + width; ++i) {
                printf("%s%c", "    ", i);
        }
        printf("%s\n", "  ");
        for (i = 0; i < height; ++i) {
                line_1();
                line_2(i);
        }
        line_1();
}

void line_1()
{
        int i;
        printf("%s", "  ");
        for (i = 'A'; i <= 'A' + width; ++i) {
                printf("%s", "+----");
        }
        printf("%c\n", '+');
}

void line_2(int row)
{
        int i;
        printf("%2i", row);
        for (i = 'A'; i <= 'A' + width; ++i) {
                printf("%s", "|    ");
        }
        printf("%c\n", '|');
}


/* 
Schiffe:
1x 5
2x 4
2x 3
2x 2
 */
