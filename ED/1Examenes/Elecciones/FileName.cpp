/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>

using namespace std;

class ConteoVotos {
public:
  
    void nuevo_estado(const string& nombre, int num_compromisarios) {

        if (estados.count(nombre) > 0) {
            throw domain_error("Estado ya existente");
        }
        estados[nombre] = {};
        estados[nombre].numComp = num_compromisarios;
    }

    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        if (estados.count(estado) == 0) {
            throw domain_error("Estado no encontrado");
        }
        auto m = estados.find(estado);
        InfoEstado& ie = m->second;
        
        ie.votos[partido] += num_votos;

        if (ie.votos[partido] > ie.votos[ie.ganador]) {
            string aux = ie.ganador;
            ie.ganador = partido;

            partidos[partido] += ie.numComp;

            if (aux != "") {
                partidos[aux] -= ie.numComp;

                if (partidos[aux] == 0)
                    partidos.erase(aux);
            }
        }
        
    }

    string ganador_en(const string& estado) const {
        if (estados.count(estado) == 0) {
            throw domain_error("Estado no encontrado");
        }
        string g = estados.at(estado).ganador;
        return g;
    }

    vector<pair<string, int>> resultados() const {

        vector<pair<string, int>> v;
           
        for (auto it = partidos.begin(); it != partidos.end(); ++it) {
            v.push_back({ it->first, it->second });
        }
        return v;
    }


private:
    // Información asociada a cada estado

    struct InfoEstado {
        int numComp;
        unordered_map<string, int> votos;
        string ganador;
    };
    
    unordered_map<string, InfoEstado> estados;
    map<string, int> partidos;

};


bool tratar_caso() {
    // Completar
  //{{{
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    ConteoVotos cv;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                string estado;
                int num_compromisarios;
                cin >> estado >> num_compromisarios;
                cv.nuevo_estado(estado, num_compromisarios);
            }
            else if (comando == "sumar_votos") {
                string estado;
                string partido;
                int num_votos;
                cin >> estado >> partido >> num_votos;
                cv.sumar_votos(estado, partido, num_votos);
            }
            else if (comando == "ganador_en") {
                string estado;
                cin >> estado;
                string ganador = cv.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            }
            else if (comando == "resultados") {
                for (const auto& [partido, num_comp] : cv.resultados()) {
                    cout << partido << " " << num_comp << "\n";
                }
            }
        }
        catch (std::exception& e) {
            cout << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
    //}}}
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