#include <iostream>
#include <python2.7/Python.h>
#include "utils.h"

using namespace std;



void menuPendientes()
{
	int opc = 0;

	while(opc != 5)
	{
		cout << endl << endl;
		cout << "MENU PENDIENTES" << endl;
		cout << "1.- Insertar Pendiente" << endl;
		cout << "2.- Listar pendientes por realizarse" << endl;
		cout << "3.- Listar pendientes realizandose" << endl;
		cout << "4.- Listar pendientes realizados" << endl;
		cout << "5.- Volver al menu anterior" << endl;
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

	while(opc != 6)
	{
		cout << endl << endl;
		cout << "MENU REPORTES" << endl;
		cout << "1.- Listar pendientes realizandose" << endl;
		cout << "2.- Cambiar Estado a LISTO" << endl;
		cout << "3.- Cambiar Estado a PENDIENTE" << endl;
		cout << "4.- Listar pendientes por realizarse" << endl;
		cout << "5.- Listar pendientes realizandos" << endl;
		cout << "6.- Volver al menu anterior" << endl;
		cout << "Opcion: "; cin >> opc;
		switch(opc)
		{
			case 1:
				cout << "Listar pendientes realizandose" << endl;
				listar_realizandose();
				break;
			case 2:
				cout << "Actividades Ejecutadas:" << endl;
				cambiar_estado_realizandose();
				break;
			case 3:
				cout << "Actividades No Ejecutadas:" << endl;
				cambiar_estado_inicial();
				break;
			case 4:
				cout << "Listar pendientes por realizarse" << endl;
				listar_pendientes();
				break;
			case 5:
				cout << "Listar pendientes realizados" << endl;
				listar_listos();
				break;
			case 6:
				cout << "Volver al menu anterior" << endl;
				break;
			default:
				cout << "ERROR: OPCION INCORRECTA" << endl;
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
				//test_model();
				modelo_general_correrlo();
				break;
			case 5:
				cout << "Mostrar Actividades del Dia" << endl;
				listar_realizandose();
				break;
			case 6:
				cout << "Realizar Reporte de Actividades" << endl;
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
	upload_txt_actividades();*/

	/*Py_SetProgramName(argv[0]);
	Py_Initialize();
	PyRun_SimpleString("execfile(\"test.py\")");
	Py_Finalize();*/
	
	menuPrincipal();
	
	return 0;
}
