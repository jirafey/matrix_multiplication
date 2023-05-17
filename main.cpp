#include <iostream>
#include "class.h"

void ask(matrix& C) {
    std::cout << "\n\nWould you like to transpose this matrix? 1/0\n";
    int choice;
    std::cin >> choice;
    while (choice < 0 || choice > 1 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Please enter a correct value\nTry entering it again: ";
        std::cin >> choice;
    }
    if (choice) {
        C.matrixTranspose();
        std::cout << "\nCt = \n";
        C.displayTransposed();
    }
}

void menu(matrix& A, matrix& B, matrix& C) {
    int subchoice = 0;
    int choice = 0;
    while (true) {
        system("cls");
        //INSTRUCTIONS
        std::cout << "Matrix operator\n";
        std::cout << "1 - Display matrices A and B\n";
        std::cout << "2 - Create matrix\n";
        std::cout << "3 - Delete matrix\n";
        std::cout << "4 - Edit matrix\n";
        std::cout << "5 - A * B\n";
        std::cout << "6 - Display transposed matrix\n";
        std::cout << "7 - Exit program\n";
        std::cout << "Select option: \n";
        std::cin >> choice;
        while (choice < 1 || choice > 7 || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "Please enter a correct value\nTry entering it again: ";
            std::cin >> choice;
        }
        system("cls");
        switch (choice) {
            case 1:
                std::cout << "A = \n";
                A.matrixPrint();
                std::cout << "\n\nB = \n";
                B.matrixPrint();
                break;
            case 2:
                std::cout << "Which matrix would you like to construct/overwrite?\n";
                std::cout << "1 - A\n";
                std::cout << "2 - B\n";
                std::cin >> subchoice;
                while (subchoice < 1 || subchoice > 2 || std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                    std::cout << "Please enter a correct value\nTry entering it again: ";
                    std::cin >> subchoice;
                }
                if (subchoice == 1) {
                    A.matrixCreate();
                } else {
                    B.matrixCreate();
                }
                system("cls");
                std::cout << "Matrix has been created successfully\n";
                break;

            case 3:
                std::cout << "Which matrix would you like to delete?\n";
                std::cout << "1 - A\n";
                std::cout << "2 - B\n";
                std::cin >> subchoice;
                while (subchoice < 1 || subchoice > 2 || std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                    std::cout << "Please enter a correct value\nTry entering it again: ";
                    std::cin >> subchoice;
                }
                if (subchoice == 1) {
                    if (A.exist()) {
                        A.matrixDelete();
                        break;
                    } else {
                        std::cout << "Matrix A doesn't exist!";
                        break;
                    }
                } else if (B.exist()) {
                    B.matrixDelete();
                    break;
                }
                std::cout << "Matrix B doesn't exist!";
                break;
            case 4:
                std::cout << "Which matrix would you like to edit?\n";
                std::cout << "1 - A\n";
                std::cout << "2 - B\n";
                std::cin >> subchoice;
                while (subchoice < 1 || subchoice > 2 || std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                    std::cout << "Please enter a correct value\nTry entering it again: ";
                    std::cin >> subchoice;
                }
                if (subchoice == 1) {
                    if (A.exist()) {
                        A.matrixEdit();
                        break;
                    }
                    std::cout << "Matrix A doesn't exist!\n";
                    break;
                } else if (B.exist()) {
                    B.matrixEdit();
                    break;
                }
                std::cout << "Matrix B doesn't exist!\n";
                break;
            case 5:
                if (A.exist() && B.exist()) {
                    if (A.access_matrix()[0].size() == B.access_matrix().size()) {
                        C.setValue(A * B);
                        std::cout << "A * B = \n";
                        C.matrixPrint();
                        ask(C);
                    } else {
                        std::cout << "\nMatrix dimensions are incorrect!\n";
                    }
                } else {
                    std::cout << "At least one of the required matrices doesn't exist!\n";
                }
                break;
            case 6:
                std::cout << "Which matrix would you like to transpose?\n";
                std::cout << "1 - A\n";
                std::cout << "2 - B\n";
                std::cin >> subchoice;
                while (subchoice < 1 || subchoice > 2 || std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                    std::cout << "Please enter a correct value\nTry entering it again: ";
                    std::cin >> subchoice;
                }
                if (subchoice == 1) {
                    if (A.exist()) {
                        std::cout << "At = \n";
                        A.displayTransposed();
                    } else {
                        std::cout << "Matrix A doesn't exist\n";
                    }
                } else if (subchoice == 2) {
                    if (B.exist()) {
                        std::cout << "Bt = \n";
                        B.displayTransposed();
                    } else {
                        std::cout << "Matrix B doesn't exist\n";
                    }
                }
                break;
            case 7:
                return;
            default:
                std::cout << "Something went wrong :P";
        }
        system("PAUSE");
    }
}

int main() {
    matrix A, B, C;
    menu(A, B, C);
    return 0;
}
