#ifndef BST_HPP
#define BST_HPP

/**
 * @brief A standard Binary Search Tree for ordered seating chart views.
 * @tparam K Key type (e.g., GlobalSeatNumber)
 * @tparam V Value type (e.g., Seat*)
 */
template<typename K, typename V>
class BST
{
private:
    struct Node
    {
        K key;
        V value;
        Node* left;
        Node* right;

        Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper methods for recursive operations
    Node* insert(Node* node, K key, V value);
    Node* remove(Node* node, K key);
    Node* find(Node* node, K key) const;
    void clear(Node* node);
    void inOrder(Node* node, void (*callback)(K, V)) const;

public:
    BST();
    ~BST();

    /**
     * @brief Insert a key-value pair into the tree.
     */
    void insert(K key, V value);

    /**
     * @brief Remove a node by its key.
     */
    void remove(K key);

    /**
     * @brief Search for a value associated with a key.
     */
    V search(K key) const;

    /**
     * @brief Perform an in-order traversal (Left, Root, Right).
     */
    void traverseInOrder(void (*callback)(K, V)) const;

    /**
     * @brief Clear all nodes from the tree.
     */
    void clear();

    /**
     * @brief Check if the tree is empty.
     */
    bool isEmpty() const;
};

#endif // BST_HPP
