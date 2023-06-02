#include <iostream>   // debugging

template<class Key, class Item>
class A23 {
    private:
        class Node {
        public:
            Key key1, key2;
            Item val1, val2;
            Node* p1;
            Node* p2;
            Node* p3;
            bool eh2no;
            bool cresceu;
            Node() {
                p1 = nullptr;
                p2 = nullptr;
                p3 = nullptr;
                eh2no = true;
            }
            Node(Key key, Item val) {
                this->key1 = key;
                this->val1 = val;
                p1 = nullptr;
                p2 = nullptr;
                p3 = nullptr;
                eh2no = true;
            }
        };
        Node* root;
        void destroyTree(Node* root) {
            if (root != nullptr) {
                destroyTree(root->p1);
                destroyTree(root->p2);
                destroyTree(root->p3);
                delete root;
            }
        }

        Node* put23(Node* root, Key key, Item val, bool &cresceu) {
            if (root == nullptr) { // árvode vazia -> inicializa a árvore
                root = new Node(key, val);
                cresceu = true;
                return root;
            }
            if (root->p1 == nullptr) { // é folha
                if (root->eh2no) { // só adiciona na própria folha
                    if (key > root->key1) {
                        root->key2 = key;
                        root->val2 = val;
                        root->eh2no = false;
                    } else if (key < root->key1) {
                        root->key2 = root->key1;
                        root->val2 = root->val1;
                        root->key1 = key;
                        root->val1 = val;
                        root->eh2no = false;
                    } else { // key == key1 -> atualiza valor
                        root->val1.addOcorrencia();
                    }
                    cresceu = false;
                    return root;
                } else { // é 3 no
                    if (root->key2 == key){
                        root->val2.addOcorrencia();
                        cresceu = false;
                        return root;
                    } else if (root->key1 == key) {
                        root->val1.addOcorrencia();
                        cresceu = false;
                        return root;
                    }
                    Node* newRoot = new Node();
                    Node* newRight = new Node();
                    if (key < root->key1) { // root (recebe key) < newRoot (recebe key1) < newRight (recebe key2)
                        newRoot->key1 = root->key1;
                        newRoot->val1 = root->val1;
                        root->key1 = key;
                        root->val1 = val;
                        newRight->key1 = root->key2;
                        newRight->val1 = root->val2;
                    } else if (key < root->key2) { // root (mantém key1) < newRoot (recebe key) < newRight (recebe key2)
                        newRight->key1 = root->key2;
                        newRight->val1 = root->val2;
                        newRoot->key1 = key;
                        newRoot->val1 = val;
                    } else { // key > root->key2    root (mantém key1) < newRoot (recebe key2) < newRight (recebe key)
                        newRight->key1 = key;
                        newRight->val1 = val;
                        newRoot->key1 = root->key2;
                        newRoot->val1 = root->val2;
                    }
                    root->p2 = nullptr;
                    newRight->eh2no = newRoot->eh2no = root->eh2no = true;
                    newRoot->p1 = root;
                    newRoot->p3 = newRight;
                    cresceu = true;
                    return newRoot; 
                }
            }
            
            /*if (root->eh2no && root->key1 == key){
                root->val1.addOcorrencia();
                return root;
            } 

            if (!(root->p1 == nullptr))*/ else { // nao é folha
                if (!root->eh2no) {
                    if (root->key1 == key){
                        root->val1.addOcorrencia();
                        return root;
                    } 
                    if (root->key2 == key){
                        root->val2.addOcorrencia();
                        return root;
                    } 
                }
                if (root->key1 > key) {
                    Node* p = put23(root->p1, key, val, cresceu);
                    if (cresceu) {
                        if (root->eh2no) { // consigo só inserir
                            root->key2 = root->key1;
                            root->val2 = root->val1;
                            root->key1 = p->key1;
                            root->val1 = p->val1;
                            root->p1 = p->p1;
                            root->p2 = p->p3;
                            root->eh2no = false;
                            cresceu = false;
                            delete p;
                            return root;
                        } else {
                            Node* newRoot = new Node();
                            newRoot->key1 = root->key1;
                            newRoot->val1 = root->val1;
                            newRoot->p1 = p;
                            newRoot->p3 = root;
                            root->key1 = p->key2;
                            root->val1 = p->val2;
                            root->p1 = root->p2;
                            root->p2 = nullptr;
                            newRoot->eh2no = root->eh2no = p->eh2no = true;
                            cresceu = true;
                            return newRoot;
                        }
                    } else { // não cresceu
                        return root;
                    }
                }
                Key tmp;
                if (root->eh2no) tmp = root->key1;
                else tmp = root->key2;
                if (key > tmp) {
                    // é 3-nó e está vindo pela direita
                    // esquerda fica na esquerda
                    // antiga direita vai subir
                    Node* p = put23(root->p3, key, val, cresceu);
                    if (cresceu) {
                        if (root->eh2no) {
                            root->key2 = p->key1;
                            root->val2 = p->val1;
                            root->p2 = p->p1;
                            root->p3 = p->p3;
                            // p1/esquerda permanece inalterada
                            root->eh2no = false;
                            cresceu = false;
                            return root;
                        } else {
                            Node* newRoot = new Node(root->key2, root->val2); // já está vindo pelo meio, então vai subir mais
                            newRoot->p1 = root;
                            newRoot->p3 = p;
                            root->p3 = root->p2;
                            root->p2 = nullptr;
                            newRoot->eh2no = p->eh2no = root->eh2no = true;
                            cresceu = true;
                            return newRoot;
                        }
                    } else { // não cresceu
                        // falta algo?
                        return root;
                    }
                }
                if ((!root->eh2no) && (root->key2 > key) && (key > root->key1)) {
                    Node* p = put23(root->p2, key, val, cresceu);
                    if (cresceu) {
                        Node* newRoot = new Node(root->key1, root->val1);
                        newRoot->p2 = p->p1;
                        newRoot->p1 = root;
                        p->key1 = root->key2;
                        p->val1 = root->val2;
                        p->p1 = p->p3;
                        p->p3 = root->p3;
                        root->p3 = newRoot->p2;
                        newRoot->p1 = root;
                        newRoot->p3 = p;
                        root->p2 = nullptr;
                        newRoot->eh2no = p->eh2no = root->eh2no = true;
                        return newRoot;
                    } else {
                        return root;
                    }
                }
            }
        }

