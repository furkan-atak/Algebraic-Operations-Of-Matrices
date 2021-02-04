/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test.cpp
 * Author: Pc
 *
 * Created on 16 January 2021, 17:37
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include "lal.h"
#include <typeinfo>
#include <future>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int rows = 5, cols = 5;
    double* matrix1 = (double*) calloc(sizeof (double), rows * cols);
    double* matrix2 = (double*) calloc(sizeof (double), rows * cols);
    double* vector1 = (double*) calloc(sizeof (double), rows);
    double* vector2 = (double*) calloc(sizeof (double), rows);
    double counter = 0;
    for (int i = 0; i < rows; i++) {
        vector1[i] = counter;
        vector2[i] = counter + 1;
        for (int j = 0; j < cols; j++) {
            matrix1[i * cols + j] = counter++;
            matrix2[i * cols + j] = counter + 1;
        }
    }
    Matrix *m = new Matrix(matrix1, 3, 3);
    Matrix *m2 = new Matrix(matrix2, 3, 3);
    Vector *v = new Vector(vector1, 3);
    Vector *v2 = new Vector(vector2, 3);
    cout << "m1: " << endl;
    m->print();
    cout << "m2: " << endl;
    m2->print();

    cout << endl << "Matrix Toplam" << endl;
    Matrix *m3 = *m + *m2;
    m3->print();

    cout << endl << "Matrix Çıkarma" << endl;
    Matrix *m4 = (*m2)-(*m);
    m4->print();

    cout << endl << "Matrix Çarpma" << endl;
    Matrix *m5 = (*m)*(*m2);
    m5->print();

    cout << endl << "Matris İnc-Pre" << endl;
    (++(*m5))->print();

    cout << endl << "Matris Inc-Post";
    ((*m2)++)->print();
    cout << endl << "Post matrix";
    m2->print();

    cout << "Matrix1" << endl;
    m->print();
    cout << "Matrix Transpose";
    Matrix* trans = transpose(*m);
    trans->print();

    cout << endl << "vektor1:" << endl;
    v->print();
    cout << endl << "vektor2:" << endl;
    v2->print();
    cout << endl << "Vektor Toplam" << endl;
    (*v + *v2)->print();
    cout << "with casting";
    Matrix *v3 = *v + *v2;
    Vector *sumV = static_cast<Vector*> (v3);
    sumV->print();

    cout << endl << "Vektor Cıkarma" << endl;
    (*v2 - *v)->print();
    cout << "with casting";
    Matrix *v4 = *v2 - *v;
    Vector *subV = static_cast<Vector*> (v4);
    subV->print();

    cout << "Vector Ic Carpım";
    double multiVec = (*v) * (*v2);
    cout << endl << multiVec << " " << endl;


    cout << "vector1" << endl;
    v->print();
    cout << "Vector Inc-Pre" << endl;
    (++(*v))->print();

    cout << "Vector Inc-Post" << endl;
    ((*v)++)->print();
    cout << "post vector";
    v->print();

    cout << "Matrix x Vector" << endl;
    Matrix *multMV = (*m)*(*v);
    multMV->print();

    cout << endl << "Vector Transpose" << endl;
    (transpose(*v))->print();


    cout << "vector norm" << endl;
    norm(*v);
    cout << endl << "matrix norm" << endl;
    norm(*m);

    int f = 5;
    int g = 4;
    Vector** arrVec = CreateVectorArray(f, g);
    FillVectorArray(arrVec, f, g);

    Matrix *myMat = vectorArray2Matrix(arrVec, f, g);
    myMat->print();

    Matrix* arr[4];
    arr[0] = m;
    arr[1] = m2;
    arr[2] = v;
    arr[3] = v2;

    arr[0]->print();
    arr[3]->print();

    return 0;
}

