#include <algorithm>
#include "polynomial.h"
using namespace std;


Polynomial::Polynomial() : min_power(0), max_power(0), n(1) {
    V[0] = 0;
}

Polynomial::Polynomial(int min_power_, int max_power_, const int *elements) : min_power(min_power_),
                                                                              max_power(max_power_), n(abs(max_power - min_power) + 1) {
    for (auto i = 0; i < n; i++) {
        this->V[i] = elements[i];
    }
}

void Polynomial::show() const {
    for (auto i = 0; i < n; i++) {
        cout << V[i] << " ";
    }
    cout << endl;
    cout << min_power << " " << max_power << endl;
}
void Polynomial::Format() {
    while (V[n - 1] == 0 && n != 1) {
        max_power--;
        n--;
    }

    while (V[0] == 0 && n != 1) {
        for (int i = 0; i < n - 1; i++) {
            V[i] = V[i + 1];
        }
        min_power++;
        n--;
    }

}

Polynomial::Polynomial(const Polynomial &other){
    delete [] this->V;
    this->n = other.n;
    this->min_power = other.min_power;
    this->max_power = other.max_power;
    this->V = new int[this->n];
    for (int i = 0; i < this->n; i++) {
        this->V[i] = other.V[i];
    }
}


Polynomial & Polynomial::operator = (const Polynomial &other)  {
    if (&other == this) {
        return *this;
    } else {
        delete [] this->V;
        this->n = other.n;
        this->max_power = other.max_power;
        this->min_power = other.min_power;
        this->V = new int[n];
        for (int i = 0; i < n; i++) {
            this->V[i] = other.V[i];
        }
    }
    return *this;
}


bool Polynomial::operator == (const Polynomial &lhs) const {
    Polynomial tmp1(lhs);
    Polynomial tmp2(*this);
    tmp1.Format();
    tmp2.Format();
    bool check = true;
    if (tmp1.n != tmp2.n || tmp1.max_power != tmp2.max_power || tmp1.min_power != tmp2.min_power) {
        return false;
    } else {
        for (int i = 0; i < tmp2.n; i++) {
            if (tmp1.V[i] != tmp2.V[i]) {
                check = false;
            }
        }
    }

    return check;
}

bool Polynomial::operator != ( Polynomial &rhs) const {
    return !(*this == rhs);
}

Polynomial& Polynomial::operator+= (const Polynomial &rhs) {
    *this = sign(*this, rhs, 1);
    return *this;
}

Polynomial& Polynomial::operator -= (const Polynomial &rhs) {
    *this = sign(*this, rhs, -1);
    return *this;
}

Polynomial Polynomial::operator - () const {
    Polynomial res(*this);
    std::for_each(res.V, res.V + res.n, [](int &i) {i = -i;});
    return res;
}

Polynomial Polynomial::operator - (const Polynomial &rhs) const {
    Polynomial res = *this;
    res -= rhs;
    return res;
}

Polynomial Polynomial::operator + (const Polynomial &rhs) const {
    Polynomial res = *this;
    res += rhs;
    return res;
}


Polynomial Polynomial::operator * (const Polynomial &rhs) const {
    int max_degree = rhs.max_power + this->max_power;
    int min_degree = rhs.min_power + this->min_power;
    int *s1 = new int[abs(max_degree - min_degree) + 1]();
    if (min_degree == rhs.min_power) {
        for (int i = 0; i < rhs.n; i++) {
            for (int j = 0; j < this->n; j++) {
                s1[i + j] += rhs.V[i] * this->V[j];
            }
        }
    } else {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < rhs.n; j++) {
                s1[j + i] += this->V[i] * rhs.V[j];
            }
        }
    }

    Polynomial tmp = Polynomial(min_degree, max_degree, s1);
    delete [] s1;
    tmp.Format();
    return tmp;
}

Polynomial Polynomial::operator / (const int divider) {
    Polynomial tmp(*this);
    std::for_each(tmp.V, tmp.V + tmp.n, [divider](int &i) { i /= divider;});
    return tmp;
}

