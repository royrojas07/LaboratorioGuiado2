/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alan.calderon
 *
 * Created on October 22, 2018, 6:00 PM
 */

#include <iostream>
#include <exception>
using namespace std;

#include "matriz_rala.h"
#include "itr_matriz_rala.h"

// "%TEST_FAILED% testname = testMatriz_rala() message = "

void testMatriz_rala() { // pruebas sobre constructor estándar
    // detecta dimensiones incorrectas:
    matriz_rala< int > mr; // se crea una matriz_rala de 20x10
    if (mr.obtCF() != 20 || mr.obtCC() != 10) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = dimensiones diferentes de 20x10" << std::endl;
    }

    // detecta contenido incorrecto, algún elemento diferente de cero
    const matriz_rala< int >& mr_alias = mr; // se crea una referencia const para poder invocar los operator[] const
    bool no_cero = true;
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 10; j++)
            if (0 != mr_alias[i][j])
                no_cero = false;
    if (!no_cero)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no todos los elementos son cero" << std::endl;


    // pruebas de generación de excepciones:
    bool detecto_excepcion = false;
    try {
        mr[0][0] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[0][0] = 1;" << std::endl;
    else detecto_excepcion = false;

    try {
        mr[20][0] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[20][0] = 1;" << std::endl;
    else detecto_excepcion = false;

    try {
        mr[0][10] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[0][10] = 1;" << std::endl;
    else detecto_excepcion = false;
}

void testMatriz_rala2() {
    matriz_rala< int > mr(5, 10); // crea una matriz_rala de 5x10

    // detecta dimensiones incorrectas:
    if (mr.obtCF() != 5 || mr.obtCC() != 10) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala2() message = dimensiones diferentes de 5x10" << std::endl;
    }

    // detecta contenido incorrecto, algún elemento diferente de cero
    const matriz_rala< int >& mr_alias = mr; // se crea una referencia const para poder invocar los operator[] const
    bool no_cero = true;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 10; j++)
            if (mr_alias[i][j] != 0)
                no_cero = false;
    if (!no_cero) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala2() message = no todos los elementos son cero" << std::endl;
    }

    // pruebas de generación de excepciones:
    bool detecto_excepcion = false;
    try {
        mr[0][0] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[0][0] = 1;" << std::endl;
    else detecto_excepcion = false;

    try {
        mr[0][0] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[20][0] = 1;" << std::endl;
    else detecto_excepcion = false;

    try {
        mr[0][10] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[0][10] = 1;" << std::endl;
    else detecto_excepcion = false;
}

void testMatriz_rala3() {
    matriz_rala< int > mr_orig;
    matriz_rala< int > mr(mr_orig);

    // detecta dimensiones incorrectas:
    if (mr.obtCF() != mr_orig.obtCF() || mr.obtCC() != mr_orig.obtCC()) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala3() message = dimensiones diferentes de matriz original" << std::endl;
    }

    // detecta contenido incorrecto, algún elemento diferente de cero
    const matriz_rala< int >& mr_alias = mr; // se crea una referencia const para poder invocar los operator[] const
    bool no_cero = true;
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 10; j++)
            if (mr_alias[i][j] != 0)
                no_cero = false;
    if (!no_cero) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala3() message = no todos los elementos son cero" << std::endl;
    }

    // pruebas de generación de excepciones:
    bool detecto_excepcion = false;
    try {
        mr[0][0] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[0][0] = 1;" << std::endl;
    else detecto_excepcion = false;

    try {
        mr[20][0] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[20][0] = 1;" << std::endl;
    else detecto_excepcion = false;

    try {
        mr[0][10] = 1;
    } catch (out_of_range oor) {
        detecto_excepcion = true;
    }
    if (!detecto_excepcion)
        std::cout << "%TEST_FAILED% testname = testMatriz_rala() message = no detecto excepcion en mr[0][10] = 1;" << std::endl;
    else detecto_excepcion = false;
}

void testMatriz_rala_insertar() {
    matriz_rala< int > mr; // se crea una matriz_rala de 20x10

    // se agregan elementos mediante fila_rala< int >::insertar(...) y se comprueba su correcto almacenamiento:
    try {
        mr[0].insertar(0, 1);
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar mr[0].insertar(0, 1)" << std::endl;
    }

    try {
        mr[19].insertar(9, 99);
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar mr[19].insertar(9, 99)" << std::endl;
    }

    try {
        mr[0].insertar(5, 55);
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar mr[0].insertar(5, 55)" << std::endl;
    }

    try {
        mr[19].insertar(5, 595);
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar mr[19].insertar(5, 595)" << std::endl;
    }

    // verificación del correcto almacenamiento:
    const matriz_rala< int > mr_alias = mr; // se crea una constante
    try {
        if (mr_alias[0][0] != 1)
            std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = mr[0][0] != 1" << std::endl;
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar mr[0][0] != 1" << std::endl;
    }

    try {
        if (mr_alias[19][9] != 99)
            std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = mr_alias[19][9] != 99" << std::endl;
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar mr_alias[19][9] != 99" << std::endl;
    }

    try {
        if (mr_alias[0][5] != 55)
            std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = mr_alias[0][5] != 55" << std::endl;
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar mr_alias[0][5] != 55" << std::endl;
    }

    try {
        if (mr_alias[19][5] != 595)
            std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = mr_alias[19][5] != 595" << std::endl;
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar mr_alias[19][5] != 595" << std::endl;
    }

    // detecta contenido incorrecto en todos los demás elementos de la matriz
    bool no_cero = true;
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 10; j++)
            if (mr_alias[i][j] != 0)
                if (((i == 0) && (j == 0)) || ((i == 0) && (j == 5)) || ((i == 19) && (j == 5)) || ((i == 19) && (j == 9)))
                    no_cero = true;
                else no_cero = false;
    if (!no_cero) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala3() message = no todos los elementos son cero" << std::endl;
    }
}

