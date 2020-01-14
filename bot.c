#include "bot.h"
#include "global.h"

int GetRandInt(int upper, int lower)
{
        int res = (rand() % (upper - lower +1)) + lower;
        return res;
}

void GetFieldBot(int *row, char* column)
{
         /*Generate Column (65 == A 90 == Z)*/

        *column = GetRandInt(65 + width-1, 65);
        *row = GetRandInt(height-1, 0);
}

void GetField_onHit(int *row, char* column)
{
    /* get Driection of followup */
    int followup_direction = GetRandInt(3, 0); /* 0=up, 1=right, 2=down, 3=left*/

    switch(followup_direction)
    {
        case 0:
            if( *row -1 >= 0)
            {
                *row = *row-1;
            } else {
                GetFieldBot(row, column);
            }
            break;
        case 1:
            if( (*column - 'A') + 1 < width)
            {
                *column = *column + 1;
            } else {
                GetFieldBot(row, column);
            }
            break;
        case 2:
            if( *row + 1 < height)
            {
                *row = *row + 1;
            } else {
                GetFieldBot(row, column);
            }
            break;
        case 3:
            if( (*column - 'A') -1 >= 0 )
            {
                *column = *column - 1;
            } else {
                GetFieldBot(row, column);
            }
            break;
    }
}

char GetOrientationBot()
{
        int choice = GetRandInt(1, 0);
        if(choice == 0)
        {
                return 'H';
        } else {
                return 'V';
        }
}


int GetStartBot(int length, int number)
{
        int row;
        char column;
        char orientation;

        while(1)
        {
                GetFieldBot(&row, &column);

                orientation = GetOrientationBot();

                if (orientation == 'H')
                {
                        if (((column - 'A') + length) <= width) /*passt das schiff horizontal in das grid?*/
                        {
                                int i;
                                int not_fit = 0;
                                for (i = 0; i < length; ++i) {
                                        not_fit += spieler2[column - 'A' + i][row].content; /*nicht alle Felder sind frei*/
                                }
                                if (not_fit == 0)
                                { /*Legaler input*/
                                        for (i = 0; i < length; ++i)
                                        {
                                                spieler2[column - 'A' + i][row].content = ship;
                                                spieler2[column - 'A' + i][row].length = length;
                                                spieler2[column - 'A' + i][row].number = number;
                                                if (i == 0) {
                                                        spieler2[column - 'A' + i][row].position = left;
                                                } else if (i == length - 1) {
                                                        spieler2[column - 'A' + i][row].position = right;
                                                } else {
                                                        spieler2[column - 'A' + i][row].position = horizontal;
                                                }
                                        }
                                        break;
                                }
                        }

                } else {
                        if (((row) + length) <= height) {
                                int i;
                                int not_fit = 0;
                                for (i = 0; i < length; ++i) {
                                        not_fit += spieler2[column - 'A'][row + i].content; /*nicht alle Felder sind frei*/
                                }
                                if (not_fit == 0)
                                {
                                        /*Legaler input*/
                                        for (i = 0; i < length; ++i) {
                                                spieler2[column - 'A'][row + i].content = ship;
                                                spieler2[column - 'A'][row + i].length = length;
                                                spieler2[column - 'A'][row + i].number = number;
                                                if (i == 0) {
                                                        spieler2[column - 'A'][row + i].position = top;
                                                } else if (i == length - 1) {
                                                        spieler2[column - 'A'][row + i].position = bottom;
                                                } else {
                                                        spieler2[column - 'A'][row + i].position = vertical;
                                                }
                                        }
                                        break;
                                }
                        }
                }
        } /*End of while loop*/

            /*==> successfully placed ship*/
            
        return 0;
}

int SetStartBot()
{
    /* Set start for bot */
    if (GetStartBot(5, 1)) {
            return -1;
    }
    if (GetStartBot(4, 2)) {
            return -1;
    }
    if (GetStartBot(4, 3)) {
            return -1;
    }
    if (GetStartBot(3, 4)) {
            return -1;
    }
    if (GetStartBot(3, 5)) {
            return -1;
    }
    if (GetStartBot(2, 6)) {
            return -1;
    }
    if (GetStartBot(2, 7)) {
            return -1;
    }
    printf("Bot has placed his ships!\n");

    return 0;
}
