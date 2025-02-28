/*Ejercicio de aplicacion de compras para practicar el uso de listas enladas a traves de nodos
que tengan 1 puntero hacia la siguiemte posicion*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

enum optionMenu {exitOp, showOp, addOp, deleteOp};

struct ListElement{
    char product[64];
    int price;
    int amount;
    ListElement* nextElement;
};

class List{
private:
    ListElement* header;
    int listElements;
public:
    List(){ 
        header = nullptr; 
        listElements = 0; 
    };
    ~List(){
        ListElement* currentElem = header;
        while (currentElem){
            ListElement* temp = currentElem;
            currentElem = currentElem->nextElement;
            delete temp;
        }
    };

    int getElementsNum() const { return this->listElements; }

    int showElements(void) const {
        if (!header){ //Cuando el header es null
            cout<<"There is nothing to show\n";
            return 1;
        }
        
        int id = 1;
        //Variable temporal que usaremos para recorrer
        ListElement* temp = header; 
        cout<<"ID\tElement\t\tAmount\tUnit Price\tTotal Product Price\n";
        while (temp){
            cout<<id<<"\t"<<temp->product<<"\t\t"<<temp->amount<<"\t";
            cout<<temp->price<<"\t\t$"<<temp->amount*temp->price<<"\n";
            //Despues de imprimir los valores de temporal, la redifinimos para el sgte elemento
            temp = temp->nextElement;
            id++;
        }
        return 0;
    }
    
    bool elementExists(ListElement* toComprobe) const {
        ListElement* temp = header;
        while (temp){
            if (strcmp(toComprobe->product, temp->product) == 0 && toComprobe->price == temp->price){
                return true;
            }
            temp = temp->nextElement;
        }
        return false;
    }

    void increaseAmount(ListElement* newData){
        ListElement* temp = header;
        while (temp){
            //Al encontrar elemento coincidente aumentamos su cantidad y rompemos el bucle
            if (strcmp(newData->product, temp->product) == 0 && newData->price == temp->price){
                temp->amount += newData->amount;
                break;
            }
            temp = temp->nextElement;
        }
        cout<<"Amount of "<<temp->product<<" has been updated ("<<temp->amount<<")\n";
    }

    void addElement(ListElement* newElement){
        //Si el header esta vacio agregaremos al header el elemento a agregar
        if (!header){ header = newElement; } 
        else {
            //Variable temporal para recorrer los elementos hasta que no haya un sgte
            ListElement* temp = header;
            while (temp->nextElement){
                temp = temp->nextElement;
            }
            //Al no haber mas elementos despues de temporal, definimos como ultimo elemento al nuevo
            temp->nextElement = newElement;
        }
        listElements++;
        cout<<newElement->product<<" has been added succesfully\n";
    }

    int deleteElement(int idToDelete){
        if (idToDelete <= 0 || idToDelete > this->listElements){ 
            throw out_of_range("Number out of range\n"); 
        }

        if (idToDelete == 1){
            /*Si el ID es 1, quiere decir que hay que borrar el 1er elemento, 
            borramos el header y lo volvemos a crear con el elemento al que 
            inicialmente apuntaba*/
            ListElement* next = header->nextElement; 
            delete header;
            header = next;
            this->listElements--;
            return 0;
        } else {
            ListElement* temp = header;
            int idIter = 1;        
            while (temp){
                /*Evaluamos desde el elemento anterior al que queremos borrar 
                para redireccionar los punters*/
                if (idIter == idToDelete-1){ 
                    ListElement* toDelete = temp->nextElement;
                    /*Si el elemento que queremos borrar es el ultimo, asignamos
                    el puntero de su elemento anterior a null, de lo contrario
                    el elemento anterior tomara el puntero que tenga al sgte elemento*/
                    if (!toDelete->nextElement){
                        temp->nextElement = nullptr;
                    } else {
                        temp->nextElement = toDelete->nextElement;
                    }
                    delete toDelete;
                    this->listElements--;
                    return 0;
                }
                temp = temp->nextElement;
                idIter++;
            }
        }
        return -1;
    }

};

int main(){

    List* shoppingList = new List();
    optionMenu option;
    int opt, toDelete;
    bool exists;
    
    do{
        cout<<"SuperMarket Menu:\t\tYou have "<<shoppingList->getElementsNum()<<" products\n\t1. Show my list";   
        cout<<"\n\t2. Add product\n\t3. Delete product\n\t0. Exit\n";
        cin>>opt;
        option = static_cast<optionMenu>(opt);

        switch (option){
            case exitOp:
                cout<<"Thanks for buying with us\n";
                break;

            case showOp:
                cout<<"----------------------------------------------------\n";
                shoppingList->showElements();
                cout<<"----------------------------------------------------\n";
                system("pause"); system("cls");
                break;
            
            case addOp: {
                ListElement* newProduct = new ListElement();
                cout<<"Type the product's name -> ";
                cin.ignore();
                cin.getline(newProduct->product, 64);

                cout<<"Type the product's price -> ";
                cin>>newProduct->price;

                cout<<"Type the product's amount -> ";
                cin>>newProduct->amount;

                newProduct->nextElement = nullptr;

                exists = shoppingList->elementExists(newProduct);
                if (exists){
                    shoppingList->increaseAmount(newProduct);
                } else {
                    shoppingList->addElement(newProduct);
                }
                
                system("pause"); system("cls");
                break;
            }

            case deleteOp:
                if (shoppingList->showElements() == 0){
                    bool inRange;
                    do{
                        cout<<"Type the product's id to delete -> ";
                        cin>>toDelete;
                        inRange = true;
                        if (toDelete > shoppingList->getElementsNum()){
                            cout<<"Id out of range, try again\n";
                            inRange = false;
                        }    
                    } while (!inRange);
                    int deleted = shoppingList->deleteElement(toDelete);
                    if (deleted == 0){
                        cout<<"----------------------------------------------------\n";
                        cout<<"Product eliminated successfully\n";
                        cout<<"----------------------------------------------------\n";
                    } else {
                        cout<<"----------------------------------------------------\n";
                        cout<<"Error deleting product\n";
                        cout<<"----------------------------------------------------\n";
                    }
                }
                system("pause"); system("cls");
                break;

            default:
                cout<<"Invalid option, try again\n";
                break;
        }

    } while (option != optionMenu::exitOp);
    
    delete shoppingList;
    return 0;
}