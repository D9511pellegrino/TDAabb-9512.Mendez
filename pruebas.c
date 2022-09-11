#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

typedef struct alumno{
	int padron;
	char* nombre;  
} alumno_t;

int comparador_int(int* primero, int* segundo){
	return *primero-*segundo;
}

int comparador_padron(struct alumno* primero, struct alumno* segundo){
	return comparador_int(&(primero->padron), &(segundo->padron));
}

bool chequear_alumni_orden(alumno_t** alumnos_ordenados, alumno_t** alumnos_orden_CORRECTO, size_t cantidad){
	if(!alumnos_ordenados || !alumnos_orden_CORRECTO) return false;

	for(int i = 0; i<cantidad; i++){
		if(comparador_padron(alumnos_ordenados[i], alumnos_orden_CORRECTO[i])!=0) return false;
		i++;
	}
	return true;
}

bool mostrar_alumno(void* a, void* b){
	alumno_t* alumno = a;

	printf("Alumno: %s (%d)\n", alumno->nombre, alumno->padron);
	return true;
}

bool buscar_alumno(void* a, void* b){
	alumno_t* alumno_a = a;
	alumno_t* alumno_b = b;

	if(comparador_padron(alumno_a, alumno_b)==0) return false;
	else return true;
}


void puedoCrearUnABB(){
	abb_t* a = NULL;

	pa2m_afirmar((a=abb_crear((abb_comparador) comparador_int)), "Crear un ABB devuelve un ABB");
	pa2m_afirmar(abb_vacio(a), "ABB se crea vacio");
	pa2m_afirmar(abb_tamanio(a)==0, "ABB tiene 0 elementos");
	pa2m_afirmar(!abb_buscar(a, NULL), "El elemento raiz es NULL");

	abb_destruir(a);
}


void dadoUnABB_PuedoInsertar(){
	abb_t* a = abb_crear((abb_comparador) comparador_int);

	int numeros[5] = {0,1,2,3,4};

	pa2m_afirmar(abb_vacio(a), "ABB se crea vacio");
	pa2m_afirmar(abb_tamanio(a)==0, "ABB tiene 0 elementos");
	
	pa2m_afirmar(abb_insertar(a, &(numeros[2]))==a, "Puedo insertar un elemento en un ABB vacío");
	pa2m_afirmar(abb_buscar(a, &(numeros[2]))==&(numeros[2]), "El elemento insertado está en el ABB");
	pa2m_afirmar(abb_tamanio(a)==1, "El tamaño del ABB es 1");

	pa2m_afirmar(abb_insertar(a, &(numeros[1]))==a, "Puedo insertar un elemento menor al anterior");
	pa2m_afirmar(abb_buscar(a, &(numeros[1]))==&(numeros[1]), "El elemento insertado está en el ABB");
	pa2m_afirmar(abb_tamanio(a)==2, "El tamaño del ABB es 2");

	abb_destruir(a);
}

void dadoUnABBconElementos_PuedoBuscar(){
	abb_t* a = abb_crear((abb_comparador) comparador_padron);

	struct alumno alumnos[5];

	alumnos[0].padron=104368;
	alumnos[0].nombre="Maria"; 
	alumnos[1].padron=105368;
	alumnos[1].nombre="Ophelia";
	alumnos[2].padron=106368;
	alumnos[2].nombre="Esperanza";
	alumnos[3].padron=107368;
	alumnos[3].nombre="Daniela";
	alumnos[4].padron=109368;
	alumnos[4].nombre="Alba"; 

	bool insercion_correcta=true;


	for (int i = 0; i < 5; i++){
		if(abb_insertar(a, &(alumnos[i]))!=a) insercion_correcta = false;  
	}

	pa2m_afirmar(insercion_correcta,"Se insertaron 5 elementos");
	pa2m_afirmar(!abb_vacio(a), "El ABB no está vacio");

	struct alumno alumno_busqueda = {.padron=109368, .nombre=""};
	pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[4], "Busco el elemento 5 y lo encuentro");

	alumno_busqueda.padron=108368;
	pa2m_afirmar(!abb_buscar(a, &alumno_busqueda), "Buscar un elemento inexistente devuelve null");

	pa2m_afirmar(abb_buscar(a, NULL)==NULL, "Buscar con parámetro NULL devuelve null");

	abb_destruir(a);
}

