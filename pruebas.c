#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int comparador_int(int* primero, int* segundo){
  return *primero-*segundo;
}

void puedoCrearUnABB(){
  abb_t* a = NULL;

  pa2m_afirmar((a=abb_crear((abb_comparador) comparador_int)), "Crear un ABB devuelve un ABB");
  pa2m_afirmar(abb_vacio(a), "ABB se crea vacio")
  pa2m_afirmar(abb_tamanio(a)==0, "ABB tiene 0 elementos");
  pa2m_afirmar(!abb_buscar(a, NULL), "El elemento raiz es NULL");

  abb_destruir(a);
}


void dadoUnABB_PuedoInsertar(){
  abb_t* a = abb_crear((abb_comparador) comparador_int);

  int numeros[5] = {0,1,2,3,4};

  pa2m_afirmar(abb_vacio(a), "ABB se crea vacio")
  pa2m_afirmar(abb_tamanio(a)==0, "ABB tiene 0 elementos");
  
  pa2m_afirmar(abb_insertar(a, &(numeros[2]))==a, "Puedo insertar un elemento en un ABB vacío");
  pa2m_afirmar(abb_buscar(a, &(numeros[2]))==&(numeros[2]), "El elemento insertado está en el ABB");
  pa2m_afirmar(abb_tamanio(a)==1, "El tamaño del ABB es 1");

  pa2m_afirmar(abb_insertar(a, &(numeros[1]))==a, "Puedo insertar un elemento menor al anterior");
  pa2m_afirmar(abb_buscar(a, &(numeros[1]))==&(numeros[1]), "El elemento insertado está en el ABB");
  pa2m_afirmar(abb_tamanio(a)==2, "El tamaño del ABB es 2");

  //abb_destruir(a);

}

void dadoUnABBconElementos_Puedoquitar(){

}


void puedoRecorrerunABB_INORDEN(){

}

void puedoRecorrerunABB_POSTORDEN(){

}

void puedoRecorrerunABB_PREORDEN(){

}

int main(){

  pa2m_nuevo_grupo("Pruebas de creacion ABB");
  puedoCrearUnABB();

  pa2m_nuevo_grupo("Pruebas de insercion");
  dadoUnABB_PuedoInsertar();

  pa2m_nuevo_grupo("Pruebas de borrado");
  dadoUnABBconElementos_Puedoquitar();

  pa2m_nuevo_grupo("Pruebas de recorrido inorden");
  puedoRecorrerunABB_INORDEN();

  pa2m_nuevo_grupo("Pruebas de recorrido postorden");
  puedoRecorrerunABB_POSTORDEN();

  pa2m_nuevo_grupo("Pruebas de recorrido preorden");
  puedoRecorrerunABB_PREORDEN();



  return pa2m_mostrar_reporte();
}
