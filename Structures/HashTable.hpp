#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

template <typename K, typename V>
class HashTable
{
private:
    struct Entry
    {
        K key;
        V value;
        Entry* next;

        Entry(K k, V v) : key(k), value(v), next(nullptr)
        {
        }
    };

    Entry** table;
    int capacity;
    int size;

    int hash(K key) const;

public:
    HashTable(int initialCapacity = 101);
    ~HashTable();

    void insert(K key, V value);

    void remove(K key);

    V search(K key) const;

    void rehash();

    template <typename Func>
    void forEach(Func callback) const;

    int getSize() const;
    bool isEmpty() const;
    void clear();
};

#include <functional>
#include <stdexcept>

template <typename K, typename V>
HashTable<K, V>::HashTable(int initialCapacity) : capacity(initialCapacity), size(0)
{
    table = new Entry*[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        table[i] = nullptr;
    }
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    clear();
    delete[] table;
}

template <typename K, typename V>
int HashTable<K, V>::hash(K key) const
{
    size_t h = std::hash<K>{}(key);
    return static_cast<int>(h % static_cast<size_t>(capacity));
}

template <typename K, typename V>
void HashTable<K, V>::insert(K key, V value)
{
    if (size * 4 >= capacity * 3)
    {
        rehash();
    }

    int index = hash(key);
    Entry* current = table[index];

    while (current != nullptr)
    {
        if (current->key == key)
        {
            current->value = value;
            return;
        }
        current = current->next;
    }

    Entry* newEntry = new Entry(key, value);
    newEntry->next = table[index];
    table[index] = newEntry;
    size++;
}

template <typename K, typename V>
void HashTable<K, V>::remove(K key)
{
    int index = hash(key);
    Entry* current = table[index];
    Entry* prev = nullptr;

    while (current != nullptr)
    {
        if (current->key == key)
        {
            if (prev == nullptr)
            {
                table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current;
            size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

template <typename K, typename V>
V HashTable<K, V>::search(K key) const
{
    int index = hash(key);
    Entry* current = table[index];

    while (current != nullptr)
    {
        if (current->key == key)
        {
            return current->value;
        }
        current = current->next;
    }
    throw std::runtime_error("Key not found in Hash Table");
}

template <typename K, typename V>
void HashTable<K, V>::rehash()
{
    int oldCapacity = capacity;
    Entry** oldTable = table;

    capacity *= 2;
    table = new Entry*[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        table[i] = nullptr;
    }
    size = 0;

    for (int i = 0; i < oldCapacity; ++i)
    {
        Entry* current = oldTable[i];
        while (current != nullptr)
        {
            insert(current->key, current->value);
            Entry* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] oldTable;
}

template <typename K, typename V>
int HashTable<K, V>::getSize() const
{
    return size;
}

template <typename K, typename V>
template <typename Func>
void HashTable<K, V>::forEach(Func callback) const
{
    for (int i = 0; i < capacity; ++i)
    {
        Entry* current = table[i];
        while (current != nullptr)
        {
            callback(current->key, current->value);
            current = current->next;
        }
    }
}

template <typename K, typename V>
bool HashTable<K, V>::isEmpty() const
{
    return size == 0;
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
    for (int i = 0; i < capacity; ++i)
    {
        Entry* current = table[i];
        while (current != nullptr)
        {
            Entry* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
    size = 0;
}

#endif
