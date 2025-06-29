#include <iostream>
#include <fstream>
using namespace std;


void saveJaggedToFile(int** arr, int* colSizes, int rows, ofstream& file) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colSizes[i]; j++) {
            file << arr[i][j] << " ";
        }
        file << endl;
    }
}


void growJaggedFront(int**& arr, int*& colSizes, int& rows, int* newRow, int newCols) {
    int** arr2 = new int* [rows + 1];
    int* cols2 = new int[rows + 1];

    arr2[0] = newRow;
    cols2[0] = newCols;

    for (int i = 0; i < rows; i++) {
        arr2[i + 1] = arr[i];
        cols2[i + 1] = colSizes[i];
    }

    delete[] arr;
    delete[] colSizes;

    arr = arr2;
    colSizes = cols2;
    rows++;
}


void growJaggedEnd(int**& arr, int*& colSizes, int& rows, int* newRow, int newCols) {
    int** arr2 = new int* [rows + 1];
    int* cols2 = new int[rows + 1];

    for (int i = 0; i < rows; i++) {
        arr2[i] = arr[i];
        cols2[i] = colSizes[i];
    }

    arr2[rows] = newRow;
    cols2[rows] = newCols;

    delete[] arr;
    delete[] colSizes;

    arr = arr2;
    colSizes = cols2;
    rows++;
}

void growJaggedAtPosition(int**& arr, int*& colSizes, int& rows, int pos, int* newRow, int newCols) {
    if (pos < 0 || pos > rows) {
        cout << "Invalid position!\n";
        return;
    }

    int** arr2 = new int* [rows + 1];
    int* cols2 = new int[rows + 1];

    for (int i = 0; i < pos; i++) {
        arr2[i] = arr[i];
        cols2[i] = colSizes[i];
    }

    arr2[pos] = newRow;
    cols2[pos] = newCols;

    for (int i = pos; i < rows; i++) {
        arr2[i + 1] = arr[i];
        cols2[i + 1] = colSizes[i];
    }

    delete[] arr;
    delete[] colSizes;

    arr = arr2;
    colSizes = cols2;
    rows++;
}


void shrinkJaggedFront(int**& arr, int*& colSizes, int& rows) {
    if (rows == 0) {
        return;
    }

    delete[] arr[0];

    int** arr2 = new int* [rows - 1];
    int* cols2 = new int[rows - 1];

    for (int i = 1; i < rows; i++) {
        arr2[i - 1] = arr[i];
        cols2[i - 1] = colSizes[i];
    }

    delete[] arr;
    delete[] colSizes;

    arr = arr2;
    colSizes = cols2;
    rows--;
}


void shrinkJaggedEnd(int**& arr, int*& colSizes, int& rows) {
    if (rows == 0) {
        return;
    }

    delete[] arr[rows - 1];

    int** arr2 = new int* [rows - 1];
    int* cols2 = new int[rows - 1];

    for (int i = 0; i < rows - 1; i++) {
        arr2[i] = arr[i];
        cols2[i] = colSizes[i];
    }

    delete[] arr;
    delete[] colSizes;

    arr = arr2;
    colSizes = cols2;
    rows--;
}


void shrinkJaggedAtPosition(int**& arr, int*& colSizes, int& rows, int pos) {
    if (pos < 0 || pos >= rows) {
        cout << "Invalid position!\n";
        return;
    }

    delete[] arr[pos];

    int** arr2 = new int* [rows - 1];
    int* cols2 = new int[rows - 1];

    for (int i = 0; i < pos; i++) {
        arr2[i] = arr[i];
        cols2[i] = colSizes[i];
    }

    for (int i = pos + 1; i < rows; i++) {
        arr2[i - 1] = arr[i];
        cols2[i - 1] = colSizes[i];
    }

    delete[] arr;
    delete[] colSizes;

    arr = arr2;
    colSizes = cols2;
    rows--;
}


void displayJagged(int** arr, int* colSizes, int rows) {
    cout << "\nCurrent Jagged Array:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colSizes[i]; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    int rows;
    cout << "Enter number of rows in jagged array: ";
    cin >> rows;

    int** arr = new int* [rows];
    int* colSizes = new int[rows];

   
    for (int i = 0; i < rows; i++) {
        cout << "Enter number of elements in row " << i << ": ";
        cin >> colSizes[i];
    }

    for (int i = 0; i < rows; i++) {
        arr[i] = new int[colSizes[i]];
    }

    for (int i = 0; i < rows; i++) {
        cout << "Enter " << colSizes[i] << " elements for row " << i << ":\n";
        for (int j = 0; j < colSizes[i]; j++) {
            cin >> arr[i][j];
        }
    }

    ofstream originalFile("originalJagged.txt");
    saveJaggedToFile(arr, colSizes, rows, originalFile);
    originalFile.close();

Menu:
    int choice, newCols, pos;
    int* newRow;

    cout << "\n--- Menu ---\n";
    cout << "1. Add row at front\n";
    cout << "2. Add row at end\n";
    cout << "3. Add row at position\n";
    cout << "4. Remove row from front\n";
    cout << "5. Remove row from end\n";
    cout << "6. Remove row at position\n";
    cout << "0. Exit\nChoose: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        cout << "Enter number of elements for new row: ";
        cin >> newCols;
        newRow = new int[newCols];
        cout << "Enter elements:\n";
        for (int i = 0; i < newCols; i++) {
            cin >> newRow[i];
        }
        growJaggedFront(arr, colSizes, rows, newRow, newCols);
        break;
    }

    case 2: {
        cout << "Enter number of elements for new row: ";
        cin >> newCols;
        newRow = new int[newCols];
        cout << "Enter elements:\n";
        for (int i = 0; i < newCols; i++) {
            cin >> newRow[i];
        }
        growJaggedEnd(arr, colSizes, rows, newRow, newCols);
        break;
    }

    case 3: {
        cout << "Enter position to insert new row (0 to " << rows << "): ";
        cin >> pos;
        cout << "Enter number of elements for new row: ";
        cin >> newCols;
        newRow = new int[newCols];
        cout << "Enter elements:\n";
        for (int i = 0; i < newCols; i++) {
            cin >> newRow[i];
        }
        growJaggedAtPosition(arr, colSizes, rows, pos, newRow, newCols);
        break;
    }

    case 4: {
        shrinkJaggedFront(arr, colSizes, rows);
        break;
    }

    case 5: {
        shrinkJaggedEnd(arr, colSizes, rows);
        break;
    }

    case 6: {
        cout << "Enter position to remove row (0 to " << rows - 1 << "): ";
        cin >> pos;
        shrinkJaggedAtPosition(arr, colSizes, rows, pos);
        break;
    }

    case 0: {
        cout << "Exiting the program! \n";
        ofstream finalFile("updatedJagged.txt");
        saveJaggedToFile(arr, colSizes, rows, finalFile);
        finalFile.close();
        for (int i = 0; i < rows; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        delete[] colSizes;
        return 0;
    }

    default: {
        cout << "Invalid option!\n";
    }
    }

    ofstream updatedFile("updatedJagged.txt");
    saveJaggedToFile(arr, colSizes, rows, updatedFile);
    updatedFile.close();

    displayJagged(arr, colSizes, rows);
    goto Menu;
}
