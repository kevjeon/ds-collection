//============================================================================
// Name        : sparseMatrix.cpp
// Author      : Seongbeom Jeon
// Description : A simple sparse matrix generator
//============================================================================

#include <iostream>
#include <vector>
using namespace std;


template<class DT>
class ExceptionAdd {
};

template<class DT>
class ExceptionMultiply {
};

template<class DT>
class ExceptionCV {
};

template<class DT>
class SparseRow {
protected:
	int row;  //Row#
	int col;  //Column#
	DT value; //We will assume that all our values will be integers
public:
	SparseRow(); //default constructor; row=-1;col=-1;value=0
	SparseRow(int r, int c, DT &v);
	virtual ~SparseRow(); //Destructor
	void display();       // print Row#, Column#, value
						  //other methods as you deem fit
	int getRowN(); //Get the Row number
	int getColN(); //Get the Column number
	DT getValue(); //Get the value
	void setRow(int r, int c, DT &v); //Set the Row values when storing to sparse matrix
};

template<class DT>
class SparseMatrix {
protected:
	int noRows;      //Number of rows of the original matrix
	int noCols;      //Number of columns of the original matrix
	int commonValue; //read from input
	vector<SparseRow<DT>>* myMatrix; //Array
public:
	SparseMatrix(); //Empty constructor
	SparseMatrix(int n, int m, int cv); //Constructor
	virtual ~SparseMatrix(); //Destructor
	void setSparseRow(int pos, int r, int c, DT &v); //Sets the specified row or sparse matrix
	SparseMatrix<DT> operator*(SparseMatrix<DT> M)
		throw (ExceptionMultiply<DT>, ExceptionCV<DT>); //for multiplication
	SparseMatrix<DT> operator+(SparseMatrix<DT> M) throw (ExceptionAdd<DT>,
		ExceptionCV<DT>); //for addition
	SparseMatrix<DT> operator!(); //Transpose
	friend ostream& operator<<(ostream& output, SparseMatrix<DT> M) //ostream overload
	{
		M.display(output);
		return output;
	}
	void display(ostream& output);                  //Display the sparse matrix
	void displayMatrix();            //Display the matrix in its original format

	vector<SparseRow<DT>>* getmyMatrix(); //Gets the matrix object
	int getSize(); //return the size of the matrix(# of Rows)
	DT getValueAt(int index); //Return the value at specified index
	int getColNumAt(int index); //Return the Column # (2nd value) at specified index
	int getRowNumAt(int index); //Return the Row # (1st value) at specified index
};

template<class DT>
SparseRow<DT>::SparseRow() {
	row = -1;
	col = -1;
	value = 0;
}
template<class DT>
SparseRow<DT>::SparseRow(int r, int c, DT &v) {
	row = r;
	col = c;
	value = v;
}

template<class DT>
SparseRow<DT>::~SparseRow() {

}

template<class DT>
void SparseRow<DT>::display() {
	cout << row << ", " << col << ", " << value;
}

template<class DT>
int SparseRow<DT>::getRowN() {
	return row;
}
template<class DT>
int SparseRow<DT>::getColN() {
	return col;
}
template<class DT>
DT SparseRow<DT>::getValue() {
	return value;
}
template<class DT>
void SparseRow<DT>::setRow(int r, int c, DT &v) {
	row = r;
	col = c;
	value = v;
}
template<class DT>
SparseMatrix<DT>::SparseMatrix() {

}

template<class DT>
SparseMatrix<DT>::SparseMatrix(int n, int m, int cv) {
	noRows = n;
	noCols = m;
	commonValue = cv;
	myMatrix = new vector<SparseRow<DT>>(0);
}

template<class DT>
SparseMatrix<DT>::~SparseMatrix() {
		
}
template<class DT>
void SparseMatrix<DT>::setSparseRow(int pos, int r, int c, DT &v) {
	//Specify position, then setRow on that position
	myMatrix->at(pos).setRow(r, c, v);
}
template<class DT>
void SparseMatrix<DT>::display(ostream& output) {
	for (int i = 0; i < this->getSize(); i++) {
		//If value is valid
		if (myMatrix->at(i).getRowN() != -1) {
			output << this->myMatrix->at(i).getRowN() << ", "
				<< this->myMatrix->at(i).getColN() << ", "
				<< this->myMatrix->at(i).getValue() << endl;
		}
	}
}

