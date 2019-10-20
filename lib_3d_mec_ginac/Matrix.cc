#include "Globals.h"
#include "Matrix.h"

using GiNaC::ex;
using GiNaC::matrix;
using GiNaC::lst;
using GiNaC::relational;
using GiNaC::symbol;
using std::string;
using std::ostream;
using std::exception;

int atomization;

/*
Method that initialize the Matrix atributes
*/
void Matrix::init ( string name , matrix mat ) {
	this-> name = name;
	this-> mat = mat;
	this-> last_row = 0;
	this-> last_col = 0;
//	this-> system = NULL;
	* this = atomize ( * this );
}


/*
Constructor with name and one matrix
*/
Matrix::Matrix ( string name , Matrix mat ) {
	init ( name , mat.get_matrix () );
}


/*
Constructor with one matrix
*/
Matrix::Matrix ( matrix mat ) {
	init ( "" , mat );
}


/*
Constructor with name and number of rows and cols initilized by 0'name
*/
Matrix::Matrix ( string name , long rows , long cols ) {
	init ( name , matrix ( rows , cols ) );
}


/*
Constructor with number of rows and cols initilized by 0'name
*/
Matrix::Matrix ( long rows , long cols ) {
	init ( "" , matrix ( rows , cols ) );
}


/*
Constructor with name , number of rows and cols and the values of this
*/
Matrix::Matrix ( string name , long rows , long cols , ex * first , ... ) {
	try{
		int j = 1;

		this-> name = name;
		matrix aux ( rows , cols );
		aux ( 0 , 0 ) = * first;
		/* Classic form of catch a elements from a function with a undefined number of parameters*/
		va_list marcador;
		va_start ( marcador , first );
		for ( int i = 0 ; i < aux.rows () ; i++ ) {
			while ( j < aux.cols () ) {
				ex * exClase = va_arg ( marcador , ex * );
				aux ( i , j ) = * exClase;
				j++;
			}
			j = 0;
		}
		va_end ( marcador );
		mat = aux;
//		system = NULL;
		* this = atomize ( * this );
	}catch ( exception & p ) {
  		outError ( "ERR - Unspected error building Matrix" );
	}
}



