//
// Created by lucas krayacich on 2022-10-09.
// 20201392
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "fraction_19lmk2.h"

FractionException::FractionException(const string &message) : message(message) {}
string& FractionException::what() {return message;}

//Constructor with no parameter
Fraction::Fraction() {
    num_ = 0;
    denom_ = 1;
}

//Constructor with single parameter
Fraction:: Fraction(int num){
    num_ = num;
    denom_ = 1;
}

//Constructor with both parameters
//uses gcd function to simplify
Fraction ::Fraction(int num, int denom) {

    if (denom == 0){
        throw FractionException("Illegal Operation: Fraction has a Zero Value in Denominator");
    }

    int com_denom = gcd(num, denom);
    num = num / com_denom;
    denom = denom / com_denom;

    if (num > 0 && denom < 0) {
        denom = denom * -1;
        num = num * -1;
    }else {
        num = num*1;
    }

    num_ = num;
    denom_ = denom;
}

//num_ accessor
int Fraction::numerator() {
    return num_;
}

//denom_ accessor
int Fraction::denominator() {
    return denom_;
}

//recursive member gcd function
int Fraction::gcd(int num, int denom){
    if (denom != 0)
        return gcd(denom, num % denom);
    else
        return num;
}

//recursive non-member gcd function
int gcd(int num, int denom){
   if (denom != 0)
       return gcd(denom, num % denom);
   else
       return num;
}


//Least common multiple function
int lcm(int x,int y){
    return  (x * y) / gcd(x,y);
}

//overloads + operator to add together fractions
Fraction operator+(const Fraction& frac1, const Fraction& frac2){
    int common1 = lcm(frac1.denom_, frac2.denom_) / frac1.denom_;
    int common2 = lcm(frac1.denom_, frac2.denom_) / frac2.denom_;
    int final = (frac1.num_*common1 + frac2.num_*common2);

    return( Fraction(final, lcm(frac1.denom_,frac2.denom_)) );
}

//overloads - operator to subtract fractions
Fraction operator-(const Fraction& frac1, const Fraction& frac2){
    int common1 = lcm(frac1.denom_, frac2.denom_) / frac1.denom_;
    int common2 = lcm(frac1.denom_, frac2.denom_) / frac2.denom_;
    int final = (frac1.num_*common1 - frac2.num_*common2);

    return( Fraction(final, lcm(frac1.denom_,frac2.denom_)) );
}

//overloads * operator to multiply fractions
Fraction operator*(const Fraction& frac1, const Fraction& frac2){
    int final_denom = frac1.denom_ * frac2.denom_;
    int final_num = frac1.num_ * frac2.num_;

    return Fraction(final_num, final_denom);
}

//overloads / operator to divide fractions
Fraction operator/(const Fraction& frac1, const Fraction& frac2){

    return Fraction(frac1.num_*frac2.denom_, frac2.num_*frac1.denom_);
}

//overloads == to compare fractions
//also works when comparing fractions to integer values
bool operator ==(const Fraction& frac1, const Fraction& frac2){
    Fraction simple_frac1 = Fraction(frac1.num_,frac1.denom_);
    Fraction simple_frac2 = Fraction(frac2.num_, frac2.denom_);
    if (simple_frac1.num_ ==  simple_frac2.num_ && simple_frac1.denom_ == simple_frac2.denom_){
        return true;
    } else {
        return false;
    }
}

//overloads != to check fraction equality
bool operator != (const Fraction& frac1, const Fraction& frac2){
    return(!(frac1 == frac2));
}

//overloads pre increment ++ to increment by adding the denominator
Fraction& Fraction::operator++(){
    this->num_ = this->num_ + this->denom_;
    return *this;
}

//overloads post increment ++(int) operator
Fraction Fraction::operator++(int) {
    Fraction frac_copy = Fraction(this->num_, this->denom_);
    this->num_ = this->num_ + this->denom_;
    return frac_copy;
}

//overloads addition and assignment operator
Fraction& Fraction::operator+=(const Fraction &frac1) {
    Fraction frac_checker = Fraction(frac1.num_,frac1.denom_);
    *this = *this + frac1;
    return *this;
}

//turns fraction negative
Fraction& Fraction::operator-(){
    this->num_ = this->num_ * -1;
    return *this;
}


bool operator >(const Fraction& frac1, const Fraction& frac2){
    return ((frac1.num_/frac1.denom_) - (frac2.num_/frac2.denom_) > 0);
}

bool operator <(const Fraction& frac1, const Fraction& frac2){
    return ((frac2.num_/frac2.denom_) - (frac1.num_/frac1.denom_) > 0);
}

bool operator>(const Fraction& frac1, int integer){
    Fraction intFrac = Fraction(integer);
    float checkBool = (frac1.num_/(float)frac1.denom_) - (intFrac.num_/(float)intFrac.denom_);
    return (checkBool > 0);
}

bool operator<(int integer, const Fraction& frac1){
    Fraction intFrac = Fraction(integer);
    float checkBool = (frac1.num_/(float)frac1.denom_) - (intFrac.num_/(float)intFrac.denom_);
    return (checkBool > 0);
}

bool operator >=(const Fraction& frac1, const Fraction& frac2){
    return ((frac1.num_/frac1.denom_) - (frac2.num_/frac2.denom_) >= 0);
}

bool operator <=(const Fraction& frac1, const Fraction& frac2){
    return ((frac1.num_/frac1.denom_) - (frac2.num_/frac2.denom_) <= 0);
}

//overloads << operator to output the numerator and denominator into fraction format
ostream& operator <<(ostream& output, const Fraction& frac){
    output << frac.num_ << "/" << frac.denom_ << endl;
    return output;
}

//overloads >> operator in order to store inputted values into numerator and denominator values
istream& operator>>(istream& input, Fraction& frac){

    vector<string> numAndDenom;

    string input_val;
    input >> input_val;

    stringstream ss(input_val);
    string numberString;

    while(getline(ss, numberString, '/')){
        numAndDenom.push_back(numberString);
    }
    
    if (numAndDenom.size() < 2) {
        frac.num_ = stoi(input_val);
        frac.denom_ = 1;
    }else if (stoi(numAndDenom[1]) == 0)
        throw FractionException("Illegal Operation: Fraction has a Zero Value in Denominator");
    else{
        frac.num_ = stoi(numAndDenom[0]);
        frac.denom_ = stoi(numAndDenom[1]);
    }
    
    return input;
}

