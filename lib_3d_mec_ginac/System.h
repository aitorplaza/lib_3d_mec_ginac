#ifndef SYSTEM_H
#define SYSTEM_H

#include "Base.h"
#include "Vector3D.h"
#include "Tensor3D.h"
#include "Frame.h"
#include "Point.h"
#include "symbol_numeric.h"
#include "Solid.h"
#include "Wrench3D.h"
#include "Drawing3D.h"
#include "VectorE.h"

#include <ginac/ginac.h>
//#include <gsl/gsl_vector.h>
//#include <gsl/gsl_matrix.h>

extern Point * Point_O;
extern Base * Base_xyz;
extern Frame * Frame_abs;
extern Solid * Ground;
extern symbol_numeric * g;

extern exhashmap < ex > atom_hashmap;


using GiNaC::ex;
using GiNaC::matrix;
using GiNaC::symbol;
using GiNaC::lst;
using GiNaC::numeric;
using std::string;
using std::vector;

class System{

        //Atributes

        symbol_numeric t;
        vector < symbol_numeric * > coordinates; //q
        vector < symbol_numeric * > velocities; //dq
        vector < symbol_numeric * > accelerations; //ddq

        vector < symbol_numeric * > aux_coordinates; //q_aux
        vector < symbol_numeric * > aux_velocities; //dq_aux
        vector < symbol_numeric * > aux_accelerations; //ddq_aux

        vector < symbol_numeric * > parameters;
        vector < symbol_numeric * > unknowns;
        vector < symbol_numeric * > inputs;

        vector < Base * > Bases;
        vector < Matrix * > Matrixs;
        vector < Vector3D * > Vectors;
        vector < Tensor3D * > Tensors;
        vector < VectorE * > VectorEs;
        vector < Frame * > Frames;
        vector < Point * > Points;
        vector < Solid * > Solids;
        vector < Wrench3D * > Wrenches;
        vector < Drawing3D * > Drawings;


    private:

        //Private methods

        int can_Erase_Point ( string point_name );
        int can_Erase_Base ( string base_name );
        int can_Erase_Vector3D ( string Vector3D_name );
        Matrix Rec_Rotation_Matrix (  Base * BaseA , Base * BaseB );
        //Vector3D Angular_Velocity_Aux ( Base * BaseA , Base * BaseB );
        void Rec_Angular_Velocity (  Base * BaseA , Base * BaseB  , Vector3D & Vomega);
        //Vector3D Position_Vector_Aux ( Point * PointA , Point * PointB );
        void Rec_Position_Vector ( Point * PointA , Point * PointB , Vector3D & Vpos );
        //Vector3D Velocity_Vector_Aux ( Point * PointA , Point * PointB );
        void Rec_Velocity_Vector ( Frame * FrameF , Point * PointF , Point * PointO, Vector3D & Vvel );
        //Matrix Rotation_Matrix_Aux ( Base * BaseA , Base * BaseB );
        void Rec_Angular_Acceleration (  Base * BaseA , Base * BaseB  , Vector3D & Valpha);
        int Bases_Position ( Base * BaseA , Base * BaseB );
        int Points_Position ( Point * PointA , Point * PointB );
        void init ( void  ( * func ) ( const char * ) );

    public:
        //void Rec_Position_Vector ( Point * PointA , Point * PointB , Vector3D & Vpos );
        //void Rec_Angular_Velocity (  Base * BaseA , Base * BaseB  , Vector3D & Vomega);
        //Vector3D Angular_Velocity_Tables ( Base * BaseA , Base * BaseB, map  < Base*, Vector3D > &OM_abs );
        //Matrix Rec_Rotation_Matrix (  Base * BaseA , Base * BaseB );
        //void Rec_Velocity_Vector ( Frame * FrameF , Point * PointF , Point * PointO, Vector3D & Vvel );

        //Constructors

        System ( void );
        System ( void  ( * func ) ( const char * ) );

        //Public methods

        symbol_numeric * new_Coordinate ( symbol_numeric * coord , symbol_numeric * vel , symbol_numeric * accel );

        symbol_numeric * new_Coordinate ( string coord_name , string vel_name , string accel_name , numeric coord_value , numeric vel_value , numeric accel_value );
        symbol_numeric * new_Coordinate ( string coord_name , numeric coord_value , numeric vel_value , numeric accel_value );
        symbol_numeric * new_Coordinate ( string coord_name , numeric coord_value , numeric vel_value );
        symbol_numeric * new_Coordinate ( string coord_name , numeric coord_value );
        symbol_numeric * new_Coordinate ( string coord_name );

