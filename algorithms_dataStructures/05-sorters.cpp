#include <iostream>
#include <ctime>

using namespace std;

class Sorter {
public:
    static void show(int* array, int numElem, bool ascending = true){
        cout<<"Array elements:\n";
        
        if (ascending){
            for (int i = 0; i < numElem; i++){
                cout<<*(array+i)<<endl;
            }
        }
        else{
            for (int i = numElem-1; i >= 0; i--){
                cout<<*(array+i)<<endl;
            }
        }
    } 
    
    static void bubble(int* array, int numElem){
        //Declaramos auxiliar para realizar intercambio
        int aux;
        bool isOrder = false;

        unsigned intialTime, finalTime;
        intialTime = clock();

        while (!isOrder){
            isOrder = true;

            /*Recorremos cada elememto del arreglo menos el ultimo, ya que es el
            que queda ordenado en cada iteracion*/
            for (int i = 0; i < numElem-1; i++){

                if (*(array+i) > *(array+i+1)){
                    aux = *(array+i); 
                    *(array+i) = *(array+i+1); 
                    *(array+i+1) = aux; 
                    isOrder =  false;
                }
            }   
        }
        finalTime = clock();
        double totalTime = double(finalTime-intialTime) / CLOCKS_PER_SEC;
        cout<<"Bubble sorter has finished in "<<totalTime<<" seconds\n";
    }

    static void insertion(int* array, int numElem){
        int pos, aux;
        unsigned intialTime, finalTime;
        intialTime = clock();

        for (int i = 1; i < numElem; i++){ //Recorremos cada elemento desde la 2da posicion
            pos = i; //Position en la que va
            aux = *(array+i); //Valor del numero de la iteracion
            while (aux < *(array+i-1)){ //Bucle para mover elementos menores
                *(array+i) = *(array+i-1);
                pos--;
            }
            *(array+pos) = aux;
        }
        finalTime = clock();
        double totalTime = double(finalTime-intialTime) / CLOCKS_PER_SEC;
        cout<<"Insertion sorter has finished in "<<totalTime<<" seconds\n";
    }

    static void selection(int* array, int numElem){
        int i, j, aux, min;

        unsigned intialTime, finalTime;
        intialTime = clock();
        
        for (i = 0; i < numElem; i++){ //Recorremos cada elemento del array
            min = *(array+i); //Definimos el valor de la iteracion por defecto como el valor minimo
            for (j = i+1; j < numElem; j++){ //Empezamos a recorrer desde el siguiente elemento
                //Si el siguitente elemento es menor hacemos el intercambio
                if (*(array+j) < min){ min = *(array+j); }
            }

        //En la posicion de iteracion reemplazamos el valor que haya sido definido como el minimo
        aux = *(array+i);
        *(array+i) = min;
        min = aux;
        }
        finalTime = clock();
        double totalTime = double(finalTime-intialTime) / CLOCKS_PER_SEC;
        cout<<"Selection sorter has finished in "<<totalTime<<" seconds\n";
    }

    static void scanning(int* array, int numElem){
        int minPos, maxPos, minAux, maxAux;
        int lastPos = numElem-1;

        unsigned intialTime, finalTime;
        intialTime = clock();
        
        for (int i = 0; i < numElem/2; i++){
            minPos = i;
            maxPos = i;

            for (int j = i; j <= lastPos; j++){
                if (*(array+j) < *(array+minPos)){ minPos = j; }
                if (*(array+j) > *(array+maxPos)){ maxPos = j; }
            }

            minAux = *(array+minPos);
            *(array+minPos) = *(array+i);
            *(array+i) = minAux;

            if (maxPos == i){ maxPos = minPos; }

            maxAux = *(array+lastPos);
            *(array+lastPos) = *(array+maxPos);
            *(array+maxPos) = maxAux;
            lastPos--;
        }
        finalTime = clock();
        double totalTime = double(finalTime-intialTime) / CLOCKS_PER_SEC;
        cout<<"Scanning sorter has finished in "<<totalTime<<" seconds\n";   
    }

    static void mySorter(int* array, int numElem){
        int max = *(array+0);

        for (int i = 1; i < numElem; i++){
            if (*(array+i) > max){ max = *(array+i); }
        }

        for (int i = 0; i < numElem; i++){
            if (*(array+i) < max/2){
                /* code */
            }
            
        }
        
        
    }
};

int main(){
    int nums;
    cout<<"Arrays' positions => ";
    cin>>nums;

    int* array = new int[nums]; 

    for (int i = 0; i < nums; i++){
        cout<<"Array position ["<<i<<"] => ";
        cin>>*(array+i);
    }
    
    cout<<"Original array:\n";
    Sorter::show(array, nums);
    cout<<"---------------\n";

    //Sorter::bubble(array, nums);
    //cout<<"Bubble order:\n";
    //Sorter::show(array, nums);
    //cout<<"---------------\n";
    //
    //Sorter::insertion(array, nums);
    //cout<<"Insertion order:\n";
    //Sorter::show(array, nums);
    //cout<<"---------------\n";
    //
    //Sorter::selection(array, nums);
    //cout<<"Selection order:\n";
    //Sorter::show(array, nums);
    //cout<<"---------------\n";

    Sorter::scanning(array, nums);
    cout<<"Scanning order:\n";
    Sorter::show(array, nums);
    cout<<"---------------\n";

    delete[] array;

    system("pause");
    return 0;
}