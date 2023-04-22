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
#include <utility>
#include <unordered_map>
#include <cctype>


using namespace std;

pair<char, int> mayor_frecuencia(const string &palabra_inicial, int n) {

  // Implementa tu solución aquí en función de la palabra y el número de expansiones
  // pasados como parámetro.
  //
  // Indica el coste en función de la longitud L de la cadena inicial y el número N de expansiones
  // que queremos realizar.
    string cadena = palabra_inicial;
    for (int i = 0; i < n; i++) {
        string cadena_nueva = "";
        for (int j = 0; j < cadena.length() - 1; j++) {
            char x = cadena[j], y = cadena[j + 1];
            char nueva_letra = (code(x) + code(y)) % 26 + 'A';
            cadena_nueva += x;
            cadena_nueva += nueva_letra;
        }
        cadena_nueva += cadena.back();
        cadena = cadena_nueva;
    }
    unordered_map<char, int> ocurrencias;
    for (char c : cadena) {
        ocurrencias[c]++;
    }
    char letra_max = 'A';
    int frecuencia_max = 0;
    for (auto p : ocurrencias) {
        if (p.second > frecuencia_max) {
            letra_max = p.first;
            frecuencia_max = p.second;
        }
        else if (p.second == frecuencia_max && p.first < letra_max) {
            letra_max = p.first;
        }
    }
    return { letra_max, frecuencia_max };
}

int code(char letra) {
    return toupper(letra) - 'A';
}


bool tratar_caso() {  
  // Leemos los datos de la entrada.
  string palabra_inicial;
  int num_expansiones;
  cin >> palabra_inicial >> num_expansiones;
  
  // Si no hemos podido leer lo anterior porque hemos llegado al fin de fichero,
  // devolvemos false
  if (cin.eof()) return false;

  // En caso contrario, tratamos el caso de prueba y devolvemos true
  auto [c, num_veces] = mayor_frecuencia(palabra_inicial, num_expansiones);
  cout << c << ' ' << num_veces << '\n';

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
  // Descomentar si se trabaja en Windows
#endif
  return 0;
}