        symbol_numeric * new_Coordinate ( string coordinate_name , string velocity_name , string acceleration_name , string coordinate_name_tex , string velocity_name_tex , string acceleration_name_tex , numeric coordinate_value , numeric velocity_value , numeric acceleration_value );
        symbol_numeric * new_Coordinate ( string coordinate_name , string coordinate_name_tex , numeric coordinate_value , numeric velocity_value , numeric acceleration_value );

        symbol_numeric * new_AuxCoordinate ( symbol_numeric * aux_coord , symbol_numeric * aux_vel , symbol_numeric * aux_accel );
        symbol_numeric * new_AuxCoordinate ( string aux_coord_name , string aux_vel_name , string aux_accel_name , numeric aux_coord_value , numeric aux_vel_value , numeric aux_accel_value );
        symbol_numeric * new_AuxCoordinate ( string aux_coordinate_name , string aux_velocity_name , string aux_acceleration_name , string aux_coordinate_name_tex , string aux_velocity_name_tex , string aux_acceleration_name_tex , numeric aux_coordinate_value , numeric aux_velocity_value , numeric aux_acceleration_value );

        symbol_numeric * new_Parameter ( symbol_numeric * parameter );
        symbol_numeric * new_Parameter ( symbol_numeric * parameter , numeric parameter_value );
        symbol_numeric * new_Parameter ( string parameter_name , numeric parameter_value );
        symbol_numeric * new_Parameter ( string parameter_name );

        symbol_numeric * new_Parameter ( string parameter_name , string parameter_name_tex , numeric parameter_value );
        symbol_numeric * new_Parameter ( string parameter_name , string parameter_name_tex );

        symbol_numeric * new_Joint_Unknown ( symbol_numeric * joint_unknown );
        symbol_numeric * new_Joint_Unknown ( string joint_unknown_name );
        symbol_numeric * new_Joint_Unknown ( string joint_unknown_name , numeric joint_unknown_value );

        symbol_numeric * new_Joint_Unknown ( string joint_unknown_name , string joint_unknown_name_tex , numeric joint_unknown_value );
        symbol_numeric * new_Joint_Unknown ( string joint_unknown_name , string joint_unknown_name_tex);

        symbol_numeric * new_Input ( symbol_numeric * input );
        symbol_numeric * new_Input ( string input_name , numeric input_value );
        symbol_numeric * new_Input ( string input_name , string input_name_tex , numeric input_value );
        symbol_numeric * new_Input ( string input_name );
        symbol_numeric * new_Input ( string input_name , string input_name_tex);

        void new_Base ( Base * BaseA );
        Matrix * new_Matrix ( Matrix * MatrixA );
        void new_Vector3D ( Vector3D * Vector3DA );
        void set_Time_Symbol ( symbol_numeric timesymbol );

        Base * new_Base ( string name , Base * previous_base , Matrix rotation_tupla , ex rotation_angle );
        Base * new_Base ( string , string previous_base_name , Matrix rotationmatrix , ex rotation_angle );
        Base * new_Base ( string name , string previous_base_name , ex expression1 , ex expression2 , ex expression3 , ex rotation_angle );
        Vector3D * new_Vector3D ( string name , Matrix mat , Base * base );
        Vector3D * new_Vector3D ( string name , Matrix mat , string base_name );
        Vector3D * new_Vector3D ( string name , Matrix * mat , string base_name );
        Vector3D * new_Vector3D ( string name , ex expression1 , ex expression2 , ex expression3 , Base * base );
        Vector3D * new_Vector3D ( string name , ex expression1 , ex expression2 , ex expresion3 , string base_name );

        Tensor3D * new_Tensor3D ( string name , Matrix * mat , Base * base );
        Tensor3D * new_Tensor3D ( string name , ex exp1 , ex exp2 , ex exp3 , ex exp4 , ex exp5 , ex exp6 , ex exp7 , ex exp8 , ex exp9 , Base * base );
        Tensor3D * new_Tensor3D ( string name , ex exp1 , ex exp2 , ex exp3 , ex exp4 , ex exp5 , ex exp6 , ex exp7 , ex exp8 , ex exp9 , string base_name );

        Point * new_Point ( string name , Point * previous_point , Vector3D * position_vector );
        Point * new_Point ( string name , string previous_point_name , Vector3D * position_vector );
        Point * new_Point ( string name , string p , ex exp1 , ex exp2 , ex exp3 , string s_base  );


