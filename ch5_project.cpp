// ============================================================
// Name    : Andy Nguyen
// Course  : COSC 1437 — Programming Fundamentals II
// Date    : 6/14/26
// Program : Chapter 5 Major Project
// Option  : A — Cookie Sales Tracker
// Purpose : Takes data from a file and creates a summary report
// ============================================================

// ===== SECTION 1: PSEUDOCODE DESIGN BLOCK =====
/*
Start of Program

    Open input file
    IF fail
        display "error"
        exit
    Open output file
    IF fail
        display "error"
        exit

(READ BOXES)

    attempts = 0
    validCost = false;
    WHILE attempts < MAX_RETRIES (3) AND validCost == false:
        read CostPerBox
        IF costPerBox > 0
            validCost = true
        ELSE
            attempts++

    IF validCost == false:
        exit

(MAIN DATA LOOP - EOF)

    WHILE read volunteerName and boxesSold:

        dailySum = 0
        read dailyValue

        Daily Total Loop (SENTINEL)

        WHILE dailyValue != SENTINEL:
            dailySum += dailyValue
            read dailyValue

        IF boxesSold <= 0:
            continue

        IF dailySum != boxesSold:
            Write discrepancy to output file

        totalBoxes += boxesSold
        volunteerCount++
        totalRevenue += boxesSold * costPerBox

        put voluteerName into VolunteerNames
        put boxesSold into volunteerBoxes

    END WHILE

    (AVERAGE CALCULATION)

    IF volunteerCount > 0:
        averageBoxes = totalBoxes / volunteerCount
    ELSE:
        averageBoxes = 0

    (FLAG CONTROLLED)
    
    first = true;
    FOR i = 0 to size-1:
        IF first OR volunteerBoxes[i] > maxBoxes:
            maxBoxes = volunteerBoxes[i]
            topSellers = volunteerNames[i]
            first = false;
        ELSE IF volunteerBoxes[i] == maxBoxes:
            add volunteerNames[i] to topSellers
    End For

    (WRITE REPORT)

    Write table name
    FOR each volunteer:
        write name, boxes sold

    Write totals, revenue, average, top sellers

    (BREAK)

    WHILE true:
        IF totalRevenue > 0:
            break
        else:
            break

    (DO WHILE VALIDATION)

    DO:
        ask user Y/N
    WHILE response not Y, y, N, n

    IF Y or y:
        Display restart message
    ELSE:
        Display goodbye message

End of Program
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const string INPUT_FILE = "ch5_sales.txt";
const string OUTPUT_FILE = "ch5_report.txt";
const int SENTINEL = -999;
const int MAX_RETRIES = 3;
const int DIVIDER_LEN = 10;
const int COLUMN_WIDTH = 20;

// ===== SECTION 2: Input & Validation =====

int main () {
    ifstream inFile(INPUT_FILE);
    ofstream outFile(OUTPUT_FILE);

    if (!inFile) {
        cout << "Error: Couldn't open input file" << endl;
        return 1;
    }

    if (!outFile) {
        cout << "Error: Couldn't open output file" << endl;
        return 1;
    }

    cout << "Files were open with no issues" << endl;

    // ===== SECTION 3: Loop Type Showcase =====

    double costPerBox = 0;
    bool validCost = false;
    int attempts = 0;

    // counter controlled
    while (attempts < MAX_RETRIES && !validCost) {

        if (!(inFile >> costPerBox)) {
            cout << "Error with reading costs per box" << endl;
            return 1;
        }

        if (costPerBox > 0) {
            validCost = true;
        }

        else {
            attempts++;
        }
    }

    if (!validCost) {
        cout << "Bad cost per box after 3 attempts" << endl;
        return 1;
    }

    // ===== SECTION 4: Core Loop Logic =====

    int totalBoxes = 0;
    int volunteerCount = 0;
    double totalRevenue = 0;

    bool first = true;
    int maxBoxes = 0;
    string topSellers = "";

    // ===== SECTION 9: Formatted Output =====

    outFile << fixed << setprecision(2);

    for (int i = 0; i < DIVIDER_LEN; i++) {
        outFile << "-";
    }

    outFile << endl;

    outFile << left << setw(COLUMN_WIDTH) << "Volunteer"
            << right << setw(COLUMN_WIDTH) << "Boxes Sold" << endl;

    for (int i = 0; i < DIVIDER_LEN; i++) {
        outFile << "-";
    }
    
    outFile << endl;

    // ===== SECTION 4: Core Loop Logic =====

    string volunteerName;
    int boxesSold;

    // eof controlled loop
    while (inFile >> volunteerName >> boxesSold) {
        // ===== SECTION 5: Nested Control Structures =====

        int dailyValue, dailySum = 0;

        if (!(inFile >> dailyValue)) {
            break;
        }

        // sentinel controlled loop
        while (dailyValue != SENTINEL) {
            dailySum += dailyValue;
            if (!(inFile >> dailyValue)) {
                break;
            }
        }

        // ===== SECTION 6: break and continue Demonstration =====

        if (boxesSold <= 0) {
            cout << "Skipping " << volunteerName << " (bad box count)" << endl;
            continue;
        }

        // discrepancy check
        if (dailySum != boxesSold) {
            outFile << "Discrepancy: " << volunteerName
                    << " reported " << boxesSold
                    << " but daily total was " << dailySum << endl;
        }

        totalBoxes += boxesSold;
        volunteerCount++;
        totalRevenue += boxesSold * costPerBox;

        // ===== SECTION 3: Loop Type Showcase =====

        // flag controlled loop
        if (first || boxesSold > maxBoxes) {
            maxBoxes = boxesSold;
            topSellers = volunteerName;
            first = false;
        }
        else if (boxesSold == maxBoxes) {
            topSellers += ", " + volunteerName;
        }

        // print volunteer row

        outFile << left << setw(COLUMN_WIDTH) << volunteerName
                << right << setw(COLUMN_WIDTH) << boxesSold << endl;

    }

    double averageBoxes = 0;
    if (volunteerCount > 0) {
        // divide by zero protection
        averageBoxes = static_cast<double>(totalBoxes) / volunteerCount;
    }

    // ===== SECTION 9: Formatted Output =====

    for (int i = 0; i < DIVIDER_LEN; i++) {
        outFile << "-";
    }

    outFile << endl;

    outFile << left << setw(COLUMN_WIDTH) << "Total Boxes: "
            << right << setw(COLUMN_WIDTH) << totalBoxes << endl;

    outFile << left << setw(COLUMN_WIDTH) << "Total Revenue: "
            << right << setw(COLUMN_WIDTH) << totalRevenue << endl;

    outFile << left << setw(COLUMN_WIDTH) << "Average Boxes: "
            << right << setw(COLUMN_WIDTH) << averageBoxes << endl;

    outFile << left << setw(COLUMN_WIDTH) << "Top Seller(s): "
            << right << setw(COLUMN_WIDTH) << topSellers << endl;

    while (true) {
        if (totalRevenue > 0) {
            cout << "Revenue check is good" << endl;
            break;
        }
        else {
            cout << "Revenue check is not good" << endl;
            break;
        }
    }

    // ===== SECTION 7: do...while Input Validation =====
    char again;
    do {
        cout << "Do you want to process another file? (Y/N): ";
        cin >> again;
    }
    while (again!='Y' && again!='y' && again!='N' && again!='n');

    if (again == 'Y' || again == 'y') {
        cout << "The program is restarting..." << endl;
    }
    else {
        cout << "Goodbye!" << endl;
    }

    // ===== SECTION 8: Avoiding Bugs / Debugging Commentary =====
    /*
    
    Off-by-one: For the for loop that added the divided, I made sure to use < and not <=

    Infinite loop: Sentinel loop could've been infinite, but it is updated constantly

    Divide by zero: Added a check before calculating average to prevent divide by zero

    Software patch: Logged a discrepancy instead of adding a way to fix it

    Semicolon after loop header: If I added a semicolon after the header,
                                 the logic of the program would be messed up and incorrect
    
    
    */

    return 0;
}

/* Input: ch5_sales.txt 

5.00
Andy 12
3
4
5
-999
Bobby 8
2
2
2
2
-999

*/

/* Input and Output: Console 

@andynguyen2121 ➜ /workspaces/assignment5 (main) $ g++ -Wall -Wextra -std=c++17 ch5_project.cpp 
@andynguyen2121 ➜ /workspaces/assignment5 (main) $ ./a.out 
Files were open with no issues
Revenue check is good
Do you want to process another file? (Y/N): n
Goodbye!
@andynguyen2121 ➜ /workspaces/assignment5 (main) $ 

*/

/* Output: ch5_sales.txt 

----------
Volunteer                     Boxes Sold
----------
Andy                                  12
Bobby                                  8
----------
Total Boxes:                          20
Total Revenue:                    100.00
Average Boxes:                     10.00
Top Seller(s):                      Andy

*/