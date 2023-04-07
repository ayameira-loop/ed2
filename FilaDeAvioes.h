#include "LinkedList.h"
#include "Aviao.h"

class FilaDeAvioes : public LinkedList<Aviao> {
    public:
        void insertEmergency(Aviao* aviao);
};

void FilaDeAvioes::insertEmergency(Aviao* aviao) {
    Node* newNode = new Node();
    newNode->value = aviao;
    newNode->next = nullptr;
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    n++;
}