#include <iostream>
#include <vector>

using namespace std;

//Declaracion de la clase y sus metodos
class MyNumber{
private:
    int* x = nullptr;
    int value;

public:
    MyNumber(int num){
        x = new int(num);
        value = *(this->x);
    };

    ~MyNumber(){
        delete x;
    };

    static long long fact(int number);
    static bool isPrime(int number);
    static bool isPerfect(int number);
    static int mcd(int num1, int num2);
    static int mcm(int num1, int num2);

    int getValue();
    void setValue(int newValue);

    /*Cuando inplace es true, se retornara y actualizara el numero con el valor del resultado de la operacion.
    Cuando es false solo se retorna el resultado de la operacion y el objeto sigue con su valor de inicio*/
    int add(int y, bool inplace = false);
    int sub(int y, bool inplace = false);
    int divide(int y, bool inplace = false);
    int mult(int y, bool inplace = false);
    long long pot(int y, bool inplace = false);
    bool areFriends(int y);
};

/*Ejercicio. Crea una clase Numero y define metodos para resolver los sgtes ejercicios: 
-Pedir dos numeros y sumarlos, restarlos, multplicarlos, dividirlos y potenciarlos sin 
    operadores y obtener el factorial de cada uno recursivamente
-Comprobar si los numeros son primos (solo divisibles por 1 y si mismos)
-Comprobar si los numeros son perfectos (es perfecto si la suma de sus divisores dan el mismo num)
-Comprobar si los numeros son amigos, debes usar arrays 
    (son amigos si la suma de sus divisores dan el otro num y viceversa)
-Hallar el M.C.M y el M.C.D*/

void exercises(){
    int x, y;
    int* yptr;

    cout << "Type the first number => ";
    cin >> x;
    MyNumber myNum = MyNumber(x); 
    
    cout << "Type the second number => ";
    cin >> y;
    yptr = new int(y);

    if (!(myNum.getValue() >= *yptr)){
        cout << "The first number is greater than the second one to operate, change done" << endl;
        int aux = myNum.getValue();
        myNum.setValue(*yptr);
        delete yptr;
        yptr = new int(aux);
    }

    cout << "-----------------------------------\nBasic Operations:\n";
    cout << myNum.getValue() << " + " << *yptr << " = " << myNum.add(*yptr) << endl;   
    cout << myNum.getValue() << " - " << *yptr << " = " << myNum.sub(*yptr) << endl;   
    cout << myNum.getValue() << " / " << *yptr << " = " << myNum.divide(*yptr) << endl;   
    cout << myNum.getValue() << " * " << *yptr << " = " << myNum.mult(*yptr) << endl;
    cout << myNum.getValue() << " ** " << *yptr << " = " << myNum.pot(*yptr) << endl;
    
    cout << "-----------------------------------\nOther Operations:\n";    
    cout << "Are friends (" <<myNum.getValue()<< "," <<*yptr<< ")? => " << boolalpha << myNum.areFriends(*yptr) << endl;
    cout << "!" << myNum.getValue() << " = " << MyNumber::fact(myNum.getValue()) << endl;   
    cout << "!" << *yptr << " = " << MyNumber::fact(*yptr) << endl;   
    cout << "Is prime number (" << myNum.getValue() << ")? => " << boolalpha << MyNumber::isPrime(myNum.getValue()) << endl;   
    cout << "Is prime number (" << *yptr << ")? => " << boolalpha << MyNumber::isPrime(*yptr) << endl;    
    cout << "Is perfect number (" << myNum.getValue() << ")? => " << boolalpha << MyNumber::isPerfect(myNum.getValue()) << endl;   
    cout << "Is perfect number (" << *yptr << ")? => " << boolalpha << MyNumber::isPerfect(*yptr) << endl;   
    cout<<"Maximum Comun Divisor beetwen "<<myNum.getValue()<<" and "<<*yptr<<" is: "<<MyNumber::mcd(myNum.getValue(),  *yptr)<<endl;
    cout<<"Minimum Comun Multiple beetwen "<<myNum.getValue()<<" and "<<*yptr<<" is: "<<MyNumber::mcm(myNum.getValue(),  *yptr)<<endl;
    cout << "-----------------------------------\n";

    delete yptr;
}

