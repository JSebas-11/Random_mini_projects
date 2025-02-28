#include <iostream>
#include <string>
#include <exception>
#include <vector>

using namespace std;

/*Implementar la clase MyString y:
    √ -Internamente almacene un array de caracteres y tenga un tamaño máximo predefinido (64 caracteres). 
    √ -Método para imprimir la cadena 
    √ -Método para obtener la longitud de la cadena.
    √ -Método que devuelva índice de la primera o ultima aparición de un carácter (Si no existe -1, puede o no ser Case sensitive)
    √ -Métodos conviertan los caracteres de la cadena a upper, lower, title or capitalize.
    √ -Método que reemplace todas las ocurrencias de oldChar por newChar en la cadena.
    √ Método que elimine el carácter en la posición especificada. (-1 para la ultima posicion)
    √ -Método que inserte un carácter en una posición específica de la cadena. (-1 para la ultima posicion)
    √ -Método que determine si la cadena actual es un palíndromo (se lee igual de izquierda a derecha que de derecha a izquierda).
    √ -Método que elimine los espacios en blanco o un char especifico de la cadena.
    √ -Método que invierta los caracteres de la cadena.
    √ -Método que cuente cuántas veces aparece un carácter específico en la cadena.
    √ -Concatenar con otra cadena al final o principio de la cadena actual.
    √ -Método que ajuste la longitud de la cadena a un ancho fijo. Si la cadena es más corta que el ancho, rellena con el carácter
        fillChar. Si es más larga, corta los caracteres excedentes.
    √ -Método que determine si la cadena actual empieza o termina con una subcadena específica.
    √ -Método que determine si la cadena actual contiene una subcadena específica.
    √ -Implementa un método estatico que compare si dos cadenas son iguales.
    √ -Método que devuelva una nueva instancia de MyString que contenga una subcadena de la cadena actual, 
        comenzando en la posición start y con una longitud de length.
*/

class myString {
private:
    char* str;
    int length = 0;

public:
    myString(int size = 64){ 
        str = new char[size]; 
        *(this->str+0) = '\0';
    }
    ~myString(){ delete[] str; }

    void initString(); //Metodo para ingresar texto e inicializar tamaño
    void show() const; //Metodo para imprimir el string
    int getLen() const { return this->length; }
    myString copy() const; //Crear y retornar copia del string
    int lookFor(char character, bool first = true, bool caseSensitive = true) const;
    void transformTo(string which); //Metodo para convertir string a upper case, lower case, title o capitalize
    void replace(char oldChar, char newChar, int limit = 64);
    void remove(char character = ' '); //Metodo para eliminar espacios en blanco o caracter en especifico de la cadena
    void indexRemove(int index); //Metodo para eliminar caracter de un index en especifico
    void insertIn(char character, int index); //Metodo para insertar un caracter en una posicion especifica
    bool isPalindrome() const; //Metodo para comprobar si una palabra se lee igual de derecha a izquierda y viceversa
    void transpose(); //Metodo para invertir la cadena
    int count(char character) const; //Metodo para contar las apariciones de una palabra en la cadena
    void concat(const myString& string, bool end = true); //Metodo para concatenar otra cadena al incio o final
    void fill(int newLen, char fillchar = '*'); //Metodo para ajustar la longitud de la cadena
    bool startsEndsWith(const myString& string, bool starts = true) const; //Metodo para verificar si la cadena termina o comienza con otra cadena especifica
    bool isIn(const myString& string) const; //Metodo para verificar si cadena contiene una subcadena especifica
    static bool isEqual(const myString& string1, const myString& string2, bool caseSensitive = false); //Metodo estatico para comparar si dos cadenas son iguales
    myString subString(int startsIndex) const; //Metodo para retornar una subcadena a partir de un index
};

