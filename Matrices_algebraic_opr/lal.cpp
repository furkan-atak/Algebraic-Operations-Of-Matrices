/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "lal.h"
#include <typeinfo>
#include <future>


using namespace std;

// Transpose of given matrix (also works for vectors) not belong any of them but friend func. of matrix class
Matrix* transpose(Matrix&mat) {

    if ((typeid (mat).name()) == typeid (Matrix).name()) {
        double *entries = (double*) calloc(sizeof (double), mat.cols * mat.rows);
        for (int i = 0; i < mat.rows; i++) {
            for (int j = 0; j < mat.cols; j++) {
                entries[j * mat.rows + i] = mat.entries[i * mat.cols + j];
            }
        }
        return new Matrix(entries, mat.cols, mat.rows);
    } else if ((typeid (mat).name()) == typeid (Vector).name()) {
        double *entries = (double*) calloc(sizeof (double), mat.cols * mat.rows);
       /* for (int i = 0; i < mat.rows * mat.cols; i++) {
            entries[i] = mat.entries[mat.rows * mat.cols - i - 1];
        }*/
        entries = mat.entries;
        return new Matrix(entries,1,mat.rows);
    } else {
        cout << "Be sure the input is valid for the function";
        return new Matrix();
    }
}

// Norm of the given matrix not a class function but a friend function of matrix class
void norm(Matrix& mat){
    if (typeid(mat).name() == typeid(Vector).name()) {
        Vector *v = dynamic_cast<Vector*>(&mat);
		cout << v->getl2norm();
	} else {
		double l2Norm = 0.0;
		for (int i = 0; i < mat.rows * mat.cols; i++) {
			l2Norm += pow(mat.entries[i], 2);
		}
		l2Norm = sqrt(l2Norm);
		cout << l2Norm << endl;
	}
}
//Empty constructor for matrix
Matrix::Matrix() {
    this->empty = true;
}

// Constructor for matrix
Matrix::Matrix(double* entries, int rows, int cols) {
    this->entries = entries;
    this->rows = rows;
    this->cols = cols;
    this->empty = false;

}

// print function of matrix
void Matrix::print() {
    cout << "\n";
    if (!this->empty) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                cout << this->entries[i * cols + j] << " ";
            }
            cout << endl;
        }
    }
}

// Deconstructor for matrix
Matrix::~Matrix() {
    if (this->entries != NULL) {
        delete this->entries;
    }

}

// Sum operator overloading for matrix (also works for vectors 'cuz vectors are also matrices)
Matrix* Matrix::operator+(Matrix &mat) {
    if (mat.cols == this->cols && mat.rows == this->rows) {
        double *entries = (double*) calloc(sizeof (double), mat.cols * mat.rows);
        for (int i = 0; i < mat.rows; i++) {
            for (int j = 0; j < mat.cols; j++) {
                entries[i * cols + j] = this->entries[i * cols + j] + mat.entries[i * cols + j];
            }
        }
        return new Matrix(entries, mat.rows, mat.cols);
    } else {
        cout << "Those Matrices Can Not Sum";
        return new Matrix();
    }
}

// Subtraction operator overloading
Matrix* Matrix::operator-(Matrix &mat) {
    if (mat.cols == this->cols && mat.rows == this->rows) {
        double *entries = (double*) calloc(sizeof (double), mat.cols * mat.rows);
        for (int i = 0; i < mat.rows; i++) {
            for (int j = 0; j < mat.cols; j++) {
                entries[i * cols + j] = this->entries[i * cols + j] - mat.entries[i * cols + j];
            }
        }
        return new Matrix(entries, mat.rows, mat.cols);
    } else {
        cout << "Those Matrices Can Not Be Subtracted";
        return new Matrix();
    }
}

// Multiplication operator overloading for matrices
Matrix* Matrix::operator*(Matrix& mat) {
    if (this->cols == mat.rows) {
        double *entries = (double*) calloc(sizeof (double), this->rows * mat.cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < mat.cols; j++) {
                for (int k = 0; k < this->cols; k++) {
                    entries[i * mat.cols + j] += this->entries[i * this->cols + k] * mat.entries[k * mat.cols + j];
                }

            }
        }
        return new Matrix(entries, this->rows, mat.cols);
    } else {
        cout << "Those matrices Can Not Be Multiplied";
        return new Matrix();
    }
}

