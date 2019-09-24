#include <stdio.h>
#include <math.h>
//#define printf mexPrintf



#define a param[pos_a]
#define b param[pos_a+1]
#define G param[pos_G]

#define C11 param[pos_c11]
#define C22 param[pos_c11+1]
#define C23 param[pos_c11+2]
#define C33 param[pos_c11+3]

#define Vx_slip output[pos_vx + 0]
#define Vy_slip output[pos_vx + 1]
#define Omegaz_slip output[pos_vx + 2]

//#define domega output[pos_vx + 3]
//#define dx output[pos_vx + 4]
//#define r output[pos_vx + 5]

#define Vav output[pos_vx + 4]

int sign(int x) {
    return (x > 0) - (x < 0);
}




void kalker_forces (double * output, int pos_vx, double * param, int pos_c11, int pos_a, int pos_G, double * inputs, int pos_fx ){

 
    /*double Vx  = output[pos_vx + 0];
    double Vy  = output[pos_vx + 1];
    double Phi = output[pos_vx + 2];*/

    


    double Vx,Vy, Phi;

    //~ if ( fabs(output[pos_vx + 0]) < 1e-6 ) {  
      //~ Vx  = 0.0; Vy = 0.0; Phi = 0.0; 
    //~ }
 //~ 
    //~ else{
      //Vav=fabs(0.5* ( dx + domega * r ) );
      
      Vav= fabs(Vav);
      double Vcrit=0.005;
      if (Vav==0.0){ Vx  = 0.0; Vy = 0.0; Phi = 0.0; }
      else if (Vav<=Vcrit){Vav=Vcrit;}

      Vx  = Vx_slip / Vav;
      Vy  = Vy_slip / Vav;
      Phi = Omegaz_slip / Vav;
    //~ } 


    /*
    |Fx|                 | C11  0               0             |   |Vx |
    |Fy| = - G * a * b * | 0    C22             sqrt(a*b)*C23 | * |Vy |
    |Mz|                 | 0    -sqrt(a*b)*C23  a*b*C33       |   |Phi|   
    */
    double scale =1;


    
//#define N output[pos_vx -1 ]
//double Vcrit = (0.001/2) * G *a *b*C11 *(N / 9.8 * r* r - 79.60) / (N / 9.8 *79.60 );
//printf ("Vcrict = %f\n", Vcrit);
    
  
    inputs[pos_fx]   = - scale * G * a * b * ( C11 * Vx);
    inputs[pos_fx+1] = - scale * G * a * b * ( C22 * Vy + sqrt(a*b) * C23 * Phi);
    inputs[pos_fx+2] = - scale * G * a * b * ( -sqrt(a*b)* C23 * Vy + a * b * C33 * Phi );

    
    //~ double limit = sqrt(Vx*Vx+Vy*Vy);// + abs(Phi/1000.0);
    //~ printf ("limit = %f\n",limit);
    //~ printf ("a2 = %f\n",a);
    //~ printf ("b2 = %f\n",b);   
    //~ printf ("G = %f\n",G);    
    printf ("Gab = %f\n",G * a * b*C11);
    printf ("Gab = %f\n",G * a * b*C22);    
    //~ printf ("Vx = %f\n",Vx);
    //~ printf ("Vy = %f\n",Vy);
    //~ printf ("C11 = %f\n",C11);    
    //~ printf ("============ \n");


}