        Frame * new_Frame ( string name , Point * point , Base * base );
        Frame * new_Frame ( string name , string point_name , string base_name );

        VectorE  * new_VectorE ( string name ) ;


        Solid * new_Solid ( string name , Point * point , Base * base, symbol_numeric * new_mass , Vector3D * new_CM, Tensor3D * new_IT);
        Solid * new_Solid ( string name , string s_Point , string s_Base, string s_mass , string s_CM, string s_IT);
        Solid * new_Solid ( string name , string s_Point , string s_Base, symbol_numeric * new_mass , string s_CM, string s_IT);


        Wrench3D * new_Wrench3D ( string name , Vector3D F , Vector3D M , Point * P , Solid * Sol, string type);
        Wrench3D * new_Wrench3D ( string name , string s_F , string s_M , string s_P, string s_Sol, string type);
        Wrench3D * new_Wrench3D (string s_name, ex f1, ex f2, ex f3, string s_baseF, ex m1, ex m2, ex m3, string s_baseM, string s_P, string s_Sol, string type );
        Wrench3D * new_Wrench3D ( string name , Vector3D F , Vector3D M , Point * P, Solid * Sol1, Solid * Sol2, string type);
        Wrench3D * new_Wrench3D ( string name , string s_F , string s_M , string s_P, string s_Sol1, string s_Sol2, string type);
        Wrench3D * new_Wrench3D(string s_name, ex f1, ex f2, ex f3, string s_baseF, ex m1, ex m2, ex m3, string s_baseM, string s_P, string s_Sol1, string s_Sol2, string type );


        Drawing3D * new_Drawing3D ( string s_name , Solid * Sol, string new_file, numeric r, numeric g,numeric b,numeric alpha );
        Drawing3D * new_Drawing3D ( string s_name , string s_Sol, string new_file, numeric r, numeric g,numeric b,numeric alpha );
        Drawing3D * new_Drawing3D ( string s_name , string s_point , string s_base ,string file_name, numeric r, numeric g,numeric b,numeric alpha);
        Drawing3D * new_Drawing3D ( string s_name , Solid * Sol, string new_file );
        Drawing3D * new_Drawing3D ( string s_name , string s_Sol, string new_file );
        Drawing3D * new_Drawing3D ( string s_name , string s_point , string s_base ,string file_name);
        Drawing3D * new_Drawing3D ( string s_name , Frame * Fra, numeric scale );
        Drawing3D * new_Drawing3D ( string s_name , string s_Fra, numeric scale );
        Drawing3D * new_Drawing3D ( string s_name , Point * Pnt, numeric scale );
        Drawing3D * new_Drawing3D ( string s_name , Point * Pnt, numeric scale, numeric r, numeric g,numeric b,numeric alpha );
        Drawing3D * new_Drawing3D ( string s_name , Vector3D * Vec, Point * Pnt, numeric r, numeric g,numeric b,numeric alpha);
        Drawing3D * new_Drawing3D ( string s_name ,Vector3D * Vec, Point * Pnt);

        Matrix * new_Matrix ( string name , Matrix mat );

        symbol_numeric get_Time_Symbol ( void );

        vector < symbol_numeric * > get_Coordinates ( void );
        vector < symbol_numeric * > get_Velocities ( void );
        vector < symbol_numeric * > get_Accelerations ( void );
        vector < symbol_numeric * > get_AuxCoordinates ( void );
        vector < symbol_numeric * > get_AuxVelocities ( void );
        vector < symbol_numeric * > get_AuxAccelerations ( void );
        vector < symbol_numeric * > get_Parameters ( void );
        vector < symbol_numeric * > get_Joint_Unknowns ( void );
        vector < symbol_numeric * > get_Inputs ( void );

        vector < Base * > get_Bases ( void );
        vector < Matrix * > get_Matrixs ( void );
        vector < Vector3D * > get_Vectors ( void );
        vector < Tensor3D * > get_Tensors ( void );
        vector < Point * > get_Points ( void );
        vector < Frame * > get_Frames ( void );
        vector < Solid * > get_Solids ( void );
        vector < Wrench3D * > get_Wrenches ( void );
        vector < Drawing3D * > get_Drawings ( void );

