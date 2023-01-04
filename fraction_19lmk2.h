//
// Created by lucas krayacich on 2022-10-09.
// 20201392
#include <string>
using namespace std;

#ifndef ASSIGNMENT2_FRACTION_19LMK2_H
#define ASSIGNMENT2_FRACTION_19LMK2_H

class Fraction {
    int num_, denom_;
public:
    //Constructor with no input parameters
    Fraction();
    //constructor with a single parameter
    Fraction(int num);
    //constructor with a numerator and denominator as inputs
    Fraction(int num, int denom);
    //numerator accessor
    int numerator();
    //denominator accessor
    int denominator();
    //greatest common denominator function
    int gcd(int num, int denom);


    //Overloading Unary Operators
    Fraction& operator++();
    Fraction  operator++(int);
    Fraction& operator-();

    //Overloading Binary Operators
    Fraction& operator+=(const Fraction& frac1);
    friend Fraction operator+(const Fraction& fraction1, const Fraction& fraction2 );
    friend Fraction operator-(const Fraction& fraction1, const Fraction& fraction2 );
    friend Fraction operator*(const Fraction& fraction1, const Fraction& fraction2 );
    friend Fraction operator/(const Fraction& fraction1, const Fraction& fraction2 );
    friend bool operator==(const Fraction& fraction1, const Fraction& fraction2);
    friend bool operator!=(const Fraction& fraction1, const Fraction& fraction2);
    friend bool operator>=(const Fraction& fraction1, const Fraction& fraction2);
    friend bool operator<=(const Fraction& fraction1, const Fraction& fraction2);
    friend bool operator>(const Fraction& fraction1, const Fraction& fraction2);
    friend bool operator<(const Fraction& fraction1, const Fraction& fraction2);
    friend bool operator>(const Fraction& fraction1, int integer);
    friend bool operator<(int integer, const Fraction& fraction2);
    friend ostream& operator<<(ostream& out,const Fraction& fraction);
    friend istream& operator>>(istream& in, Fraction& fraction);

};

//Exception Class Fraction Exception
class FractionException{
public:
    FractionException(const string& message);
    string& what();
private:
    string message;
};

#endif //ASSIGNMENT2_FRACTION_19LMK2_H
