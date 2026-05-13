#ifndef CIRCULAR_DOUBLY_LINKED_LIST_HPP
#define CIRCULAR_DOUBLY_LINKED_LIST_HPP

#include <stdexcept>

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

private:
    Node* getNodeAt(int index) const
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;

        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }

        return current;
    }

public:
    CircularDoublyLinkedList();
    ~CircularDoublyLinkedList();

    void addFront(const T& value);
    void addEnd(const T& value);
    void insertAt(const T& value, int index);
    void removeAt(int index);

    template <typename Predicate>
    T find(Predicate predicate) const;

    template <typename Func>
    void forEach(Func callback) const;

    void reverse();

    int size() const;

    T& getAt(int index);
    const T& getAt(int index) const;

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
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
    }
    else
    {
        Node* tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;

        head = newNode;
    }

    ++count;
}

template <typename T>
void CircularDoublyLinkedList<T>::addEnd(const T& value)
{
    Node* newNode = new Node(value);

    if (isEmpty())
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
    }
    else
    {
        Node* tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;
    }

    ++count;
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
        return;
    }

    if (index == count)
    {
        addEnd(value);
        return;
    }

    Node* current = getNodeAt(index);
    Node* previous = current->prev;

    Node* newNode = new Node(value);

    newNode->next = current;
    newNode->prev = previous;

    previous->next = newNode;
    current->prev = newNode;

    ++count;
}

template <typename T>
void CircularDoublyLinkedList<T>::removeAt(int index)
{
    if (isEmpty() || index < 0 || index >= count)
    {
        throw std::out_of_range("Index out of range");
    }

    Node* target = getNodeAt(index);

    if (count == 1)
    {
        head = nullptr;
    }
    else
    {
        target->prev->next = target->next;
        target->next->prev = target->prev;

        if (target == head)
        {
            head = head->next;
        }
    }

    delete target;
    --count;
}

template <typename T>
template <typename Predicate>
T CircularDoublyLinkedList<T>::find(Predicate predicate) const
{
    if (isEmpty())
    {
        throw std::runtime_error("List is empty");
    }

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
    if (isEmpty())
    {
        return;
    }

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
    if (count <= 1)
    {
        return;
    }

    Node* current = head;

    do
    {
        Node* temp = current->next;

        current->next = current->prev;
        current->prev = temp;

        current = temp;

    } while (current != head);

    head = head->next;
}

template <typename T>
int CircularDoublyLinkedList<T>::size() const
{
    return count;
}

template <typename T>
T& CircularDoublyLinkedList<T>::getAt(int index)
{
    return getNodeAt(index)->data;
}

template <typename T>
const T& CircularDoublyLinkedList<T>::getAt(int index) const
{
    return getNodeAt(index)->data;
}

template <typename T>
bool CircularDoublyLinkedList<T>::isEmpty() const
{
    return count == 0;
}

template <typename T>
void CircularDoublyLinkedList<T>::clear()
{
    while (!isEmpty())
    {
        removeAt(0);
    }
}

#endif