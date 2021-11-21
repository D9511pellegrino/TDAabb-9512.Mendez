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

bool chequear_alumni_postorden(alumno_t** alumnos_ordenados, alumno_t alumnos_postorden[6]){
  if(!alumnos_ordenados || !alumnos_postorden) return false;

  int i = 0;
  while(alumnos_ordenados[i]){
    if(comparador_padron(alumnos_ordenados[i], &alumnos_postorden[i])!=0) return false;
    if(!alumnos_ordenados[i+1]) break;
    i++;
  }
  return true;
}

bool mostrar_alumno(void* a, void* b){
  alumno_t* alumno = a;

  printf("Alumnos %s (%d)\n", alumno->nombre, alumno->padron);
  return true;
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

  pa2m_afirmar(insercion_correcta,"Se insertaron 5 alumnos");
  pa2m_afirmar(!abb_vacio(a), "El ABB no está vacio");

  struct alumno alumno_busqueda = {.padron=104368, .nombre=""};
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[0], "Busco un elemento y lo encuentro");

  alumno_busqueda.padron=105368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[1], "Busco un elemento y lo encuentro");

  alumno_busqueda.padron=106368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[2], "Busco un elemento y lo encuentro");

  alumno_busqueda.padron=107368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[3], "Busco un elemento y lo encuentro");

  alumno_busqueda.padron=108368;
  pa2m_afirmar(!abb_buscar(a, &alumno_busqueda), "Busco un elemento inexistente y devuelve null");

  alumno_busqueda.padron=109368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[4], "Busco un elemento y lo encuentro");


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

  pa2m_afirmar(insercion_correcta,"Se insertaron 6 alumnos");
  pa2m_afirmar(!abb_vacio(a), "El ABB no está vacio");

  struct alumno alumno_busqueda = {.padron=106368, .nombre=""};
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[0], "Busco un elemento y lo encuentro");
  pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[0], "Puedo quitar nodo raiz con 2 hijos, el elemento es correcto");
  pa2m_afirmar(a->nodo_raiz->elemento==&alumnos[4], "El elmento raiz es correcto");
  pa2m_afirmar(abb_tamanio(a)==5, "El arbol tiene 5 elementos");

  alumno_busqueda.padron=104368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[1], "Busco un elemento y lo encuentro");
  pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[1], "Puedo quitar nodo con hijo izquierdo, el elemento es correcto");
  pa2m_afirmar(abb_tamanio(a)==4, "El arbol tiene 4 elementos");


  alumno_busqueda.padron=107368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[2], "Busco un elemento y lo encuentro");
  pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[2], "Puedo quitar nodo con hijo derecho, el elemento es correcto");
  pa2m_afirmar(abb_tamanio(a)==3, "El arbol tiene 3 elementos");

  alumno_busqueda.padron=105368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[4], "Busco un elemento y lo encuentro");
  pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[4], "Puedo quitar nodo raiz con hijo derecho, el elemento es correcto");
  pa2m_afirmar(a->nodo_raiz->elemento==&alumnos[5], "El elmento raiz es correcto");
  pa2m_afirmar(abb_tamanio(a)==2, "El arbol tiene 2 elementos");

  alumno_busqueda.padron=109368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[3], "Busco un elemento y lo encuentro");
  pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[3], "Puedo quitar nodo hoja, el elemento es correcto");
  pa2m_afirmar(abb_tamanio(a)==1, "El arbol tiene 1 elemento");

  alumno_busqueda.padron=103368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[5], "Busco un elemento y lo encuentro");
  pa2m_afirmar(abb_quitar(a, &alumno_busqueda)==&alumnos[5], "Puedo quitar nodo raiz sin hijos, el elemento es correcto");
  pa2m_afirmar(!a->nodo_raiz, "El nodo raiz es NULL");
  pa2m_afirmar(abb_vacio(a), "El arbol esta vacio")
  pa2m_afirmar(abb_tamanio(a)==0, "El arbol tiene 0 elementos");


  for (int i = 0; i < 3; i++) abb_insertar(a, &(alumnos[i]));

  alumno_busqueda.padron=106368;
  pa2m_afirmar(abb_buscar(a, &alumno_busqueda)==&alumnos[0], "Busco un elemento y lo encuentro");
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
  pa2m_afirmar(!abb_vacio(a), "El ABB no está vacio");

  struct alumno* alumnos_ordenados[6];


  /*abb_t* a = abb_crear((abb_comparador) comparador_int);

  int numeros[7] = {5, 3, 9, 2, 4, 8, 11};

  bool insercion_correcta=true;


  for (int i = 0; i < 7; i++){
    if(abb_insertar(a, &(numeros[i]))!=a) insercion_correcta = false;  
  }

  pa2m_afirmar(insercion_correcta,"Se insertaron 7 elementos");
  

  int numeros_inorden[7] = {2, 3, 4, 5, 8, 9, 11};
  int** numeros_ordenados_todos = calloc(7, sizeof(int*));
  if(!numeros_ordenados_todos){
    abb_destruir(a);
    return;
  }*/


  //pa2m_afirmar(abb_recorrer(a, 1, (void**)&numeros_ordenados_todos, 7)==7, "Se recorren la cantidad de elementos correcta");
  //pa2m_afirmar(numeros_inorden==*numeros_ordenados_todos, "Los elementos se guardan inorden");

  pa2m_afirmar(abb_recorrer(a, INORDEN, (void**)alumnos_ordenados, 6)==6, "Se recorren la cantidad de elementos correcta");

  abb_con_cada_elemento(a, INORDEN, mostrar_alumno, NULL);


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

  //struct alumno alumnos_postorden[6] = {alumnos[5], alumnos[4], alumnos[1], alumnos[3], alumnos[2], alumnos[0]};
  struct alumno* alumnos_ordenados[6];

  pa2m_afirmar(abb_recorrer(a, 1, (void**)alumnos_ordenados, 6)==6, "Se recorren la cantidad de elementos correcta");
  //pa2m_afirmar(chequear_alumni_postorden(alumnos_ordenados, alumnos_postorden), "Los alumnos se guardan postorden");
  abb_con_cada_elemento(a, POSTORDEN, mostrar_alumno, NULL);



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

  abb_con_cada_elemento(a, PREORDEN, mostrar_alumno, NULL);



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

  pa2m_nuevo_grupo("Pruebas de recorrido inorden");
  puedoRecorrerunABB_INORDEN();

  pa2m_nuevo_grupo("Pruebas de recorrido postorden");
  puedoRecorrerunABB_POSTORDEN();

  pa2m_nuevo_grupo("Pruebas de recorrido preorden");
  puedoRecorrerunABB_PREORDEN();



  return pa2m_mostrar_reporte();
}
