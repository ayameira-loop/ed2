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
    int binarySearch(std::string a[], std::string item, int low, int high, bool& achou) {
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (item == a[mid]) {
                achou = true;
                return mid + 1;
            }
            else if (item > a[mid])
                low = mid + 1;
            else
                high = mid - 1;
        }
        return low;
    }

public:
    VetorDinamicoOrdenado();
    ~VetorDinamicoOrdenado();
    int size();
    void add(Key key, Item val);
    Item value(Key key);
    void mostFrequent();
    int getFrequency(std::string palavra);
    void longest();
    void print();
};

template<class Key, class Item>
void VetorDinamicoOrdenado<Key, Item>::print() {
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
    bool achou = false;
    int result = binarySearch(keys, key, 0, tam-1, achou);

    if (achou == false) {
        // escorrega o resto do array para a direita
        for (int i = tam-1; i >= result; i--) {
            keys[i+1] = keys[i]; 
            values[i+1] = values[i]; 
        }
        tam++;
        keys[result] = key;
        values[result] = val;
    } else {
        // se não, só incrementa uma ocorrecia
        values[result-1].addOcorrencia();
    }
}

template<class Key, class Item>
Item VetorDinamicoOrdenado<Key, Item>::value(Key key) {
    bool achou = false;
    int result = binarySearch(keys, key, 0, tam-1, achou);
    if (achou == false) {
        std::cout << "não achou a chave " << key  << std::endl;
        throw "Key não encontrada";
    }
    return values[result-1];
}

// quais as palavras mais frequentes no texto (F);
template<class Key, class Item>
void VetorDinamicoOrdenado<Key, Item>::mostFrequent() {
    int highestF = 1;
    int tamHighest = 0;
    std::string* highest = new std::string[tam];
    for (size_t i = 0; i < tam; i++) {
        if (values[i].getOcorrencias() > highestF) {
            highestF = values[i].getOcorrencias();
            highest[0] = keys[i];
            tamHighest = 1;
        } else if (values[i].getOcorrencias() == highestF) {
            highest[tamHighest] = keys[i];
            tamHighest++;
        }
    }
    for (size_t i = 0; i < tamHighest; i++) {
        std::cout << highest[i] << std::endl;
    }
    
}

// dada uma palavra, quantas vezes ocorre no texto (O “palavra”);
template<class Key, class Item>
int VetorDinamicoOrdenado<Key, Item>::getFrequency(std::string palavra) {
    return value(palavra).getOcorrencias();
}

// quais as palavras mais longas (L);
template<class Key, class Item>
void VetorDinamicoOrdenado<Key, Item>::longest() {
    int longestF = 1;
    int tamLongest = 0;
    std::string* longest = new std::string[tam];
    for (size_t i = 0; i < tam; i++)
    {
        if (values[i].getNumLetras() > longestF) {
            longestF = values[i].getNumLetras();
            longest[0] = keys[i];
            tamLongest = 1;
        } else if (values[i].getNumLetras() == longestF) {
            longest[tamLongest] = keys[i];
            tamLongest++;
        }
    }
    for (size_t i = 0; i < tamLongest; i++)
    {
        std::cout << longest[i] << std::endl;
    }
    
}

// quais as maiores palavras que n ̃ao repetem letras (SR)
// quais as menores palavras com mais vogais sem repeti ̧c ̃ao (VD)



#endif