#ifndef INPUT_H
#define INPUT_H

#include "global.h"
#include "printing.h"
#include <stdio.h>
#include <ctype.h>

/*Methode zum setzen der Startpositionen*/
int set_start_values(void);
int get_start(int length, int number);
char get_orientation(int length);
int ship_not_fit(int length, int number);

/*Allgemeine Methoden*/
int get_size(void);
int get_field(int *row, char *column);
int flush(void);

#endif