/*
Constructor with number of rows and cols and the values of this
*/
Matrix::Matrix ( long rows , long cols , ex * first , ... ) {
	try{
		int j = 1;

		name = "";
		matrix aux ( rows , cols );
		aux ( 0 , 0 ) = * first;
		//Classic form of catch a elements from a function with a undefined number of parameters
		va_list marcador;
		va_start ( marcador , first );
		for ( int i = 0 ; i < aux.rows () ; i++ ) {
			while ( j < aux.cols () ) {
				ex * exClase = va_arg ( marcador , ex * );
				aux ( i , j ) = * exClase;
				j++;
			}
			j = 0;
		}
		va_end ( marcador );
		mat = aux;
//		system = NULL;
		* this = atomize ( * this );
	}catch ( exception & p ) {
  		outError ( "ERR - Unspected error building Matrix" );
	}
}
/*
Constructor with name, number of Matrix in rows and cols for compose a new Matrix with this Matrix
*/
Matrix::Matrix ( string name, long rows , long cols , Matrix * first , ... ) {
	try{

		this -> name = name;

		/* Introduce all the Matrix-es in the auxMatrixs vector*/
		/* Classic form of catch a elements from a function with a undefined number of parameters*/
		vector < Matrix * > auxMatrixs;
		auxMatrixs.push_back ( first );
		va_list marcador;
		va_start ( marcador , first );
		int j = 1;
		for ( int i = 0 ; i < rows ; i++ ) {
			while ( j < cols ) {
				auxMatrixs.push_back ( va_arg ( marcador , Matrix * ) );
				j++;
			}
			j = 0;
		}
		va_end ( marcador );

		//Checks on data and determination of numbre of numRows and numCols of the final Matrix

		if ( rows*cols!=auxMatrixs.size () ) throw 1;

		long int numCols=0;
		long int this_row_number_of_rows;
		for (long int i=0 ; i < rows ; i++)
		{
			for (long int j=0 ; j < cols ; j++)
			{
				if (j==0)
				{
					this_row_number_of_rows=auxMatrixs[i*cols+j]->rows();
					numCols=auxMatrixs[i*cols+j]->cols();
				}
				else
				{
					numCols=numCols+auxMatrixs[i*cols+j]->cols();
					if ( auxMatrixs[i*cols+j]->rows() != this_row_number_of_rows ) throw 2;
				};
			};
		};

		long int numRows = 0;
		long int this_column_number_of_columns;
		for (long int j=0 ; j < cols ; j++)
		{
			for (long int i=0 ; i < rows ; i++)
			{
				if (i==0)
				{
					this_column_number_of_columns=auxMatrixs[i*cols+j]->cols();
					numRows=auxMatrixs[i*cols+j]->rows();
				}
				else
				{
					numRows=numRows+auxMatrixs[i*cols+j]->rows();
					if ( auxMatrixs[i*cols+j]->cols() != this_column_number_of_columns ) throw 3;
				};
			};
		};

		//Create the final matrix with the adecuate number of rows and cols
		matrix aux ( numRows , numCols );

		long int start_block_n=0;
		long int start_block_m=0;
		long int n = 0;
		long int m = 0;

		for ( n = 0 ; n < rows ; n++ ) {
		for ( m = 0 ; m < cols ; m++ ) {
			for ( long int i = 0 ; i < auxMatrixs[n*cols+m]-> rows () ; i++ ) {
			for ( long int j = 0 ; j < auxMatrixs[n*cols+m]-> cols () ; j++ ) {
					//Write the values
					aux ( start_block_n + i , start_block_m + j ) = auxMatrixs[n*cols+m]-> get_matrix () ( i , j );
			}
			}
		start_block_m = start_block_m + auxMatrixs[n*cols+m] -> cols ();
		}
		start_block_m = 0;
		m=m-1;//m gets increased on exit of the for block
		start_block_n = start_block_n + auxMatrixs[n*cols+m] -> rows ();
		}
		start_block_n = 0;

		mat = aux;
//		system = NULL;
		* this = atomize ( * this );
	}catch ( exception &  p ) {
  		outError ( "ERR - Unspected error building Matrix" );
	}catch ( int i ) {
		     if (i==1){outError ( "ERR - number rows*cols different of number of Matrixes" );}
		else if (i==2){outError ( "ERR - Matrixes in a row must have the same number of rows" );}
		else if (i==3){outError ( "ERR - Matrixes in a column must have the same number of columns" );};
	}
}
/*
Constructor with number of Matrix in rows and cols for compose a new matrix with the
given matrices passed on a std::vector.
*/
Matrix::Matrix ( long rows, long cols, const vector<Matrix*>& auxMatrixs) {
	try{

		name = "";

		//Checks on data and determination of numbre of numRows and numCols of the final Matrix

		if ( rows*cols!=auxMatrixs.size () ) throw 1;

		long int numCols=0;
		long int this_row_number_of_rows;
		for (long int i=0 ; i < rows ; i++)
		{
			for (long int j=0 ; j < cols ; j++)
			{
				if (j==0)
				{
					this_row_number_of_rows=auxMatrixs[i*cols+j]->rows();
					numCols=auxMatrixs[i*cols+j]->cols();
				}
				else
				{
					numCols=numCols+auxMatrixs[i*cols+j]->cols();
					if ( auxMatrixs[i*cols+j]->rows() != this_row_number_of_rows ) throw 2;
				};
			};
		};

		long int numRows = 0;
		long int this_column_number_of_columns;
		for (long int j=0 ; j < cols ; j++)
		{
			for (long int i=0 ; i < rows ; i++)
			{
				if (i==0)
				{
					this_column_number_of_columns=auxMatrixs[i*cols+j]->cols();
					numRows=auxMatrixs[i*cols+j]->rows();
				}
				else
				{
					numRows=numRows+auxMatrixs[i*cols+j]->rows();
					if ( auxMatrixs[i*cols+j]->cols() != this_column_number_of_columns ) throw 3;
				};
			};
		};

		//Create the final matrix with the adecuate number of rows and cols
		matrix aux ( numRows , numCols );

		long int start_block_n=0;
		long int start_block_m=0;
		long int n = 0;
		long int m = 0;

		for ( n = 0 ; n < rows ; n++ ) {
		for ( m = 0 ; m < cols ; m++ ) {
			for ( long int i = 0 ; i < auxMatrixs[n*cols+m]-> rows () ; i++ ) {
			for ( long int j = 0 ; j < auxMatrixs[n*cols+m]-> cols () ; j++ ) {
					//Write the values
					aux ( start_block_n + i , start_block_m + j ) = auxMatrixs[n*cols+m]-> get_matrix () ( i , j );
			}
			}
		start_block_m = start_block_m + auxMatrixs[n*cols+m] -> cols ();
		}
		start_block_m = 0;
		m=m-1;//m gets increased on exit of the for block
		start_block_n = start_block_n + auxMatrixs[n*cols+m] -> rows ();
		}
		start_block_n = 0;

		mat = aux;
//		system = NULL;
		* this = atomize ( * this );
	}catch ( exception &  p ) {
  		outError ( "ERR - Unspected error building Matrix" );
	}catch ( int i ) {
		     if (i==1){outError ( "ERR - number rows*cols different of number of Matrixes" );}
		else if (i==2){outError ( "ERR - Matrixes in a row must have the same number of rows" );}
		else if (i==3){outError ( "ERR - Matrixes in a column must have the same number of columns" );};
	}
}


