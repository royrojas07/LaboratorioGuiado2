#ifndef ITR_MATRIZ_RALA_H
#define ITR_MATRIZ_RALA_H
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
    itr_matriz_rala< T >& operator=(const itr_matriz_rala< T >& orig);

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
itr_matriz_rala< T >::itr_matriz_rala(): p_elem_act(0){
}

template < typename T >
itr_matriz_rala< T >::itr_matriz_rala(const itr_matriz_rala& orig) : mr(orig.mr), p_elem_act(orig.p_elem_act), f_act(orig.f_act), c_act(orig.c_act) {
}

template < typename T >
itr_matriz_rala< T >::~itr_matriz_rala() {
}

template < typename T >
T& itr_matriz_rala< T >::operator*() {
    return p_elem_act->v;
}

template < typename T >
T* itr_matriz_rala< T >::operator->() {
    T* valor = 0;
    if( p_elem_act )
        T* valor = p_elem_act->v;
    return valor;
}

template < typename T >
itr_matriz_rala< T >& itr_matriz_rala< T >::operator++() {
    if( p_elem_act && p_elem_act->sgt ){
        p_elem_act = p_elem_act->sgt;
        c_act = p_elem_act->c;
    } else if( p_elem_act ){
        p_elem_act = obtSgtFilaRalaNoVacia( mr, f_act );
        c_act = p_elem_act->c;
    }
    return *this;
}

template < typename T >
bool itr_matriz_rala< T >::operator==(const itr_matriz_rala< T >& orig) const {
    if( p_elem_act && orig.p_elem_act )
        return (p_elem_act->c == orig.p_elem_act->c) && (p_elem_act->v == orig.p_elem_act->v);
    else if( !p_elem_act && !orig.p_elem_act )
        return true;
    else
        return false;
    //return &(p_elem_act->v) == &(p_elem_act->v);
}

template < typename T >
bool itr_matriz_rala< T >::operator!=(const itr_matriz_rala< T >& orig) const {
    return !(*this == orig);
}

template < typename T >
itr_matriz_rala< T >& itr_matriz_rala< T >::operator=(const itr_matriz_rala< T >& orig){
    p_elem_act = orig.p_elem_act;
    mr = orig.mr;
    f_act = orig.f_act;
    c_act = orig.c_act;
    return *this;
}

template < typename T >
void itr_matriz_rala< T >::asg_matriz_rala(matriz_rala< T >& mr) {
    this->mr = &mr;
    f_act = -1;
    c_act = 0;
    p_elem_act = obtSgtFilaRalaNoVacia( this->mr, f_act );
    if( p_elem_act )
        c_act = p_elem_act->c;
}

template < typename T >
int itr_matriz_rala< T >::obtFila() {
    return f_act;
}

template < typename T >
int itr_matriz_rala< T >::obtColumna() {
    return c_act;
}

template < typename T >
typename itr_matriz_rala< T >::T_p_elem itr_matriz_rala< T >::obtSgtFilaRalaNoVacia(matriz_rala< T >* mr, int& f_act) {
    T_p_elem p_elem = 0;
    matriz_rala<T> & matriz = *mr;
    while( f_act < mr->obtCF()-1 && !p_elem ){
        f_act++;
        p_elem = matriz[f_act].inicio;
    }
    return p_elem;
}

#endif