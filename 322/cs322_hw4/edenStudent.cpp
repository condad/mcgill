#include "eden.h"
#include <stack>


/* Question 2 : 0-credit */

/*  getting an approximation using the new Fraction class */
Fraction<cf_int> ContinuedFraction::getApproximation(unsigned int k) const {
	if (k ==0) throw 0; // throw exception if arg is 0
	
	auto it = getIterator();//iterator through cf
	auto fract = Fraction<cf_int>(0);// fraction to return
	stack<cf_int> stk;//temporary stack to hold cf values

	for(;k > 0; k--){//initialize the stack
		stk.push(it->next()); 
		if (it->isDone()) break;}
		
	while (!stk.empty()){
		fract += Fraction<cf_int>(stk.top());
		stk.pop();//modify the fraction
		if (!stk.empty())
			fract.invert(); }
	
	return fract; }	

/* Building a rational cf using the new Fraction class*/
RationalCF::RationalCF(Fraction<cf_int> f): PeriodicCF() {
	if (f == Fraction<cf_int>(1,0)) throw 0;
	
	while (f.getDenominator() != 0){
		auto n = f.getNumerator(), d = f.getDenominator();
		this->fixedPart.push_back(n / d);
		f = Fraction<cf_int> (d, n%d); }}


/* Question 3 : Euler squared */

Iterator *EulerSquared::getIterator() const {return new EulerSquaredIterator();}


cf_int EulerSquaredIterator::next() {
	auto x = index++;
	if (x == 0) return 7;//the head
        switch (x % 5) {
                case 1:
                        return 3*(x/5) + 2;
                        break;
                case 4:
                        return 3*(x/5) + 3;
                        break;
                case 0:
                        return 12*(x/5) + 6;
                        break;
                default: 
			return 1; }}

bool EulerSquaredIterator::isDone() const {return false;}


/* Question 4 : PeriodicCF iterator*/

Iterator *PeriodicCF::getIterator() const {return new PeriodicCFIterator(*this);}	

cf_int PeriodicCFIterator::next() {
	auto fs = cf.fixedPart.size(), ps = cf.periodicPart.size();
	if (it < fs)
		return cf.fixedPart[it++];
	else
		return cf.periodicPart[(it++ - fs)%ps]; }

bool PeriodicCFIterator::isDone() const {
	if (!cf.periodicPart.empty()) 
		return false;
	else if( it < cf.fixedPart.size())
		return false;
	else return true; }


/* Question 5 : MagicBoxCF iterator */

Iterator *MagicBoxCF::getIterator() const {return new MagicBoxCFIterator(boxedFraction.getIterator(), a, b);}

cf_int MagicBoxCFIterator::next() {
	if (isDone()) throw -1.0;
	auto numb = i/k, ni = k, nj = l;
	k = i - numb*k; l = j - numb*l;
	i = ni; j = nj;
	updateIndeces();
	return numb; }

bool MagicBoxCFIterator::isDone() const { return k==0 && l == 0; }


