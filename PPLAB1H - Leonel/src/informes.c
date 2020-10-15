/*
 * informes.c
 *
 *  Created on: 15 oct. 2020
 *      Author: leo
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "aviso.h"

int inf_imprimirCantidadDeAvisosPausados(Aviso* pArray, int limite)
{
	int retorno = -1;
	int i;
	int cantAvisosPausados = 0;

	for(i=0; i < limite; i++)
	{
		if(pArray[i].estado == FALSE && pArray[i].estado == ESTADO_PAUSADO)
		{
			cantAvisosPausados++;
			retorno = 0;
		}
	}
	printf("\n\t     Cantidad de Avisos Pausados: %d\n",cantAvisosPausados);
	return retorno;
}
