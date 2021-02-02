#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


const int rows = 5;
const int cols = 5;
int exeTime = 1;        // Record the number of times fillMatrix() is invoked in a single program execution 
                        // to create a unique seed for every srand() call.
void checkPassword(){
    string pWord;
    cout << "Please type in the password: ";
    cin >> pWord;
    int len = pWord.length();
    bool errors = false;
    if (len < 8){
        cout << "Password should be at least eight characters long!" << endl;
        errors = true;
    }
    /* There are 128 characters in the ASCII table, so make an int array of that size to record the
        number of times every character occur in the passowrd. */
    int arr[128] = {0};         
    bool hasNum = false;        // A flag to indicate if numbers are found in the password.           
    bool hasSpec = false;       // A flag to indicate if special characters are found in the passowrd.
    for (int i = 0; i < len; i++){
        int pASCII = int(pWord[i]);  // Convert every character in the password to its ASCII value, then increment the
        arr[pASCII]++;               // corresponding array entry.
    }
    for (int j = 0; j < 128; j++){
        if (arr[j] > 2){
            cout << "The character '" << char(j) << "' occurs more than two times!" << endl;
            errors = true;
        }
        if (arr[j] == 1){
            if (j >= 48 && j <= 57){hasNum = true;}                 // Number found.
            if (j == 42 || j == 35 || j == 36){hasSpec = true;}     // Special character found.
        }
    }
    if (hasNum == false){
        cout << "No number found in the password!" << endl;
        errors = true;
    }
    if (hasSpec == false){
        cout << "No special characters '*', '#' or '$' found in the password!" << endl;
        errors = true;
    }
    if (!errors){
        cout << "Password accepted!" << endl;
    }
}


void convertPhonetic(){
    string word;
    cout << "Please enter a word: ";
    cin >> word;
    int len = word.length();
    for (int i = 0; i < len; i++){
        char initial = word[i];
        if (int(initial) >= 97 && int(initial) <= 122){initial = char(int(initial) - 32);}  // Change all the initials to upper case.

        switch (initial){       // Match every initial with its corresponding word.
            case 'A':
                cout << "Alfa ";
                break;
            case 'B':
                cout << "Bravo ";
                break;
            case 'C':
                cout << "Charlie ";
                break;
            case 'D':
                cout << "Delta ";
                break;
            case 'E':
                cout << "Echo ";
                break;
            case 'F':
                cout << "Foxtrot ";
                break;
            case 'G':
                cout << "Golf ";
                break;
            case 'H':
                cout << "Hotel ";
                break;
            case 'I':
                cout << "India ";
                break;
            case 'J':
                cout << "Juliett ";
                break;
            case 'K':
                cout << "Kilo ";
                break;
            case 'L':
                cout << "Lima ";
                break;
            case 'M':
                cout << "Mike ";
                break;
            case 'N':
                cout << "November ";
                break;
            case 'O':
                cout << "Oscar ";
                break;
            case 'P':
                cout << "Papa ";
                break;
            case 'Q':
                cout << "Quebec ";
                break;
            case 'R':
                cout << "Romeo ";
                break;
            case 'S':
                cout << "Sierra ";
                break;
            case 'T':
                cout << "Tango ";
                break;
            case 'U':
                cout << "Uniform ";
                break;
            case 'V':
                cout << "Victor ";
                break;
            case 'W':
                cout << "Whiskey ";
                break;
            case 'X':
                cout << "X-ray ";
                break;
            case 'Y':
                cout << "Yankee ";
                break;
            case 'Z':
                cout << "Zulu ";
                break;
        }
    }
    cout << endl;
}


void fillMatrix(int matrix[rows][cols]){
    srand(time(NULL) * exeTime);        // Since time(NULL) only updates once in every second, multiplying it by the exeTime
    for (int i = 0; i < rows; i++){     // counter is neededassure that a unique seed is generated every time.
        for (int j = 0; j < cols; j++){
            matrix[i][j] = rand() % 26;
        }
    }
    exeTime++;      // Increment the counter.
}


void printMatrix(int matrix[rows][cols]){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols - 1; j++){
            cout << matrix[i][j] << "  |  ";
        }
        cout << matrix[i][cols - 1] << endl;
        cout << string(30, '-') << endl;
    }
    cout << endl;
}


void multiplyMatrices(int matrix_left[rows][cols], int matrix_right[rows][cols], int matrix_result[rows][cols]){
    static int row = 0;             // Indicate the row number of the enrty in the result that is being calculated.
    static int col = 0;             // Indicate the column number of the enrty in the result that is being calculated.
    static int pointer = 0;
    static bool reset = false;      // Record if an entry in the result has been reset to zero before assigning
    if (row >= rows){return;}       // value to it.
    if (col < cols){
        if (pointer < cols){
            if (!reset){                        // Since the result matrix is not initialized with all zero, 
                matrix_result[row][col] = 0;    // manually resetting the value is required.
                reset = true;
            }
            matrix_result[row][col] += matrix_left[row][pointer] * matrix_right[pointer][col];
            pointer++;
            multiplyMatrices(matrix_left, matrix_right, matrix_result);
        }
        reset = false;      // Move on to calculate the next entry in the same row, so reset the 
        pointer = 0;        // "enrty reset" flag.
        col++;
        multiplyMatrices(matrix_left, matrix_right, matrix_result);
    }
    reset = false;          // Move on to calculate the first entry in the next row, so reset the
    col = 0;                // "entry reset" flag and the "current column" indicator.
    row++;
    multiplyMatrices(matrix_left, matrix_right, matrix_result);
}


int main(){
    checkPassword();
    convertPhonetic();
    int matrix[rows][cols];
    int matrix2[rows][cols];
    int matrix_result[rows][cols];
    fillMatrix(matrix);
    fillMatrix(matrix2);
    printMatrix(matrix);
    multiplyMatrices(matrix, matrix2, matrix_result);
    printMatrix(matrix_result);
    return 0;
}