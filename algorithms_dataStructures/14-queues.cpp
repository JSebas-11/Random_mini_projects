//Colas <- Basadas en fisolofia FIFO (First In, First Out)

/*Ejercicio para practica uso de queues con doble enlace:
Desarrollar aplicación que administre solicitudes en queue en 3 diferentes estaciones.
Solicitud debe tener:
    Nombre del solicitante.
    Tipo de solicitud.
    Descricion breve.
    Estado.

Funcionalidades requeridas:
    Mostrar todas las solicitudes pendientes en orden de llegada de acuerdo a la estacion.
    Contar la cantidad de solicitudes en la cola.
    Cancelar solicitudes, sacandolas de la cola.
    Vaciar la cola completamente en caso de mantenimiento del sistema.
    Permitir que las solicitudes no procesadas se guarden en un archivo CSV para persistencia de datos.*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const string STRAIGHT_LINES = "----------------------------------------------\n";
const string DEFAULT_CSV_PATH = "..\\Queue_csv\\queueStation"; //Ext y numStat seran definidos mas adelante 
const string PRELOADED_CSV_PATH = "..\\Queue_csv\\preloaded.csv";
char sep = ',';

enum Status { APPROVED, DISAPPROVED, TOREVIEW, CANCELED };
Status strToStatus(const string& statusStr) {
    if (statusStr == "APPROVED") return APPROVED;
    if (statusStr == "DISAPPROVED") return DISAPPROVED;
    if (statusStr == "TOREVIEW") return TOREVIEW;
    if (statusStr == "CANCELED") return CANCELED;
    throw invalid_argument("Invalid status string");
}

string statusTostr(const Status& stat) {
    switch (stat) {
        case APPROVED: return "Approved";
        case DISAPPROVED: return "Disapproved";
        case TOREVIEW: return "ToReview";
        case CANCELED: return "Canceled";
        default: throw invalid_argument("Invalid status parameter");
    }
}

void upperCase(string& text){
    for (size_t i = 0; i < text.size(); i++){
        text[i] = toupper(text[i]); 
    }
}

vector<string> split(const string& text, char separator = sep){
    //Metodo para separar palabras en un texto
    vector<string> data = {};
    string newWord = "";

    //Concatenamos cada palabra y al llegar a un sep, agregamos la palabra al vector y la reiniciamos
    for (char ch : text){
        if (ch == separator){
            data.push_back(newWord);
            newWord.clear();
            continue;
        }
        newWord += ch;
    }
    if (!newWord.empty()){
        //Agregamos ultimo elemento, ya que este no alcanza a llegar al sep
        data.push_back(newWord);
    }
    
    return data;
}

int cleanWait(){
    cout<<"Press any key to continue...\n";
    cin.get();
    #ifdef _WIN32
        system("cls");
    #else
        cout<<"\033[2J\033[1;1H";
    #endif
        return 0;
}

struct Request{ //Struct que actuara como nodo para la cola
    string by;
    string type;
    string desciption;
    Status stat;
    Request* next; //Hara referencia al que sigue en la cola (elemento que entro despues)
    Request* previuos; //Hara referencia al anterior de la cola (elemento que entro antes)

    Request(){ //Constructor a partir de entradas de usuario
        cout<<"Type name of the requester -> ";
        getline(cin, this->by);
        cout<<"Type request' type -> ";
        getline(cin, this->type);
        cout<<"Type request' description -> ";
        getline(cin, this->desciption);
        this->stat = TOREVIEW;
        this->next = nullptr;
        this->previuos = nullptr;
    }

    Request(const vector<string>& data){ //Constructor a partir de vector (para importar csv)
        this->by = data.at(0);
        this->type = data.at(1);
        this->desciption = data.at(2);
        this->stat = strToStatus(data.at(3));
        this->next = nullptr;
        this->previuos = nullptr;
    }

    void showInfo() const {
        cout<<this->by<<sep<<" "<<this->type<<sep<<" "<<this->desciption<<sep<<" "<<statusTostr(this->stat)<<"\n";
    }

    void manageRequest(const Status& newStatus){
        //Actualizaremos el estado de la solicitud
        this->stat = newStatus;
    }
};

class Queue{ //Cola que contendra los Request Objects
private:
    Request* head;
    int numRequests;

    void clean(){
        Request* current = head;
        while (current){ //Recorremos cada elemento para ser borrado
            Request* aux = current;
            current = current->next;
            aux->next = nullptr;
            aux->previuos = nullptr;
            aux = nullptr;
            delete aux;
        }
    }

public:
    Queue(){
        this->head = nullptr;
        this->numRequests = 0;
    };
    ~Queue(){
        this->clean();
    };

    int getElementsNum(){ return this->numRequests; }

    void addRequest(Request* toAdd){
        if (!head) head = toAdd; //Si no hay elementos lo asignamos en la cabecera
        else {
            Request* aux = head;
            while (aux){ 
                if (!aux->next){ //Verificar si estamos en el ultimo elemento
                    aux->next = toAdd; //Asignamos los punteros para ubicar elemento al final
                    toAdd->previuos = aux;
                    break;
                }   
                aux = aux->next;
            }
        }
        this->numRequests++;
        cout<<"Request added succesfully\n";
    }

    void showRequest(int limit) const {
        if (!head){
            cout<<"There's nothing to show\n";
            return;
        }
        
        cout<<this->numRequests<<" requests\n";
        cout<<STRAIGHT_LINES<<"Pos"<<sep<<" by"<<sep<<" type"<<sep<<" description"<<sep<<" status\n"<<STRAIGHT_LINES;
        Request* aux = head;
        for (int i = 0; aux && i < limit; i++){ //Recorremos elemento desde el head y mostaramos su info
            cout<<i<<sep<<" ";
            aux->showInfo();
            aux = aux->next;
        }
        cout<<STRAIGHT_LINES;
    }

    void cleanQueue(){ //Metodo para reinciar la cola
        if (!head){
            cout<<"This queue is empty\n";
            return;
        }
        this->clean();
        cout<<"Queue has been cleaned successfully\n";
        this->head = nullptr;
        this->numRequests = 0;
    }

    void handleRequest(const Status& newStatus){
        if (!head){ //Si el header es null quiere decir que no hay elementos
            cout<<"There's nothing to manage\n";
            return;
        } else {
            head->manageRequest(newStatus); //Actualizamos el estado de la Request en cuestion
            cout<<"Request processed: ";
            head->showInfo();
            //Borramos elemento en head para posteriormente reemplazarlo por el sgte de la cola
            Request* newHead = head->next;
            delete head;
            head = newHead;
            //Si si hay un elemento en head apuntamos su prev a null
            if (head) { head->previuos = nullptr; }
            this->numRequests--;
        }
    }

    void cancelRequest(int position){
        if (position < 0 && position >= this->numRequests){
            throw out_of_range("Position out of range");
        }

        if (position == 0){
            head->manageRequest(CANCELED);
            cout<<"Request canceled: ";
            head->showInfo();
            Request* newHead = head->next;
            delete head;
            head = newHead;
            if (head) { head->previuos = nullptr; }
            this->numRequests--;
        } else {
            Request* temp = head->next;
            for (int pos = 1; temp; pos++){
                if (pos == position){
                    Request* toCancel = temp;
                    if (!temp->next){
                        //Si el elementos es el ultimo quitamos su referencia del anterior y la tiramos a null
                        temp->previuos->next = nullptr;
                    } else {
                        //Redirreccionamos punteros del request anterior y posterior
                        temp->next->previuos = temp->previuos;
                        temp->previuos->next = temp->next;
                    }
                    toCancel->manageRequest(CANCELED);
                    cout<<"Request canceled: ";
                    toCancel->showInfo();
                    delete toCancel;
                    this->numRequests--;
                    break;
                }
                temp = temp->next;
            }
        }
    }

    void importCsv(const string& path){
        ifstream importedQueue;
        importedQueue.open(path);

        if (!importedQueue.good()){
            importedQueue.close();
            cout<<"There has been an error with the file\n";
            return;
        }

        string line;
        int i = 0;
        for (i = 0; getline(importedQueue, line); i++){
            if (i == 0) { continue; }
            //Creamos objeto request a partir de split que retornara los atributos en un vector
            Request* newRequest = new Request(split(line));
            this->addRequest(newRequest);
        }
        importedQueue.close();
        cout<<"Queue imported with "<<i-1<<" new requests\n";
    }

    void toCsv(const string& path) const {
        if (!head){
            cout<<"There's nothing to export\n";
            return;
        }
        
        ofstream exportedQueue;
        exportedQueue.open(path, ios::out | ios::trunc);

        if (!exportedQueue.good()){
            exportedQueue.close();
            cout<<"There has been an error with the file\n";
            return;
        }

        Request* temp = head;
        string statusStr;
        exportedQueue<<"by"<<sep<<"type"<<sep<<"description"<<sep<<"status\n";

        while (temp){
            statusStr = statusTostr(temp->stat);
            upperCase(statusStr);
            exportedQueue<<temp->by<<sep<<temp->type<<sep<<temp->desciption<<sep<<statusStr<<"\n";
            temp = temp->next;
        }
        exportedQueue.close();
        cout<<"Queue exported "<<this->numRequests<<" requests\n";
    }
};

class Station{ //Clase que actuara como gestor de queue
private:
    Queue* stationQueue;
    string path;
    int stationId;
public:
    Station(int _id){
        this->stationId = _id;
        this->path = DEFAULT_CSV_PATH + to_string(this->stationId) + ".csv";
        this->stationQueue = new Queue();
    };

    int getId() const { return this->stationId; }
    string getPath() const { return this->path; }
    Queue* queue(){ return this->stationQueue; } 
};

void mainMenu(Station* station){
    bool exit = false;
    string option;

    Queue* queue = station->queue();
    while (!exit){
        cout<<"Main menu: (Station "<<station->getId()<<")\n\t1.Show Requests\n\t2.Add Request\n\t3.Handle request\n\t4.Cancel Request"
        <<"\n\t5.Clean queue up\n\t6.Import (csv) queue\n\t7.Export (csv) queue\n\t0. Close Station\n-> ";
        getline(cin, option);

        if (option == "0"){
            cout<<"Closing station...\n";
            cleanWait();
            exit = true;

        } else if (option == "1"){ 
            queue->showRequest(queue->getElementsNum());
            cleanWait();

        } else if (option == "2"){
            queue->addRequest(new Request());
            cleanWait();

        } else if (option == "3"){
            if (queue->getElementsNum() == 0){
                cout<<"There's nothing to manage\n";
            } else {
                string stat = "0";
                Status finalStat;
                queue->showRequest(1);
                while (stat != "1" && stat != "2"){
                    cout<<"What do you want to do with this request?\n\t1.Approved\n\t2.Disapproved\n-> ";
                    getline(cin, stat);

                    if (stat != "1" && stat != "2"){ cout<<"Type a valid option\n"; }
                    else if (stat == "1"){ finalStat = APPROVED; } 
                    else { finalStat = DISAPPROVED; }
                }
                queue->handleRequest(finalStat);
            }
            cleanWait();

        } else if (option == "4"){
            if (queue->getElementsNum() == 0){
                cout<<"There's nothing to cancel\n";
            } else {
                int position = -1;
                queue->showRequest(queue->getElementsNum());
                while (position < 0 || position >= queue->getElementsNum()){
                    cout<<"Type the position of the element to delete -> ";
                    cin>>position;
                    cin.ignore();

                    if (position < 0 || position >= queue->getElementsNum()){
                        cout<<"Position out of range\n";
                    }
                }
                queue->cancelRequest(position);
            }
            cleanWait();

        } else if (option == "5"){
            string act;
            cout<<"Are you sure? (y/any) -> ";
            getline(cin, act);
            if (act == "y"){ queue->cleanQueue(); } 
            else { cout<<"Operation canceled\n"; }
            cleanWait();

        } else if (option == "6"){
            string act;
            cout<<"Are you sure? (y/any) -> ";
            getline(cin, act);
            if (act == "y"){ queue->importCsv(PRELOADED_CSV_PATH); } 
            else { cout<<"Operation canceled\n"; }
            cleanWait();

        } else if (option == "7"){
            queue->toCsv(station->getPath());
            cleanWait();

        } else {
            cout<<"Invalid option, try again\n";
            continue;
        }
    }
};

int main(){

    Station* station1 = new Station(1);
    Station* station2 = new Station(2);
    Station* station3 = new Station(3);
    
    bool close = false;
    string stationNum = "";
    while (!close){
        cout<<"Station Menu\nGo to:\n\t1.Station 1\n\t2.Station 2\n\t3.Station 3\n\t0.Exit\n-> ";
        getline(cin, stationNum);

        if (stationNum == "0"){
            cout<<"Closing program...\n";
            close = true;

        } else if (stationNum == "1" || stationNum == "2" || stationNum == "3"){
            cout<<"You will be gotten to station "<<stationNum<<"\n";
            cleanWait();
            if (stationNum == "1"){ mainMenu(station1); } 
            else if (stationNum == "2"){ mainMenu(station2); } 
            else if (stationNum == "3"){ mainMenu(station3); }
            
        } else {
            cout<<"Invalid option, try again\n";
            close = false;
        }
    }
    
    delete station1;
    delete station2;
    delete station3;
    return 0;
}