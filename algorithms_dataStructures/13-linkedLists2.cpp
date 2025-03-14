/*Ejercicio para practicar uso de listas doblemente enlazadas por medio de punteros: 
Desarrollar un programa que permita gestionar una colección de videojuegos
Funcionalidades requeridas:
    -Evitar nombres duplicados en la lista. Ψ
    -Agregar un videojuego a la lista. Ψ
    -Mostrar todos los videojuegos en la lista. Ψ
    -Buscar un videojuego por nombre. Ψ
    -Eliminar un videojuego por nombre. Ψ
    -Modificar los datos de un videojuego. Ψ
    -Exportar lista a un archivo binario o csv. Ψ
    -Importar la lista desde un archivo csv Ψ*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <vector>
#include <any>

using namespace std;

const int CHARSIZE = 32;
const int SPACING = 18;
const int LINE_SIZE = 256;
const char STRAIGHT_LINES[] = "----------------------------------------------\n";
//Ruta por defecto donde almacenar los archivos exportados a binaro
const char DEFAULT_BIN_PATH[] = "..\\LinkedList-Bin_csv\\linkedList.bin";
//Ruta por defecto donde almacenar los archivos exportados a csv
const char DEFAULT_CSV_PATH[] = "..\\LinkedList-Bin_csv\\linkedList.csv";
//Rutas archivos precargados
const char DEFAULT_BIN[] = "..\\LinkedList-Bin_csv\\preloaded.bin";
const char DEFAULT_CSV[] = "..\\LinkedList-Bin_csv\\preloaded.csv";

vector<char*> split(char line[LINE_SIZE], char sep = ';'){ //Vector con campos de struct Game
    vector<char*> gameVector = {}; 
    /*Struct tiene 5 campos pero asignamos 4 ya que al final habra un campo sin separador,
    esto sera comprobado mediante la 2da condicion del for*/
    int gameFields = 4; 
    int fields = 0;
    char* word = new char[CHARSIZE];
    int wordIndex = 0;
    
    for (int i = 0; fields < gameFields || line[i] != '\0'; i++){
        /*Si char iterado es el sep agregaremos al vector la palabra anteriormente formada
        y reinciamos palabra*/
        if (line[i] == sep){
            word[wordIndex] = '\0'; 
            gameVector.push_back(word);
            fields++;
            wordIndex = 0;
            word = new char[CHARSIZE];
            continue;
        }
        //Acumulamos chars para formar la palabra
        word[wordIndex] = line[i];
        wordIndex++;
    }

    if (wordIndex > 0){ //Agregar la palabra que no tiene separador
        word[wordIndex] = '\0';
        gameVector.push_back(word);
    }

    return gameVector;
};

struct Game{ //Struct que actuara como nodo de la lista
    char title[CHARSIZE];
    char genre[CHARSIZE];
    char platform[CHARSIZE];
    char publisher[CHARSIZE];
    int releaseYear;
    Game* previous;
    Game* next;

    void showInfo(){
        cout<<left<<setw(SPACING)<<this->title<<setw(SPACING)<<this->genre<<setw(SPACING)
        <<this->platform<<setw(SPACING)<<this->publisher<<setw(SPACING)<<this->releaseYear<<"\n";
    }

    void initFields(){
        cout<<"Type the title's game -> ";
        cin.getline(this->title, CHARSIZE);
        cout<<"Type the genre's game -> ";
        cin.getline(this->genre, CHARSIZE);
        cout<<"Type the platform's game -> ";
        cin.getline(this->platform, CHARSIZE);
        cout<<"Type the publisher's game -> ";
        cin.getline(this->publisher, CHARSIZE);

        while (true){ //Ciclo para asegurarse que el usuario inserte un numero
            
            cout<<"Type the release year of game -> ";
            cin>>this->releaseYear;
            
            if (cin.fail()){
                cin.clear();
                cin.ignore(1024, '\n');
                cout<<"You have to introduce a number\n";
                continue;
            }
            break;
        }

        this->previous = nullptr;
        this->next = nullptr;
    }

    void initByVector(vector<char*> data){
        strcpy(this->title, data[0]);
        strcpy(this->genre, data[1]);
        strcpy(this->platform, data[2]);
        strcpy(this->publisher, data[3]);
        this->releaseYear = atoi(data[4]);

        this->previous = nullptr;
        this->next = nullptr;
    }

