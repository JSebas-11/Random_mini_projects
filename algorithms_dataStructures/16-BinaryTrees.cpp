/*Arboles binarios: Estructura de datos jerárquica donde cada nodo tiene dos hijos (izq-der)

Raiz: Nodo principal del árbol.
Nodos: Elementos que almacenan información y tienen conexiones con otros nodos.
Hijos: Son los nodos que descienden de otro nodo padre.
Hojas: Nodos que no tienen hijos.
Altura: La cantidad de niveles en el árbol.*/

/*Crear un Árbol Binario de Búsqueda (BST) con las siguientes operaciones:
    -Insertar valores en el árbol.
    -Buscar un valor en el árbol.
    -Eliminar un nodo del árbol.
    -Recorrer el árbol en orden (inorden), postorden, preorden.
    -Limpiar el árbol.
    -Balancear el árbol.

Probar diferentes casos en la estructura del árbol.
    -Eliminacion nodos con diferentes casos (Nodo hoja, nodo con 1 hijo, nodo con 2 hijos.)
Agrega funciones como:
    -Obtener min y max.    
    -altura(): Devuelve la altura del árbol.
    -contarNodos(): Cuenta la cantidad de nodos en el árbol.*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

const string STRAIGHT_LINES = "----------------------------------------------\n";

struct btNode{
    int value;
    btNode* left;
    btNode* right;

    btNode(int _value){
        this->value = _value;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinaryTree{
private:
    btNode* root;
    vector<btNode*> nodesVector;
    int nodes;
    int height;
    int leaves;

    int setHeight(btNode* node) const {
       if (!node) { return 0; }
       int leftHeight = setHeight(node->left);
       int rightHeight = setHeight(node->right);
       return 1 + max(leftHeight, rightHeight);
    }

    void setLeaves(btNode* node){
        if (!node){ return; }
        
        if (!node->left && !node->right){ 
            this->leaves++;
            return; 
        } 
        setLeaves(node->left);
        setLeaves(node->right);
    }

    void removeNode(btNode* node, btNode* parent){
        if (!node) { return; }

        this->removeNode(node->left, node);
        this->removeNode(node->right, node);

        if (parent){
            //Redireccionamos a null el ptr padre del hijo correspondiente a eliminar
            if (node->value < parent->value) { parent->left = nullptr; }
            else { parent->right = nullptr; }
        } 

        if (node == this->root) { this->root = nullptr; }

        cout<<"Node ("<<node->value<<") has been deleted\n";
        delete node;
        this->nodes--;
        this->height = this->setHeight(this->root);
        this->leaves = 0;
        this->setLeaves(this->root);
    }

    void store(btNode* node){
        if (!node){ return; }
        store(node->left);
        this->nodesVector.push_back(new btNode(node->value));
        store(node->right);
    }

    btNode* newBalancedTree(int start, int end){
        if (start > end){ return nullptr; }
        int mid = (start+end)/2;
        btNode* newRoot = this->nodesVector[mid];
        newRoot->left = newBalancedTree(start, mid-1);
        newRoot->right = newBalancedTree(mid+1, end);
        return newRoot;
    }

    void dispose(btNode* node){
        if (!node){ return; }
        
        dispose(node->left);
        dispose(node->right);
        delete node;
    }

public:
    BinaryTree(){
        this->root = nullptr;
        this->nodes = 0;
        this->height = 0;
        this->leaves = 0;
    };
    ~BinaryTree(){ this->dispose(this->root); };

    int getNumNodes() const { return this->nodes; }
    int getHeight() const { return this->height; }
    int getLeaves() const { return this->leaves; }
    btNode* getRoot() const { return this->root; }

    void addNode(btNode* newNode){
        if (!root){ 
            root = newNode; 
            this->height++;
        }
        else {
            btNode* temp = root;
            while (temp){
                if (newNode->value < temp->value){ //Al ser menor no vamos por la 'rama' izquierda
                    if (!temp->left){
                        //Si no hay hijo izq en el nodo actual, agregamos nuevo nodo alli
                        temp->left = newNode;
                        break;
                    }
                    //En caso de nodo no estar vacio, actualizamos temporal para volver a hacer las verificaciones
                    temp = temp->left; 
                    
                } else if (newNode->value > temp->value) { //Ocurre lo mismo que en 'rama' izquierda pero del lado contrario
                    if (!temp->right){
                        temp->right = newNode;
                        break;
                    }
                    temp = temp->right;
                } else {
                    cout<<"Node with value ("<<newNode->value<<") already exists\n";
                    return;            
                }
            }
        }
        cout<<"Node with value ("<<newNode->value<<") has been added\n";
        this->nodes++;
        this->height = this->setHeight(this->root);
        this->leaves = 0;
        this->setLeaves(this->root);
    }

    void showInorder(const btNode* toShow) const { //Devuelve valores en orden ASC (Izq - Raiz - Der)
        if (!toShow){ return; } //Saldra de la funcion al recibir parametro nulo

        showInorder(toShow->left);
        cout<<toShow->value<<" ";
        showInorder(toShow->right);
    }

    void showPostorder(const btNode* toShow) const { //Util eliminacion o procesamiento en final (Izq - Der - Raiz)
        if (!toShow){ return; }
        
        showPostorder(toShow->left);
        showPostorder(toShow->right);
        cout<<toShow->value<<" ";
    }

    void showPreorder(const btNode* toShow) const { //Util procesamiento de raiz antes que nodos hijos (Raiz - Izq - Der)
        if (!toShow){ return; }
        
        cout<<toShow->value<<" ";
        showPreorder(toShow->left);
        showPreorder(toShow->right);
    }

    void search(int value, bool remove = false){
        btNode* temp = this->root;
        btNode* parent = nullptr;
        int height = 1;

        while (temp){
            //Si encontramos valor en nodo, hacemos las correspondientes operaciones
            if (value == temp->value){
                if (remove){
                    this->removeNode(temp, parent);
                    return;
                } else {
                    string parentValue = (parent) ? to_string(parent->value) : "null";
                    string lChildValue = (temp->left) ? to_string(temp->left->value) : "null";
                    string rChildValue = (temp->right) ? to_string(temp->right->value) : "null";
                    
                    cout<<"Node found:\n\tValue: "<<temp->value<<"\n\tHeight: "<<height<<"\n\tParent: "<<parentValue
                    <<"\n\tLeft Child: "<<lChildValue<<"\n\tRight Child: "<<rChildValue<<"\n";
                    return;
                }
            } 
            //Sino nos movemos a nodo que corresponda
            parent = temp;
            if (value < temp->value){ temp = temp->left; }
            else { temp = temp->right; }
            height++;
        }
        cout<<"Node not found\n";
    }

    int minValue(btNode* node) const {
        if (!node) { return 0; }
        if (!node->left) { return node->value; }
        
        minValue(node->left);
    }

    int maxValue(btNode* node) const {
        if (!node) { return 0; }
        if (!node->right){ return node->value; }
        
        maxValue(node->right);
    }

    void clear(){
        this->dispose(this->root);
        this->root = nullptr;
        this->nodes = 0;
        this->height = 0;
        this->leaves = 0;
        cout<<"Tree cleaned succesfully\n";
    }

    bool isUnbalanced() const {
        if (this->nodes <= 1){ return false; }
        return this->height > log2(this->nodes)*1.5;
    }

    void balance(){
        this->nodesVector = {};
        this->store(this->root);
        this->dispose(this->root);
        this->root = newBalancedTree(0, this->nodesVector.size()-1);
        this->height = this->setHeight(this->root);
        this->leaves = 0;
        this->setLeaves(this->root);
        cout<<"Tree has been balanced\n";
    }

    void loadDefault(){
        this->addNode(new btNode(5));
        this->addNode(new btNode(4));
        this->addNode(new btNode(9));
        this->addNode(new btNode(-2));
        this->addNode(new btNode(8));
        this->addNode(new btNode(0));
        this->addNode(new btNode(3));
        this->addNode(new btNode(6));
        this->addNode(new btNode(-1));
        this->addNode(new btNode(16));
        this->addNode(new btNode(29));
        this->addNode(new btNode(-15));
        this->addNode(new btNode(55));
        this->addNode(new btNode(-13));
        this->addNode(new btNode(36));
        this->addNode(new btNode(13));
        this->addNode(new btNode(40));
    }
};

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

int askNumber(const string& type = "value"){
    if (type != "search" && type != "value" && type != "del"){
        throw invalid_argument("'Type' parameter must by: search or value or del");
    }

    string strNumber;
    int number;
    
    string txtOutput = type == "value" ? "Type the node's value -> " : 
        type == "search" ? "Type the value to look for -> " : "Type the value to delete -> ";  

    while (true){
        cout<<txtOutput;
        getline(cin, strNumber);

        try {
            number = stoi(strNumber);
            return number;
        } catch (const invalid_argument& e) {
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }
    }
}

int main(){

    bool exit = false;
    string option;
    BinaryTree* binTree = new BinaryTree();

    while (!exit){
        cout<<"Actual: nodes ("<<binTree->getNumNodes()<<") height ("<<binTree->getHeight()
        <<") leaves ("<<binTree->getLeaves()<<")\n\t Minumum value ("<<binTree->minValue(binTree->getRoot())
        <<") Maximum value ("<<binTree->maxValue(binTree->getRoot())<<")\n"<<STRAIGHT_LINES;
        cout<<"1. Add node\n2. Delete node\n3. Look for value\n4. Show tree (inorden)"
        <<"\n5. Show tree (postorden)\n6. Show tree (preorden)\n7. Balance tree\n"<<
        "8. Clear tree\n9. Load default tree\n0. Exit\n-> ";
        getline(cin, option);

        if (option == "0"){
            cout<<"Closing program...\n";
            exit = true;

        } else if (option == "1"){
            binTree->addNode(new btNode(askNumber()));
            cleanWait();

        } else if (option == "2"){
            cout<<STRAIGHT_LINES;        
            binTree->search(askNumber("del"), true);
            cout<<STRAIGHT_LINES;
            cleanWait();

        } else if (option == "3"){
            cout<<STRAIGHT_LINES;          
            binTree->search(askNumber());
            cout<<STRAIGHT_LINES;
            cleanWait();

        } else if (option == "4"){
            cout<<STRAIGHT_LINES;
            if (binTree->getNumNodes() == 0){ cout<<"There's nothing to show...\n"; }
            else { 
                cout<<"InOrder:\n";
                binTree->showInorder(binTree->getRoot()); 
                cout<<"\n"; 
            }
            cout<<STRAIGHT_LINES;
            cleanWait();

        } else if (option == "5"){
            cout<<STRAIGHT_LINES;
            if (binTree->getNumNodes() == 0){ cout<<"There's nothing to show...\n"; }
            else { 
                cout<<"PostOrder:\n";
                binTree->showPostorder(binTree->getRoot()); 
                cout<<"\n"; 
            }
            cout<<STRAIGHT_LINES;
            cleanWait();

        } else if (option == "6"){
            cout<<STRAIGHT_LINES;
            if (binTree->getNumNodes() == 0){ cout<<"There's nothing to show...\n"; }
            else { 
                cout<<"PreOrder:\n";
                binTree->showPreorder(binTree->getRoot()); 
                cout<<"\n"; 
            }
            cout<<STRAIGHT_LINES;
            cleanWait();
        
        } else if (option == "7"){
            cout<<STRAIGHT_LINES;
            if (!binTree->isUnbalanced()){ cout<<"This tree doesnt need be balanced...\n"; } 
            else { binTree->balance(); }
            cout<<STRAIGHT_LINES;
            cleanWait();
        
        } else if (option == "8"){
            cout<<STRAIGHT_LINES;
            if (binTree->getNumNodes() == 0){ cout<<"There's nothing to clear...\n"; }
            else { binTree->clear(); }
            cout<<STRAIGHT_LINES;
            cleanWait();
        } 
        
        else if (option == "9"){
            binTree->loadDefault();
            cleanWait();
        
        } else {
            cout<<"Invalid option, try again\n";
        }
    }

    delete binTree;
    return 0;
}