#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

//Plantilla para adaptar las distintas struct utilizadas en el script dentro de la funcion liberateMemory
template <typename Structure>
void liberateMemory (vector<Structure*> vector){
    for (Structure* element : vector){
        delete element;
    }
    vector.clear();
}

//Struct: Coleccion de elementos de diferentes tipos de datos
struct Album{
    string title; 
    string artist; 
    int songsNumber; 
    float price; 
    string date; 
}; // <-Variables tambien pueden ser declaradas aca 

/*Union: Funciona igual que struct, pero almacena los diferentes tipos de datos en el mismo espacio 
de memoria, asi que todos los miembros comparten la misma dirección, lo que lo hace eficiente en 
uso de memoria. Debe ser bien administrado para no generar conflictos entre los campos*/
union AlbumUnion {
    char title[50]; 
    char artist[50]; 
    int songsNumber; 
    float price;
};

/*Enum: Genera secuencia de valores constantes enumerados (Por defecto empieza en 0, 
Podemos definir el primer elemento con otro numero y seguira la secuencia)*/
enum calification {awful=1, bad, regular, good, brilliant};

void firstLook(){
    Album myAlbum = {"Hello World", "X Programmer", 3, 29.99, "09/09/2024"}; //Instanciar y definir sus campos 
    cout<<myAlbum.artist<<endl; //Acceder a sus campos para mostrar, modificar, etc

    calification yourNote = awful;
    calification myNote = brilliant;
    cout<<yourNote<<endl<<myNote<<endl;
}

/*Crear struct llamada corredor, con campos: nombre, edad y sexo. Crear un corredor y asignarle 
    una categoria (Juvenil <= 18, Señor <= 40, Veterano > 40). Imprimir datos y categoria*/
struct Runner{
private:
    string category;
public:
    string name;
    int age;
    string genre; 
    
    void defineCategory(){
        int age = this->age;
        if (age <= 18){
            this->category = "Junior";
        }
        else if (age > 18 && age <= 40){
            this->category = "Senior";
        }
        else if (age > 40){
            this->category = "Veteran";
        }        
    }
    void printData(){
        cout<<"Name: "<<this->name<<endl<<"Age: "<<this->age<<endl;
        cout<<"Genre: "<<this->genre<<endl<<"Category: "<<this->category<<endl;
    }
}runner1;

void exercise1(){
    int genreNum;
    cout<<"Type the runner's name => "; getline(cin, runner1.name);
    cout<<"Type the runner's age => "; cin>>runner1.age;
    cout<<"Type the runner's genre (0.Female/ 1.Male) => "; cin>>genreNum;

    if (genreNum == 0){
        runner1.genre = "Female";
    }
    else if (genreNum == 1){
        runner1.genre = "Male";
    }
    else {
        runner1.genre = "Unknown";
    }

    runner1.defineCategory();
    runner1.printData();
}

/*Crear struct Alumno con campos: Nombre, edad, promedio. Pedir datos por consola e imprimir el mejor 
y peor promedio con los datos del estudiante*/
struct Student{
    string name;
    int age;
    float average;

    static void bestAvg(Student st1, Student st2, Student st3){
        Student students[3] = {st1, st2, st3}; //Creamos array con los objetos estudiantes para despues recorrerlos
        Student best = st1; //Asignamos como el mayor al primer objeto para empezar las comparaciones
        for (const Student& e : students){ 
            if (e.average > best.average){
            //Si el atributo promedio del objeto de la iteracion es mayor al almacenado en best, actualizamos el objeto de la variable
                best = e; 
            }
        }
        //En la variable best se guarda el objeto con mayor salario asi que imprimimos sus datos
        cout<<"The best student's average is: "<<best.name<<" ("<<best.age<<" years old)\n";
        cout<<"Average: "<<best.average<<"\n";
    }

    static void worstAvg(Student st1, Student st2, Student st3){
        Student students[3] = {st1, st2, st3};
        Student worst = st1;
        for (const Student& e : students){
            if (e.average < worst.average){
                worst = e;
            }
        }
        cout<<"The worst student's average is: "<<worst.name<<" ("<<worst.age<<" years old)\n";
        cout<<"Average: "<<worst.average<<"\n";
    }

}student1, student2, student3;

void exercise2(){
    Student* students[] = {&student1, &student2, &student3};
    int i = 1;
    for (Student* e : students){
        fflush(stdin);
        
        cout<<"Info Student "<<i<<":\n";
        cout<<"Type the name => "; getline(cin, e->name);
        cout<<"Type the age => "; cin>>e->age;
        cout<<"Type the average => "; cin>>e->average;
        
        i++;
    }   

    Student::bestAvg(student1, student2, student3);
    Student::worstAvg(student1, student2, student3);
}

