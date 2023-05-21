#ifndef TSARVORE23_H
#define TSARVORE23_H
#include <iostream>

using namespace std;

template <class Key, class Item>
class Node23 {
    public:
    Node23(){};
    Node23(Key key, Item val, bool ehDoisNo);

    Key key1;
    Item val1;
 
    Key key2;
    Item val2;

    Node23 * ap1;   // Aponta para os menores que key1
    Node23 * ap2;   // Aponta para os entre key1 e key2
    Node23 * ap3;   // Aponta para os maiores que key2

    bool ehDoisNo;

    bool ehFolha();

    int N;
};

template <class Key, class Item>
Node23<Key, Item>::Node23(Key key, Item val, bool ehDoisNo){
    key1 = key;
    val1 = val;
    this->ehDoisNo = ehDoisNo;
}

template <class Key, class Item>
bool Node23<Key, Item>::ehFolha(){
    return (ap1 == nullptr && ap2 == nullptr && ap3 == nullptr);
}


template <class Key, class Item>
class TSArvore23 {
    private:
    Node23<Key, Item> * put23(Node23<Key, Item> * raiz, Key key, Item val, bool &cresceu);
    bool cresceu;
    Item get(Node23<Key, Item> * raiz, Key key);
    Key select(Node23<Key, Item> * raiz, int k);
    int size(Node23<Key, Item> * raiz);
    int rank(Node23<Key, Item> * raiz, Key key); 
    /*void printRecursive(Node* node) {
        if (node != nullptr) {
            if (node->ehDoisNo) {
                printRecursive(node->ap1);
                if (node->key1 == "") {
                    std::cout << "foi uma k1 de 2no" << std::endl;
                    std::cout << node->ap1->key1 << std::endl;
                } 
                std::cout << node->key1 << ": "<< node->val1.toString() << std::endl;
                printRecursive(node->ap3);
            } else {
                printRecursive(node->ap1);
                if (node->key1 == "") {
                    std::cout << "foi uma k1 de 3no" << std::endl;
                } 
                std::cout << node->key1 << ": "<< node->val1.toString() << std::endl;
                printRecursive(node->ap2);
                if (node->key2 == "") {
                    std::cout << "foi uma k2 de 3no" << std::endl;
                } 
                std::cout << node->key2 << ": "<< node->val2.toString() << std::endl;
                printRecursive(node->ap3);
            }
        }
    }*/
    public:

    Node23<Key, Item> * raiz;
    void mostra(Node23<Key, Item> * raiz, bool ehRaiz);
    //void print();
    void add(Key key, Item val);
    Item value(Key key);
    int rank(Key key);
    Key select(int k);
};

template <class Key, class Item>
void TSArvore23<Key, Item>::mostra(Node23<Key, Item> * raiz, bool ehRaiz){
    if(raiz == nullptr) return;
    if(ehRaiz){
        if(raiz->ehDoisNo) cout << "raiz = (" << raiz->key1 << ")" << endl;
        else  cout << "raiz = (" << raiz->key1 << " ; " << raiz->key2 << ")" << endl;
    }
    else{
        if(raiz->ehDoisNo) cout << "(" << raiz->key1 << ")" << endl;
        else cout << "(" << raiz->key1 << " ; " << raiz->key2 << ")" << endl;
    }
    if(raiz->ehDoisNo){
        if(raiz->ap1 != nullptr){
            cout << "filho esquerdo de (" << raiz->key1 << ") = ";
            mostra(raiz->ap1, false);
        }
        if(raiz->ap3 != nullptr){
            cout << "filho direito de (" << raiz->key1 << ") = ";
            mostra(raiz->ap3, false);
        }
        return;
    }
    else{
        if(raiz->ap1 != nullptr){
            cout << "filho esquerdo de (" << raiz->key1 << " ; " << raiz->key2 << ") = ";
            mostra(raiz->ap1, false);
        }
        if(raiz->ap2 != nullptr){
            cout << "filho centro de (" << raiz->key1 << " ; " << raiz->key2 << ") = ";
            mostra(raiz->ap2, false);
        }
        if(raiz->ap3 != nullptr){
            cout << "filho direito de (" << raiz->key1  << " ; " << raiz->key2 << ") = ";
            mostra(raiz->ap3, false);
        }
        return;
    }
}


