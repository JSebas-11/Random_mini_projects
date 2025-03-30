//Pilas <- Basadas en fisolofia LIFO (Last In, First Out)

/*Ejercicio: Aplicación de Gestión de Historial de Navegación con Pilas
Desarrollar una aplicación en C++ que simule el historial de navegación de un navegador web. 
Debera ser usada una pila (stack) para almacenar las páginas visitadas y permitir
funcionalidades como:
    -Mostrar el historial: Muestra todas las páginas visitadas.
    -Visitar una nueva página: Se agrega a la pila.
    -Agregar un límite, eliminando la página más antigua si se supera este mismo. 
    -Cerrar pagina actual: Se elimina la página actual.
    -Cerrar pagina especifica: Se elimina la página en posicion x.
    -Limpiar el historial: Vacía la pila.
    -Guardar el historial en un archivo csv y poder cargarlo.*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const string STRAIGHT_LINES = "----------------------------------------------\n";
const string DEFAULT_CSV_PATH = "..\\Stack_csv\\stackData.csv";
const string PRELOADED_CSV_PATH = "..\\Stack_csv\\preloaded.csv";
int limit = 30;
char sep = ',';

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

vector<string> split(const string& line, char separator = sep){
    vector<string> lineSep = {};
    string word = "";

    for (char letter : line){
        if (letter == separator){
            lineSep.push_back(word);
            word.clear();
            continue;
        }
        word += letter;
    }
    if (!word.empty()){
        lineSep.push_back(word);
    }

    return lineSep;
}

struct WebPage{ //Struct que actuara como nodo de la pila
    string scheme;
    string subDomain;
    string tld;
    string domain;
    string path;
    WebPage* higher;
    WebPage* bottom;

    WebPage(const string& _domain, const string& _scheme = "https://", 
            const string& _subDomain = "www.", const string& _tld = ".com")
             : scheme(_scheme), subDomain(_subDomain), tld(_tld), domain(_domain) {
        this->path = this->scheme + this->subDomain + this->domain + this->tld;
        this->higher = nullptr;
        this->bottom = nullptr;
    };

    WebPage(const vector<string>& data)
         : scheme(data.at(1)), subDomain(data.at(2)), tld(data.at(3)), domain(data.at(0)) {
        this->path = this->scheme + this->subDomain + this->domain + this->tld;
        this->higher = nullptr;
        this->bottom = nullptr;
    };
    
    const string& getPath() const { return this->path; }
};

class Browser{ //Pila con los nodos WebPage
private:
    WebPage* top;
    int numPages;

    void clean(){
        while (top){
            WebPage* newTop = top->bottom;
            delete top;
            top = newTop;
            if (top){ top->higher = nullptr; }
        }
    }
public:
    Browser(){
        this->top = nullptr;        
        this->numPages = 0;
    };
    ~Browser(){ this->clean(); };

    int getNumPages() const { return this->numPages; } 

    void showHistory() const {
        if (!top){
            cout<<"There's nothing to show\n";
            return;
        }
        
        cout<<this->numPages<<" pages\n"<<STRAIGHT_LINES;
        WebPage* temp = top;
        
        //Bucle que se ejecutara hasta que temp sea null (final)
        for (int i = 0; temp; i++){
            cout<<i<<" - "<<temp->getPath()<<"\n";
            temp = temp->bottom;
        }

        cout<<STRAIGHT_LINES;
    }

    void surf() const {
        cout<<STRAIGHT_LINES;
        if (!top){ cout<<"You dont have pages opened\n"; } 
        else { cout<<"You are currently ("<<top->getPath()<<")\n"; }
        cout<<STRAIGHT_LINES;
    }

    void newPage(WebPage* newPage) {
        //Cancelamos operacion en caso de superar el limite definido 
        if (this->numPages >= limit){
            cout<<"You has reached the limit ("<<limit<<") last page will be deleted... ";
            this->closePage(this->numPages-1);
        }
        
        //Asignamos la nueva pagina al top en caso de estar vacio 
        if (!top){ top = newPage; }
        else{
            //Almacenamos top en variable auxiliar para redireccionar los punteros
            WebPage* topTemp = top;
            top = newPage;
            top->bottom = topTemp;
            topTemp->higher = newPage;
        }
        this->numPages++;
        cout<<"Page added succesfully\n";
    }

    void closePage(int index = 0){
        if (!top){
            cout<<"There's nothing to close\n";
            return;
        }

        if (index == 0){
            WebPage* newTop = top->bottom;
            delete top;
            top = newTop;
            if (top){ top->higher = nullptr; }

        } else {
            WebPage* temp = top->bottom;
            for (int i = 1; temp; i++){
                if (i == index){
                    WebPage* toDel = temp;
                    temp = temp->bottom;
                    toDel->higher->bottom = temp;
                    
                    if (temp){ temp->higher = toDel->higher; }
                    
                    delete toDel;
                    break;
                }
                temp = temp->bottom;
            }
        }
        this->numPages--;
        cout<<"Page deleted succesfully\n";
    }

    void clear(){
        this->clean();
        this->top = nullptr;
        this->numPages = 0;
        cout<<"Stack cleaned succesfully\n";
    }

    void exportCsv(const string& path = DEFAULT_CSV_PATH) const {
        if (!top){
            cout<<"Stack empty, there's nothing to export\n";
            return;
        }
        
        ofstream exportedStack;
        exportedStack.open(path, ios::out | ios::trunc);

        if (!exportedStack.good()){
            exportedStack.close();
            cout<<"There has been an error with the file\n";
            return;
        }

        exportedStack<<"domain"<<sep<<"scheme"<<sep<<"subDomain"<<sep<<"tld"<<"\n";
        WebPage* temp = top;
        while (temp){
            exportedStack<<temp->domain<<sep<<temp->scheme<<sep<<temp->subDomain<<sep<<temp->tld<<"\n";
            temp = temp->bottom;
        }
        exportedStack.close();
        cout<<"Stack exported "<<this->numPages<<" web pages\n";
    }

    void importCsv(const string& path = PRELOADED_CSV_PATH){
        ifstream importedStack;
        importedStack.open(path);

        if (!importedStack.good()){
            importedStack.close();
            cout<<"There has been an error with the file\n";
            return;
        }

        string line;
        int i;
        for (i = 0; getline(importedStack, line); i++){
            if (i == 0) { continue; }
            WebPage* newPage = new WebPage(split(line));
            this->newPage(newPage);
        }
        importedStack.close();
        cout<<"Stack imported with "<<i-1<<" new web pages\n";
    }
};

int main(){
    bool exit = false;
    string option;
    Browser* browser = new Browser();

    while (!exit){
        browser->surf();
        cout<<"1. Show Browsing History\n2. Surf New Page\n3. Delete Actual page\n4. Delete From Page"
        <<"\n5. Clean History Up\n6. Import (csv) Stack\n7. Export (csv) Stack\n0. Exit\n-> ";
        getline(cin, option);

        if (option == "0"){
            cout<<"Closing program...\n";
            exit = true;

        } else if (option == "1"){
            browser->showHistory();
            cleanWait();

        } else if (option == "2"){
            string domain;
            cout<<"Type domain's page -> ";
            getline(cin, domain);
            browser->newPage(new WebPage(domain));
            cleanWait();

        } else if (option == "3"){
            if (browser->getNumPages() == 0){
                cout<<"There's nothing to close\n";
            } else {    
                string del;
                cout<<"Are you sure you want to close the current page? (y/any) -> ";
                getline(cin, del);
                if (del == "y" || del == "Y"){ browser->closePage(); } 
                else { cout<<"Operation canceled\n"; }
            }

            cleanWait();

        } else if (option == "4"){
            //El 1 es para evitar que borren la pagina actual desde este menu
            if (browser->getNumPages() == 0 || browser->getNumPages() == 1){
                cout<<"There's nothing to close\n";
            } else {    
                int ind;
                browser->showHistory();
                while (true){
                    cout<<"Type index that you want to delete (-1 Back to menu) -> ";
                    cin>>ind; cin.ignore();

                    if (ind == 0){
                        cout<<"Current page only can be deleted from the main menu\n";
                        continue;
                    } else if (ind == -1){
                        break;
                    } else if (ind < 1 || ind > browser->getNumPages()-1){
                        cout<<"Index out of range\n";
                        continue;
                    } else {
                        browser->closePage(ind);
                        break;
                    }
                }
            }
            cleanWait();

        } else if (option == "5"){
            if (browser->getNumPages() == 0){
                cout<<"There's nothing to clean\n";
            } else {    
                string del;
                cout<<"Are you sure you want to clean the stack up? (y/any) -> ";
                getline(cin, del);
                if (del == "y" || del == "Y"){ browser->clear(); } 
                else { cout<<"Operation canceled\n"; }
            }
            cleanWait();

        } else if (option == "6"){
            browser->importCsv();
            cleanWait();
            
        } else if (option == "7"){
            browser->exportCsv();
            cleanWait();

        } else {
            cout<<"Invalid option, try again\n";
        }
    }

    delete browser;
    return 0;
}