/*Leer un array de struct Empleados, que imprima los datos de n empleados y mostrar el
de mayor y menor salario*/
struct Employee{
    int id;
    string name;
    float salary;

    static void greatestSalary(const vector<Employee*> employees){ //Pasamos como parametro un vector con direcciones de objeto
        //Funcionamiento similar al del anterior ejercicio pero con sintaxis de punteros
        Employee greatest = *employees[0]; 
        for (Employee* employee : employees){
            if (employee->salary > greatest.salary){
                greatest = *employee;
            }
        }
        cout<<"The greatest salary is: "<<greatest.name<<" ("<<greatest.id<<" id)\n";
        cout<<"Salary: "<<greatest.salary<<"\n";
    }

    static void leastSalary(const vector<Employee*> employees){
        Employee least = *employees[0];
        for (const Employee* employee : employees){
            if (employee->salary < least.salary){
                least = *employee;
            }
        }
        cout<<"The least salary is: "<<least.name<<" ("<<least.id<<" id)\n";
        cout<<"Salary: "<<least.salary<<"\n";
    }
};

void exercise3(){
    int employeeNum;
    cout<<"How many employees do you want to evaluate? => ";
    cin>>employeeNum;

    vector<Employee*> employees = {};
    
    for (int i = 1; i <= employeeNum; i++){
        Employee* emplo = new Employee();
        cout<<"Info employee "<<i<<":\n";
        cout<<"Type the id => "; cin>>emplo->id;
        fflush(stdin);
        cout<<"Type the name => "; getline(cin, emplo->name);
        cout<<"Type the salary => "; cin>>emplo->salary;

        employees.push_back(emplo);
    }

    Employee::greatestSalary(employees);
    Employee::leastSalary(employees);
    liberateMemory(employees);
}

/*Definir struct Persona con campos: Nombre y discapacidad. Hacer que dado un vector de personas
rellenar dos nuevos vectores con las personas que tengan y no tengan discapacidades*/
struct Person{
    string name;
    bool disability;
    
    static vector<Person*> getDisability(const vector<Person*> people, bool disability = true){
        vector<Person*> newVector = {};
        if (disability){
            for (Person* person : people){
                if (person->disability){
                    newVector.push_back(person);
                }
            }
        }
        else{
            for (Person* person : people){
                if (!person->disability){
                    newVector.push_back(person);
                }
            }
        }
        return newVector;
    }

    static void showVector(const vector<Person*> people){
        int i = 1;
        for (Person* person : people){
            cout<<"Name: "<<person->name<<", Disabiltiy: "<<boolalpha<<person->disability<<"\n";
            i++;
        }
    }           
};

void exercise4(){
    int personNum, disab;
    cout<<"How many persons do you want to evaluate => "; cin>>personNum;
    vector<Person*> people = {};

    for (int i = 1; i <= personNum; i++){
        Person* person = new Person();
        fflush(stdin);
        cout<<"Info person "<<i<<":\n";
        cout<<"Type the name => "; getline(cin, person->name);
        cout<<"Has person disabilties? (0. No/1. Yes) => "; cin>>disab; 
        
        if (disab == 0){
            person->disability = false;
        }
        else if (disab == 1){
            person->disability = true;
        }
        else{
            cout<<"You must type 0 or 1, try again\n";
            i--;
            delete person;
            continue;
        }
        people.push_back(person);    
    }
    vector<Person*> disabilities = Person::getDisability(people);
    vector<Person*> notDisabilities = Person::getDisability(people, false);

    cout<<"--------------------------\nDisabilities:\n";
    Person::showVector(disabilities);
    cout<<"--------------------------\nNot disabilities:\n";
    Person::showVector(notDisabilities);

    liberateMemory(people);
};

/*Crear struct con datos de n personas e imprimir filtrando por sexos o por nacidos en 
cierto rango de fechas. Ademas la edad se debe calcular automaticamente*/
enum genre {female, male, unknown};

string genreToStr(genre genre){
    switch (genre) {
        case female: return "Female";
        case male: return "Male";
        case unknown: return "Unknown";
        default: return "Unknown";
    }
}

struct Date {
    int day;
    int month;
    int year;    

    int yearsToToday(){
        //Obtenemos fecha actual y convertimos a estructura tm la cual desglosara dias, meses etc
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);
        vector<int> currentDate = {localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday};
        
