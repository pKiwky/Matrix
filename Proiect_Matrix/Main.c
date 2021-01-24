#include "CMatrix.h";

void main() {
	//while(true) {
	CMatrix* m1 = Matrix_Create(2, 2, false);
	Matrix_Fill(m1, 5);

	CMatrix* temp = Matrix_Operation(m1, m1, Sum);
	Matrix_Print(temp);
	Matrix_Delete(&temp);
	Matrix_Delete(&m1);
	//}
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