    void modifyFields(){
        cout<<"Type the new title's game -> ";
        cin.getline(this->title, CHARSIZE);
        cout<<"Type the new genre's game -> ";
        cin.getline(this->genre, CHARSIZE);
        cout<<"Type the new platform's game -> ";
        cin.getline(this->platform, CHARSIZE);
        cout<<"Type the new publisher's game -> ";
        cin.getline(this->publisher, CHARSIZE);

        while (true){
            
            cout<<"Type the new release year of game -> ";
            cin>>this->releaseYear;
            
            if (cin.fail()){
                cin.clear();
                cin.ignore(1024, '\n');
                cout<<"You have to introduce a number\n";
                continue;
            }
            break;
        }
    }

};

class List{
private:
    int gamesNum;
    Game* header;
    
    static void format(){
        //STRAIGHT_LINES y funcion setw son para darles un 'formato'
        cout<<STRAIGHT_LINES;
        cout<<left<<setw(5)<<"Pos."<<setw(SPACING)<<"Name"<<setw(SPACING)<<"Genre"<<setw(SPACING)
            <<"Platform"<<setw(SPACING)<<"Publisher"<<"Release Year\n";
        cout<<STRAIGHT_LINES;
    }
public:
    List(){
        //Al crear lo definimos con 0 elementos y el header nulo
        gamesNum = 0;
        header = nullptr;
    };
    ~List(){
        Game* current = header;
        while (current){
            Game* temp = current;
            current = current->next;
            delete temp;
        }
    };
    
    //Uso de const para garantizar que el objeto (List) no se modifique
    bool isEmpty() const { return (this->gamesNum == 0); }

    int getNumElements() const { return this->gamesNum; }

    //Uso de referencias constantes para no crear copias innecesarias en parametros
    bool gameExists(const Game& toComprobe) const {
        Game* temp = header;
        while (temp){
            if (strcmp(toComprobe.title, temp->title) == 0){ return true; }
            temp = temp->next;
        }
        return false;
    }

    void show() const { //Mostrar los elementos
        Game* temp = header;
        cout<<"Games ("<<this->gamesNum<<")\n";
        List::format();
        int position = 0;
        while (temp){
            cout<<left<<setw(5)<<position;
            temp->showInfo();
            temp = temp->next;
            position++;
        }
        cout<<STRAIGHT_LINES;
    }

    void addGame(Game* toAdd){ //Agregar elementos a la lista
        //Si el header esta nulo, ingresamos el elemento en él
        if (!header){ header = toAdd; }
        else {
            Game* temp = header;
            while (temp){
                /*Si no hay un sgte elemento (fin de lista), asignamos los 
                punteros como corresponden para enlazarlos doblemente*/
                if (!temp->next){
                    temp->next = toAdd;
                    toAdd->previous = temp;
                    break;
                }
                temp = temp->next;
            }
        }
        this->gamesNum++;
        cout<<toAdd->title<<" has been added successfully\n";
    }

    void lookFor(const char* titleToSearch) const { //Buscar elementos por nombre
        Game* temp = header;
        int position = 0;
        while (temp){
            if (strcmp(temp->title, titleToSearch) == 0){
                List::format();
                cout<<left<<setw(5)<<position;
                temp->showInfo();
                cout<<STRAIGHT_LINES;
                return;
            }
            position++;
            temp = temp->next;
        }
        cout<<titleToSearch<<" not found\n";
    }

    void deleteGame(const char* titleToDel){ //Borrar elementos
        //Comprobamos si el elemento que hay que borrar esta en el header
        if (strcmp(header->title, titleToDel) == 0){
            //Si no hay un sgte elemento dejamos el puntero nul
            if (!header->next){
                header = nullptr;
            } else {    
                /*En caso de si haber mas elementos, borramos el header
                y lo creamos de nuevo asginandole el elemento que seguia 
                en la lista*/
                Game* next = header->next;
                delete header;
                header = next;
                header->previous = nullptr;
            }
            this->gamesNum--;
            cout<<titleToDel<<" deleted successfully\n";
            return;
        } else {    
            //Iniciamos desde el segundo elemento, ya que el header ya fue comprobado
            Game* temp = header->next;
            while (temp){
                if (strcmp(temp->title, titleToDel) == 0){
                    Game* toDelete = temp;
                    
                    /*Si el elemento a borrar es el ultimo, asignamos el puntero next del 
                    elemento anterior a nulo, ya que no hay mas elementos*/
                    if (!toDelete->next){
                        toDelete->previous->next = nullptr;
                    } else {
                    /*Si hay mas elementos despues del que queremos borrar, asignamos el
                    puntero next del elemento anterios al sgte del que borraremos y el 
                    puntero previous del next elemento al previo del actual. Borrando
                    asi las referencias al elemento a borrar y redireccionando los punteros
                    a los elementos que corresponden*/
                        toDelete->previous->next = toDelete->next;
                        toDelete->next->previous = toDelete->previous;
                    }
                    
                    delete toDelete;
                    this->gamesNum--;
                    cout<<titleToDel<<" deleted successfully\n";
                    return;
                }
                temp = temp->next;
            }
        }
        cout<<titleToDel<<" couldnt be deleted (Maybe it doesnt exist)\n";
    }

