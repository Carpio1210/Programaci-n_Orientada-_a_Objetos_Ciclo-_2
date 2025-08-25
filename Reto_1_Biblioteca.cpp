#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include "json.hpp"

using nlohmann::json;

using namespace std;

class Libro {
public:
    string titulo;
    string autor;
    string genero;
    bool estaDisponible;
    int anioPublicacion;
    string usuario;

    Libro() : anioPublicacion(0), estaDisponible(true) {}

    void mostrarDetallesCompletos() {
        cout << "---------------------------------" << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Genero: " << genero << endl;
        cout << "Año de publicacion: " << anioPublicacion << endl;
        cout << "Disponibilidad: " << (estaDisponible ? "Disponible" : "No disponible") << endl;
    }
};

class Usuario {
public:
    string nombre;
    string trabajo;
    string id;
    vector<string> prestamos;

    void mostrar() const {
        cout << "---------------------------------" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Trabajo: " << trabajo << endl;
        cout << "ID: " << id << endl;
    }
};

class Biblioteca {
private:
    vector<Libro> coleccion;  // Donde esta todo, la coleccion
    vector<Usuario> usuarios;

public:

    void agregarUsuario(const Usuario& nuevoUsuario);    //USUARIOS
    Usuario*buscarusuarios(const string& nombre);        //USUARIOS
    void mostrarUsuarios() const;                         //USUARIOS

    void agregarLibro(const Libro& nuevoLibro);   // Promesa de agregar un libro

    void mostrarInventario();    // Promesa de mostrar inventario

    Libro* buscarLibro(const std::string& tituloBuscado);

    void prestarLibro(const std::string& tituloPrestamo);    // Promesa de prestamo de libro

    void devolverLibro(const std::string& tituloDevolucion);    // Promesa de devolver libro
};


// Paso de definiciones:

void Biblioteca::agregarUsuario(const Usuario& nuevoUsuario) {
    for (Usuario& usuario : usuarios) {
        if (usuario.nombre == nuevoUsuario.nombre or usuario.id == nuevoUsuario.id) {
            cout << "Ya esta registrado" << endl;
            return;
        }
    }
    usuarios.push_back(nuevoUsuario);
    cout << "Usuario registrado" << endl;
}


void Biblioteca::mostrarUsuarios() const {
    if (usuarios.empty()) {
        cout << "No hay usuarios en la plataforma." << endl;
        return;
    }
    for (auto& u : usuarios) {
        u.mostrar();
    }
}

void Biblioteca::agregarLibro(const Libro& nuevoLibro) {     // Definicion de la promesa de agregar los libros
    for (Libro& libro : coleccion) {
        if (libro.titulo == nuevoLibro.titulo) {
            cout << "Este libro ya existe " << endl;
            return;
        }
    }
    coleccion.push_back(nuevoLibro);
    nlohmann::json j = {
        {"titulo", nuevoLibro.titulo},
        {"autor", nuevoLibro.autor},
        {"genero", nuevoLibro.genero},
        {"anioPublicacion", nuevoLibro.anioPublicacion},
        {"estaDisponible", nuevoLibro.estaDisponible},
        {"usuario", nuevoLibro.usuario}
    };
    std::ofstream("Reto_1.json", std::ios::app) << j.dump() << '\n';
    cout << "Libro registrado " << endl;
}

void Biblioteca::mostrarInventario() {
    if (coleccion.empty()) {
        cout << "No hay libros" << endl;
        return;
    }
    for (Libro& libro : coleccion) {
        libro.mostrarDetallesCompletos();
    }
}

Libro* Biblioteca::buscarLibro(const std::string& tituloBuscado) {
    for (auto& l : coleccion) {
        if (l.titulo == tituloBuscado) return &l;
    }
    return nullptr;
}

void Biblioteca::prestarLibro(const std::string &tituloPrestamo) {
    Libro* libro = buscarLibro(tituloPrestamo);
    if (!libro) {
        cout << "Este libro no esta en nuestro in   ventario" << endl;
        return;
    }

    if (!libro->estaDisponible) {
        cout << "Este libro no esta disponible momentaneamente, porfavor vuelva a intentar mas tarde. Feliz dia." << endl;
        return;
        }

    string respuesta;
    cout << "El libro esta disponible desea prestarlo? si/no : " << libro->titulo << endl;
    cin >> respuesta;

    if (respuesta != "si" && respuesta != "no" && respuesta != "No" && respuesta != "Si" && respuesta != "SI" && respuesta != "Sí" && respuesta != "No" && respuesta != "sí") {
        cout << "respuesta invalida" << endl;
        return;
    }

    else if (respuesta == "si" or respuesta == "Si" or respuesta == "SI" or respuesta == "Sí" or respuesta == "sí") {
        libro->estaDisponible = false;
        cout << "Disfruta de tu libro " << libro->titulo << endl;
        return;
    }
    else if (respuesta == "no" or respuesta == "No") {
        cout << "Cancelamos su prestamo" << endl;
        return;
    }
}

