#include <iostream>
#include <string>

class Futbol {
protected:
    std::string equipo;
    std::string capitan;
    std::string lugar;
public:
    Futbol(const std::string& equipo, const std::string& capitan, const std::string& lugar) {

        this->equipo = equipo;
        this->capitan = capitan;
        this->lugar = lugar;
        std::cout << "Se ha hecho un Equipo." << std::endl;
    }
    void equipos() {
        std::cout << "El equipo  " << equipo << " ha jugado en  " << lugar << std::endl;
    }
    void ganar() {
        std::cout << "El equipo " << equipo << " ha ganado y el jugador" << capitan << " ha metido el gol." << std::endl;
    }
};


    class Club : public Futbol {
private:
    int titulos;
public:

    Club(const std::string& equipo, const std::string& capitan, const std::string& lugar ,int titulos)
    : Futbol(equipo, capitan, lugar) {
        this->titulos = titulos;
        std::cout << "Se ha definido que equipo es." << std::endl;
    }
    void campeones() {
        std::cout << "Bienvenido al equipo " << equipo << std::endl;
    }
    void mostrarDetallesclub() {
        std::cout << "--- Detalles del Equipo ---" << std::endl;
        std::cout << "Equipo: " << this->equipo << std::endl;
        std::cout << "Capitan: " << this->capitan << std::endl;
        std::cout << "Lugar: " << this->lugar << std::endl;
        std::cout << "Titulos: " << this->titulos << std::endl;
    }
};

int main() {
    std::cout << "Creando Historial de un Club..." << std::endl;
    Club miCel("Barcelona", " Diego Carpio","Espana", 103);
    std::cout << "\n--- Probando metodos ---\n";
    miCel.equipos();
    miCel.ganar();
    miCel.mostrarDetallesclub();
    return 0;
}