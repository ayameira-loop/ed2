template<class Item>
class LinkedList {
private:
    struct Node {
        Item* value;
        Node* next;
    };

    Node* head;
    int count;

public:
    LinkedList();
    ~LinkedList();
    void add(Item* item);
    bool isEmpty();
    int size();
    Item* at(int index);
};

template<class Item>
LinkedList<Item>::LinkedList() {
    count = 0;
    head = nullptr;
}

template<class Item>
LinkedList<Item>::~LinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<class Item>
void LinkedList<Item>::add(Item* item) {
    Node* newNode = new Node();
    newNode->value = item;
    newNode->next = head;
    head = newNode;
    count++;
}

template<class Item>
bool LinkedList<Item>::isEmpty() {
    return count == 0;
}

template<class Item>
int LinkedList<Item>::size() {
    return count;
}

template<class Item>
Item* LinkedList<Item>::at(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}