        int years = currentDate[0] - this->year; 
        if (this->month > currentDate[1] || (this->month == currentDate[1] && this->day > currentDate[2])){
            years --;
        }
        return years;
    }

    string dateAsStr(char sep = '/'){
        return to_string(this->day) + sep + to_string(this->month) + sep + to_string(this->year);
    } 
};

struct Person2 {
    string name;
    enum genre genre;
    Date birthDate;
    int age;

    void setAge(){
        this->age = this->birthDate.yearsToToday();
    }

    void showData(){
        cout<<"Name: "<<this->name<<"\nAge: "<<this->age<<"\nBirthDate: ";
        cout<<this->birthDate.dateAsStr()<<"\nGenre: "<<genreToStr(this->genre)<<"\n";
    }

    static vector<Person2*> registerPeople(int personNum){
        vector<Person2*> people = {};

        for (int i = 1; i <= personNum; i++){
            int genre;
            Person2* person = new Person2();

            cout<<"Person "<<i<<" name => ";
            getline(cin, person->name);

            cout<<"Person "<<i<<" genre (0.Female / 1.Male) => "; cin>>genre;
            if (genre == 0){ person->genre = female; }
            else if (genre == 1){ person->genre = male; }
            else { person->genre = unknown; }
            fflush(stdin);

            cout<<"Birth's day => "; cin>>person->birthDate.day;
            cout<<"Birth's month => "; cin>>person->birthDate.month;
            cout<<"Birth's year => "; cin>>person->birthDate.year;
            fflush(stdin);
            person->setAge();

            people.push_back(person);
        }
        return people;
    }
};

void mainSectionExercise5(const vector<Person2*> peoplee);

void exercise5(){
    int personNum;
    cout<<"How many people do you want to include => ";
    cin>>personNum;
    fflush(stdin);

    vector<Person2*> peoplee = Person2::registerPeople(personNum);
    system("cls");

    mainSectionExercise5(peoplee);
    
    liberateMemory(peoplee);
}

//-------------------------------Main function--------------------------------
int main (){
    firstLook();
    system("pause");
    system("cls");

    int action = 1;
    do{
        cout<<"What exercise do you want to do?\n1.Runners\n2.Students\n3.Employees\n4.People 1\n5.People 2\n0.Exit\n";
        cin>>action;
        if (action == 0){
            cout<<"Closing program...";
        }
        
        else if (action == 1){
            exercise1();
            system("pause");
            system("cls");
        }
        else if (action == 2){
            exercise2();
            system("pause");
            system("cls");
        }
        else if (action == 3){
            exercise3();
            system("pause");
            system("cls");
        }
        else if (action == 4){
            exercise4();
            system("pause");
            system("cls");
        }
        else if (action == 5){
            exercise5();
            system("pause");
            system("cls");
        }
        else{
            cout<<"Invalid option\n";
        }
    } while (action != 0);

    return 0;
}
//----------------------------------------------------------------------------


void mainSectionExercise5(const vector<Person2*> peoplee){
    while (true){
        int action;
        cout<<"How do you want to show the information: \n\t1.All\t2.Filter by genre\t3.Filter by dates\t0.Exit\n";
        cin>>action;
        if (action == 0){
            cout<<"Closing exercise...\n";
            break;
        }
        else if (action == 1){
            for (Person2* person : peoplee){
                person->showData();
                cout<<"----------------\n";
            }
            system("pause");
            system("cls");
        }
        else if (action == 2){
            int filter;
            cout<<"Filter by genre: \n\t1.Female\t2.Male\t3.Unkonwn\n";
            cin>>filter;
            if (!(filter >= 1 && filter <= 3)){
                cout<<"Incorrect filter\n";
            }
            for (Person2* person : peoplee){
                if (filter == 1){
                    if (person->genre == female){
                        person->showData();
                        cout<<"----------------\n";
                    }
                }
                else if (filter == 2){
                    if (person->genre == male){
                        person->showData();
                        cout<<"----------------\n";
                    }
                }
                else if (filter == 3){
                    if (person->genre == unknown){
                        person->showData();
                        cout<<"----------------\n";
                    }
                }
            }
            system("pause");
            system("cls");
        }
        else if (action == 3){
            int initial, final;
            cout<<"Initial year => "; cin>>initial;
            cout<<"Final year => "; cin>>final;
            if (initial > final){
                int aux = initial;
                initial =  final;
                final = aux;
                cout<<"Initial year can't be greater than final, we have done the change\n";
            }
            for (Person2* person : peoplee){
                if (person->birthDate.year >= initial && person->birthDate.year <= final){
                    person->showData();
                    cout<<"----------------\n";
                }
            }
            system("pause");
            system("cls");
        }
        else{
            cout<<"Invalid option, try again\n";
        }
    }
}