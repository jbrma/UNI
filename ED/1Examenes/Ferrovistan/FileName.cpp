
/*
 * Nombre y apellidos: ___________________________________________
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>

using namespace std;

class Ferrovistan {
public:
    // Parte pública. ¡No olvides el coste!

    void nueva_linea(const string& nombre) {
        if (todasLin.count(nombre) > 0) {
            throw domain_error("Linea existente");
        }
        todasLin.insert(nombre);
        lineas[nombre] = {};
    }

    void nueva_estacion(const string& linea, const string& nombre, int posicion) {
        if (todasLin.count(linea) == 0) {
            throw domain_error("Linea no existente");
        }
       
        if (estaciones[nombre].count(linea) > 0) {
            throw domain_error("Estacion duplicada en linea");
        }
        
        //inserto la estacion en la ultima posicion de la lista de la linea y me guardo en it el iterador que apunta
        lineas[linea].push_back({ nombre, posicion });
        auto it = prev(lineas[linea].end());

        // guardo ese iterador en el otro mapa
        estaciones[nombre][linea] = it;
    }

    void eliminar_estacion(const string& estacion) {
        if (estaciones.count(estacion) == 0) {
            throw domain_error("Estacion no existente");
        }

        auto linea = estaciones[estacion];

        for (auto it = linea.begin(); it != linea.end(); it++) {
            lineas[it->first].erase(it->second);
        }
        
    }

    vector<string> lineas_de(const string& estacion) const {
        if (estaciones.count(estacion) == 0) {
            throw domain_error("Estacion no existente");
        }
        vector<string> v;

        for (auto it = estaciones.at(estacion).cbegin(); it != estaciones.at(estacion).cend(); ++it) {
            v.push_back(it->first);
        }

        return v;
    }

    string proxima_estacion(const string& linea, const string& estacion) const {

        if (todasLin.count(linea) == 0) {
            throw domain_error("Linea no existente");
        }
        if (estaciones.count(estacion) == 0) {
            throw domain_error("Estacion no existente");
        }

    }
    
private:
    // Parte privada
    
    unordered_set<string> todasLin;

    unordered_map<string, list<pair<string, int>>> lineas;

    unordered_map<string, map<string, list<pair<string, int>>::iterator>> estaciones;

};


bool tratar_caso() {
    Ferrovistan oe;
    string op;
    cin >> op;

    if (cin.eof()) return false;
    /*
    while (op != "FIN") {
        try {
            if (op == "nuevo") {
                string dni;
                cin >> dni;
                oe.nuevo(dni);
            }
            else if (op == "quitar") {
                string dni;
                int puntos;
                cin >> dni >> puntos;
                oe.quitar(dni, puntos);
            }
            else if (op == "consultar") {
                string dni;
                cin >> dni;
                int ptos = oe.consultar(dni);
                cout << "Puntos de " << dni << ": " << ptos;
                cout << "\n";
            }
            else if (op == "cuantos_con_puntos") {
                int puntos;
                cin >> puntos;
                int num = oe.cuantos_con_puntos(puntos);
                cout << "Con " << puntos << " puntos hay  " << num;
                cout << "\n";
            }
        }
        catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> op;
    }
    cout << "---\n";
    */
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
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

// SALT: ##