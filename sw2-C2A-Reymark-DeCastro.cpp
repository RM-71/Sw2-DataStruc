#include <iostream>
#include <algorithm>
using namespace std;

class HouseCost{
	public:
		float flooringcost, paintcost, paintlabor, floorlabor;
		float expenses, sumdays;
		
		float GetLaborCost(float worker, float days){
			return worker * days;	
		}
		float GetTotal(){
			return flooringcost + paintcost + paintlabor + floorlabor;
		}
};

void getPaintandFloorcost(HouseCost ForCost[], string housetype, int i) {
    int nobedroom, sqm, nobathroom;
    float totalFloorArea;
    bool validInput;

    do {
        totalFloorArea = 0;
        validInput = true; 

        cout << "Enter number of bedrooms: ";
        while (!(cin >> nobedroom) || nobedroom < 1) {
            cout << "Error: Please enter a positive number for bedrooms: ";
            cin.clear();
            cin.ignore();
        }
        if ((housetype == "lin" || housetype == "LIN") && nobedroom > 4) {
            cout << "Error: LIN type can only have up to 4 bedrooms." << endl;
            validInput = false;
        } else if ((housetype == "lan" || housetype == "LAN") && nobedroom > 5) {
            cout << "Error: LAN type can only have up to 5 bedrooms." << endl;
            validInput = false;
    	}if(!validInput)continue;
        ForCost[i].paintcost = 0; 
        for (int j = 0; j < nobedroom; j++) {
            cout << "Enter the size of bedroom " << j + 1 << " in sqm: ";
            while (!(cin >> sqm) || sqm <= 0) {
                cout << "Error: Please enter a positive number for sqm: ";
                cin.clear();
                cin.ignore();
            }
            totalFloorArea += sqm; // Accumulate the size
            if (sqm < 30) {
                ForCost[i].paintcost += sqm * 125;
            } else if (sqm >= 30 && sqm < 41) {
                ForCost[i].paintcost += sqm * 175.25;
            } else {
                ForCost[i].paintcost += sqm * 205.50;
            }
        }
        cout << "Enter the size of kitchen in sqm: ";
        while (!(cin >> sqm) || sqm <= 0) {
            cout << "Error: Please enter a positive number for sqm: ";
            cin.clear();
            cin.ignore();
        }
        totalFloorArea += sqm; 
        ForCost[i].paintcost += 12500;
        if (sqm > 50) {
            ForCost[i].paintcost += (sqm - 50) * 75.45;
        }
        if ((housetype == "lin" || housetype == "LIN") && totalFloorArea > 180) {
            cout << "Error: LIN type can only have a maximum floor area of 180 sqm." << endl;
            validInput = false;
        } 
		else if ((housetype == "lan" || housetype == "LAN") && totalFloorArea > 250) {
            cout << "Error: LAN type can only have a maximum floor area of 250 sqm." << endl;
            validInput = false;
        }
    } while (!validInput); 
    validInput = false;
    while (!validInput) {
        cout << "Enter no. of bathrooms: ";
        while (!(cin >> nobathroom) || nobathroom < 1) {
            cout << "Error: Please enter a positive number for bathrooms: ";
            cin.clear();
            cin.ignore();
        }
        if ((housetype == "lin" || housetype == "LIN") && nobathroom > 2) {
            cout << "Error: LIN type can only have up to 2 bathrooms." << endl;
        } else if ((housetype == "lan" || housetype == "LAN") && nobathroom > 3) {
            cout << "Error: LAN type can only have up to 3 bathrooms." << endl;
        } else {
            validInput = true;
        }
    }
    ForCost[i].paintcost += nobathroom * 6550;
    if (housetype == "lin" || housetype == "LIN") {
        ForCost[i].flooringcost = 123450;
    } else if (housetype == "lan" || housetype == "LAN") {
        ForCost[i].flooringcost = 180500;
    }
    if (nobedroom > 2) {
        ForCost[i].flooringcost += (nobedroom - 2) * 8500;
    }
    if (nobathroom > 1) {
        ForCost[i].flooringcost += (nobathroom - 1) * 4750;
    }
}


