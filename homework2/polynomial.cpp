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
	//todo useless arg
    void Polynomial::Format(Polynomial &Poly) {
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
        //todo check if other == *this
        delete [] this->V;
        this->n = other.n;
        this->max_power = other.max_power;
        this->min_power = other.min_power;
        this->V = new int[n];
        if (&other == this) {
            return *this;
        } else {
            for (int i = 0; i < n; i++) {
                this->V[i] = other.V[i];
            }
        }
        return *this;
    }


    //todo const&
    bool Polynomial::operator ==(Polynomial lhs) {
        lhs.Format(lhs);
        this->Format(*this);
        bool check = true;
        if (lhs.n != this->n || lhs.max_power != this->max_power || lhs.min_power != this->min_power) {
            return false;
        } else {
            for (int i = 0; i < this->n; i++) {
                if (lhs.V[i] != this->V[i]) {
                    check = false;
                }
            }
        }

        return check;
    }

    bool Polynomial::operator != ( Polynomial &rhs) {
        return !(*this == rhs);
    }

    //todo + from +=
    //todo const Polynomial&, int d
    // a += b, a-= b -> a += d * b
    Polynomial Polynomial::operator+ (const Polynomial &rhs) const {
        int max_degree = max(rhs.max_power, this->max_power);
        int min_degree = min(rhs.min_power, this->min_power);

        int *s1 = new int[abs(max_degree - min_degree) + 1]();
        int abs_min = abs(this->min_power - rhs.min_power);

        if (min_degree == rhs.min_power) {
            for (int i = 0; i < rhs.n; i++) {
                s1[i] += rhs.V[i];
            }

            for (int i = abs_min; i < this->n + abs_min; i++) {
                s1[i] += this->V[i - abs_min];
            }

        } else {
            for (int i = 0; i < this->n; i++) {
                s1[i] += this->V[i];
            }
            for (int i = abs_min; i < rhs.n + abs_min; i++) {
                s1[i] += rhs.V[i - abs_min];
            }
        }

        Polynomial tmp = Polynomial(min_degree, max_degree, s1);
        delete [] s1;
        return tmp;
    }

    Polynomial Polynomial::operator - () const {
        //todo vars from small letter
        Polynomial Res(*this);
        for (int i = 0; i < n; ++i) {
            Res.V[i] = -Res.V[i];
        }
        return Res;
    }

    //todo without unary -
    Polynomial Polynomial::operator - (const Polynomial &rhs) const {
        Polynomial minuend(*this);
        minuend = minuend + (-rhs);
        return minuend;
    }

    Polynomial Polynomial::operator += (const Polynomial &rhs) {
        *this = *this + rhs;
        return *this;
    }

    Polynomial Polynomial::operator -= (const Polynomial &rhs) {
        *this = *this - rhs;
        return *this;
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
        tmp.Format(tmp);
        return tmp;
    }

    Polynomial Polynomial::operator / (const int divider) {
        Polynomial tmp(*this);
        //todo for_each
        for (int i = 0; i < tmp.n; i++) {
            tmp.V[i] /= divider;
        }
        tmp.Format(tmp);
        return tmp;
    }

    Polynomial & Polynomial::operator *= (const Polynomial &rhs) {
        *this = *this * rhs;
        return *this;
    }

    Polynomial & Polynomial::operator *= (const int multiplier) {
        *this = *this * multiplier;
        return *this;
    }

    Polynomial & Polynomial::operator /= (const int divider) {
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
        //todo memory-leak
        int *V2 = new int[this->n]();
        for (int i = 0; i < tmp; i++)
            V2[i] = this->V[i];
        Polynomial temp = Polynomial(min_power, max_power, V2);
        *this = temp;
        return this->V[index - this->min_power];
    }

    //todo O(n)
    double Polynomial::get(int value) {
        double result = 0;
        for (int i = 0; i < this->n; i++) {
            result += std::pow(value, i + this->min_power) * this->V[i];
        }
        return result;
    }

    Polynomial::~Polynomial() {
        delete [] this->V;
    }



istream& operator >> (istream &in, Polynomial &Poly) {
    in >> Poly.min_power >> Poly.max_power;
    Poly.n = abs(Poly.max_power - Poly.min_power) + 1;
    Poly.V = new int[Poly.n];
    for (int i = 0; i < Poly.n; i++) {
        in >> Poly.V[i];
    }
    return in;
}


ostream& operator << (ostream &out, const Polynomial &Poly) {
    if (Poly.min_power == 0 && Poly.max_power == 0) {
        out << Poly.V[0];
    } else {
        for (auto i = Poly.n - 1; i >= 0; i--) {
            if (Poly.V[i] != 0) {
                if (Poly.V[i] > 0 && i != Poly.n - 1) {
                    out << "+";
                }
                if (i + Poly.min_power == 0) {
                    out << Poly.V[i];
                } else if (i + Poly.min_power == 1) {
                    out << Poly.V[i] << "x";
                } else if (Poly.V[i] == 1) {
                    out << "x^" << i + Poly.min_power;
                } else if (Poly.V[i] == -1) {
                    out << "-x^" << i + Poly.min_power;
                } else {
                    out << Poly.V[i] << "x^" << i + Poly.min_power;
                }
            }
        }
    }
    //out << endl;
    return out;
}

Polynomial operator * (const Polynomial &rhs, const int multiplier) {
    Polynomial tmp = rhs;
    for (int i = 0; i < tmp.n; i++) {
        tmp.V[i] *= multiplier;
    }
    return tmp;
}

Polynomial operator * (const int multiplier, const Polynomial &rhs) {
    Polynomial tmp = rhs;
    for (int i = 0; i < tmp.n; i++) {
        tmp.V[i] *= multiplier;
    }
    return tmp;
}