#include <iostream>
#include <fstream>
using namespace std;



void saveToFile(int** arr, int rows, int cols, ofstream& file) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << arr[i][j] << " ";
        }
        file << endl;
    }
}


void growRowFront(int**& arr, int& rows, int cols, int* newRow) {
    int** arr2 = new int* [rows + 1];
    arr2[0] = newRow;
    for (int i = 0; i < rows; i++) {
        arr2[i + 1] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    rows++;
}

void growRowEnd(int**& arr, int& rows, int cols, int* newRow) {
    int** arr2 = new int* [rows + 1];
    for (int i = 0; i < rows; i++) {
        arr2[i] = arr[i];
    }
    arr2[rows] = newRow;
    delete[] arr;
    arr = arr2;
    rows++;
}
void growRowAtPosition(int**& arr, int& rows, int cols, int pos, int* newRow) {
    if (pos < 0 || pos > rows) {
        cout << "Invalid position!\n";
        return;
    }
    int** arr2 = new int* [rows + 1];
    for (int i = 0; i < pos; i++) {
        arr2[i] = arr[i];
    }
    arr2[pos] = newRow;
    for (int i = pos; i < rows; i++) {
        arr2[i + 1] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    rows++;
}

// from front
void shrinkRowFront(int**& arr, int& rows) {
    
    delete[] arr[0];
    int** arr2 = new int* [rows - 1];
    for (int i = 1; i < rows; i++) {
        arr2[i - 1] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    rows--;
}


void shrinkRowEnd(int**& arr, int& rows) {
    
    delete[] arr[rows - 1];
    int** arr2 = new int* [rows - 1];
    for (int i = 0; i < rows - 1; i++) {
        arr2[i] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    rows--;
}

//  at specific position
void shrinkRowAtPosition(int**& arr, int& rows, int pos) {
    if (pos < 0 || pos >= rows) {
        cout << "Invalid position!\n";
        return;
    }
    delete[] arr[pos];
    int** arr2 = new int* [rows - 1];
    for (int i = 0; i < pos; i++) {
        arr2[i] = arr[i];
    }
    for (int i = pos + 1; i < rows; i++) {
        arr2[i - 1] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    rows--;
}

// Display array
void displaying(int** arr, int rows, int cols) {
    cout << "\nCurrent 2D Array:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows, cols;
    cout << "Enter number of rows and columns: ";
    cin >> rows >> cols;

    int** arr = new int* [rows];
    cout << "Enter " << rows << " rows with " << cols << " columns:\n";
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            cout << "Enter arr[" << i << "][" << j << "] :";
            cin >> arr[i][j];
        }
    }

    // Saving original array
    ofstream originalFile("original.txt");
    saveToFile(arr, rows, cols, originalFile);
    originalFile.close();

menu:
    int choice, pos;
    int* newRow;

    cout << "\n--- Menu ---\n";
    cout << "1) Add row at front\n";
    cout << "2) Add row at end\n";
    cout << "3) Add row at position\n";
    cout << "4) Remove row from front\n";
    cout << "5) Remove row from end\n";
    cout << "6) Remove row from position\n";
    cout << "0) Exit\nChoose: ";
    cin >> choice;

  switch (choice) {
    case 1: {
        newRow = new int[cols];
        cout << "Enter " << cols << " elements for new row:\n";
        for (int i = 0; i < cols; i++) {
            cin >> newRow[i];
        }
        growRowFront(arr, rows, cols, newRow);
        break;
    }

    case 2: {
        newRow = new int[cols];
        cout << "Enter " << cols << " elements for new row:\n";
        for (int i = 0; i < cols; i++) {
            cin >> newRow[i];
        }
        growRowEnd(arr, rows, cols, newRow);
        break;
    }

    case 3: {
        cout << "Enter position starting from 0: ";
        cin >> pos;
        newRow = new int[cols];
        cout << "Enter " << cols << " elements for new row:\n";
        for (int i = 0; i < cols; i++) {
            cin >> newRow[i];
        }
        growRowAtPosition(arr, rows, cols, pos, newRow);
        break;
    }

    case 4: {
        shrinkRowFront(arr, rows);
        break;
    }

    case 5: {
        shrinkRowEnd(arr, rows);
        break;
    }

    case 6: {
        cout << "Enter position starting from zero to remove row: ";
        cin >> pos;
        shrinkRowAtPosition(arr, rows, pos);
        break;
    }

    case 0: {
        cout << "Exiting the program!\n";
        ofstream finalFile("updated2D.txt");
        saveToFile(arr, rows, cols, finalFile);
        finalFile.close();
        for (int i = 0; i < rows; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        return 0;
    }

    default: {
        cout << "Invalid choice!\n";
    }
  }

    ofstream updatedFile("updated.txt");
    saveToFile(arr, rows, cols, updatedFile);
    updatedFile.close();

    displaying(arr, rows, cols);
    goto menu;
}
