#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

/**
 * @brief A custom Hash Table for O(1) seat lookups.
 * @tparam K Key type
 * @tparam V Value type
 */
template<typename K, typename V>
class HashTable
{
private:
    struct Entry
    {
        K key;
        V value;
        Entry* next; // For separate chaining

        Entry(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    Entry** table;
    int capacity;
    int size;

    /**
     * @brief Simple hash function for keys.
     */
    int hash(K key) const;

public:
    /**
     * @brief Construct a new Hash Table.
     * @param initialCapacity Starting size of the table.
     */
    HashTable(int initialCapacity = 101);
    ~HashTable();

    /**
     * @brief Insert or update a key-value pair.
     */
    void insert(K key, V value);

    /**
     * @brief Remove an entry by its key.
     */
    void remove(K key);

    /**
     * @brief Retrieve a value by its key.
     */
    V search(K key) const;

    /**
     * @brief Resize the table when load factor is exceeded.
     */
    void rehash();

    int getSize() const;
    bool isEmpty() const;
};

#endif // HASH_TABLE_HPP
