#include <stdio.h>

/*Methode zum setzen der Startpositionen*/
void set_start();

/*Methoden für den graphischen Output*/
void print();
void line_1();
void line_2();

/*Methoden für die Logik*/
void set_start();

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
        
}

void print()
{
        int i;
        for (i = 'A'; i <= 'J'; ++i) {
                printf("%s%c", "    ", i);
        }
        printf("%s\n", "  ");
        for (i = 1; i <= 10; ++i) {
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