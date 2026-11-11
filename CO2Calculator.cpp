
#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>

using namespace std;

// Ask the user to enter the journey distance
double enterDistance() {
    double miles;

    cout << "Enter your journey distance in miles: ";

    while (!(cin >> miles) || miles < 0) {
        cout << "Invalid distance. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return miles;
}

// Ask the user to select the fuel type
char selectFuel() {
    char fuel;

    while (true) {
        cout << "Choose fuel type (P = Petrol, D = Diesel): ";

        if (!(cin >> fuel)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        fuel = static_cast<char>(
            toupper(static_cast<unsigned char>(fuel))
        );

        if (fuel == 'P' || fuel == 'D') {
            return fuel;
        }

        cout << "Invalid fuel type. Please try again." << endl;
    }
}

// Calculate the estimated CO2 emissions
double estimateEmissions(double miles, char fuel) {

    // Example fuel consumption: 8.5 litres per 100 miles
    const double fuelRate = 8.5;

    // CO2 emission factors in kg per litre
    const double petrolFactor = 2.31;
    const double dieselFactor = 2.68;

    double litresUsed = (miles / 100.0) * fuelRate;

    double emissionFactor;

    if (fuel == 'P') {
        emissionFactor = petrolFactor;
    } else {
        emissionFactor = dieselFactor;
    }

    return litresUsed * emissionFactor;
}

// Main program
int main() {

    cout << "================================" << endl;
    cout << "      CO2 JOURNEY CALCULATOR     " << endl;
    cout << "================================" << endl;

    cout << "\nCalculate the estimated CO2 emissions"
         << " produced during your journey.\n" << endl;

    double distance = enterDistance();

    char fuelType = selectFuel();

    double result = estimateEmissions(distance, fuelType);

    cout << fixed << setprecision(2);

    cout << "\n---------- JOURNEY SUMMARY ----------" << endl;
    cout << "Distance: " << distance << " miles" << endl;

    if (fuelType == 'P') {
        cout << "Fuel type: Petrol" << endl;
    } else {
        cout << "Fuel type: Diesel" << endl;
    }

    cout << "Estimated CO2 emissions: "
         << result << " kg" << endl;

    cout << "-------------------------------------" << endl;

    cout << "\nNote: This calculation uses an estimated"
         << " fuel consumption of 8.5 litres per 100 miles."
         << endl;

    cout << "\nThank you for using CO2 Journey Calculator!"
         << endl;

    return 0;
}
