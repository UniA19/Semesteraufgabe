#include "input.h"

int get_size() 
{
        int right = 0;
        int temp = 0;
        int valid = 0;
        printf("Please enter the width of the field (between %i and %i): ", WIDTH_MIN, WIDTH_MAX);
        while (!right) {
                scanf("%i", &temp);
                if (temp < WIDTH_MIN) {
                        right = 0;
                        printf("The width must be between %i and %i!\nPlease try again: ", WIDTH_MIN, WIDTH_MAX);
                } else if (WIDTH_MIN <= temp && temp <= WIDTH_MAX) {
                        right = 1;
                } else if (WIDTH_MAX < temp) {
                        right = 0;
                        printf("The width must be between %i and %i!\nPlease try again: ", WIDTH_MIN, WIDTH_MAX);
                }
        }
        width = temp;
        if (flush()) {
                return -1;
        }
        
        temp = 0;
        right = 0;
        printf("Please enter the height of the field (between %i and %i): ", HEIGHT_MIN, HEIGHT_MAX);
        while (!right) {
                scanf("%i", &temp);
                if (temp < HEIGHT_MIN) {
                        right = 0;
                        printf("The height must be between %i and %i!\nPlease try again: ", HEIGHT_MIN, HEIGHT_MAX);
                } else if (HEIGHT_MIN <= temp && temp <= HEIGHT_MAX) {
                        right = 1;
                } else if (HEIGHT_MAX < temp) {
                        right = 0;
                        printf("The height must be between %i and %i!\nPlease try again: ", HEIGHT_MIN, HEIGHT_MAX);
                }
        }
        height = temp;
        if (flush()) {
                return -1;
        }
    
        /* Get difficulty level*/
        printf("Please enter the desired difficulty level! (1 or 2): ");
        temp = 0;
        while(!valid)
        {
                scanf("%i", &temp);
                if(temp == 1)
                {
                        difficulty = 1;
                        valid = 1;
                } else if (temp == 2) {
                        difficulty = 2;
                        valid = 1;
                } else {
                        printf("Difficulty level musst be 1 or 2! Please try again: ");
                }
        }
        return 0;
}

int get_field(int *row, char *column)
{
        int end = 0;
        int ic = 0;     /*z.B. 0A*/
        int ci = 0;     /*z.B. A0*/
        
        char input[3];
        
        input[0] = getchar();
                
        /*Fehlerbehandlung bei zu kurzem Input*/
        if (input[0] != '\n') {
                input[1] = getchar();
                if (input[1] != '\n') {
                        input[2] = getchar();
                } else {
                        input[2] = ' ';
                }
        } else {
                input[1] = ' ';
        }
        
        /*Überschüssigen Input löschen*/
        if (input[0] != '\n' && input[1] != '\n' && input[2] != '\n') {
                if (flush()) { /*EOF*/
                        return -1;
                }
        }
        
        /*Hinzufügen der 0 bei Zahlen < 10 (A3 -> A03 bzw. 3A -> 03A)*/
        if (input[2] == '\n') {
                if (input[0] >= '0' && input[0] <= '9') {
                        input[2] = input[1];
                        input[1] = input[0];
                        input[0] = '0';
                } else {
                        input[2] = input[1];
                        input[1] = '0';
                }
        }
        
        input[0] = toupper(input[0]);
        input[1] = toupper(input[1]);
        input[2] = toupper(input[2]);
        
        /*Input validieren*/
        ic = (input[0] >= '0' && input[0] <= '9') && (input[1] >= '0' && input[1] <= '9') && (input[2] >= 'A' && input[2] <= 'Z');
        ci = (input[0] >= 'A' && input[0] <= 'Z') && (input[1] >= '0' && input[1] <= '9') && (input[2] >= '0' && input[2] <= '9');
        
        if (ic) {
                char temp = input[0];
                input[0] = input[2];
                input[2] = input[1];
                input[1] = temp;
        }
        
        /*Input umrechnen*/
        *column = input[0];
        *row = ((input[1] - '0') * 10) + (input[2] - '0');
        
        end = *column - 'A' < width && *column - 'A' >= 0 && *row < height && *row >= 0;
        
        end = end && (ic || ci);
        
        if (!end) {
                printf("'%c%c%c' is no legal input!\nPlease try again:\a", input[0], input[1], input[2]);
                get_field(row, column);
        }
        return 0;
}

