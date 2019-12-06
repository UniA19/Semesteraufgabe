#include "printing.h"
#include <stdio.h>

#define SPACE_BETWEEN "            "

extern struct Field **spieler1;
extern struct Field **spieler2;

void print()
{
        int i;
        printf("\n");
        printf("%s", "                        DU                           ");
        printf("%s\n\n","                                   GEGNER");
        for (i = 'A'; i < 'A' + width; ++i) {
                printf("%s%c", "    ", i);
        }
        printf("%s", "  ");
        printf("%s", SPACE_BETWEEN);
        printf("%s", " ");
        for (i = 'A'; i < 'A' + width; ++i) {
                printf("%s%c", "    ", i);
        }
        printf("\n");
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
        printf("%c", '+');
        printf("%s", SPACE_BETWEEN);
        printf("%s", "  ");/*space for numbers of row*/
        for (i = 'A'; i < 'A' + width; ++i) {
                printf("%s", "+----");
        }
        printf("%c\n", '+');
}

void line_2(int row)
{
        int i;
        printf("%2i", row);
        /*Spieler 1*/
        for (i = 0; i < width; ++i) {
                switch (spieler1[i][row].content) {
                        case water:
                                printf("%s", "|    ");
                                break;
                        case hit_water:
                                printf("%s", "| () ");
                                break;
                        case ship:
                                switch (spieler1[i][row].position) {
                                        case left:
                                                printf("%s", "| <= ");
                                                break;
                                        case horizontal:
                                                printf("%s", "| == ");
                                                break;
                                        case right:
                                                printf("%s", "| => ");
                                                break;
                                        case top:
                                                printf("%s", "| /\\ ");
                                                break;
                                        case vertical:
                                                printf("%s", "| || ");
                                                break;
                                        case bottom:
                                                printf("%s", "| \\/ ");
                                                break;
                                        default:
                                                printf("%s", "| ERR"); /*Should never be reached*/
                                }
                                break;
                        case hit_ship:
                                switch (spieler1[i][row].position) {
                                        case left:
                                                printf("%s", "|#<=#");
                                                break;
                                        case horizontal:
                                                printf("%s", "|#==#");
                                                break;
                                        case right:
                                                printf("%s", "|#=>#");
                                                break;
                                        case top:
                                                printf("%s", "|#/\\#");
                                                break;
                                        case vertical:
                                                printf("%s", "|#||#");
                                                break;
                                        case bottom:
                                                printf("%s", "|#\\/#");
                                                break;
                                        default:
                                                printf("%s", "| ERR"); /*Should never be reached*/
                                }
                                break;
                        case destroyed_ship:
                                switch (spieler1[i][row].position) {
                                        case left:
                                                printf("%s", "|<***");
                                                break;
                                        case horizontal:
                                                printf("%s", "|****");
                                                break;
                                        case right:
                                                printf("%s", "|***>");
                                                break;
                                        case top:
                                                printf("%s", "|*/\\*");
                                                break;
                                        case vertical:
                                                printf("%s", "|*||*");
                                                break;
                                        case bottom:
                                                printf("%s", "|*\\/*");
                                                break;
                                        default:
                                                printf("%s", "| ERR"); /*Should never be reached*/
                                }
                                break;
                        default:
                                printf("%s", "| ERR"); /*Should never be reached*/
                }
        }
        
        printf("%c", '|');
        printf("%s", SPACE_BETWEEN);
        printf("%2i", row);
        /*Spieler 2*/
        for (i = 0; i < width; ++i) {
                switch (spieler2[i][row].content) {
                        case water:
                                printf("%s", "|    ");
                                break;
                        case hit_water:
                                printf("%s", "| () ");
                                break;
                        case ship:
                                printf("%s", "|    ");
                                break;
                        case hit_ship:
                                printf("%s", "| >< ");
                                break;
                        case destroyed_ship:
                                switch (spieler1[i][row].position) {
                                        case left:
                                                printf("%s", "|<***");
                                                break;
                                        case horizontal:
                                                printf("%s", "|****");
                                                break;
                                        case right:
                                                printf("%s", "|***>");
                                                break;
                                        case top:
                                                printf("%s", "|*/\\*");
                                                break;
                                        case vertical:
                                                printf("%s", "|*||*");
                                                break;
                                        case bottom:
                                                printf("%s", "|*\\/*");
                                                break;
                                        default:
                                                printf("%s", "| ERR"); /*Should never be reached*/
                                }
                                break;
                        default:
                                printf("%s", "| ERR"); /*Should never be reached*/
                }
        }
        printf("%c\n", '|');
}