#ifndef FILA_RALA_H
#define FILA_RALA_H
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
    T retorno;
    shared_ptr< elem< T > > iterando = inicio;
    if( c >= cc || c < 0 ){
        throw out_of_range("Indice no válido.");
    } else {
        while( iterando && iterando->c != c )
            iterando = iterando->sgt;
    }
    if( iterando )
        retorno = iterando->v;
    return retorno;
}

template < typename T >
T& fila_rala< T >::operator[](int c) throw (out_of_range) {
    shared_ptr< elem< T > > iterando = inicio;
    if ( c >= this->cc || c < 0 ){
        throw out_of_range( "Indice no válido." );
    }else{
        while( iterando && iterando->c != c )
            iterando = iterando->sgt;
        if( !iterando )
            throw out_of_range( "La posición c no existe." );
        else
            return iterando->v;
    }
}

template < typename T >
void fila_rala< T >::insertar(int c, const T& t) throw (out_of_range) {
    shared_ptr<elem<T>> iterador = inicio;
    if( c < 0 || c >= cc ){
        throw out_of_range( "El posición c es inválida!" );
    } else {
        if( !inicio ){
            inicio = shared_ptr<elem<T>>( new elem<T>(c) );
            inicio->v = t;
        } else {
            bool yaExiste = false;
            shared_ptr<elem<T>> ant = iterador;
            while( iterador && iterador->c <= c ){
                ant = iterador;
                if( iterador->c == c )
                    yaExiste = true;
                iterador = iterador->sgt;
            }
            if( !yaExiste ){
                if( inicio->c > c ){
                    inicio = shared_ptr<elem<T>>( new elem<T>(c) );
                    inicio->v = t;
                    inicio->sgt = ant;
                    ant->ant = inicio;
                } else {
                    ant->sgt = shared_ptr<elem<T>>( new elem<T>(c) );
                    ant->sgt->v = t;
                    ant->sgt->ant = ant;
                    if( iterador )
                        ant->sgt->sgt = iterador;
                }
            } else {
                throw out_of_range( "La columna c ya existe!" );
            }
        }
    }
//    int cl=c;
//    bool entro=false;
//    bool ultim=false;
//    int bandCas=0;
//    //EL QUE VA RECORRIENDO LA FILA PARA COMPARAR
//    shared_ptr<elem<T>>iterando;
//    //GUARDA LA CADENA PARA LUEGO VOLVER A UNIRLA
//    shared_ptr<elem<T>>temporal;
//    //CASO #1 SALE DEL RANGO
//    if(cl>=this->cc){
//        throw std::out_of_range("fila se salió del rango");
//        bandCas=1;
//    }
//    //CASO #2 LA FILA ESTA VACÍA
//    else if (inicio==0){
//        inicio=shared_ptr<elem<T>>(new elem<T>(cl));
//        inicio->v=t;
//        bandCas=1;
//    }
//    //CASO #3 DEBE SER EL PRIMER ELEMENTO
//    else if(inicio->c>cl){
//        temporal=inicio;
//        inicio=shared_ptr<elem<T>>(new elem<T>(cl));
//        inicio->v=t;
//        inicio->sgt=temporal;
//        temporal->ant=inicio;
//        bandCas=1;
//    }
//    else if(bandCas==0){
//        iterando=inicio;
//        while(iterando!=nullptr){
//            //CASO #4 LA COLUMNA YA EXISTE
//            if(cl==iterando->c){
//               throw std::out_of_range("La columna ya existe");
//            }else{
//                if(cl>iterando->c){
//                    temporal=iterando;
//                    iterando=iterando->sgt;
//                    entro=true;
//                    if(iterando==nullptr){ //CASO #5 ÚLTIMO ELEMENTO
//                        ultim=true;
//                    }
//                }
//                else if(cl<iterando->c && entro==true){
//                    iterando=nullptr;
//                }
//            }
//        }
//        if(ultim==false){ //AQUÍ SE AGREGA EN MEDIO
//            iterando=temporal->sgt;
//            temporal->sgt=shared_ptr<elem<T>>(new elem<T>(cl));
//            temporal->sgt->v=t;
//            temporal->sgt->ant=temporal;
//            temporal->sgt->sgt=iterando;
//            iterando->ant=temporal->sgt;
//        }else if(ultim==true){ //AQUÍ SE AGREGA AL FINAL
//            temporal->sgt=shared_ptr<elem<T>>(new elem<T>(cl));
//            temporal->sgt->v=t;
//            temporal->sgt->ant=temporal;
//        }
//    }
}
 
#endif