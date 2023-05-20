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
                        root->val1 = val;
                    }
                    return root;
                } else { // é 3 no
                    Node* newRoot = new Node();
                    Node* newRight = new Node();
                    if (key < root->key1) { // root (recebe key) < newRoot (recebe key1) < newRight (recebe key2)
                        newRoot->key1 = root->key1;
                        newRoot->val1 = root->val1;
                        newRight->key1 = root->key2;
                        newRight->val1 = root->val2;
                        newRoot->p1 = root;
                        newRoot->p2 = newRight;
                        root->key1 = key;
                        root->val1 = val;
                    } else if (key < root->key2) { // root (mantém key1) < newRoot (recebe key) < newRight (recebe key2)
                        newRoot->key1 = key;
                        newRoot->val1 = val;
                        newRight->key1 = root->key2;
                        newRight->val2 = root->val2;
                        newRoot->p1 = root;
                        newRoot->p2 = newRight;
                    } else { // key > root->key2    root (mantém key1) < newRoot (recebe key2) < newRight (recebe key)
                        newRoot->key1 = root->key2;
                        newRoot->val2 = root->val2;
                        newRight->key1 = key;
                        newRight->val1 = val;
                    }
                    root->eh2no = false;
                    //nullptr root->key2 = nullptr;
                    //nullptr root->val2 = nullptr;
                    cresceu = true;
                    return newRoot; 
                }
            } else { // não é folha
                if (root->key1 > key) {
                    Node* p = put23(root->p1, key, val, cresceu);
                    if (cresceu) {
                        if (root->eh2no) { // consigo só inserir
                            root->key2 = root->key1;
                            root->val2 = root->val1;
                            root->p3 = root->p2;
                            root->key1 = p->key1;
                            root->val1 = p->val1;
                            root->p2 = p->p2;
                            root->eh2no = false;
                            cresceu = false;
                            return root;
                        } else {
                            Node* newRight = new Node(root->key2, root->val2);
                            newRight->p2 = root->p3;
                            newRight->p1 = root->p2;
                            Node* newRoot = new Node(root->key1, root->val1);
                            newRoot->p1 = root;
                            newRoot->p2 = newRight;
                            root->key1 = p->key1;
                            root->val1 = p->val1;
                            //nullptr root->key2 = nullptr;
                            //nullptr root->val2 = nullptr;
                            root->p3 = nullptr;
                            root->eh2no = true;
                            root->p2 = p->p2; 
                            delete(p);
                            cresceu = true;
                            return newRoot;
                        }
                    } else { // não cresceu
                        root->p1 = p; // precisa?
                        cresceu = false; // precisa?
                        return root;
                    }
                } else if (root->eh2no || root->key2 > key) {
                    Node* p = put23(root->p2, key, val, cresceu);
                    if (cresceu) {
                        if (root->eh2no) {
                            root->key2 = p->key1;
                            root->val2 = p->val1;
                            root->p3 = p->p2;
                            //root->p2 = p->p1 (acho que fica igual então estou comentando)
                            // p1/esquerda permanece inalterada
                            root->eh2no = false;
                            cresceu = false;
                            return root;
                        } else {
                            Node* newRight = new Node(root->key2, root->val2);
                            newRight->p2 = root->p3;
                            newRight->p1 = p->p2;
                            Node* newRoot = new Node(p->key1, p->val1); // já está vindo pelo meio, então vai subir mais
                            newRoot->p1 = root;
                            newRoot->p2 = newRight;
                            root->p3 = nullptr;
                            root->eh2no = true;
                            delete(p);
                            cresceu = true;
                            return newRoot;
                        }
                    } else { // não cresceu
                        // falta algo?
                        return root;
                    }
                } else { // é 3-nó e está vindo pela direita
                    Node* p = put23(root->p3, key, val, cresceu);
                    if (cresceu) {
                        // p vai entrar no lugar de newRight
                        // esquerda fica na esquerda
                        // antiga direita vai subir
                        Node* newRoot = new Node(root->key2, root->val2);
                        newRoot->p2 = p;
                        newRoot->p1 = root;
                        root->p3 = nullptr;
                        root->eh2no = true;
                        return newRoot;
                    } else {
                        return root;
                    }
                }
            }
        }

        Item searchRecursive(Node* root, Key key) {
            if (key == root->key1)
                return root->val1;
            if (key == root->key2)
                return root->val2;
            if (root->eh2no) {
                if (key < root->key1) { // procura pela esquerda
                    return searchRecursive(root->p1, key);
                } else { // procura pela direita
                    return searchRecursive(root->p2, key);
                }
            } else {
                if (key < root->key1) { // procura pela esquerda
                    return searchRecursive(root->p1, key);
                } else if (key > root->key2) { // procura pela direita
                    return searchRecursive(root->p3, key);
                } else { // procura pelo meio
                    return searchRecursive(root->p2, key);
                }
            }
        }

        void printRecursive(Node* node, int level) {
            int space = 3;
            if (node != nullptr) {
                if (node->eh2no) {
                    printRecursive(node->p3, level + space);
                    /*for (int i = 0; i < level; i++) {
                        std::cout << "   ";
                    }*/
                    std::cout << "K2:" << node->key2 << std::endl;
                    printRecursive(node->p2, level + space);
                    std::cout << "K1:" << node->key1 << std::endl;
                    printRecursive(node->p1, level + space);
                    /*for (int i = 0; i < level; i++) {
                        std::cout << "   ";
                    }*/
                } else {
                    printRecursive(node->p2, level + space);
                    /*for (int i = 0; i < level; i++) {
                        std::cout << "   ";
                    }*/
                    std::cout << "K1:" << node->key1 << std::endl;
                    printRecursive(node->p1, level + space);
                }
                /*
                for (int i = 0; i < level; i++) {
                    std::cout << "   ";
                }
                */
            }
        }

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