void excercises1(myString* myStr){
    char lookFor, newChar, oldChar, countChar;
    cout<<"String has "<<myStr->getLen()<<" characters\n";
    cout<<"String content: "; myStr->show();

    cout<<"What character do you want to know the index (-1 if it doesn't exist) => ";
    cin>>lookFor;
    cout<<"First position: "<<myStr->lookFor(lookFor);
    cout<<"\nLast position: "<<myStr->lookFor(lookFor, false);
    cout<<"\nNo case sensitive and first: "<<myStr->lookFor(lookFor, true, false);
    
    cout<<"\nString to upper: "; myStr->transformTo("upper"); myStr->show();
    cout<<"String to title: "; myStr->transformTo("title"); myStr->show();
    cout<<"String to capitalize: "; myStr->transformTo("capitalize"); myStr->show();
    cout<<"String to lower: "; myStr->transformTo("lower"); myStr->show();

    cout<<"Type the char to be replaced => "; cin>>oldChar;
    cout<<"Type the new char to replace ("<<oldChar<<") => "; cin>>newChar;
    myStr->replace(oldChar, newChar);
    myStr->show();

    cout<<"Is palidrome: "<<boolalpha<<myStr->isPalindrome()<<"\n";
    myStr->show();

    myStr->transpose();
    cout<<"Inverted string: "; myStr->show();
    myStr->transpose();

    cout<<"Type the character to count => "; cin>>countChar;
    cout<<countChar<<" is "<<myStr->count(countChar)<<" times in string\n";
}  

void excercises2(myString* myStr){
    int indexToRemove, indexToInsert, indexToFill;
    char charToInsert;
    myString strToConcat = myString();
    myString strCopy = myStr->copy(); 

    cout<<"Type the index to delete in string => "; 
    cin>>indexToRemove;
    cin.ignore();
    myStr->indexRemove(indexToRemove); 
    myStr->show();

    cout<<"Type the index to insert in string => "; 
    cin>>indexToInsert; cin.ignore();
    cout<<"Type the char to insert in index ("<<indexToInsert<<") => "; 
    cin>>charToInsert;
    myStr->insertIn(charToInsert, indexToInsert);
    myStr->show();

    cout<<"String to concat: \n"; cin.ignore(); 
    strToConcat.initString();
    cout<<"String concat end: ";
    strCopy.concat(strToConcat); strCopy.show();
    cout<<"String concat begin: ";
    strCopy.concat(strToConcat, false); strCopy.show();

    cout<<"Type new size of the string => "; 
    cin>>indexToFill; cin.ignore();
    strCopy.fill(indexToFill); strCopy.show();
    cout<<"String length: "<<strCopy.getLen()<<"\n";
}   

void excercises3(myString* myStr){
    myString verifyStarts = myString();
    myString verifyEnds = myString();
    myString verifyIsIn = myString();
    myString toCompare = myString();
    int indexToSubStr;

    cout<<"String to compare if starts with: ";
    verifyStarts.initString();
    cout<<boolalpha<<myStr->startsEndsWith(verifyStarts)<<"\n";

    cout<<"String to compare if ends with: ";
    verifyEnds.initString();
    cout<<boolalpha<<myStr->startsEndsWith(verifyEnds, false)<<"\n";

    cout<<"String to compare if is in the string: ";
    verifyIsIn.initString();
    cout<<boolalpha<<myStr->isIn(verifyIsIn)<<"\n";

    myStr->show();

    cout<<"String to compare: "; 
    toCompare.initString();
    cout<<"No case sensitive: "<<boolalpha<<myString::isEqual(*myStr, toCompare)<<"\n";
    cout<<"Case sensitive: "<<boolalpha<<myString::isEqual(*myStr, toCompare, true)<<"\n";

    cout<<"Type the index to start the new sub string => ";
    cin>>indexToSubStr; cin.ignore();
    cout<<"New Sub String: ";
    myStr->subString(indexToSubStr).show();
}  

int main(){
    char action;
    do{
        cout<<"String exercises\n";
        myString myStr = myString();
        myStr.initString();

        excercises1(&myStr);
        excercises2(&myStr);
        excercises3(&myStr);

        cout<<"Continue (y/n)? => ";
        cin>>action;
        cin.ignore();

        system("cls");

    } while (tolower(action) != 'n');
    
    return 0;
}

void myString::initString(){ //Metodo para ingresar texto e inicializar tamaño
    cout<<"Type string's text => ";
    cin.getline(str, 64);
    
    this->length = 0;
    for (int i = 0; i < 64 && *(str+i) != '\0'; ++i) { this->length++; }
}

void myString::show() const { //Metodo para imprimir el string 
    for (int i = 0; i < this->length; i++){
        cout<<*(this->str+i);
    }
    cout<<"\n";
}

myString myString::copy() const { //Crear y retornar copia del string
    myString copy = myString(this->length+1);
    for (int i = 0; i < this->length; i++){
        *(copy.str+i) = *(this->str+i);
    }
    copy.str[this->length] = '\0';
    copy.length = this->length;
    return copy;
}

