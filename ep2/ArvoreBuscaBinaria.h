

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
            if (root == nullptr)
            {
                Node *p = new Node(key, val);
                return p;
            }
            if (key < root->key)
            {
                root->left = addRecursive(root->left, key, val);
                return root;
            }
            if (key > root->key)
            {
                root->right = addRecursive(root->right, key, val);
                return root;
            }
            if (key == root->key)
            {
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
            else
            {
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