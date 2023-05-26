/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
 * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
 * modificar el c�digo contenido entre las etiquetas <answer>
 * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
 * prohibida, pues no se tendr� en cuenta para la correcci�n.
 *
 * Tampoco esta permitido modificar las l�neas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */


 //@ <answer>
 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1:
   Componente 2:
 */
 //@ </answer>


#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const int& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const int& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const int& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    int& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    // El m�todo se implementa m�s abajo, fuera de la definici�n de la clase.
    void zip(ListLinkedDouble& other);

private:
    // Declara aqu� los m�todos auxiliares privados que necesites,
    // pero implem�ntalos m�s adelante entre las etiquetas <answer> y </answer>

    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
};

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}

//@ <answer>
// ===========================================================
// Escribe tu soluci�n por debajo de esta l�nea
// ===========================================================

// Si has definido operaciones auxiliares privadas en la clase, implem�ntalas
// aqu�.



// Implementa el m�todo pedido aqu�. No te olvides del coste.
void ListLinkedDouble::zip(ListLinkedDouble& other) {

    bool ultimo = false; // false si el ultimo num en a�adir ha sido de this, true de other
    Node* curr_this = head->next;
    Node* curr_other = other.head->next;

    while (curr_this != head && curr_other != other.head) {

        Node* sig_this = curr_this->next;
        Node* sig_other = curr_other->next;

        curr_this->next = curr_other;
        curr_other->prev = curr_this;

        curr_other->next = sig_this;
        sig_this->prev = curr_other;

        curr_this = sig_this;
        curr_other = sig_other;

    }

    if (curr_other != other.head) {
        Node* last_this = head->prev;
        Node* first_other = curr_other;
        Node* last_other = other.head->prev;

        last_this->next = first_other;
        first_other->prev = last_this;

        last_other->next = head;
        head->prev = last_other;
    }

    other.head->next = other.head;
    other.head->prev = other.head;
    other.num_elems = 0;


}


void leeLista(ListLinkedDouble &aux) {

    int n;
    cin >> n; //tama�o de la lista 

    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        aux.push_back(num);
    }
}

void tratar_caso() {
    // Escribe aqu� el c�digo para leer de la entrada
    // un caso de prueba y procesarlo.
    ListLinkedDouble thi, other;
    leeLista(thi);
    leeLista(other);
    thi.zip(other);

    cout << thi << endl;
}

//@ </answer>
// ===========================================================
// No modifiques nada por debajo de esta l�nea
// ===========================================================

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int num_casos;
    std::cin >> num_casos;

    while (num_casos > 0) {
        tratar_caso();
        num_casos--;
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