    Game* getGame(const char* toReturn){ //Obtener puntero Game apartir del title
        Game* temp = header;
        while (temp){
            if (strcmp(temp->title, toReturn) == 0){
                return temp;
            }
            temp = temp->next;
        }
        //En caso de no ser encontrado lanzamos excepcion (Sera capturada en el Main)
        throw runtime_error("Game not found\n");
    }

    int exportToBin(const char* path) const {
        //Exportar a la ruta un archivo binario con los elementos contenidos 
        
        /*Creamos y abrimos archivo en modo binario y modo trunc para borrar contenido de archivo
        si este ya existe y poder realizar las correspondientes operaciones*/
        ofstream exportedList;
        exportedList.open(path, ios::binary | ios::trunc);

        if (!exportedList.good()){
            exportedList.close();
            return -1;
        }

        Game* temp = header;
        while (temp){
            //Por cada elemento pasamos individualmente sus atributos
            exportedList.write((char*)&temp->title, sizeof(temp->title));  
            exportedList.write((char*)&temp->genre, sizeof(temp->genre));  
            exportedList.write((char*)&temp->platform, sizeof(temp->platform));  
            exportedList.write((char*)&temp->publisher, sizeof(temp->publisher));  
            exportedList.write((char*)&temp->releaseYear, sizeof(temp->releaseYear));
            temp = temp->next;
        }

        exportedList.close();
        return 0;
    }

    int exportToCsv(const char* path) const {
        //Exportar a la ruta un archivo txt con los elementos contenidos
        
        /*Creamos y abrimos archivo en modo escritura y modo trunc para borrar contenido de archivo
        si este ya existe y poder realizar las correspondientes operaciones*/
        ofstream exportedList;
        exportedList.open(path, ios::out | ios::trunc);

        if (!exportedList.good()){
            exportedList.close();
            return -1;
        }

        Game* temp = header;
        //Escribimos en el archivo el head con los nombres de las columnas
        exportedList<<"title;genre;platform;publisher;releaseYear\n";

        while (temp){
            //Escribimos en el archivo los datos de cada elemento con el formato indicado
            exportedList<<temp->title<<";"<<temp->genre<<";"<<temp->platform
                        <<";"<<temp->publisher<<";"<<temp->releaseYear<<"\n";
            temp = temp->next;
        }
        
        exportedList.close();
        return 0;
    }

    int importCsv(const char* path){
        //Creamos y abrimos archivo con la data en modo lectura
        ifstream importedList;
        importedList.open(path);

        if (!importedList.good()){
            importedList.close();
            return -1;
        }

        char line[LINE_SIZE] = {0};
        int i = 0;
        while (importedList.getline(line, LINE_SIZE)){
            if (i == 0){ //Ignoramos 1ra linea ya que contiene los headers del dataset
                i++;
                continue;
            }
            
            //Creamos objeto e inilizamos sus campos para ser agregado a la lista
            Game* newElem = new Game();
            vector<char*> data = split(line); //Separamos cada campo y los almacenamos en un vector
            newElem->initByVector(data);
            this->addGame(newElem);
            i++;
        }

        importedList.close();
        return 0;
    }
};

void cleanAndWait(){
    system("pause");
    system("cls");
};