void testItr_matriz_rala() {
    matriz_rala< int > mr; // se crea una matriz_rala de 20x10

    // se agregan elementos mediante fila_rala< int >::insertar(...) y se comprueba su correcto almacenamiento:
    try {
        mr[0].insertar(0, 1);
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testItr_matriz_rala() message = excepcion al intentar mr[0].insertar(0, 1)" << std::endl;
    }

    try {
        mr[19].insertar(9, 99);
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testItr_matriz_rala() message = excepcion al intentar mr[19].insertar(9, 99)" << std::endl;
    }

    try {
        mr[0].insertar(5, 55);
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testItr_matriz_rala() message = excepcion al intentar mr[0].insertar(5, 55)" << std::endl;
    }

    try {
        mr[19].insertar(5, 595);
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testItr_matriz_rala() message = excepcion al intentar mr[19].insertar(5, 595)" << std::endl;
    }

    cout << "valores originales de la matriz: " << endl;
    for (matriz_rala< int >::const_iterator itr = mr.begin(); itr != mr.end(); ++itr)
        cout << "fila: " << itr.obtFila() << " columna: " << itr.obtColumna() << " valor: " << *itr << endl;

    // se modifican los valores agregados:
    try {
        mr[0][0] = 11;
        mr[0][5] = 66;
        mr[19][5] = 696;
        mr[19][9] = 88;
    } catch (out_of_range oor) {
        std::cout << "%TEST_FAILED% testname = testMatriz_rala_insertar() message = excepcion al intentar modificar --> " << oor.what() << std::endl;
    }

    const matriz_rala< int >& mr_alias = mr; // se crea una referencia const para invocar los observadores
    if ((mr_alias[0][0] != 11)||(mr_alias[0][5] != 66)||(mr_alias[19][5] != 696)||(mr_alias[19][9] != 88))
        std::cout << "%TEST_FAILED% testname = testItr_matriz_rala() message = falló alguna modificación" << std::endl;
        
    cout << "valores modificados de la matriz: " << endl;
    for (matriz_rala< int >::const_iterator itr = mr.begin(); itr != mr.end(); ++itr)
        cout << "fila: " << itr.obtFila() << " columna: " << itr.obtColumna() << " valor: " << *itr << endl;
}



int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTED% pruebas" << std::endl;

    std::cout << "%TEST_STARTED% testMatriz_rala" << std::endl;
    testMatriz_rala();
    std::cout << "%TEST_FINISHED% testMatriz_rala" << std::endl;

    std::cout << "%TEST_STARTED% testMatriz_rala2" << std::endl;
    testMatriz_rala2();
    std::cout << "%TEST_FINISHED% testMatriz_rala2" << std::endl;

    std::cout << "%TEST_STARTED% testMatriz_rala3" << std::endl;
    testMatriz_rala3();
    std::cout << "%TEST_FINISHED% testMatriz_rala3" << std::endl;

    std::cout << "%TEST_STARTED% testMatriz_rala_insertar" << std::endl;
    testMatriz_rala_insertar();
    std::cout << "%TEST_FINISHED% testMatriz_rala_insertar" << std::endl;

    std::cout << "%TEST_STARTED% testItr_matriz_rala" << std::endl;
    testItr_matriz_rala();
    std::cout << "%TEST_FINISHED% testItr_matriz_rala" << std::endl;

    std::cout << "%SUITE_FINISHED% pruebas" << std::endl;
    
    return (EXIT_SUCCESS);
}
