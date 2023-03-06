/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no se tendrá en cuenta para la corrección.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */


 //@ <answer>
 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1: Jorge Bravo
   Componente 2: Javier de la Cruz
 */
 //@ </answer>

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

// Implementación del TAD lista utilizando listas enlazadas simples.

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    // La función está declarada aquí, pero se implementa
    // más abajo
    void replicate(const ListLinkedSingle& ys);

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}


//@ <answer>
// ===========================================================
// Escribe tu solución por debajo de esta línea
// ===========================================================

// Implementa aquí la función pedida. No olvides indicar el coste.


void ListLinkedSingle::replicate(const ListLinkedSingle& ys) {
    Node *prev = nullptr, * curr = head, *curr_ys = ys.head;

    while (curr != nullptr) {
        if (curr_ys->value == 0) {
            // Eliminamos curr correspondiente a 0 en curr_y
            Node* aux = curr;
            if (prev != nullptr) {
                prev->next = curr->next;
            }
            else {
                head = curr->next;
            }
            curr = curr->next;
            delete aux;
        }
        else {
            // Repetimos el elemento tantas veces como sea el valor de curr_y
            for (int i = 1; i < curr_ys->value; i++) {
                Node* new_node = new Node();
                new_node->value = curr->value;
                new_node->next = curr->next;
                curr->next = new_node;
                curr = new_node;
            }
            prev = curr;
            curr = curr->next;
        }
        curr_ys = curr_ys->next;
    }

    //El coste es de O(n), donde n es la longitud de las listas, en cada iteracion se accede
    // al elemento una unica vez
}



void tratar_caso() {
    // Escribe aquí el código para tratar UN caso de prueba

    int N = 0;
    cin >> N;
    int aux = 0;
    ListLinkedSingle a;
    ListLinkedSingle b;

    for (int i = 0; i < N; i++) {

        cin >> aux;
        a.push_front(aux);
    }
    for (int i = 0; i < N; i++) {

        cin >> aux;
        b.push_front(aux);
    }

    a.replicate(b);
    a.display();

    cout <<endl;

}

//@ </answer>
// ===========================================================
// No modifiques nada por debajo de esta línea
// ===========================================================


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // El primer dato leído indica el número de casos de prueba
    int num_casos;
    cin >> num_casos;

    // Llamamos a tratar_caso tantas veces como indica num_caso
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}