int main(){
    List* myGames = new List();
    int option;

    do{
        cout<<"Main menu\n\t1.Show games\n\t2.Add game\n\t3.Search game\n\t4.Delete game\n\t";
        cout<<"5.Modify data game\n\t6.Export List\n\t7.Load List\n\t0.Exit\n";
        cin>>option;
        cin.clear();

        switch (option){
            case 0:
                cout<<"Closing program...\n";
                break;

            case 1:{
                if (myGames->isEmpty()){ cout<<"There is nothing to show\n"; }
                else { myGames->show(); }
                cleanAndWait();
                break;
            }
            
            case 2:{
                Game* newGame = new Game();
                cin.ignore(1024, '\n'); 
                newGame->initFields();
                if (myGames->gameExists(*newGame)){
                    cout<<"Games with the same name are not allowed\n";
                    delete newGame;
                } else {
                    myGames->addGame(newGame);
                }
                cleanAndWait();
                break;
            }

            case 3:{
                char* title = new char[CHARSIZE];
                if (myGames->isEmpty()){ 
                    cout<<"This List doesnt have any elements\n"; 
                } else { 
                    cin.ignore(1024, '\n'); 
                    cout<<"Type the title's game to look for -> ";
                    cin.getline(title, CHARSIZE);
                    myGames->lookFor(title); 
                }
                delete[] title;
                cleanAndWait();
                break;
            }

            case 4:{
                char* title = new char[CHARSIZE];
                if (myGames->isEmpty()){ 
                    cout<<"This List doesnt have any elements\n"; 
                } else { 
                    myGames->show();
                    cin.ignore(1024, '\n'); 
                    cout<<"Type the title's game to delete -> ";
                    cin.getline(title, CHARSIZE);
                    myGames->deleteGame(title);
                }
                delete[] title;
                cleanAndWait();
                break;
            }

            case 5:{
                char* title = new char[CHARSIZE];
                if (myGames->isEmpty()){ 
                    cout<<"This List doesnt have any elements\n"; 
                } else { 
                    myGames->show();
                    cin.ignore(1024, '\n'); 
                    cout<<"Type the title's game to modify -> ";
                    cin.getline(title, CHARSIZE);
                    
                    try {
                        Game* game = myGames->getGame(title);
                        system("cls");
                        cout<<"Old fields:\n";
                        myGames->lookFor(title);
                        game->modifyFields();
                        cout<<game->title<<" has been modified succesfully\n";    
                    } catch(const runtime_error& e){
                        cerr<<e.what();
                    }
                    
                }
                delete[] title;
                cleanAndWait();
                break;
            }
            case 6:{
                if (myGames->isEmpty()){
                    cout<<"You cant export a LinkedList empty\n";
                } else {
                    int option;
                    do{
                        cout<<"1.Export to bin file\n2.Export to csv\n0.Back\n";
                        cin>>option; 
                        cin.clear();

                        if (option != 1 && option != 2 && option != 0){
                            cout<<"Invalid number, try again\n";
                        };
                    } while (option != 1 && option != 2 && option != 0);

                    if (option == 0){
                        cleanAndWait();
                        break;
                    }

                    int exported;
                    if (option == 1){
                        exported = myGames->exportToBin(DEFAULT_BIN_PATH);
                    } else {
                        exported = myGames->exportToCsv(DEFAULT_CSV_PATH);
                    }

                    if (exported == 0){
                        cout<<"List exported succefully with "<<myGames->getNumElements()<<" elements\n";
                    } else {
                        cout<<"List wasnt able to be exported\n";
                    }
                }
                cleanAndWait();
                break;
            }

            case 7:{
                if (!myGames->isEmpty()){
                    cout<<"Current list must be empty to load from external file\n";
                } else {
                    int option;
                    do{
                        cout<<"1.Import from csv\n0.Back\n";
                        cin>>option; 
                        cin.clear();

                        if (option != 1 && option != 0){
                            cout<<"Invalid number, try again\n";
                        };
                    } while (option != 1 && option != 0);
                    
                    if (option == 0){
                        cleanAndWait();
                        break;
                    }

                    int imported;
                    imported = myGames->importCsv(DEFAULT_CSV);

                    if (imported == 0){
                        cout<<"List imported succefully with "<<myGames->getNumElements()<<" elements\n";
                    } else {
                        cout<<"List wasnt able to be imported\n";
                    }
                }
                cleanAndWait();
                break;
            }
            
            default:
                cout<<"Invalid option, try again\n";
                cleanAndWait();
                break;
        }

    } while (option != 0);
    
    delete myGames;
    return 0;
}