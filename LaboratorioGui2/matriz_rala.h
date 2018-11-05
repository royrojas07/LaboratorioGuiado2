#ifndef MATRIZ_RALA_H
#define MATRIZ_RALA_H
#include <stdexcept> // para usar excepciones de tipo "out_of_range".
#include <vector>
using namespace std;

#include "fila_rala.h"
#include "itr_matriz_rala.h"

template < typename T >
class itr_matriz_rala;

template < typename T >
class matriz_rala {
    /* Plantilla matriz_rala: representa una matriz rala de contenido T de dimensiones cf x cc,
     * con cf la cantidad de filas y cc la cantidad de columnas. Se pueden agregar nuevas posiciones
     * a la matriz siempre que no se rebase ni cf ni cc. En una matriz rala se supone que la mayor
     * parte de las entradas guardan el valor cero por lo que s�lo se guardan efectivamente los 
     * valores diferentes de cero. 
     * Se supone que T puede ser int, double, float, long, long int, long long int o long double.
     */

public:
    typedef itr_matriz_rala< T > const_iterator;
    friend class itr_matriz_rala< T >;

    /* CONSTRUCTORES */
    // Construye una matriz rala vac�a de 20 filas y 10 columnas.
    matriz_rala();

    // Construye una matriz rala vac�a de cf filas y cc columnas.
    matriz_rala(int cf, int cc);

    // Construye una matriz rala copia id�ntica a mr_orig.
    matriz_rala(const matriz_rala< T >& mr_orig);

    /* DESTRUCTOR */

    ~matriz_rala();

    /* OBSERVADORES */

    // EFE: retorna la cantidad de filas.
    int obtCF() const;

    // EFE: retorna la cantidad de columnas.
    int obtCC() const;


    // EFE: retorna "out_of_range" si ( 0 > f ) || ( obtCF() <= f ), de lo contrario
    //		retorna una copia de la fila rala correspondiente al �ndice f.
    const fila_rala< T >& operator[](int f) const throw (out_of_range);

    /* MODIFICADORES */
    // EFE: retorna "out_of_range" si ( 0 > f ) || ( obtCF() <= f ), de lo contrario
    //		retorna una referencia de la fila rala correspondiente al �ndice f.
    fila_rala< T >& operator[](int f) throw (out_of_range);

    /* ITERADORES */
    // EFE: retorna un iterador que apunta a la primera posici�n de *this.
    const_iterator& begin();

    // EFE: retorna un iterador que apunta a la posici�n despu�s de la final en *this.
    const_iterator& end();
private:
    int cf; // cantidad de filas
    int cc; // cantidad de columnas
    vector< fila_rala< T > > filas;

    /* iteradores */
    static itr_matriz_rala< T > itr_begin; // Se le asocia un CnjOrd_gnr para recorrer
    static itr_matriz_rala< T > itr_end; // NO se le asocia nunca un CnjOrd_gnr.
};

template < typename T >
itr_matriz_rala< T > matriz_rala< T >::itr_begin;

template < typename T >
itr_matriz_rala< T > matriz_rala< T >::itr_end;

template < typename T >
matriz_rala< T >::matriz_rala() {
    cf = 20;
    cc = 10;
    filas.reserve(cf);
    for( int i = 0; i < cf; i++ ){
        fila_rala< T > fila;
        filas.push_back( fila );
    }
}

template < typename T >
matriz_rala< T >::matriz_rala(int cf, int cc) {
    this->cc = cc;
    this->cf = cf;
    filas.reserve(cf);
    for( int i = 0; i < cf; i++ ){
        fila_rala< T > fila(cc);
        filas.push_back( fila );
    }
}

template < typename T >
matriz_rala< T >::matriz_rala(const matriz_rala< T >& mr_orig){
    this->cf = mr_orig.obtCF();
    this->cc = mr_orig.obtCC();
    filas.reserve(cf);
    for( int i = 0; i < cf; i++ ){
        fila_rala< T > fila( mr_orig.filas[i] );
        filas.push_back( fila );
    }
}

template < typename T >
matriz_rala< T >::~matriz_rala() {
}

template < typename T >
const fila_rala< T >& matriz_rala< T >::operator[](int f) const throw (out_of_range) {
    if( 0 > f || cf <= f ){
        throw out_of_range( "Indice no válido." );
    }else{
        return filas[f];
    }
}

template < typename T >
fila_rala< T >& matriz_rala< T >::operator[](int f) throw (out_of_range) {
    if( 0 > f || cf <= f ){
        throw out_of_range( "Indice no válido." );
    }else{
        return filas[f];
    }
}

template < typename T >
int matriz_rala< T >::obtCF() const {
    return cf;
}

template < typename T >
int matriz_rala< T >::obtCC() const {
    return cc;
}

template < typename T >
itr_matriz_rala< T >& matriz_rala< T >::begin() {
    itr_begin.asg_matriz_rala( *this );
    return itr_begin;
}

template < typename T >
itr_matriz_rala< T >& matriz_rala< T >::end() {
    return itr_end;
}

#endif