void Biblioteca::devolverLibro(const std::string & tituloDevolucion) {     // Definicion de la promesa de devolver las cosas
    Libro* libro = buscarLibro(tituloDevolucion); {
        if (!libro) {
            cout << "Este libro no existe" << endl;
            return;
        }
        else if (libro->estaDisponible) {
            cout << "Este libro esta en el inventario, no ha sido prestado." << endl;
            return;
        }
        libro->estaDisponible = true;
        cout << "Libro devuelto" << endl;
    }
}

int main() {
    Biblioteca miBiblioteca;
    string opcion;

    Libro libroInicial;
    libroInicial.titulo = "El Hobbit";
    libroInicial.autor = "J.R.R. Tolkien";
    libroInicial.genero = "Novela/Fantasia";
    libroInicial.anioPublicacion = 1937;
    libroInicial.estaDisponible = true;
    miBiblioteca.agregarLibro(libroInicial);

    Usuario UsuarioInicial;
    UsuarioInicial.nombre = "Diego Carpio";
    UsuarioInicial.trabajo = "Ingeniero Industrial";
    UsuarioInicial.id = "000011";
    miBiblioteca.agregarUsuario(UsuarioInicial);

    while (opcion != "7") {
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "1. Anadir libro" << std::endl;
        std::cout << "2. Mostrar inventario" << std::endl;
        std::cout << "3. Prestar libro" << std::endl;
        std::cout << "4. Devolver libro" << std::endl;
        cout << "5. Agregar usuario nuevo" << std::endl;
        cout << "6. Mostrar usuario" << std::endl;
        std::cout << "7. Salir" << std::endl;
        std::cout << "Seleccione una opcion del 1 al 7:  ";
        std::cin >> opcion;

        if (opcion != "1" && opcion != "2" && opcion != "3" && opcion != "4" && opcion != "5" && opcion != "6" && opcion != "7") {
            cout << "Opcion invalida, intente con una opcion entre (1 a 7)." << endl;
            continue;
            }


        if (opcion == "1" or opcion == "2" or opcion == "3" or opcion == "4" or opcion == "5" or opcion == "6" or opcion == "7") {
            if (opcion == "1") {
                string libro_nuevo;
                string autor_libro;
                string genero_libro;
                int anioPublicacion;

                Libro nuevo;

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Titulo del nuevo libro: " << endl;     // Llamado de la promesa de libro nuevo
                getline(cin, libro_nuevo);
                cout << "Autor: " << endl;
                getline(cin, autor_libro);
                cout << "Genero: " << endl;
                getline(cin, genero_libro);
                cout << "Anio del Libro: " << endl;
                cin >> anioPublicacion;

                nuevo.titulo = libro_nuevo;
                nuevo.autor = autor_libro;
                nuevo.genero = genero_libro;
                nuevo.anioPublicacion = anioPublicacion;

                miBiblioteca.agregarLibro(nuevo);
            }

            else if (opcion == "2") {
                miBiblioteca.mostrarInventario();
            }

            else if (opcion == "3") {
                string titulo;

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Titulo del libro que quiere prestar: \n";
                getline(cin, titulo);
                miBiblioteca.prestarLibro(titulo);
            }

            else if (opcion == "4") {
                string devolver;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Que libro quiere devolver: " << endl;
                getline(cin, devolver);
                miBiblioteca.devolverLibro(devolver);
            }

            else if (opcion == "5") {
                string name;
                string job;
                string id;

                Usuario reciente;

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Nombre: " << endl;     // Llamado de la promesa de libro nuevo
                getline(cin, name);
                cout << "Trabajo: " << endl;
                getline(cin, job);
                cout << "ID: " << endl;
                getline(cin, id);

                reciente.nombre = name;
                reciente.trabajo = job;
                reciente.id = id;

                miBiblioteca.agregarUsuario(reciente);
            }

            else if (opcion == "6") {
                miBiblioteca.mostrarUsuarios();
            }

            else if (opcion == "7") {
                cout << "Gracias por visitar la biblioteca virtual. " << endl;
                break;
            }
        }
    }
    return 0;
}