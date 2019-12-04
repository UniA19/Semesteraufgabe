#include "input.h"

void get_field(char input[])
{
        int end = 0;
        int ic = 0;     /*z.B. 0A*/
        int ci = 0;     /*z.B. A0*/
        
        input[0] = getchar();
                
        /*Fehlerbehandlung bei zu kurzem Input*/
        if (input[0] != '\n') {
                input[1] = getchar();
        } else {
                input[1] = ' ';
        }
        
        /*Überschüssigen Input löschen*/
        if (input[0] != '\n' && input[1] != '\n') {
                while ((getchar()) != '\n');
        }
        
        input[0] = toupper(input[0]);
        input[1] = toupper(input[1]);
        
        /*Input validieren*/
        ic = (input[0] - '0' >= 0 && input[0] - '0' < height) && (input[1] - 'A' >= 0 && input[1] - 'A' < width);
        ci = (input[0] - 'A' >= 0 && input[0] - 'A' < width) && (input[1] - '0' >= 0 && input[1] - '0' < height);
        end = ic || ci;
        if (ic) {
                char temp = input[0];
                input[0] = input[1];
                input[1] = temp;
        }
        if (!end) {
                printf("'%c%c' is no legal input!\nPlease try again:\a", input[0], input[1]);
                get_field(input);
        }
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
        get_start(5, 1);
        print();
        get_start(4, 2);
        print();
        get_start(4, 3);
        print();
        get_start(3, 4);
        print();
        get_start(3, 5);
        print();
        get_start(2, 6);
        print();
        get_start(2, 7);
        print();
}

void get_start(int length, int number)
{
        char input[2];
        char orientation;
        printf("Please enter the starting field of ship with length '%i': ", length);
        get_field(input);
        
        orientation = get_orientation(length);
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