// Multiplication operator overloading for "matrix*vector".
Matrix* Matrix::operator*(Vector& vec) {
    if (this->cols == vec.rows) {
        double *entries = (double*) calloc(sizeof (double), this->rows * vec.cols);
        for (int i = 0; i < this->rows; i++) {
            double sum = 0;
            for (int j = 0; j < this->cols; j++) {
                sum += this->entries[i * cols + j] * vec.entries[j];
            }
            entries[i] = sum;
        }
        return new Matrix(entries, vec.rows, 1);
    } else {
        cout << "Those matrices Can Not Be Multiplied";
        return new Matrix();
    }
}

// Equality comparison operator overloading 
bool Matrix::operator==(Matrix& mat) {
    bool isEqual = true;
    if (mat.cols == this->cols && mat.rows == this->rows) {
        for (int i = 0; i < mat.rows * mat.cols; i++) {
            if (this->entries[i] != mat.entries[i]) {
                isEqual = false;
                break;
            }
        }
        return isEqual;
    } else {
        cout << "Those Matrices Can Not Compare";
        return false;
    }
}

// Pre-Increment operator overloading
Matrix* Matrix::operator++() {
    double *newEntries = (double*) calloc(sizeof (double), this->cols * this->rows);
    for (int i = 0; i < this->rows * this->cols; i++) {
        newEntries[i] = ++this->entries[i];
    }
    return new Matrix(newEntries, this->rows, this->cols);
}

// Post-Increment operator overloading
Matrix* Matrix::operator++(int) {
    double *newEntries = (double*) calloc(sizeof (double), this->cols * this->rows);
    for (int i = 0; i < this->rows * this->cols; i++) {
        newEntries[i] = this->entries[i]++;
    }
    return new Matrix(newEntries, this->rows, this->cols);
}

int Matrix::getRows() {
    return this->rows;
}

int Matrix::getCols() {
    return this->cols;
}
double* Matrix::getEntries(){
    return this->entries;
}

// A function to create array of vectors
Vector **CreateVectorArray(int m,int p){
	Vector **vectorArray = (Vector**) calloc(m, sizeof(Vector*));  
	for (int i = 0; i < m; i++) {           
		vectorArray[i] = (Vector*) calloc(p, sizeof(Vector));
	}
	return vectorArray;
}

// A function for filling given vector array with random values
void FillVectorArray(Vector** vectorArray, int m, int p){
	for(int i = 0; i < m; i++){
		double *entries = (double*) calloc(p, sizeof(double));
		for(int j = 0; j < p; j++){
			entries[j] = (double) rand() / (double) (RAND_MAX) + 1.0; 
		}
		Vector *v = new Vector(entries,p);
		vectorArray[i] = v;
	}
}

// A function to convert given function array into a matrix
Matrix* vectorArray2Matrix(Vector** vectorArray, int m, int p){
	double* entries = (double*)calloc(sizeof(double),m*p);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < p; j++){
			entries[j*m+i] = vectorArray[i]->getEntries()[j];
		}
	}
	Matrix *theMatrix = new Matrix(entries, p, m);
	return theMatrix;
}

//Vector empty constructor
Vector::Vector() {
    this->empty = true;
}

// Vector Constructor
Vector::Vector(double* entries, int rows) : Matrix(entries, rows, 1) {
    double theNorm = 0;
    for (int i = 0; i < rows; i++) {
        theNorm += pow(*(entries + i), 2);
    }
    this->l2norm = sqrt(theNorm);
    this->empty = false;
}

// Vector Deconstructor
Vector::~Vector() {
    if (this->entries != NULL) {
        delete this->entries;
    }
}

double Vector::getl2norm() {
    return this->l2norm;
}

void Vector::print() {
    cout << "\n";
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            cout << this->entries[i*cols+j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

double Vector::operator*(Vector& vec) {
    if (this->rows == vec.rows) {
        double sum = 0;
        for (int i = 0; i < this->rows; i++) {
            sum += this->entries[i] * vec.entries[i];
        }
        return sum;
    } else {
        cout << "Vector sizes should be equal to be multiplied";
        return 0;
    }
}




