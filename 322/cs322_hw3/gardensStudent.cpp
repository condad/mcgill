#include "gardens.h"
#include <stack>
#include <iostream>
#include <math.h>

 /* 0-credit */
Fraction ContinuedFraction::getApproximation(unsigned int k) const {
	Fraction fract;//fraction to return
	stack<cf_int> stck;
	resetIterator(); 

	for (int i = k; i >=1; i--){
		stck.push(next()); // push all values onto stack
		if (hasNoMore()) break;}
	
	fract = {0,1};//initialize fraction
	
	while(!stck.empty()){
		fract.numerator = fract.denominator*stck.top() + fract.numerator;
		stck.pop();
		if(!stck.empty()){//modifying the fraction
			cf_int temp = fract.numerator;
			fract.numerator = fract.denominator;
			fract.denominator = temp;} }

	return fract;	}


RationalCF::RationalCF(Fraction f): PeriodicCF({}, {}){
	cf_int a, b, x, temp;//need to fill this one out
	a = f.numerator; b = f.denominator;

	while (b != 0){
		x = a/b;
		a -= x*b;
		temp = a;
		a = b;
		b = temp;
		fixedPart.push_back(x);} }

RationalCF::~RationalCF() {}

/* QUESTION 3*/

cf_int PeriodicCF::next() const {
	cf_int index = *iteratorPosition;
	(*iteratorPosition)++;
	
	if (index < fixedPart.size())
		return fixedPart.at(index);//determines if the value repeats
	else
		return periodicPart.at((index-fixedPart.size())%periodicPart.size()); }
 
bool PeriodicCF::hasNoMore() const {
    return (*iteratorPosition >= fixedPart.size() && periodicPart.empty()); }

void PeriodicCF::resetIterator() const {
    *iteratorPosition = 0; }

PeriodicCF::~PeriodicCF() {
    delete iteratorPosition; }


/* QUESTION 4*/

MagicBoxCF::MagicBoxCF(ContinuedFraction const *f, unsigned long aParam, unsigned long bParam): a(aParam), b(bParam){
	mbnums = new cf_int[4];
	mbnums[0] = a; mbnums[1] = b;
	mbnums[2] = 1; mbnums[3] = 0;
	boxedFraction = f;
	resetIterator(); }

cf_int MagicBoxCF::next() const {
	while( ((mbnums[2] == 0 || mbnums[3] == 0) && !(mbnums[2] == 0 && mbnums[3] == 0)) ||
            (mbnums[2] != 0 && mbnums[3] != 0 && mbnums[0]/mbnums[2] != mbnums[1]/mbnums[3]) ){
		
		if(boxedFraction->hasNoMore()){
			mbnums[0] = mbnums[1];//manipulates the box 
			mbnums[2] = mbnums[3];//until
            		continue; }//desired form is achieved
		
		cf_int p = boxedFraction->next();
		
		int i = mbnums[1], j = mbnums[0] + mbnums[1] * p,
		k = mbnums[3], l = mbnums[2] + mbnums[3] * p;
		
		mbnums[0] = i; mbnums[1] = j;
		mbnums[2] = k; mbnums[3] = l; }//this loop isn't terminating
	
    // if we reached the end of the cf - return -1
	if(mbnums[2] == 0 && mbnums[3] == 0) 
		return -1;
    // return q and change box accordingly
	
	int q = mbnums[0] / mbnums[2];
	int i = mbnums[2], j = mbnums[3],
	k = mbnums[0] - mbnums[2] * q,
	l = mbnums[1] - mbnums[3] * q;
	
	mbnums[0] = i; mbnums[1] = j;
	mbnums[2] = k; mbnums[3] = l;
	
	return q; }

bool MagicBoxCF::hasNoMore() const {
	return (mbnums[2] == 0 && mbnums[3] == 0); }

void MagicBoxCF::resetIterator() const {
	mbnums[0] = a; mbnums[1] = b;
	mbnums[2] = 1; mbnums[3] = 0;
	boxedFraction->resetIterator(); }

MagicBoxCF::~MagicBoxCF() {
	delete[] mbnums; }



/* QUESTION 5*/

ostream &operator<<(ostream& outs, const ContinuedFraction &cf) {
	cf.resetIterator();
	int length = 10;
	bool first = true;
	outs<<"[";
	while (!cf.hasNoMore()){
		outs << cf.next();
		if (--length == 0 || cf.hasNoMore()){
			if (length == 0)
				outs << " ...";
			break;}
		else
			outs << ((first)? "; " : ", ");
		first = false;}
	outs<<"]";
	return outs; }


/* QUESTION 6 */

Flower::Flower(const ContinuedFraction *f, unsigned int apx): theta(f), apx_length(apx){}

	
float Flower::getAngle(unsigned int k) const {
	float angle;
	
	Fraction fract = theta->getApproximation(apx_length);
	
	angle = (float) fract.numerator/ (float) fract.denominator;
	
	return angle*2.0*pie; }


Seed Flower::getSeed(unsigned int k) const {
	Seed sd;
	
	float angle = getAngle(k);
	sd.x = sqrt(k/pie)*cos(k*angle);
	sd.y = sqrt(k/pie)*sin(k*angle);
	return sd; }

vector<Seed> Flower::getSeeds(unsigned int k) const {
	vector<Seed> seeds;
	
	for(int i = 0; i < k; i++)	
		seeds.push_back(getSeed(i));

	return seeds; }


Flower::~Flower() {}

/* QUESTION 7*/

void Flower::writeMVGPicture(ostream &out, unsigned int k, unsigned int scale_x, unsigned int scale_y) const {
	unsigned int c_x, c_y, b_x;
	vector<Seed> seeds = getSeeds(k);
	
	for(vector<Seed>::iterator it = seeds.begin(); it != seeds.end(); it++){
		int i = distance(seeds.begin(), it);
		c_x = scale_x/2 + seeds.at(i).x * (scale_x - 200)/2 * sqrt(pie/k);
		c_y = scale_y/2 + seeds.at(i).y * (scale_y - 200)/2 * sqrt(pie/k);
		b_x = c_x + sqrt((float) i / k) *  min(scale_y, scale_x) / 100; 
		if (b_x - c_x < 1)
			b_x++;  
		out <<"fill blue circle "<< c_x << "," << c_y <<" " << b_x << "," <<c_y<<endl;} }


