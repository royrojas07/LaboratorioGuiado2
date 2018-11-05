int cl=c;
    bool entro=false;
    bool ultim=false;
    int bandCas=0;
    //EL QUE VA RECORRIENDO LA FILA PARA COMPARAR
    shared_ptr<elem<T>>iterando;
    //GUARDA LA CADENA PARA LUEGO VOLVER A UNIRLA
    shared_ptr<elem<T>>temporal;
    //CASO #1 SALE DEL RANGO
    if(cl>=this->cc){
        throw std::out_of_range("fila se salió del rango");
        bandCas=1;
    }
    //CASO #2 LA FILA ESTA VACÍA
    else if (inicio==0){
        inicio=shared_ptr<elem<T>>(new elem<T>(cl));
        inicio->v=t;
        bandCas=1;
    }
    //CASO #3 DEBE SER EL PRIMER ELEMENTO
    else if(inicio->c>cl){
        temporal=inicio;
        inicio=shared_ptr<elem<T>>(new elem<T>(cl));
        inicio->v=t;
        inicio->sgt=temporal;
        temporal->ant=inicio;
        bandCas=1;
    }
    else if(bandCas==0){
        iterando=inicio;
        while(iterando!=nullptr){
            //CASO #4 LA COLUMNA YA EXISTE
            if(cl==iterando->c){
               throw std::out_of_range("La columna ya existe");
            }else{
                if(cl>iterando->c){
                    temporal=iterando;
                    iterando=iterando->sgt;
                    entro=true;
                    if(iterando==nullptr){ //CASO #5 ÚLTIMO ELEMENTO
                        ultim=true;
                    }
                }
                else if(cl<iterando->c && entro==true){
                    iterando=nullptr;
                }
            }
        }
        if(ultim==false){ //AQUÍ SE AGREGA EN MEDIO
            iterando=temporal->sgt;
            temporal->sgt=shared_ptr<elem<T>>(new elem<T>(cl));
            temporal->sgt->v=t;
            temporal->sgt->ant=temporal;
            temporal->sgt->sgt=iterando;
            iterando->ant=temporal->sgt;
        }else if(ultim==true){ //AQUÍ SE AGREGA AL FINAL
            temporal->sgt=shared_ptr<elem<T>>(new elem<T>(cl));
            temporal->sgt->v=t;
            temporal->sgt->ant=temporal;
        }
    }
