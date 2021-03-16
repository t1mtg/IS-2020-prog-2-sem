#include <cmath>
#include <vector>
#define M_PI 3.14159265358979323846

const double eps = 1e-9;

class Point {
private:
    double x;
    double y;
public:

    Point();
    Point(double x_, double y_);
    Point(const Point &other);
    Point& operator= (const Point &other);
    double getX() const;
    double getY() const;
    //fixed default
    ~Point() = default;
};

class PolygonalChain {
protected:
    std::vector <Point> V;
public:
    PolygonalChain();
    PolygonalChain(int k, Point *a);
    PolygonalChain(const PolygonalChain &other);
    PolygonalChain& operator= (const PolygonalChain &other);
    double side_length (const Point& a, const Point& b) const;
    virtual double perimeter() const;
    double getN() const;
    Point getPoint(int n) const;
    virtual ~PolygonalChain() = default;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain();
    ClosedPolygonalChain(int k, Point *a);
    ClosedPolygonalChain(const ClosedPolygonalChain &other);
    ClosedPolygonalChain& operator= (const ClosedPolygonalChain &other);
    ~ClosedPolygonalChain() = default;
    double perimeter() const override;
};


class Polygon : public ClosedPolygonalChain {
public:
    Polygon(int k, Point *a);
    Polygon(const Polygon &other);
    Polygon &operator=(const Polygon &other);
    ~Polygon() = default;
    virtual double area() const;
};

class Triangle : public Polygon {
public:
    Triangle(int k, Point *a);
    Triangle(const Triangle &other);
    Triangle& operator= (const Triangle &other);
    ~Triangle() = default;
    double area() const override;
    bool pCheck(double &a1, double &a2, double &a3) const;
    bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
    Trapezoid(int k, Point *a);
    Trapezoid(const Trapezoid &other);
    Trapezoid& operator= (const Trapezoid &other);
    ~Trapezoid() = default;
    double slope(const Point& a, const Point& b) const;
    double point_to_line_dist(const Point& x, const Point& l1, const Point& l2) const;
    std::pair<double,double> height_square() const;
    double height() const;
    double area() const override;

};

class RegularPolygon : public Polygon {
public:
    RegularPolygon(int k, Point *a);
    RegularPolygon(const RegularPolygon &other);
    RegularPolygon& operator= (const RegularPolygon &other);
    ~RegularPolygon() = default;
    double perimeter() const override;
    double area() const override;
};


Point::Point() {
    x = 0;
    y = 0;
}
Point::Point(double x_, double y_)
        : x(x_), y(y_) {
}

Point::Point(const Point &other)
        : x(other.x), y(other.y) {
}

Point& Point::operator= (const Point &other) {
    if (&other == this) {
        return *this;
    } else {
        x = other.x;
        y = other.y;
        return *this;
    }
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}


PolygonalChain::PolygonalChain() {
}

PolygonalChain::PolygonalChain(int k, Point *a) {
    for (int i = 0; i < k; i++) {
        V.push_back(a[i]);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain &other) {
    for (const auto & i : other.V) {
        this->V.push_back(i);
    }
}

PolygonalChain& PolygonalChain::operator= (const PolygonalChain &other)  {
    //fixed vector clear is strange here
    this->V = other.V;
    return *this;
}

double PolygonalChain::side_length (const Point& a, const Point& b) const{
    return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
}

double PolygonalChain::perimeter() const {
    double p = 0;
    for (unsigned i = 0; i < V.size() - 1; i++) {
        p += side_length(V[i], V[i+1]);
    }
    return p;
}

double PolygonalChain::getN() const {
    return V.size();
}

Point PolygonalChain::getPoint(int n) const {
    return V[n];
}



ClosedPolygonalChain::ClosedPolygonalChain() {
}

ClosedPolygonalChain::ClosedPolygonalChain(int k, Point *a) : PolygonalChain(k, a) {

}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &other) : PolygonalChain(other) {
}

ClosedPolygonalChain& ClosedPolygonalChain::operator= (const ClosedPolygonalChain &other) {
    this->V = other.V;
    return *this;
}


double ClosedPolygonalChain::perimeter() const {
    //fixed copy-paste with prevoius
    double p = perimeter();
    p += side_length(V[0], V[V.size()-1]);
    return p;
}

Polygon::Polygon(int k, Point *a) : ClosedPolygonalChain(k, a) {

}

Polygon::Polygon(const Polygon &other) : ClosedPolygonalChain(other) {

}

Polygon& Polygon::operator= (const Polygon &other) {
    this->V = other.V;
    return *this;
}

//fixed indenation problems


double Polygon::area () const {
    double sum = 0;
    for (unsigned i = 0;  i < V.size() - 1; i++) {
        sum += ((V[i+1].getX() - V[i].getX())*(V[i].getY() + V[i+1].getY()));
    }
    return std::abs(sum / 2);
}


Triangle::Triangle(int k, Point *a) : Polygon(k, a) {
}

Triangle::Triangle(const Triangle &other) : Polygon(other) {
}

Triangle& Triangle::operator= (const Triangle &other) {
    this->V = other.V;
    return *this;
}


double Triangle::area() const {
    return (std::abs((V[0].getX() - V[2].getX()) * (V[1].getY() - V[2].getY()) -
                     (V[1].getX() - V[2].getX()) * (V[0].getY() - V[2].getY()))) / 2;
}

bool Triangle::pCheck(double &a1, double &a2, double &a3) const {
    return ((a1 + a2 - a3) < eps);
};