/*
Constructor with number of Matrix in rows and cols for compose a new Matrix with this Matrix
*/
Matrix::Matrix ( long rows , long cols , Matrix * first , ... ) {
	try{

		name = "";

		/* Introduce all the Matrix-es in the auxMatrixs vector*/
		/* Classic form of catch a elements from a function with a undefined number of parameters*/
		vector < Matrix * > auxMatrixs;
		auxMatrixs.push_back ( first );
		va_list marcador;
		va_start ( marcador , first );
		int j = 1;
		for ( int i = 0 ; i < rows ; i++ ) {
			while ( j < cols ) {
				auxMatrixs.push_back ( va_arg ( marcador , Matrix * ) );
				j++;
			}
			j = 0;
		}
		va_end ( marcador );

		//Checks on data and determination of numbre of numRows and numCols of the final Matrix

		if ( rows*cols!=auxMatrixs.size () ) throw 1;

		long int numCols=0;
		long int this_row_number_of_rows;
		for (long int i=0 ; i < rows ; i++)
		{
			for (long int j=0 ; j < cols ; j++)
			{
				if (j==0)
				{
					this_row_number_of_rows=auxMatrixs[i*cols+j]->rows();
					numCols=auxMatrixs[i*cols+j]->cols();
				}
				else
				{
					numCols=numCols+auxMatrixs[i*cols+j]->cols();
					if ( auxMatrixs[i*cols+j]->rows() != this_row_number_of_rows ) throw 2;
				};
			};
		};

		long int numRows = 0;
		long int this_column_number_of_columns;
		for (long int j=0 ; j < cols ; j++)
		{
			for (long int i=0 ; i < rows ; i++)
			{
				if (i==0)
				{
					this_column_number_of_columns=auxMatrixs[i*cols+j]->cols();
					numRows=auxMatrixs[i*cols+j]->rows();
				}
				else
				{
					numRows=numRows+auxMatrixs[i*cols+j]->rows();
					if ( auxMatrixs[i*cols+j]->cols() != this_column_number_of_columns ) throw 3;
				};
			};
		};

		//Create the final matrix with the adecuate number of rows and cols
		matrix aux ( numRows , numCols );

		long int start_block_n=0;
		long int start_block_m=0;
		long int n = 0;
		long int m = 0;

		for ( n = 0 ; n < rows ; n++ ) {
		for ( m = 0 ; m < cols ; m++ ) {
			for ( long int i = 0 ; i < auxMatrixs[n*cols+m]-> rows () ; i++ ) {
			for ( long int j = 0 ; j < auxMatrixs[n*cols+m]-> cols () ; j++ ) {
					//Write the values
					aux ( start_block_n + i , start_block_m + j ) = auxMatrixs[n*cols+m]-> get_matrix () ( i , j );
			}
			}
		start_block_m = start_block_m + auxMatrixs[n*cols+m] -> cols ();
		}
		start_block_m = 0;
		m=m-1;//m gets increased on exit of the for block
		start_block_n = start_block_n + auxMatrixs[n*cols+m] -> rows ();
		}
		start_block_n = 0;

		mat = aux;
//		system = NULL;
		* this = atomize ( * this );
	}catch ( exception &  p ) {
  		outError ( "ERR - Unspected error building Matrix" );
	}catch ( int i ) {
		     if (i==1){outError ( "ERR - number rows*cols different of number of Matrixes" );}
		else if (i==2){outError ( "ERR - Matrixes in a row must have the same number of rows" );}
		else if (i==3){outError ( "ERR - Matrixes in a column must have the same number of columns" );};
	}
}



