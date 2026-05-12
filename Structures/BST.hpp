#ifndef BST_HPP
#define BST_HPP

#include <stdexcept>

/**
 * @brief A standard Binary Search Tree for ordered seating chart views.
 * @tparam K Key type (e.g., GlobalSeatNumber)
 * @tparam V Value type (e.g., Seat*)
 */
template <typename K, typename V>
class BST
{
private:
    struct Node
    {
        K key;
        V value;
        Node* left;
        Node* right;

        Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr)
        {
        }
    };

    Node* root;

    // Helper methods for recursive operations
    Node* insert(Node* node, K key, V value);
    Node* remove(Node* node, K key);
    Node* find(Node* node, K key) const;
    void clear(Node* node);

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
     * Accepts any callable: lambda, functor, or function pointer.
     */
    template <typename Func>
    void traverseInOrder(Func callback) const;

    /**
     * @brief Clear all nodes from the tree.
     */
    void clear();

    /**
     * @brief Check if the tree is empty.
     */
    bool isEmpty() const;
};

template <typename K, typename V>
BST<K, V>::BST() : root(nullptr)
{
}

template <typename K, typename V>
BST<K, V>::~BST()
{
    clear();
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::insert(Node* node, K key, V value)
{
    if (node == nullptr)
    {
        return new Node(key, value);
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key, value);
    }
    else
    {
        node->value = value;  // Update value if key exists
    }
    return node;
}

template <typename K, typename V>
void BST<K, V>::insert(K key, V value)
{
    root = insert(root, key, value);
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::remove(Node* node, K key)
{
    if (node == nullptr) return nullptr;

    if (key < node->key)
    {
        node->left = remove(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = remove(node->right, key);
    }
    else
    {
        // Node to be deleted found
        if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: Get inorder successor
        Node* temp = node->right;
        while (temp && temp->left != nullptr)
        {
            temp = temp->left;
        }
        node->key = temp->key;
        node->value = temp->value;
        node->right = remove(node->right, temp->key);
    }
    return node;
}

template <typename K, typename V>
void BST<K, V>::remove(K key)
{
    root = remove(root, key);
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::find(Node* node, K key) const
{
    if (node == nullptr || node->key == key)
    {
        return node;
    }
    if (node->key < key)
    {
        return find(node->right, key);
    }
    return find(node->left, key);
}

template <typename K, typename V>
V BST<K, V>::search(K key) const
{
    Node* result = find(root, key);
    if (result == nullptr)
    {
        throw std::runtime_error("Key not found in BST");
    }
    return result->value;
}

template <typename K, typename V>
template <typename Func>
void BST<K, V>::traverseInOrder(Func callback) const
{
    // Lambda for recursive in-order traversal
    struct InOrder
    {
        static void traverse(Node* node, Func& cb)
        {
            if (node != nullptr)
            {
                traverse(node->left, cb);
                cb(node->key, node->value);
                traverse(node->right, cb);
            }
        }
    };
    InOrder::traverse(root, callback);
}

template <typename K, typename V>
void BST<K, V>::clear(Node* node)
{
    if (node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename K, typename V>
void BST<K, V>::clear()
{
    clear(root);
    root = nullptr;
}

template <typename K, typename V>
bool BST<K, V>::isEmpty() const
{
    return root == nullptr;
}

#endif  // BST_HPP