int set_start_values()
{       
        int i;
        int j;
        for (i = 0; i < width; ++i) {
                for (j = 0; j < height; ++j) {
                        spieler1[i][j].content = water;
                        spieler1[i][j].length = 0;
                        spieler1[i][j].number = 0;
                        spieler1[i][j].position = none;
                        
                        spieler2[i][j].content = water;
                        spieler2[i][j].length = 0;
                        spieler2[i][j].number = 0;
                        spieler2[i][j].position = none;
                }
        }
        print();
        if (get_start(5, 1)) {
                return -1;
        }
        print();
        if (get_start(4, 2)) {
                return -1;
        }
        print();
        if (get_start(4, 3)) {
                return -1;
        }
        print();
        if (get_start(3, 4)) {
                return -1;
        }
        print();
        if (get_start(3, 5)) {
                return -1;
        }
        print();
        if (get_start(2, 6)) {
                return -1;
        }
        print();
        if (get_start(2, 7)) {
                return -1;
        }
        print();
    
    
        return 0;
}

int get_start(int length, int number)
{
        int row;
        char column;
        char orientation;
        printf("Please enter the starting field of ship with length '%i': ", length);
        
        if (get_field(&row, &column)) {
                return -1;
        }
        
        orientation = get_orientation(length);
        if (orientation < 0) {
                return orientation;
        }
        if (orientation == 'H') {
                if (((column - 'A') + length) <= width) {
                        int i;
                        int not_fit = 0;
                        for (i = 0; i < length; ++i) {
                                not_fit += spieler1[column - 'A' + i][row].content; /*nicht alle Felder sind frei*/
                        }
                        if (not_fit) {
                                ship_not_fit(length, number);
                        } else { /*Legaler input*/
                                for (i = 0; i < length; ++i) {
                                        spieler1[column - 'A' + i][row].content = ship;
                                        spieler1[column - 'A' + i][row].length = length;
                                        spieler1[column - 'A' + i][row].number = number;
                                        if (i == 0) {
                                                spieler1[column - 'A' + i][row].position = left;
                                        } else if (i == length - 1) {
                                                spieler1[column - 'A' + i][row].position = right;
                                        } else {
                                                spieler1[column - 'A' + i][row].position = horizontal;
                                        }
                                }
                        }
                } else {
                        /*Das Schiff passt horizontal nicht in das Feld!*/
                        ship_not_fit(length, number);
                }
        } else {
                if (((row) + length) <= height) {
                        int i;
                        int not_fit = 0;
                        for (i = 0; i < length; ++i) {
                                not_fit += spieler1[column - 'A'][row + i].content; /*nicht alle Felder sind frei*/
                        }
                        if (not_fit) {
                                ship_not_fit(length, number);
                        } else { /*Legaler input*/
                                for (i = 0; i < length; ++i) {
                                        spieler1[column - 'A'][row + i].content = ship;
                                        spieler1[column - 'A'][row + i].length = length;
                                        spieler1[column - 'A'][row + i].number = number;
                                        if (i == 0) {
                                                spieler1[column - 'A'][row + i].position = top;
                                        } else if (i == length - 1) {
                                                spieler1[column - 'A'][row + i].position = bottom;
                                        } else {
                                                spieler1[column - 'A'][row + i].position = vertical;
                                        }
                                }
                        }
                } else {
                        /*Das Schiff passt vertikal nicht in das Feld!*/
                        ship_not_fit(length, number);
                }
        }
        return 0;
}

int ship_not_fit(int length, int number)
{
        printf("%s", "The ship doesn't fit like this!\n\a");
        if (get_start(length, number)) {
                return -1;
        }
        return 0;
}

char get_orientation(int length)
{
        char input[1];
        int end = 0;
        while (!end) {
                printf("Please enter the orientation of ship with length '%i'\n 'h' for horizontal or 'v' for vertical: ", length);
                input[0] = getchar();
                if (input[0] != '\n') {
                        if (flush()) {
                                return -1;
                        }
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

int flush()
{
        char c = getchar();
        while (c != EOF && c != '\n') c = getchar();
        return c == EOF;
}
