/*
 * cliente.c
 *
 *  Created on: 15 oct. 2020
 *      Author: leo
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "cliente.h"

static int cli_generarIdNuevo(void);

//Funcion agregado
int cli_confirmaLaBajaDeUsuario(Cliente* pArray, int limite, int idBajar)
{
	int respuesta = 0;

	if(pArray != NULL && limite > 0 && idBajar > 0)
	{
		for(int i = 0; i < limite;  i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].id == idBajar)
			{
				pArray[i].isEmpty = TRUE;
				respuesta = 1;
			}
		}
	}
	return respuesta;
}

/**@brief cli_altaForzada(): Completa los datos de un alta utilizando los parametros
 * @param Cliente* pArray, Es el puntero al array de enteros.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int cli_altaForzada(Cliente* pArray, int limite, int indice,
		int id,
		char* nombre,
		char* apellido,
		char* cuit)
{
	int retorno = -1;

	Cliente buffer;

	if(	pArray != NULL && limite > 0 && id > 0 && indice >= 0)
	{
		strncpy(buffer.nombre,nombre,SIZE_NOMBRE);
		strncpy(buffer.apellido,apellido,SIZE_NOMBRE);
		strncpy(buffer.cuit,cuit,SIZE_CUIT);

		buffer.id = cli_generarIdNuevo();
		pArray[indice] = buffer;
		pArray[indice].isEmpty = FALSE;

		retorno = 0;
	}
	return retorno;
}

/**@brief generarIdNuevo(): Cada vez que la llamo, me devuelve un ID nuevo que nunca me devolvio antes.
 */
static int cli_generarIdNuevo(void)
{
	static int id = 0; // es global para solo la fn puede usarla

	//guardar el ultimo que asigne (ultimo que devolvi)
	//para devolver 1+
	id = id + 1;
	return id;
}

/**@brief cli_initArray(): Inicializa el array.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int cli_initArray(Cliente* pArray, int limite)
{
	int retorno = -1;
	if(pArray != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**@brief cli_alta(): Realiza el alta de una entidad solo si el indice que se busca corresponde en Empty.
 * @param Cliente* pArray, Es el puntero al array de enteros.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int cli_alta(Cliente* pArray,int limite)
{
	int retorno = -1;
	int indice;
	Cliente buffer;

	if(	pArray != NULL && limite > 0)
	{
		if(cli_buscarLibreRef(pArray, limite,&indice) == 0) // Busca un lugar libre
		{
			if(	utn_getNombre("\n . Nombre: "," > Error!\n",buffer.nombre,2,SIZE_NOMBRE) == 0 &&
					utn_getNombre("\n . Apellido: "," > Error!\n",buffer.apellido,2,SIZE_NOMBRE) == 0 &&
					utn_getCuilOrCuit(buffer.cuit, 2) == 0)
			{
				buffer.id = cli_generarIdNuevo();
				pArray[indice] = buffer;
				pArray[indice].isEmpty = FALSE;
				printf("\n . Informacion:\n");
				cli_imprimirPorID(pArray,limite,indice);
				retorno = 0;
			}
			else
			{
				printf("\n > Error en la carga de datos!\n");
			}
		}
		else
		{
			printf("\n > Lo sentimos, no hay posiciones libres!\n");
		}
	}
	return retorno;
}

/**@brief cli_modificar(): Modifica los datos de un ent solo si el indice corresponde a un NO Empty.
 * @param Cliente* pArray, Es el puntero al array.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el dato.
 * @return (-1) Error / (0) Ok
 */
