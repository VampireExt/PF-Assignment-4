#include <iostream>
#include <fstream>
using namespace std;

void saveToFile(int arr[], int size, ofstream& file) {
    for (int i = 0; i < size; i++) {
        file << arr[i] << " ";
    }
    file << endl;
}

void growFront(int*& arr, int& size, int value) {
    int* arr2 = new int[size + 1];
    arr2[0] = value;
    for (int i = 0; i < size; i++) {
        arr2[i + 1] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    size++;
}

void growEnd(int*& arr, int& size, int value) {
    int* arr2 = new int[size + 1];
    for (int i = 0; i < size; i++) {
        arr2[i] = arr[i];
    }
    arr2[size] = value;
    delete[] arr;
    arr = arr2;
    size++;
}

void growAtPosition(int*& arr, int& size, int pos, int value) {
    if (pos < 0 || pos > size) {
        cout << "Invalid position!\n";
        return;
    }
    int* arr2 = new int[size + 1];
    for (int i = 0; i < pos; i++) {
        arr2[i] = arr[i];
    }
    arr2[pos] = value;
    for (int i = pos; i < size; i++) {
        arr2[i + 1] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    size++;
}

void shrinkFront(int*& arr, int& size) {
    
    int* arr2 = new int[size - 1];
    for (int i = 1; i < size; i++) {
        arr2[i - 1] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    size--;
}

void shrinkEnd(int*& arr, int& size) {
    
    int* arr2 = new int[size - 1];
    for (int i = 0; i < size - 1; i++) {
        arr2[i] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    size--;
}

void shrinkAtPosition(int*& arr, int& size, int pos) {
    if (pos < 0 || pos >= size) {
        cout << "Invalid position!\n";
        return;
    }
    int* arr2 = new int[size - 1];
    for (int i = 0; i < pos; i++) {
        arr2[i] = arr[i];
    }
    for (int i = pos + 1; i < size; i++) {
        arr2[i - 1] = arr[i];
    }
    delete[] arr;
    arr = arr2;
    size--;
}

void displayArray(int arr[], int size) {
    cout << "Current Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    int* arr = new int[n];

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    ofstream originalFile("original.txt");
    saveToFile(arr, n, originalFile);
    originalFile.close();

Menu:
    int choice, value, pos;
    cout << "\n--- Menu ---\n";
    cout << "1. Grow from Front\n2. Grow from End\n3. Grow at Position\n";
    cout << "4. Shrink from Front\n5. Shrink from End\n6. Shrink at Position\n";
    cout << "0. Exit\nChoose: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        cout << "Enter value to insert at front: ";
        cin >> value;
        growFront(arr, n, value);
        break;
    }

    case 2: {
        cout << "Enter value to insert at end: ";
        cin >> value;
        growEnd(arr, n, value);
        break;
    }

    case 3: {
        cout << "Enter position from 0 to " << n - 1 << " to add : ";
        cin >> pos >> value;
        growAtPosition(arr, n, pos, value);
        break;
    }

    case 4: {
        shrinkFront(arr, n);
        break;
    }

    case 5: {
        shrinkEnd(arr, n);
        break;
    }

    case 6: {
        cout << "Enter position from 0 to " << n - 1 << " to remove : ";
        cin >> pos;
        shrinkAtPosition(arr, n, pos);
        break;
    }

    case 0: {
        cout << "Exiting the Program!\n";
        ofstream finalFile("updated.txt");
        saveToFile(arr, n, finalFile);
        finalFile.close();
        delete[] arr;
        return 0;
    }

    default: {
        cout << "Invalid option.\n";
    }
    }

    ofstream updateFile("updated.txt");
    saveToFile(arr, n, updateFile);
    updateFile.close();

    displayArray(arr, n);
    goto Menu;
}