/*
Constructor with number of rows , cols and one list for compose a new Matrix
*/
Matrix::Matrix ( long rows , long cols , lst expressions_list ) {
	try{
		if (  ( rows * cols ) != expressions_list.nops () ) throw 1;
			init ( "" , matrix ( rows , cols , expressions_list ) );
	}catch ( int e ) {
		outError ( "ERR - Incompatible dimensions in input Matrixes" );
	}catch ( exception &  p ) {
		outError ( "ERR - Unspected error building Matrix" );
	}
}


/*
Constructor with name and one list for compose a new Matrix
*/
Matrix::Matrix ( string name , lst expressions_list ) {
	try{
		//The number of colums is the number of elements of the first sub-list
		matrix aux ( expressions_list.nops () , expressions_list.op ( 0 ).nops () );

		//One sub-list is one row in the final Matrix
		for ( int i = 0 ; i < aux.rows () ; i++ )
			for ( int j = 0 ; j < aux.cols () ; j++ )
				aux ( i , j ) = expressions_list.op ( i ).op ( j );
		init ( name , aux );
	}catch ( int e ) {
		outError ( "ERR - Incompatible dimensions in input Matrixes" );
	}catch ( exception &  p ) {
  		outError ( "ERR - Unspected error building Matrix" );
	}
}


/*
Constructor with one list for compose a new Matrix
*/
Matrix::Matrix ( lst expressions_list ) {
	try{
		//The number of columns of this Matrix we obtain it for the number of elements of the first list
		matrix aux ( expressions_list.nops () , expressions_list.op ( 0 ) .nops () );

		//One lst is one row of the final Matrix
		for ( int i = 0 ; i< aux.rows () ; i++ )
			for ( int j = 0 ; j < aux.cols () ; j++ )
				aux ( i , j ) = expressions_list.op ( i ) .op ( j );
		init ( "" , aux );
	}catch ( int e ) {
		outError ( "ERR - Incompatible dimensions in input Matrixes" );
	}catch ( exception & p ) {
  		outError ( "ERR - Unspected error building Matrix" );
	}
}


/*
Return the name of this Matrix
*/
string Matrix::get_name ( void ) {
	return name;
}


/*
Put the name of this Matrix
*/
void Matrix::set_name ( string new_name ) {
	name = new_name;
}


/*
Return the matrix of this Matrix
*/
matrix Matrix::get_matrix ( void ) {
	return mat;
}


