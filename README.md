# Semesteraufgabe
In dieser Semesteraufgabe wird das Spiel "Schiffe versenken" in c programmiert.

Compile with:
gcc -c printing.c -o printing.o -ansi -pedantic -Wall -Wextra
gcc -c input.c -o input.o -ansi -pedantic -Wall -Wextra
gcc printing.o input.o Semesteraufgabe.c -o Semesteraufgabe -ansi -pedantic -Wall -Wextra

Test with:
type test.txt | ./Semesteraufgabe