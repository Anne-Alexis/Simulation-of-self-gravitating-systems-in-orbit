#ifndef BOITE_H
#define BOITE_H

#include <iostream>
#include <list>
#include "particule.hpp"

using namespace std;


// Class Point2d
class Point2d{
    public:
        double x;
        double y;
        Point2d(double x0=0,double y0=0):x(x0),y(y0){} //constructeur prenant deux coordonnées
        Point2d& operator +=(const Point2d & P){x+=P.x; y+=P.y; return *this;}
        Point2d& operator -=(const Point2d & P){x-=P.x; y-=P.y; return *this;}
        Point2d& operator *=(double a){x*=a; y*=a; return *this;}
        Point2d& operator /=(double a){x/=a; y/=a; return *this;}
};
Point2d operator + (const Point2d&, const Point2d&);
Point2d operator - (const Point2d&, const Point2d&);
Point2d operator * (double a, const Point2d&);
Point2d operator * (const Point2d&, double a);
Point2d operator / (double a, const Point2d&);
Point2d operator / (const Point2d&, double a);
bool operator == (const Point2d&, const Point2d&);
bool operator != (const Point2d&, const Point2d&);
ostream & operator <<(ostream & os ,const Point2d&);



//CLass Boite
class Boite {
    public:
        int level;
        Point2d C; //Center
        double length;
        double width;
        Point2d G; //center of mass
        double m; //mass
        Particule * P; // Pointer on the only particule remaining in the boite
        Boite *  sister; // Pointer sister
        Boite * child; // Pointer first child
        //Constructeur
        Boite(const list<Particule> &);
        //Method
        bool check_number_particule(const list<Particule> &); // true if there are particules in false if there is no particules. Have to change P.
        Point2d find_new_center();

};

void create_graph(Boite &, const list<Particule> &);






#endif