#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int comparador_int(int* primero, int* segundo){
  return *primero-*segundo;
}

void puedoCrearYDestruirUnABB(){
  abb_t* a = NULL;

  pa2m_afirmar((a=abb_crear((abb_comparador) comparador_int)), "Crear un ABB devuelve un ABB");
  pa2m_afirmar(abb_vacio(a), "ABB se crea vacio")
  pa2m_afirmar(abb_tamanio(a)==0, "ABB tiene 0 elementos");

  abb_destruir(a);
}


void dadaUnABBVacio_Puedorealizaroperaciones(){
  abb_t* a = abb_crear((abb_comparador) comparador_int);

  int numeros[5] = {0,1,2,3,4};

  pa2m_afirmar(abb_vacio(a), "ABB se crea vacio")
  pa2m_afirmar(abb_tamanio(a)==0, "ABB tiene 0 elementos");

  pa2m_afirmar(abb_insertar(a, &(numeros[0]))==a, "Puedo insertar un elemento en un ABB vacío");
  abb_destruir(a);

}

int main(){
  pa2m_nuevo_grupo("Pruebas de ABB");

  pa2m_nuevo_grupo("Pruebas de creacion y destruccion");
  puedoCrearYDestruirUnABB();

  pa2m_nuevo_grupo("Con un ABB vacío puedo operar");
  dadaUnABBVacio_Puedorealizaroperaciones();

  return pa2m_mostrar_reporte();
}
