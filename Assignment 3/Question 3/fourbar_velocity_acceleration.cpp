#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define PI 3.14159265358979323846

double newton(double a, double b, double c, double guess)
{
    double x = guess;
    for(int i=0;i<50;i++)
    {
        double fx = a*x*x + b*x + c;
        double dfx = 2*a*x + b;

        if(fabs(fx) < 1e-10) return x;
        if(fabs(dfx) < 1e-12) break;

        x = x - fx/dfx;
    }
    return x;
}

int main()
{
    double a=20, b=30, c=50, d=45;
    double omega2=1.0;
    double alpha2=0.0;
    double alpha_deg = 42.0;
    double alpha = alpha_deg*PI/180.0;

    double L = (b*sin(alpha))/sin(2*alpha);

    ofstream velFile("omega_vs_t.dat");
    ofstream accFile("alpha_vs_t.dat");
    ofstream pointFile("point_motion.dat");

    double x_guess=0.5, y_guess=0.5;

    for(double theta2_deg=0; theta2_deg<=360; theta2_deg+=2)
    {
        double theta2 = theta2_deg*PI/180.0;
        double t = theta2/omega2;

        // --- loop closure ---
        double A = 0.1*cos(theta2) - 0.2375;
        double B = -2*sin(theta2);
        double C = 4.2715 - 1.9*cos(theta2);

        double D = -0.5*cos(theta2) - 2.9375;
        double E = -2*sin(theta2);
        double F = 1.5625 + 0.5*cos(theta2);

        double x = newton(A,B,C,x_guess);
        double y = newton(D,E,F,y_guess);

        x_guess=x; y_guess=y;

        double theta4=2*atan(x);
        double theta3=2*atan(y);

        // --- velocities ---
        double omega3=(a*omega2/b)*
            (sin(theta4-theta2)/sin(theta3-theta4));

        double omega4=(a*omega2/c)*
            (sin(theta2-theta3)/sin(theta4-theta3));

        velFile<<t<<" "<<omega3<<" "<<omega4<<endl;

        // --- accelerations ---
        double A1=c*sin(theta4);
        double B1=b*sin(theta3);
        double D1=c*cos(theta4);
        double E1=b*cos(theta3);

        double C1=a*omega2*omega2*cos(theta2)
                 +b*omega3*omega3*cos(theta3)
                 -c*omega4*omega4*cos(theta4);

        double F1=-a*omega2*omega2*sin(theta2)
                 -b*omega3*omega3*sin(theta3)
                 +c*omega4*omega4*sin(theta4);

        double denom=(A1*E1-B1*D1);

        double alpha3=(C1*D1-A1*F1)/denom;
        double alpha4=(C1*E1-B1*F1)/denom;

        accFile<<t<<" "<<alpha3<<" "<<alpha4<<endl;

        // =========================
        // Part C: Point Velocity & Acceleration
        // =========================

        // Point A
        double Ax=a*cos(theta2);
        double Ay=a*sin(theta2);

        double vAx=-a*omega2*sin(theta2);
        double vAy=a*omega2*cos(theta2);

        double aAx=-a*omega2*omega2*cos(theta2);
        double aAy=-a*omega2*omega2*sin(theta2);

        // r_PA
        double rPx=L*cos(theta3+alpha);
        double rPy=L*sin(theta3+alpha);

        // Velocity of P
        double vPx=vAx - omega3*rPy;
        double vPy=vAy + omega3*rPx;

        double vP=sqrt(vPx*vPx+vPy*vPy);

        // Acceleration of P
        double aPx=aAx - alpha3*rPy - omega3*omega3*rPx;
        double aPy=aAy + alpha3*rPx - omega3*omega3*rPy;

        double aP=sqrt(aPx*aPx+aPy*aPy);

        pointFile<<t<<" "<<vP<<" "<<aP<<endl;
    }

    velFile.close();
    accFile.close();
    pointFile.close();

    cout<<"All data generated.\n";
    return 0;
}