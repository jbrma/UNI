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
    map<int, string> mapa;

    cin >> w >> h;

    if (w != 0 && h != 0){
        // Leer los tramos
        cin >> n;
        int x = 0;
        for (int i = 0; i < n; i++) {
            int longitud;
            string color;
            cin >> longitud >> color;
            mapa.insert({ longitud + x, color });
            x += longitud;
        }
    
        // Leer consultas e imprimir
        cin >> q;
        for (int i = 0; i < q; i++) {
            int x, y;
            cin >> x >> y;
            int pixel = w * (y - 1) + x;
            auto it = mapa.lower_bound(pixel);
            cout << it->second;
            cout << endl;

        }
        cout << "---" << endl;
        return true;
    }

    else
        return false;

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

