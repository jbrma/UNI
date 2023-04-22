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

typedef int lista[26];

void anade(unordered_map<string, int> m, unordered_map<string, int> mm, int i, lista l, string s);
void anadee(unordered_map<string, int> m, unordered_map<string, int> mm, int i, lista l, string s, string s2);
void aux(pair<string, int> ss2, unordered_map<string, int> mm);
pair<string, string> code(string s);

pair<char, int> mayor_frecuencia(const string &palabra_inicial, int n) {

  // Implementa tu solución aquí en función de la palabra y el número de expansiones
  // pasados como parámetro.
  //º
  // Indica el coste en función de la longitud L de la cadena inicial y el número N de expansiones
  // que queremos realizar.
    string cadena = palabra_inicial;
    lista l = { 0 };
    unordered_map<string, int> m;

    for (int i = 0; i < cadena.length(); i++) {
        l[cadena[i] - 'A']++;
    }

    for (int i = 0; i < cadena.length(); i++) {
        string cadena_nueva = cadena.substr(i,2);

        if (m.find(cadena_nueva) != m.end()) {
            m.at(cadena_nueva);
        }
        else {
            pair<string, int> pair = { cadena_nueva,1 };
            m.insert(pair);
        }
    }


    unordered_map<string, int> mm;
    for (int i = 0; i < n; i++) {
        mm.clear();
        for (auto it = m.begin(); it != m.end(); it++) {
            anade(m, mm, it->second, l, it->first);
        }
        m = mm;
    }
    int may = 0;
    int r = 0;
    for (int i = 0; i < 26; i++) {
        if (l[i] > r) {
            r = l[i];
            may = i;
        }
    }
    char c = may + 'A';
    pair<char, int> pair = { c, r };
    return pair;
}

pair<string, string> code(string s) {
    char caract = (s[0] - 'A' + s[1] - 'A') % 26 + 'A';
    pair<string, string> s2;
    string str;
    str.push_back(s[0]);
    str.push_back(caract);
    string strr;
    strr.push_back(caract);
    strr.push_back(s[1]);
    s2.second = strr;
    return s2;
}

void anadee(unordered_map<string, int> m, unordered_map<string, int> mm, int i, lista l, string s, string s2) {
    pair<string, int> ss2 = {s2, i};
    aux(ss2, mm);
}

void aux(pair<string, int> ss2, unordered_map<string, int> mm) {
    if (mm.find(ss2.first) != mm.end()) {
        mm.at(ss2.first) += ss2.second;
    }
    else {
        mm.insert(ss2);
    }
}

void anade(unordered_map<string, int> m, unordered_map<string, int> mm, int i, lista l, string s) {
    pair<string, string> ss2;
    ss2 = code(s);
    anadee(m, mm, i, l, s, ss2.first);
    anadee(m, mm, i, l, s, ss2.second);
    l[ss2.first[1] - 'A'] += i;

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
