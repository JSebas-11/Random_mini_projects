#include <iostream>
#include <exception>
#include <tuple>

using namespace std;

void firstLook(){
    //Arrays estaticos son los que tienen un tamaño definido y reserva esa cantidad de memoria especifica  
    int myArray[5] = {};
    //Podemos acceder a sus posiciones por indice 
    myArray[0] = 11;
    cout<<myArray[0]<<"\n";

    //Arrays dinamicos
    int size = 5;
    int* myDinArray = new int[size];
    delete[] myDinArray;
}

/*Crear una clase array de numeros y: 
    -Calcular la suma o multiplicacion acumulada de sus elementos
    -Mostrar los elementos del array con su correspondiente indice 
        y despues muestra los elementos en orden inverso
    -Hallar el mayor y menor elemento del array
    -Calcular si en el array existe algun elemento cuyo valor sea igual a
        la suma del resto de elementos
    -Sumar, restar, multiplicar o dividir el array con otro array (Ambos array deben tener misma longitud)*/

class myArray{
private:
    int size;
    int* array;

    int returnNum(string which);

public:
    myArray(int _size) : size(_size) {
        array = new int[_size];
    };
    ~myArray(){
        delete[] array;
    };

    int getSize() const;
    void pushElements();
    int calculate(string kind);
    void show(bool reverse=false, string sep="\n");
    int max();
    int min();
    tuple<bool, int> isThereBigEle();
    static myArray operateArrays(string operation, const myArray& array1, const myArray& array2);
};

void arrayExercises(){
    int size, num;
    bool isThere;

    cout<<"How many numbers do you want to include in your array => ";
    cin>>size;

    myArray array = myArray(size);
    myArray array2 = myArray(size);

    array.pushElements();
    
    cout<<"-----------------------------\n";
    cout<<"Elements' add of array: "<<array.calculate("add")<<"\n"; 
    cout<<"Elements' product of array: "<<array.calculate("prod")<<"\n"; 
    cout<<"-----------------------------\n";
    cout<<"Order array:\n"; array.show();
    cout<<"\nReverse array:\n"; array.show(true);
    cout<<"\n-----------------------------\n";
    cout<<"Minimum: "<<array.min()<<"\n";
    cout<<"Maximum: "<<array.max()<<"\n";
    
    tie(isThere, num) = array.isThereBigEle();
    cout<<"Is there a number that it's value is the sum of the rest of numbers? "<<boolalpha<<isThere<<" ("<<num<<")\n";
    cout<<"-----------------------------\n";
    system("pause");
    system("cls");

    cout<<"Second array's elements to calculate operations\n";
    array2.pushElements();

    cout<<"-----------------------------\n";
    cout<<"Array 1:\n"; array.show(false, ", ");
    cout<<"\nArray 2:\n"; array2.show(false, ", ");
    cout<<"\n-----------------------------\n";
    cout<<"Sum: \n"; myArray::operateArrays("sum", array, array2).show(false, ", "); cout<<"\n";
    cout<<"Difference: \n"; myArray::operateArrays("sub", array, array2).show(false, ", "); cout<<"\n";
    cout<<"Product: \n"; myArray::operateArrays("prod", array, array2).show(false, ", "); cout<<"\n";
    cout<<"Division: \n"; myArray::operateArrays("div", array, array2).show(false, ", "); cout<<"\n";
}

int main(){
    firstLook();
    arrayExercises();
    system("pause");
    system("cls");
    return 0;
}

int myArray::returnNum(string which){
    int firstNum = *(this->array+0), number;
    if (which == "max"){
        int max = firstNum;
        for (int i = 0; i < this->getSize(); i++){
            if (*(this->array+i) > max){
                max = *(this->array+i);
            }
        }
        number = max; 
    }
    else if (which == "min"){
        int min = firstNum;
        for (int i = 0; i < this->getSize(); i++){
            if (*(this->array+i) < min){
                min = *(this->array+i);
            }
        }
        number = min;
    }
    return number;
}

int myArray::getSize() const {
    return this->size;
}

void myArray::pushElements(){
    for (int i = 0; i < this->getSize(); i++){
        cout<<"Type the element "<<i+1<<" => ";
        cin>>*(this->array+i);
    }
}

int myArray::calculate(string kind){
    int result = 0;
    if (kind=="add"){
        for (int i = 0; i < this->size; i++){
            result += *(this->array+i);
        }
    }
    else if (kind=="prod"){
        result = 1;
        for (int i = 0; i < this->size; i++){
            result *= *(this->array+i);
        }
    }
    else{
        throw invalid_argument("Operation parameter invalid");
    }
    return result;
}

void myArray::show(bool reverse, string sep){
    if (reverse){
        for (int i = this->size-1; i >= 0; i--){
            if (i==0) { cout<<*(this->array+i); }
            else { cout<<*(this->array+i)<<sep; }
        }
    }
    else{
        for (int i = 0; i < this->size; i++){
            if (i==this->getSize()-1) { cout<<*(this->array+i); }
            else { cout<<*(this->array+i)<<sep; }
        }
    }
}

int myArray::max(){
    return returnNum("max");
}

int myArray::min(){
    return returnNum("min");
}

/*
tuple<bool, int> isThereBigEle(){
    for (int i = 0; i < this->getSize(); i++){ //Recorremos cada elemento del array
        int sumOthers = 0; //Inicializamos contador de la suma de los elementos distintos al elemento en iteracion
        for (int j = 0; j < this->getSize(); j++){ 
            //Recorremos cada elemento del array, pero omitimos al toparnos con el elemento de la iteracion
            if (*(this->array+j) == *(this->array+i)){
                continue;
                j--;
            }
            else{
                sumOthers += *(this->array+j);
            }
        }
        //Comprobamos si la suma del resto elementos es igual al numero en iteracion
        if (sumOthers == *(this->array+i)){
            return make_tuple(true, *(this->array+i));
        }
    }
    //Retornamos false y null, en caso de que al acabar todas las iteraciones no encontrasemos los que buscabamos
    return make_tuple(false, 0);
}*/

//Version Optimizada
tuple<bool, int> myArray::isThereBigEle() {
    int totalSum = this->calculate("add"); 

    for (int i = 0; i < this->getSize(); i++) {
        int currentElement = *(this->array + i);
        int sumOthers = totalSum - currentElement; 

        if (currentElement == sumOthers) {
            return make_tuple(true, currentElement); 
        }
    }
    return make_tuple(false, 0); 
}

myArray myArray::operateArrays(string operation, const myArray& array1, const myArray& array2){
    myArray newArray = myArray(array1.getSize());

    for (int i = 0; i < array1.getSize(); i++){
        if (operation=="sum"){
            *(newArray.array+i) = *(array1.array+i) + *(array2.array+i); 
        }
        else if (operation=="sub"){
            *(newArray.array+i) = *(array1.array+i) - *(array2.array+i); 
        }
        else if (operation=="prod"){
            *(newArray.array+i) = *(array1.array+i) * *(array2.array+i); 
        }
        else if (operation=="div"){
            *(newArray.array+i) = *(array1.array+i) / *(array2.array+i); 
        }
        else{
            throw invalid_argument("Operation parameter invalid");
        }
    }
    return newArray;
}