template<class DT>
void SparseMatrix<DT>::displayMatrix() {
	//Create Array to store origial matrix
	typedef int* ArrayPrt;
	ArrayPrt *original = new ArrayPrt[noRows];
	int i, j;
	for (i = 0; i < noRows; i++) {
		original[i] = new int[noCols];
	}

	//Create full matrix from sparse matrix to display
	int counter = 0;
	for (i = 0; i < noRows; i++) {
		for (j = 0; j < noCols; j++) {
			//See if Row# and Col# match to set the matrix
			if (counter < this->getSize()
				&& j == myMatrix->at(counter).getColN()
				&& i == myMatrix->at(counter).getRowN()) {
				original[i][j] = getValueAt(counter);
				counter++;
			}

			else {
				//otherwise fill with the designated commonvalue
				original[i][j] = commonValue;
			}
		}

	}

	//Iterate through the matrix and print the values in order
	for (i = 0; i < noRows; i++) {
		for (j = 0; j < noCols; j++) {
			cout << original[i][j] << " ";

			if (j == noCols - 1) {
				cout << endl;
			}
		}
	}

	//Manually delete the original matrix
	delete[] original;
}

template<class DT>
vector<SparseRow<DT>>* SparseMatrix<DT>::getmyMatrix() {
	return this->myMatrix;
}

template<class DT>
int SparseMatrix<DT>::getSize() {
	return myMatrix->size();
}
template<class DT>
DT SparseMatrix<DT>::getValueAt(int index) {
	return myMatrix->at(index).getValue();
}

template<class DT>
int SparseMatrix<DT>::getColNumAt(int index) {
	return myMatrix->at(index).getColN();
}

template<class DT>
int SparseMatrix<DT>::getRowNumAt(int index) {
	return myMatrix->at(index).getRowN();
}

template<class DT>
SparseMatrix<DT> SparseMatrix<DT>::operator*(SparseMatrix<DT> M)
throw (ExceptionMultiply<DT>, ExceptionCV<DT>) {
	//Throw Exceptions when the commonvalues do not match
	if (commonValue != M.commonValue) {
		throw ExceptionCV<DT>();
	}

	//Or when the Column value of the first does not equal the Row value of the second
	if (noCols != M.noRows) {
		throw ExceptionMultiply<DT>();
	}

	
		SparseMatrix<DT>* multiple = new SparseMatrix<DT>(noRows, noCols,
			commonValue);

		//Create an array to store original matrix
		typedef int* ArrayPrt;
		ArrayPrt *original = new ArrayPrt[noRows];
		ArrayPrt *original2 = new ArrayPrt[M.noRows];
		ArrayPrt *temp = new ArrayPrt[noRows];
		int i, j, k;
		//Set the temporary matrices
		for (i = 0; i < noRows; i++) {
			original[i] = new int[noCols];
		}
		for (i = 0; i < M.noRows; i++) {
			original2[i] = new int[M.noCols];
		}
		for (i = 0; i < noRows; i++) {
			temp[i] = new int[M.noCols];
		}

		//Create full matrix from sparse matrix to operate on
		int counter = 0;
		for (i = 0; i < noRows; i++) {
			for (j = 0; j < noCols; j++) {

				//See if Row# and Col# match to set the matrix
				if (counter < this->getSize()
					&& j == myMatrix->at(counter).getColN()
					&& i == myMatrix->at(counter).getRowN()) {
					original[i][j] = getValueAt(counter);
					counter++;
				}

				else {
					//otherwise fill with the designated commonvalue
					original[i][j] = commonValue;
				}

			}

		}

		//Create full matrix from sparse matrix to operate on
		counter = 0;
		for (i = 0; i < M.noRows; i++) {
			for (j = 0; j < M.noCols; j++) {

				if (counter < M.getSize() && i == M.getRowNumAt(counter)
					&& j == M.getColNumAt(counter)) {
					original2[i][j] = M.getValueAt(counter);
					counter++;
				}

				else {
					original2[i][j] = commonValue;
				}

			}

		}

		//initialize temporary matrix
		for (i = 0; i < noRows; i++) {
			for (j = 0; j < M.noCols; j++) {
				temp[i][j] = 0;
			}
		}

		//Actual multiplication happens here
		for (i = 0; i < noRows; i++) {
			for (j = 0; j < M.noCols; j++) {
				for (k = 0; k < noCols; k++) {
					temp[i][j] += original[i][k] * original2[k][j];
				}
			}
		}

		counter = 0;
		//Set the returning matrix with temp matrix
		for (i = 0; i < noRows; i++) {
			for (j = 0; j < M.noCols; j++) {
				if (temp[i][j] != commonValue) {
					//Increate the size of matrix by one every before a value is stored
					multiple->getmyMatrix()->resize(multiple->getSize() + 1);
					multiple->setSparseRow(counter, i, j, temp[i][j]);
					counter++;
				}
			}
		}


		//Manually delete the stored matrices and return the multiple
		delete[] original;
		delete[] original2;
		delete[] temp;

		return *multiple;

		multiple->~SparseMatrix();
	

}

