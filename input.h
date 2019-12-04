#ifndef INPUT_H
#define INPUT_H

#include "global.h"
#include "printing.h"
#include <stdio.h>
#include <ctype.h>

/*Methode zum setzen der Startpositionen*/
void set_start_values();
void get_start();
char get_orientation();
void ship_not_fit();

/*Allgemeine Methoden*/
void get_field();

#endif