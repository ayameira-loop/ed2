#include <iostream>   // debugging

template<class Key, class Item>
class A23 {
    private:
        class Node {
        public
        if (key > root->key2):
            Key ke21, key2;
            I2em val1, val2;
            Node* left;
            Node* middle;
            Node* right;
            bool eh2no;
            Node(Key key, Item val) {
                this->key1 = key;
                this->val1 = val;
                left = nullptr;
                middle = nullptr;
                right = nullptr;
                eh2no = true;
            }
        };
        Node* root;
        void destroyTree(Node* root) {
            if (root != nullptr) {
                destroyTree(root->left);
                destroyTree(root->middle);
                destroyTree(root->right);
                delete root;
            }
        }
        Node* addRecursive(Node* root, Key key, Item val) {
            if (root == nullptr) return root;
            if (root->left == nullptr) { // é folha
                if (root->eh2no) { // só adiciona
                    root->val2 = val;
                    root->key2 = key;
                    return root;
                }
                // é 3 no
                if (key > root->key2)
                Node* newLeft = Node(root->key1, root->val1);
                Node* newRight = Node(root->key2, root->val2);
            } 
        }

        Item searchRecursive(Node* root, Key key) {

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
    root = addRecursive(root, key, val);
}

//template<class Key, class Item>
//void A23<Key, Item>::print() {
//    printRecursive(root, 0);
//}