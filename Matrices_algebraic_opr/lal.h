/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lal.h
 * Author: Pc
 *
 * Created on 17 January 2021, 10:15
 */

#ifndef LAL_H
#define LAL_H
class Vector;
class Matrix{
protected:
    bool empty;
    double *entries;
    int rows;
    int cols;
public:
    Matrix(double*,int,int);
    Matrix();
    void print();
    Matrix* operator+(Matrix&);
    Matrix* operator-(Matrix&);
    Matrix* operator*(Matrix&);
    Matrix* operator*(Vector&);
    int getRows();
    int getCols();
    bool operator==(Matrix&);
    Matrix* operator++(); // pre-inc
    Matrix* operator++(int); // pre-inc
    friend Matrix* transpose(Matrix&);
    friend void norm(Matrix&);
    double* getEntries();
    virtual ~Matrix();
};

class Vector: public Matrix{
private:
    double l2norm;
public:
    Vector(double*,int);
    Vector();
    double getl2norm();
    void print();
    double operator*(Vector&);
    ~Vector();
};

Matrix* transpose(Matrix&);
void norm(Matrix&);
Vector **CreateVectorArray(int,int);
void FillVectorArray(Vector** vectorArray, int m, int p);
Matrix* vectorArray2Matrix(Vector**,int,int);

#endif /* LAL_H */