/*
Put the matrix of this Matrix
*/
void Matrix::set_matrix ( matrix new_mat ) {
	mat = new_mat;
}

/*
Extracts the i-th col of a matrix
*/
Matrix Matrix::get_col ( int j ) {

    try{
	Matrix AuxMat(rows(),1);
    for (int i=0; (i < rows()); ++i) {
        AuxMat(i,0) = mat(i,j);
    }
    return AuxMat;
    }catch ( int e ) {
		outError ( (string("ERR - The index of the column is out of range")).c_str() );
    }
}
/*
Extracts the i-th row of a matrix
*/
Matrix Matrix::get_row ( int i ) {
    try{
        Matrix AuxMat(1,cols());
        for (int j=0; (j < cols()); ++j) {
            AuxMat(0,j) = mat(i,j);
        }
        return AuxMat;
    }catch ( int e ) {
		outError ( (string("ERR - The index of the row is out of range")).c_str() );
    }

}

/*
Extracts the item at the ith row and jth column (it is the same as the operator ())
*/
ex& Matrix::get(int i, int j) {
	return (*this)(i, j);
}

/*
Change the value at the ith row and jth column (same as using the operator ())
*/
void Matrix::set(int i, int j, const ex& value) {
	(*this)(i, j) = value;
}

/*
Removes the j-th col of a matrix
*/
Matrix Matrix::remove_col ( int jth ) {

    try{
	    Matrix AuxMat(rows(),cols()-1);

        for (int j=0; (j < jth); ++j) {
            for (int i=0; (i < rows()); ++i) {
                AuxMat(i,j) = mat(i,j);
            }
        }
        for (int j=jth; (j < cols()-1); ++j) {
            for (int i=0; (i < rows()); ++i) {
                AuxMat(i,j) = mat(i,j+1);
            }
        }


        return AuxMat;

    }catch ( int e ) {
		outError ( (string("ERR - The index of the column is out of range")).c_str() );
    }


}

/*
Removes the i-th row of a matrix
*/
Matrix Matrix::remove_row ( int ith ) {
    try{
	    Matrix AuxMat(rows()-1,cols());

        for (int i=0; (i < ith); ++i) {
            for (int j=0; (j < cols()); ++j) {
                AuxMat(i,j) = mat(i,j);
            }
        }
        for (int i=ith; (i < rows()-1); ++i) {
            for (int j=0; (j < cols()); ++j) {
                AuxMat(i,j) = mat(i+1,j);
            }
        }


        return AuxMat;

    }catch ( int e ) {
		outError ( (string("ERR - The index of the column is out of range")).c_str() );
    }
}

/*
Introduces a set of values to the j-th col of a matrix
*/
void Matrix::set_col ( const int j , Matrix VectorC ) {

    try{
    for (int i=0; (i < rows()); ++i) {
        mat(i,j) = VectorC(i,0);
    }
    }catch ( int e ) {
		outError ( (string("ERR - Size error")).c_str() );
    }
}

/*
Introduces a set of values to the i-th row of a matrix
*/
void Matrix::set_row ( const int i , Matrix VectorR ) {

    try{
    for (int j=0; (j < cols()); ++j) {
        mat(i,j) = VectorR(0,j);
    }
    }catch ( int e ) {
		outError ( (string("ERR - Size error")).c_str() );
    }
}




/*
Destructor method of Matrix
*/
Matrix::~Matrix ( void ) {}


/*
Operator that return the value of one concrete possition or ERR if this possition don't exist
*/
ex outIndex = symbol ( "ERR" );
ex&  Matrix::operator () ( long row , long col ) {
	try{
		//Return the expression of this index fil col
   		return mat ( row , col );
	}catch ( exception & p ) {
		outError ( "Index out of range" );
		return outIndex;
	}
}


/*
Return the number of rows
*/
long Matrix::rows ( void ) {
	return mat.rows ();
}


/*
Return the number of columns
*/
long Matrix::cols ( void ) {
	return mat.cols ();
}