void dadoUnABBconElementos_Puedoquitar(){
	abb_t* a = abb_crear((abb_comparador) comparador_padron);

	struct alumno alumnos[6];

	alumnos[0].padron=106368;
	alumnos[0].nombre="Maria"; 
	alumnos[1].padron=104368;
	alumnos[1].nombre="Ophelia";
	alumnos[2].padron=107368;
	alumnos[2].nombre="Esperanza";
	alumnos[3].padron=109368;
	alumnos[3].nombre="Daniela";
	alumnos[4].padron=105368;
	alumnos[4].nombre="Alba"; 
	alumnos[5].padron=103368;
	alumnos[5].nombre="Bela"; 

	bool insercion_correcta=true;


	for (int i = 0; i < 6; i++){
		if(abb_insertar(a, &(alumnos[i]))!=a) insercion_correcta = false;  
	}

	pa2m_afirmar(insercion_correcta,"Se insertaron 6 elementos");
	pa2m_afirmar(!abb_vacio(a), "El ABB no está vacio");

	struct alumno alumno_busqueda = {.padron=106368, .nombre=""};
	pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[0], "Busco el elemento 1 y lo encuentro");
	pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[0], "Puedo quitar nodo raiz con 2 hijos, el elemento es correcto");
	pa2m_afirmar(a->nodo_raiz->elemento==&alumnos[4], "El elmento raiz es correcto");
	pa2m_afirmar(abb_tamanio(a)==5, "El arbol tiene 5 elementos");

	alumno_busqueda.padron=104368;
	pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[1], "Puedo quitar nodo con hijo izquierdo, el elemento es correcto");
	pa2m_afirmar(abb_tamanio(a)==4, "El arbol tiene 4 elementos");


	alumno_busqueda.padron=107368;
	pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[2], "Puedo quitar nodo con hijo derecho, el elemento es correcto");
	pa2m_afirmar(abb_tamanio(a)==3, "El arbol tiene 3 elementos");

	alumno_busqueda.padron=105368;
	pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[4], "Puedo quitar nodo raiz con hijo derecho, el elemento es correcto");
	pa2m_afirmar(a->nodo_raiz->elemento==&alumnos[5], "El elmento raiz es correcto");
	pa2m_afirmar(abb_tamanio(a)==2, "El arbol tiene 2 elementos");

	alumno_busqueda.padron=109368;
	pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[3], "Puedo quitar nodo hoja, el elemento es correcto");
	pa2m_afirmar(abb_tamanio(a)==1, "El arbol tiene 1 elemento");

	alumno_busqueda.padron=103368;
	pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[5], "Puedo quitar nodo raiz sin hijos, el elemento es correcto");
	pa2m_afirmar(!a->nodo_raiz, "El nodo raiz es NULL");
	pa2m_afirmar(abb_vacio(a), "El arbol esta vacio");
	pa2m_afirmar(abb_tamanio(a)==0, "El arbol tiene 0 elementos");


	for (int i = 0; i < 3; i++) 
	if(abb_insertar(a, &(alumnos[i]))!=a) insercion_correcta=false;

	pa2m_afirmar(insercion_correcta,"Se insertaron 3 elementos");

	alumno_busqueda.padron=106368;
	pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[0], "Puedo quitar nodo raiz con 2 hijos sin hijos, el elemento es correcto");
	pa2m_afirmar(a->nodo_raiz->elemento==&alumnos[1], "El elmento raiz es correcto");
	pa2m_afirmar(abb_tamanio(a)==2, "El arbol tiene 2 elementos");


	alumno_busqueda.padron=10368;
	pa2m_afirmar(!abb_quitar(a, &alumno_busqueda), "Quitar un elemento inexistente devuelve NULL");

	abb_destruir(a);
}


