/**************************************************
*	Assignment #2	Intro. C++		  *
*	Winter 2015	McGill University	  *
**************************************************/

#include "flowers.h"
#include <math.h>

using namespace std;

unsigned int spitEulerSquare(unsigned int index) {
	if (index == 0)
		return 7;//the head
	switch (index % 5) { 
		case 1:
			return 3*(index/5) + 2;
			break;
		case 4:
			return 3*(index/5) + 3;
			break;
		case 0:
			return 12*(index/5) + 6;
			break;
		default:
			return 1; }}  


Fraction getApproximation(ContinuedFraction &fr, unsigned int n){
	Fraction *fract = new Fraction();
	vector<int> ray = fr.fixedPart;
	
	if (!fr.periodicPart.empty())
		while (ray.size() < n)//append the periodic bit
			ray.insert(ray.end(),fr.periodicPart.begin(),fr.periodicPart.end());
	if(ray.size() >= n)//make sure ray is big enough
		ray.resize(n);	//set to size n
	
	fract->numerator = 1;	//initialize fraction	
	fract->denominator = ray.back();
	ray.pop_back();
	
	while (!ray.empty()) {
		fract->numerator = ray.back()*fract->denominator + fract->numerator;		
		ray.pop_back();
		if (ray.empty())
			break;
		int temp = fract->numerator;	//flipping fraction
		fract->numerator = fract->denominator;// for next
		fract->denominator = temp;}
	
	return *fract; }

ContinuedFraction rmInt(ContinuedFraction &fr){
	fr.fixedPart[0] = 0; 
	return fr; }

double getAngle(ContinuedFraction &theta, int k) {
	theta = rmInt(theta);
	Fraction fract = getApproximation(theta,7);
	
	double top = (double) ((fract.numerator*k)%fract.denominator); //casting ints
	double bottom = (double) fract.denominator; // to doubles
	
	top = top*2.00*M_PI;
	
	return top/bottom; }

Seed getSeed(ContinuedFraction &theta, int k) {
	Seed *seed = new Seed();
	double angle = getAngle(theta,k);	
	float n = (float) k;
	seed->x = sqrt(n/M_PI)*cos(angle);
	seed->y = sqrt(n/M_PI)*sin(angle);
	return *seed; }

void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
	int k = flower.size();
	flower.push_back(getSeed(theta,k));		
	return; }

int spitNextMagicBox(MagicBox &box) {
	while(true){
		int i = (box).i; int j = (box).j;
		int k = (box).k; int l = (box).l;

		if (k==0 && l==0)
			return 0; //reached end

		else if (k==0 || l==0 || (i/k != j/l)) {
			int p = spit((box).boxedFraction, (box).indexInBoxedFraction++);
			if(p!=-1) {
				(box).i =j; (box).j =i+j*p;
				(box).k =l; (box).l =k+l*p; }
			else {
				(box).i =j; (box).j =j;
				(box).k =l; (box).l =l; }}
		else {
			int q = i/k;
			(box).i =k; (box).j =l;
			(box).k =i-k*q; (box).l =j-l*q;
			return q; }}}

ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
	ContinuedFraction fract;
	MagicBox box;
	(box).boxedFraction = f;
	(box).i=a;
	(box).j=b;
	int numb; //variable holding the place of integer to spit
	for (int i = 0; i< length; i++){
		numb = spitNextMagicBox(box); //integer to spit out
		if(numb <= 0) 
			break;	//break out early
		fract.fixedPart.push_back(numb);}	//push k into the continued fractions

	return fract;}