/*
Derivate of this Matrix respect the time "t"
*/
//Matrix Matrix::Dt ( void ) {
//	try{
//		if ( system == NULL ) throw 1;
//		matrix aux ( rows () , cols () );
//		for ( int i = 0 ; i < rows () ; i++ )
//			for ( int j = 0 ; j < cols () ;j++ )
//				aux ( i , j ) = system-> dt ( mat ( i , j ) );
//		Matrix MatrixA ( "d" + name , aux );
//		return MatrixA;
//	}catch ( int e ) {
//		outError ( "Invalid System" );
//		return * this;
//	}
//}


/*
Method that substitute the expresions indicates in the relational form.
*/
Matrix Matrix::subs ( relational relation ) {
	Matrix sol ( rows () , cols () );
	Matrix aux = unatomize ( * this );
	ex le = relation.lhs () ;
	ex rig = relation.rhs () ;
	for ( int i = 0 ; i < rows () ; i++ )
		for ( int j = 0 ; j < cols () ; j++ ) {
			sol ( i , j ) = aux ( i , j ).subs ( le + wild ( 1 ) == rig + wild ( 1 ) );
			sol ( i , j ) = aux ( i , j ).subs ( le == rig );
		}
	return atomize ( sol );
}

/*
Method that expands the expresions indicates in the relational form.
*/
Matrix Matrix::expand ( void ) {
	Matrix sol ( rows () , cols () );
	Matrix aux = unatomize ( * this );
	for ( int i = 0 ; i < rows () ; i++ )
		for ( int j = 0 ; j < cols () ; j++ ) {
			sol ( i , j ) = aux ( i , j ).expand();
		}
	return atomize ( sol );
}

/*
Put one System in this Matrix
*/
//void Matrix::set_System ( System * new_system ) {
//	system = new_system;
//}


/*
Return the System of this Matrix
*/
//System * Matrix::get_System ( void ) {
//	return system;
//}


/*
Return the Matrix transpose
*/
Matrix Matrix::transpose ( void ) {
	matrix aux = mat.transpose () ;
	Matrix MatrixA ( ( name + "'" ) , aux );
	return MatrixA;
}


/*
Method that make the Matrix operations calculums
*/
Matrix Matrix::Operations ( const Matrix & MatrixA , const Matrix & MatrixB , int flag ) {

	try{
		Matrix sol;
		if ( flag == 1 ) {//+
			Matrix result ( MatrixA.mat.add ( MatrixB.mat ) );
			sol = result;

		}
		else if ( flag == 2 ) {//*
			//We don't use .mul () method because we need atomize all the operations
			Matrix result ( MatrixA.mat.rows () , MatrixB.mat.cols () );
			ex suma;
			for ( int i = 0 ; i < MatrixA.mat.rows () ; i++ ) {
				for ( int j = 0 ; j < MatrixB.mat.cols () ; j++ ) {
					suma = 0;
					for ( int z = 0 ; z < MatrixB.mat.rows () ; z++ ) {
						suma = atomize_ex ( suma + atomize_ex ( MatrixA.mat ( i , z ) * MatrixB.mat ( z , j ) ) );
					}
					result.mat ( i , j ) = suma;
				}
			}
			sol = result;
		}
		else if ( flag == 3 ) {//-
			Matrix result ( MatrixA.mat.sub ( MatrixB.mat ) );
			sol = result;
		}
		else if ( flag == 4 ) {//- unary
			matrix aux ( MatrixA.mat.rows () , MatrixA.mat.cols () );
			Matrix result ( aux.sub ( MatrixA.mat ) );
			sol = result;
		}
        return atomize ( sol );

	}catch ( exception & p ) {
		outError ( "ERR - Failure in Matrix operation" );
		Matrix empty;
		return empty;
	}
}