Polynomial& Polynomial::operator *= (const Polynomial &rhs) {
    *this = *this * rhs;
    return *this;
}

Polynomial& Polynomial::operator *= (const int multiplier) {
    *this = *this * multiplier;
    return *this;
}

Polynomial& Polynomial::operator /= (const int divider) {
    *this = *this / divider;
    return *this;
}

int Polynomial::operator[] (const int index) const {
    if (index > this->max_power || index < this->min_power)
        return 0;
    return this->V[index + this->min_power];
}

int & Polynomial::operator[] (const int index)  {
    int tmp = this->n;
    if (index > this->max_power)
        this->max_power = index;
    if (index < this->min_power)
        this->min_power = index;
    this->n = abs(max_power - min_power) + 1;
    //fixed memory-leak
    int *V2 = new int[this->n]();
    for (int i = 0; i < tmp; i++)
        V2[i] = this->V[i];
    Polynomial temp = Polynomial(min_power, max_power, V2);
    *this = temp;
    delete [] V2;
    return this->V[index - this->min_power];
}

double Polynomial::get(int value) {
    double x = V[0] * std::pow(value, min_power);
    double result = x;
    for (int i = 1; i < this->n; i++) {
        x *= value;
        result += V[i] * x;
    }
    return result;
}

Polynomial::~Polynomial() {
    delete [] this->V;
}



istream& operator >> (istream &in, Polynomial &poly) {
    in >> poly.min_power >> poly.max_power;
    poly.n = abs(poly.max_power - poly.min_power) + 1;
    poly.V = new int[poly.n];
    for (int i = 0; i < poly.n; i++) {
        in >> poly.V[i];
    }
    return in;
}


ostream& operator << (ostream &out, const Polynomial &poly) {
    if (poly.min_power == 0 && poly.max_power == 0) {
        out << poly.V[0];
    } else {
        for (auto i = poly.n - 1; i >= 0; i--) {
            if (poly.V[i] != 0) {
                if (poly.V[i] > 0 && i != poly.n - 1) {
                    out << "+";
                }
                if (i + poly.min_power == 0) {
                    out << poly.V[i];
                } else if (i + poly.min_power == 1) {
                    out << poly.V[i] << "x";
                } else if (poly.V[i] == 1) {
                    out << "x^" << i + poly.min_power;
                } else if (poly.V[i] == -1) {
                    out << "-x^" << i + poly.min_power;
                } else {
                    out << poly.V[i] << "x^" << i + poly.min_power;
                }
            }
        }
    }
    //out << endl;
    return out;
}

Polynomial operator * (const Polynomial &rhs, const int multiplier) {
    Polynomial tmp = rhs;
    std::for_each(tmp.V, tmp.V + tmp.n, [multiplier](int &i) { i *= multiplier;});
    return tmp;
}

Polynomial operator * (const int multiplier, const Polynomial &rhs) {
    Polynomial tmp = rhs;
    std::for_each(tmp.V, tmp.V + tmp.n, [multiplier](int &i) { i *= multiplier;});
    return tmp;
}

Polynomial &Polynomial::sign(Polynomial &lhs, const Polynomial &rhs, int d) {
    int max_degree = max(rhs.max_power, lhs.max_power);
    int min_degree = min(rhs.min_power, lhs.min_power);

    int *s1 = new int[abs(max_degree - min_degree) + 1]();
    int abs_min = abs(rhs.min_power - lhs.min_power);

    if (min_degree == rhs.min_power) {
        for (int i = 0; i < rhs.n; i++) {
            s1[i] += d * rhs.V[i];
        }

        for (int i = abs_min; i < lhs.n + abs_min; i++) {
            s1[i] += d * lhs.V[i - abs_min];
        }

    } else {
        for (int i = 0; i < lhs.n; i++) {
            s1[i] += d * lhs.V[i];
        }
        for (int i = abs_min; i < rhs.n + abs_min; i++) {
            s1[i] += d * rhs.V[i - abs_min];
        }
    }

    lhs = Polynomial(min_degree, max_degree, s1);
    delete [] s1;
    return lhs;
}
