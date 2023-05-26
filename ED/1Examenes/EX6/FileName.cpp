
/*
 * Nombre y apellidos: Jorge Bravo Mateos
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <list>

using namespace std;


using nombre = string;
using empleo = string;


class oficinaEmpleo {
public:
    // Parte pública. ¡No olvides el coste!

    void altaOficina(string nombre, string empleo) {
        empleos[empleo].push_back(nombre);

        personas[nombre][empleo] = prev(empleos[empleo].end());
    }

    string ofertaEmpleo(string empleo) {
        if (empleos.count(empleo) == 0) {
            throw domain_error("No existen personas apuntadas a este empleo");
        }

        if (empleos[empleo].empty()) {
            throw domain_error("No existen personas apuntadas a este empleo");
        }

        string persona = empleos[empleo].front();
        empleos[empleo].pop_front();

        if (empleos[empleo].empty()) {
            empleos.erase(empleo);
        }

        for (const auto &it : personas[persona]) {
            
            string empleo = it.first;
            list<string>::iterator ite = it.second;

            empleos[empleo].erase(it.second);

        }

        personas.erase(persona);

        return persona;
    }

    vector<string> listadoEmpleos(string persona) {
        if (personas.count(persona) == 0) {
            throw domain_error("Persona inexistente");
        }
        vector<string> empleos;

        for (const auto& e : personas[persona]) {
            empleos.push_back(e.first);
        }

        sort(empleos.begin(), empleos.end());

        return empleos;
    }

private:
    // Parte privada
                                  
    unordered_map<string, list<string>> empleos; //mapa q guarda los empleos con sus personas cualificadas
                                   
    unordered_map<string, map<string, list<string>::iterator>> personas;

};


bool tratar_caso() {
    oficinaEmpleo oe;
    string op;
    cin >> op;

    if (cin.eof()) return false;

    while (op != "FIN") {
        try {
            if (op == "altaOficina") {
                string nombre, empleo;
                cin >> nombre >> empleo;
                oe.altaOficina(nombre, empleo);
            }
            else if (op == "ofertaEmpleo") {
                string empleo;
                cin >> empleo;
                string persona = oe.ofertaEmpleo(empleo);
                cout << empleo << ": " << persona << "\n";
            }
            else if (op == "listadoEmpleos") {
                string persona;
                cin >> persona;
                vector<string> empleos = oe.listadoEmpleos(persona);
                cout << persona << ":";
                for (const string& e : empleos) {
                    cout << " " << e;
                }
                cout << "\n";
            }
        }
        catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> op;
    }
    cout << "---\n";

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
    system("PAUSE");
#endif
    return 0;
}

// SALT: ##