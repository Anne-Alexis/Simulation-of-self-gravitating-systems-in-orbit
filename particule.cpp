#include "boite.hpp"
#include "math.h"

void Particule::generateur()
{
    double x,x_1,x_2,x_3,x_4,v,v_e,r;
    x = 1.0/RAND_MAX;
    double u_r=2;
    double u_v=2;
    while (u_r>1){
        x_1 = x*rand();
        x_2 = x*rand();
        x_3 = x*rand();
        x_4 = x*rand();
        r=pow(0.999*pow(x_1,-2/3)-1,-1/2);
        u_r=pow(pow(x_2,2)+pow(x_3,2)+pow(x_4,2),1/2);
    }
    r_x=r*x_2/u_r;
    r_y=r*x_3/u_r;
    r_z=r*x_4/u_r;

    x_1 = x*rand();
    x_2 = x*rand();
    v_e=sqrt(2)*(1+pow(r,2))*(-1/4);
    while (x_2<10*pow(x_1,2)*pow(1-pow(x_1,2),7/2)){
        x_1 = x*rand();
        x_2 = x*rand();
    }
    v=x_1*v_e;
    while (u_v>1){
        x_1 = x*rand();
        x_2 = x*rand();
        x_3 = x*rand();
        x_4 = x*rand();
        u_v=pow((pow(x_2,2)+pow(x_3,2)+pow(x_4,2)),1/2);
    }
    v_x=v*x_2/u_v;
    v_y=v*x_3/u_v;
    v_z=v*x_4/u_v;
}


void force(Particule &pr, Boite *b)  
{   const double G= 6.6742*pow(10,-11);
    const double epsilon1 = min(b->l,min(b->w,b->d))/100;
    const double epsilon2 =???;
    Particule *P_term;
    Point3d Centre=b->G;
    double d,r;
    d=pow(pr.r_x-Centre.x,2)+pow(pr.r_y-Centre.y,2)+pow(pr.r_z-Centre.z,2);

//d est le carre de la distance entre la particule et le centre de la boite 
//si d n'est pas plus grand que la distance entre les particules de la boite, on va entrer dans la boite et calculer la force pour chaque particule dedans
    if (b->l/pow(d,1/2)>=epsilon1) {
        if (b->child!=0) {
                force(pr,b->child);
                if (b->sister!=0){force(pr,b->sister);}  
            else {
                if (b->P==0){                             //Si on est face à une boite terminale sans particule, on passe à la soeur
                    if (b->sister==0){exit;}              //Si la boite n'a ni soeur ni fille, on a parcourut toutes les boites
                        else {force(pr,b->sister);}}
                    else {                               //Alors il y a une particule dans la boite
                        P_term=b->P;
                        //r est le carré de la distance entre la particule en argument et la particule terminale de la boite
                        r=pow(pr.r_x-P_term->r_x,2)+pow(pr.r_y-P_term->r_y,2)+pow(pr.r_z-P_term->r_z,2); 
                        if (r<=epsilon2){r=epsilon2;};
                        pr.F_x-=G*b->m*pr.m*(P_term->r_x-pr.r_x)/pow(r,3);
                        pr.F_y-=G*b->m*pr.m*(P_term->r_y-pr.r_y)/pow(r,3);
                        pr.F_z-=G*b->m*pr.m*(P_term->r_z-pr.r_z)/pow(r,3);
        if (b->sister!=0){force(pr,b->sister);};
            };
        }}
//Si d  est beaucoup plus grand que la distance entre les particules de la boite (sa taille), on fait comme si la boite etait une grande particule,
//Et on passe à la boite soeur
        else {
            pr.F_x-=G*b->m*pr.m*(Centre.x-pr.r_x)/pow(d,3);
            pr.F_y-=G*b->m*pr.m*(Centre.y-pr.r_y)/pow(d,3);
            pr.F_z-=G*b->m*pr.m*(Centre.z-pr.r_z)/pow(d,3);
            if (b->sister!=0){force(pr,b->sister);};}

    };

}


void Particule::initialisation(double M){
    double t=pow(10,-2);
    v_x=r_x+t*F_x/2*M;
    v_y=r_y+t*F_y/2*M;
    v_z=r_z+t*F_z/2*M;
}

void Particule::mise_a_jour(double M){
    double t=pow(10,-2);
    v_x=r_x+t*F_x/M;
    v_y=r_y+t*F_y/M;
    v_z=r_z+t*F_z/M;
    r_x=r_x+t*v_x;
    r_y=r_y+t*v_y;
    r_z=r_z+t*v_z;
}



ostream & operator<< (ostream & os, Particule& p)
{   os<<"masse:"<<p.m<<"\nposition:("<<p.r_x<<","<<p.r_y<<","<<p.r_z<<")\n vitesse:("<<p.v_x<<","<<p.v_y<<","<<p.v_z<<") \n Force:("<<p.F_x<<","<<p.F_y<<","<<p.F_z<<")";
    return os;}
