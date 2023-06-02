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
            Node() {
                left = nullptr;
                right = nullptr;
                pai = nullptr;
                isBlack = false;
            }
        };
        Node* root;
        Node* rotateRight(Node* node) {
            if (node != nullptr && node->left != nullptr) {
                Node* newNode = node->left;
                node->left = newNode->right;
                if (node->left != nullptr)
                    node->left->pai = node;
                newNode->right = node;
                newNode->pai = node->pai;
                node->pai = newNode;
                node = newNode;
            }
            return node;
        }
        Node* rotateLeft(Node* node) {
            if (node != nullptr && node->right != nullptr) {
                Node* newNode = node->right;
                node->right = newNode->left;
                if (node->right != nullptr)
                    node->right->pai = node;
                newNode->left = node;
                newNode->pai = node->pai;
                node->pai = newNode;
                node = newNode;
            }
            return node;
        }
        void printRecursive(Node* node, int level) {
            if (node != nullptr) {
                printRecursive(node->right, level + 1);
                for (int i = 0; i < level; i++) {
                    std::cout << "   ";
                }
                std::cout << node->val.toString() << (node->isBlack ? "(B)" : "(R)") << std::endl;
                printRecursive(node->left, level + 1);
            }
        }
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
                if (p->key > key && p->left == nullptr)
                    gotcha = true;
                else if (p->key > key)
                    p = p->left;
                else if (p->key < key && p->right == nullptr)
                    gotcha = true;
                else if (p->key < key)
                    p = p->right;
                else //p->key == key
                    gotcha = true;
            }
            if (p->key == key) {
                p->val.addOcorrencia();
                return root;
            }
            Node* novo = new Node(key, val);
            Node* pai = p;
            novo->pai = pai;

            if (key > pai->key) {
                pai->right = novo;
            }
            else {
                pai->left = novo;
            }

            while (1) {
                if (pai->isBlack) {
                    break;
                }
                if (pai->pai == nullptr) { // pai vermelho e não tem avÕ
                    pai->isBlack = true;
                    break;
                }
                Node* avo = pai->pai;
                Node* tio = new Node();

                if (avo->left == pai) {
                    tio = avo->right;
                } else {
                    tio = avo->left;
                }

                if (tio != nullptr && !(tio->isBlack)) {
                    tio->isBlack = !tio->isBlack;
                    avo->isBlack = !avo->isBlack;
                    pai->isBlack = !pai->isBlack;
                    p = avo;
                    if (p->pai == nullptr)
                        break;
                    pai = p->pai;
                    novo = p;
                } else { // tio não existe ou é preto
                    // p entra pela esquerda e o pai é filho esquerdo
                    if (pai->left == novo && avo->left == pai) {
                        Node* q = rotateRight(avo);
                        q->isBlack = true; // pinta o pai
                        q->right->isBlack = false; // pinta o ex-avo
                        if (q->pai != nullptr && q->pai->key > q->key) {
                            q->pai->left = q;
                            break;
                        } else if (q->pai != nullptr && q->pai->key < q->key) {
                            q->pai->right = q;
                            break;
                        } else {
                            return q;
                        }
                    }
                    // p entra pela direita e o pai é filho direito
                    if (pai->right == novo && avo->right == pai) {
                        Node* q = rotateLeft(avo);
                        q->isBlack = true; // pinta o pai
                        q->left->isBlack = false; // pinta o ex-avo
                        if (q->pai != nullptr && q->pai->key > q->key) {
                            q->pai->left = q;
                            break;
                        } else if (q->pai != nullptr && q->pai->key < q->key) {
                            q->pai->right = q;
                            break;
                        } else {
                            return q;
                        }
                    }
                    // p entra pela direita e o pai é filho esquerdo
                    if (pai->right == novo && avo->left == pai) {
                        avo->left = rotateLeft(pai);
                        Node* q = rotateRight(avo);
                        q->isBlack = true; // pinta o pai
                        q->right->isBlack = false; // pinta o ex-avo
                        if (q->pai != nullptr && q->pai->key > q->key) {
                            q->pai->left = q;
                            break;
                        } else if (q->pai != nullptr && q->pai->key < q->key) {
                            q->pai->right = q;
                            break;
                        } else {
                            return q;
                        }
                    }
                    // p entra pela esquerda e o pai é filho direito
                    if (pai->left == novo && avo->right == pai) {
                        avo->right = rotateRight(pai);
                        Node* q = rotateLeft(avo);
                        q->isBlack = true;
                        q->left->isBlack = false;
                        if (q->pai != nullptr && q->pai->key > q->key) {
                            q->pai->left = q;
                            break;
                        } else if (q->pai != nullptr && q->pai->key < q->key) {
                            q->pai->right = q;
                            break;
                        } else {
                            return q;
                        }
                    }
                }
            }
            return root;
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
    root = putRB(root, key, val);
}

template<class Key, class Item>
void RBTree<Key, Item>::print() {
    printRecursive(root, 0);
}