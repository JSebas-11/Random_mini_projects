/*Ejercicio para practicar el manejo de archivos binarios: 
    Crear una agenda basica que permita: ingresar, buscar, listar, eliminar y actualizar contactos
    almacenando la informacion en un archivo.dat. Se debe usar programacion orientada a objetos o
    otras estructuras de datos*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <limits>

using namespace std;

//-----------------DECLARACION CONSTANTES------------------------------------
const string DIRNAME = "..\\files-Files\\contacts.dat"; //Ruta en la que se creara el archivo con la data
//Ruta en la que se creara el archivo con la data temporal para operaciones de actualizacion y elminacion
const string DIRTEMPNAME = "..\\files-Files\\temp.dat"; 
//Colores para la consola con codigos ANSI
const string WHITE = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";

//-----------------DECLARACION Y PROTOTIPADO DE FUNCIONES GENERALES----------
string toLower(string str);

void pauseScreen();
int clearScreen();

//-----------------DECLARACION Y PROTOTIPADO DE ESTRUCTURAS Y CLASES USADAS--
struct contact{
    char name[64];
    unsigned int number;
    int prefix = 57;

    //Metodo encargado de pedir y establecer el numero telefonico, asegurandose que tenga la cantidad de digitos requeridos 
    void askForNumber(string type = "init"); 
    void initContact(); //Metodo para inicializar los campos de un contacto
    int update(string which = "all"); //Metodo para actualizar un contacto ya sea todos o un campo especifico
    void show(); //Metodo para mostrar los datos de un contacto
};

class Directory{ //Clase que se encarga de gestionar los contactos
private:
    ofstream writtingFile; //Objeto para escribir en el archivo
    ofstream tempFile; //Objeto para escribir en el archivo temporal
    ifstream readingFile; //Objeto para leer el archivo
    string filePath;
    int contactsAmount;

    int countContacts();
    
public:
    Directory(string _filePath = DIRNAME) : filePath(_filePath) {
        this->contactsAmount = this->countContacts();
    }
    ~Directory() {}

    int addContact(contact newContact);
    bool contactExists(string by, string name = "undefined", unsigned int number = 0);
    contact returnContact(string by, string name = "undefined", unsigned int number = 0);
    int showContacts();
    int deleteContact(contact toDelete);
    int updateContact(contact oldContact, contact newContact);
};

//-----------------DECLARACION Y PROTOTIPADO DE SECCIONES--------------------
void showSection(Directory* directory);
void searchSection(Directory* directory);
void addSection(Directory* directory);
void deleteSection(Directory* directory);
void updateSection(Directory* directory);

//-----------------MAIN FUNCTION---------------------------------------------
int main(){
    Directory* directory = new Directory();
    string action;

    do{
        cout<<"Main Menu:\n\t1.Show Contacts\n\t2.Search Contact\n\t3.Add Contact\n\t4.Delete Contact\n\t5.Update Contact\n\t0.Exit\n";
        getline(cin, action);

        if (action == "0"){
            cout<<GREEN<<"Closing program..."<<WHITE;
        }
        else if (action == "1"){
            showSection(directory);
        }
        else if (action == "2"){
            searchSection(directory);
        }
        else if (action == "3"){
            addSection(directory);
        }
        else if (action == "4"){
            deleteSection(directory);
        }
        else if (action == "5"){
            updateSection(directory);
        }
        else{
            cout<<YELLOW<<"Invalid option, try again"<<WHITE<<"\n";
        }
        
    } while (action != "0");
    
    delete directory;

    return 0;
}

//-----------------IMPLEMENTACION DE FUNCIONES GENERALES---------------------
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void pauseScreen(){
    cout<<YELLOW<<"Press any key to continue..."<<WHITE;
    cin.get();
}

int clearScreen(){
    #ifdef _WIN32 //Si el sistema operativo es Windows
        system("cls");
    #else
        cout<<"\033[2J\033[1;1H"; //Limipia la pantalla y mueve el cursor a posicion 1,1
    #endif
        return 0;
} 

//-----------------IMPLEMENTACION METODOS DE STRUCT Y CLASS------------------
//-----------------CONTACT STRUCT:
void contact::askForNumber(string type){
    bool isRight;
    string numberStr;

    do{ //Nos aseguramos que el numero ingresa tenga 10 digitos para castearlo al tipo de dato adecuado
        if (type == "init"){ cout<<"Type the contact's number => "; }
        else if (type == "update"){ cout<<"Type the new number => "; }
        
        getline(cin, numberStr);

        if (numberStr.size() != 10){
            isRight = false;
            cout<<YELLOW<<"The number must have 10 digits, try again"<<WHITE<<"\n";
        }
        else{
            isRight = true;

            //Intentamos castear el string a un unsigned int
            try{ this->number = stoul(numberStr); }
            catch(const invalid_argument& e) {
                cout<<YELLOW<<"You must enter a number, try again"<<WHITE<<"\n";
                isRight = false;
            }
        }
        
    } while (!isRight);
}

void contact::initContact(){ 
    cout<<"Type the name => ";
    cin.getline(this->name, 64);
    this->askForNumber();
}

int contact::update(string which){ 

    if (which == "all"){
        cout<<"Type the new name => "; cin.getline(this->name, 64);
        this->askForNumber("update");
        cout<<"Type the new prefix => "; cin>>this->prefix;
        cin.ignore();
        return 0;
    } 
    else if (which == "name"){
        cout<<"Type the new name => "; cin.getline(this->name, 64);
        return 0;
    }
    else if (which == "number"){
        this->askForNumber("update");
        return 0;
    }
    else if (which == "prefix"){
        cout<<"Type the new prefix => "; cin>>this->prefix;
        cin.ignore();
        return 0;
    }
    else {
        throw invalid_argument("Invalid argument, must be 'name', 'number', 'prefix' or 'all'\n");
    }
    
    return 1;
}

void contact::show(){ 
    cout<<"Name: "<<this->name<<"\n\t +"<<this->prefix<<" "<<this->number<<"\n";
}

//-----------------DIRECTORY CLASS:
int Directory::countContacts(){
    //Abrimos y recorremos los objetos del archivo para contar cuantos contactos hay
    readingFile.open(this->filePath, ios::binary);
    contact importedCont;

    int count = 0;
    if (readingFile.good()){
        while (readingFile.read((char*)&importedCont, sizeof(contact))){
            count++;
        }
    }
    readingFile.close();
    return count;
}

int Directory::addContact(contact newContact) {
    //Metodo que recibe un objeto contact y lo escribe en el archivo (retorna si hay fallos)
    writtingFile.open(this->filePath, ios::app | ios::binary);
    
    if (writtingFile.good()) {
        writtingFile.write((char*)&newContact, sizeof(contact));
        this->contactsAmount++;
    } else {
        writtingFile.close();
        return 1;
    }
    writtingFile.close();
    return 0;
}

bool Directory::contactExists(string by, string name, unsigned int number){
    /*Metodo que dependiendo el by verificara si existe un contacto con ese dato*/
    if (by != "name" && by != "number" && by != "both") {
        throw invalid_argument("Invalid argument, must be 'name', 'number' or 'both'\n");
    }
    
    readingFile.open(this->filePath, ios::binary);
    contact importedCont;
    
    if (!readingFile.is_open()) { return false; }

    if (readingFile.good()){

        while (readingFile.read((char*)&importedCont, sizeof(contact))) {
            if (by == "both") {
                if (toLower(importedCont.name) == toLower(name) && importedCont.number == number) {
                    readingFile.close();
                    return true;
                }
            } else if (by == "name") {
                if (toLower(importedCont.name) == toLower(name)) {
                    readingFile.close();
                    return true;
                }
            } else if (by == "number") {
                if (importedCont.number == number) {
                    readingFile.close();
                    return true;
                }
            }
        }
        
        readingFile.close();
        return false;

    } else {
        readingFile.close();
        return false;
    }
}

