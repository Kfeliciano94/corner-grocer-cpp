#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

class CornerGrocerTracker {
    public:
    explicit CornerGrocerTracker(const string& inputFileName) {
        LoadPurchaseData(inputFileName);
    }
    void CreateBackupFile(const string& outputFileName) const {
        ofstream outputFile(outputFileName);

        if (!outputFile.is_open()) {
            throw runtime_error("Unable to create backup file: " + outputFileName);
        }

        for (const auto& item : itemFrequencies) {
            outputFile << item.first << " " << item.second << '\n';
        }
    }

    int GetItemFrequency(const string& itemName) const {
        string formattedName = FormatItemName(itemName);
        auto item = itemFrequencies.find(formattedName);

        if (item == itemFrequencies.end()) {
            return 0;
        }

        return item->second;
    }

    void PrintFrequencyList() const {
        cout << "\nItem Frequencies\n";
        cout << "----------------\n";

        for (const auto& item : itemFrequencies) {
            cout << left << setw(15) << item.first << item.second << '\n';
        }
    }

    void PrintHistogram() const {
        cout << "\nPurchase Histogram\n";
        cout << "------------------\n";

        for (const auto& item : itemFrequencies) {
            cout << left << setw(15) << item.first << string(item.second, '*') << '\n';
        }
    }

private:
    map<string, int> itemFrequencies;

    void LoadPurchaseData(const string& inputFileName) {
        ifstream inputFile(inputFileName);
        string itemName;

        if (!inputFile.is_open()) {
            throw runtime_error("Unable to open input file: " + inputFileName);
        }

        while (inputFile >> itemName) {
            ++itemFrequencies[FormatItemName(itemName)];
        }
    }

    static string FormatItemName(const string& itemName) {
        string formattedName = itemName;

        if (formattedName.empty()) {
            return formattedName;
        }

        transform(formattedName.begin(), formattedName.end(), formattedName.begin(),
            [](unsigned char character) { return static_cast<char>(tolower(character)); });
        formattedName.at(0) = static_cast<char>(toupper(formattedName.at(0)));

        return formattedName;
    }
};

int GetMenuChoice() {
    int choice = 0;

    while (true) {
        cout << "\nCorner Grocer Item Tracker\n";
        cout << "1. Search for an item frequency\n";
        cout << "2. Print all item frequencies\n";
        cout << "3. Print purchase histogram\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (cin >> choice && choice >= 1 && choice <= 4) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "\nInvalid selection. Please enter a number from 1 through 4.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void RunMenu(const CornerGrocerTracker& tracker) {
    int choice = 0;

    while (choice != 4) {
        choice = GetMenuChoice();

        switch (choice) {
        case 1: {
            string itemName;

            cout << "\nEnter the item name to search for: ";
            getline(cin, itemName);
            cout << itemName << " appears " << tracker.GetItemFrequency(itemName)
                 << " time(s).\n";
            break;
        }
        case 2:
            tracker.PrintFrequencyList();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "\nThank you for using the Corner Grocer Item Tracker.\n";
            break;
        default:
            break;
        }
    }
}

int main() {
    const string inputFileName = "CS210_Project_Three_Input_File.txt";
    const string backupFileName = "frequency.dat";

    try {
        CornerGrocerTracker tracker(inputFileName);

        // The backup is created before showing the menu, as requested by Corner Grocer.
        tracker.CreateBackupFile(backupFileName);
        RunMenu(tracker);
    }
    catch (const exception& error) {
        cerr << "Program error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
