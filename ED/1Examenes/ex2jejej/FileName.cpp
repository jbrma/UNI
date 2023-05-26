

//@ <answer>

// Nombre y apellidos: ________________________________________  

//@ </answer>



#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <list>
#include <utility>

using namespace std;

//@ <answer>

// -------------------------------------------------------------
// Implementa la función pedida aquí.
// Para ello utiliza las librerías de la STL.
//
// No olvides justificar brevemente el coste.
//
void equilibrar_lista(list<int>& lista) {

}

//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------
//@ </answer>


// Función que trata un caso de prueba.
bool tratar_caso() {
    int num_elems;
    list<int> lista;

    cin >> num_elems;
    if (cin.eof()) return false;

    // Leemos lista
    for (int i = 0; i < num_elems; i++) {
        int elem;
        cin >> elem;
        lista.push_back(elem);
    }

    // Llamamos a la función pedida
    equilibrar_lista(lista);

    // Imprimimos el resultado
    bool primero = true;
    for (auto x : lista) {
        cout << (primero ? "" : " ") << x;
        primero = false;
    }
    cout << "\n";

    return true;
} // tratar_caso


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}