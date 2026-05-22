#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

string readFromInput(istream&);
string getTextFromKeyboard();
string getTextFromFile();
string encryptCaesar(const string& text, int key);
string decryptCaesar(const string& text, int key);
bool getOutputAndSave(const string& result);

int main() {
    int choice, operationChoice, key;

    cout << "Choose if you want to read text from the keyboard [1] or from a file [2]:" << endl;
    cin >> choice;
    cin.ignore();

    string text;
    if (choice == 1) {
        text = getTextFromKeyboard();
    } else if (choice == 2) {
        text = getTextFromFile();
    }
    if (text.empty()) {
        cout << "Input text is empty.\n";
        cout << "Closing the program..." << endl;
        return 1;
    }

    cout << "Choose an operation: encryption [1] or decryption [2]: ";
    cin.clear();
    while (true) {
        cin >> operationChoice;
        if (operationChoice == 1 || operationChoice == 2) break;
        cout << "Invalid choice. Enter 1 for encryption or 2 for decryption: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter the key: ";
    while (true) {
        if (!(cin >> key)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Please enter a number: " << endl;
        } else {
            break;
        }
    }

    string result;
    if (operationChoice == 1) {
        result = encryptCaesar(text, key);
        cout << "Encrypted text:\n" << result << endl;
    } else if (operationChoice == 2) {
        result = decryptCaesar(text, key);
        cout << "Decrypted text:\n" << result << endl;
    }

    cout << "Final result:\n" << result << endl;
        if (choice == 2) {
            if (getOutputAndSave(result)) {
                cout << "Result successfully saved." << endl;
            } else {
                cout << "Failed to save the result." << endl;
            }
        }
    return 0;
    }

string readFromInput(istream& input) {
    string text, line;
    while(getline(input, line)){
        text += line;
        text += "\n";
    }
    return text;
}
string getTextFromKeyboard() {
    cout << "Enter some text (press Ctrl+Z to finish):\n";
    return readFromInput(cin);
}
string getTextFromFile() {
    string text;

    string iFilename;
    cout << "Enter name of input file:\n";
    if (!getline(cin, iFilename)) {
        cerr << "Error: Unable to read file name." << endl;
        return "";
    }

    ifstream iFilehandle(iFilename);
    if (!iFilehandle) {
        cout << "Could not open input file " << iFilename << "\n";
        cout << "Attempting to read from standard input instead...\n";
        cout << "Enter some text now:\n";
        text = readFromInput(cin);
    }
    else {
        text = readFromInput(iFilehandle);
    }

    return text;
}

string encryptCaesar(const string& text, int key) {
    string result;
    key = key  % 26;
    for (const char character : text) {
        if (character >= 'A' && character <= 'Z') {
            result += (character - 'A' + key + 26) % 26 + 'A';
        } else if (character >= 'a' && character <= 'z') {
            result += (character - 'a' + key + 26) % 26 + 'a';
        } else {
            result += character;
        }
    }
    return result;
}
string decryptCaesar(const string& text, int key) {
        key = -key % 26;
        if (key < 0) key += 26;
        return encryptCaesar(text, key);
    }
bool getOutputAndSave(const string& result) {string outputFilename;
    cout << "Enter output file name to save the result: ";
    cin.ignore();
    getline(cin, outputFilename);

    ofstream outfhandle(outputFilename);
    if (!outfhandle) {
        cout << "Failed to open \"" << outputFilename << "\" for writing. Exiting program." << endl;
        return false;
    }
    outfhandle << result;
    return true;
}