contact Directory::returnContact(string by, string name, unsigned int number){
    //Metodo que dependiendo el by retornara el contacto con ese dato
    if (by != "name" && by != "number" && by != "both") {
        throw invalid_argument("Invalid argument, must be 'name', 'number' or 'both'\n");
    }
    
    readingFile.open(this->filePath, ios::binary);
    contact importedCont;
        
    while (readingFile.read((char*)&importedCont, sizeof(contact))) {
        if (by == "both") {
            if (toLower(importedCont.name) == toLower(name) && importedCont.number == number) {
                readingFile.close();
                return importedCont;
            }
        } else if (by == "name") {
            if (toLower(importedCont.name) == toLower(name)) {
                readingFile.close();
                return importedCont;
            }
        } else if (by == "number") {
            if (importedCont.number == number) {
                readingFile.close();
                return importedCont;
            }
        }
    }
    readingFile.close();
    return importedCont;
}

int Directory::showContacts(){
    //Metodo que muestra todos los contactos en el archivo con cierto formato (retorna 1 si hay fallos)
    readingFile.open(this->filePath, ios::binary);
    
    if (!readingFile.is_open()){
        readingFile.close();
        return 1;
    }

    if (readingFile.good()){
        contact importedCont;
        cout<<"------------------------------------------\nYour Contacts:\t\t\t";
        cout<<this->contactsAmount<<" contacts\n\n";
        while (readingFile.read((char*)&importedCont, sizeof(contact))){
            importedCont.show();
        }
        cout<<"------------------------------------------\n";
    } else {
        readingFile.close();
        return 1;
    }

    readingFile.close();
    return 0;
}

