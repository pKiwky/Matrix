#include "CMatrix.h"

bool Matrix_IsValid(const CMatrix* matrix) {
	return (matrix != NULL		 /**/ &&
			matrix->data != NULL /**/ &&
			matrix->lines > 0	 /**/ &&
			matrix->cols > 0);
}

CMatrix* Matrix_Create(int _lines, int _cols, bool _read) {
	CMatrix* result = (CMatrix*)malloc(sizeof(CMatrix));

	// Se salveaza numarul de linii si coloane.
	result->lines = _lines;
	result->cols = _cols;

	result->data = (int**)malloc(sizeof(int) * _lines);
	for(int i = 0; i < _lines; i++) {
		result->data[i] = (int*)malloc(sizeof(int) * _cols);
	}

	for(int i = 0; i < _lines; i++) {
		for(int j = 0; j < _cols; j++) {
			if(_read == true) { // _read = true -> Se citeste elementul.
				scanf("%i", &result->data[i][j]);
			} else { // _read = false -> Se initializeaza cu 0.
				result->data[i][j] = 0;
			}
		}
	}

	return result;
}

void Matrix_Fill(CMatrix* matrix, int _value) {
	if(Matrix_IsValid(matrix) == false) return;

	for(int i = 0; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->cols; j++) {
			matrix->data[i][j] = _value;
		}
	}
}

void Matrix_Delete(CMatrix** matrix) {
	if(*matrix != NULL) {
		for(int i = 0; i < (*matrix)->lines; i++) {
			free((*matrix)->data[i]);
		}
		free((*matrix)->data);
		free(*matrix);

		// Pointeaza matricea la null.
		(*matrix) = NULL;
	}
}

int Matrix_Print(const CMatrix* matrix) {
	if(Matrix_IsValid(matrix) == false) return 0;

	for(int i = 0; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->cols; j++) {
			printf("%i ", matrix->data[i][j]);
		}
		printf("\n");
	}

	return 1;
}

int Matrix_SafeGet(const CMatrix* matrix, int _line, int _col) {
	if(Matrix_IsValid(matrix) == false) return -1;

	if(_line >= matrix->lines || _col >= matrix->cols) return 0;

	return matrix->data[_line][_col];
}

CMatrix* Matrix_Operation(const CMatrix* matrix1, const CMatrix* matrix2, SimpleOperation operation) {
	// Una dintre matrice nu exista, nu are element, linii sau coloane.
	if(Matrix_IsValid(matrix1) == false || Matrix_IsValid(matrix2) == false)
		return NULL;

	// Maximul de linii dintre cele doua matrice.
	int maxLines = matrix1->lines > matrix2->lines ? matrix1->lines : matrix2->lines;

	// Maximul de coloane dintre cele doua matrice.
	int maxCols = matrix1->cols > matrix2->cols ? matrix1->cols : matrix2->cols;

	// Matricea care se returneaza. Este formata din numarul maxim de linii si coloane.
	CMatrix* result = Matrix_Create(maxLines, maxCols, false);

	for(int i = 0; i < maxLines; i++) {
		for(int j = 0; j < maxCols; j++) {
			if(operation == Sum) {
				result->data[i][j] = Matrix_SafeGet(matrix1, i, j) + Matrix_SafeGet(matrix2, i, j);
			} else {
				result->data[i][j] = Matrix_SafeGet(matrix1, i, j) - Matrix_SafeGet(matrix2, i, j);
			}
		}
	}

	return result;
}

void Matrix_Increment(CMatrix* matrix, int _value) {
	for(int i = 0; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->cols; j++) {
			matrix->data[i][j] += _value;
		}
	}
}

CMatrix* Matrix_Multiply(const CMatrix* matrix1, const CMatrix* matrix2) {
	// Una dintre matrice nu exista, nu are element, linii sau coloane.
	if(Matrix_IsValid(matrix1) == false || Matrix_IsValid(matrix2) == false)
		return NULL;

	// Daca nu se pot inmulti se returneaza NULL. 
	if(matrix1->cols != matrix2->lines)
		return NULL;

	// Matricea care se returneaza. (Liniile matricei 1 si coloanele matricei 2).
	CMatrix* result = Matrix_Create(matrix1->lines, matrix2->cols, false);

	for(int i = 0; i < matrix1->lines; i++) {
		for(int j = 0; j < matrix2->cols; j++) {
			for(int k = 0; k < matrix1->cols; k++) {
				result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
			}
		}
	}

	return result;
}

void Matrix_Multiply_Scalar(CMatrix* matrix, int _value) {
	for(int i = 0; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->cols; j++) {
			matrix->data[i][j] *= _value;
		}
	}
}

void Matrix_Spirtal(const CMatrix* matrix) {
	if(Matrix_IsValid(matrix) == false) return;

	int k = 0;
	int rowSize = matrix->lines - 1;
	int colSize = matrix->cols - 1;

	while(rowSize + 1 > k) {
		for(int i = k; i < colSize; i++) {
			printf("%i ", matrix->data[k][i]);
		}
		for(int i = k; i < rowSize; i++) {
			printf("%i ", matrix->data[i][colSize]);
		}
		for(int i = colSize; i > k; i--) {
			printf("%i ", matrix->data[rowSize][i]);
		}
		for(int i = rowSize; i > k; i--) {
			printf("%i ", matrix->data[i][k]);
		}

		colSize--;
		rowSize--;
		k++;
	}

	if(matrix->lines % 2 == 1 && matrix->cols % 2 == 1) {
		printf("%i", matrix->data[k - 1][k - 1]);
	}
}

