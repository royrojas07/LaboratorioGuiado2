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

    // EFE: retorna por referencia la posici�n en c o "out_of_range" en caso que: c >= cc o la posici�n c no exista en la fila .
    T& operator[](int c) throw (out_of_range);

    // EFE: agrega la columna c en *this con el valor c, o genera "out_of_range" si tal columna ya existe en this.
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
    //reserve
    shared_ptr< elem< T > > inicio;
    int cc; // cantidad de columnas
};

template < typename T >
fila_rala< T >::fila_rala() {
    cc = 10;
    inicio = 0;
}

template < typename T >
fila_rala< T >::fila_rala(int cc) {
    this->cc = cc;
    inicio = 0;
}

template < typename T >
fila_rala< T >::fila_rala(const fila_rala< T >& fr_orig) {
    cc = fr_orig.cc;
    inicio = 0;
    if( fr_orig.inicio ){
        inicio = shared_ptr<elem<T>>(new elem<T>( *fr_orig.inicio ));
        shared_ptr<elem<T>> agregado = inicio;
        shared_ptr<elem<T>> porAgregar = fr_orig.inicio->sgt;
        while( porAgregar ){
            agregado->sgt = shared_ptr<elem<T>>(new elem<T>( *porAgregar ));
            porAgregar = porAgregar->sgt;
            agregado = agregado->sgt;
        }
    }
}

template < typename T >
fila_rala< T >::~fila_rala() {
}

template < typename T >
const T fila_rala< T >::operator[](int c) const throw (out_of_range) {
    int col=c;
    int valor=0;
    shared_ptr< elem< T > > iterando;
    if (col >= this->cc){
        throw std::out_of_range("indice no válido");
    }else{
        iterando=inicio;
        while(iterando!=nullptr){
            if(iterando->c==col){
                return iterando->v;
                iterando=nullptr;
            }else{
                iterando=iterando->sgt;
            }
        }
    }
}

template < typename T >
T& fila_rala< T >::operator[](int c) throw (out_of_range) {
    int col=c;
        shared_ptr< elem< T > > iterando;
        if (col>=this->cc){
            throw std::out_of_range("indice no válido");
        }else{
            iterando=inicio;
            while(iterando!=nullptr){
                if(iterando->c==col){
                    return iterando->v;
                    iterando=nullptr;
                }else{
                    iterando=iterando->sgt;
                }
            }
        }
}

template < typename T >
void fila_rala< T >::insertar(int c, const T& t) throw (out_of_range) {
    shared_ptr< elem< T > > iterando;
    shared_ptr< elem< T > > p;
    int cor=0;
    int col=c;
    bool entro=false;
    iterando=inicio;
    shared_ptr< elem< T > > temporal;
     if (inicio == 0){ // se agrega el primer elemento a *this
        inicio = shared_ptr< elem< T > >(new elem< T >(col));
        inicio->v=t;
     }else if(iterando->c>col){ //se agrega al principio
        temporal=shared_ptr< elem< T > >(new elem< T >(col));
        temporal->sgt=inicio;
        temporal->v=t;
        inicio=temporal;
    }else{
        while(iterando!=nullptr){
            if(iterando->c==col){
              throw std::out_of_range("columna ya existe");
              iterando=nullptr;
              cor=1;
            }else{
                if(iterando->c<col){
                  temporal=iterando;
                  entro=true;
                  iterando=iterando->sgt;
                }else if(iterando->c>col && entro==false){
                    temporal=iterando;
                    iterando=nullptr;
                }else if(iterando->c>col && entro==true){
                iterando=nullptr;
                }
            }
        }
        if(entro==true){
            p=temporal->sgt;
            temporal->sgt=shared_ptr< elem< T > >(new elem< T >(col));
            temporal->sgt->v=t;
            temporal->sgt->sgt=p;
            temporal->sgt->ant=temporal;
        }else if(entro==false && cor==0 ){
            temporal->sgt=shared_ptr< elem< T > >(new elem< T >(col));
            temporal->sgt->v=t;
            temporal->sgt->ant=temporal;
        }
    }
}
 
