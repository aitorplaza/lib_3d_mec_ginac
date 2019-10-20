#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdarg.h>
#include <ginac/ginac.h>
//class System;

using GiNaC::ex;
using GiNaC::symbol;
using GiNaC::matrix;
using GiNaC::lst;
using GiNaC::wild;
using GiNaC::exvector;
using GiNaC::relational;
using std::string;
using std::ostream;
using std::vector;

	class Matrix{

	protected:

		//Atributes

		string name;
		matrix mat;
		//System *system;
		long last_row;
		long last_col;

		//Protected methods


		//Protected constructor

	private:

		//Private methods

		void init ( string name , matrix mat );
		static Matrix Operations ( const Matrix & MatrixA , const Matrix & MatrixB , int flag );
		static Matrix Operations ( const Matrix & MatrixA , const ex & expression , int flag );

	public:

		//Constructors

		Matrix ( matrix mat );
		Matrix (){name="";}
		Matrix ( string name , Matrix mat );
		Matrix ( string name , long rows , long cols );
		Matrix ( long rows , long cols );
		Matrix ( string name , long rows , long cols , ex * first , ... );
		Matrix ( long rows , long cols , ex * first , ... );
		Matrix ( string name, long rows , long cols , Matrix * first , ... );
		Matrix ( long rows , long cols , Matrix * first , ... );
		Matrix ( long rows, long cols, const vector<Matrix*>&);
		Matrix ( long rows , long cols , lst expressions_list );
		Matrix ( lst expressions_list );
		Matrix ( string name , lst expression_list );

		//Access methods

		string get_name ( void );
		//System * get_System ( void );
		matrix get_matrix ( void );
		void set_matrix ( matrix new_mat );

		void set_name ( string new_name );
		//void set_System ( System * new_system );

		//Methods

		Matrix transpose ( void );
		//Matrix Dt ( void );
		Matrix subs ( relational relation );
		Matrix expand ( void );
		ex& operator () ( const long row , const long col );
		long rows ( void );
		long cols ( void );
        Matrix get_col ( int j );
        Matrix get_row ( int i );
        void set_col ( const int j , Matrix VectorC );
        void set_row ( const int i , Matrix VectorR );
        Matrix remove_col ( int jth );
        Matrix remove_row ( int i );

		void set(int row, int col, const ex& value);
		ex& get(int row, int col);


		//Operators

		friend Matrix operator + ( const Matrix & MatrixA , const Matrix & MatrixB );
		friend Matrix operator - ( const Matrix & MatrixA , const Matrix & MatrixB );
		friend Matrix operator - ( const Matrix & MatrixA );
		friend Matrix operator * ( const Matrix & MatrixA , const Matrix & MatrixB );
		friend Matrix operator * ( const ex & expression , const Matrix & MatrixA );
		friend Matrix operator * ( const Matrix & MatrixA , const ex & expression );
		Matrix& operator = ( const ex & expression );
		Matrix& operator , ( const ex & expression );
		friend ostream & operator << ( ostream & , const Matrix & MatrixA );

		//Destructor

		~Matrix ( void );
	};

#endif // MATRIX_H
