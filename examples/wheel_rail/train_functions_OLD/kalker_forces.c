#include <stdio.h>
#include <math.h>
#define printf mexPrintf
void kalker_forces (double * output, int pos_vx, double * param, int pos_c11, int pos_a, int pos_G, double * inputs, int pos_fx ){

 
    /*double Vx  = output[pos_vx + 0];
    double Vy  = output[pos_vx + 1];
    double Phi = output[pos_vx + 2];*/
    double Vx,Vy, Phi;

    if ( fabs(output[pos_vx + 0]) < 1e-6 ) {
      Vx  = 0;
    }
    else{
      Vx  = output[pos_vx + 0] / fabs(0.5* ( output[pos_vx + 4] + output[pos_vx + 3] * output[pos_vx + 5] ) );
      Vy  = output[pos_vx + 1] / fabs(0.5* ( output[pos_vx + 4] + output[pos_vx + 3] * output[pos_vx + 5] ) );
      Phi = output[pos_vx + 2] / fabs(0.5* ( output[pos_vx + 4] + output[pos_vx + 3] * output[pos_vx + 5] ) );
    } 


    /*
    |Fx|                 | C11  0               0             |   |Vx |
    |Fy| = - G * a * b * | 0    C22             sqrt(a*b)*C23 | * |Vy |
    |Mz|                 | 0    -sqrt(a*b)*C23  a*b*C33       |   |Phi|
    */


    inputs[pos_fx]   = - 1e-3*param[pos_G]*param[pos_a]*param[pos_a+1] * ( param[pos_c11] * Vx);
    inputs[pos_fx+1] = - 1e-3*param[pos_G]*param[pos_a]*param[pos_a+1] * ( param[pos_c11+1]*Vy + sqrt(param[pos_a]*param[pos_a+1])*param[pos_c11+2]*Phi);
    inputs[pos_fx+2] = - 1e-3*param[pos_G]*param[pos_a]*param[pos_a+1] * ( -sqrt(param[pos_a]*param[pos_a+1])*param[pos_c11+2]*Vy + param[pos_a] * param[pos_a+1] * param[pos_c11+3] * Phi );

/*
printf("===============================\n");
printf("Vx = %f\n",Vx);
printf("Vy = %f\n",Vy );
printf("Phi = %f\n",Phi );
printf("C22= %f\n",param[pos_c11+1]);
printf("C23= %f\n",param[pos_c11+2]);
printf("a  = %f\n",param[pos_a] );
printf("b  = %f\n", param[pos_a+1]);
printf("G  = %f\n", param[pos_G]);
printf("Fx  = %f\n", inputs[pos_fx]);
printf("Fy  = %f\n", inputs[pos_fx+1]);
printf("Mz  = %f\n", inputs[pos_fx+2]);*/


}
