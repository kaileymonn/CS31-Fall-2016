#include <iostream>
#include <string>
using namespace std;

int main()
{
	// Prompt units sent and check for -ve value
	cout << "Units sent: ";
	int unitsSent;
	cin >> unitsSent;
	if (unitsSent < 0)
	{
		cout << "---" << endl << "The number of units sent must be nonnegative." << endl;
		return 0;
	}
	cin.ignore(10000, '\n');

	// Prompt title and check for 'empty' string
	cout << "Title: ";
	string title;
	getline(cin, title);
	if (title.empty())
	{
		cout << "---" << endl << "You must enter a title." << endl;
		return 0;
	}

	// Prompt base price and check for -ve value
	cout << "Base price: ";
	double basePrice;
	cin >> basePrice;
	if (basePrice < 0)
	{
		cout << "---" << endl << "The base price must be nonnegative." << endl;
		return 0;
	}
	cin.ignore(10000, '\n');

	// Prompt premium/nonpremium and check for invalid input
	cout << "Premium item? (y/n): ";
	string premium;
	getline(cin, premium);
	if (premium != "y" && premium != "n")
	{
		cout << "---" << endl << "You must enter y or n." << endl;
		return 0;
	}

	cout << "---" << endl;

	// Royalty calculation if all prior inputs were valid
	double royalty;

	if (unitsSent <= 400)
		royalty = unitsSent*0.09*basePrice;
	else if (unitsSent <= 1200 && premium == "y")
		royalty = (unitsSent - 400)*0.16*basePrice + (400 * 0.09*basePrice);
	else if (unitsSent <= 1200 && premium == "n")
		royalty = (unitsSent - 400)*0.13*basePrice + (400 * 0.09*basePrice);
	else if (unitsSent > 1200 && premium == "y")
		royalty = (800*0.16*basePrice) + (400 * 0.09*basePrice) + (unitsSent - 1200)*0.14*basePrice;
	else if (unitsSent > 1200 && premium == "n")
		royalty = (800 * 0.13*basePrice) + (400 * 0.09*basePrice) + (unitsSent - 1200)*0.14*basePrice;
	
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << title << " earned $" << royalty << " in royalties." << endl;


}
