#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t* abb_crear(abb_comparador comparador)
{
	if(!comparador) return NULL;

	abb_t* nuevo_abb = calloc(1,sizeof(abb_t));
	if(!nuevo_abb) return NULL;

	//nuevo_abb->nodo_raiz = NULL;
	nuevo_abb->comparador = comparador;
	//nuevo_abb->tamanio = 0;

	return nuevo_abb;
}

nodo_abb_t* abb_insertar_recursivo(nodo_abb_t* nodo_padre, void* elemento, abb_comparador comparador)
{
	if(!comparador) return NULL;

	if(!nodo_padre){
	nodo_abb_t* nuevo_nodo = calloc(1,sizeof(nodo_abb_t));
	if(!nuevo_nodo) return NULL;

	nuevo_nodo->elemento = elemento;
	//nuevo_nodo->izquierda = NULL;
	//nuevo_nodo->derecha = NULL;
	return nuevo_nodo;
}

	int comparacion = comparador(elemento, nodo_padre->elemento);

	if(comparacion<=0)
	nodo_padre->izquierda = abb_insertar_recursivo(nodo_padre->izquierda, elemento, comparador);
	else if(comparacion>0)
	nodo_padre->derecha = abb_insertar_recursivo(nodo_padre->derecha, elemento, comparador);

	return nodo_padre; 
}

abb_t* abb_insertar(abb_t* arbol, void* elemento){
	if(!arbol) return NULL;

	arbol->nodo_raiz = abb_insertar_recursivo(arbol->nodo_raiz, elemento, arbol->comparador);
	if(!arbol->nodo_raiz) return NULL;

	arbol->tamanio++;
	return arbol;
}

nodo_abb_t* abb_extraer_predecesor_inorden(nodo_abb_t* nodo_padre)
{
	if(nodo_padre){
		nodo_abb_t* nodo_actual = nodo_padre;
		while(nodo_actual->derecha){
			nodo_padre = nodo_actual;
			nodo_actual = nodo_actual->derecha;
		}
		nodo_abb_t* nodo_extraer = nodo_actual;

		if(nodo_actual->izquierda) nodo_padre->derecha = nodo_actual->izquierda;
		else nodo_padre->derecha = NULL;

		return nodo_extraer;
	}

	return NULL; 
}

void* abb_quitar_recursivo(nodo_abb_t* nodo_actual, nodo_abb_t* nodo_padre, void* elemento, abb_comparador comparador, bool* se_elimino)
{
	if(!nodo_actual) return NULL;
	void* elemento_quitar = NULL;
	
	
	int comparacion = comparador(elemento, nodo_actual->elemento);
	
	if(comparacion==0){ 
	elemento_quitar = nodo_actual->elemento;

	if(nodo_actual->derecha && nodo_actual->izquierda){
		nodo_abb_t* predecesor = abb_extraer_predecesor_inorden(nodo_actual->izquierda);
		if(predecesor!=nodo_actual->izquierda) 
		predecesor->izquierda = nodo_actual->izquierda;
		predecesor->derecha = nodo_actual->derecha;
	
		if(nodo_actual == nodo_padre->derecha) nodo_padre->derecha = predecesor;
		else nodo_padre->izquierda = predecesor;
		free(nodo_actual);
	}
	else{
		nodo_abb_t* hijo = nodo_actual->derecha? nodo_actual->derecha: nodo_actual->izquierda;

		if(nodo_actual == nodo_padre->derecha) nodo_padre->derecha = hijo;
		else nodo_padre->izquierda = hijo;

		free(nodo_actual);
	}
	*se_elimino = true;
	}
	else if(comparacion<0)
	return abb_quitar_recursivo(nodo_actual->izquierda, nodo_actual, elemento, comparador, se_elimino);
	else return abb_quitar_recursivo(nodo_actual->derecha, nodo_actual, elemento, comparador, se_elimino);
	return elemento_quitar;
}

