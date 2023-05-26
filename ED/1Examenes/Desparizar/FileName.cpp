/*
 * ---------------------------------------------------------------
 *                 ESTRUCTURAS DE DATOS - EXAMEN FINAL
 *                   CONVOCATORIA EXTRAORDINARIA
 * ---------------------------------------------------------------
 *                            Ejercicio 1
 * ---------------------------------------------------------------
 *
 * IMPORTANTE: Para realizar este ejercicio solo es necesario
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas no se
 * tendrá en cuenta para la corrección.
 *
 * ---------------------------------------------------------------
 */


 //@ <answer>

 // Manuel Montenegro Montes

 //@ </answer>

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <list>
#include <utility>
#include <cassert>

using namespace std;

/*
 * Implementación del TAD Lista mediante listas doblemente enlazadas circulares
 * con nodo fantasma.
 *
 */

template <typename T> class ListLinkedDouble {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };

    template <typename U> class gen_iterator;

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

    void push_front(const T& elem) { insert(cbegin(), elem); }

    void push_back(const T& elem) { insert(cend(), elem); }

    void pop_front() { erase(cbegin()); }

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

    const T& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    T& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const T& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    T& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const T& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    T& operator[](int index) {
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

    using iterator = gen_iterator<T>;
    using const_iterator = gen_iterator<const T>;

    iterator begin() { return iterator(head, head->next); }

    iterator end() { return iterator(head, head); }

    const_iterator begin() const { return const_iterator(head, head->next); }

    const_iterator end() const { return const_iterator(head, head); }

    const_iterator cbegin() const { return const_iterator(head, head->next); }

    const_iterator cend() const { return const_iterator(head, head); }

    template <typename U>
    gen_iterator<U> insert(gen_iterator<U> it, const T& elem) {
        // Comprobamos que el iterador pertenece a la misma
        // lista en la que realizamos la inserción.
        assert(it.head == head);
        Node* new_node = new Node{ elem, it.current, it.current->prev };
        it.current->prev->next = new_node;
        it.current->prev = new_node;
        num_elems++;
        return gen_iterator<U>(head, new_node);
    }

    template <typename U> gen_iterator<U> erase(gen_iterator<U> it) {
        // Comprobamos que el iterador pertenece a la misma
        // lista en la que realizamos la inserción, y que no
        // estamos en el último elemento.
        assert(it.head == head && it.current != head);
        Node* target = it.current;
        it.current->prev->next = it.current->next;
        it.current->next->prev = it.current->prev;
        gen_iterator<U> result(head, it.current->next);
        delete target;
        num_elems--;
        return result;
    }

    // Nueva operación. Se implementa más abajo
    void desparizar(ListLinkedDouble& aux);


private:
    Node* head;
    int num_elems;

    template <typename U> class gen_iterator {
    public:
        gen_iterator& operator++() {
            assert(current != head);
            current = current->next;
            return *this;
        }

        gen_iterator operator++(int) {
            assert(current != head);
            gen_iterator antes = *this;
            current = current->next;
            return antes;
        }

        U& operator*() const {
            assert(current != head);
            return current->value;
        }

        bool operator==(const gen_iterator& other) const {
            return (head == other.head) && (current == other.current);
        }

        bool operator!=(const gen_iterator& other) const {
            return !(*this == other);
        }

        friend class ListLinkedDouble;

    private:
        gen_iterator(Node* head, Node* current) : head(head), current(current) {}
        Node* head;
        Node* current;
    };

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);

    //{{{  
    static void detach(Node* n);
    static void attach(Node* n, Node* before);
    //}}}
};

template <typename T>
typename ListLinkedDouble<T>::Node* ListLinkedDouble<T>::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename T> void ListLinkedDouble<T>::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename T>
void ListLinkedDouble<T>::copy_nodes_from(const ListLinkedDouble& other) {
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

template <typename T>
void ListLinkedDouble<T>::display(std::ostream& out) const {
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << " " << current->value;
            current = current->next;
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const ListLinkedDouble<T>& l) {
    l.display(out);
    return out;
}

//@ <answer>

// -------------------------------------------------------------
// Implementa el método pedido aquí.
// -------------------------------------------------------------
//
// Puedes añadir las operaciones privadas auxiliares
// que consideres necesarias. Estas operaciones nuevas se declaran
// en la clase, pero han de implementarse aquí.



template <typename T>
void ListLinkedDouble<T>::desparizar(ListLinkedDouble& aux) {

    Node* prev = head;
    Node* cur = head->next;
    Node* last_aux = aux.head->prev;

    while (cur != head) {

        if (cur->value % 2 == 0) {

            //desacoplar
            prev->next = cur->next;
            cur->next->prev = prev;
            
            //acoplar
            last_aux->next = cur;
            cur->prev = last_aux;

            cur->next = aux.head;
            aux.head->prev = cur;

            last_aux = cur;
            cur = prev->next;
            
        }
        else {
            prev = cur;
            cur = cur->next;
        }
    }

}


//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>


// Función que lee una lista de la entrada
void leer_lista(ListLinkedDouble<int>& result) {
    int num;
    cin >> num;
    while (num != 0) {
        result.push_back(num);
        cin >> num;
    }
}

// Función que trata un caso de prueba.
void tratar_caso() {
    ListLinkedDouble<int> source, dest;

    leer_lista(source);
    leer_lista(dest);

    source.desparizar(dest);

    cout << source << '\n' << dest << '\n';
}


int main() {
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

    return 0;
}