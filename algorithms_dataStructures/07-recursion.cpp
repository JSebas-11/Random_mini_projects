#include <iostream>

using namespace std;

//Ejercicio basico Void Recurision (Crear funcion recursiva que retorne cuenta atras de un numero) 
void recursion(int number){
    cout<<number<<" ";
    if (number > 0){ recursion(number-1); } 
    else { cout<<"end\n"; }
}

//Ejercicio medio (Crear una funcion que retorne el factorial de un numero recursivamente)
int noRecursiveFact(int number){
    int result = 1;
    for (int i = 1; i < number; i++) {
        result *= i+1;
    }
    return result;
}

int recursiveFact(int number){
    if (number > 1) {
        number *= recursiveFact(number-1);
    }
    return number;
}

/*Ejercicio dificil-Torres Hanoi (Consiste en 3 torres, la 1ra con bases las cuales deben ser movidas a la 
3er torre nunca puede haber una base encima de otra mas pequeña)*/
void hanoi(int basis, int from, int to, int aux){
    if (basis > 0) {
        hanoi(basis-1, from, aux, to);
        cout<<"Disk from pos: "<<from<<" to "<<to<<"\n";
        hanoi(basis-1, aux, to, from);
    }
}

int main(void){
    int numberCountdown, factNumber;
    bool playing;
    char keepPlaying;
    do {
        cout<<"Type a number to show its countdown -> ";
        cin>>numberCountdown; cin.clear();

        cout<<"CountDown: ";
        recursion(numberCountdown);

        cout<<"Type a number to calculate its factorial -> ";
        cin>>factNumber; cin.clear();

        cout<<"Not recursive !"<<factNumber<<": "<<noRecursiveFact(factNumber)<<"\n";
        cout<<"Recursive !"<<factNumber<<": "<<recursiveFact(factNumber)<<"\n";

        hanoi(3, 1, 3, 2);
        
        cout<<"Do you want to try again? (y/n) -> ";
        cin>>keepPlaying;

        if (tolower(keepPlaying) == 'n') { playing = false; } 
        else { 
            system("cls");
            playing = true; 
        }

    } while (playing);
    
    
    return 0;
}