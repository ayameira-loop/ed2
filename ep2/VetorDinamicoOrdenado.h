#ifndef VDO_H
#define VDO_H
#include <string>

template<class Key, class Item>
class VetorDinamicoOrdenado {
private:
    int tam;
    int cap;
    Key* keys;
    Item* values;

public:
    VetorDinamicoOrdenado();
    ~VetorDinamicoOrdenado();
    int size();
    void add(Key key, Item val);
    Item value(Key key);
    void show();
};

template<class Key, class Item>
void VetorDinamicoOrdenado<Key, Item>::show() {
    for (size_t i = 0; i < tam; i++)
    {
        std::cout << i << " - " << " { " << keys[i] << ", " << values[i].toString() << " }" << std::endl;
    }
    
}

template<class Key, class Item>
VetorDinamicoOrdenado<Key, Item>::VetorDinamicoOrdenado() {
    tam = 0;
    cap = 2;
    keys = new Key[cap];
    values = new Item[cap];
}

template<class Key, class Item>
VetorDinamicoOrdenado<Key, Item>::~VetorDinamicoOrdenado() {
    delete[] keys;
    delete[] values;
}

template<class Key, class Item>
int VetorDinamicoOrdenado<Key, Item>::size() {
    return tam;
}

template<class Key, class Item>
void VetorDinamicoOrdenado<Key, Item>::add(Key key, Item val) {
    if (tam == cap) {
        Key* newKeys = new Key[cap*2];
        Item* newVals = new Item[cap*2];
        for (size_t i = 0; i < cap; i++)
        {
            newKeys[i] = keys[i];
            newVals[i] = values[i];
        }
        delete[] values;
        delete[] keys;
        values = newVals;
        keys = newKeys;
        cap *= 2;
    }
    // bin search
    int l = 0;
    int r = tam;
    int mid = (l+r)/2;
    bool achou = false;
    while (l <= r && achou == false) {
        if (r == 0)
            break;
        mid = (l+r)/2;
        if (keys[mid] == key)
            achou = true;
        if (keys[mid] < key)
            l = mid + 1;
        else
            r = mid - 1;
    }
    if (achou == false) {
        // escorrega o resto do array para a direita
        for (int i = tam-1; i >= mid; i--) {
            keys[i+1] = keys[i]; 
            values[i+1] = values[i]; 
        }
        tam++;
    }
    keys[mid] = key;
    values[mid] = val;
}

template<class Key, class Item>
Item VetorDinamicoOrdenado<Key, Item>::value(Key key) {
    int l = 0;
    int r = tam;
    int mid = (l+r)/2;
    bool achou = false;
    while (l <= r && achou == false) {
        if (r == 0)
            break;
        mid = (l+r)/2;
        if (keys[mid] == key)
            achou = true;
        if (keys[mid] < key)
            l = mid + 1;
        else
            r = mid - 1;
    }
    if (achou == false)
        throw "Key não encontrada";
    return values[mid];
}

#endif