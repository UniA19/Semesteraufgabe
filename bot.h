#ifndef BOT_H
#define BOT_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"

int GetRandInt(int upper, int lower);

void GetFieldBot(int *row, char *column);

void GetField_onHit(int *row, char* column);

char GetOrientationBot(void);

int GetStartBot(int length, int number);

int SetStartBot(void);

#endif