void puedoRecorrerunABB_INORDEN(){
	abb_t* a = abb_crear((abb_comparador) comparador_padron);

	struct alumno alumnos[6];

	alumnos[0].padron=106368;
	alumnos[0].nombre="Maria"; 
	alumnos[1].padron=104368;
	alumnos[1].nombre="Ophelia";
	alumnos[2].padron=107368;
	alumnos[2].nombre="Esperanza";
	alumnos[3].padron=109368;
	alumnos[3].nombre="Daniela";
	alumnos[4].padron=105368;
	alumnos[4].nombre="Alba"; 
	alumnos[5].padron=103368;
	alumnos[5].nombre="Bela"; 


	for (int i = 0; i < 6; i++){
		abb_insertar(a, &(alumnos[i]));  
	}

	alumno_t** alumnos_inorden = calloc(6, sizeof(alumno_t*));
	if(!alumnos_inorden){
		abb_destruir(a);
		return;
	}

	bool reserva_fallida = false;

	for(int i = 0; i<6; i++){
		alumnos_inorden[i] = malloc(sizeof(alumno_t));
		if(!alumnos_inorden[i]) reserva_fallida = true;
	}

	if(reserva_fallida){
		for(int i = 0; i<6; i++) free(alumnos_inorden[i]);
		free(alumnos_inorden);
		abb_destruir(a);
	}

	*alumnos_inorden[0] = alumnos[5];
	*alumnos_inorden[1] = alumnos[1];
	*alumnos_inorden[2] = alumnos[4];
	*alumnos_inorden[3] = alumnos[0];
	*alumnos_inorden[4] = alumnos[2];
	*alumnos_inorden[5] = alumnos[3];

	alumno_t** alumnos_ordenados = calloc(6, sizeof(alumno_t*));
	if(!alumnos_ordenados){
		abb_destruir(a);
		return;
	}


	pa2m_afirmar(abb_recorrer(a, INORDEN, (void**)alumnos_ordenados, 6)==6, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_inorden, 6), "Los elementos se guardan inorden");

	alumnos_ordenados = realloc(alumnos_ordenados, 3*sizeof(alumno_t*));
	if(!alumnos_ordenados){
		for(int i = 0; i<6; i++) free(alumnos_inorden[i]);
		free(alumnos_inorden);
		abb_destruir(a);
		return;
	}

	pa2m_afirmar(abb_recorrer(a, INORDEN, (void**)alumnos_ordenados, 3)==3, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_inorden, 3), "Los alumnos se guardan inorden");

	alumnos_ordenados = realloc(alumnos_ordenados, 8*sizeof(alumno_t*));
	if(!alumnos_ordenados){
		for(int i = 0; i<6; i++) free(alumnos_inorden[i]);
		free(alumnos_inorden);
		abb_destruir(a);
		return;
	}

	pa2m_afirmar(abb_recorrer(a, INORDEN, (void**)alumnos_ordenados, 8)==6, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_inorden, 6), "Los alumnos se guardan inorden");


	pa2m_afirmar(abb_con_cada_elemento(a, INORDEN, buscar_alumno, &alumnos[4])==3, "El iterador interno devuelve la cantidad de elementos que se esperaba iterar.");
	printf("Los alumnos en orden inorden son:\n");
	pa2m_afirmar(abb_con_cada_elemento(a, INORDEN, mostrar_alumno, NULL)==6, "Puedo llamar al iterador con aux=NULL y recorre la cantidad correcta");



	for(int i = 0; i<6; i++) free(alumnos_inorden[i]);
	free(alumnos_inorden);
	free(alumnos_ordenados);
	abb_destruir(a);
}

