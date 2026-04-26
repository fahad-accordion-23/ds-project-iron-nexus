#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

/**
 * @brief A self-balancing AVL Tree for the high-capacity Train Registry.
 * @tparam K Key type (e.g., TrainID)
 * @tparam V Value type (e.g., Train*)
 */
template<typename K, typename V>
class AVLTree
{
private:
    struct Node
    {
        K key;
        V value;
        int height;
        Node* left;
        Node* right;

        Node(K k, V v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // AVL Internal balancing operations
    int getHeight(Node* n) const;
    int getBalanceFactor(Node* n) const;
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* n);

    Node* insert(Node* node, K key, V value);
    Node* remove(Node* node, K key);
    Node* find(Node* node, K key) const;
    void inOrder(Node* node, void (*callback)(K, V)) const;

public:
    AVLTree();
    ~AVLTree();

    void insert(K key, V value);
    void remove(K key);
    V search(K key) const;
    void traverseInOrder(void (*callback)(K, V)) const;
    
    bool isEmpty() const;
};

#endif // AVL_TREE_HPP
