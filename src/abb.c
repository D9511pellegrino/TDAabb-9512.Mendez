#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t* abb_crear(abb_comparador comparador){
    if(!comparador) return NULL;

    abb_t* nuevo_abb = calloc(1,sizeof(abb_t));
    if(!nuevo_abb) return NULL;

    nuevo_abb->nodo_raiz = NULL;
    nuevo_abb->comparador = comparador;
    nuevo_abb->tamanio = 0;

    return nuevo_abb;
}

nodo_abb_t* abb_insertar_recursivo(nodo_abb_t* nodo_padre, nodo_abb_t* nuevo_nodo, abb_comparador comparador){
    if(!nodo_padre || !nuevo_nodo || !comparador) return NULL;

    int comparacion = comparador(nuevo_nodo->elemento, nodo_padre->elemento);

    if(comparacion<=0){
        if(!nodo_padre->izquierda){
            nodo_padre->izquierda = nuevo_nodo;
            return nodo_padre->izquierda;
        }
        else return abb_insertar_recursivo(nodo_padre->izquierda, nuevo_nodo, comparador);
    }
    else if(comparacion>0){
        if(!nodo_padre->derecha){
          nodo_padre->derecha = nuevo_nodo;
          return nodo_padre->derecha;
        }
        else return abb_insertar_recursivo(nodo_padre->derecha, nuevo_nodo, comparador);
    }

    return NULL; 

}

abb_t* abb_insertar(abb_t* arbol, void* elemento){
    if(!arbol) return NULL;

    nodo_abb_t* nuevo_nodo = calloc(1,sizeof(nodo_abb_t));
    if(!nuevo_nodo) return NULL;

    nuevo_nodo->elemento = elemento;
    nuevo_nodo->izquierda = NULL;
    nuevo_nodo->derecha = NULL;

    if(arbol->tamanio == 0){
        arbol->nodo_raiz = nuevo_nodo;
    }
    else arbol->nodo_raiz = abb_insertar_recursivo(arbol->nodo_raiz, nuevo_nodo, arbol->comparador);
    if(!arbol->nodo_raiz) return NULL;

    arbol->tamanio++;
    return arbol;
}


void* abb_quitar(abb_t* arbol, void *elemento){
    if(!arbol) return NULL;




}

void* abb_buscar_recursivo(nodo_abb_t* nodo_padre, void* elemento, abb_comparador comparador){
  if(!nodo_padre) return NULL;

  int comparacion = comparador(elemento, nodo_padre->elemento);

    if(comparacion==0) return nodo_padre->elemento;
    else if(comparacion<0){
        if(!nodo_padre->izquierda) return NULL;
        else return abb_buscar_recursivo(nodo_padre->izquierda, elemento, comparador);
    }
    else if(comparacion>0){
        if(!nodo_padre->derecha) return NULL;
        else return abb_buscar_recursivo(nodo_padre->derecha, elemento, comparador);
    }

    return NULL; 


}

void* abb_buscar(abb_t* arbol, void* elemento){
  if(!arbol) return NULL;

  int comparacion = comparador(elemento, arbol->nodo_raiz->elemento);

  if(comparacion==0) return nodo_raiz->elemento;
    else if(comparacion<0){
        if(!nodo_raiz->izquierda) return NULL;
        else return abb_buscar_recursivo(nodo_raiz->izquierda, elemento, arbol->comparador);
    }
    else if(comparacion>0){
        if(!nodo_raiz->derecha) return NULL;
        else return abb_buscar_recursivo(nodo_raiz->derecha, elemento, arbol->comparador);
    }

    return NULL;
}

bool abb_vacio(abb_t* arbol){
  return (!arbol || arbol->tamanio==0);
}

size_t abb_tamanio(abb_t *arbol){
  if(!arbol) return 0;
  return arbol->tamanio;
}

void abb_destruir(abb_t *arbol){
  if(!arbol) return;
  while(!abb_vacio(arbol)) abb_quitar(arbol, arbol->nodo_raiz->elemento);
  free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){
    if(!arbol || !destructor) return;

    void* elemento_eliminar = NULL;

    while(!abb_vacio(arbol)){
        elemento_eliminar = abb_quitar(arbol, arbol->nodo_raiz->elemento);
        destructor(elemento_eliminar);
    }
    free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
  return 0;
}

size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){
  return 0;
}
