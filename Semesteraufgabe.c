#include <stdio.h>
#include <ctype.h>

/*Methode zum setzen der Startpositionen*/
void set_start_values();
void get_start();
char get_orientation();
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

int spieler1[10][10];
int spieler2[10][10];



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
        print();
        get_start(4, 1);
        print();
        get_start(4, 2);
        print();
        get_start(3, 3);
        print();
        get_start(3, 4);
        print();
        get_start(2, 5);
        print();
        get_start(2, 6);
        print();
}

void get_start(int length, int number)
{
        char input[2];
        int end = 0;
        int ic = 0;     /*z.B. 0A*/
        int ci = 0;     /*z.B. A0*/
        while (!end) {
                printf("Please enter the starting field of ship with length '%i': ", length);
                input[0] = getchar();
                if (input[0] != '\n') {
                        input[1] = getchar();
                } else {
                        input[1] = ' ';
                }
                
                if (input[0] != '\n' && input[1] != '\n') {
                        while ((getchar()) != '\n');
                }
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
                        if (orientation == 'H') {
                                if (((input[0] - 'A') + length) <= width) {
                                        int i;
                                        int not_fit = 0;
                                        for (i = 0; i < length; ++i) {
                                                not_fit += spieler1[input[0] - 'A' + i][input[1] - '0']; /*nicht alle Felder sind frei*/
                                        }
                                        if (not_fit) {
                                                ship_not_fit(length, number);
                                        } else {
                                                for (i = 0; i < length; ++i) {
                                                        spieler1[input[0] - 'A' + i][input[1] - '0'] = 10 + number;
                                                }
                                        }
                                } else {
                                        /*Das Schiff passt horizontal nicht in das Feld!*/
                                        ship_not_fit(length, number);
                                }
                        } else {
                                if (((input[1] - '0') + length) <= height) {
                                        int i;
                                        int not_fit = 0;
                                        for (i = 0; i < length; ++i) {
                                                not_fit += spieler1[input[0] - 'A'][input[1] - '0' + i]; /*nicht alle Felder sind frei*/
                                        }
                                        if (not_fit) {
                                                ship_not_fit(length, number);
                                        } else {
                                                for (i = 0; i < length; ++i) {
                                                        spieler1[input[0] - 'A'][input[1] - '0' + i] = 10 + number;
                                                }
                                        }
                                } else {
                                        /*Das Schiff passt vertikal nicht in das Feld!*/
                                        ship_not_fit(length, number);
                                }
                        }
                } else {
                        printf("'%c%c' is no legal input!\n\a", input[0], input[1]);
                }
        }       
}

void ship_not_fit(int length, int number)
{
        printf("%s", "The ship doesn't fit like this!\n\a");
        get_start(length, number);
}

char get_orientation(int length)
{
        char input[1];
        int end = 0;
        while (!end) {
                printf("Please enter the orientation of ship with length '%i'\n 'h' for horizontal or 'v' for vertical: ", length);
                input[0] = getchar();
                if (input[0] != '\n') {
                        while ((getchar()) != '\n');
                }
                input[0] = toupper(input[0]);
                end = (input[0] == 'H') || (input[0] == 'V');
                if (end) {
                        return input[0];
                } else {
                        printf("'%c' is no legal input!\n\a", input[0]);
                }
        }
        return 'h'; /*Will never be reached, but causes warning*/
}

void print()
{
        int i;
        for (i = 'A'; i < 'A' + width; ++i) {
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
        for (i = 'A'; i < 'A' + width; ++i) {
                printf("%s", "+----");
        }
        printf("%c\n", '+');
}

void line_2(int row)
{
        int i;
        printf("%2i", row);
        for (i = 0; i < width; ++i) {
                switch (spieler1[i][row]) {
                        case 00: printf("%s", "|    "); break;
                        case 01: printf("%s", "| () "); break;
                        case 10: printf("%s", "|===="); break;
                        case 11: printf("%s", "|===="); break;
                        case 12: printf("%s", "|===="); break;
                        case 13: printf("%s", "|===="); break;
                        case 14: printf("%s", "|===="); break;
                        case 15: printf("%s", "|===="); break;
                        case 16: printf("%s", "|===="); break;
                        case 17: printf("%s", "|===="); break;
                        case 18: printf("%s", "|===="); break;
                        case 19: printf("%s", "|===="); break;
                        case 20: printf("%s", "| >< "); break;
                        case 21: printf("%s", "| >< "); break;
                        case 22: printf("%s", "| >< "); break;
                        case 23: printf("%s", "| >< "); break;
                        case 24: printf("%s", "| >< "); break;
                        case 25: printf("%s", "| >< "); break;
                        case 26: printf("%s", "| >< "); break;
                        case 27: printf("%s", "| >< "); break;
                        case 28: printf("%s", "| >< "); break;
                        case 29: printf("%s", "| >< "); break;
                        case 30: printf("%s", "|(><)"); break;
                        case 31: printf("%s", "|(><)"); break;
                        case 32: printf("%s", "|(><)"); break;
                        case 33: printf("%s", "|(><)"); break;
                        case 34: printf("%s", "|(><)"); break;
                        case 35: printf("%s", "|(><)"); break;
                        case 36: printf("%s", "|(><)"); break;
                        case 37: printf("%s", "|(><)"); break;
                        case 38: printf("%s", "|(><)"); break;
                        case 39: printf("%s", "|(><)"); break;
                }
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
