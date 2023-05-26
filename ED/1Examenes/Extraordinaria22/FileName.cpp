﻿/*@ <answer>
 *
 * Nombre y apellidos: ____________________________________________________
 *
 *@ </answer> */

 /*
  * Implementa las operaciones pedidas en el ejercicio al final de
  * este fichero, entre las etiquetas.
  */

#include <iostream>
#include <fstream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>
#include <cassert>

  /* --------------------------------------------------------------------
   * Clase BinTree
   * --------------------------------------------------------------------
   * Implementa el TAD de los �rboles binarios
   * --------------------------------------------------------------------
   */

template<class T>
class BinTree {

private:
    struct TreeNode;
    template <typename S>
    class iterator_gen;

    using NodePointer = std::shared_ptr<TreeNode>;

public:
    using const_iterator = iterator_gen<const T&>;
    using iterator = iterator_gen<T&>;


    BinTree() : root_node(nullptr) { }

    BinTree(const T& elem) : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        :root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }


    bool empty() const {
        return root_node == nullptr;
    }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const {
        display_node(root_node, out);
    }

    template <typename U>
    void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U>
    void inorder(U func) const {
        std::stack<NodePointer> st;

        descend_and_push(root_node, st);

        while (!st.empty()) {
            NodePointer current = st.top();
            st.pop();

            func(current->elem);

            descend_and_push(current->right, st);
        }
    }

    template <typename U>
    void postorder(U func) const {
        postorder(root_node, func);
    }

    template <typename U>
    void levelorder(U func) const;


    iterator begin() {
        return iterator(root_node);
    }

    iterator end() {
        return iterator();
    }

    const_iterator begin() const {
        return const_iterator(root_node);
    }

    const_iterator end() const {
        return const_iterator();
    }

    const_iterator cbegin() {
        return const_iterator(root_node);
    }

    const_iterator cend() {
        return const_iterator();
    }
private:


    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right) : elem(elem), left(left), right(right) { }

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    template <typename S>
    class iterator_gen {
    public:

        S operator*() const {
            assert(!st.empty());
            return st.top()->elem;
        }

        iterator_gen& operator++() {
            assert(!st.empty());
            NodePointer top = st.top();
            st.pop();
            BinTree::descend_and_push(top->right, st);
            return *this;
        }

        iterator_gen operator++(int) {
            iterator_gen previous = *this;
            ++(*this);
            return previous;
        }

        bool operator==(const iterator_gen& other) const {
            return st == other.st;
        }

        bool operator!=(const iterator_gen& other) const {
            return !this->operator==(other);
        }

    private:
        friend class BinTree;

        iterator_gen() { }

        iterator_gen(const NodePointer& root) {
            BinTree::descend_and_push(root, st);
        }

        std::stack<NodePointer> st;
    };



    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }

    static void descend_and_push(const NodePointer& node, std::stack<NodePointer>& st);

    template <typename U>
    static void preorder(const NodePointer& node, U func);

    template <typename U>
    static void postorder(const NodePointer& node, U func);

};


template <typename T>
void BinTree<T>::descend_and_push(const NodePointer& node, std::stack<NodePointer>& st) {
    NodePointer current = node;
    while (current != nullptr) {
        st.push(current);
        current = current->left;
    }
}


template<typename T>
template<typename U>
void BinTree<T>::preorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template<typename T>
template<typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}


template<typename T>
template<typename U>
void BinTree<T>::levelorder(U func) const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        func(current->elem);
        if (current->left != nullptr) {
            pending.push(current->left);
        }
        if (current->right != nullptr) {
            pending.push(current->right);
        }
    }
}


template<typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}


template<typename T>
BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }

}



/* --------------------------------------------------------------------
 * Implementa la funci�n pedida a continuaci�n.
 * --------------------------------------------------------------------
 *
 * Puedes a�adir las funciones auxiliares que necesites, pero has de
 * hacerlo entre las etiquetas <answer> y </answer>
 *
 *@ <answer>
 */

using namespace std;

//
// COSTE: O(____________), donde n es el n�mero de nodos del �rbol de entrada.
// 


int numImparColgantes(const BinTree<int>& tree) {
    int sumaImparDes = 0;
    int sumaImparAnc = 0;

    if (tree.empty()) {
        return 0;
    }
    else if (tree.left().empty() && tree.right().empty()) {

    }
    else {
        
    }
}


bool impar(const BinTree<int>& tree) {
    return tree.root() % 2 == 0 ? false : true;
}

int sumaDescendientes(const BinTree<int>& tree) {
    int aux = 0;
    if (impar(tree)) {
        aux = sumaDescendientes(tree.left()) + sumaDescendientes(tree.right());
    }
        
    return aux;
}

/*@ </answer> */


void tratar_caso() {
    BinTree<int> tree = read_tree<int>(std::cin);
    std::cout << (numImparColgantes(tree)) << std::endl;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int num_casos;
    std::cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}

// SALT: ##