template <class Key, class Item>
Key TSArvore23<Key, Item>::select(int k){
    return select(raiz, k);
}

template <class Key, class Item>
Key TSArvore23<Key, Item>::select(Node23<Key , Item> * raiz, int k){
    if(raiz == nullptr) return Key();
    if(raiz->ehDoisNo){
        int t = size(raiz->ap1);
        if(t > k) return select(raiz->ap1, k);
        else if(t < k) return select(raiz->ap3, k - t - 1);
        else return raiz->key1;
    }
    else{
        int t1 = size(raiz->ap1);
        int t2 = size(raiz->ap2);
        if(k == t1) return raiz->key1;
        if(k == t1 + t2 + 1) return raiz->key2;
        if(k < t1) return select(raiz->ap1, k);
        if(k > t1 && (t1 + t2 + 1) > k) return select(raiz->ap2, k - t1 - 1);
        if(k > t1 + t2) return select(raiz->ap3, k - t1 - t2 - 2);

    }
}


template <class Key, class Item>
int TSArvore23<Key, Item>::size(Node23<Key, Item> * raiz){
    if(raiz == nullptr) return 0;
    return raiz->N;
}

template <class Key, class Item>
int TSArvore23<Key, Item>::rank(Node23<Key, Item> * raiz, Key key){
    if(raiz == nullptr) return 0;
    if(raiz->ehDoisNo){
        if(key == raiz->key1){
            //if(key == "b") cout << "size(raiz->ap1) = " << size(raiz->ap1) << endl;
            return size(raiz->ap1);
        }
        else if(key < raiz->key1) return rank(raiz->ap1, key);
        else{
            //if(key == "b") cout << "size(raiz->ap1) = " << size(raiz->ap1) << endl;
            return 1 + size(raiz->ap1) + rank(raiz->ap3, key);
        }
    }
    else{
        if(key == raiz->key1) return size(raiz->ap1);
        if(key == raiz->key2) return size(raiz->ap1) + size(raiz->ap2) + 1;
        if(key < raiz->key1) return rank(raiz->ap1, key);
        if(key > raiz->key2) return 2 + size(raiz->ap1) + size(raiz->ap2) + rank(raiz->ap3, key);
        if(raiz->key2 > key && key > raiz->key1) return 1 + size(raiz->ap1) + rank(raiz->ap2, key);

    }
}

template <class Key, class Item>
int TSArvore23<Key, Item>::rank(Key key){
    return rank(raiz, key);
}

template <class Key, class Item>
Item TSArvore23<Key, Item>::value(Key key){
    return get(raiz, key);
}

template <class Key, class Item>
Item TSArvore23<Key, Item>::get(Node23<Key, Item> * raiz, Key key){
    if(raiz == nullptr) return Item();
    if(raiz->ehDoisNo){
        if(raiz->key1 == key) return raiz->val1;
        if(raiz->key1 > key) return get(raiz->ap1, key);
        if(raiz->key1 < key) return get(raiz->ap3, key);
    }
    else{
        if(raiz->key1 == key) return raiz->val1;
        if(raiz->key2 == key) return raiz->val2;
        if(raiz->key1 > key) return get(raiz->ap1, key);
        if(raiz->key2 > key && key > raiz->key1) return get(raiz->ap2, key);
        if(raiz->key2 < key) return get(raiz->ap3, key);
    }
}

template <class Key, class Item>
void TSArvore23<Key, Item>::add(Key key, Item val){
    raiz = put23(raiz, key, val, cresceu);
}

