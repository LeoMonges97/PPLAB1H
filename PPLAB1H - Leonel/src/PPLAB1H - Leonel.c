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
#include "informes.h"
#define CANT_OPCIONES 8
#define CANT_OPCIONES_INFORMES 4
#define ACTIVAR_ABM 1 // 0 = activar abm sin hardcodeo / 1 = iniciar abm con altaForzada

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
	int contIndices = 0;
	int contIDs = 1;
	int contIndicesAvi = 0;
	int contIDsAvi = 1;
	int idUsuario;
	int opcionInformes;

	cli_altaForzada(arrayClientes, QTY_CLIENTES,contIndices++,contIDs++,"A_firstName","A_lastName","21-45631278-5");
	cli_altaForzada(arrayClientes, QTY_CLIENTES,contIndices++,contIDs++,"B_firstName","B_lastName","21-41234579-5");
	cli_altaForzada(arrayClientes, QTY_CLIENTES,contIndices++,contIDs++,"C_firstName","C_lastName","21-35634470-5");
	cli_altaForzada(arrayClientes, QTY_CLIENTES,contIndices++,contIDs++,"D_firstName","D_lastName","21-20233571-5");
	cli_altaForzada(arrayClientes, QTY_CLIENTES,contIndices++,contIDs++,"E_firstName","E_lastName","21-31245687-5");

	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,1,"ZARZAZRAZ",3,2);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,1,"QWEWQEQWE",3,1);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,1,"ASDASDASD",3,3);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,0,"QWEWQEQWE",5,3);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,0,"ASDASDASD",1,4);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,1,"ZARZAZRAZ",4,2);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,0,"QWEWQEQWE",2,1);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,0,"ASDASDASD",4,2);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,0,"QWEWQEQWE",2,2);
	avi_altaForzada(arrayAvisos,QTY_AVISOS,contIndicesAvi++,contIDsAvi++,0,"ASDASDASD",1,5);


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
				"\n 7 - Informes."
				"\n 8 - Salir."
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
			if(flagDatoCargado  == 1 && cli_baja(arrayClientes,QTY_CLIENTES,&idUsuario) == 0)
			{
				if(avi_baja(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES,idUsuario) == 0)
				{
					if(cli_confirmaLaBajaDeUsuario(arrayClientes,QTY_CLIENTES,idUsuario) == 1)
					{
						printf("\n . Baja realizada correctamente!\n");
					}
				}
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
			break;
		case 5:
			if(avi_modificar(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES) == 0)
			{
				printf("\n . Aviso actualizado correctamente!\n");
			}
			break;
		case 6:
			if(flagDatoCargado == 1)
			{
				avi_imprimirTodosLosClientesConSusAvisosActivos(arrayAvisos,QTY_AVISOS,arrayClientes,QTY_CLIENTES);
			}
			else
			{
				printf(" > Error! No hay datos cargados.\n");
			}
			break;
		case 7:
			do
			{
				utn_getInt("\n   ********* Informes *********\n"
						" . Seleccione la opcion a elegir:\n\n"
						" 1 - Clientes con mas avisos.\n"
						" 2 - Cantidad de avisos pausados.\n"
						" 3 - Rubros con mas avisos.\n"
						" 4 - Salir.\n"
						"\n ~ Ingrese la opcion: "
						," > Error!\n",&opcionInformes,2,1,4);
				switch(opcionInformes)
				{
				case 1:
					printf(" Me falta Clientes con mas avisos");
					break;
				case 2:
					//printf("Cantidad de avisos pausados");
					inf_imprimirCantidadDeAvisosPausados(arrayAvisos,QTY_AVISOS);
					break;
				case 3:
					printf(" Me falta Rubros con mas avisos");
					break;
				}
			}while(opcionInformes != CANT_OPCIONES_INFORMES);
			break;
		}

	}while(op != CANT_OPCIONES);
}

//Ordenamiento
/*if(flagOrdenamiento == 1 && cli_ordenarAlfabeticamente(arrayClientes,QTY_CLIENTES,1) == 0)
{
	printf("\n . Datos ordenados correctamente!\n");
}
else
{
	printf(" > Error!\n");
}*/
