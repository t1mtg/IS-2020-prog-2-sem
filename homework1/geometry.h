

#ifndef HW1_GEOMETRY_H
#define HW1_GEOMETRY_H
#include <cmath>
#include <vector>
const double eps = 1e-9;

class Point {
private:
    double x;
    double y;
public:
    explicit Point(double x_ = 0, double y_ = 0)
            : x(x_), y(y_) {
    }

    Point(const Point &other)
            : x(other.x), y(other.y) {
    }

    Point& operator= (const Point &other) {
        if (&other == this) {
            return *this;
        } else {
            x = other.x;
            y = other.y;
            return *this;
        }
    }

    ~Point() {

    }

    void setX(double x_) {
        x = x_;
    };

    void setY(double y_) {
        y = y_;
    };

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }
};

class PolygonalChain {
protected:
    std::vector <Point> V;
public:
    PolygonalChain() {
    }

    PolygonalChain(int k, Point *a) {
        for (int i = 0; i < k; i++) {
            V.push_back(a[i]);
        }
    }

    PolygonalChain(const PolygonalChain &other) {
        for (const auto & i : other.V) {
            this->V.push_back(i);
        }
    }

    PolygonalChain& operator= (const PolygonalChain &other)  {
        this->V.clear();
        this->V = other.V;
        return *this;
    }

    double side_length (const Point& a, const Point& b) const{
        return sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
    }

    virtual double perimeter() const {
        double p = 0;
        for (unsigned i = 0; i < V.size() - 1; i++) {
            p += side_length(V[i], V[i+1]);
        }
        return p;
    }


    double getN() const {
        return V.size();
    }

    Point getPoint(int n) const {
        return V[n];
    }



    virtual ~PolygonalChain() {
        V.clear();
    }

};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain() {
    }

    ClosedPolygonalChain(int k, Point *a) : PolygonalChain(k, a) {

    }

    ClosedPolygonalChain(const ClosedPolygonalChain &other) : PolygonalChain(other) {
    }

    ClosedPolygonalChain& operator= (const ClosedPolygonalChain &other) {
        this->V.clear();
        this->V = other.V;
        return *this;
    }

    ~ClosedPolygonalChain() {
        V.clear();
    }

    double perimeter() const override {
        double p = 0;
        for (unsigned i = 0; i < V.size() - 1; i++) {
            p += side_length(V[i], V[i+1]);
        }
        p += side_length(V[0], V[V.size()-1]);
        return p;
    }
};

class Polygon : public ClosedPolygonalChain {
public:

    Polygon(int k, Point *a) : ClosedPolygonalChain(k, a) {
    }

    Polygon(const Polygon &other) : ClosedPolygonalChain(other) {
    }

    Polygon& operator= (const Polygon &other) {
        this->V.clear();
        this->V = other.V;
        return *this;
    }

    ~Polygon() {
        V.clear();
    }

    virtual double area () const {
        double sum = 0;
        for (unsigned i = 0;  i < V.size() - 1; i++) {
            sum += ((V[i+1].getX() - V[i].getX())*(V[i].getY() + V[i+1].getY()));
        }
        return std::abs(sum / 2);
    }
};

class Triangle : public Polygon {
public:

    Triangle(int k, Point *a) : Polygon(k, a) {
    }

    Triangle(const Triangle &other) : Polygon(other) {
    }

    Triangle& operator= (const Triangle &other) {
        this->V.clear();
        this->V = other.V;
        return *this;
    }

    ~Triangle() {
        V.clear();
    }

    double area() const override {
        return (std::abs((V[0].getX() - V[2].getX()) * (V[1].getY() - V[2].getY()) -
                    (V[1].getX() - V[2].getX()) * (V[0].getY() - V[2].getY()))) / 2;
    }

    bool pCheck(double &a1, double &a2, double &a3) const {
        if (std::abs((pow(a1, 2) + pow(a2, 2) - pow(a3, 2))) < eps) {
            return true;
        } else {
            return false;
        }
    };

    bool hasRightAngle() const {
        double a1 = side_length(V[0], V[1]);
        double a2 = side_length(V[1], V[2]);
        double a3 = side_length(V[0], V[2]);
        if (pCheck(a1, a2, a3) || pCheck(a1, a3, a2) || pCheck(a2, a3, a1)) {
            return true;
        } else {
            return false;
        }
    }
};

class Trapezoid : public Polygon {
public:

    Trapezoid(int k, Point *a) : Polygon(k, a) {
    }

    Trapezoid(const Trapezoid &other) : Polygon(other) {
    }

    Trapezoid& operator= (const Trapezoid &other) {
        this->V.clear();
        this->V = other.V;
        return *this;
    }

    ~Trapezoid() {
        V.clear();
    }

    double slope(const Point& a, const Point& b) const {
        return (a.getY() - b.getY())/(a.getX() - b.getX());
    }

    double point_to_line_dist(const Point& x, const Point& l1, const Point& l2) const {
        double A = l1.getY() - l2.getY();
        double B = l1.getX() - l2.getX();
        double C = l1.getY() * l2.getX() - l2.getY() * l1.getX();
        return std::abs((A * x.getX() + B * x.getY() + C) / std::sqrt(std::abs(A * A + B * B)));
    }

    std::pair<double,double> height_square() const {
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

    double height() const {
        return height_square().first;
    }

    double area() const override {
        return height_square().second;
    }

};

class RegularPolygon : public Polygon {
public:
    RegularPolygon(int k, Point *a) : Polygon(k, a) {
    }

    RegularPolygon(const RegularPolygon &other) : Polygon(other) {
    }

    RegularPolygon& operator= (const RegularPolygon &other) {
        this->V.clear();
        this->V = other.V;
        return *this;
    }

    ~RegularPolygon() {
        V.clear();
    }

    double area() const override {
        double n = V.size();
        double a = side_length(V[0], V[1]);
        return n * pow(a, 2) / (4 * tan(M_PI/n));
    }
};
#endif //HW1_GEOMETRY_H
