#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class MyMatrix{
private:
    int rows, cols, **pointerMatrix; //Puntero de punteros (puntero a las filas de la matriz)
public:
    MyMatrix(int _rows, int _cols) : rows(_rows), cols(_cols) {
       pointerMatrix = new int* [rows]; //Reservando memoria para filas
       for (int i = 0; i < rows; i++){
            pointerMatrix[i] = new int[cols]; //Reservando memoria para columnas de cada fila
       }
    }

    ~MyMatrix(){
        for (int i = 0; i < this->rows; i++){
            //Borrando memoria reservada de cada fila 
            delete[] pointerMatrix[i];
        }
        delete[] pointerMatrix;
    }

    void addElements(){
        int i, j;
        for (i = 0; i < this->rows; i++){
            cout<<"Matrix ["<<i<<"]:\n";
            for (j = 0; j < this->cols; j++){
                cout<<"Value ["<<i<<"]"<<"["<<j<<"] => ";
                cin>>*(*(pointerMatrix+i)+j);
            }
        }
    }

    void show() const {
        int i, j;
        for (i = 0; i < this->rows; i++){
            for (j = 0; j < this->cols; j++){
                cout<<*(*(pointerMatrix+i)+j)<<" ";
            }
            cout<<endl;
        }
        cout<<"----------------\n";
    }

    void transpose() const {
        for (int i = 0; i < this->cols; i++){
            for (int j = 0; j < this->rows; j++){
                cout<<*(*(this->pointerMatrix+j)+i)<<" ";
            }
            cout<<endl;
        }
    }

    void addition(MyMatrix& matrix2) const {
        for (int i = 0; i < this->rows; i++){
            for (int j = 0; j < this->cols; j++){
                cout<<(*(*(this->pointerMatrix+i)+j)) + (*(*(matrix2.pointerMatrix+i)+j))<<" ";
            }
        cout<<endl;
        }
        cout<<"----------------\n";
    }

    MyMatrix product(MyMatrix& matrix2) const {
        MyMatrix newMatrix = MyMatrix(this->rows, this->cols);
        
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++){
                int sumPos = 0;
                for (int k = 0; k < this->cols; k++){
                /* El bucle interno `k` recorre los elementos de la fila `i` de la 1ra matriz y la columna `j` de la 2da matriz.
                Multiplica cada elemento de la fila `i` de la 1ra matriz con el elemento correspondiente de la columna `j` de la 2da matriz,
                y suma estos productos para obtener el valor del elemento en la posición `(i, j)` de la matriz resultante. */
                    sumPos += (*(*(this->pointerMatrix+i)+k)) * (*(*(matrix2.pointerMatrix+k)+j));
                }
                *(*(newMatrix.pointerMatrix+i)+j) = sumPos;
            }
        }
        return newMatrix;
    }

    /*A partir de un array de numeros devolver una matriz con los numeros elevados al cuadrado y al cubo 
    (Mostrar en cada elemento del array con su cuadrado y cubo en paralelo vertical)*/
    static MyMatrix toSqrtCubic(int* array, int arrSize) {  
        MyMatrix newMatrix = MyMatrix(arrSize, 3);

        for (int i = 0; i < newMatrix.rows; i++) {
            for (int j = 0; j < newMatrix.cols; j++) {
                if (j == 0) {
                    (*(*(newMatrix.pointerMatrix+i)+j)) = array[i]; 
                } else if (j == 1) {
                    (*(*(newMatrix.pointerMatrix+i)+j)) = pow(array[i], 2); 
                } else if (j == 2) {
                    (*(*(newMatrix.pointerMatrix+i)+j)) = pow(array[i], 3); 
                }
            }
        }
        return newMatrix;
    }
};

class MyIrregularMatrix{ //Matriz con filas con diferente cantidad de columnas
private:
    int rows, **pointerMatrix;
    vector<int> colsInRows;
public:
    MyIrregularMatrix(int _rows, vector<int> _colsInRows): rows(_rows), colsInRows(_colsInRows) {
        pointerMatrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            pointerMatrix[i] = new int[colsInRows[i]];
        }
    };
    ~MyIrregularMatrix(){
        for (int i = 0; i < rows; i++) {
            delete[] pointerMatrix[i];
        }
        delete pointerMatrix;
    };

    void addElements(){
        for (int i = 0; i < this->rows; i++) {
            cout<<"Row "<<i<<": \n";
            for (int j = 0; j < this->colsInRows[i]; j++) {
                cout<<"Value ["<<i<<"]"<<"["<<j<<"] -> ";
                cin>>*(*(this->pointerMatrix+i)+j);
            }
        } 
    } 

    void show() const {
        for (int i = 0; i < this->rows; i++){
            for (int j = 0; j < this->colsInRows[i]; j++){
                cout<<*(*(this->pointerMatrix+i)+j)<<" ";
            }
            cout<<endl;
        }
        cout<<"----------------\n";
    }
};

int main(){
    int nRows, nCols;

    cout<<"Number of matrix's rows => ";
    cin>>nRows;
    cout<<"Number of matrix's columns => ";
    cin>>nCols;

    MyMatrix matrix1 = MyMatrix(nRows, nCols);
    MyMatrix matrix2 = MyMatrix(nRows, nCols);

    matrix1.addElements();
    matrix1.transpose();
    cout<<"Matrix is going to be used for add and product of matrix (Matrix 2 will have same dimensions than the previous one)\n";
    matrix2.addElements();
    matrix1.show();  
    matrix2.show();

    system("pause");
    system("cls");

    cout<<"Addition:\n";
    matrix1.addition(matrix2);
    cout<<"Product:\n";
    matrix1.product(matrix2).show();

    system("pause");
    system("cls");

    int arrayElem;
    cout<<"How many elements do you want to throw in your array -> ";
    cin>>arrayElem; cin.clear();

    int* array = new int[arrayElem];

    for (int i = 0; i < arrayElem; i++){
        cout<<"Type the number position ["<<i<<"] -> ";
        cin>>*(array+i);
    }
    
    MyMatrix::toSqrtCubic(array, arrayElem).show();

    system("pause");
    system("cls");

    int asymMatrixRows;
    vector<int> matrixVector = {};

    cout<<"Rows number to asymetric matrix (Rows with diferent number of columns) -> ";
    cin>>asymMatrixRows; cin.clear();
    int col;
    for (int i = 0; i < asymMatrixRows; i++){
        cout<<"How many columns do you want to throw in your row "<<i<<" -> ";
        cin>>col;
        matrixVector.push_back(col);
    }

    MyIrregularMatrix asymMatrix = MyIrregularMatrix(asymMatrixRows, matrixVector); 

    asymMatrix.addElements();
    asymMatrix.show();

    return 0;
}