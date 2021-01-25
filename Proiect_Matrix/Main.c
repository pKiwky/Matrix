#include "CMatrix.h";

void main() {
	CMatrix* m1 = Matrix_Create(5, 5, true);
	printf("%i", Matrix_Determinant(m1));
}

/*

1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5
1 2 3 4 5

3 4 5 6 8
6 7 3 7 7
7 3 2 5 5			= -1550
5 3 1 6 6
4 32 3 4 4
*/