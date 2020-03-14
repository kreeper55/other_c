#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//  объявляем "свой тип данных" матрица
//  (на самом деле это не новый тип данных, а лишь новое обозначение для данных типов)
typedef struct Matrix
{
    int rows;       //  строки
    int columns;    //  столбцы
    int **field;    //  поле
} Matrix;

//  инициализируем матрицу
Matrix* init_matrix_zero(const int n, const int m)
{
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = n;
    matrix->columns = m;
    //  выделяем под нее память
    matrix->field = (int**) malloc(n * sizeof(int*)); //  выделяем память под строки
    for (int i = 0; i < n; i++)
    {
        matrix->field[i] = (int*) malloc(m * sizeof(int));  //  выделяем память под столбцы
        for (int j = 0; j < m; j++)
        {
            //  и задаем начальное значени 0
            matrix->field[i][j] = 0;
        }
    }
    return matrix;  //  и возвращаем нашу матрицу
}

//  функция освообждения памяти поля матрицы
void clear_field(Matrix *arr)
{
    for (int i = 0; i < arr->rows; i++)
    {
        //  высвобождаем память каждого столбца
        free(arr->field[i]);
    }
    //  высвобождаем память нашего поля
    free(arr->field);
    //  указателю на поле присваиваем нул
    arr->field = NULL;
}

//  функция высвобождении памяти матрицы
void delete_matrix(Matrix **matrix)
{
    //  вызываем функцию очистки поля матрицы
    clear_field(*matrix);
    //  высвобождаем память, которая занимала матрица
    free(*matrix);
    matrix = NULL;
}

//  вывод матрицы в консоль
void printf_matrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            printf("%d ", matrix->field[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
