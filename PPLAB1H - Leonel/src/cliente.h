/*
 * cliente.h
 *
 *  Created on: 12 oct. 2020
 *      Author: leo
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

	#define QTY_CLIENTES 10
	#define TRUE 1
	#define FALSE 0
	#define SIZE_NOMBRE 50
	#define SIZE_CUIT 17
	#define MIN 1
	#define MAX 100

	typedef struct
	{
		int id;
		int isEmpty;
		char nombre[SIZE_NOMBRE];
		char apellido[SIZE_NOMBRE];
		char cuit[SIZE_CUIT];
	}Cliente;

	int cli_initArray(Cliente* pArray, int limite);

	int cli_alta(Cliente* pArray,int limite);
	int cli_altaConIndice(Cliente* pArray,int limite,int indice);
	int cli_modificar(Cliente* pArray,int limite);
	int cli_baja(Cliente* pArray,int limite);

	int cli_imprimir(Cliente* pArray, int limite);
	int cli_imprimirPorID(Cliente* pArray, int limite, int index);

	int cli_buscarId(Cliente* pArray, int limite, int* pIndex, int idBuscar);
	int cli_buscarLibreRef(Cliente* pArray, int limite, int *pIndex);
	int cli_buscarLibreValor(Cliente* pArray, int limite);

	int cli_ordenarAlfabeticamente(Cliente* pArray, int limite, int orden);
	int cli_ordenarAlfaX2Criterios(Cliente* pArray, int limite);

	int cli_altaForzada(Cliente* pArray,int limite, int indice, int id,
			char* nombre,
			char* apellido,
			char* cuit);

#endif /* CLIENTE_H_ */
