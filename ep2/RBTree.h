#include <iostream>   // debugging

template<class Key, class Item>
class RBTree {
    private:
        class Node {
        public:
            Key key;
            Item val;
            Node* left;
            Node* right;
            Node* pai;
            bool isBlack;
            Node(Key key, Item val) {
                this->key = key;
                this->val = val;
                left = nullptr;
                right = nullptr;
                pai = nullptr;
                isBlack = false;
            }
        };
        Node* root;
        void destroyTree(Node* root) {
            if (root != nullptr) {
                destroyTree(root->left);
                destroyTree(root->right);
                delete root;
            }
        }
        Node* putRB(Node* root, Key key, Item val) {
            if (root == nullptr) { // arvore vazia
                Node* newRoot = new Node(key, val);
                return newRoot;
            }
            // procura o lugar certo para inserir
            Node* p = root;
            bool gotcha = false;
            while (!gotcha) {
                if (p->key > key && p->esq == nullptr)
                    gotcha = true;
                else if (p->key > key)
                    p = p->esq;
                else if (p->key < key && p->dir == nullptr)
                    gotcha = true;
                else if (p->key < key)
                    p = p->dir;
                else //p->key == key
                    gotcha = true
            }
            if (p->key == key) {
                p->val = val;
                return root;
            }
            Node* novo = new Node(key, val);
            Node* pai = p;
            p = novo;

            while (1) {
                if (pai->isBlack)
                    break;
                if (pai->pai == nullptr) { // pai vermelho e não tem avÕ
                    pai->isBlack = true;
                    break;
                }
                Node* avo = pai->pai;
                if (avo->left = pai)
                    Node* tio = avo->right;
                else
                    Node* tio = avo->left;
                if (tio != nullptr && !(tio->isBlack)) {
                    avo->isBlack = false;
                    pai->isBlack = true;
                    p = avo;
                    if (p->pai == nullptr)
                        break;
                    pai = p->pai;
                } else { // tio não existe ou é preto
                    // p entra pela esquerda e o pai é filho esquerdo
                    // p entra pela direita e o pai é filho direito
                    // p entra pela direita e o pai é filho esquerdo
                    // p entra pela esquerda e o pai é filho direito
                    if (pai->left == p && avo->right == pai) {
                        avo->right = rotateRight(pai);
                        Node* q = rotateLeft(avo);
                        avo->isBlack = false;
                        if (q->pai != nullptr && q->pai->key > q->key) {
                            q->pai->left = q;
                        }
                    }
                }
                return root;
            }
        }

        Item searchRecursive(Node* root, Key key) {
            if (root == nullptr)
                throw std::runtime_error("Key not found in tree.");
            if (key == root->key)
                return root->val;
            if (key < root->key) {
                return searchRecursive(root->left, key);
            }
            else {
                return searchRecursive(root->right, key);
            }

        }
        
    public:
        RBTree();
        ~RBTree();
        void add(Key key, Item val);
        void print();
        Item value(Key key);
};


template<class Key, class Item>
RBTree<Key, Item>::RBTree() {
    root = nullptr;
}

template<class Key, class Item>
RBTree<Key, Item>::~RBTree() {
    if (root != nullptr) {
        destroyTree(root);
    }
}

template<class Key, class Item>
Item RBTree<Key, Item>::value(Key key) {
    return searchRecursive(root, key);
}

template<class Key, class Item>
void RBTree<Key, Item>::add(Key key, Item val) {
    root = addRecursive(root, key, val);
}

template<class Key, class Item>
void RBTree<Key, Item>::print() {
    printRecursive(root, 0);
}