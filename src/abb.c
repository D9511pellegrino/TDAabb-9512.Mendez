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
    
    if(arbol->tamanio == 0){
        arbol->nodo_raiz = nuevo_nodo;
        nuevo_nodo->izquierda = NULL;
        nuevo_nodo->derecha = NULL;
    }
    else arbol->nodo_raiz = abb_insertar_recursivo(arbol->nodo_raiz, nuevo_nodo, arbol->comparador);
    if(!arbol->nodo_raiz) return NULL;

    arbol->tamanio++;
    return arbol;
}


void* abb_quitar(abb_t* arbol, void *elemento){
    if(!arbol || abb_vacio(arbol)) return NULL;

    nodo_abb_t* nodo_padre = arbol->nodo_raiz;
    nodo_abb_t* nodo_quitar = NULL;

    if(arbol->comparador(nodo_padre->elemento, elemento)==0){

    }


    return elemento;


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
  if(!arbol || abb_vacio(arbol)) return NULL;

  int comparacion = arbol->comparador(elemento, arbol->nodo_raiz->elemento);

  if(comparacion==0) return arbol->nodo_raiz->elemento;
    else if(comparacion<0){
        if(!arbol->nodo_raiz->izquierda) return NULL;
        else return abb_buscar_recursivo(arbol->nodo_raiz->izquierda, elemento, arbol->comparador);
    }
    else if(comparacion>0){
        if(!arbol->nodo_raiz->derecha) return NULL;
        else return abb_buscar_recursivo(arbol->nodo_raiz->derecha, elemento, arbol->comparador);
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

//iterador interno recursivo de manera postorden
void abb_con_cada_elemento_postorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), void* aux, bool* seguir_recorriendo){
  if(!(*seguir_recorriendo) || !nodo) return 0;

  size_t contador = 0;

  if(nodo->izquierda && *seguir_recorriendo)
    contador+=abb_con_cada_elemento_postorden(nodo->izquierda, funcion, aux, seguir_recorriendo);
  
  if(nodo->derecha && *seguir_recorriendo)
    abb_con_cada_elemento_postorden(nodo->derecha, funcion, aux, seguir_recorriendo);
  
  if(*seguir_recorriendo){
    *seguir_recorriendo = funcion(nodo->elemento, extra);
    contador++;
  }    
}

//iterador interno recursivo de manera inorden
size_t abb_con_cada_elemento_inorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), void* aux, bool* seguir_recorriendo){
  if(!(*seguir_recorriendo) || !nodo) return 0;

  size_t contador = 0;

  if(nodo->izquierda && *seguir_recorriendo)
      contador+=abb_con_cada_elemento_inorden(nodo->izquierda, funcion, aux, seguir_recorriendo);
  
  if(*seguir_recorriendo){
    *seguir_recorriendo = funcion(nodo->elemento, aux);
    contador++;
  }

  if(nodo->derecha && *seguir_recorriendo)
      contador+=abb_con_cada_elemento_inorden(nodo->derecha, funcion, aux, seguir_recorriendo);

  return contador;
}

//iterador interno recursivo de manera preorden
size_t abb_con_cada_elemento_preorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), void* extra, bool* seguir_recorriendo){
  if(!(*corte) || !nodo) return 0; 

  size_t contador = 0;

  *corte = funcion(nodo->elemento, extra);
  contador++;    
  
  if(nodo->izquierda)
    contador+=abb_con_cada_elemento_preorden(nodo->izquierda, funcion, extra, corte);
  if(nodo->derecha)
    contador+=abb_con_cada_elemento_preorden(nodo->derecha, funcion, extra, corte);

  return contador;
}


size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
    if(!arbol || !recorrido || !funcion) return 0;

    bool* seguir_recorriendo 
    *seguir_recorriendo = true;

    switch(recorrido){
        case INORDEN:
            return abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, seguir_recorriendo);
        case PREORDEN:
            return abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, seguir_recorriendo);
        case POSTORDEN:
            return abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, seguir_recorriendo);
        default:
            return 0;
    }
}

size_t arbol_recorrido_postorden_recursivo(nodo_abb_t* nodo, void** array, int tamanio_array, int* posarray){ 
  int cant = 0; 
  if(nodo->izquierda)
    cant += arbol_recorrido_postorden_rec(nodo->izquierda, array, tamanio_array, posarray);
  if(nodo->derecha)
    cant += arbol_recorrido_postorden_rec(nodo->derecha, array, tamanio_array, posarray);
  if(*posarray < tamanio_array){
    array[*posarray] = nodo->elemento;
    cant += 1;
          *posarray += 1;
  } 
  return cant;
}


size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){
  return 0;
}
