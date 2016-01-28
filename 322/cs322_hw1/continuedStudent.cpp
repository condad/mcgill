/********************************************************
*	Assignment 1, Intro. to C++, COMP 322		*
*	Winter 2015, PROF. GEORGHE COMANCHI.		*		
*********************************************************/

#include <iostream>
#include "continued.h"
using namespace std;


ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {
	ContinuedFraction *fract = new ContinuedFraction;
	fract->head = b / a; //assuming b > a
	fract->tail = (b % a == 0) ?
			nullptr :
			getCFlargerThanOne(a, b%a);
	return fract;	}

ContinuedFraction *getCF(unsigned int b, unsigned int a) {	
        return getCFlargerThanOne(b, a);}		


ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {
	ContinuedFraction *fract = new ContinuedFraction;// the one we return
	fract->head = head;	//new fraction with first arg as head
	ContinuedFraction *it_f, *it_p, *it_r; //iterators 
	/*here we work through both the fixed and period bits one at a time*/ 
	it_f = fixed; it_p = period; it_r = fract;//initializing iterators
	ContinuedFraction *holder = period; //remembers the periods place for later connection
	
	while (it_f != nullptr){ //iterating 
		it_r->tail = new ContinuedFraction;//through
		it_r = it_r->tail;//the
		it_r->head= it_f->head;//fixed
		it_f = it_f->tail; }//part
	bool first = true;//connection catalyst
	while (it_p != nullptr){ //iterating 
		it_r->tail = new ContinuedFraction;//through
		if (first){
			holder = it_r->tail;
			first = false;}
		it_r = it_r->tail;//the
		it_r->head = it_p->head;//period
		it_p = it_p->tail; }//part 
	
	it_r->tail = holder; //connecting..
	return fract;	}

Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {
	Fraction *fract = new Fraction;
	if (fr == nullptr) return *fract;

	if ( n <= 1 || fr->tail == nullptr){//base case
		fract->numerator = fr->head;
		fract->denominator = 1;}
	else {
		Fraction temp = getApproximation(fr->tail, n-1);
		fract->numerator = fr->head*temp.numerator + temp.denominator;
		fract->denominator = temp.numerator; }

	return *fract;}
