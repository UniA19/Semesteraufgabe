#include <stdio.h>
#include <ctype.h>

/*Methode zum setzen der Startpositionen*/
void set_start();
void get_start();
void get_orientation();

/*Methoden für den graphischen Output*/
void print();
void line_1();
void line_2();

/*Globale Variablen*/
/*
00 -> Wasser "    "
01 -> getroffenes Wasser " () "
1x -> Schiff Nr. x "===="
2x -> gtroffenes Schiff Nr. x " >< " 
3x -> versenktes Schiff Nr. x "(><)"
*/
int spieler1[10][10];
int spieler2[10][10];

int main(void)
{
        print();
        set_start();
        return 0;
}

void set_start()
{
        get_start(5);
        get_start(4);
        get_start(4);
        get_start(3);
        get_start(3);
        get_start(2);
        get_start(2);
        
}

void get_start(int length)
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
                ic = (input[0] >= '0' && input[0] <= '9') && (input[1] >= 'A' && input[1] <= 'J');
                ci = (input[0] >= 'A' && input[0] <= 'J') && (input[1] >= '0' && input[1] <= '9');
                end = ic || ci;
                if (ic) {
                        char temp = input[0];
                        input[0] = input[1];
                        input[1] = temp;
                }
                if (!end) {
                        printf("'%s' is no legal input!\n", input);
                } 
        }       
}

void get_orientation(int lngth)
{
        
}

void print()
{
        int i;
        for (i = 'A'; i <= 'J'; ++i) {
                printf("%s%c", "    ", i);
        }
        printf("%s\n", "  ");
        for (i = 0; i < 10; ++i) {
                line_1();
                line_2(i);
        }
        line_1();
}

void line_1()
{
        int i;
        printf("%s", "  ");
        for (i = 'A'; i <= 'J'; ++i) {
                printf("%s", "+----");
        }
        printf("%c\n", '+');
}

void line_2(int row)
{
        int i;
        printf("%2i", row);
        for (i = 'A'; i <= 'J'; ++i) {
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