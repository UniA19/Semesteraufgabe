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

/*enums*/
enum { none, left, horizontal, right, top, vertical, bottom };
enum { water, hit_water, ship, hit_ship, destroyed_ship};

/*structs*/
struct field {
        short content;
        short length; /*0 if no ship*/
        short number; /*0 if no ship*/
        short position; /*enum left, horizontal, ... (0 if no ship)*/
};

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

struct field spieler1[10][10];
struct field spieler2[10][10];




/*---------------------------------------- Methoden ----------------------------------------*/
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
                        spieler1[i][j].content = water;
                        spieler1[i][j].length = 0;
                        spieler1[i][j].number = 0;
                        spieler1[i][j].position = none;
                        
                        spieler1[i][j].content = water;
                        spieler1[i][j].length = 0;
                        spieler1[i][j].number = 0;
                        spieler1[i][j].position = none;
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
                
                /*Fehlerbehandlung bei zu kurzem Input*/
                if (input[0] != '\n') {
                        input[1] = getchar();
                } else {
                        input[1] = ' ';
                }
                
                /*Überschüssigen input löschen*/
                if (input[0] != '\n' && input[1] != '\n') {
                        while ((getchar()) != '\n');
                }
                
                input[0] = toupper(input[0]);
                input[1] = toupper(input[1]);
                
                /*Input validieren*/
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
                                                not_fit += spieler1[input[0] - 'A' + i][input[1] - '0'].content; /*nicht alle Felder sind frei*/
                                        }
                                        if (not_fit) {
                                                ship_not_fit(length, number);
                                        } else { /*Legaler input*/
                                                for (i = 0; i < length; ++i) {
                                                        spieler1[input[0] - 'A' + i][input[1] - '0'].content = ship;
                                                        spieler1[input[0] - 'A' + i][input[1] - '0'].length = length;
                                                        spieler1[input[0] - 'A' + i][input[1] - '0'].number = number;
                                                        if (i == 0) {
                                                                spieler1[input[0] - 'A' + i][input[1] - '0'].position = left;
                                                        } else if (i == length - 1) {
                                                                spieler1[input[0] - 'A' + i][input[1] - '0'].position = right;
                                                        } else {
                                                                spieler1[input[0] - 'A' + i][input[1] - '0'].position = horizontal;
                                                        }
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
                                                not_fit += spieler1[input[0] - 'A'][input[1] - '0' + i].content; /*nicht alle Felder sind frei*/
                                        }
                                        if (not_fit) {
                                                ship_not_fit(length, number);
                                        } else { /*Legaler input*/
                                                for (i = 0; i < length; ++i) {
                                                        spieler1[input[0] - 'A'][input[1] - '0' + i].content = ship;
                                                        spieler1[input[0] - 'A'][input[1] - '0' + i].length = length;
                                                        spieler1[input[0] - 'A'][input[1] - '0' + i].number = number;
                                                        if (i == 0) {
                                                                spieler1[input[0] - 'A'][input[1] - '0' + i].position = top;
                                                        } else if (i == length - 1) {
                                                                spieler1[input[0] - 'A'][input[1] - '0' + i].position = bottom;
                                                        } else {
                                                                spieler1[input[0] - 'A'][input[1] - '0' + i].position = vertical;
                                                        }
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
        return 'h'; /*Will never be reached, but causes warning if missing*/
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
                switch (spieler1[i][row].content) {
                case water:
                        printf("%s", "|    "); break;
                case hit_water:
                        printf("%s", "| () "); break;
                case ship:
                        switch (spieler1[i][row].position) {
                        case left:
                                printf("%s", "| <= "); break;
                        case horizontal:
                                printf("%s", "| == "); break;
                        case right:
                                printf("%s", "| => "); break;
                        case top:
                                printf("%s", "| /\\ "); break;
                        case vertical:
                                printf("%s", "| || "); break;
                        case bottom:
                                printf("%s", "| \\/ "); break;
                        }
                        break;
                case hit_ship:
                        switch (spieler1[i][row].position) {
                        case left:
                                printf("%s", "|#<=#"); break;
                        case horizontal:
                                printf("%s", "|#==#"); break;
                        case right:
                                printf("%s", "|#=>#"); break;
                        case top:
                                printf("%s", "|#/\\#"); break;
                        case vertical:
                                printf("%s", "|#||#"); break;
                        case bottom:
                                printf("%s", "|#\\/#"); break;
                        }
                        break;
                case destroyed_ship:
                        switch (spieler1[i][row].position) {
                        case left:
                                printf("%s", "|<***"); break;
                        case horizontal:
                                printf("%s", "|****"); break;
                        case right:
                                printf("%s", "|***>"); break;
                        case top:
                                printf("%s", "|*/\\*"); break;
                        case vertical:
                                printf("%s", "||**|"); break;
                        case bottom:
                                printf("%s", "|*\\/*"); break;
                        }
                        break;
                default:
                        printf("%s", "| ERR"); /*Should never be reached*/
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
