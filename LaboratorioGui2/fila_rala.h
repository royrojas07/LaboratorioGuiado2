#pragma once

#include  <stdexcept> // para usar excepciones de tipo "out_of_range".
#include <memory>
#include <sstream>
using namespace std;

template < typename T >
class matriz_rala;

template < typename T >
class itr_matriz_rala;

template < typename T >
class fila_rala {
    /*
     * Representa una fila de una matriz rala de tipo T con cc columnas. Se pueden agregar nuevas
     * posiciones a la fila siempre que no se rebase cc. S�lo se representan los valores direntes
     * de cero.
     * Se supone que T:
     * puede ser un tipo num�rico como int, double, float, long, long int, long long int o long double.
     * tiene sobrecargado T().
     * tiene sobrecargado operator=(...)
     * tiene sobrecargado operator<<(...)
     */

    friend class matriz_rala< T >;
    friend class itr_matriz_rala< T >;

public:
    /* CONSTRUCTOR DE COPIAS DEBE SER P�BLICO POR REQUERIMIENTO DE LA STL */
    fila_rala(const fila_rala< T >& fr_orig);

    /* DESTRUCTOR */
    ~fila_rala();

    /* OBSERVADORES */

    // EFE: retorna el valor en la posici�n in o "out_of_range" en caso que c >= cc.
    const T operator[](int c) const throw (out_of_range);

    /* MODIFICADORES */

    // EFE: retorna por referencia la posici�n en in o "out_of_range" en caso que: c >= cc o la posici�n c no exista en la fila .
    T& operator[](int c) throw (out_of_range);

    // EFE: agrega la columna c en *this con el valor t, o genera "out_of_range" si tal columna ya existe en this.
    void insertar(int c, const T& t) throw (out_of_range);

private:

    /* CONSTRUCTORES */
    // EFE: construye una fila rala vac�a con 10 columnas.
    fila_rala();

    // EFE: construye una fila rala vac�a con cc columnas
    fila_rala(int cc);

    template < typename V >
    struct elem {
    public:
        int c; // columna
        V v; // valor
        shared_ptr< elem< V > > sgt; // puntero al siguiente elemento
        shared_ptr< elem< V > > ant; // puntero al anterior elemento

        elem< V >() : c(0), v(), sgt(0), ant(0) {
        };

        elem< V >(int cn) : c(cn), v(), sgt(0), ant(0) {
        };

        elem< V >(const elem< V >& e) : c(e.c), v(e.v), sgt(0), ant(0) {
        };

        ~elem< V >() {
        };
    };

    shared_ptr< elem< T > > inicio;
    int cc; // cantidad de columnas
};

template < typename T >
fila_rala< T >::fila_rala() {

}

template < typename T >
fila_rala< T >::fila_rala(int cc) {

}

template < typename T >
fila_rala< T >::fila_rala(const fila_rala< T >& fr_orig) {

}

template < typename T >
fila_rala< T >::~fila_rala() {
}

template < typename T >
const T fila_rala< T >::operator[](int c) const throw (out_of_range) {

}

template < typename T >
T& fila_rala< T >::operator[](int c) throw (out_of_range) {

}

template < typename T >
void fila_rala< T >::insertar(int c, const T& t) throw (out_of_range) {

}