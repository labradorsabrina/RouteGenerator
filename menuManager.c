#include <iostream>
#include <python2.7/Python.h>
#include "utils.h"
#include <stdlib.h>

using namespace std;



void menuPendientes()
{
	int opc = 0;

	while(opc != 7)
	{
		cout << endl << endl;
		cout << "MENU PENDIENTES" << endl;
		cout << "1.- Insertar Pendiente" << endl;
		cout << "2.- Listar pendientes por realizarse" << endl;
		cout << "3.- Listar pendientes realizandose" << endl;
		cout << "4.- Listar pendientes realizados" << endl;
		cout << "5.- Imprimir codigos de vallas" <<endl;
		cout << "6.- Imprimir codigos de actividades" <<endl;
		cout << "7.- Volver al menu anterior" << endl;
		cout << "Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				cout << "Insertar nuevo pendiente" << endl;
				insert_new_pendiente();
				break;
			case 2:
				cout << "Listar pendientes por realizarse" << endl;
				listar_pendientes();
				break;
			case 3:
				cout << "Listar pendientes realizandose" << endl;
				listar_realizandose();
				break;
			case 4:
				cout << "Listar pendientes realizados" << endl;
				listar_listos();
				break;
			case 5:
				cout << "Codigos de Vallas" << endl;
				getAllCodesVallas();
				break;
			case 6:
				cout << "Codigos de Actividades" << endl;
				getAllCodesActividades();
				break;
			case 7:
				cout << "Volver al menu anterior" << endl;
				break;	
			default:
				cout << "ERROR: OPCION INCORRECTA" << endl;
				break;
		}
	}
}

void menuReportes()
{
	int opc = 0;
	system("clear");
	while(opc != 7)
	{
		cout << "MENU REPORTES" << endl;
		cout << "1.- Listar actividades planificadas" << endl;
		cout << "2.- Cambiar Estado a LISTO" << endl;
		cout << "3.- Cambiar Estado a PENDIENTE" << endl;
		cout << "4.- Jornada laboral anulada" << endl;
		cout << "5.- Listar actividades pendientes" << endl;
		cout << "6.- Listar actividades realizadas" << endl;
		cout << "7.- Volver al menu anterior" << endl;
		cout << "Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				cout << "Actividades Planificadas para el Dia: " << endl;
				listar_realizandose();
				cout << endl << endl;
				break;
			case 2:
				cout << "Insertar ID de Actividad Ejecutada --> " ;
				cambiar_estado_realizandose();
				cout << endl << endl;
				break;
			case 3:
				cout << "Insertar ID de Actividad No Ejecutada --> " ;
				cambiar_estado_inicial();
				cout << endl << endl;
				break;
			case 4:
				cout << "--> ANULADA LA PLANIFICACION DIARIA <--" << endl;
				all_to_inicial();
				cout << endl << endl;
				break;
			case 5:
				system("clear");
				cout << "Actividades pendientes por realizar: " << endl;
				listar_pendientes();
				cout << endl << endl;
				break;
			case 6:
				system("clear");
				cout << "Actividades Realizadas: " << endl;
				listar_listos();
				cout << endl << endl;
				break;
			case 7:
				cout << "Volver al menu anterior" << endl;
				cout << endl << endl;
				break;
			default:
				cout << "ERROR: OPCION INCORRECTA" << endl;
				cout << endl << endl;
				break;
		}
	}
}


void menuActividades()
{
	int opc = 0;

	while(opc != 3)
	{
		cout << endl << endl;
		cout << "MENU ACTIVIDADES" << endl;
		cout << "1.- Insertar Actividades" << endl;
		cout << "2.- Listar Actividades" << endl;
		cout << "3.- Volver al menu anterior" << endl;
		cout << "Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				cout << "Insertar nueva Actividad" << endl;
				insert_new_actividad();
				break;
			case 2:
				cout << "Listado de Actividades" << endl;
				getAllTableDataActividades();
				break;
			case 3:
				cout << "Volviendo al menu anterior" << endl;
				break;
			default:
				cout << "ERROR: OPCION INCORRECTA" << endl;
				break;
		}
	}
}


void menuVallas()
{
	int opc = 0;

	while(opc != 3)
	{
		cout << endl << endl;
		cout << "MENU VALLAS" << endl;
		cout << "1.- Insertar Vallas" << endl;
		cout << "2.- Listar Vallas" << endl;
		cout << "3.- Volver al menu anterior" << endl;
		cout << "Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				cout << "Insertar nueva valla" << endl;
				insert_new_valla();
				break;
			case 2:
				cout << "Listado de Vallas" << endl;
				getAllTableDataVallas();
				break;
			case 3:
				cout << "Volviendo al menu anterior" << endl;
				break;
			default:
				cout << "ERROR: OPCION INCORRECTA" << endl;
				break;
		}
	}
}

void menuPrincipal()
{
	int opc = 0;
	
	while(opc != 7)
	{
		system("clear");
		cout << endl << endl;
		cout << "    Gestion Operativa de Vallas [GTM 2014 C.A.]" << endl<<endl;
		cout << "        1.- Control de Vallas" << endl;
		cout << "        2.- Control de Actividades" << endl;
		cout << "        3.- Control de Pendientes" << endl;
		cout << "        4.- Correr el Modelo" << endl;
		cout << "        5.- Imprimir Planificacion" << endl;
		cout << "        6.- Reportar Actividades" <<endl;
		cout << "        7.- Salir" << endl<<endl;
		cout << "        Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				cout << "Control de Vallas" << endl;
				menuVallas();
				break;
			case 2:
				cout << "Control de Actividades" << endl;
				menuActividades();
				break;
			case 3:
				cout << "Control de Pendientes" << endl;
				menuPendientes();
				break;
			case 4:
				cout << "Corriendo Modelo" << endl;
				modelo_general_correrlo();
				break;
			case 5:
				system("geany OC.txt");
				break;
			case 6:
				menuReportes();
				break;
			case 7:
				cout << endl<< endl;
				break;
			default:
				cout << "ERROR: OPCION INCORRECTA" << endl;
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	/*create_table_vallas();
	create_table_actividades();
	create_table_pendientes();
	upload_txt_vallas();
	upload_txt_actividades();
	//listar_pendientes_test();
	/*Py_SetProgramName(argv[0]);
	Py_Initialize();
	PyRun_SimpleString("execfile(\"test.py\")");
	Py_Finalize();*/
	//test_create_data_model();
	/*read_matrix_distance();
	list<string>  codes;
	int num_vallas;
	int ** matriz;
	read_matrix_distance_getALLVALUES(num_vallas,codes,matriz);
	cout << num_vallas << endl;
	for (std::list<string>::iterator it=codes.begin(); it != codes.end(); ++it)
    		cout << *it << endl;
    
    cout << matriz[0][0] << endl;
    for(int i = 0 ; i < num_vallas; i++)
		{
			for(int j = 0 ; j < num_vallas; j++)
			{
				cout << matriz[i][j] << " ";
			}
			cout << endl;
		}*/
	//std::cout << timestamp_to_seconds("2013-07-05") << std::endl;
	//listar_pendientes_nuevo();
	//test_obtener_vallas_no_repetidas();
	//test_obtener_vallas_no_repetidas_para_usar();
	//probar_obtener_matriz_de_distancia();
	menuPrincipal();
	//int numVehi = test_create_data_model1(false);
	
	return 0;
}
