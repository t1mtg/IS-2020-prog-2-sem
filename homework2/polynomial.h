#pragma once
#include <sstream>
#include <cmath>
#include <iostream>

class Polynomial {
private:
    int min_power = 0;
    int max_power = 0;
    int n = abs(max_power - min_power) + 1;
    int *V = new int[n];
public:

    Polynomial();
    Polynomial(int min_power_, int max_power_, const int *elements);
    void show() const;
    void Format(Polynomial &Poly);
    Polynomial(const Polynomial &other);
    Polynomial &operator = (const Polynomial &other);
    bool operator ==(Polynomial lhs);
    bool operator != ( Polynomial &rhs);
    Polynomial operator+ (const Polynomial &rhs) const;
    Polynomial operator - () const;
    Polynomial operator - (const Polynomial &rhs) const;
    Polynomial operator += (const Polynomial &rhs);
    Polynomial operator -= (const Polynomial &rhs);
    Polynomial operator * (const Polynomial &rhs) const;
    Polynomial operator / (const int divider);
    Polynomial & operator *= (const Polynomial &rhs);

    Polynomial & operator *= (const int multiplier);
    Polynomial & operator /= (const int divider);

    int operator[] (const int index) const;
    int &operator[] (const int index);
    double get(int value);
    ~Polynomial();
    friend Polynomial operator * (int multiplier, const Polynomial &rhs);
    friend Polynomial operator * (const Polynomial &rhs, int multiplier);
    friend std::ostream& operator << (std::ostream &out, const Polynomial &Poly);
    friend std::istream& operator >> (std::istream &in, Polynomial &Poly);
};

std::istream& operator >> (std::istream &in, Polynomial &Poly);
std::ostream& operator << (std::ostream &out, const Polynomial &Poly);
Polynomial operator * (const Polynomial &rhs, const int multiplier);
Polynomial operator * (const int multiplier, const Polynomial &rhs);