template<class DT>
SparseMatrix<DT> SparseMatrix<DT>::operator+(SparseMatrix<DT> M)
throw (ExceptionAdd<DT>, ExceptionCV<DT>) {
	//Throws Exception when the matrix dimensions do not match
	if (noRows != M.noRows || noCols != M.noCols) {
		throw ExceptionAdd<DT>();
	}
	//Or when common values do not match
	else if (commonValue != M.commonValue) {
		throw ExceptionCV<DT>();
	}

	SparseMatrix<DT>* sum = new SparseMatrix<DT>(noRows, noCols, commonValue);
	typedef int* ArrayPrt;
	ArrayPrt *original = new ArrayPrt[noRows];
	ArrayPrt *original2 = new ArrayPrt[M.noRows];
	ArrayPrt *temp = new ArrayPrt[noRows];
	int i, j;
	//Set the temporary matrices
	for (i = 0; i < noRows; i++) {
		original[i] = new int[noCols];
	}
	for (i = 0; i < M.noRows; i++) {
		original2[i] = new int[M.noCols];
	}
	for (i = 0; i < noRows; i++) {
		temp[i] = new int[M.noCols];
	}

	//Create full matrix from sparse matrix to operate on
	int counter = 0;
	for (i = 0; i < noRows; i++) {
		for (j = 0; j < noCols; j++) {

			//See if Row# and Col# match to set the matrix
			if (counter < this->getSize()
				&& j == myMatrix->at(counter).getColN()
				&& i == myMatrix->at(counter).getRowN()) {
				original[i][j] = getValueAt(counter);
				counter++;
			}

			else {
				//otherwise fill with the designated commonvalue
				original[i][j] = commonValue;
			}

		}

	}

	//Create full matrix from sparse matrix to operate on
	counter = 0;
	for (i = 0; i < M.noRows; i++) {
		for (j = 0; j < M.noCols; j++) {

			if (counter < M.getSize() && i == M.getRowNumAt(counter)
				&& j == M.getColNumAt(counter)) {
				original2[i][j] = M.getValueAt(counter);
				counter++;
			}

			else {
				original2[i][j] = commonValue;
			}

		}

	}

	//initialize temporary matrix
	for (i = 0; i < noRows; i++) {
		for (j = 0; j < M.noCols; j++) {
			temp[i][j] = 0;
		}
	}

	for (i = 0; i < noRows; i++) {
		for (j = 0; j < noCols; j++) {
			temp[i][j] = original[i][j] + original2[i][j];
		}
	}

	counter = 0;
	//Set the returning matrix with temp matrix
	for (i = 0; i < noRows; i++) {
		for (j = 0; j < noCols; j++) {
			if (temp[i][j] != commonValue) {
				sum->getmyMatrix()->resize(sum->getSize() + 1);
				sum->setSparseRow(counter, i, j, temp[i][j]);
				counter++;
			}
		}
	}

	//Delete original arrays once operation is finished
	delete[] original;
	delete[] original2;
	delete[] temp;

	return *sum;

	sum->~SparseMatrix();
}

