#include <iostream>
#include <string>
using namespace std;

int main()
{
	//constants
	const int BASE_COST = 43;
	const int BASE_COST_LUX = 71;
	const double COST_FIRST_100 = 0.27;
	const double COST_NEXT_400_WINTER = 0.27;
	const double COST_NEXT_400_NONWINTER = 0.21;
	const double COST_OVER_500 = 0.17;

	//variables
	int odoStart;
	int odoEnd;
	int days;
	string name;
	string lux;
	int month;

	int miles;
	double total = 0;

	//formatting
	cout.setf(ios::fixed);
	cout.precision(2);

	//Inputs
	cout << "Odometer at start: ";
	cin >> odoStart;
	if (odoStart < 0) {
		cout << "---\nThe starting odometer reading must not be negative." << endl;
		return 1;
	}

	cout << "Odometer at end: ";
	cin >> odoEnd;
	if (odoEnd < odoStart) {
		cout << "---\nThe ending odometer reading must be at least as large as the starting reading." << endl;
		return 2;
	}

	cout << "Rental days: ";
	cin >> days;
	if (days < 0) {
		cout << "---\nThe number of rental days must be positive." << endl;
		return 3;
	}

	cin.ignore();
	cout << "Customer name: ";
	getline(cin, name);
	if (name == "") {
		cout << "---\nYou must enter a customer name." << endl;
		return 4;
	}

	cout << "Luxury car? (y/n): ";
	getline(cin, lux);
	if (lux != "y" && lux != "n") {
		cout << "---\nYou must enter y or n." << endl;
		return 5;
	}

	cout << "Month (1=Jan, 2=Feb, etc.): ";
	cin >> month;
	if (month < 1 || month > 12) {
		cout << "---\nThe month number must be in the range 1 through 12." << endl;
		return 6;
	}

	//calculation
	miles = odoEnd - odoStart;
	total += ((lux == "y") ? BASE_COST_LUX : BASE_COST) * days;
	if (miles > 100) {
		total += 100 * COST_FIRST_100;
		if (miles > 500) {
			total += (400) * ((month == 12 || month <= 3) ? COST_NEXT_400_WINTER : COST_NEXT_400_NONWINTER);
			total += (miles - 500) * COST_OVER_500;
		} else {
			total += (miles - 100) * ((month == 12 || month <= 3) ? COST_NEXT_400_WINTER : COST_NEXT_400_NONWINTER);
		}
	} else {
		total += miles * COST_FIRST_100;
	}

	//Result
	cout << "---\nThe rental charge for " << name << " is $" << total << endl;
	return 0;
}
