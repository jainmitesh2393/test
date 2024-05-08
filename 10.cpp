#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Define the structure of a record
struct Record {
    int id;
    string name;
    string email;
};

class Database {
private:
    ofstream file;
    ifstream readFile;
    const string filename = "database.txt";

public:
    Database() {
        // Open the file in append mode to create it if it doesn't exist
        file.open(filename, ios::app);
        file.close();
    }

    ~Database() {
        file.close();
    }

    bool isIdExists(int id) {
        readFile.open(filename);
        string line;
        while (getline(readFile, line)) {
            stringstream ss(line);
            Record record;
            ss >> record.id >> record.name >> record.email;
            if (record.id == id) {
                readFile.close();
                return true;
            }
        }
        readFile.close();
        return false;
    }

    void createDatabase() {
        Record record;
        cout << "Enter record ID, name, and email (separated by spaces):" << endl;
        cin >> record.id >> record.name >> record.email;

        if (isIdExists(record.id)) {
            cout << "Data with given ID already exists." << endl;
            return;
        }

        file.open(filename, ios::app);
        file << record.id << " " << record.name << " " << record.email << endl;
        file.close();

        cout << "Record added to the database." << endl;
    }

    void displayDatabase() {
        readFile.open(filename);
        string line;
        cout << "Records in the database:" << endl;
        while (getline(readFile, line)) {
            cout << line << endl;
        }
        readFile.close();
    }

    void searchRecord(int id) {
        readFile.open(filename);
        string line;
        bool found = false;
        while (getline(readFile, line)) {
            stringstream ss(line);
            Record record;
            ss >> record.id >> record.name >> record.email;
            if (record.id == id) {
                found = true;
                cout << "Record found:" << endl;
                cout << "ID: " << record.id << ", Name: " << record.name << ", Email: " << record.email << endl;
                break;
            }
        }
        readFile.close();
        if (!found) {
            cout << "Record not found." << endl;
        }
    }

    void deleteRecord(int id) {
        vector<Record> records;
        bool found = false;

        readFile.open(filename);
        string line;
        while (getline(readFile, line)) {
            stringstream ss(line);
            Record record;
            ss >> record.id >> record.name >> record.email;
            if (record.id == id) {
                found = true;
                continue; // Skip adding this record to the vector
            }
            records.push_back(record);
        }
        readFile.close();

        if (!found) {
            cout << "Record not found." << endl;
            return;
        }

        ofstream writeFile(filename);
        for (const auto& rec : records) {
            writeFile << rec.id << " " << rec.name << " " << rec.email << endl;
        }
        writeFile.close();

        cout << "Record deleted successfully." << endl;
    }
};

int main() {
    Database db;

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Create Database" << endl;
        cout << "2. Display Database" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. Delete Record" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                db.createDatabase();
                break;
            case 2:
                db.displayDatabase();
                break;
            case 3: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                db.searchRecord(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                db.deleteRecord(id);
                break;
            }
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
