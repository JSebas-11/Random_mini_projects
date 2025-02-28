// # <-Directivas de preprocesador (compilador procesa antes de compilar)
#include <iostream>

/*
Secuencias de escape: 
    \n: salto linea, \t: tabulacion, \b: retroceder cursor 1 char, 
    \r: retroceder cursor inicio linea, \0: caracter vacio (final char arrays)

Tipos datos:
    Simples:
        char:   Almacena un carácter [1 byte (8 bits), ASCII -128 to 127 (signed) || 0 to 255 (unsigned)]
        int:	Enteros	[4 bytes (32 bits), -2,147,483,648 to 2,147,483,647]
        float:	Números decimales [4 bytes (32 bits), ±3.e-38 to ±3.4e+38]
        double:	Números decimales  de doble precisión [8 bytes (64 bits), ±1.7e-308 a ±1.7e+308]
        bool:	Valores booleanos [(true || false), 1 byte]	
        void:	Sin valor (funciones)
    Derivados:
        array:	Colección de elementos del mismo tipo.
        pointer: Dirección de memoria de una variable.
        reference: Un alias o referencia a otra variable.
    User defined:
        struct:	Colección de variables agrupadas.
        class: Estructura con métodos y propiedades.
        enum: Enumeración, conjunto de constantes nombradas.
        typedef || using: Alias para un tipo existente.
    Constantes:
        Pueden ser declaradas en preprocesador #define NAME value || en programa const type NAME = value;

Modificadores:
    signed + int || char <- Valores positivos y negativos
    unsigned + int || char <- Valores positivos    
    short + int <- Menor tamaño que int
    long + int || double <- Mayor tamaño


*/

void drawTriangle(float height, bool reverse = false, char charac = '*'){
    if (reverse){
        for (int i = height; i >= 1; i--){
            for (int j = 1; j <= i; j++){
                std::cout<<charac;
            }
            std::cout<<"\n";
        }
    }
    else{ 
        for (int i = 1; i <= height; i++){
            for (int j = 1; j <= i; j++){
                std::cout<<charac;
            }
            std::cout<<"\n";
        }
    }
}

void fibonacci(int limit = 10){
    int aux1 = 0, aux2 = 1, result = 0;
    for (int i = 1; i <= limit; i++){
        if (i==1){
            result = 0;
        }
        else if (i==2){
            result = 1;
        }
        else{
            result = aux1+aux2;
            aux1 = aux2;
            aux2 = result;
        }
    }
    std::cout<<result;
}

int main(){
    int number;
    std::cout<< "Int's size: "<<sizeof(int)<<" bytes\n";
    
    std::cout<<"Type a number => ";
    std::cin>>number;
    
    int* num = new int(number), centinel = *num, digNum = 0;

    do{
        centinel /= 10;
        digNum ++;
    } while (centinel!=0);
    std::cout<<*num<<" has "<<digNum<<" digits\n";
    delete num;

    float height;
    std::cout<<"Type triangle's height => ";
    std::cin>>height;
    drawTriangle(height);
    std::cout<<"------------------------\n";
    drawTriangle(height, true);
    std::cout<<"------------------------\n";
    
    int fibNums;
    std::cout<<"How many numbers of the Fibonacci series do you want to show => ";
    std::cin>>fibNums;

    fibonacci(fibNums+1);

    return 0;
}