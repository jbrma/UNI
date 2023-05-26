
//@ <answer>
// Nombre y Apellidos:
//@ </answer>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <vector>

// añade las librerías de la STL que necesites


#include <unordered_map>
#include <set>
using namespace std;


// Elige el tipo representante adecuado para el TAD ElGrande e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente. Justifica la elección de los tipos y el
// coste de las operaciones.
//@ <answer>

using jugador = string;
using region = string;

class ElGrande {

    // escribe aquí los atributos privados

    unordered_map<region, jugador> jugDom; //jugadores que dominan cada region
    unordered_map<jugador, int> partida; //jugadores y sus puntaciones (num de regiones dominadas)
    set<region> regionesDisp; //regiones en disputa
    unordered_map<region, unordered_map<jugador, int>> numCaballeros; //numero de caballeros de un jug en una region

    int caballerosDom(const region& r) {
        return numCaballeros.at(r).at(jugDom.at(r));
    }

public:

    void anyadir_jugador(const jugador& j) {

        if (partida.count(j) != 0) {
            throw domain_error("Jugador existente");
        }
        //partida.insert({ j, 0 });
        partida[j] = 0;
    }

    void colocar_caballero(const jugador& j, const region& r) {
        if (partida.count(j) == 0) {
            throw domain_error("Jugador no existente");
        }
        if (numCaballeros.count(r) == 0) {
            numCaballeros[r][j] = 1;
            jugDom[r] = j;
            partida[j]++;
        }
        else {
            numCaballeros[r][j] += 1; //colocamos un caballero

            if (regionesDisp.count(r) != 0) { //si la region estaba en disputa

                if (numCaballeros[r][j] >= numCaballeros[r][jugDom[r]]){ //el jugador pasa a dominarla si cumple

                    jugDom[r] = j;
                    regionesDisp.erase(r);
                    partida[j]++;
                }
            }
            else if (jugDom[r] != j) { //si la region no esta en disputa
                if (numCaballeros[r][j] == numCaballeros[r][jugDom[r]]) { //el jugador tiene la misma puntuacion q el dominante

                    regionesDisp.insert(r);
                    partida[jugDom[r]]--;
                }
            }
        }

    }

    int puntuacion(const jugador& j) const {
        if (partida.count(j) == 0) {
            throw domain_error("Jugador no existente");
        }
        return partida.at(j);
    }

    vector<region> regiones_en_disputa() const {
        return vector<region>(regionesDisp.begin(), regionesDisp.end());
    }

    void expulsar_caballeros(const region& r) {
        if (numCaballeros.count(r) == 0) {
            throw domain_error("Region vacia");
        }
        regionesDisp.erase(r);
        partida.at(jugDom.at(r))--;
        numCaballeros.at(r).clear();
        numCaballeros.erase(r);
    }

};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string orden, jug, reg;
    cin >> orden;
    if (!cin)
        return false;

    ElGrande juego;

    while (orden != "FIN") {
        try {
            if (orden == "anyadir_jugador") {
                cin >> jug;
                juego.anyadir_jugador(jug);
            }
            else if (orden == "colocar_caballero") {
                cin >> jug >> reg;
                juego.colocar_caballero(jug, reg);
            }
            else if (orden == "puntuacion") {
                cin >> jug;
                auto puntos = juego.puntuacion(jug);
                cout << "Puntuacion de " << jug << ": " << puntos << '\n';
            }
            else if (orden == "regiones_en_disputa") {
                auto regs = juego.regiones_en_disputa();
                cout << "Regiones en disputa:\n";
                for (auto const& r : regs) {
                    cout << r << '\n';
                }
            }
            else if (orden == "expulsar_caballeros") {
                cin >> reg;
                juego.expulsar_caballeros(reg);
            }
        }
        catch (domain_error& e) {
            cout << "ERROR: " << e.what() << '\n';
        }
        cin >> orden;
    }
    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se necesita
    // system("PAUSE");
#endif
    return 0;
}