        Matrix Coordinates ( void );
        Matrix Accelerations ( void );
        Matrix Velocities ( void );
        Matrix Aux_Coordinates ( void );
        Matrix Aux_Accelerations ( void );
        Matrix Aux_Velocities ( void );
        Matrix Parameters ( void );
        Matrix Joint_Unknowns ( void );
        Matrix Inputs ( void );

        symbol_numeric * get_Coordinate ( string coordinate_name );
        symbol_numeric * get_Velocity ( string velocity_name );
        symbol_numeric * get_Acceleration ( string acceleration_name );
        symbol_numeric * get_AuxCoordinate ( string aux_coordinate_name );
        symbol_numeric * get_AuxVelocity ( string aux_velocity_name );
        symbol_numeric * get_AuxAcceleration ( string aux_acceleration_name );
        symbol_numeric * get_Parameter ( string parameter_name );
        symbol_numeric * get_Unknown ( string joint_unknown_name );
        symbol_numeric * get_Input ( string input_name );

        Base * get_Base ( string base_name );
        Frame * get_Frame ( string frame_name );
        Solid * get_Solid ( string solid_name );
        Tensor3D * get_Tensor3D ( string tensor3D_name );
        Matrix * get_Matrix ( string Matrix_name );
        Vector3D * get_Vector3D ( string vector3D_name );
        Point * get_Point ( string point_name );
        Wrench3D * get_Wrench3D  ( string wrench_name );
        Drawing3D * get_Drawing3D  ( string drawing_name );


        /******************** Kinematic Operators Methods ********************/

        Base * Reduced_Base ( string BaseA_name , string BaseB_name );
        Base * Reduced_Base ( Base * BaseA , Base * BaseB );
        Point * Reduced_Point ( string PointA_name , string PointB_name );
        Point * Reduced_Point ( Point * PointA , Point * PointB );

        Point *	Pre_Point_Branch( Point * PointA , Point * PointB );

        Matrix Rotation_Matrix ( Base * BaseA , Base * BaseB );
        Matrix Rotation_Matrix ( string  base_frame_nameA , string  base_frame_nameB );

        Vector3D Position_Vector ( Point * PointA , Point * PointB );
        Vector3D Position_Vector ( string PointA_name , string PointB_name );

        Vector3D Angular_Velocity ( Base * BaseA , Base * BaseB );
        Vector3D Angular_Velocity ( string  base_frame_nameA , string  base_frame_nameB );
        Tensor3D Angular_Velocity_Tensor ( Base * BaseA , Base * BaseB );

        Vector3D Velocity_Vector (Frame * FrameF , Point * PointB );//recursive
        Vector3D Velocity_Vector (string Frame_name , string PointA_name );
        Vector3D Velocity_Vector (Frame * FrameF , Point * PointB, Solid * Sol );
        Vector3D Velocity_Vector (string Frame_name , string PointA_name, string Solid_name );


        Vector3D Angular_Acceleration ( Base * BaseA , Base * BaseB );
        Vector3D Angular_Acceleration ( string  base_frame_nameA , string  base_frame_nameB );

        Vector3D Acceleration_Vector (Frame * FrameF , Point * PointB );//recursive
        Vector3D Acceleration_Vector (string Frame_name , string PointA_name );
        Vector3D Acceleration_Vector (Frame * FrameF , Point * PointB, Solid * SolS );
        Vector3D Acceleration_Vector (string Frame_name , string PointA_name, string Solid_name );



        void remove_Matrix ( string matrix_name );
        void remove_Vector3D ( string vector3D_name );
        void remove_Point ( string point_name );
        void remove_Base ( string base_name );

        ex dt ( ex expression );
        Vector3D dt ( Vector3D Vector3DA);
        Matrix Dt ( Matrix MatrixA );
        Vector3D Dt ( Vector3D Vector3DA , Base * base );
        Vector3D Dt ( Vector3D Vector3DA , Frame * frame );
        Vector3D Dt ( Vector3D Vector3DA , string base_frame_name );

