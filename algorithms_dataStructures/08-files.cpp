#include <iostream>
#include <fstream> //Libreria para manejar flujos de entrada y salida en archivos

using namespace std;

/*
(Pueden ser abiertos en distintos modos, ejemplo: ios::app | ios::binary)
ifstream -> InputFile Stream (entrada)
    Modos apertura:
        ios::out: Abre en modo escritura (predeterminado). Si el archivo ya existe, se sobrescribe.
        ios::app: Abre en modo de adición (append). Los nuevos datos se añaden al final del archivo.
        ios::trunc: Borra el contenido del archivo si este ya existe (predeterminado para ios::out).
        ios::ate: Posicion incial sera al final (At The End)
        ios::binary: Abre el archivo en modo binario.

ofstream -> OutputFile Stream (salida)
    Modos apertura:
        ios::in: Abre en modo lectura (predeterminado).
        ios::binary: Abre en modo binario.

Principales pasos sobre archivos:
    Open -> Operate -> close 

Estados:
    .bad() -> Errores: no hay permiso, no hay espacio o no existe
    .fail() -> Errores: errores formato o tipos
    .eof() -> End Of File
    .good() -> No errores
*/

void firstLook(){
    //----------Archivos texto----------
    ofstream outfile;
    outfile.open("..\\files-Files\\files-Txt.txt", ios::app);
    outfile<<"Hello word from ofstream\n"; //Redireccionar flujo hacia el archivo
    outfile<<"Line 2 with append mode\n";
    outfile.close();

    ifstream infile;
    char line[128];
    infile.open("..\\files-Files\\files-Txt.txt");

    while (!infile.bad() && !infile.eof()){
        infile.getline(line, 128);
        cout<<line<<"\n";
    }

    infile.close();

    //----------Archivos Binarios----------
    /*Procesos escritura en archivos binarios son: Memoria (RAM) -> Archivo
    Internamente byte por byte, debemos conocer:
        1. Punto memoria a empezar      2. Cantidad de bytes

        archivo.write(Puntero tipo char con direccion de inicio, cantidad de bytes)*/
    struct Person{
        string name;
        int age;
        int id;
    }personToExport, personToImport;
    personToExport = {"David", 21, 12337};
    
    ofstream binFile;
    binFile.open("..\\files-Files\\files-binary.bin", ios::binary);
    //Casteamos a tipo puntero char la direccion de memoria del struct y el peso en bytes 
    binFile.write((char*)&personToExport, sizeof(personToExport));
    binFile.close();

    /*Procesos lectura en archivos binarios son: Archivo -> Memoria (RAM)
    Internamente byte por byte, debemos conocer:
        1. Punto memoria a pasar      2. Cantidad de bytes

        archivo.read(Puntero tipo char con direccion destino, cantidad de bytes)*/
    ifstream readBin;
    readBin.open("..\\files-Files\\files-binary.bin", ios::binary);
    readBin.read((char*)&personToImport, sizeof(personToImport));
    cout<<"Imported info: "<<personToImport.name<<"-"<<personToImport.id<<"-"<<personToImport.age;
    readBin.close();

    /*Otras funciones archivos:
        rename("oldName.ext", "newName.ext") -> Renombrar archivos Retorna 0 si salio correcto
        remove("file.ext") -> Borrar archivos Retorna 0 si salio correcto*/
}

/*Leer el archivo txt y pasar el contenido a mayusculas y agregar al final un texto*/
void lineToUpper(char* line){
    for (int i = 0; *(line+i) != '\0'; i++){
        *(line+i) = toupper(*(line+i));
    }
}

void exercise(){
    ifstream fileRead;
    ofstream newFile;
    char line[256] = {0};

    fileRead.open("..\\files-Files\\files-lowerTxt.txt");
    
    if (fileRead.good()){
        
        newFile.open("..\\files-Files\\files-upperTxt.txt");
        while (fileRead.getline(line, 256)) {
            lineToUpper(line);
            newFile<<line<<endl;
        }
        newFile.close();
    }

    else{
        cout<<"It has happened an error with the input file";
        return;
    }

    fileRead.close();
}

int main(){

    /*firstLook();
    system("pause");
    system("cls");*/

    exercise();

    return 0;
}