void puedoRecorrerunABB_POSTORDEN(){
	abb_t* a = abb_crear((abb_comparador) comparador_padron);

	struct alumno alumnos[6];

	alumnos[0].padron=106368;
	alumnos[0].nombre="Maria"; 
	alumnos[1].padron=104368;
	alumnos[1].nombre="Ophelia";
	alumnos[2].padron=107368;
	alumnos[2].nombre="Esperanza";
	alumnos[3].padron=109368;
	alumnos[3].nombre="Daniela";
	alumnos[4].padron=105368;
	alumnos[4].nombre="Alba"; 
	alumnos[5].padron=103368;
	alumnos[5].nombre="Bela"; 


	for (int i = 0; i < 6; i++){
		abb_insertar(a, &(alumnos[i]));  
	}

	alumno_t** alumnos_postorden = calloc(6, sizeof(alumno_t*));
	if(!alumnos_postorden){
		abb_destruir(a);
		return;
	}

	bool reserva_fallida = false;

	for(int i = 0; i<6; i++){
		alumnos_postorden[i] = malloc(sizeof(alumno_t));
		if(!alumnos_postorden[i]) reserva_fallida = true;
	}

	if(reserva_fallida){
		for(int i = 0; i<6; i++) free(alumnos_postorden[i]);
		free(alumnos_postorden);
		abb_destruir(a);
	}

	*alumnos_postorden[0] = alumnos[5];
	*alumnos_postorden[1] = alumnos[4];
	*alumnos_postorden[2] = alumnos[1];
	*alumnos_postorden[3] = alumnos[3];
	*alumnos_postorden[4] = alumnos[2];
	*alumnos_postorden[5] = alumnos[0];

	alumno_t** alumnos_ordenados = calloc(6, sizeof(alumno_t*));
	if(!alumnos_ordenados){
		abb_destruir(a);
		return;
	}


	pa2m_afirmar(abb_recorrer(a, POSTORDEN, (void**)alumnos_ordenados, 6)==6, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_postorden, 6), "Los alumnos se guardan postorden");





	alumnos_ordenados = realloc(alumnos_ordenados, 8*sizeof(alumno_t*));
	if(!alumnos_ordenados){
		for(int i = 0; i<6; i++) free(alumnos_postorden[i]);
		free(alumnos_postorden);
		abb_destruir(a);
		return;
	}

	pa2m_afirmar(abb_recorrer(a, POSTORDEN, (void**)alumnos_ordenados, 8)==6, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_postorden, 6), "Los alumnos se guardan postorden");




	alumnos_ordenados = realloc(alumnos_ordenados, 3*sizeof(alumno_t*));
	if(!alumnos_ordenados){
		for(int i = 0; i<6; i++) free(alumnos_postorden[i]);
		free(alumnos_postorden);
		abb_destruir(a);
		return;
	}

	pa2m_afirmar(abb_recorrer(a, POSTORDEN, (void**)alumnos_ordenados, 3)==3, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_postorden, 3), "Los alumnos se guardan postorden");


	pa2m_afirmar(abb_con_cada_elemento(a, POSTORDEN, buscar_alumno, &alumnos[4])==2, "El iterador interno devuelve la cantidad de elementos que se esperaba iterar.");
	printf("Los alumnos en orden postorden son:\n");
	pa2m_afirmar(abb_con_cada_elemento(a, POSTORDEN, mostrar_alumno, NULL)==6, "Puedo llamar al iterador con aux=NULL y recorre la cantidad correcta");

	for(int i = 0; i<6; i++) free(alumnos_postorden[i]);
	free(alumnos_postorden);
	free(alumnos_ordenados);
	abb_destruir(a);

}

