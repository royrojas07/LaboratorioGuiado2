#pragma once

#include <memory>
using namespace std;

#include "matriz_rala.h"
#include "fila_rala.h"

template < typename T >
class itr_matriz_rala {
public:
    friend class matriz_rala< T >;
    friend class fila_rala< T >;

    itr_matriz_rala(const itr_matriz_rala& orig);
    ~itr_matriz_rala();

    /* OPERADORES COMUNES */
    T& operator*();
    T* operator->();
    itr_matriz_rala< T >& operator++();
    bool operator==(const itr_matriz_rala< T >& orig) const;
    bool operator!=(const itr_matriz_rala< T >& orig) const;
    itr_matriz_rala< T >& operator=(const itr_matriz_rala< T >& orig) const;

    /* OBTENEDORES ESPEC�FICOS */
    int obtFila();
    int obtColumna();

private:
    // Se debe resolver ambig�edades para el compilador indicando que:
    // el tipo contenido es un template.
    // matriz_rala< T >::template NdoT< T > es un tipo.
    typedef shared_ptr< typename fila_rala< T >::template elem< T > > T_p_elem;

    // Construye un iterador NO asociado a ning�n conjunto que sirve de "end()".
    itr_matriz_rala();

    // Le asocia un conjunto a un iterador previamente construido. Sirve al begin().
    void asg_matriz_rala(matriz_rala< T >& mr);

    // Retorna puntero al primer elemento de la primera fila_rala no vac�a a partir de f_act en mr->filas.
    // Modifica f_act con el valor de la primera fila_rala no vac�a a partir de f_act en mr->filas.
    T_p_elem obtSgtFilaRalaNoVacia(matriz_rala< T >* mr, int& f_act);

    /* variables de estado del iterador */
    matriz_rala< T >* mr; // puntero a la matriz_rala
    T_p_elem p_elem_act; // puntero a elemento actual
    int f_act; // �ndice de fila actual
    int c_act; // �ndice de columna actual
};

template < typename T >
itr_matriz_rala< T >::itr_matriz_rala() {

}

template < typename T >
itr_matriz_rala< T >::itr_matriz_rala(const itr_matriz_rala& orig) : mr(orig.mr), p_elem_act(orig.p_elem_act), f_act(orig.f_act), c_act(orig.c_act) {
}

template < typename T >
itr_matriz_rala< T >::~itr_matriz_rala() {
}

template < typename T >
T& itr_matriz_rala< T >::operator*() {

}

template < typename T >
T* itr_matriz_rala< T >::operator->() {

}

template < typename T >
itr_matriz_rala< T >& itr_matriz_rala< T >::operator++() {

}

template < typename T >
bool itr_matriz_rala< T >::operator==(const itr_matriz_rala< T >& orig) const {

}

template < typename T >
bool itr_matriz_rala< T >::operator!=(const itr_matriz_rala< T >& orig) const {

}

template < typename T >
itr_matriz_rala< T >& itr_matriz_rala< T >::operator=(const itr_matriz_rala< T >& orig) const {

}

template < typename T >
void itr_matriz_rala< T >::asg_matriz_rala(matriz_rala< T >& mr) {

}

template < typename T >
int itr_matriz_rala< T >::obtFila() {

}

template < typename T >
int itr_matriz_rala< T >::obtColumna() {

}

template < typename T >
typename itr_matriz_rala< T >::T_p_elem itr_matriz_rala< T >::obtSgtFilaRalaNoVacia(matriz_rala< T >* mr, int& f_act) {

}