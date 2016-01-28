#include <vector>
#include <iostream>

#ifndef hw3_gardens_h
#define hw3_gardens_h

using namespace std;

typedef unsigned long cf_int;

struct Fraction {
    cf_int numerator;
    cf_int denominator; };


class ContinuedFraction {
friend class MagicBoxCF; //magic box will need to use the iterator
protected:
    virtual cf_int next() const = 0;
    virtual bool hasNoMore() const = 0;
    virtual void resetIterator() const = 0;
public:
    Fraction getApproximation(unsigned int k) const;
    virtual ~ContinuedFraction() {} // since this class is abstract, we need to define a virtual descructor
    friend ostream &operator<<(ostream &out, const ContinuedFraction &cf); };


class PeriodicCF : public ContinuedFraction {
protected:
    vector<cf_int> fixedPart;
    vector<cf_int> periodicPart;
    
    unsigned int *iteratorPosition;
    
    virtual cf_int next() const;
    virtual bool hasNoMore() const;
    virtual void resetIterator() const;
public:
    PeriodicCF(const vector<cf_int> &fixedParam, const vector<cf_int> &periodicParam) : fixedPart{fixedParam}, periodicPart{periodicParam} 
		{iteratorPosition = new unsigned int(0); }
    PeriodicCF(const vector<cf_int> &periodicParam) : PeriodicCF({}, periodicParam) {}
    ~PeriodicCF(); };


class RationalCF : public PeriodicCF {
public:
    RationalCF (const vector<cf_int> &fixedParam) : PeriodicCF(fixedParam,{}) {}
    RationalCF (Fraction frac);
    ~RationalCF();
    unsigned int length() const {return (unsigned int) fixedPart.size(); }
    Fraction getValue() const { return PeriodicCF::getApproximation(length()); } };


class MagicBoxCF : public ContinuedFraction {
private:
    const ContinuedFraction *boxedFraction;
    const cf_int a,b;
    cf_int *mbnums;
    
    virtual cf_int next() const;
    virtual bool hasNoMore() const;
    virtual void resetIterator() const;
public:
    MagicBoxCF(const ContinuedFraction *f, cf_int a, cf_int b);
    ~MagicBoxCF(); };

/** Gardens **/

struct Seed { float x, y;};

class Flower {
protected:
    const float pie = 3.141592654;
    const ContinuedFraction *theta;
    const unsigned int apx_length;
    float getAngle(unsigned int k) const;
public:
    Flower(const ContinuedFraction *f, unsigned int apxLengthParam);
    ~Flower();
    Seed getSeed(unsigned int k) const;
    vector<Seed> getSeeds(unsigned int k) const;
    void writeMVGPicture(ostream &out, unsigned int k, unsigned int scale_x, unsigned int scale_y) const; }; 

// printing methods - explained in the write-up that comes with this assignment
ostream &operator<<(ostream &out, const ContinuedFraction &cf); //TODO

ostream &operator<<(ostream &out, const Flower &flower); //DONE in test
ostream &operator<<(ostream &out, const Fraction &f); //DONE in test


#endif
