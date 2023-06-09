

template<class Key, class Item>
class ArvoreBuscaBinaria {
    private:
        class Node {
        public:
            Key key;
            Item val;
            Node* left;
            Node* right;
            Node(Key key, Item val) {
                this->key = key;
                this->val = val;
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
        Node* addRecursive(Node* root, Key key, Item val) {
            if (root == nullptr) {
                Node *p = new Node(key, val);
                return p;
            }
            if (key < root->key) {
                root->left = addRecursive(root->left, key, val);
                return root;
            } else if (key > root->key) {
                root->right = addRecursive(root->right, key, val);
                return root;
            } else { // (key == root->key)
                root->val.addOcorrencia();
                return root;
            }
        }

        void printRecursive(Node* node, int level) {
            if (node != nullptr) {
                printRecursive(node->right, level + 1);
                for (int i = 0; i < level; i++) {
                    std::cout << "   ";
                }
                std::cout << node->val.toString() << std::endl;
                printRecursive(node->left, level + 1);
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
        ArvoreBuscaBinaria();
        ~ArvoreBuscaBinaria();
        void add(Key key, Item val);
        void print();
        Item value(Key key);
};

template<class Key, class Item>
Item ArvoreBuscaBinaria<Key, Item>::value(Key key) {
    return searchRecursive(root, key);
}

template<class Key, class Item>
ArvoreBuscaBinaria<Key, Item>::ArvoreBuscaBinaria() {
    root = nullptr;
}

template<class Key, class Item>
ArvoreBuscaBinaria<Key, Item>::~ArvoreBuscaBinaria() {
    if (root != nullptr) {
        destroyTree(root);
    }
}

template<class Key, class Item>
void ArvoreBuscaBinaria<Key, Item>::add(Key key, Item val) {
    root = addRecursive(root, key, val);
}

template<class Key, class Item>
void ArvoreBuscaBinaria<Key, Item>::print() {
    printRecursive(root, 0);
}