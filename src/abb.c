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

nodo_abb_t* abb_extraer_nodo_recursivo(nodo_abb_t* nodo_padre, void* elemento, abb_comparador comparador, nodo_abb_t** nodo_extraer){

    int comparacion = comparador(elemento, nodo_padre->elemento);


    if(comparacion == 0){
      *nodo_extraer = nodo_padre;
      if(nodo_padre->izquierda && nodo_padre->derecha){
        //TENGO 2 HIJOS
      }
      else{
        //TENGO UN HIJO
        nodo_abb_t* hijo = nodo_padre->derecha? nodo_padre->derecha: nodo_padre->izquierda;
        free(nodo_padre);
        return hijo;
        }
    }
    else if(comparacion<0){
        nodo_padre->izquierda = abb_extraer_nodo_recursivo(nodo_padre->izquierda, elemento, comparador, nodo_extraer);
    }
    else if(comparacion>0){
        nodo_padre->derecha = abb_extraer_nodo_recursivo(nodo_padre->derecha, elemento, comparador, nodo_extraer);
    }

    return NULL; 

}

void* abb_quitar(abb_t* arbol, void *elemento){
    if(!arbol || abb_vacio(arbol)) return NULL;

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;
    nodo_abb_t* nodo_quitar = NULL;
    void* elemento_quitar = NULL;

    bool elemento_encontrado = false;

    while(!elemento_encontrado){

      if(arbol->comparador(nodo_actual->elemento, elemento)==0){
        nodo_quitar = nodo_actual;
        elemento_quitar = nodo_quitar->elemento;
        free(nodo_quitar);
        return elemento_quitar;
      }
      else if(arbol->comparador(nodo_actual->elemento, elemento)<0){

      }
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

void abb_destruir_recursivo(nodo_abb_t* nodo_padre, void (*destructor)(void *)){
  if(nodo_padre){
    abb_destruir_recursivo(nodo_padre->izquierda, destructor);
    abb_destruir_recursivo(nodo_padre->derecha, destructor);
    if(destructor) destructor(nodo_padre->elemento);
    free(nodo_padre);
  }
}

void abb_destruir(abb_t *arbol){
    if(arbol){
        abb_destruir_recursivo(arbol->nodo_raiz, NULL);
        free(arbol);
  }
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){
    if(arbol){
        abb_destruir_recursivo(arbol->nodo_raiz, destructor);
        free(arbol);
    }
}

//iterador interno recursivo de manera postorden
size_t abb_con_cada_elemento_postorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), void* aux, bool* seguir_recorriendo){
  if(!(*seguir_recorriendo) || !nodo) return 0;

  size_t contador = 0;

  if(nodo->izquierda && *seguir_recorriendo)
    contador+=abb_con_cada_elemento_postorden(nodo->izquierda, funcion, aux, seguir_recorriendo);
  
  if(nodo->derecha && *seguir_recorriendo)
    abb_con_cada_elemento_postorden(nodo->derecha, funcion, aux, seguir_recorriendo);
  
  if(*seguir_recorriendo){
    *seguir_recorriendo = funcion(nodo->elemento, aux);
    contador++;
  }
  return contador;    
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
size_t abb_con_cada_elemento_preorden(nodo_abb_t* nodo, bool (*funcion)(void*,void*), void* aux, bool* seguir_recorriendo){
  if(!(*seguir_recorriendo) || !nodo) return 0; 

  size_t contador = 0;

  if(seguir_recorriendo){
    *seguir_recorriendo = funcion(nodo->elemento, aux);
    contador++;    
  }

  if(nodo->izquierda || seguir_recorriendo)
    contador+=abb_con_cada_elemento_preorden(nodo->izquierda, funcion, aux, seguir_recorriendo);
  if(nodo->derecha || seguir_recorriendo)
    contador+=abb_con_cada_elemento_preorden(nodo->derecha, funcion, aux, seguir_recorriendo);

  return contador;
}


size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
    if(!arbol || !recorrido || !funcion) return 0;

    bool seguir_recorriendo = true;

    switch(recorrido){
        case INORDEN:
            return abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, &seguir_recorriendo);
        case PREORDEN:
            return abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, &seguir_recorriendo);
        case POSTORDEN:
            return abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, &seguir_recorriendo);
        default:
            return 0;
    }
}

/*size_t arbol_recorrido_postorden_recursivo(nodo_abb_t* nodo, void** array, int tamanio_array, int* posarray){ 
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

size_t arbol_recorrido_inorden_recursivo(nodo_abb_t* nodo, void** array, int tamanio_array, int* posarray){ 
  int cant = 0; 
  if(nodo->izquierda)
    cant += arbol_recorrido_inorden_rec(nodo->izquierda, array, tamanio_array, posarray);
  
  if(*posarray < tamanio_array){
    array[*posarray] = nodo->elemento;
    cant += 1;
          *posarray += 1;
  } 
  if(nodo->derecha)
    cant += arbol_recorrido_inorden_rec(nodo->derecha, array, tamanio_array, posarray);

  return cant;
}

size_t arbol_recorrido_preorden_recursivo(nodo_abb_t* nodo, void** array, int tamanio_array, int* posarray){ 
  int cant = 0; 
  if(*posarray < tamanio_array){
    array[*posarray] = nodo->elemento;
    cant += 1;
          *posarray += 1;
  }
  if(nodo->izquierda)
    cant += arbol_recorrido_preorden_rec(nodo->izquierda, array, tamanio_array, posarray);
  if(nodo->derecha)
    cant += arbol_recorrido_preorden_rec(nodo->derecha, array, tamanio_array, posarray);
  return cant;
}*/


size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){
    if(!arbol || !recorrido) return 0;

    bool seguir_recorriendo = true;

    switch(recorrido){
        case INORDEN:
            return abb_con_cada_elemento_inorden(arbol->nodo_raiz, NULL, NULL, &seguir_recorriendo);
        case PREORDEN:
            return abb_con_cada_elemento_preorden(arbol->nodo_raiz, NULL, NULL, &seguir_recorriendo);
        case POSTORDEN:
            return abb_con_cada_elemento_postorden(arbol->nodo_raiz, NULL, NULL, &seguir_recorriendo);
        default:
            return 0;
    }
}