//fixed without sqrt
bool Triangle::hasRightAngle() const {
    double a1 = pow(V[0].getX() - V[1].getX(), 2) + pow(V[0].getY() - V[1].getY(), 2);
    double a2 = pow(V[1].getX() - V[2].getX(), 2) + pow(V[1].getY() - V[2].getY(), 2);
    double a3 = pow(V[0].getX() - V[2].getX(), 2) + pow(V[0].getY() - V[2].getY(), 2);
    //fixed return
    return (pCheck(a1, a2, a3) || pCheck(a1, a3, a2) || pCheck(a2, a3, a1));

}

Trapezoid::Trapezoid(int k, Point *a) : Polygon(k, a) {
}

Trapezoid::Trapezoid(const Trapezoid &other) : Polygon(other) {
}

Trapezoid& Trapezoid::operator= (const Trapezoid &other) {
    this->V = other.V;
    return *this;
}


double Trapezoid::slope(const Point& a, const Point& b) const {
    return (a.getY() - b.getY())/(a.getX() - b.getX());
}

double Trapezoid::point_to_line_dist(const Point& x, const Point& l1, const Point& l2) const {
    double A = l1.getY() - l2.getY();
    double B = l1.getX() - l2.getX();
    double C = l1.getY() * l2.getX() - l2.getY() * l1.getX();
    return std::abs((A * x.getX() + B * x.getY() + C) / std::sqrt(std::abs(A * A + B * B)));
}

std::pair<double,double> Trapezoid::height_square() const {
    double Height = 0;
    double m1 = 0, m2 = 0;
    double slope1 = slope(V[0], V[1]);
    double slope2 = slope(V[2], V[3]);
    double slope3 = slope(V[0], V[3]);
    double slope4 = slope(V[1], V[2]);

    if (slope1 == slope2) {
        Height = point_to_line_dist(V[3], V[0], V[1]);
        m1 = side_length(V[0], V[1]);
        m2 = side_length(V[2], V[3]);
    }

    if (slope3 == slope4) {
        Height = point_to_line_dist(V[1], V[0], V[3]);
        m1 = side_length(V[0], V[3]);
        m2 = side_length(V[1], V[2]);
    }
    double Square = std::abs(0.5 * (m1 + m2) * Height);

    return std::pair<double, double> (Height, Square);
}

double Trapezoid::height() const {
    return height_square().first;
}

double Trapezoid::area() const  {
    return height_square().second;
}


RegularPolygon::RegularPolygon(int k, Point *a) : Polygon(k, a) {
}

RegularPolygon::RegularPolygon(const RegularPolygon &other) : Polygon(other) {
}

RegularPolygon& RegularPolygon::operator= (const RegularPolygon &other) {
    this->V = other.V;
    return *this;
}


double RegularPolygon::perimeter() const {
    double n = V.size();
    double a = side_length(V[0], V[1]);
    return n * a;
}
double RegularPolygon::area() const {
    double n = V.size();
    double a = side_length(V[0], V[1]);
    return n * pow(a, 2) / (4 * tan(M_PI/n));
}


#include <iostream>
#include <cassert>

using namespace std;

const double EPS = 1e-9;

void PointCheck() {
    const Point p1;
    assert(p1.getX() == 0 && p1.getY() == 0);
    const Point p2(3, 4);
    assert(p2.getX() == 3 && p2.getY() == 4);
}

void InheritancePolygonalChainCheck(const PolygonalChain *pc, const PolygonalChain *cpc) {
    assert(pc->perimeter() == 9);
    assert(cpc->perimeter() == 12);
}

void PolygonsCheck() {
	cerr << "I am here";
    Point *a = new Point[3]{Point(0, 0), Point(3, 4), Point(3, 0)};
    Point *b = new Point[4]{Point(0, 0), Point(1, 4), Point(3, 4), Point(3, 0)};
    const Polygon p(3, a);
    const Triangle t(3, a);
    const Trapezoid tr(4, b);
    const PolygonalChain pc(3, a);
    assert(pc.getN() == 3 && pc.getPoint(1).getX() == 3 && pc.getPoint(1).getY() == 4);
    assert(pc.perimeter() == 9);
    const ClosedPolygonalChain cpc(3, a);
	cerr << "I am here2";
    a[1] = Point();
    assert(cpc.getN() == 3 && cpc.getPoint(1).getX() == 3 && cpc.getPoint(1).getY() == 4);
    assert(cpc.perimeter() == 12);
    InheritancePolygonalChainCheck(&pc, &cpc);
    assert(p.area() == 6);
    assert(abs(tr.height() - 4) < EPS);
    assert(t.hasRightAngle());
    Triangle trSharpestAsMyHand(3, new Point[3]{Point(0, 0), Point(1, 1), Point(0, 100)});
    assert(!trSharpestAsMyHand.hasRightAngle());
    RegularPolygon rp(4, new Point[4]{Point(0, 0), Point(0, 2), Point(2, 2), Point(2, 0)});
    assert(abs(rp.area() - 4) < EPS && abs(rp.perimeter() - 8) < EPS);
    Trapezoid tra(4, b);
	cerr << "I am here3";
    tra = tr;
    assert(abs(tra.height() - 4) < EPS);
    Trapezoid* trap = new Trapezoid(4, b);
    Trapezoid trCopy(*trap);
    delete trap;
    assert(abs(trCopy.height() - 4) < EPS);
    Triangle floatArea(3, new Point[3]{Point(0, 0), Point(1, 1), Point(0, 1)});
    assert(floatArea.area() == 0.5);
	cerr << "I am here4";
}

int main() {
    PointCheck();
    PolygonsCheck();
}