int main() {
    char goOn = 'y';
    do{
        exercises();
        cout << "Do you want try with other numbers? (y/n)" << endl;
        cin >> goOn;
    } while (tolower(goOn) != 'n');
    
    return 0;
}

//Definicion de metodos de la clase
int MyNumber::getValue(){
    return this->value;
}

void MyNumber::setValue(int newValue){
    *(this->x) = newValue;
    this->value = *(this->x);
}

int MyNumber::add(int y, bool inplace){
    if (inplace){
        for (int i = 1; i <= y; i++){
            *(this->x) += 1;
        };
        this->setValue(*(this->x));
        return *(this->x);
    }
    else{
        int result = *(this->x);
        for (int i = 1; i <= y; i++){
            result += 1;
        };
        return result;
    }
}

int MyNumber::sub(int y, bool inplace){
    int result = 0;
    for (; y < this->getValue(); y++){
            result++;
        };

    if (inplace){
        this->setValue(result);
        return *(this->x);
    }
    else{
        return result;
    }
}

int MyNumber::divide(int y, bool inplace){
    int result = 0, x = this->getValue();
    for (; x >= y; x -= y){
        result++;
    };

    if (inplace){
        this->setValue(result);
        return *(this->x);
    }
    else{
        return result;
    }
}

int MyNumber::mult(int y, bool inplace){
    int result = 0;
    for (int i = 1; i <= y; i++){
        result += this->getValue();
    };

    if (inplace){
        this->setValue(result);
        return *(this->x);
    }
    else{
        return result;
    }
}

long long MyNumber::pot(int y, bool inplace){
    int result = 1;
    for (int i = 0; i < y; i++){
        result *= this->getValue();
    };
    
    if (inplace){
        this->setValue(result);
        return *(this->x);
    }
    else{
        return result;
    }
}

bool MyNumber::areFriends(int y){
    if (this->getValue() <= 0 || y <= 0){
        return false;
    }

    int array[2] = {this->getValue(), y}; //Almacenaremos los numeros a evaluar
    vector<int> multplesSum = {}; //Almacenaremos la suma de los multiplos de x e y
    
    for (int i = 0; i < 2; i++){ //Recorremos dos veces el array, 1ro con el num x y despues y 
        int sum = 0;
        for (int j = 1; j <= array[i]/2; j++){ 
            //Buscamos los multiplos de x en la 1ra iter y de y en la 2da
            if (array[i] % j == 0){
                sum += j;
            }
        }
        multplesSum.push_back(sum); //Agregamos al vector la suma de los multiplos del numero de la iteracion
    }
    
    //En caso de que la suma de los multiplos de x no sea igual a y, y viceversa. Quiere decir que no son amigos 
    return (multplesSum[0] == array[1] && multplesSum[1] == array[0]);
}

long long MyNumber::fact(int number){
    if (number <= 1) {
        return 1;
    } else {
        return number * fact(number - 1);
    }
}

bool MyNumber::isPrime(int number){
    for (int i = 2; i <= number/2; i++){
        if (number % i == 0 && i != number){
            return false;
        }
    }
    return true;
}

bool MyNumber::isPerfect(int number){
    if (number <= 0){
        return false;
    }

    int divisors = 0;
    for (int i = 1; i <= number/2; i++){
        if (number % i == 0){
            divisors += i;
        }
    }

    return (divisors == number); 
}

int MyNumber::mcd(int num1, int num2){
    int aux = 0;
    while (num2 != 0){
        aux = num1;
        num1 = num2;
        num2 = aux % num2;
    }
    return num1;
}

int MyNumber::mcm(int num1, int num2){
    return (num1*num2)/(mcd(num1, num2));
}