/* QUESTION 1 */

/* We will build a general fraction class using templates provide code for all methods listed as TODO*/ 

#ifndef hw4_fraction_h
#define hw4_fraction_h

#include <iostream>

template<typename T> class Fraction {
private:
    T numerator;
    T denominator;
public:
    Fraction(T num, T den): numerator{num}, denominator{den} {
		if (numerator == 0){
			if (denominator == 0) throw 0;
			else denominator = 1;}
		else
			if (denominator == 0)
				numerator = 1; }
	
    Fraction(T num) : numerator{num}, denominator{1} {}
    Fraction(const Fraction &f) : numerator{f.numerator}, denominator{f.denominator} {}
    
    //-- returns the numerator
    T getNumerator() const{ return numerator; }

    //-- returns the denominator
    T getDenominator() const{ return denominator; }
    
    //-- inverts the fraction: swaps denominator and numerator
    Fraction &invert() {
        T temp = numerator;
	numerator = denominator;
	denominator = temp; 
	return *this; }
    
    //-- adds the fraction f to the current fraction a/b + c/d = (a*d + b*c) / (b*d) (don't simplify!)
    Fraction &operator+=(const Fraction &f) {
	auto temp = Fraction(numerator*f.denominator + denominator*f.numerator, denominator*f.denominator);
	numerator = temp.numerator;
	denominator = temp.denominator;
	return *this; }
 
    //-- adds the fraction f to the current fraction a/b + c/d = (a*d + b*c) / (b*d) (don't simplify!)
    Fraction operator+(const Fraction &f) const {
        return Fraction(numerator*f.denominator + denominator*f.numerator, denominator*f.denominator);}
    
    //-- subtracts the fraction f from the current fraction a/b - c/d = (a*d - b*c) / (b*d) (don't simplify!)
    Fraction &operator-=(const Fraction &f) {
        auto temp = Fraction(numerator*f.denominator - denominator*f.numerator, denominator = denominator*f.denominator);
	numerator = temp.numerator;
	denominator = temp.denominator;
	return *this; }
    
    //-- subtracts the fraction f from the current fraction a/b - c/d = (a*d - b*c) / (b*d) (don't simplify!)
    Fraction operator-(const Fraction &f) const {
        return Fraction(numerator*f.denominator - denominator*f.numerator, denominator*f.denominator);}
    
    //-- multiplies the fraction f to the current fraction a/b * c/d = (a*c) / (b*d) (don't simplify!)
    Fraction operator*(const Fraction &f) const {
	return Fraction(numerator*f.numerator, denominator*f.denominator);}
		
    //-- divides the current fraction by f: (a/b) / (c/d) = (a*d) / (b*c) (don't simplify!)
    Fraction operator/(const Fraction &f) const {
	return Fraction(numerator*f.denominator, denominator*f.numerator); }
    
    //-- compares the current fraction to f.
    // * If both denominators are 0, return true (they are both infinity)
    bool operator==(const Fraction &f) const {
       	bool temp = false;
	if (denominator == f.denominator)
		if ((numerator == f.numerator) || (denominator == 0))
			temp = true; 
	return temp;}
    
    //-- compares the current fraction to f for inequality.  use == above!!
    bool operator!=(const Fraction &f) const {
        return !(*this == f); }
    
    T quotient() const {
        if (denominator == 0 ) throw 1;
        return numerator / denominator; }
    
    void simplify() {
        if( numerator == denominator) {
            numerator = denominator = 1;
            return; }
        
        T &smaller = ( numerator < denominator ) ? numerator : denominator;
        // try all possible factors and simplify as long as possible
        for(T factor = 2; factor <= smaller; (factor == 2) ? factor++ : factor += 2) {
            while(numerator % factor == 0 && denominator % factor == 0) {
                numerator /= factor;
                denominator /= factor; } } }
    
    friend std::ostream& operator<<( std::ostream& os, const Fraction& f ) {
        os << "(" << f.numerator << "/" << f.denominator << ")";
        return os; }

};

#endif
