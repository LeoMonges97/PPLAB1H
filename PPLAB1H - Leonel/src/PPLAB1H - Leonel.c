/*
 ============================================================================
 Name        : PPLAB1H.c
 Author      : Leonel Monges - 1H
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#define CANT_OPCIONES 8
#define ACTIVAR_ABM 0 // 0 = activar abm sin hardcodeo / 1 = iniciar abm con altaForzada

int main(void)
{
	int op;

	Cliente arrayClientes[QTY_CLIENTES];
	Aviso arrayAvisos[QTY_AVISOS];

	// ABM Validacion
	int flagDatoCargado = ACTIVAR_ABM;
	//int flagOrdenamiento = ACTIVAR_ABM;
	int contDatosCargados = 0;

	cli_initArray(arrayClientes,QTY_CLIENTES);
	avi_initArray(arrayAvisos,QTY_AVISOS);

	//altaForzada:
	//int contIndices = 0;
	//int contIDs = 1;

	//int contIndicesAvi = 0;
	//int contIDsAvi = 1;

	//cli_altaForzada(arrayClientes, QTY_CLIENTES,contIndices++,contIDs++,"Leonel","Monges","21-45631278-5",1);
	//cli_altaForzada(arrayClientes, QTY_CLIENTES,contIndices++,contIDs++,"Diego","Maradona","21-45631278-5",1);
	//cli_altaForzada(arrayClientes, QTY_CLIENTES,contIndices++,contIDs++,"German","Martitegui","21-45631278-5",0);

	//avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,1,"ZARZAZRAZ",2,2);
	//avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,0,"QWEWQEQWE",2,2);
	//avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,1,"ASDASDASD",1,3);

	do
	{
		utn_getInt("\n ****************************************************\n"
				" PP1LAB1H - ABM AVISOS CLASIFICADOS (Leonel Monges)\n"
				"\n 1 - Alta cliente."
				"\n 2 - Modificar datos del cliente."
				"\n 3 - Baja cliente."
				"\n 4 - Alta Aviso."
				"\n 5 - Modificar aviso."
				"\n 6 - Imprimir lista de clientes."
				"\n 7 - Salir."
				"\n\n ~ Ingrese opcion: ",
				"\nError",&op,2,1,CANT_OPCIONES);
		switch(op)
		{
		case 1:
			if(cli_alta(arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Datos cargados correctamente!\n");
				flagDatoCargado = 1;
				contDatosCargados++; // Si hay al menos 2 o mas datos cargados, se púede ordenar.
				//if(contDatosCargados >= 2)
				//{
				//flagOrdenamiento = 1;
				//}
			}
			else
			{
				printf(" > Error!");
			}
			break;
		case 2:
			if(flagDatoCargado == 1 && cli_modificar(arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Datos modificados correctamente!\n");
			}
			else
			{
				printf(" > Error!\n");
			}
			break;
		case 3:
			if(flagDatoCargado  == 1 && cli_baja(arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Baja realizada correctamente!\n");
			}
			else
			{
				printf(" > Error!\n");
			}
			break;
		case 4:
			if(avi_alta(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Aviso cargado correctamente!\n");
			}
			else
			{
				printf(" > Error!\n");
			}

			/*if(flagOrdenamiento == 1 && cli_ordenarAlfabeticamente(arrayClientes,QTY_CLIENTES,1) == 0)
			{
				printf("\n . Datos ordenados correctamente!\n");
			}
			else
			{
				printf(" > Error!\n");
			}*/
			break;
		case 5:
			if(avi_modificar(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Aviso actualizado correctamente!\n");
			}
			{
				printf(" > Error!\n");

			}
			break;
		case 6:
			if(flagDatoCargado == 1)
			{
				cli_imprimir(arrayClientes,QTY_CLIENTES);
				avi_imprimir(arrayAvisos,QTY_AVISOS);
			}
			else
			{
				printf(" > Error! No hay datos cargados.\n");
			}
			break;
		case 7:
			printf("Informes");
			break;
		}

	}while(op != CANT_OPCIONES);
}
