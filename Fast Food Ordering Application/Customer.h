#pragma once
#include<iostream>
#include<string>
#include <fstream>

using namespace std;
class Customer {
public:
	Customer(string name, string contactNo, double topUpValue) {
		this->name = name;
		this->contactNo = contactNo;
		this->topUpValue = topUpValue;
		ifstream InputMemberFile("member.txt");
		int noOfLines = 0;
		std::string line;

		bool isEmpty = InputMemberFile.peek() == EOF;

		if (isEmpty) {
			noOfLines = 0;
		}
		else {
			noOfLines--;
			while (std::getline(InputMemberFile, line))
				++noOfLines;
		//	std::cout << "Number of lines in text file: " << noOfLines;
		}
		string nextNumber = to_string(++noOfLines);
		// string randomNumber = to_string(rand() % 6);
		int paddedLength = 6;
		nextNumber.insert(nextNumber.begin(), paddedLength - nextNumber.size(), '0');
		this->cardNo = "ABC" + nextNumber;
	}
	string getName() {
		return this->name;
	}
	string getCardNo() {
		return this->cardNo;
	}
	string getContactNo() {
		return this->contactNo;
	}
	int getPoint() {
		return this->point;
	}
	double getTopUpValue() {
		return this->topUpValue;
	}

	// modify < operator, when a < b, it will compare based on memberNo, can be changed if we want to compare based on other property
	bool operator< (const Customer& other) const {
		return cardNo < other.cardNo;
	}
private:
	string name;
	string cardNo;
	string contactNo;
	double topUpValue;
	int point = 0;
};


Customer registerCustomer();
void writeMemberToFile(Customer customer);
void cardTopUp(string passedInCardNo="");
double getCurrentTopUpValueFromFile(string cardNo) ;
int getCurrentPointFromFile(string cardNo);
void updatePoint(string cardNo, int newPoint);
void updateValue(string cardNo, double newValue);