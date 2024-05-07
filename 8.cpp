#include <iostream>
#include <vector>

using namespace std;

class HashTable {
private:
    int size;
    vector<int> keys;
    vector<int> values;
    vector<bool> flag;

public:
    HashTable(int size) {
        this->size = size;
        keys.resize(size, -1);
        values.resize(size);
        flag.resize(size, false);
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key, int value) {
        int index = hashFunction(key);
        while (flag[index]) {
            index = (index + 1) % size;
        }

        keys[index] = key;
        values[index] = value;
        flag[index] = true;
    }

    int search(int key) {
        int index = hashFunction(key);
        while (flag[index] && keys[index] != key) {
            index = (index + 1) % size;
        }

        if (flag[index] && keys[index] == key) {
            return values[index];
        } else {
            return -1; 
        }
    }

    void display() {
        for (int i = 0; i < size; i++) {
            if (flag[i]) {
                cout << "Key: " << keys[i] << ", Value: " << values[i] << endl;
            } else {
                cout << "Slot " << i << ": Empty" << endl;
            }
        }
    }
};

int main() {
    int size;
    cout << "Enter the size of the hash table: ";
    cin >> size;
    HashTable ht(size);

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Display" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        int key, value, searchKey, result; // Declare variables here

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                cout << "Enter value to insert: ";
                cin >> value;
                ht.insert(key, value);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> searchKey;
                result = ht.search(searchKey); // Initialize result here
                if (result != -1) {
                    cout << "Value found: " << result << endl;
                } else {
                    cout << "Value not found." << endl;
                }
                break;
            case 3:
                ht.display();
                break;
            case 4:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
