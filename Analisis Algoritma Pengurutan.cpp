#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bubbleSort(vector<int>& arr);
void insertionSort(vector<int>& arr);
void selectionSort(vector<int>& arr);
void mergeSort(vector<int>& arr, int left, int right);
void quickSort(vector<int>& arr, int low, int high);

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

void measureTime(void(*sortFunc)(vector<int>&), vector<int>& arr, const string& sortName) {
    vector<int> arrCopy = arr;

    auto start = chrono::high_resolution_clock::now();
    sortFunc(arrCopy);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start;
    cout << sortName << ": " << duration.count() << " microseconds" << endl;
}

void measureTimeMerge(void(*sortFunc)(vector<int>&, int, int), vector<int>& arr, const string& sortName) {
    vector<int> arrCopy = arr;

    auto start = chrono::high_resolution_clock::now();
    sortFunc(arrCopy, 0, arrCopy.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> duration = end - start;
    cout << sortName << ": " << duration.count() << " microseconds" << endl;
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 10000};

    for (int size : sizes) {
        vector<int> arr(size);
        srand(time(NULL));
        for (int& num : arr) {
            num = rand();
        }

        cout << "Sorting array of size " << size << " with different algorithms:" << endl;

        measureTime(bubbleSort, arr, "Bubble Sort");
        measureTime(insertionSort, arr, "Insertion Sort");
        measureTime(selectionSort, arr, "Selection Sort");
        measureTimeMerge(mergeSort, arr, "Merge Sort");
        measureTimeMerge(quickSort, arr, "Quick Sort");

        cout << endl;
    }

    return 0;
}
