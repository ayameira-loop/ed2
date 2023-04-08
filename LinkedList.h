#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class Item>
class LinkedList {
private:
    struct Node {
        Item* value;
        Node* next;
    };

    Node* head;
    Node* tail;
    int n;

public:
    LinkedList();
    ~LinkedList();
    void enqueue(Item* item);
    Item* dequeue();
    void insert(int index, Item* item);
    void moveTo(int idx_moved, int idx_destination);
    void insertEmergency(Item* item);
    Item* remove(int index);
    bool isEmpty();
    int size();
    Item* at(int index);
    Item* backOfTheLine();
    Item* frontOfTheLine();
};

template<class Item>
LinkedList<Item>::LinkedList() {
    n = 0;
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
void LinkedList<Item>::enqueue(Item* item) {
    Node* newNode = new Node();
    newNode->value = item;
    newNode->next = head;
    head = newNode;
    n++;
}

template<class Item>
Item* LinkedList<Item>::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    Node* temp = head;
    Node* prev = nullptr;
    while (temp->next != nullptr) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == nullptr) {
        head = nullptr;
    } else {
        prev->next = nullptr;
    }
    Item* item = temp->value;
    delete temp;
    n--;
    return item;
}

template<class Item>
void LinkedList<Item>::insert(int index, Item* item) {
    if (index < 0 || index >= n) {
        throw std::out_of_range("Index out of range (insert)");
    }
    Node* newNode = new Node();
    newNode->value = item;

    if (index == 0) {
        enqueue(item);
        return;
    }

    Node* temp = head;
    for (int i = 0; i < index-1; i++) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    n++;
}

template<class Item>
Item* LinkedList<Item>::remove(int index) {
    if (index < 0 || index >= n) {
        throw std::out_of_range("Index out of range (remove)");
    }

    Node* temp = head;
    if (index == 0) {
        Node* aux = head;
        Item* item = aux->value;
        head = head->next;
        delete aux;
        n--;
        return item;
    }
    for (int i = 0; i < index-1; i++) {
        temp = temp->next;
    }
    Node* aux = temp->next;
    temp->next = aux->next;
    Item* item = aux->value;
    delete aux;
    n--;
    return item;
}

template<class Item>
bool LinkedList<Item>::isEmpty() {
    return n == 0;
}

template<class Item>
int LinkedList<Item>::size() {
    return n;
}

template<class Item>
Item* LinkedList<Item>::at(int index) {
    if (index < 0 || index >= n) {
        throw std::out_of_range("Index out of range (at)");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

template<class Item>
Item* LinkedList<Item>::backOfTheLine() {
    return head->value;
}

template<class Item>
Item* LinkedList<Item>::frontOfTheLine() {
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return temp->value;
}

template<class Item>
void LinkedList<Item>::insertEmergency(Item* item) {
    Node* newNode = new Node();
    newNode->value = item;
    newNode->next = nullptr;
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    n++;
}
template<class Item>
void LinkedList<Item>::moveTo(int idx_moved, int idx_destination) {
    Item* item = remove(idx_moved); // n--;
    if (idx_destination == size()) // se for do tamanho, coloca no topo
        insertEmergency(item);
    else
        insert(idx_destination, item);
}

#endif

