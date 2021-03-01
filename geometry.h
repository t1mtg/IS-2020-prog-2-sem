#pragma once
#include <cmath>
#include <vector>
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
    ~Point();
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
    virtual ~PolygonalChain();
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain();
    ClosedPolygonalChain(int k, Point *a);
    ClosedPolygonalChain(const ClosedPolygonalChain &other);
    ClosedPolygonalChain& operator= (const ClosedPolygonalChain &other);
    ~ClosedPolygonalChain();
    double perimeter() const override;
};


class Polygon : public ClosedPolygonalChain {
public:
    Polygon(int k, Point *a);
    Polygon(const Polygon &other);
    Polygon &operator=(const Polygon &other);
    ~Polygon();
    virtual double area() const;
};

class Triangle : public Polygon {
public:
    Triangle(int k, Point *a);
    Triangle(const Triangle &other);
    Triangle& operator= (const Triangle &other);
    ~Triangle();
    double area() const override;
    bool pCheck(double &a1, double &a2, double &a3) const;
    bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
    Trapezoid(int k, Point *a);
    Trapezoid(const Trapezoid &other);
    Trapezoid& operator= (const Trapezoid &other);
    ~Trapezoid();
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
    ~RegularPolygon();
    double perimeter() const override;
    double area() const override;
};