int myString::lookFor(char character, bool first, bool caseSensitive) const {
    //Metodo para buscar y retornar index de caracteres en cadena 
    myString copy = this->copy();
    if (!caseSensitive){
        character = tolower(character);
        for (int i = 0; i < this->length; i++){
            *(copy.str+i) = tolower(*(this->str+i));
        }
    }
    
    if (first){
        for (int i = 0; i < copy.length-1; i++){
            if (*(copy.str+i) == character) { return i; }
        }
    }
    else{
        for (int i = copy.length-1; i >= 0; i--){
            if (*(copy.str+i) == character) { return i; }
        }
    }
    return -1;
}

void myString::transformTo(string which){ //Metodo para convertir string a upper case, lower case, title o capitalize
    if (which != "upper" && which != "lower" && which != "title" && which != "capitalize"){
        throw invalid_argument("Invalid argument, must be 'upper', 'lower', 'title' or 'capitalize'\n");
    }

    for (int i = 0; i < this->length; i++){

        if (which == "upper"){ //Todas las letras a mayuscula
            *(this->str+i) = toupper(*(this->str+i)); 
        }

        else if (which == "lower"){ //Todas las letras a minuscula
            *(this->str+i) = tolower(*(this->str+i));
        }

        else if (which == "title"){ //Cada letra de comienzo de palabra a masyucula
            if (*(this->str+i) == ' '){
                *(this->str+i+1) = toupper(*(this->str+i+1));
                i++;
            } 
            else if (i == 0){
                *(this->str+i) = toupper(*(this->str+i));
            }
            else {
                *(this->str+i) = tolower(*(this->str+i));
            }
        }

        else if (which == "capitalize"){ //Solo primera letra a masyucula
            if (i == 0){
                *(this->str+i) = toupper(*(this->str+i));    
            } else {
                *(this->str+i) = tolower(*(this->str+i));
            }
        }
    }
}

void myString::replace(char oldChar, char newChar, int limit){ 
    /*Metodo para reemplazar un char por /otro en toda la cadena, podemos agregar limite para solo 
    hacer cierta cantidad de reemplazos*/
    int changes = 0;
    for (int i = 0; i < this->length; i++){
        if (changes == limit){
            break;
        }
        if (*(this->str+i) == oldChar){
            *(this->str+i) = newChar;
            changes++;
        }
    }
}

void myString::remove(char character){ //Metodo para eliminar espacios en blanco o caracter en especifico de la cadena
    for (int i = 0; i < this->length; i++){
        //Al hallar una posicion que sea igual al char especificado
        if (*(this->str+i) == character){
            this->length--; //Decrementaremos la lonigtud de la cadena
            for (int j = i; j < this->length; j++){
                //Entramos en otro for que correra las posiciones 
                *(this->str+j) = *(this->str+j+1);
            }
            i--;
        }
    }
}

void myString::indexRemove(int index){ //Metodo para eliminar caracter de un index en especifico
    if (index == -1){ index = this->length-1; } //-1 se tomara como la ultima posicion

    for (int i = 0; i < this->length; i++){
        if (i == index){
            /*Al encontrarlo, corremos la cadena una posicion hacia la izquierda, 
            eliminando asi el char de la posicion indicada*/ 
            this->length--;
            for (int j = i; j < this->length; j++){
                *(this->str+j) = *(this->str+j+1);
            }
            break;
        }
    }
}

void myString::insertIn(char character, int index){ //Metodo para insertar un caracter en una posicion especifica
    if (index == -1){ 
        index = this->length; 
        this->length++;
        *(this->str+index) = character;
        *(this->str+(index+1)) = '\0';
        return;
    }

    //Creamos una copia del string original con el fin de tener los caracteres originales
    myString originalCopy = this->copy(); 

    for (int i = 0; i < this->length; i++){
        if (i == index){
            *(this->str+i) = character; //Agregamos el caracter a la posicion especificada 
            this->length++;

            for (int j = i+1; j < this->length; j++){
                /*Recorremos el resto de la cadena agregando los caracteres que previamente
                estaban presentes*/
                *(this->str+j) = originalCopy.str[j-1];
            }
            break;
        }
    }
}

bool myString::isPalindrome() const {
    myString copy = this->copy(); //Creamos una copia para no modificar la cadena original

    copy.remove(); //Removemos espacios en blanco
    int reverse = copy.length-1; //Variables para recorrer la cadena a la inversa
    int equals = 0;
    copy.transformTo("lower"); //Convertimos las palabras a minuscula para garantizar uniformidad

    for (int i = 0; i < copy.length/2; i++){
        if (copy.str[i] == copy.str[reverse-i]){
            equals++;
        }
    }

    return (equals == copy.length/2);
}