template<class DT>
SparseMatrix<DT> SparseMatrix<DT>::operator!() {
	SparseMatrix<DT>* temp = new SparseMatrix<DT>(noCols, noRows, commonValue);
	typedef int* ArrayPrt; //Define new int pointer for arrays
	ArrayPrt *original = new ArrayPrt[this->noRows]; //Initialize arrays to operate on
	ArrayPrt *transpose = new ArrayPrt[this->noCols];
	int i, j;

	//Set the matrix
	for (i = 0; i < noRows; i++) {
		original[i] = new int[noCols];
	}
	//Set the matrix
	for (i = 0; i < noCols; i++) {
		transpose[i] = new int[noRows];
	}

	//Create full matrix from sparse matrix to operate on
	int counter = 0;
	for (i = 0; i < noRows; i++) {
		for (j = 0; j < noCols; j++) {

			//See if Row# and Col# match to set the matrix
			if (counter < this->getSize()
				&& j == myMatrix->at(counter).getColN()
				&& i == myMatrix->at(counter).getRowN()) {
				original[i][j] = getValueAt(counter);
				counter++;
			}

			else {
				//otherwise fill with the designated commonvalue
				original[i][j] = commonValue;
			}

		}

	}

	//Exchange rows and column (transpose)
	for (i = 0; i < noRows; i++) {
		for (j = 0; j < noCols; j++) {
			transpose[j][i] = original[i][j];
		}
	}

	counter = 0;
	//Set the returning matrix with temp matrix
	for (i = 0; i < noCols; i++) {
		for (j = 0; j < noRows; j++) {
			if (transpose[i][j] != commonValue) {
				//Resize before every new entry
				temp->getmyMatrix()->resize(temp->getSize() + 1);
				temp->setSparseRow(counter, i, j, transpose[i][j]);
				counter++;
			}
		}
	}
	

	//Manually delete the stored matrices and return the transpose
	delete[] original;
	delete[] transpose;
	return *temp;

	temp->~SparseMatrix();

}

int main() {
	int n, m, cv;

	//Read in row, col, and common value from input
	cin >> n >> m >> cv;

	//Initialize the temporary and first Sparse matrices
	SparseMatrix<int> *temp = new SparseMatrix<int>(n, m, cv);
	SparseMatrix<int> *firstOne = new SparseMatrix<int>(n, m, cv);

	//Create new 2d array to store the original matrix input
	std::vector<std::vector<int>> vec2D(n, std::vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> vec2D[i][j];
		}
	}

	//Convert the original matrix into sparse
	int counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (vec2D[i][j] != cv) {
				//Increase the size by 1 before new entry
				firstOne->getmyMatrix()->resize(firstOne->getSize() + 1);
				;
				firstOne->setSparseRow(counter, i, j, vec2D[i][j]);
				counter++;
			}
		}
	}

	//Read in the input for second Sparse Matrix
	cin >> n >> m >> cv;

	//Initalize the second Sparse Matrix
	SparseMatrix<int> *secondOne = new SparseMatrix<int>(n, m, cv);
	std::vector<std::vector<int>> vec2DS(n, std::vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> vec2DS[i][j];
		}
	}

	counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (vec2DS[i][j] != cv) {
				secondOne->getmyMatrix()->resize(secondOne->getSize() + 1);
				secondOne->setSparseRow(counter, i, j, vec2DS[i][j]);
				counter++;
			}
		}
	}

	cout << "First one in sparse matrix format" << endl;
	cout << *firstOne;

	cout << "First one in normal matrix format" << endl;
	firstOne->displayMatrix();

	cout << "second one in sparse matrix format" << endl;
	cout << *secondOne;

	cout << "Second one in normal matrix format" << endl;
	secondOne->displayMatrix();

	temp = &!(*firstOne);
	cout << "After transpose first one in normal format" << endl;
	temp->displayMatrix();

	temp = &!(*secondOne);
	cout << "After transpose second one in normal format" << endl;
	temp->displayMatrix();

	try {
		cout << "Multiplication of matrices in sparse matrix form:" << endl;
		temp = &((*secondOne) * (*firstOne));
		cout << *temp;
	}
	catch (ExceptionMultiply<int>) {
		cout << "Dimensions of two matrices do not match for multiplication"
			<< endl;
	}
	catch (ExceptionCV<int>) {
		cout << "Common values do not match" << endl;
	}

	try {
		cout << "Addition of matrices in sparse matrix form:" << endl;
		temp = &((*secondOne) + (*firstOne));
		cout << *temp;
	}
	catch (ExceptionAdd<int>) {
		cout << "Cannot add matrices with two different dimensions" << endl;
	}
	catch (ExceptionCV<int>) {
		cout << "Common values do not match" << endl;
	}

	
	temp->~SparseMatrix();
	firstOne->~SparseMatrix();
	secondOne->~SparseMatrix();

}
