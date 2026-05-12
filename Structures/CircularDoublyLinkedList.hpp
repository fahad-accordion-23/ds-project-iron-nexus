#ifndef CIRCULAR_DOUBLY_LINKED_LIST_HPP
#define CIRCULAR_DOUBLY_LINKED_LIST_HPP

#include <stdexcept>

/**
 * @brief A custom Circular Doubly Linked List implementation for Coach management.
 * @tparam T The type of data stored in the nodes.
 */
template <typename T>
class CircularDoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr)
        {
        }
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
     * Accepts any callable: lambda, functor, or function pointer.
     */
    template <typename Predicate>
    T find(Predicate predicate) const;

    /**
     * @brief Execute a callback for each element in the list.
     * Accepts any callable: lambda, functor, or function pointer.
     */
    template <typename Func>
    void forEach(Func callback) const;

    /**
     * @brief Reverse the entire list by swapping next/prev pointers.
     */
    void reverse();

    /**
     * @brief Get the current number of elements.
     */
    int size() const;

    /**
     * @brief Get element at specific index.
     */
    T& getAt(int index);
    const T& getAt(int index) const;

    /**
     * @brief Check if the list is empty.
     */
    bool isEmpty() const;
    void clear();
};

template <typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList() : head(nullptr), count(0)
{
}

template <typename T>
CircularDoublyLinkedList<T>::~CircularDoublyLinkedList()
{
    clear();
}

template <typename T>
void CircularDoublyLinkedList<T>::addFront(const T& value)
{
    Node* newNode = new Node(value);
    if (isEmpty())
    {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else
    {
        Node* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
    count++;
}

template <typename T>
void CircularDoublyLinkedList<T>::addEnd(const T& value)
{
    Node* newNode = new Node(value);
    if (isEmpty())
    {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else
    {
        Node* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
    }
    count++;
}

template <typename T>
void CircularDoublyLinkedList<T>::insertAt(const T& value, int index)
{
    if (index < 0 || index > count)
    {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0)
    {
        addFront(value);
    }
    else if (index == count)
    {
        addEnd(value);
    }
    else
    {
        Node* newNode = new Node(value);
        Node* current = head;
        for (int i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        Node* nextNode = current->next;

        newNode->prev = current;
        newNode->next = nextNode;
        current->next = newNode;
        nextNode->prev = newNode;
        count++;
    }
}

template <typename T>
void CircularDoublyLinkedList<T>::removeAt(int index)
{
    if (isEmpty() || index < 0 || index >= count)
    {
        throw std::out_of_range("Index out of range");
    }

    Node* target = head;
    if (count == 1)
    {
        head = nullptr;
    }
    else
    {
        for (int i = 0; i < index; ++i)
        {
            target = target->next;
        }
        target->prev->next = target->next;
        target->next->prev = target->prev;
        if (index == 0)
        {
            head = target->next;
        }
    }
    delete target;
    count--;
}

template <typename T>
template <typename Predicate>
T CircularDoublyLinkedList<T>::find(Predicate predicate) const
{
    if (isEmpty()) throw std::runtime_error("List is empty");

    Node* current = head;
    do
    {
        if (predicate(current->data))
        {
            return current->data;
        }
        current = current->next;
    } while (current != head);

    throw std::runtime_error("Element not found");
}

template <typename T>
template <typename Func>
void CircularDoublyLinkedList<T>::forEach(Func callback) const
{
    if (isEmpty()) return;

    Node* current = head;
    do
    {
        callback(current->data);
        current = current->next;
    } while (current != head);
}

template <typename T>
void CircularDoublyLinkedList<T>::reverse()
{
    if (isEmpty() || count == 1) return;

    Node* current = head;
    do
    {
        Node* temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;  // advance using original next
    } while (current != head);

    head = head->prev;  // After full traversal, the old tail (now new head) is head->prev
}

template <typename T>
int CircularDoublyLinkedList<T>::size() const
{
    return count;
}

template <typename T>
bool CircularDoublyLinkedList<T>::isEmpty() const
{
    return count == 0;
}

template <typename T>
T& CircularDoublyLinkedList<T>::getAt(int index)
{
    if (isEmpty() || index < 0 || index >= count)
    {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; ++i)
    {
        current = current->next;
    }
    return current->data;
}

template <typename T>
const T& CircularDoublyLinkedList<T>::getAt(int index) const
{
    if (isEmpty() || index < 0 || index >= count)
    {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; ++i)
    {
        current = current->next;
    }
    return current->data;
}

template <typename T>
void CircularDoublyLinkedList<T>::clear()
{
    while (!isEmpty())
    {
        removeAt(0);
    }
}

#endif  // CIRCULAR_DOUBLY_LINKED_LIST_HPP