int Directory::deleteContact(contact toDelete){
    //Metodo para eliminar contacto mediante tecnica de reescritura
    readingFile.open(this->filePath, ios::binary);
    tempFile.open(DIRTEMPNAME, ios::binary);

    if (!readingFile.is_open() || !tempFile.is_open()){
        readingFile.close();
        tempFile.close();
        remove(DIRTEMPNAME.c_str());
        return 1;
    }

    if (readingFile.good() && tempFile.good()){
        contact importedCont;
        while (readingFile.read((char*)&importedCont, sizeof(contact))){
            if (!(strcmp(importedCont.name, toDelete.name) == 0 && importedCont.number == toDelete.number)){
                tempFile.write((char*)&importedCont, sizeof(contact));
            }
        }
    } else {
        tempFile.close();
        readingFile.close();
        remove(DIRTEMPNAME.c_str());
        return 1;
    }

    tempFile.close();
    readingFile.close();

    remove(this->filePath.c_str()); //c_str() convierte el string a un puntero char
    rename(DIRTEMPNAME.c_str(), this->filePath.c_str());
    
    this->contactsAmount--;
    return 0;   
}

int Directory::updateContact(contact oldContact, contact newContact){
    //Metodo para eliminar contacto mediante tecnica de reescritura
    readingFile.open(this->filePath, ios::binary);
    tempFile.open(DIRTEMPNAME, ios::binary);

    if (!readingFile.is_open() || !tempFile.is_open()){
        readingFile.close();
        tempFile.close();
        remove(DIRTEMPNAME.c_str());
        return 1;
    }

    if (readingFile.good() && tempFile.good()){
        contact importedCont;

        while (readingFile.read((char*)&importedCont, sizeof(contact))){
            
            if (strcmp(importedCont.name, oldContact.name) == 0 && importedCont.number == oldContact.number){
                tempFile.write((char*)&newContact, sizeof(contact));
            } else {
                tempFile.write((char*)&importedCont, sizeof(contact));
            }

        }

    } else {
        tempFile.close();
        readingFile.close();
        remove(DIRTEMPNAME.c_str());
        return 1;
    }

    tempFile.close();
    readingFile.close();

    remove(this->filePath.c_str()); 
    rename(DIRTEMPNAME.c_str(), this->filePath.c_str());
    
    return 0;  
}

//-----------------IMPLEMENTACION FUNCIONES SECCIONES------------------------
void showSection(Directory* directory){
    clearScreen();
    directory->showContacts();
    pauseScreen();
    clearScreen();
}

