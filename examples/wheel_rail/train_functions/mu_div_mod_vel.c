#include <math.h>
#include <stdio.h>
//void mu_div_mod_vel (double * vel_ms , double * mu_V){
double mu_div_mod_vel (double vel_ms){
   
   int rain = 1;

   double a_w1 = 1.0;    double a_w2 = 0.54; 
   double b_w1 = 4.01;   double b_w2 = 1.2;
   double c_w1 = 0.7;    double c_w2 = 0.29; 
   double d_w1 = 0.7;    double d_w2 = 0.29; 

   double epsilon=0.0001;

   double vel;
   double mu_V;

   vel = vel_ms * 3.6;


    if (rain == 1){
        if (fabs(vel)<=epsilon){
            mu_V = (b_w1*d_w1)/exp(b_w1*fabs(vel)) - (a_w1*c_w1)/exp(a_w1*fabs(vel));
        }
        else{
            mu_V = +(c_w1*exp(-a_w1*fabs(vel))-d_w1*exp(-b_w1*fabs(vel)))/fabs(vel);

        };
    }
    else{
        if (fabs(vel)<=epsilon){
           mu_V =(b_w2*d_w2)/exp(b_w2*fabs(vel)) - (a_w2*c_w2)/exp(a_w2*fabs(vel));
        }
        else{
           mu_V =+(c_w2*exp(-a_w2*fabs(vel))-d_w2*exp(-b_w2*fabs(vel)))/fabs(vel); 
        };
    }
    return mu_V;

}
