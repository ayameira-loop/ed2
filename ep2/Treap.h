#include <cstdlib> // rand() e srand()
#include <ctime>   // time()
#include <iostream>   // debugging

template<class Key, class Item>
class Treap {
    private:
        class Node {
        public:
            Key key;
            Item val;
            int priority;
            Node* left;
            Node* right;
            Node(Key key, Item val) {
                this->key = key;
                this->val = val;
                this->priority = rand();  // assign a random priority
                std::cout << val << " " << priority << "\n";
                left = nullptr;
                right = nullptr;
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
        Node* rotateRight(Node* node) {
            if (node != nullptr && node->left != nullptr) {
                Node* newNode = node->left;
                node->left = newNode->right;
                newNode->right = node;
                node = newNode;
            }
            return node;
        }
        Node* rotateLeft(Node* node) {
            if (node != nullptr && node->right != nullptr) {
                Node* newNode = node->right;
                node->right = newNode->left;
                newNode->left = node;
                node = newNode;
            }
            return node;
        }
        Node* addRecursive(Node* root, Key key, Item val) {
            if (root == nullptr) {
                Node *p = new Node(key, val);
                return p;
            }
            if (key < root->key) {
                root->left = addRecursive(root->left, key, val);
                if (root->left->priority < root->priority) {
                    root = rotateRight(root);
                }
                return root;
            }
            if (key > root->key) {
                root->right = addRecursive(root->right, key, val);
                if (root->right->priority < root->priority) {
                    root = rotateLeft(root);
                }
                return root;
            }
            if (key == root->key) {
                root->val = val;
                return root;
            }
        }


        void printRecursive(Node* root, int space) {
            // Base case
            if (root == NULL)
                return;
        
            // Increase distance between levels
            space += 5;
        
            // Process right child first
            printRecursive(root->right, space);
        
            // Print current node after space
            std::cout << std::endl;
            for (int i = 5; i < space; i++)
                std::cout << " ";
            std::cout << root->val << "\n";
        
            // Process left child
            printRecursive(root->left, space);
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
        Treap();
        ~Treap();
        void add(Key key, Item val);
        void print();
        Item value(Key key);
};


template<class Key, class Item>
Treap<Key, Item>::Treap() {
    root = nullptr;
}

template<class Key, class Item>
Treap<Key, Item>::~Treap() {
    if (root != nullptr) {
        destroyTree(root);
    }
}

template<class Key, class Item>
Item Treap<Key, Item>::value(Key key) {
    return searchRecursive(root, key);
}

template<class Key, class Item>
void Treap<Key, Item>::add(Key key, Item val) {
    root = addRecursive(root, key, val);
}



template<class Key, class Item>
void Treap<Key, Item>::print() {
    printRecursive(root, 0);
}