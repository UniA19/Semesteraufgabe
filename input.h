#ifndef INPUT_H
#define INPUT_H

#include "global.h"
#include "printing.h"
#include <stdio.h>
#include <ctype.h>

/*Methode zum setzen der Startpositionen*/
int set_start_values();
int get_start();
char get_orientation();
int ship_not_fit();

/*Allgemeine Methoden*/
int get_size();
int get_field(int *row, char *column);
int flush();

#endif