        Item searchRecursive(Node* root, Key key) {
            if (root == nullptr) return Item();
            if (root->eh2no) {
                if (key == root->key1)
                    return root->val1;
                if (key < root->key1) { // procura pela esquerda
                    return searchRecursive(root->p1, key);
                } else { // procura pela direita
                    return searchRecursive(root->p3, key);
                }
            } else {
                if (key == root->key1)
                    return root->val1;
                if (key == root->key2)
                    return root->val2;
                if (key < root->key1) { // procura pela esquerda
                    return searchRecursive(root->p1, key);
                } else if (key > root->key2) { // procura pela direita
                    return searchRecursive(root->p3, key);
                } else { // procura pelo meio
                    return searchRecursive(root->p2, key);
                }
            }
        }
        void printRecursive(Node* node, bool isRoot) {
            if (node != nullptr) {
                if (node->eh2no) {
                    printRecursive(node->p1, isRoot);
                    if (node->key1 == "") {
                        std::cout << "foi uma k1 de 2no" << std::endl;
                        std::cout << node->p1->key1 << std::endl;
                    } 
                    std::cout << node->key1 << ": "<< node->val1.toString() << std::endl;
                    printRecursive(node->p3, isRoot);
                } else {
                    printRecursive(node->p1, isRoot);
                    if (node->key1 == "") {
                        std::cout << "foi uma k1 de 3no" << std::endl;
                    } 
                    std::cout << node->key1 << ": "<< node->val1.toString() << std::endl;
                    printRecursive(node->p2, isRoot);
                    if (node->key2 == "") {
                        std::cout << "foi uma k2 de 3no" << std::endl;
                    } 
                    std::cout << node->key2 << ": "<< node->val2.toString() << std::endl;
                    printRecursive(node->p3, isRoot);
                }
            }
        }
    /*
        void printRecursive(Node* node, bool isRoot) {
            if (node != nullptr) {
                if (isRoot) {
                    if (node->eh2no) 
                        std::cout << "raiz = (" << node->key1 << ")" << std::endl;
                    else
                        std::cout << "raiz = (" << node->key1 << " ; " << node->key2 << ")" << std::endl;
                } else {
                    if (node->eh2no) 
                        std::cout << "(" << node->key1 << ")" << std::endl;
                    else 
                        std::cout << "(" << node->key1 << ": " << node->val1.toString() << " ; " << node->key2 << ": " << node->val2.toString() << ")" << std::endl;
                }
                if (node->eh2no){
                    if (node->p1 != nullptr){
                        std::cout << "filho esquerdo de (" << node->key1 << ") = ";
                        printRecursive(node->p1, false);
                    }
                    if (node->p3 != nullptr){
                        std::cout << "filho direito de (" << node->key1 << ") = ";
                        printRecursive(node->p3, false);
                    }
                    return;
                } else {
                    if (node->p1 != nullptr){
                        std::cout << "filho esquerdo de (" << node->key1 << " ; " << node->key2 << ") = ";
                        printRecursive(node->p1, false);
                    }
                    if (node->p2 != nullptr){
                        std::cout << "filho centro de (" << node->key1 << " ; " << node->key2 << ") = ";
                        printRecursive(node->p2, false);
                    }
                    if (node->p3 != nullptr){
                        std::cout << "filho direito de (" << node->key1  << " ; " << node->key2 << ") = ";
                        printRecursive(node->p3, false);
                    }
                    return;
                }
            }
        }*/
    public:
        A23();
        ~A23();
        void add(Key key, Item val);
        void print();
        Item value(Key key);
};


template<class Key, class Item>
A23<Key, Item>::A23() {
    root = nullptr;
}

template<class Key, class Item>
A23<Key, Item>::~A23() {
    if (root != nullptr) {
        destroyTree(root);
    }
}

template<class Key, class Item>
Item A23<Key, Item>::value(Key key) {
    return searchRecursive(root, key);
}

template<class Key, class Item>
void A23<Key, Item>::add(Key key, Item val) {
    bool cresceu = false;
    root = put23(root, key, val, cresceu);
}

template<class Key, class Item>
void A23<Key, Item>::print() {
    printRecursive(root, 0);
}