void myString::transpose(){ //Metodo para invertir la cadena
    myString copy = this->copy();

    for (int i = this->length-1, j = 0; i >= 0; i--, j++){
        *(this->str+j) = copy.str[i];
    }
}

int myString::count(char character) const { //Metodo para contar las apariciones de una palabra en la cadena
    int counter = 0;
    
    for (int i = 0; i < this->length; i++){
        if (*(this->str+i) == character){ counter++; }
    }
    return counter;
}

void myString::concat(const myString& string, bool end){ //Metodo para concatenar otra cadena al incio o final
    if (this->length+string.getLen() > 64){ throw length_error("The new length of string is not allow\n"); }
    
    for (int i = 0; i < string.getLen(); i++){
        //Por medio del metodo anteriormente realizado insertamos el caracter en la respectiva posicion
        if (end){ this->insertIn(string.str[i], -1); } 
        else { this->insertIn(string.str[i], i); }
    }
}

void myString::fill(int newLen, char fillchar){ //Metodo para ajustar la longitud de la cadena
    if (newLen <= 0 || newLen > 64){ throw length_error("The new length of string is not allow\n"); }

    if (newLen < this->length){
        *(this->str+newLen) = '\0'; //En caso de que sea menor truncamos la cadena 
        this->length = newLen;
    } else {
        for (int i = 0; i < newLen; i++){ 
            /*Evaluamos que no haya algun caracter en el index de la iteracion, y en
            caso de no haberlo agregamos con el caracter especificado*/ 
            if (!*(this->str+i)){ this->insertIn(fillchar, -1); } 
        }
    }
}

bool myString::startsEndsWith(const myString& string, bool starts) const { //Metodo para verificar si la cadena termina o comienza con otra cadena especifica
    if (string.length > this->length) { return false; }
    
    int coincidences = 0; //Se llevara un conteo de las concidencias
    if (starts){
        //Recorremos desde la 1ra posicion de cada cadena y si conciden incrementamos las coincidencias
        for (int i = 0; i < string.length; i++){
            if (*(this->str+i) == string.str[i]){ coincidences++; }
        }
    } else {
        /*Definimos la ultima posicion de cada cadena y las recorremos decrementandolas en cada iteracion  
        en caso de tener el mismo caracter incrementamos las coincidencias*/
        for (int i = string.length-1, j = this->length-1; i >= 0; i--, j--){
            if (*(this->str+j) == string.str[i]){ coincidences++; }
        }
    }
    return (coincidences == string.length); //Si hubo coincidencias en todos los caracteres de la cadena ingresada retornara true
}

bool myString::isIn(const myString& string) const { //Metodo para verificar si cadena contiene una subcadena especifica
    if (string.length > this->length){ return false; }
    
    //Recorremos la diferencia entre los tamaños de las cadenas con el fin evitar iteraciones innecesarias
    for (int i = 0; i <= this->length-string.length; i++){
        int j = 0;
        while (j < string.length && this->str[i + j] == string.str[j]) {
            j++;
        }
        if (j == string.length) {
            return true;
        }
    }
    return false;
}  

bool myString::isEqual(const myString& string1, const myString& string2, bool caseSensitive){ //Metodo estatico para comparar si dos cadenas son iguales
    if (string1.length != string2.length) { return false; }

    myString stringCopy1 = string1.copy();
    myString stringCopy2 = string2.copy();

    if (!caseSensitive) {
        stringCopy1.transformTo("lower");
        stringCopy2.transformTo("lower");
    }

    for (int i = 0; i < stringCopy1.length; i++) {
        if (stringCopy1.str[i] != stringCopy2.str[i]) { return false; }
    }

    return true;
}

myString myString::subString(int startsIndex) const { //Metodo para retornar una subcadena a partir de un index
    if (startsIndex < 0 || startsIndex >= this->length){ throw out_of_range("Index out of range'\n"); }
    
    int newStrLen = this->length - startsIndex;
    myString newStr(newStrLen+1);
    
    for (int i = 0; i < newStrLen; i++){
        newStr.str[i] = *(this->str+(startsIndex+i));
    }

    newStr.str[newStrLen] = '\0';
    newStr.length = newStrLen;
    return newStr;
}