void searchSection(Directory* directory){
    clearScreen();
    string searchBy, name;
    unsigned int number;
    bool exists;

    while (true){
        cout<<"Search by:\n\t1.Name\n\t2.Number\n\t3.Both\n\t0.Back\n";
        cin>>searchBy;
        if (searchBy == "0"){
            pauseScreen();
            clearScreen();
            break;
        }
        else if (searchBy == "1"){
            cout<<"Type the name => ";
            cin>>name;
            exists = directory->contactExists("name", name);
        } 
        else if (searchBy == "2"){
            cout<<"Type the number => ";
            cin>>number;
            cin.ignore();
            exists = directory->contactExists("number", "undefined", number);
        } 
        else if (searchBy == "3"){
            cout<<"Type the name => ";
            cin>>name;
            cout<<"Type the number => ";
            cin>>number;
            cin.ignore();
            exists = directory->contactExists("both", name, number);
        }
        else {
            cout<<YELLOW<<"Invalid option, try again"<<WHITE<<"\n";
            continue;
        }

        if (exists){
            cout<<"------------------------------------------\n";
            if (searchBy == "1"){
                directory->returnContact("name", name).show();
            }
            else if (searchBy == "2"){
                directory->returnContact("number", "undefined", number).show();
            }
            else if (searchBy == "3"){
                directory->returnContact("both", name, number).show();
            }
            cout<<"------------------------------------------\n";
        }
        else{
            cout<<RED<<"The contact does not exist"<<WHITE<<"\n";
            continue;
        }
    }
}

void addSection(Directory* directory){
    contact newCont;
    newCont.initContact();

    if (directory->contactExists("both", newCont.name, newCont.number)){
        cout<<YELLOW<<"The contact already exists"<<WHITE<<"\n";
    } else {
        if (directory->addContact(newCont) == 0){
        cout<<GREEN<<"Contact added successfully"<<WHITE<<"\n";
        } else {
            cout<<RED<<"Error adding contact"<<WHITE<<"\n";
        };
    }
    
    pauseScreen();
    clearScreen();
}

void deleteSection(Directory* directory){
    string name;
    unsigned int number;

    directory->showContacts();
    cout<<"Type the contact's name to delete => ";
    getline(cin, name);
    cout<<"Type the contact's number to delete => ";
    cin>>number;
    cin.ignore();

    if (directory->contactExists("both", name, number)){
        contact toDelete = directory->returnContact("both", name, number);
        
        if (directory->deleteContact(toDelete) == 0){
            cout<<GREEN<<"Contact deleted successfully"<<WHITE<<"\n";
        } else {
            cout<<RED<<"Error deleting contact"<<WHITE<<"\n";
        }  

    } else {
        cout<<RED<<"Error, the contact does not exist"<<WHITE<<"\n";
    }
    pauseScreen();
    clearScreen();
}

void updateSection(Directory* directory){
    string name;
    unsigned int number;

    directory->showContacts();
    cout<<"Type the contact's name to update => ";
    getline(cin, name);
    cout<<"Type the contact's number to update => ";
    cin>>number;
    cin.ignore();

    if (directory->contactExists("both", name, number)){
        contact toUpdate = directory->returnContact("both", name, number);
        contact oldContactAux = toUpdate;
        
        string action;
        bool finish = false;
        int change = 1;

        do{
            cout<<"What do you want to change:\n\t1.Name\n\t2.Number\n\t3.Prefix\n\t4.All\n";
            getline(cin, action);
            if (action == "1"){
                change = toUpdate.update("name");
                finish = true;
            }
            else if (action == "2"){
                change = toUpdate.update("number");
                finish = true;
            }
            else if (action == "3"){
                change = toUpdate.update("prefix");
                finish = true;
            }
            else if (action == "4"){
                change = toUpdate.update();
                finish = true;
            }
            else {
                cout<<YELLOW<<"Invalid option, try again"<<WHITE<<"\n";
            }

        } while (!finish);

        if (directory->updateContact(oldContactAux, toUpdate) == 0 || change == 0){
            cout<<GREEN<<"Contact updated successfully"<<WHITE<<"\n";
        } else {
            cout<<RED<<"Error updating contact"<<WHITE<<"\n";
        }  

    } else {
        cout<<RED<<"Error, the contact does not exist"<<WHITE<<"\n";
    }
    pauseScreen();
    clearScreen();
}