void getPaintLabor(HouseCost ForLabor[], string housetype, int i){
	float workers, days;
	bool validInput = false;
	do {
		cout << "Enter number of workers for painting (Lin 5-10|Lan 10-15):";
		while(!(cin >> workers)) {
			cout << "Error: Please enter a valid number:";
			cin.clear();
			cin.ignore();
		}
		if ((housetype == "lin" && workers >= 5 && workers <= 10) || 
		    (housetype == "lan" && workers >= 10 && workers <= 15)) {
			validInput = true;
		} 
		else 
			cout << "Error: Please Input Appropriate range for " << housetype << endl;
	} while (!validInput);
	do {
		cout << "Enter how many days of painting (Lin 5-10|Lan 7-14):";
		while(!(cin >> days)) {
			cout << "Error: Please enter a valid number:";
			cin.clear();
			cin.ignore();
		}
		if ((housetype == "lin" && days >= 5 && days <= 10) || 
		    (housetype == "lan" && days >= 7 && days <= 14)) {
			ForLabor[i].sumdays += days;
			validInput = true;
		} 
		else 
			cout << "Error: Please Input Appropriate range for " << housetype << endl;
	} while (!validInput);
	ForLabor[i].paintlabor = ForLabor[i].GetLaborCost(workers, days) * 650;
}

void getFloorLabor(HouseCost ForLabor[], int i){
	float workers, days;
	cout << "Enter number of workers for flooring (10-15):";
	while(!(cin >> workers) || workers < 10 || workers > 15) {
		cout << "Error: Please enter between 10-15 workers:";
		cin.clear();
		cin.ignore();
	}
	cout << "Enter how many days of flooring (7-15): ";
	while(!(cin >> days) || days < 7 || days > 15) {
		cout << "Error: Please enter between 7-15 days:";
		cin.clear();
		cin.ignore();
	}
	ForLabor[i].sumdays += days;
	ForLabor[i].floorlabor = ForLabor[i].GetLaborCost(workers, days) * 550;
}

void getDisplay(HouseCost Expenses[], int i){
	cout << endl << "Total Cost for House no." << i+1 << endl;
	cout << "Painting Cost:" << Expenses[i].paintcost << endl;
	cout << "Flooring Cost:" << Expenses[i].flooringcost << endl;
	cout << "Painting Labor Cost:" << Expenses[i].paintlabor << endl;
	cout << "Flooring Labor Cost:" << Expenses[i].floorlabor << endl;
	cout << "Total Overall Cost:" << Expenses[i].GetTotal() << endl;
	cout << "Total of Days:" << Expenses[i].sumdays << endl;
}

int main() {
    HouseCost Expenses[5];
    int nohouse;
    float totalPaintCost = 0, totalFlooringCost = 0, totalLabor = 0, totalExpenses = 0, totalSumDays = 0;
    string housetype;

    do {
    	cout << "Enter Number of Houses (1-5):";
        cin >> nohouse;
        cin.clear();
        cin.ignore();
        if (!(nohouse <= 5 && nohouse >= 1)) {
            cout << "Please enter 1-5" << endl;
    	}
    } while (!(nohouse <= 5 && nohouse >= 1));
    for (int i = 0; i < nohouse; i++) {
        cout << endl << "Details for House " << i + 1 << endl;
        bool validHouseType = false;
        while (!validHouseType) {
            cout << "Choose House Type (lin/lan): ";
            getline(cin, housetype);
            transform(housetype.begin(), housetype.end(), housetype.begin(), ::tolower);
            if (housetype == "lin" || housetype == "lan") {
                validHouseType = true;
            } 
			else 
                cout << "Error:Please enter 'lin' or 'lan'." << endl;
        }
        getPaintandFloorcost(Expenses,housetype, i);
        getPaintLabor(Expenses, housetype, i);
        getFloorLabor(Expenses, i);
        getDisplay(Expenses, i);

        totalPaintCost += Expenses[i].paintcost;
        totalFlooringCost += Expenses[i].flooringcost;
        totalLabor += Expenses[i].paintlabor +Expenses[i].floorlabor;
        totalExpenses += Expenses[i].GetTotal();
        totalSumDays += Expenses[i].sumdays;
        cin.ignore();
    }
    cout << endl << "Overall Project Expenses" << endl;
    cout << "Painting Cost: " << totalPaintCost << endl;
    cout << "Flooring Cost: " << totalFlooringCost << endl;
    cout << "Total Labor Cost: " << totalLabor << endl;
    cout << "Total Overall Cost: " << totalExpenses << endl;
    cout << "Total Days: " << totalSumDays << endl;
    return 0;
}