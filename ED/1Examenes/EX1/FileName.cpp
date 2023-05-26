/*
 * Implementa las operaciones pedidas en el ejercicio al final de
 * este fichero, entre las etiquetas.
 */


#include <iostream>
#include <fstream>
#include <cassert>

 /* --------------------------------------------------------------------
  * Clase ListLinkedSingle
  * --------------------------------------------------------------------
  * Implementa el TAD lista mediante una lista enlazada simple con
  * nodo fantasma y punteros al primer y �ltimo elemento.
  * --------------------------------------------------------------------
  */

template<typename T>
class ListLinkedSingle {
private:
    struct Node {
        T value;
        Node* next;
    };

public:
    ListLinkedSingle() : num_elems(0) {
        head = new Node;
        head->next = nullptr;
        last = head;
    }

    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)), num_elems(other.num_elems) {
        last = last_node();
    }

    void push_front(const T& elem) {
        Node* new_node = new Node{ elem, head->next };
        if (head->next == nullptr) { last = new_node; }
        head->next = new_node;
        num_elems++;
    }

    void push_back(const T& elem);

    void pop_front() {
        assert(num_elems > 0);
        Node* old_head = head->next;
        head->next = head->next->next;
        if (head->next == nullptr) { last = head; }
        delete old_head;
        num_elems--;
    }

    void pop_back();

    int size() const {
        return num_elems;
    }

    bool empty() const {
        return num_elems == 0;
    };

    const T& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    T& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const T& back() const {
        return last->value;
    }

    T& back() {
        return last->value;
    }

    const T& operator[](int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    T& operator[](int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    ListLinkedSingle& operator=(const ListLinkedSingle& other) {
        if (this != &other) {
            delete_list(head);
            head = copy_nodes(other.head);
            last = last_node();
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const {
        display(std::cout);
    }

    void replace(int pos_begin, int pos_end, ListLinkedSingle& other);

private:
    Node* head;
    Node* last;
    int num_elems;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

template<typename T>
typename ListLinkedSingle<T>::Node* ListLinkedSingle<T>::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

template<typename T>
void ListLinkedSingle<T>::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

template<typename T>
void ListLinkedSingle<T>::push_back(const T& elem) {
    Node* new_node = new Node{ elem, nullptr };
    last->next = new_node;
    last = new_node;
    num_elems++;
}

template<typename T>
void ListLinkedSingle<T>::pop_back() {
    assert(num_elems > 0);
    Node* previous = head;
    Node* current = head->next;

    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    delete current;
    previous->next = nullptr;
    last = previous;
    num_elems--;
}

template<typename T>
typename ListLinkedSingle<T>::Node* ListLinkedSingle<T>::last_node() const {
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

template<typename T>
typename ListLinkedSingle<T>::Node* ListLinkedSingle<T>::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

template<typename T>
void ListLinkedSingle<T>::display(std::ostream& out) const {
    out << "[";
    if (head->next != nullptr) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}


template<typename T>
std::ostream& operator<<(std::ostream& out, const ListLinkedSingle<T>& l) {
    l.display(out);
    return out;
}

/* --------------------------------------------------------------------
 * Implementa el m�todo pedido aqu�
 * --------------------------------------------------------------------
 *
 * Puedes a�adir los m�todos privados auxiliares que quieras. Para eso
 * puedes declararlos en la clase, pero has de implementarlos aqu�, entre
 * las etiquetas <answer> y </answer>.
 *
 *@ <answer>
 */


template <typename T>
void ListLinkedSingle<T>::replace(int pos_begin, int pos_end, ListLinkedSingle& other) {
    // Implementar
  

    Node* beg = this->nth_node(pos_begin);
    Node* end = this->nth_node(pos_end - 1);

   // std::cout << *this << std::endl;

   

        if (pos_begin == 0)
            head->next = other.head->next;
        else
            nth_node(pos_begin - 1)->next = other.head->next;

        if (pos_end == this->size() - 1)
            this->last = other.last;
        else
            other.last->next = end->next;
    

    

    other.head->next = beg;
    other.last = end;
    other.last->next = nullptr;


    num_elems = num_elems + other.num_elems - (pos_end - pos_begin);
    other.num_elems = pos_end - pos_begin;

}

/*@ </answer> */

using namespace std;

// Funci�n para tratar cada uno de los casos de prueba
void tratar_caso() {
    int n1, n2, ini, fin;
    cin >> n1 >> n2 >> ini >> fin;

    ListLinkedSingle<int> l1, l2;

    for (int i = 0; i < n1; i++) {
        int elem;
        cin >> elem;
        l1.push_back(elem);
    }

    for (int i = 0; i < n2; i++) {
        int elem;
        cin >> elem;
        l2.push_back(elem);
    }

    l1.replace(ini, fin, l2);

    cout << l1 << endl << l2 << endl;
}



int main() {
    int num_casos;
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    std::cin >> num_casos;

    while (num_casos > 0) {
        tratar_caso();
        num_casos--;
    }


#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Comentar si no se trabaja en Visual Studio
    system("PAUSE");
#endif

    return 0;
}

// SALT: ##