CMatrix* Matrix_Pow(const CMatrix* matrix, int _power) {
	if(Matrix_IsValid(matrix) == false) return NULL;

	// Daca _power este <= 1 returneaza matricea initiala.
	if(_power <= 1) return matrix;

	CMatrix* result = Matrix_Multiply(matrix, matrix);

	for(int i = 2; i < _power; i++) {
		result = Matrix_Multiply(result, matrix);
	}

	return result;
}

CMatrix* Matrix_Transposed(const CMatrix* matrix) {
	if(Matrix_IsValid(matrix) == false) return NULL;

	// Rezulatul are coloanele si liniile inversate.
	CMatrix* result = Matrix_Create(matrix->cols, matrix->lines, false);

	for(int i = 0; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->cols; j++) {
			result->data[j][i] = matrix->data[i][j];
		}
	}

	return result;
}

void Matrix_Remove_Line(CMatrix* matrix, int _line) {
	if(Matrix_IsValid(matrix) == false) return NULL;

	matrix->lines--;
	for(int i = _line - 1; i < matrix->lines; i++) {
		for(int j = 0; j < matrix->cols; j++) {
			matrix->data[i][j] = matrix->data[i + 1][j];
		}
	}
}

void Matrix_Remove_Col(CMatrix* matrix, int _col) {
	if(Matrix_IsValid(matrix) == false) return NULL;

	matrix->cols--;
	for(int i = 0; i < matrix->lines; i++) {
		for(int j = _col - 1; j < matrix->cols; j++) {
			matrix->data[i][j] = matrix->data[i][j + 1];
		}
	}
}

bool Matrix_bDeterminant(const CMatrix* matrix) {
	return (matrix->cols == matrix->lines && matrix->lines >= 2);
}

/*
Nu este declarata in .h, nu trebuie folosita.
Matrix_Determinant() pentru orice matrice.
*/
int Matrix_Intern_3x3(const CMatrix* matrix) {
	if(Matrix_bDeterminant(matrix) == false) return 0;

	int det = 0;
	det += matrix->data[0][0] * matrix->data[1][1] * matrix->data[2][2];
	det += matrix->data[1][0] * matrix->data[2][1] * matrix->data[0][2];
	det += matrix->data[0][1] * matrix->data[1][2] * matrix->data[2][0];

	det -= matrix->data[0][2] * matrix->data[1][1] * matrix->data[2][0];
	det -= matrix->data[2][1] * matrix->data[1][2] * matrix->data[0][0];
	det -= matrix->data[1][0] * matrix->data[0][1] * matrix->data[2][2];
	return det;
}

int Matrix_Determinant(const CMatrix* matrix) {
	if(Matrix_bDeterminant(matrix) == false) return 0;

	int result = 0,
		lines = matrix->lines,	// Numarul initial de linii.
		cols = matrix->cols,	// Numarul initial de coloane.
		slowCounter = 0;

	if(lines == 2) return (matrix->data[0][0] * matrix->data[1][1] -
						   matrix->data[0][1] * matrix->data[1][0]);
	if(lines == 3) return (Matrix_Intern_3x3(matrix));

	while(slowCounter < cols) {
		int fastCounter = slowCounter + 1;

		while(fastCounter < cols) {
			// linia 1 | linia 2 | slowCounter | fastCounter > slowCounter si  fastCounter <= cols
			int before = (1 + 2 + slowCounter + fastCounter) % 2 == 0 ? 1 : -1;

			int firstDeterminant =
				matrix->data[0][slowCounter] * matrix->data[1][fastCounter] -
				matrix->data[0][fastCounter] * matrix->data[1][slowCounter];

			CMatrix* temp = Matrix_Create(matrix->lines, matrix->cols, false);
			for(int i = 0; i < temp->lines; i++)
				memcpy(&temp->data[i][0], &matrix->data[i][0], sizeof(int) * temp->cols);

			Matrix_Remove_Col(temp, fastCounter + 1);
			Matrix_Remove_Col(temp, slowCounter + 1);
			Matrix_Remove_Line(temp, 1);
			Matrix_Remove_Line(temp, 1);

			int secondDeterminant = 0;
			if(temp->lines <= 2) { // Matrice 2x2
				secondDeterminant =
					temp->data[0][0] * temp->data[1][1] -
					temp->data[1][0] * temp->data[0][1];

				result += (before * firstDeterminant * secondDeterminant);
			} else if(temp->lines == 3) { // Matrice 3x3 
				int det = Matrix_Intern_3x3(temp);
				result += (before * firstDeterminant * det);
			} else { // Matrice mai mare egal cu 4x4.
				result += (before * firstDeterminant * Matrix_Determinant(temp));
			}

			fastCounter++;
		}
		slowCounter++;
	}

	return result;
}