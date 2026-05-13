#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <stdexcept>

template <typename K, typename V>
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

        Node(K k, V v) : key(k), value(v), height(1), left(nullptr), right(nullptr)
        {
        }
    };

    Node* root;

    int getHeight(Node* n) const;
    int getBalanceFactor(Node* n) const;
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* n);

    Node* insert(Node* node, K key, V value);
    Node* remove(Node* node, K key);
    Node* find(Node* node, K key) const;

public:
    AVLTree();
    ~AVLTree();

    void insert(K key, V value);
    void remove(K key);
    V search(K key) const;

    template <typename Func>
    void traverseInOrder(Func callback) const;

    bool isEmpty() const;
    void clear();

private:
    void clear(Node* node);
};

template <typename K, typename V>
AVLTree<K, V>::AVLTree() : root(nullptr)
{
}

template <typename K, typename V>
AVLTree<K, V>::~AVLTree()
{
    clear();
}

template <typename K, typename V>
int AVLTree<K, V>::getHeight(Node* n) const
{
    return n == nullptr ? 0 : n->height;
}

template <typename K, typename V>
int AVLTree<K, V>::getBalanceFactor(Node* n) const
{
    return n == nullptr ? 0 : getHeight(n->left) - getHeight(n->right);
}

template <typename K, typename V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    int yLeftHeight = getHeight(y->left);
    int yRightHeight = getHeight(y->right);
    y->height = (yLeftHeight > yRightHeight ? yLeftHeight : yRightHeight) + 1;

    int xLeftHeight = getHeight(x->left);
    int xRightHeight = getHeight(x->right);
    x->height = (xLeftHeight > xRightHeight ? xLeftHeight : xRightHeight) + 1;

    return x;
}

template <typename K, typename V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    int xLeftHeight = getHeight(x->left);
    int xRightHeight = getHeight(x->right);
    x->height = (xLeftHeight > xRightHeight ? xLeftHeight : xRightHeight) + 1;

    int yLeftHeight = getHeight(y->left);
    int yRightHeight = getHeight(y->right);
    y->height = (yLeftHeight > yRightHeight ? yLeftHeight : yRightHeight) + 1;

    return y;
}

template <typename K, typename V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::balance(Node* n)
{
    if (n == nullptr) return nullptr;

    int leftHeight = getHeight(n->left);
    int rightHeight = getHeight(n->right);
    n->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);

    int balanceFactor = getBalanceFactor(n);

    if (balanceFactor > 1 && getBalanceFactor(n->left) >= 0) return rotateRight(n);

    if (balanceFactor > 1 && getBalanceFactor(n->left) < 0)
    {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    if (balanceFactor < -1 && getBalanceFactor(n->right) <= 0) return rotateLeft(n);

    if (balanceFactor < -1 && getBalanceFactor(n->right) > 0)
    {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    return n;
}

template <typename K, typename V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::insert(Node* node, K key, V value)
{
    if (node == nullptr) return new Node(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else
    {
        node->value = value;
        return node;
    }

    return balance(node);
}

template <typename K, typename V>
void AVLTree<K, V>::insert(K key, V value)
{
    root = insert(root, key, value);
}

template <typename K, typename V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::remove(Node* node, K key)
{
    if (node == nullptr) return nullptr;

    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else
    {
        if ((node->left == nullptr) || (node->right == nullptr))
        {
            Node* child = node->left ? node->left : node->right;

            if (child == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else
            {
                node->key = child->key;
                node->value = child->value;
                node->left = child->left;
                node->right = child->right;
                node->height = child->height;
                delete child;
            }
        }
        else
        {
            Node* temp = node->right;
            while (temp->left != nullptr) temp = temp->left;

            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
    }

    if (node == nullptr) return nullptr;

    return balance(node);
}

template <typename K, typename V>
void AVLTree<K, V>::remove(K key)
{
    root = remove(root, key);
}

template <typename K, typename V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::find(Node* node, K key) const
{
    if (node == nullptr || node->key == key) return node;

    if (node->key < key) return find(node->right, key);

    return find(node->left, key);
}

template <typename K, typename V>
V AVLTree<K, V>::search(K key) const
{
    Node* result = find(root, key);
    if (result == nullptr) throw std::runtime_error("Key not found in AVL Tree");
    return result->value;
}

template <typename K, typename V>
template <typename Func>
void AVLTree<K, V>::traverseInOrder(Func callback) const
{
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
void AVLTree<K, V>::clear(Node* node)
{
    if (node != nullptr)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename K, typename V>
void AVLTree<K, V>::clear()
{
    clear(root);
    root = nullptr;
}

template <typename K, typename V>
bool AVLTree<K, V>::isEmpty() const
{
    return root == nullptr;
}

#endif
