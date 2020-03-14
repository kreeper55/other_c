#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//  ��������� "���� ��� ������" �������
//  (�� ����� ���� ��� �� ����� ��� ������, � ���� ����� ����������� ��� ������ �����)
typedef struct Matrix
{
    int rows;       //  ������
    int columns;    //  �������
    int **field;    //  ����
} Matrix;

//  �������������� �������
Matrix* init_matrix_zero(const int n, const int m)
{
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = n;
    matrix->columns = m;
    //  �������� ��� ��� ������
    matrix->field = (int**) malloc(n * sizeof(int*)); //  �������� ������ ��� ������
    for (int i = 0; i < n; i++)
    {
        matrix->field[i] = (int*) malloc(m * sizeof(int));  //  �������� ������ ��� �������
        for (int j = 0; j < m; j++)
        {
            //  � ������ ��������� ������� 0
            matrix->field[i][j] = 0;
        }
    }
    return matrix;  //  � ���������� ���� �������
}

//  ������� ������������ ������ ���� �������
void clear_field(Matrix *arr)
{
    for (int i = 0; i < arr->rows; i++)
    {
        //  ������������ ������ ������� �������
        free(arr->field[i]);
    }
    //  ������������ ������ ������ ����
    free(arr->field);
    //  ��������� �� ���� ����������� ���
    arr->field = NULL;
}

//  ������� ������������� ������ �������
void delete_matrix(Matrix **matrix)
{
    //  �������� ������� ������� ���� �������
    clear_field(*matrix);
    //  ������������ ������, ������� �������� �������
    free(*matrix);
    matrix = NULL;
}

//  ����� ������� � �������
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