/*
Method that make the the operations calculates between Matrix and expressions
*/
Matrix Matrix::Operations ( const Matrix & MatrixA , const ex & expression , int flag ) {
	try{
		Matrix sol;
		if ( flag == 1 ) {//expression * Matrix
			matrix aux ( MatrixA.mat.rows () , MatrixA.mat.cols () );
			for ( int i = 0; i < aux.rows () ;  i++ )
    				for ( int j = 0; j < aux.cols () ;  j++ )
          				aux ( i , j ) = expression * MatrixA.mat ( i , j );
			Matrix result ( MatrixA.name , aux );
			sol = result;
		}
		else if ( flag == 2 ) {//Matrix * expression
			matrix aux ( MatrixA.mat.rows () , MatrixA.mat.cols () );
			for ( int i = 0; i < aux.rows () ;  i++ )
    				for ( int j = 0; j < aux.cols () ;  j++ )
          				aux ( i , j ) = MatrixA.mat ( i , j ) * expression;
			Matrix result ( MatrixA.name , aux );
			sol = result;
		}
		return atomize ( sol );
	}catch ( exception & p ) {
		outError ( "ERR - Failure in Matrix operation" );
		Matrix empty;
		return empty;
	}
}


/*
Sum between two Matrix
*/
Matrix operator + ( const Matrix & MatrixA , const Matrix & MatrixB ) {
	return Matrix::Operations ( MatrixA , MatrixB , 1 );
}


/*
Multiplication between one ex and one Matrix
*/
Matrix operator * ( const ex & expression , const Matrix & MatrixA ) {
	return Matrix::Operations ( MatrixA , expression , 1 );
}


/*
Multiplication between one Matrix and one ex
*/
Matrix operator * ( const Matrix & MatrixA , const ex & expression ) {
	return Matrix::Operations ( MatrixA , expression , 2 );
}


/*
Multiplication between two Matrix
*/
Matrix operator * ( const Matrix & MatrixA , const Matrix & MatrixB ) {
	return Matrix::Operations ( MatrixA , MatrixB , 2 );
}


/*
Diference between two Matrix
*/
Matrix operator - ( const Matrix & MatrixA , const Matrix & MatrixB ) {
	return Matrix::Operations ( MatrixA , MatrixB , 3 );
}


/*
Negation of one Matrix
*/
Matrix operator - ( const Matrix & MatrixA ) {
	return Matrix::Operations ( MatrixA , MatrixA , 4 );
}

/*
Operator that help in the inicialized of Matrixes values
*/
Matrix& Matrix::operator , ( const ex & expression ){

	if (last_row > mat.rows()-1 ) return *this;

	this-> mat ( last_row , last_col) = expression;

	if (last_col == mat.cols()-1){
		last_row++;
		last_col = 0;
	}
	else
		last_col++;

	return *this;
}


/*
Operator that help in the inicialized of Matrixes values
*/
Matrix& Matrix::operator = ( const ex & expression ){
	last_row = 0;
	last_col = 0;

	this-> mat ( 0 , 0) = expression;

	//If the Matrix oly have one column
	if (( mat.cols() == 1 ) && (mat.rows() >= 1))
		last_row++ ;
	else
		last_col++;

	return * this;
}

/*
Matrix output
*/
ostream &  operator << ( ostream &  os , const Matrix & MatrixA )
{
	try{
		if ( MatrixA.name == "ERROR" ) throw 1;
		//os << MatrixA.name << " = [";
		os << "[";
		matrix aux = MatrixA.mat ;
		for ( int i = 0; i < aux.rows () ;  i++ ) {
    			for ( int j = 0; j < aux.cols () ;  j++ ) {
          			os << aux ( i , j );
				if ( j < aux.cols () -1 ) os << " , ";
				else
					if (  ( j == aux.cols () -1 ) &&  (  ( i == aux.rows () -1 ) ) ) os << "";
					else os << ";\n";
			}
    		}
		os << "]";
	return os;
	}catch ( exception & p ) {
  		outError ( "ERR - Unespected error in out in Matrix" );
		return os;
	}
	catch ( int e ) {
		return os;
	}
}
