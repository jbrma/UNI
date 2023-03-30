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
  Componente 1: Javier de la Cruz
  Componente 2: Jorge Bravo
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <map>



using namespace std;


bool tratar_caso() {
  // Código para tratar un caso de prueba.
  // Devuelve false si se ha leído la marca del final de entrada (0 0).
  // Devuelve true en caso contrario.

    int w, h, n, q;
    while (cin >> w >> h && w != 0 && h != 0) {
        // Leer los tramos
        cin >> n;
        int x = 1, y = 1;
        map<pair<int, int>, string> pixel_map;
        while (n--) {
            int longitud;
            string color;
            cin >> longitud >> color;
            for (int i = 0; i < longitud; i++) {
                pixel_map[{x, y}] = color;
                x++;
                if (x > w) {
                    x = 1;
                    y++;
                }
            }
        }

        // Leer consultas e imprimir
        cin >> q;
        
        while (q--) {
            int x, y;
            cin >> x >> y;
            cout << pixel_map[{x, y}] << endl;

        }
        cout << "---" << endl;
    }

    if (w == 0 && h == 0)
        return false;

    return true;
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
#endif
  return 0;
}

