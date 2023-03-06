/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 
/*
  Indica el nombre y apellidos de los componentes del grupo
  ---------------------------------------------------------
  Componente 1: Jorge Bravo
  Componente 2: Javier de la Cruz
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <list>

using namespace std;

void suavizar(list<int> &l) {
  // Implementa aquí la función pedida
	/*
	auto it = l.begin(); // Iterador para recorrer la lista

	while (it != l.end()) {

		auto next = std::next(it); // Iterador al siguiente elemento

		if (next != l.end() && *next == *it) {
			// Si el siguiente es igual al actual, se elimina el repetido
			it = l.erase(it);
		}
		else if (next != l.end() && *next - *it > 1) {
			// Si la diferencia entre el siguiente y el actual es mayor que 1, se insertan los números faltantes
			int dif = *next - *it;

			for (int i = 1; i < dif; i++) {
				it = l.insert(next, *it + i);
			}
			it++; // Se salta el número insertado para continuar con el siguiente
		}
		else {
			it++; // Si no hay que insertar nada, se avanza al siguiente elemento
		}
	}
	*/

	auto it = l.begin();
	while (it != l.end()) {
		auto siguiente = next(it);
		if (siguiente != l.end() && *siguiente - *it > 1) {
			int valor = *it + 1;
			l.insert(siguiente, valor);
		}
		else if (siguiente != l.end() && *it - *siguiente > 1) {
			int valor2 = *it - 1;
			l.insert(siguiente, valor2);
		}
		else if (siguiente != l.end() && *siguiente == *it) {
			l.erase(siguiente);
		}
		else {
			it++;
		}
	}
}

bool tratar_caso() {
  // Escribe aquí el código para leer y tratar un caso de prueba.
  // La función debe devolver false si no se puede leer ningún caso de prueba
  // porque se ha llegado al fin de la entrada, o true en caso contrario.
	bool ok = true;

	int numcasos = 0;

	cin >> numcasos;

	if (!cin.eof()) {

		list<int> lista(numcasos);

		for (int i = 0; i < numcasos; i++) {

			cin >> lista.front();
			lista.push_back(lista.front());
			lista.pop_front();
		}

		suavizar(lista);

		for (auto it = lista.begin(); it != lista.end(); it++) {

			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		ok = false;
	}

	return ok;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}