int cli_modificar(Cliente* pArray,int limite)
{
	int retorno = -1;
	int idModificar;
	int indice;
	Cliente buffer;

	cli_imprimir(pArray,limite);

	if(utn_getInt("\n ~ Ingrese el ID a modificar: "," > Error!\n", &idModificar,5,1,1000) == 0)
	{
		if(cli_buscarId(pArray, limite, &indice, idModificar) == 0)
		{
			printf("\n . Dato seleccionado:\n");
			cli_imprimirPorID(pArray,limite,indice);

			if(	pArray != NULL && limite > 0 && indice >= 0 && indice < limite &&
					pArray[indice].isEmpty == FALSE)
			{
				if(	utn_getNombre("\n . nombre: "," > Error!\n",buffer.nombre,2,SIZE_NOMBRE) == 0 &&
						utn_getNombre("\n . apellido: "," > Error!\n",buffer.apellido,2,SIZE_NOMBRE) == 0 &&
						utn_getCuilOrCuit(buffer.cuit, 2) == 0
				)
				{
					buffer.id = pArray[indice].id;
					pArray[indice] = buffer;
					pArray[indice].isEmpty = FALSE;
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/**@brief cli_baja(): Realiza la baja de una entidad dando el ID correpondiente.
 * @param Cliente* pArray, Es el puntero al array.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el dato.
 * @return (-1) Error / (0) Ok
 */
int cli_baja(Cliente* pArray, int limite, int* idSeleccionado)
{
	int retorno = -1;
	int idBajar;
	int indice;

	cli_imprimir(pArray,limite);

	if(utn_getInt("\n ~ Ingrese el ID a bajar: "," > Error!\n", &idBajar,2,1,1000) == 0)
	{
		if(cli_buscarId(pArray, limite, &indice, idBajar) == 0)
		{
			printf("\n . Dato seleccionado:\n");
			cli_imprimirPorID(pArray,limite,indice);
			*idSeleccionado = idBajar;
			retorno = 0;
		}
		else
		{
			printf(" > Lo sentimos, no se puedo encontrar el ID que desea...");
		}
	}
	return retorno;

}

/**@brief cli_imprimir(): Imprime las entidades cargadas.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int cli_imprimir(Cliente* pArray, int limite)
{
	int retorno = -1;

	if(pArray != NULL && limite > 0)
	{
		printf("\n . Lista:\n");
		for(int j=0;j<limite;j++)
		{
			if(pArray[j].isEmpty == FALSE)
			{
				printf("\t     ID: %d\t CUIT: %s\t Apellido/Nombre: %s, %s\n",
						pArray[j].id,
						pArray[j].cuit,
						pArray[j].apellido,
						pArray[j].nombre);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**@brief cli_imprimirPorID(): Imprime el ID de alguna entidad que se quiera buscar.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int index, es el indice a imprimir.
 * @return (-1) Error / (0) Ok
 */
int cli_imprimirPorID(Cliente* pArray, int limite, int index)
{
	int retorno = -1;
	if(pArray != NULL && limite > 0 && index < limite)
	{
		if(pArray[index].isEmpty == FALSE)
		{
			printf("\n\t     ID de Cliente: %d\t CUIT: %s\t Apellido/Nombre: %s, %s\n",
					pArray[index].id,
					pArray[index].cuit,
					pArray[index].apellido,
					pArray[index].nombre);
			retorno = 0;
		}
	}
	return retorno;
}

/**@brief cli_buscarLibreRef(): Busca un espacio libre en el array y retorna la posicion mediante pasaje por referencia.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int *pIndex, es la varible en donde se guardara esa posicion vacia o disponible.
 * @return (-1) Error / (0) Ok
 */
int cli_buscarLibreRef(Cliente* pArray, int limite, int *pIndex)
{
	int retornar = -1;
	if(pArray != NULL && pIndex != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

/**@brief cli_buscarLibreValor(): Busca un espacio libre en el array y retorna la posicion mediante pasaje por valor.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int cli_buscarLibreValor(Cliente* pArray, int limite)
{
	int retornar = -1;
	if(pArray != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				retornar = i;
				break;
			}
		}
	}
	return retornar;
}

/**@brief cli_buscarId(): Busca el ID de una entidad.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int index, es la varible en donde se guardara la posicion del ID.
 * @param int id, es el identificador que quiero comparar y buscar.
 * @return (-1) Error / (0) Ok
 */
int cli_buscarId(Cliente* pArray, int limite, int* pIndex, int idBuscar)
{
	int retorno = -1;
	if (pArray != NULL && limite > 0 && pIndex != NULL && idBuscar >= 0)
	{
		for (int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == FALSE &&
					pArray[i].id == idBuscar)
			{

				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**@brief cli_ordenarAlfabeticamente(): Ordena alfabeticamente las cadenas de caracteres (ascendente & descendente).
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int orden, es el criterio de ordenamiento a elegir (1 = a-z || 0 = z-a).
 * @return (-1) Error / (0) Ok
 */
int cli_ordenarAlfabeticamente(Cliente* pArray, int limite, int orden)
{
	int retorno = -1;
	int flagSwap;
	Cliente buffer;

	//if(pArray[i].isEmpty == FALSE && pArray[i+1].isEmpty == FALSE

	if(pArray != NULL && limite > 0 && (orden == 0 || orden == 1))
	{
		do
		{
			flagSwap = 0;
			for(int i = 0; i < limite-1;i++)
			{
				if((orden == 1 && strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) > 0) ||
						(orden == 0 && strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) < 0)
				)
				{
					buffer = pArray[i];
					pArray[i] = pArray[i+1];
					pArray[i+1] = buffer;
					flagSwap = 1;
					retorno = 0;
				}
			}
		}while(flagSwap);
	}
	return retorno;
}

/**@brief cli_ordenarAlfaX2Criterios(): Ordena alfabeticamente las cadenas de caracteres incluyendo otro campo para "desempatar",
 *        en caso de ser iguales las cadenas.
 * @param Cliente* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
/*int cli_ordenarAlfaX2Criterios(Cliente* pArray, int limite)
{
	int retorno = -1;
	int flagSwap;
	Cliente buffer;

	//if(pArray[i].isEmpty == FALSE && pArray[i+1].isEmpty == FALSE
	do
	{
		flagSwap = 0;
		for(int i = 0; i < limite-1;i++)
		{
			if(strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) > 0 ||
					(strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) == 0
							&& pArray[i].eNT1 > pArray[i+1].eNT1))
			{
				buffer = pArray[i];
				pArray[i] = pArray[i+1];
				pArray[i+1] = buffer;
				flagSwap = 1;
				retorno = 0;
			}
		}
	}while(flagSwap);

	return retorno;
}*/