        Matrix jacobian ( Matrix MatrixA , Matrix MatrixB, ex symmetric );
        Matrix jacobian ( Matrix MatrixA , Matrix MatrixB);
        Matrix jacobian ( ex , Matrix MatrixA );
        Matrix jacobian ( Matrix MatrixA , symbol symbolA );
        ex jacobian ( ex expression , symbol symbolA );
        ex diff ( ex expression , symbol symbolA );
        Matrix diff ( Matrix MatrixA , symbol symbolA );
        Vector3D diff ( Vector3D Vector3DA , symbol symbolA );
        Tensor3D diff ( Tensor3D Tensor3DA , symbol symbolA );
        ex diff ( ex expression , string symbol_name );
        Matrix diff ( Matrix MatrixA , string symbol_name );
        Vector3D diff ( Vector3D Vector3DA , string symbol_name );
        Tensor3D diff ( Tensor3D Tensor3DA , string symbol_name );
        ex numeric_evaluate ( ex expression );
        Matrix evaluate_Matrix ( Matrix MatrixA );

/******************** Solid Methods ********************/
        Vector3D get_SOL_Omega (Solid * Sol);
        Vector3D get_SOL_Velocity (Solid * Sol);
        Vector3D get_SOL_GC_Velocity (Solid * Sol);

        Wrench3D * Gravity_Wrench(Solid * Sol);
        Wrench3D * Inertia_Wrench(Solid * Sol);
        Wrench3D * Gravity_Wrench(string Solid_name);
        Wrench3D * Inertia_Wrench(string Solid_name);

/******************** Wrench3D Methods ********************/
        Matrix GenForce(Wrench3D * wrench);
        Matrix GenForceSys(string Wrench_type);


/******************** Export functions ********************/

        void export_time_C ( void );
        void export_var_def_C ( void );
        //~ void export_var_def_C_GSL ( void );

        void export_time_H ( void );
        void export_var_def_H ( void );
        //~ void export_var_def_H_GSL ( void );

        void export_var_init_C ( void );
        //~ void export_var_init_C_GSL ( void );

        void export_atom_def_C ( lst atom_list );
        //~ void export_atom_def_C_GSL ( lst atom_list );

        void export_gen_coord_H ( void );
        void export_gen_coord_vect_def_H ( void );
        //~ void export_gen_coord_vect_def_H_GSL ( void );

        void export_gen_coord_C ( void );
        void export_gen_coord_vect_init_C ( void );
        //~ void export_gen_coord_vect_init_C_GSL ( void );

        void export_gen_vel_H ( void );
        void export_gen_vel_vect_def_H ( void );
        //~ void export_gen_vel_vect_def_H_GSL ( void );

        void export_gen_vel_C ( void );
        void export_gen_vel_vect_init_C ( void );
        //~ void export_gen_vel_vect_init_C_GSL ( void );

        void export_gen_accel_H ( void );
        void export_gen_accel_vect_def_H ( void );
        //~ void export_gen_accel_vect_def_H_GSL ( void );

        void export_gen_accel_C ( void );
        void export_gen_accel_vect_init_C ( void );
        //~ void export_gen_accel_vect_init_C_GSL ( void );

        void export_gen_auxcoord_H ( void );
        void export_gen_auxcoord_C ( void );

        void export_gen_auxvel_H ( void );
        void export_gen_auxvel_C ( void );

        void export_gen_auxaccel_H ( void );
        void export_gen_auxaccel_C ( void );

        void export_param_H ( void );
        void export_param_C ( void );
        void export_param_vect_def_H ( void );
        void export_param_vect_init_C ( void );

        void export_unknowns_H ( void );
        void export_unknowns_vect_def_H ( void );
        //~ void export_unknowns_vect_def_H_GSL ( void );

        void export_unknowns_C ( void );
        void export_unknowns_vect_init_C ( void );
        //~ void export_unknowns_vect_init_C_GSL ( void );

        void export_inputs_H ( void );
        void export_inputs_vect_def_H ( void );
        //~ void export_inputs_vect_def_H_GSL ( void );

        void export_inputs_C ( void );
        void export_inputs_vect_init_C ( void );
        //~ void export_inputs_vect_init_C_GSL ( void );

        void export_Column_Matrix_C ( string , string , Matrix , lst );
        //~ void export_Column_Matrix_C_GSL ( string , string , Matrix , lst );

        void export_Matrix_C ( string , string , Matrix , lst );
        void export_Matrix_C ( string , string , Matrix , lst , lst , int );
        void export_Matrix_C ( string , string , Matrix , int );
        //~ void export_Matrix_C_GSL ( string , string , Matrix , lst );
        //~ void export_Matrix_C_GSL ( string , string , Matrix , lst , int );

        void export_write_data_file_H ( void );
        void export_write_data_file_C ( void );
        void export_write_data_file_C ( lst expresion_list  );

        void export_read_data_file_H ( void );
        void export_read_data_file_C ( lst expresion_list  );


        void export_write_state_file_header_C ( void );
        //~ void export_write_state_file_header_C_GSL ( void );

