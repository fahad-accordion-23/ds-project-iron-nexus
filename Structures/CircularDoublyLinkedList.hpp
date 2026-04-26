#ifndef CIRCULAR_DOUBLY_LINKED_LIST_HPP
#define CIRCULAR_DOUBLY_LINKED_LIST_HPP

/**
 * @brief A custom Circular Doubly Linked List implementation for Coach management.
 * @tparam T The type of data stored in the nodes.
 */
template<typename T>
class CircularDoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    int count;

public:
    CircularDoublyLinkedList();
    ~CircularDoublyLinkedList();

    /**
     * @brief Add an element to the front of the list.
     */
    void addFront(const T& value);

    /**
     * @brief Add an element to the end of the list.
     */
    void addEnd(const T& value);

    /**
     * @brief Insert an element at a specific 0-based index.
     */
    void insertAt(const T& value, int index);

    /**
     * @brief Remove an element at a specific index.
     */
    void removeAt(int index);

    /**
     * @brief Find an element based on a predicate.
     */
    T find(bool (*predicate)(const T&)) const;

    /**
     * @brief Reverse the entire list by swapping next/prev pointers.
     */
    void reverse();

    /**
     * @brief Get the current number of elements.
     */
    int size() const;

    /**
     * @brief Check if the list is empty.
     */
    bool isEmpty() const;
};

#endif // CIRCULAR_DOUBLY_LINKED_LIST_HPP
