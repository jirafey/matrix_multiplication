#include "class.h"
#include <limits>

// Method to create a matrix. It prompts the user to enter the dimensions (rows and columns)
// and values of each element. Input is validated to ensure it's correct. The method also
// calculates the transposed matrix immediately after creation.
void matrix::matrixCreate() {
    int rows = 0, columns = 0;
    std::cout << "Input dimensions for matrix\n";
    std::cout << "Number of rows: ";
    std::cin >> rows;
    while (rows < 1 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Please enter a correct value. Try entering the number of rows again: ";
        std::cin >> rows;
    }
    std::cout << "Number of columns: ";
    std::cin >> columns;
    while (columns < 1 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Please enter a correct value. Try entering the number of columns again: ";
        std::cin >> columns;
    }
    std::vector<std::vector<int>> buffer(rows, std::vector<int>(columns));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            do {
                std::cin.clear();
                std::cin.ignore(256, '\n');
                std::cout << "[" << i << "][" << j << "] = ";
                std::cin >> buffer[i][j];
            } while (std::cin.fail());
        }
    }
    matrix::matrixName = buffer;
    matrix::matrixTranspose();
    matrix::exists = 1;
}

// Method to delete a matrix. It clears the current and transposed matrix data and sets
// the "exists" flag to 0 (false), indicating that the matrix doesn't exist.
void matrix::matrixDelete() {
    matrix::matrixName.clear();
    matrix::matrixTransposed.clear();
    matrix::exists = 0;
    std::cout << "Matrix has been deleted successfully!\n";
}

// Method to edit a specific element in the matrix. The user is prompted to enter the row
// and column of the element they want to edit, and then the new value. Input is validated
// to ensure it's correct. The transposed matrix is updated after the edit.
void matrix::matrixEdit() {
    if (matrix::exists == 1) {
        system("cls");
        matrix::matrixPrint();
        int r, c;
        std::cout << "Which element would you like to edit?\n";
        std::cout << "Row: ";
        std::cin >> r;
// segmentation error if size is not diminished by 1
        while (r < 0 || std::cin.fail() || r > matrix::matrixName.size() - 1) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "Please enter a correct value. Try entering the row number again: ";
            std::cin >> r;
        }
        std::cout << "Column: ";
        std::cin >> c;
// segmentation error if size is not diminished by 1
        while (c < 0 || std::cin.fail() || c > matrix::matrixName[0].size() - 1) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "Please enter a correct value. Try entering the column number again: ";
            std::cin >> c;
        }
        std::cout << "Now enter the new value for [" << r << "][" << c << "] = ";
        std::cin >> matrix::matrixName[r][c];
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "Please enter a correct value. Try entering it again: ";
            std::cin >> matrix::matrixName[r][c];
        }
        matrix::matrixTranspose();
    } else {
        std::cout << "Matrix doesn't exist!\n";
    }
}

// Method to print the matrix to the console. If the matrix doesn't exist, it outputs a
// message to that effect.
void matrix::matrixPrint() {
    if (matrix::exists == 1) {
        for (size_t i = 0;        i < matrix::matrixName.size(); i++) {
            for (size_t j = 0; j < matrix::matrixName[0].size(); j++) {
                if (matrix::matrixName[i][j] < 0)
                    std::cout << matrix::matrixName[i][j] << " ";
                else
                    std::cout << " " << matrix::matrixName[i][j] << " ";
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "Matrix doesn't exist!\n";
    }
}

// Method to display the transposed matrix by first ensuring the transposed matrix is up to date,
// then iterating through and printing each element.
void matrix::displayTransposed() {
    matrix::matrixTranspose();
    for (size_t i = 0; i < matrix::matrixTransposed.size(); i++) {
        for (size_t j = 0; j < matrix::matrixTransposed[0].size(); j++) {
            std::cout << matrix::matrixTransposed[i][j] << " ";
        }
        std::cout << "\n";
    }
}
// Method to check if the matrix exists. It returns the "exists" flag.
bool matrix::exist() {
    return matrix::exists;
}

// Overloaded multiplication operator to multiply two matrices together. It checks that both
// matrices exist and are compatible for multiplication. If they are, it multiplies them and
// returns the result. If they aren't, it outputs an error message and terminates the program.
std::vector<std::vector<int>> operator *(matrix A, matrix B) {
    if (A.exist() == 1 && B.exist() == 1) {
        if (A.access_matrix().size() > 0 && B.access_matrix().size() > 0) {
            std::vector<std::vector<int>> buffer(A.access_matrix().size(), std::vector<int>(B.access_matrix()[0].size()));
            for (int i = 0; i < buffer.size(); i++) {
                for (int j = 0; j < buffer[0].size(); j++) {
                    for (int n = 0; n < B.access_matrix().size(); n++) {
                        buffer[i][j] += A.access_matrix()[i][n] * B.access_matrix()[n][j];
                    }
                }
            }
            return buffer;
        }
    }
    std::cout << "Incorrect matrix dimensions!\n";
    exit(1);
}

// Method to access the matrix data. If the matrix exists, it returns the matrix data. If the
// matrix doesn't exist, it outputs an error message and terminates the program.
std::vector<std::vector<int>> matrix::access_matrix() {
    if (matrix::exists == 1)
        return matrixName;
    else {
        std::cout << "Matrix empty!\n";
        exit(1);
    }
}

// Method to set the value of the matrix. It takes a 2D vector as input and assigns it to
// the matrix data, then sets the "exists" flag to 1 (true).
void matrix::setValue(std::vector<std::vector<int>> buffer) {
    matrix::exists = 1;
    matrix::matrixName = buffer;
}

// Method to calculate and store the transposed matrix. It creates a new 2D vector with the
// dimensions of the transposed matrix, then fills it with the transposed values.
void matrix::matrixTranspose() {
    std::vector<std::vector<int>> buffer(matrix::matrixName[0].size(), std::vector<int>(matrix::matrixName.size()));
    for (int i = 0; i < matrix::matrixTransposed.size(); i++) {
        for (int j = 0; j < matrix::matrixTransposed[0].size(); j++) {
            buffer[i][j] = matrixName[j][i];
        }
    }
    matrix::matrixTransposed = buffer;
}