template <class Key, class Item>
Node23<Key, Item> * TSArvore23<Key, Item>::put23(Node23<Key, Item> * raiz, Key key, Item val, bool &cresceu){
    if(raiz == nullptr){
        raiz = new Node23<Key, Item>(key, val, true);
        return raiz;
    }
    if(raiz->ehFolha()){          // Caso base da recursão.
        if(raiz->ehDoisNo){      // Tem espaço pra colocar key no nó.
            if(raiz->key1 == key){
                raiz->val1 = val;
                cresceu = false;
                return raiz;
            }
            else if(raiz->key1 > key){
                raiz->key2 = raiz->key1;
                raiz->val2 = raiz->val1;
                raiz->key1 = key;
                raiz->val1 = val;
                raiz->ehDoisNo = false;
            }
            else{
                raiz->key2 = key;
                raiz->val2 = val;
                raiz->ehDoisNo = false;
            }
            cresceu = false;
            raiz->N = size(raiz->ap1) + size(raiz->ap2) + size(raiz->ap3) + 2;
            return raiz;
        }
        // A folha é 3Nó, então vai acontecer split.
        else{
            Node23<Key, Item> * novaRaiz = new Node23<Key, Item>();
            Node23<Key, Item> * novo = new Node23<Key, Item>();
            if(raiz->key2 == key){
                raiz->val2 = val;
                cresceu = false;
                return raiz;
            }
            else if(raiz->key1 == key){
                raiz->key1 = key;
                raiz->val1 = val;
                cresceu = false;
                return raiz;
            }
            else if(raiz->key1 > key){  // key é o menor dos três
                novaRaiz->key1 = raiz->key1;
                novaRaiz->val1 = raiz->val1;
                raiz->key1 = key;
                raiz->val1 = val;
                novo->key1 = raiz->key2;
                novo->val1 = raiz->val2;
            }
            else if(raiz->key2 > key && key > raiz->key1){  // key está no meio
                novo->key1 = raiz->key2;
                novo->val1 = raiz->val2;
                novaRaiz->key1 = key;
                novaRaiz->val1 = val;
            }
            else{  // key é o maior dos três
                novo->key1 = key;
                novo->val1 = val;
                novaRaiz->key1 = raiz->key2;
                novaRaiz->val1 = raiz->val2;
            }
            novo->ehDoisNo = novaRaiz->ehDoisNo = raiz->ehDoisNo = true;
            novaRaiz->ap1 = raiz;
            novaRaiz->ap3 = novo;
            cresceu = true;
            raiz->N = size(raiz->ap1) + size(raiz->ap3) + 1;
            novo->N = size(novo->ap1) + size(novo->ap3) + 1;
            novaRaiz->N = size(novaRaiz->ap1) + size(novaRaiz->ap3) + 1;
            return novaRaiz;
        }
    }
    // Saímos do caso base
    if(raiz->ehDoisNo && raiz->key1 == key){
        raiz->val1 = val;
        return raiz;
    } 
    if(!raiz->ehDoisNo){
        if(raiz->key1 == key){
            raiz->val1 = val;
            return raiz;
        } 
        if(raiz->key2 == key){
            raiz->val2 = val;
            return raiz;
        } 
        
    }
    if(raiz->key1 > key){
        Node23<Key, Item> * p = put23(raiz->ap1, key, val, cresceu);     
        // Colocamos uma key na árvore.
        if(cresceu){
            // Agora, se a árvore cresceu, teremos que balancear.
            if(raiz->ehDoisNo){
                raiz->key2 = raiz->key1;
                raiz->val2 = raiz->val1;
                raiz->key1 = p->key1;
                raiz->val1 = p->val1;
                raiz->ap1 = p->ap1;
                raiz->ap2 = p->ap3;
                raiz->ehDoisNo = false;
                cresceu = false;
                delete p;
                raiz->N = size(raiz->ap1) + size(raiz->ap2) + size(raiz->ap3) + 2;
                return raiz;
            }
            else{
                Node23<Key, Item> * novaRaiz = new Node23<Key, Item>();
                novaRaiz->key1 = raiz->key1;
                novaRaiz->val1 = raiz->val1;
                novaRaiz->ap1 = p;
                novaRaiz->ap3 = raiz;

                raiz->key1 = raiz->key2;
                raiz->val1 = raiz->val2;
                raiz->ap1 = raiz->ap2;

                novaRaiz->ehDoisNo = raiz->ehDoisNo = p->ehDoisNo = true;
                cresceu = true;
                raiz->N = size(raiz->ap1) + size(raiz->ap3) + 1;
                p->N = size(p->ap1) + size(p->ap3) + 1;
                novaRaiz->N = size(novaRaiz->ap1) + size(novaRaiz->ap3) + 1;
                return novaRaiz;
            }        
        }
        else{
            // Se não cresceu, então a árvore já está balanceada.
            return raiz;
        }
    }
    Key aux;
    if(raiz->ehDoisNo) aux = raiz->key1;
    else aux = raiz->key2;
    if(key > aux){
        Node23<Key, Item> * p = put23(raiz->ap3, key, val, cresceu);
        if(cresceu){
            if(raiz->ehDoisNo){/*
                if(p->key1 == "aaaa"){
                    cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << endl;
                    cout << "raiz é dois no = "  << raiz->ehDoisNo << endl;
                    cout << "antes de balancear: " << endl;
                    cout << "raiz = " << raiz->key1 << " size(raiz->ap1) = " << size(raiz->ap1);
                    cout << " size(raiz->ap3) = " << size(raiz->ap3) << endl;
                } */
                raiz->ehDoisNo = false;
                raiz->key2 = p->key1;
                raiz->val2 = p->val1;
                raiz->ap2 = p->ap1;
                raiz->ap3 = p->ap3;
                delete p;
                cresceu = false;
                raiz->N = size(raiz->ap1) + size(raiz->ap3) + 1;
                return raiz;
            }
            else{
                Node23<Key, Item> * novaRaiz = new Node23<Key, Item>();
                /*if(p->key1 == "bbb"){
                    cout << "raiz é dois no = "  << raiz->ehDoisNo << endl;
                    cout << "antes de balancear: " << endl;
                    cout << "raiz = " << raiz->key1 << " size(raiz->ap1) = " << size(raiz->ap1);
                    cout << " size(raiz->ap3) = " << size(raiz->ap3) << endl;
                } */
                novaRaiz->key1 = raiz->key2;
                novaRaiz->val1 = raiz->val2;
                
                raiz->ap3 = raiz->ap2;

                novaRaiz->ap1 = raiz;
                novaRaiz->ap3 = p;

                novaRaiz->ehDoisNo = p->ehDoisNo = raiz->ehDoisNo = true;
                cresceu = true;
                raiz->N = size(raiz->ap1) + size(raiz->ap3) + 1;
                /*if(p->key1 == "bbb"){
                    cout << "raiz é dois no = "  << raiz->ehDoisNo << endl;
                    cout << "raiz = " << raiz->key1 << " size(raiz->ap1) = " << size(raiz->ap1);
                    cout << " size(raiz->ap3) = " << size(raiz->ap3) << endl;
                } */
                p->N = size(p->ap1) + size(p->ap3) + 1;
                novaRaiz->N = size(novaRaiz->ap1) + size(novaRaiz->ap3) + 1;
                return novaRaiz;
            }
        }
        else{
            /*if(p->key2 == "aaaa"){
                cout << "raiz é dois no = "  << raiz->ehDoisNo << endl;
                cout << "raiz = " << raiz->key1 << " size(raiz->ap1) = " << size(raiz->ap1);
                cout << "; size(raiz->ap3) = " << size(raiz->ap3) << endl;
            }*/
            return raiz;
        }
    }
    if((!raiz->ehDoisNo) && (raiz->key2 > key) && (key > raiz->key1)){
        Node23<Key, Item> * p = put23(raiz->ap2, key, val, cresceu);
        if(cresceu){
            Node23<Key, Item> * novaRaiz = new Node23<Key, Item>();
            novaRaiz->key1 = p->key1;
            novaRaiz->val1 = p->val1;
            
            novaRaiz->ap2 = p->ap1;     // Usando como variável auxiliar
            
            p->key1 = raiz->key2;
            p->val1 = raiz->val2;
            p->ap1 = p->ap3;
            p->ap3 = raiz->ap3;

            raiz->ap3 = novaRaiz->ap2;  // Recuperando o valor armazenado na variável auxiliar
            
            novaRaiz->ap1 = raiz;
            novaRaiz->ap3 = p;

            novaRaiz->ehDoisNo = p->ehDoisNo = raiz->ehDoisNo = true;
            cresceu = true;
            raiz->N = size(raiz->ap1) + size(raiz->ap3) + 1;
            p->N = size(p->ap1) + size(p->ap3) + 1;
            novaRaiz->N = size(novaRaiz->ap1) + size(novaRaiz->ap3) + 1;
            return novaRaiz;
        }
        else{
            return raiz;
        }
    }
}





#endif