void* abb_quitar(abb_t* arbol, void *elemento){
	if(!arbol || abb_vacio(arbol) || !arbol->nodo_raiz) return NULL;

	nodo_abb_t* nodo_actual = arbol->nodo_raiz;
	if(!nodo_actual) return NULL;
	void* elemento_quitar = NULL;
	
	int comparacion = arbol->comparador(elemento, nodo_actual->elemento);
	bool se_elimino = false;

	if(comparacion==0){ 
		elemento_quitar = nodo_actual->elemento;
		if(nodo_actual->derecha && nodo_actual->izquierda){
			nodo_abb_t* predecesor = abb_extraer_predecesor_inorden(nodo_actual->izquierda);
			if(predecesor!=nodo_actual->izquierda) 
			predecesor->izquierda = nodo_actual->izquierda;
			predecesor->derecha = nodo_actual->derecha;
			arbol->nodo_raiz = predecesor;
			free(nodo_actual);
		}
		else{
			nodo_abb_t* hijo = nodo_actual->derecha? nodo_actual->derecha:nodo_actual->izquierda;
			arbol->nodo_raiz = hijo;
			if(!nodo_actual->derecha && !nodo_actual->izquierda) arbol->nodo_raiz =NULL;
			free(nodo_actual);
		}
		se_elimino = true;
	}
	else if(comparacion<0)
	elemento_quitar = abb_quitar_recursivo(nodo_actual->izquierda, nodo_actual, elemento, arbol->comparador, &se_elimino);
	else 
	elemento_quitar = abb_quitar_recursivo(nodo_actual->derecha, nodo_actual, elemento, arbol->comparador, &se_elimino); 
	
	if(se_elimino) arbol->tamanio--;
	return elemento_quitar;
}


void* abb_buscar(abb_t* arbol, void* elemento){
	if(!arbol || abb_vacio(arbol) || !elemento) return NULL;

	nodo_abb_t* nodo_actual = arbol->nodo_raiz;
	int comparacion;

	while(nodo_actual){

		comparacion = arbol->comparador(elemento, nodo_actual->elemento);
		if(comparacion==0) return nodo_actual->elemento;
		else if(comparacion<0)
			nodo_actual = nodo_actual->izquierda;
		else nodo_actual = nodo_actual->derecha;
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

	contador+=abb_con_cada_elemento_postorden(nodo->izquierda, funcion, aux, seguir_recorriendo);

	contador+=abb_con_cada_elemento_postorden(nodo->derecha, funcion, aux, seguir_recorriendo);
	
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

	contador+=abb_con_cada_elemento_inorden(nodo->izquierda, funcion, aux, seguir_recorriendo);
	
	if(*seguir_recorriendo){
	*seguir_recorriendo = funcion(nodo->elemento, aux);
	contador++;
	}

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

	contador+=abb_con_cada_elemento_preorden(nodo->izquierda, funcion, aux, seguir_recorriendo);

	contador+=abb_con_cada_elemento_preorden(nodo->derecha, funcion, aux, seguir_recorriendo);

	return contador;
}


size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
	if(!arbol || !funcion) return 0;

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

size_t abb_recorrer_postorden(nodo_abb_t* nodo, void** array, size_t tamanio_array, size_t* posicion){
	if(!nodo) return 0;

	size_t cant = 0;

	cant += abb_recorrer_postorden(nodo->izquierda, array, tamanio_array, posicion);

	cant += abb_recorrer_postorden(nodo->derecha, array, tamanio_array, posicion);

	if(*posicion < tamanio_array){
	array[*posicion] = nodo->elemento;
	cant += 1;
		*posicion += 1;
	} 

	return cant;
}

size_t abb_recorrer_inorden(nodo_abb_t* nodo, void** array, size_t tamanio_array, size_t* posicion){ 
	if(!nodo) return 0;

	size_t cant = 0; 

	cant += abb_recorrer_inorden(nodo->izquierda, array, tamanio_array, posicion);
	
	if(*posicion < tamanio_array){
	array[*posicion] = nodo->elemento;
	cant += 1;
	*posicion += 1;
	}

	cant += abb_recorrer_inorden(nodo->derecha, array, tamanio_array, posicion);

	return cant;
}

size_t abb_recorrer_preorden(nodo_abb_t* nodo, void** array, size_t tamanio_array, size_t* posicion){
	if(!nodo) return 0;

	size_t cant = 0; 
	if(*posicion < tamanio_array){
	array[*posicion] = nodo->elemento;
	cant += 1;
	*posicion += 1;
	}

	cant += abb_recorrer_preorden(nodo->izquierda, array, tamanio_array, posicion);

	cant += abb_recorrer_preorden(nodo->derecha, array, tamanio_array, posicion);
	
	return cant;
}


size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){
	if(!arbol || !array) return 0;

	size_t posicion = 0;

	switch(recorrido){
		case INORDEN:
		return abb_recorrer_inorden(arbol->nodo_raiz, array, tamanio_array, &posicion);
		case PREORDEN:
		return abb_recorrer_preorden(arbol->nodo_raiz, array, tamanio_array, &posicion);
		case POSTORDEN:
		return abb_recorrer_postorden(arbol->nodo_raiz, array, tamanio_array, &posicion);
		default:
		return 0;
	}
}