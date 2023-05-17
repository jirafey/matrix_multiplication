#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <vector>

class matrix {
public:

    void matrixCreate();
    void setValue(std::vector<std::vector<int>> buffer);
    void matrixTranspose();
    void matrixEdit();
    bool exist();
    void matrixPrint();
    void displayTransposed();
    void matrixDelete();

    std::vector<std::vector<int>> access_matrix();
    friend std::vector<std::vector<int>> operator *(matrix A, matrix B);

private:
    std::vector<std::vector<int>> matrixName;
    std::vector<std::vector<int>> matrixTransposed;
    bool exists = false;
};

std::vector<std::vector<int>> operator *(matrix A, matrix B);

#endif