void puedoRecorrerunABB_PREORDEN(){
	abb_t* a = abb_crear((abb_comparador) comparador_padron);

	struct alumno alumnos[6];

	alumnos[0].padron=106368;
	alumnos[0].nombre="Maria"; 
	alumnos[1].padron=104368;
	alumnos[1].nombre="Ophelia";
	alumnos[2].padron=107368;
	alumnos[2].nombre="Esperanza";
	alumnos[3].padron=109368;
	alumnos[3].nombre="Daniela";
	alumnos[4].padron=105368;
	alumnos[4].nombre="Alba"; 
	alumnos[5].padron=103368;
	alumnos[5].nombre="Bela"; 


	for (int i = 0; i < 6; i++){
		abb_insertar(a, &(alumnos[i]));  
	}

	alumno_t** alumnos_preorden = calloc(6, sizeof(alumno_t*));
	if(!alumnos_preorden){
		abb_destruir(a);
		return;
	}

	bool reserva_fallida = false;

	for(int i = 0; i<6; i++){
		alumnos_preorden[i] = malloc(sizeof(alumno_t));
		if(!alumnos_preorden[i]) reserva_fallida = true;
	}

	if(reserva_fallida){
		for(int i = 0; i<6; i++) free(alumnos_preorden[i]);
		free(alumnos_preorden);
		abb_destruir(a);
	}

	*alumnos_preorden[0] = alumnos[0];
	*alumnos_preorden[1] = alumnos[1];
	*alumnos_preorden[2] = alumnos[5];
	*alumnos_preorden[3] = alumnos[4];
	*alumnos_preorden[4] = alumnos[2];
	*alumnos_preorden[5] = alumnos[3];

	alumno_t** alumnos_ordenados = malloc(6*sizeof(alumno_t*));
	if(!alumnos_ordenados){
		for(int i = 0; i<6; i++) free(alumnos_preorden[i]);
		free(alumnos_preorden);
		abb_destruir(a);
		return;
	}

	pa2m_afirmar(abb_recorrer(a, PREORDEN, (void**)alumnos_ordenados, 6)==6, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_preorden, 6), "Los alumnos se guardan preorden");
	

	alumnos_ordenados = realloc(alumnos_ordenados, 3*sizeof(alumno_t*));
	if(!alumnos_ordenados){
		for(int i = 0; i<6; i++) free(alumnos_preorden[i]);
		free(alumnos_preorden);
		abb_destruir(a);
		return;
	}

	pa2m_afirmar(abb_recorrer(a, PREORDEN, (void**)alumnos_ordenados, 3)==3, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_preorden, 3), "Los alumnos se guardan preorden");




	alumnos_ordenados = realloc(alumnos_ordenados, 9*sizeof(alumno_t*));
	if(!alumnos_ordenados){
		for(int i = 0; i<6; i++) free(alumnos_preorden[i]);
		free(alumnos_preorden);
		abb_destruir(a);
		return;
	}

	pa2m_afirmar(abb_recorrer(a, PREORDEN, (void**)alumnos_ordenados, 9)==6, "Se recorren la cantidad de elementos correcta");
	pa2m_afirmar(chequear_alumni_orden(alumnos_ordenados, alumnos_preorden, 6), "Los alumnos se guardan preorden");
	

	for(int i = 0; i<6; i++) free(alumnos_preorden[i]);
	free(alumnos_preorden);
	free(alumnos_ordenados);


	pa2m_afirmar(abb_con_cada_elemento(a, PREORDEN, buscar_alumno, &alumnos[4])==4, "El iterador interno devuelve la cantidad de elementos que se esperaba iterar.");
	printf("Los alumnos en orden preorden son:\n");
	pa2m_afirmar(abb_con_cada_elemento(a, PREORDEN, mostrar_alumno, NULL)==6, "Puedo llamar al iterador con aux=NULL y recorre la cantidad correcta");
	
	abb_destruir(a);
}

int main(){

	pa2m_nuevo_grupo("Pruebas de creacion ABB");
	puedoCrearUnABB();

	pa2m_nuevo_grupo("Pruebas de insercion");
	dadoUnABB_PuedoInsertar();

	pa2m_nuevo_grupo("Pruebas de busqueda");
	dadoUnABBconElementos_PuedoBuscar();

	pa2m_nuevo_grupo("Pruebas de borrado");
	dadoUnABBconElementos_Puedoquitar();

	pa2m_nuevo_grupo("Pruebas de recorrido e iterador inorden");
	puedoRecorrerunABB_INORDEN();

	pa2m_nuevo_grupo("Pruebas de recorrido e iterador postorden");
	puedoRecorrerunABB_POSTORDEN();

	pa2m_nuevo_grupo("Pruebas de recorrido e iterador preorden");
	puedoRecorrerunABB_PREORDEN();

	return pa2m_mostrar_reporte();
}
