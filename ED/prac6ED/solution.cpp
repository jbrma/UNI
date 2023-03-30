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
 * las etiquetas <answer> y </answer>, obviamente 🙂
 */


 //@ <answer>
 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1: Javier de la Cruz Díaz
   Componente 2: Jorge Bravo Mateos
 */
 //@ </answer>

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>


template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

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

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

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
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
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

using namespace std;


// ----------------------------------------------------------------
// Escribe tu solución a continuación.
//
// Puedes definir funciones auxiliares. En ese caso, asegúrate de que están
// entre las etiquetas <answer> y </answer>, e indica el coste de cada una
// de ellas.
//@ <answer>
// Implementa la función pedida aquí. ¡No te olvides del coste!
//O(n) siendo n el numero de nodos del arbol
int area_mayor_sin_barreras(const BinTree<bool>& tree, int& max_area) {
    if (tree.empty())
        return 0;
    int area_izq = area_mayor_sin_barreras(tree.left(), max_area);
    int area_der = area_mayor_sin_barreras(tree.right(), max_area);
    if (!tree.root()) {
        if (area_izq + area_der + 1 > max_area)
            max_area = area_izq + area_der + 1;
        return area_izq + area_der + 1;
    }
    else {
        int aux = max(area_izq, area_der);
        if (aux > max_area)
            max_area = aux;
        return 0;
    }

}

int area_mayor_sin_barreras(const BinTree<bool>& tree) {
    int max = 0;
    area_mayor_sin_barreras(tree, max);
    return max;
}

//@ </answer>
// No modifiques nada por debajo de esta línea
// ----------------------------------------------------------------


void tratar_caso() {
    // Leemos un árbol de la entrada
    BinTree<bool> t = read_tree<bool>(cin);
    // Imprimimos el resultado tras llamar a area_mayor_sin_barreras
    cout << area_mayor_sin_barreras(t) << endl;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}