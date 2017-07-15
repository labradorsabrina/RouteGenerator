#include <iostream>
#include <python2.7/Python.h>
#include "utils.h"
#include <stdlib.h>

using namespace std;



void menuPendientes()
{
	int opc = 0;
	system("clear");
	
	while(opc != 5)
	{
		cout << endl << endl;
		cout << "	Menu de las Tareas Pendientes Por Ejecutar" << endl <<endl;
		cout << "		1.- Insertar Pendiente" << endl;
		cout << "		2.- Listar pendientes por realizarse" << endl;
		cout << "		3.- Informacion de Ayuda" <<endl;
		cout << "		4.- Link del Mapa de vallas" <<endl;
		cout << "		5.- Volver al menu anterior" << endl<<endl;
		cout << "		Opcion: "; cin >> opc;
		cout << endl;
		switch(opc)
		{
			case 1:
				cout << "	Insertar nuevo pendiente" << endl;
				insert_new_pendiente();
				break;
			case 2:
				cout << "	Listar pendientes por realizarse" << endl <<endl;
				listar_pendientes_nuevo();
				break;
			case 3:
				menuAyuda();
				break;
			case 4:
				cout << "	Mapa de vallas en GoogleMaps" << endl;	
				cout << "	https://www.google.co.ve/maps/@10.4289125,-66.9390113,12z/data=!4m2!6m1!1s10jHVhp5HVlOwpTqFppdtcSMouGI?authuser=1" <<endl;
				break;
			case 5:
				cout << "	Volver al menu anterior" << endl;
				break;	
			default:
				cout << "	ERROR: OPCION INCORRECTA" << endl;
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
		cout << endl << endl;
		cout << "	Menu para Reportar Actividades" << endl << endl;
		cout << "		1.- Listar actividades planificadas" << endl;
		cout << "		2.- Ingresar Actividad Realizada" << endl;
		cout << "		3.- Ingresar Actividad No Realizada" << endl;
		cout << "		4.- Suspendida la Jornada Laboral" << endl;
		cout << "		5.- Listar actividades pendientes" << endl;
		cout << "		6.- Listar actividades realizadas" << endl;
		cout << "		7.- Volver al menu anterior" << endl;
		cout << "		Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				cout << " Actividades Planificadas para el Dia: " << endl;
				listar_realizandose();
				cout << endl << endl;
				break;
			case 2:
				cout << endl;
				cout << " Insertar ID de Actividad Realizada --> " ;
				cambiar_estado_realizandose();
				cout << endl << endl;
				break;
			case 3:
				cout << endl;
				cout << " Insertar ID de Actividad No Realizada --> " ;
				cambiar_estado_inicial();
				cout << endl << endl;
				break;
			case 4:
				cout << endl;
				cout << " --> ELIMINADA LA PLANIFICACION DIARIA <--" << endl;
				all_to_inicial();
				cout << endl << endl;
				break;
			case 5:
				system("clear");
				cout << " Actividades pendientes por realizar: " << endl;
				listar_pendientes_nuevo();
				cout << endl << endl;
				break;
			case 6:
				system("clear");
				cout << " Actividades Realizadas: " << endl;
				listar_listos();
				cout << endl << endl;
				break;
			case 7:
				cout << " Volver al menu anterior" << endl;
				verifica();
				cout << endl << endl;
				break;
			default:
				cout << "ERROR: OPCION INCORRECTA" << endl;
				cout << endl << endl;
				break;
		}
	}
}


void menuBD()
{
	system("clear");
	int opc = 0;
	
	while(opc != 6)
	{
		cout << endl << endl;
		cout << "    Gestion de Base de Datos" << endl<<endl;
		cout << "    1.- Insertar Valla" << endl;
		cout << "    2.- Listar Vallas" << endl;
		cout << "    3.- Insertar Actividad" << endl;
		cout << "    4.- Listar Actividades" << endl;
		cout << "    5.- Llenado de BD con archivos (vallas.txt y actividades.txt)" << endl;
		cout << "    6.- Volver al menu anterior" << endl<<endl;
		cout << "    Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				cout << "  Insertar nueva valla" << endl;
				insert_new_valla();
				break;
			case 2:
				cout << "  Listado de Vallas" << endl;
				getAllTableDataVallas();
				break;
			case 3:
				cout << "  Insertar nueva Actividad" << endl;
				insert_new_actividad();
				break;
			case 4:
				cout << "  Listado de Actividades" << endl;
				getAllTableDataActividades();
				break;
			case 5:
				create_table_vallas();
				create_table_actividades();
				create_table_pendientes();
				upload_txt_vallas();
				upload_txt_actividades();
				break;
			case 6:
				cout << endl<< endl;
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
	
	while(opc != 6)
	{
		system("clear");
		cout << endl << endl;
		cout << "    Gestion Operativa de Vallas [GTM 2014 C.A.]" << endl<<endl;
		cout << "        1.- Gestion de BD" << endl;
		cout << "        2.- Gestion de Tareas Pendientes" << endl;
		cout << "        3.- Correr el Modelo" << endl;
		cout << "        4.- Imprimir Planificacion" << endl;
		cout << "        5.- Reportar Actividades" <<endl;
		cout << "        6.- Salir" << endl<<endl;
		cout << "        Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				menuBD();
				break;
			case 2:
				menuPendientes();
				break;
			case 3:
				system("clear");
				cout << "      -----> Generar Planificacion Diaria <-----" << endl<<endl;
				modelo_general_correrlo();
				break;
			case 4:
				system("geany OC.txt");
				break;
			case 5:
				menuReportes();
				break;
			case 6:
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