        void export_write_state_file_C ( void );
        //~ void export_write_state_file_C_GSL ( void );

        void export_write_state_file_header_C ( lst expresion_list  );
        //~ void export_write_state_file_header_C_GSL ( lst expresion_list  );

        void export_write_state_file_C ( lst expresion_list  );
        //~ void export_write_state_file_C_GSL ( lst expresion_list  );



        /* Export function to matlab to simplify expressions */
        void export_init_function_MATLAB();
        void export_function_MATLAB(string function_name, string function_out, Matrix symbolic_matrix_function);
        void export_function_MATLAB(string function_name, string function_out, Matrix symbolic_matrix_function, string s_in);
        void export_function_MATLAB(string function_name, string function_out, Matrix symbolic_matrix_function, lst Matrix_atom_list, lst Matrix_atom_expression_list);
        void export_function_MATLAB(string function_name, string function_out, Matrix symbolic_matrix_function, lst Matrix_atom_list, lst Matrix_atom_expression_list, string s_in);

        void export_function_MATLAB_SYMPY(string function_name, string function_out, Matrix symbolic_matrix_function);

        /* Export function to maple to atomize expressions */
        void export_Matrix_MAPLE ( string , vector < string >   , vector < Matrix * > , vector < string > , vector < string > , int order, int symmetric);
        void export_Matrix_MAPLE ( string , vector < string >   , vector < Matrix * > , vector < string > , vector < string > , int order);

        void export_Matrix_MAPLE ( string , vector < Matrix * > , vector < string > , vector < string > , int order, int symmetric);
        void export_Matrix_MAPLE ( string , vector < Matrix * > , vector < string > , vector < string > , int order);

        void export_Matrix_MAPLE ( string , vector < Matrix * > , vector < string > , int order, int symmetric);
        void export_Matrix_MAPLE ( string , vector < Matrix * > , vector < string > , int order);

        void export_Matrix_MAPLE ( string , vector < Matrix * > , int order, int symmetric);
        void export_Matrix_MAPLE ( string , vector < Matrix * > , int order);

        void export_Matrix_MAPLE ( string , string, Matrix, int order, int symmetric);
        void export_Matrix_MAPLE ( string , string, Matrix, int order);

        void load_includes_defines(string, int order);
        void make_argument_standard_list ( vector < string > , string &aux);
        void make_argument_matrixes_list ( vector < string > , string &aux);


        /* Export defines.h*/
        void export_defines ( void );

        /* Export Graphviz files*/
        void export_Graphviz_dot ( void );

        /* Export environment.m file*/
        void export_environment_m ( void );

        /* Export config.ini file*/
        void export_config_ini ( void );
        void export_param_ini ( void );
        void export_inputs_ini ( void );
        void export_gen_coord_ini ( void );
        void export_gen_vel_ini ( void );

        /* Export OSG files */
        void export_solids_homogeneous_matrix_cpp ( void );
        void export_solids_homogeneous_matrix_h ( void );
        void export_osg_read_file_cpp ( void );
        void export_osg_read_file_h ( void );
        void export_osg_root_cpp ( void );
        void export_osg_root_h ( void );
        void export_osg_state_cpp ( void );
        void export_osg_state_h ( void );

        void export_open_scene_graph( void );

        /* Export GNUplot files */
        void export_gnuplot( lst expresion_list );


        /* SYSTEM MATRIX CALCULATION and EXPORTATION */
        void Matrix_Calculation(Matrix &Phi, lst coord_indep_init ,lst vel_indep_init , Matrix &Dynamic_Equations, System &sys, int method, Matrix &dPhiNH);
        void Matrix_Calculation(Matrix &Phi, lst coord_indep_init ,lst vel_indep_init , Matrix &Dynamic_Equations, System &sys, int method);
        void Matrix_Calculation(             lst coord_indep_init ,lst vel_indep_init , Matrix &Dynamic_Equations, System &sys, int method);
        void Matrix_Calculation(lst coord_indep_init ,lst vel_indep_init ,System &sys, int method);
        void Matrix_Calculation(Matrix &Phi,lst coord_indep_init ,lst vel_indep_init,  System &sys, int method);
        void Matrix_Calculation(Matrix &Phi, lst coord_indep_init ,lst vel_indep_init ,System &sys, int method, Matrix &dPhiNH);




        void export_Dynamic_Simulation  (System &sys, int order, int maple);


        //Destructor
        ~System ( void );
};

#endif // SYSTEM_H
