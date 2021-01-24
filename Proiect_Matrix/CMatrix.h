#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int** data;
	int lines;
	int cols;
} CMatrix;

typedef enum {
	false,
	true
} bool;

typedef enum { Sum, Diff } SimpleOperation;

/*
Se verifica daca matricea este valida.
*/
bool Matrix_IsValid(const CMatrix* matrix);

/*
Se creaza matricea si se returneaza.
_lines = Numarul de linii.
_cols = Numarul de coloane.
_read = (true) Se citeste matricea, altfel se umple cu 0.
*/
CMatrix* Matrix_Create(int _lines, int _cols, bool _read);

/*
Umple matricea cu o valoare.
*/
void Matrix_Fill(CMatrix* matrix, int _value);

/*
Sterge spatiul alocat matricei.
*/
void Matrix_Delete(CMatrix** matrix);

/*
Se afiseaza matricea.
Returneaza 0 - Eroare | 1 - Succes.
*/
int Matrix_Print(const CMatrix* matrix);

/*
Verifica daca matricea are un element pe o anumita pozitie
Returneaza 0 daca nu gaseste elementul sau -1 daca matricea nu exista.
*/
int Matrix_SafeGet(const CMatrix* matrix, int _line, int _col);

/*
Calculeaza si returneaza suma / diferenta a doua matrice.
Daca o matrice este mai mare ca cealalta, elementele care nu exista sunt considerate 0.
SimpleOperation : Sum, Diff.
*/
CMatrix* Matrix_Operation(const CMatrix* matrix1, const CMatrix* matrix2, SimpleOperation operation);

/*
Incrementeaza fiecare element din matrice.
*/
void Matrix_Increment(CMatrix* matrix, int _value);

/*
Returneaza produsul a doua matrice.
*/
CMatrix* Matrix_Multiply(const CMatrix* matrix1, const CMatrix* matrix2);

/*
Returneaza rezultatul inmultirii dintre o matrice si un scalar.
*/
void Matrix_Multiply_Scalar(CMatrix* matrix, int _value);

/*
Afiseaza matricea in spirala.
*/
void Matrix_Spiral(const CMatrix* matrix);

/*
Returneaza rezultatul puterii unei matrici.
*/
CMatrix* Matrix_Pow(const CMatrix* matrix, int _power);

/*
Returneaza transpusa unei matrice.
*/
CMatrix* Matrix_Transposed(const CMatrix* matrix);

/*
Elimina o linie sau o coloana.
*/
void Matrix_Remove_Line(CMatrix* matrix, int _line);
void Matrix_Remove_Col(CMatrix* matrix, int _col);

/*
Verifica daca se poate calcula determinantul matricei.
*/
bool Matrix_bDeterminant(const CMatrix* matrix);

/* Calculeaza si returneaza determinantul matricei. */
int Matrix_Determinant(const CMatrix* matrix);



/*
	1 2 3 4	  1 2 3   1 2 3 4   1 2 3 0
	5 6 7 8 + 4 5 6 = 5 6 7 8 + 4 5 6 0
	1 2 3 4   7 8 9   1 2 3 4	7 8 9 0
	5 6 7 8			  5 6 7 8	0 0 0 0
*/

