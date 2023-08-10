#pragma once
#include<iostream>
#include <vector>
using namespace std;
class Food {
public:
	Food(string name, double price, int id) {
		this->name = name;
		this->price = price;
		this->id = id;
	}
	string getName() {
		return this->name;
	}
	double getPrice() {
		return this->price;
	}
	double getId() {
		return this->id;
	}
private:
	string name;
	double price;
	int id;
};

void foodSelection();



void payment(vector<Food>foods,vector<int>orders);