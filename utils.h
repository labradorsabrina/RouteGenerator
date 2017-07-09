#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <list>
#include <glpk.h>
#include <python2.7/Python.h>
#include <ctime>
#include <functional>
#include <cstring>


using namespace std;

//Conteo de Tiempo
std::size_t timestamp_to_seconds(const char* timestamp)
{
    std::tm tm_struct;

    strptime(timestamp, "%Y-%m-%d", &tm_struct);
    tm_struct.tm_isdst = 1;
    std::size_t t = std::mktime(&tm_struct);

    return t;
}

//Estructura 1: Valla
struct valla
{
	int id;
	string codigo;
	string origen;
	string estado;
	string parroquia;
	string municipio;
	string direccion;
	string condicion;
	string visual;
	string tipo;
	string alto;
	string ancho;
	string longitud;
	string latitud;
	int inicio;
	int fin;
	
};

//Estructura 2: Actividad
struct actividad
{
	int id;
	string codigo;
	string tipo;
	string descripcion;
	int tiempo;
	int prioridad;
	int instalacion;
};

//Estructura 3: Pendiente
struct pendiente
{
	int id;
	string codigo_valla;
	string codigo_actividad;
	int prioridad;
	int tiempo;
	string fecha;
	string estado;
};

//Funcion callback para la creacion de las BD
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

//Sobrecarga del operador ==
bool operator == (valla &va1, valla &va2)
{
	return (va1.codigo == va2.codigo);
}

//Sobre carga del operador <<
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

//Crea BD de vallas
void create_table_vallas()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char *sql;

	/* Open database */
	rc = sqlite3_open("tesisData.db", &db);
	if( rc ){
	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    return;
	}else{
	    //fprintf(stdout, "Opened database successfully\n");
	}

	/* Create SQL statement */
	sql = "CREATE TABLE VALLAS( ID INTEGER PRIMARY KEY   AUTOINCREMENT , CODIGO        TEXT    NOT NULL, ORIGEN        TEXT    NOT NULL, ESTADO        TEXT    NOT NULL, PARROQUIA     TEXT    NOT NULL, MUNICIPIO     TEXT    NOT NULL, DIRECCION     TEXT    NOT NULL, CONDICION     TEXT    NOT NULL, VISUAL        TEXT    NOT NULL, TIPO          TEXT    NOT NULL, ALTO          TEXT    NOT NULL, ANCHO         TEXT    NOT NULL, LONGITUD      TEXT    NOT NULL, LATITUD       TEXT    NOT NULL, INICIO        INT     NOT NULL, FIN           INT     NOT NULL);";

	/*
	sql = "CREATE TABLE VALLAS( ID INTEGER PRIMARY KEY   AUTOINCREMENT ," \
	        "CODIGO        TEXT    NOT NULL," \
	        "ORIGEN        TEXT    NOT NULL," \
	        "ESTADO        TEXT    NOT NULL," \
	        "PARROQUIA     TEXT    NOT NULL," \
	        "MUNICIPIO     TEXT    NOT NULL," \
	        "DIRECCION     TEXT    NOT NULL," \
	        "CONDICION     TEXT    NOT NULL," \
	        "VISUAL        TEXT    NOT NULL," \
	        "TIPO          TEXT    NOT NULL," \
	        "ALTO          TEXT    NOT NULL," \
	        "ANCHO         TEXT    NOT NULL," \
	        "LONGITUD      TEXT    NOT NULL," \
	        "LATITUD       TEXT    NOT NULL," \
	        "INICIO        INT     NOT NULL," \
	        "FIN           INT     NOT NULL );";
	*/

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	}else{
	    fprintf(stdout, "Table created successfully\n");
	}
	sqlite3_close(db);
}

//Crea BD de actividades
void create_table_actividades()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char *sql;

	/* Open database */
	rc = sqlite3_open("tesisData.db", &db);
	if( rc ){
	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    return;
	}else{
	    //fprintf(stdout, "Opened database successfully\n");
	}

	/* Create SQL statement */
	sql = "CREATE TABLE ACTIVIDADES( ID INTEGER PRIMARY KEY   AUTOINCREMENT  , CODIGO        TEXT    NOT NULL, TIPO          TEXT    NOT NULL, DESCRIPCION    TEXT    NOT NULL, TIEMPO        INT     NOT NULL, PRIORIDAD     INT     NOT NULL, INSTALACION   INT  NOT NULL );";
	
	/*
	sql = "CREATE TABLE ACTIVIDADES( ID INTEGER PRIMARY KEY   AUTOINCREMENT ," \
	        "CODIGO         TEXT    NOT NULL," \
	        "TIPO           TEXT    NOT NULL," \
	        "DESCRIPCION    TEXT    NOT NULL," \
	        "TIEMPO         INT     NOT NULL," \
	    	"PRIORIDAD      INT     NOT NULL," \
	        "INSTALACION    INT     NOT NULL );";
	*/

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	}else{
	    fprintf(stdout, "Table created successfully\n");
	}
	sqlite3_close(db);
}

//Crea BD de pendientes
void create_table_pendientes()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char *sql;

	/* Open database */
	rc = sqlite3_open("tesisData.db", &db);
	if( rc ){
	    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    return;
	}else{
	    //fprintf(stdout, "Opened database successfully\n");
	}

	/* Create SQL statement */
	sql = "CREATE TABLE PENDIENTES( ID INTEGER PRIMARY KEY   AUTOINCREMENT , CODIGO_VALLA       TEXT  NOT NULL, CODIGO_ACTIVIDAD    TEXT  NOT NULL, PRIORIDAD           INT   NOT NULL, TIEMPO    			INT   NOT NULL, FECHA    			TEXT  NOT NULL, ESTADO     		TEXT  NOT NULL );";
	
	/*
	sql = "CREATE TABLE PENDIENTES("\ 
			"ID INTEGER PRIMARY KEY   AUTOINCREMENT ," \
	        "CODIGO_VALLA       TEXT  NOT NULL," \
	        "CODIGO_ACTIVIDAD   TEXT  NOT NULL," \
	        "PRIORIDAD          INT   NOT NULL," \
	        "TIEMPO    			INT   NOT NULL," \
	        "FECHA    			TEXT  NOT NULL," \
	        "ESTADO     		TEXT  NOT NULL );";
	*/

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    sqlite3_free(zErrMsg);
	}else{
	    fprintf(stdout, "Table created successfully\n");
	}
	sqlite3_close(db);
}

//Insertar una valla
void insert_value_valla(valla v)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;

    /* Open database */
    rc = sqlite3_open("tesisData.db", &db);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }
    /*
    int id;
	string codigo;
	string origen;
	string estado;
	string parroquia;
	string municipio;
	string direccion;
	string condicion;
	string visual;
	string tipo;
	string alto;
	string ancho;
	string longitud;
	string latitud;
	int inicio;
	int fin;
    */

    /* Create SQL statement */
    string insert = "INSERT INTO VALLAS (CODIGO,ORIGEN,ESTADO,PARROQUIA,MUNICIPIO,DIRECCION,CONDICION,VISUAL,TIPO,ALTO,ANCHO,LONGITUD,LATITUD,INICIO,FIN) ";
    insert = insert + "VALUES (";
    insert = insert + "'" +v.codigo + "',";
    insert = insert + "'" +v.origen + "',";
    insert = insert + "'" +v.estado + "',";
    insert = insert + "'" +v.parroquia + "',";
    insert = insert + "'" +v.municipio + "',";
    insert = insert + "'" +v.direccion + "',";
    insert = insert + "'" +v.condicion + "',";
    insert = insert + "'" +v.visual + "',";
    insert = insert + "'" +v.tipo + "',";
    insert = insert + "'" +v.alto + "',";
    insert = insert + "'" +v.ancho + "',";
    insert = insert + "'" +v.longitud + "',";
    insert = insert + "'" +v.latitud + "',";
    insert = insert + static_cast<ostringstream*>( &(ostringstream() << v.inicio) )->str() + ",";
    insert = insert + static_cast<ostringstream*>( &(ostringstream() << v.fin) )->str() ;
    insert = insert + ");";

    cout << insert <<endl;

    sql = insert.c_str();

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}

//Escribir una newvalla.txt
void writeNewValla(valla va)
{
	ofstream arch;
	arch.open("newvalla.txt");
	if(!arch)
	{
		cout << "Error" << endl;
	}
	else
	{
		arch << va.codigo;
		arch.close();
	}
}

//Inserta una nueva valla en la BD
void insert_new_valla()
{
	valla va;
	
	cout << "CODIGO: "; cin>> va.codigo;
	cout << "ORIGEN: " ; cin>> va.origen ;
	cout << "ESTADO: " ; cin>> va.estado ;
	cout << "PARROQUIA: " ; cin>> va.parroquia ;
	cout << "MUNICIPIO: " ; cin>> va.municipio ;
	cout << "DIRECCION: " ; cin>> va.direccion ;
	cout << "CONDICION: " ; cin>> va.condicion ;
	cout << "VISUAL: " ; cin>> va.visual ;
	cout << "TIPO: " ; cin>> va.tipo ;
	cout << "ALTO: " ; cin>> va.alto ;
	cout << "ANCHO: " ; cin>> va.ancho ;
	cout << "LONGITUD: " ; cin>> va.longitud ;
	cout << "LATITUD: " ; cin>> va.latitud ;
	cout << "INICIO (INT): " ; cin>> va.inicio ;
	cout << "FIN (INT): " ; cin>> va.fin ;
	insert_value_valla(va);
	cout << "ID: " << va.id << endl;
	cout << "CODIGO: " << va.codigo << endl;
	cout << "ORIGEN: " << va.origen << endl;
	cout << "ESTADO: " << va.estado << endl;
	cout << "PARROQUIA: " << va.parroquia << endl;
	cout << "MUNICIPIO: " << va.municipio << endl;
	cout << "DIRECCION: " << va.direccion << endl;
	cout << "CONDICION: " << va.condicion << endl;
	cout << "VISUAL: " << va.visual << endl;
	cout << "TIPO: " << va.tipo << endl;
	cout << "ALTO: " << va.alto << endl;
	cout << "ANCHO: " << va.ancho << endl;
	cout << "LONGITUD: " << va.longitud << endl;
	cout << "LATITUD: " << va.latitud << endl;
	cout << "INICIO (INT): " << va.inicio << endl;
	cout << "FIN: (INT): " << va.fin << endl <<endl;
	
}

//Consulta la BD de vallas
void getAllTableDataVallas()
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    char *query = "SELECT * FROM VALLAS";

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
            	/*
			    int id;
				string codigo;
				string origen;
				string estado;
				string parroquia;
				string municipio;
				string direccion;
				string condicion;
				string visual;
				string tipo;
				string alto;
				string ancho;
				string longitud;
				string latitud;
				int inicio;
				int fin;
			    */
            	int id = sqlite3_column_int(statement, 0);
            	string codigo = (char*)sqlite3_column_text(statement, 1);
            	string origen = (char*)sqlite3_column_text(statement, 2);
            	string estado = (char*)sqlite3_column_text(statement, 3);
            	string parroquia = (char*)sqlite3_column_text(statement, 4);
            	string municipio = (char*)sqlite3_column_text(statement, 5);
            	string direccion = (char*)sqlite3_column_text(statement, 6);
				string condicion = (char*)sqlite3_column_text(statement, 7);
            	string visual = (char*)sqlite3_column_text(statement, 8);
            	string tipo = (char*)sqlite3_column_text(statement, 9);
				string alto = (char*)sqlite3_column_text(statement, 10);
            	string ancho = (char*)sqlite3_column_text(statement, 11);
            	string longitud = (char*)sqlite3_column_text(statement, 12);
            	string latitud = (char*)sqlite3_column_text(statement, 13);
            	int inicio = sqlite3_column_int(statement, 14);
            	int fin = sqlite3_column_int(statement, 15);

            	cout << "ID: " << id << " ";
            	cout << "CODIGO: " << codigo << " ";
            	cout << "ORIGEN: " << origen << " ";
            	cout << "ESTADO: " << estado << " ";
            	cout << "PARROQUIA: " << parroquia << " ";
            	cout << "MUNICIPIO: " << municipio << " ";
            	cout << "DIRECCION: " << direccion << " ";
            	cout << "CONDICION: " << condicion << " ";
            	cout << "VISUAL: " << visual << " ";
            	cout << "TIPO: " << tipo << " ";
            	cout << "ALTO: " << alto << " ";
            	cout << "ANCHO: " << ancho << " ";
            	cout << "LONGITUD: " << longitud << " ";
            	cout << "LATITUD: " << latitud << " ";
            	cout << "INICIO: " << inicio << " ";
            	cout << "FIN: " << fin << endl << endl;

            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

void getAllCodesVallas()
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    char *query = "SELECT * FROM VALLAS";

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
        
            	int id = sqlite3_column_int(statement, 0);
            	string codigo = (char*)sqlite3_column_text(statement, 1);
            	string origen = (char*)sqlite3_column_text(statement, 2);
            	string estado = (char*)sqlite3_column_text(statement, 3);
            	string parroquia = (char*)sqlite3_column_text(statement, 4);
            	string municipio = (char*)sqlite3_column_text(statement, 5);
            	string direccion = (char*)sqlite3_column_text(statement, 6);
				string condicion = (char*)sqlite3_column_text(statement, 7);
            	string visual = (char*)sqlite3_column_text(statement, 8);
            	string tipo = (char*)sqlite3_column_text(statement, 9);
				string alto = (char*)sqlite3_column_text(statement, 10);
            	string ancho = (char*)sqlite3_column_text(statement, 11);
            	string longitud = (char*)sqlite3_column_text(statement, 12);
            	string latitud = (char*)sqlite3_column_text(statement, 13);
            	int inicio = sqlite3_column_int(statement, 14);
            	int fin = sqlite3_column_int(statement, 15);;


            	cout << "Codigo: " << codigo << "    "; 
            	cout << "Tipo: " << tipo << " "<<endl;
            	
            	string ruta = "https://www.google.co.ve/maps/dir/";
            	
            	ruta += latitud;
            	ruta += ",";
            	ruta += longitud;
            	ruta += "/";
            	
            	cout << "GoogleMaps: " << ruta << endl<<endl;

            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

//Inserta una actividad en BD
void insert_value_actividad(actividad ac)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;

    /* Open database */
    rc = sqlite3_open("tesisData.db", &db);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }
    /*
    int id;
	string codigo;
	string tipo;
	string descripcion;
	int tiempo;
	int prioridad;
    */

    /* Create SQL statement */
    string insert = "INSERT INTO ACTIVIDADES (CODIGO,TIPO,DESCRIPCION,TIEMPO,PRIORIDAD,INSTALACION) ";
    insert = insert + "VALUES (";
    insert = insert + "'" +ac.codigo + "',";
    insert = insert + "'" +ac.tipo + "',";
    insert = insert + "'" +ac.descripcion + "',";
    insert = insert + static_cast<ostringstream*>( &(ostringstream() << ac.tiempo) )->str() + ",";
    insert = insert + static_cast<ostringstream*>( &(ostringstream() << ac.prioridad) )->str() + ",";
    insert = insert + static_cast<ostringstream*>( &(ostringstream() << ac.instalacion) )->str() ;
    insert = insert + ");";

    //cout << insert <<endl;

    sql = insert.c_str();

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}

//Consultar lista de Pendientes
void getDataTableDataActividades(string codigo, actividad * ac)
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    string q_select = "SELECT * FROM ACTIVIDADES WHERE CODIGO == ";
    q_select += "'" +codigo + "';";
    const char *query = q_select.c_str();
    //cout << q_select << endl;

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
            	/*
			    int id;
				string codigo_valla;
				string codigo_actividad;
				int prioridad;
				int tiempo;
				string fecha;
				string estado;
			    */

		ac->id = sqlite3_column_int(statement, 0);
            	ac->codigo = (char*)sqlite3_column_text(statement, 1);
            	ac->tipo = (char*)sqlite3_column_text(statement, 2);
            	ac->descripcion = (char*)sqlite3_column_text(statement, 3);
            	ac->tiempo = sqlite3_column_int(statement, 4);
            	ac->prioridad = sqlite3_column_int(statement, 5);
		ac->instalacion = sqlite3_column_int(statement, 6);
            	
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

//consulta la BD de vallas buscando una valla en especifico
void getDataTableDataVallas(string codigo, valla * va)
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    string q_select = "SELECT * FROM VALLAS WHERE CODIGO == ";
    q_select += "'" +codigo + "';";
    const char *query = q_select.c_str();
    //cout << q_select << endl;

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
            	/*
			    int id;
				string codigo;
				string origen;
				string estado;
				string parroquia;
				string municipio;
				string direccion;
				string condicion;
				string visual;
				string tipo;
				string alto;
				string ancho;
				string longitud;
				string latitud;
				int inicio;
				int fin;
			    */
            	va->id = sqlite3_column_int(statement, 0);
            	va->codigo = (char*)sqlite3_column_text(statement, 1);
            	va->origen = (char*)sqlite3_column_text(statement, 2);
            	va->estado = (char*)sqlite3_column_text(statement, 3);
            	va->parroquia = (char*)sqlite3_column_text(statement, 4);
            	va->municipio = (char*)sqlite3_column_text(statement, 5);
            	va->direccion = (char*)sqlite3_column_text(statement, 6);
				va->condicion = (char*)sqlite3_column_text(statement, 7);
            	va->visual = (char*)sqlite3_column_text(statement, 8);
            	va->tipo = (char*)sqlite3_column_text(statement, 9);
				va->alto = (char*)sqlite3_column_text(statement, 10);
            	va->ancho = (char*)sqlite3_column_text(statement, 11);
            	va->longitud = (char*)sqlite3_column_text(statement, 12);
            	va->latitud = (char*)sqlite3_column_text(statement, 13);
            	va->inicio = sqlite3_column_int(statement, 14);
            	va->fin = sqlite3_column_int(statement, 15);
            	
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

//Inserta nueva actividad por consola
void insert_new_actividad()
{
	actividad ac;

	cout << "CODIGO: " ; cin >> ac.codigo ;
	cout << "TIPO: " ; cin >>  ac.tipo ;
	cout << "DESCRIPCION: " ; cin >>  ac.descripcion ;
	cout << "TIEMPO (INT): " ; cin >>  ac.tiempo ;
	cout << "PRIORIDAD (INT): " ; cin >>  ac.prioridad ;
	cout << "INSTALACION (INT): " ; cin >>  ac.instalacion ;
	insert_value_actividad(ac);
	cout << "ID: " << ac.id << endl;
	cout << "CODIGO: " << ac.codigo << endl;
	cout << "TIPO: " << ac.tipo << endl;
	cout << "DESCRIPCION: " << ac.descripcion << endl;
	cout << "TIEMPO (INT): " << ac.tiempo << endl;
	cout << "PRIORIDAD (INT): " << ac.prioridad << endl;
	cout << "INSTALACION (INT): " << ac.instalacion << endl;
}

//Consultar la BD de actividades
void getAllTableDataActividades()
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    char *query = "SELECT * FROM ACTIVIDADES";

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
            	/*
			    int id;
				string codigo;
				string tipo;
				string descripcion;
				int tiempo;
				int prioridad;
				int instalacion;
			    */
            	int id = sqlite3_column_int(statement, 0);
            	string codigo = (char*)sqlite3_column_text(statement, 1);
            	string tipo = (char*)sqlite3_column_text(statement, 2);
            	string descripcion = (char*)sqlite3_column_text(statement, 3);
            	int tiempo = sqlite3_column_int(statement, 4);
            	int prioridad = sqlite3_column_int(statement, 5);
				int instalacion = sqlite3_column_int(statement, 6);

            	cout << "ID: " << id << " ";
            	cout << "CODIGO: " << codigo << " ";
            	cout << "TIPO: " << tipo << " ";
            	cout << "DESCRIPCION: " << descripcion << " ";
            	cout << "TIEMPO: " << tiempo << " ";
            	cout << "PRIORIDAD: " << prioridad << " ";
				cout << "INSTALACION: " << instalacion << endl << endl;

            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

//Imprime codigo de actividades
void getAllCodesActividades()
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    char *query = "SELECT * FROM ACTIVIDADES";

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
            	
            	int id = sqlite3_column_int(statement, 0);
            	string codigo = (char*)sqlite3_column_text(statement, 1);
            	string tipo = (char*)sqlite3_column_text(statement, 2);
            	string descripcion = (char*)sqlite3_column_text(statement, 3);
            	int tiempo = sqlite3_column_int(statement, 4);
            	int prioridad = sqlite3_column_int(statement, 5);
				int instalacion = sqlite3_column_int(statement, 6);

            	
            	cout << "Codigo: " << codigo << " ";
            	cout << "--> " << descripcion << " "<<endl;
            

            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

//Insertar nuevo Pendiente
void insert_value_pendiente(pendiente pe)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;

    /* Open database */
    rc = sqlite3_open("tesisData.db", &db);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }
    /*
    int id;
	string codigo_valla;
	string codigo_actividad;
	int prioridad;
	int tiempo;
	string fecha;
	string estado;
    */

    /* Create SQL statement */
    string insert = "INSERT INTO PENDIENTES (CODIGO_VALLA,CODIGO_ACTIVIDAD,PRIORIDAD,TIEMPO,FECHA,ESTADO) ";
    insert = insert + "VALUES (";
    insert = insert + "'" +pe.codigo_valla + "',";
    insert = insert + "'" +pe.codigo_actividad + "',";
    insert = insert + static_cast<ostringstream*>( &(ostringstream() << pe.prioridad) )->str() + ",";
    insert = insert + static_cast<ostringstream*>( &(ostringstream() << pe.tiempo) )->str() + ",";
    insert = insert + "'" +pe.fecha + "',";
    insert = insert + "'" +pe.estado+ "'";
    insert = insert + ");";

    //cout << insert <<endl;

    sql = insert.c_str();

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
}

//Buscar en lista de Pendientes
void getDataTableDataPendientes(int id, pendiente pe)
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    string q_select = "SELECT * FROM PENDIENTES WHERE ID == ";
    q_select += static_cast<ostringstream*>( &(ostringstream() << id) )->str();
    const char *query = q_select.c_str();
    cout << q_select << endl;

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
            	/*
			    int id;
				string codigo_valla;
				string codigo_actividad;
				int prioridad;
				int tiempo;
				string fecha;
				string estado;
			    */
            	pe.id = sqlite3_column_int(statement, 0);
            	pe.codigo_valla = (char*)sqlite3_column_text(statement, 1);
            	pe.codigo_actividad = (char*)sqlite3_column_text(statement, 2);
            	pe.prioridad = sqlite3_column_int(statement, 3);
            	pe.tiempo = sqlite3_column_int(statement, 4);
            	pe.fecha = (char*)sqlite3_column_text(statement, 5);
            	pe.estado = (char*)sqlite3_column_text(statement, 6);

				cout << "ID: " << pe.id << " ";
		    	cout << "CODIGO_VALLA: " << pe.codigo_valla << " ";
		    	cout << "CODIGO_ACTIVIDAD: " << pe.codigo_actividad << " ";
		    	cout << "PRIORIDAD: " << pe.prioridad << " ";
		    	cout << "TIEMPO: " << pe.tiempo << " ";
		    	cout << "FECHA: " << pe.fecha << " ";
		    	cout << "ESTADO: " << pe.estado << endl;
            	
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

//Burcar por estado en lista de pendientes
void getDataTableDataPendientes_estado(string estado, pendiente pe, list<pendiente> & lista_pendientes)
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    string q_select = "SELECT * FROM PENDIENTES WHERE ESTADO == ";
    q_select += "'"+estado+"'";
    const char *query = q_select.c_str();
    //cout << q_select << endl;

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
            	/*
			    int id;
				string codigo_valla;
				string codigo_actividad;
				int prioridad;
				int tiempo;
				string fecha;
				string estado;
			    */
            	pe.id = sqlite3_column_int(statement, 0);
            	pe.codigo_valla = (char*)sqlite3_column_text(statement, 1);
            	pe.codigo_actividad = (char*)sqlite3_column_text(statement, 2);
            	pe.prioridad = sqlite3_column_int(statement, 3);
            	pe.tiempo = sqlite3_column_int(statement, 4);
            	pe.fecha = (char*)sqlite3_column_text(statement, 5);
            	pe.estado = (char*)sqlite3_column_text(statement, 6);

            	cout << "ID: " << pe.id << " ";
            	cout << "CODIGO_VALLA: " << pe.codigo_valla << " ";
            	cout << "CODIGO_ACTIVIDAD: " << pe.codigo_actividad << " ";
            	cout << "PRIORIDAD: " << pe.prioridad << " ";
            	cout << "TIEMPO: " << pe.tiempo << " ";
            	cout << "FECHA: " << pe.fecha << " ";
            	cout << "ESTADO: " << pe.estado << endl << endl;

            	lista_pendientes.push_back(pe);
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

//Consulta la BD de pendientes segun un estado especifico y devuelve una lista pendientes 
void getDataTableDataPendientes_estado_only(string estado, pendiente pe, list<pendiente> & lista_pendientes)
{
    sqlite3_stmt * statement;
    sqlite3 * dbfile;
    char *zErrMsg = 0;
    int rc;    

    string q_select = "SELECT * FROM PENDIENTES WHERE ESTADO == ";
    q_select += "'"+estado+"'";
    const char *query = q_select.c_str();
    //cout << q_select << endl;

    /* Open database */
    rc = sqlite3_open("tesisData.db", &dbfile);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbfile));
      return;
    }else{
      //fprintf(stderr, "Opened database successfully\n");
    }


    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
            	/*
			    int id;
				string codigo_valla;
				string codigo_actividad;
				int prioridad;
				int tiempo;
				string fecha;
				string estado;
			    */
            	pe.id = sqlite3_column_int(statement, 0);
            	pe.codigo_valla = (char*)sqlite3_column_text(statement, 1);
            	pe.codigo_actividad = (char*)sqlite3_column_text(statement, 2);
            	pe.prioridad = sqlite3_column_int(statement, 3);
            	pe.tiempo = sqlite3_column_int(statement, 4);
            	pe.fecha = (char*)sqlite3_column_text(statement, 5);
            	pe.estado = (char*)sqlite3_column_text(statement, 6);

            	lista_pendientes.push_back(pe);
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }

    sqlite3_close(dbfile);
}

//Cambiar el estado de un pendiente a pendiente
void updateDataTableDataPendientes_pendiente(int id, pendiente pe)
{

    sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("tesisData.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
   }else{
      //fprintf(stderr, "Opened database successfully\n");
   }

   /* Create merged SQL statement */
   //sql = "UPDATE PENDIENTES set ESTADO = 'Realizandose' where ID=1; ";
   string q_select = "UPDATE PENDIENTES set ESTADO = 'Pendiente' where ID=";
    q_select += static_cast<ostringstream*>( &(ostringstream() << id) )->str();
    const char *sql = q_select.c_str();
    //cout << q_select << endl;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      //fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}

//Cambia el estado de un pendiente a realizandose
void updateDataTableDataPendientes_realizandose(int id, pendiente pe)
{

    sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("tesisData.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
   }else{
      //fprintf(stderr, "Opened database successfully\n");
   }

   /* Create merged SQL statement */
   //sql = "UPDATE PENDIENTES set ESTADO = 'Realizandose' where ID=1; ";
   string q_select = "UPDATE PENDIENTES set ESTADO = 'Realizandose' where ID=";
    q_select += static_cast<ostringstream*>( &(ostringstream() << id) )->str();
    const char *sql = q_select.c_str();
    //cout << q_select << endl;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      //fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}

//Cambiar el estado de un pendiente a listo
void updateDataTableDataPendientes_listo(int id, pendiente pe)
{

    sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("tesisData.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return;
   }else{
      //fprintf(stderr, "Opened database successfully\n");
   }

   /* Create merged SQL statement */
   //sql = "UPDATE PENDIENTES set ESTADO = 'Listo' where ID=1; ";
   string q_select = "UPDATE PENDIENTES set ESTADO = 'Listo' where ID=";
    q_select += static_cast<ostringstream*>( &(ostringstream() << id) )->str();
    const char *sql = q_select.c_str();
    //cout << q_select << endl;

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      //fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
}

//Myfunction es una funcion que organiza los pendientes segun tipo y luego segun fecha
bool myfunction (pendiente a,pendiente b) 
{
	bool option = false;
	actividad ac1;
	actividad ac2;
	getDataTableDataActividades(a.codigo_actividad, &ac1);
	getDataTableDataActividades(b.codigo_actividad, &ac2);
	
	if(ac1.instalacion == 1 && ac2.instalacion == 0)
	{
		option = true;
	}
	else
	{
		if(ac1.instalacion == 0 && ac2.instalacion == 1)
		{
			option = false;
		}
		else
		{
			if(timestamp_to_seconds(a.fecha.c_str()) < timestamp_to_seconds(b.fecha.c_str()))
			{
				option = true;
			}
			else
			{
				option = false;
			}
		}
	}
	return option; 
}

//Mostrar todas las actividades pendientes
void listar_pendientes()
{
	list<pendiente> lista_pendientes;
	string estado = "Pendiente";
	pendiente pe;
	getDataTableDataPendientes_estado(estado,pe,lista_pendientes);
}

//Muestra los pendientes realizandose
void listar_realizandose()
{
	list<pendiente> lista_pendientes;
	string estado = "Realizandose";
	pendiente pe;
	getDataTableDataPendientes_estado(estado,pe,lista_pendientes);
}

//Muestra los pendientes listos
void listar_listos()
{
	list<pendiente> lista_pendientes;
	string estado = "Listo";
	pendiente pe;
	getDataTableDataPendientes_estado(estado,pe,lista_pendientes);
}

//cambia el estado de un pendiente a realizandose (por consola)
void cambiar_estado_pendiente()
{
	pendiente pe;
	cout << "ID: "; cin >> pe.id;
	updateDataTableDataPendientes_realizandose(pe.id, pe);
}

//cambia el estado de un pendiente a listo (por consola)
void cambiar_estado_realizandose()
{
	pendiente pe;
	cout << "ID: "; cin >> pe.id;
	updateDataTableDataPendientes_listo(pe.id, pe);
}

//Cambia estado de un pendiente a pendiente (por consola)
void cambiar_estado_inicial()
{
	pendiente pe;
	cout << "ID: "; cin >> pe.id;
	updateDataTableDataPendientes_pendiente(pe.id, pe);
}

//Cambiar toda la lista de realizandose a pendientes
void all_to_inicial()
{
	list<pendiente> lista_pendientes;
	string estado = "Realizandose";
	pendiente pe;
	getDataTableDataPendientes_estado_only(estado,pe,lista_pendientes);
	for (std::list<pendiente>::iterator it=lista_pendientes.begin(); it != lista_pendientes.end(); ++it)
	{
		pendiente pe;
		pe = *it;
		updateDataTableDataPendientes_pendiente(pe.id, pe);
	}
}

//Llenar BD de vallas con txt
void upload_txt_vallas()
{
	ifstream arch;
	arch.open("vallas.txt");
	if(!arch)
	{
		cout << "Error" << endl;
	}
	else
	{
		//Numero&Codigo&Origen&Estado&Parroquia&Municipio&Direccion&Condicion&Visual&Tipo&Alto&Ancho&Longitud&Latitud&Inicio&Fin
		valla va;
		string inicio, fin,numero;
		while(getline(arch,numero,'&') and getline(arch,va.codigo,'&') and getline(arch,va.origen,'&') and getline(arch,va.estado,'&') and getline(arch,va.parroquia,'&') and getline(arch,va.municipio,'&') and getline(arch,va.direccion,'&') and getline(arch,va.condicion,'&') and getline(arch,va.visual,'&') and getline(arch,va.tipo,'&') and getline(arch,va.alto,'&') and getline(arch,va.ancho,'&') and getline(arch,va.longitud,'&') and getline(arch, va.latitud,'&') and getline(arch,inicio,'&') and getline(arch,fin))
		{
			va.inicio = 0;
			va.fin = 480;
			cout << "CODIGO: " << va.codigo << endl;
			cout << "ORIGEN: " << va.origen << endl;
			cout << "ESTADO: " << va.estado << endl;
			cout << "PARROQUIA: " << va.parroquia << endl;
			cout << "MUNICIPIO: " << va.municipio << endl;
			cout << "DIRECCION: " << va.direccion << endl;
			cout << "CONDICION: " << va.condicion << endl;
			cout << "VISUAL: " << va.visual << endl;
			cout << "TIPO: " << va.tipo << endl;
			cout << "ALTO: " << va.alto << endl;
			cout << "ANCHO: " << va.ancho << endl;
			cout << "LONGITUD: " << va.longitud << endl;
			cout << "LATITUD: " << va.latitud << endl;
			cout << "INICIO (INT): " << va.inicio << endl;
			cout << "FIN: (INT): " << va.fin << endl <<endl;

			insert_value_valla(va);
		}
		arch.close();
	}

}

//Llenar BD de actividaves con txt
void upload_txt_actividades()
{
	ifstream arch;
	arch.open("actividades.txt");
	if(!arch)
	{
		cout << "Error" << endl;
	}
	else
	{
		//N° de Actividad&Código&Tipo&Tipo de Actividad&Tiempo (m)&Prioridad&Instalacion
		actividad ac;
		string tiempo, prioridad,instalacion, numero;
		while(getline(arch,numero,'&') and getline(arch,ac.codigo,'&') and getline(arch,ac.tipo,'&') and getline(arch,ac.descripcion,'&') and getline(arch,tiempo,'&') and getline(arch,prioridad,'&') and getline(arch,instalacion))
		{
			ac.tiempo = atoi(tiempo.c_str());
			ac.prioridad = atoi(prioridad.c_str());
			ac.instalacion = atoi(instalacion.c_str());
			cout << "CODIGO: " << ac.codigo << endl;
			cout << "TIPO: " << ac.tipo << endl;
			cout << "DESCRIPCION: " << ac.descripcion << endl;
			cout << "TIEMPO (INT): " << ac.tiempo << endl;
			cout << "PRIORIDAD (INT): " << ac.prioridad << endl;
			cout << "INSTALACION (INT): " << ac.instalacion << endl;

			insert_value_actividad(ac);
		}
		arch.close();
	}

}

/*
void listar_pendientes_test()
{
	list<pendiente> lista_pendientes;
	string estado = "Pendiente";
	pendiente pe;
	getDataTableDataPendientes_estado_only(estado,pe,lista_pendientes);
	for (std::list<pendiente>::iterator it=lista_pendientes.begin(); it != lista_pendientes.end(); ++it)
    		cout << ' ' << it->estado;
	cout << endl;
}*/

/*
void test_model()
{
  glp_prob *mip;
  glp_tran *tran;
  
  glp_iocp *parm = new glp_iocp;
  glp_init_iocp(parm);
  parm->gmi_cuts = GLP_ON;
  parm->clq_cuts = GLP_ON;
  parm->cov_cuts = GLP_ON;
  parm->mir_cuts = GLP_ON;
  parm->presolve = GLP_ON;
  parm->binarize = GLP_ON;
  int ret;
  mip = glp_create_prob();
  tran = glp_mpl_alloc_wksp();
  ret = glp_mpl_read_model(tran, "Modelo.mod", 1);
  if (ret != 0)
  { fprintf(stderr, "Error on translating model\n");
  }
  ret = glp_mpl_read_data(tran, "Modelo.dat");
  if (ret != 0)
  { fprintf(stderr, "Error on translating data\n");
  }
  ret = glp_mpl_generate(tran, NULL);
  if (ret != 0)
  { fprintf(stderr, "Error on generating model\n");
  }
  glp_mpl_build_prob(tran, mip);
  glp_intopt(mip, parm);

  //ret = glp_mpl_postsolve(tran, mip, GLP_MIP);
  //if (ret != 0)
  //fprintf(stderr, "Error on postsolving model\n");
  
  ret = glp_print_mip(mip, "resultado.txt");
  if (ret != 0)
  { fprintf(stderr, "Error on generating output\n");
  }
  
  glp_mpl_free_wksp(tran);
  glp_delete_prob(mip);
}*/

//
void create_data(int numV,int numVehi,int x1, int * mtto,list<valla> & listavalla,list<int> & listatiempo,list<int> & listavehiculos, int numMat, int ** mat)
{
	ofstream arch;
	arch.open("modelo.dat");
	if(!arch)
	{
		cout<< "Error" <<endl;
	}
	else
	{
		//print line data
		arch << "data;" << endl << endl;
		
		//print num vallas
		arch << "#Vallas" << endl;
		arch << "param n:="<<numV<<";" << endl << endl;
		
		//print num vehiculos
		arch << "#Vehiculos" << endl;
		arch << "param z:="<<numVehi<<";" << endl << endl;
		
		//print Minumos maximos por jornada laboral
		arch << "#Minumos maximos por jornada laboral del personal subcontratado" << endl;
		arch << "param Jornada := "<<480<<";" << endl << endl;
		
		//print #Vallas de mantenimiento sin instalacion
		arch << "#Vallas de mantenimiento sin instalacion" << endl;
		arch << "set Mtto := ";
		for(int i = 0; i < x1;i++)
		{
			arch<< mtto[i] << " ";
		}
		arch<<";" << endl << endl;
		
		//print Intervalos de las Ventanas de Tiempo: [e, l]
		arch << "#Intervalos de las Ventanas de Tiempo: [e, l]" << endl;
		arch << "param:"<<"     "<<"e"<<"     "<<"l:="<<endl;
		int w = 0;
		for (std::list<valla>::iterator it=listavalla.begin(); it != listavalla.end(); ++it)
		{
			arch << w << "     "<< it->inicio << "       " << it->fin << endl;
			w++;
		}
		arch <<";" <<endl<<endl;
		
		//print Tiempo de servicio ui
		arch << "#u : Tiempo de servicio" << endl;
		arch << "param:"<<"      "<<"u:="<<endl;
		w = 0;
		for (std::list<int>::iterator it=listatiempo.begin(); it != listatiempo.end(); ++it)
		{
			arch << w << "     "<< *it << endl;
			w++;
		}

		arch <<";" <<endl<<endl;
		
		//print #p que es un parametro que indica la prioridad de asignacion a los vehiculos
		arch << "#" << endl;
		arch << "param:"<<"      "<<"p:="<<endl;
		w = 1;
		for (std::list<int>::iterator it=listavehiculos.begin(); it != listavehiculos.end(); ++it)
		{
			arch << w << "     "<< *it << endl;
			w++;
		}
		arch <<";" <<endl<<endl;
		
		//print #M es una constante aleatoriamente grande
		arch << "#M es una constante aleatoriamente grande" << endl;
		arch << "param M:="<<500000<<";" << endl << endl;
		
		//print #Tiempo de viaje desde i hasta j
		arch << "#Tiempo de viaje desde i hasta j" << endl;
		arch << "param t: ";
		for(int i = 0; i < numMat; i++)
		{
			arch << i << " " ;
		}
		arch <<":="<<endl;
		for(int i = 0; i < numMat; i++)
		{
			arch << "         " << i << " ";
			for(int j = 0; j < numMat; j++)
			{
				arch << mat[i][j] << " ";
			}
			arch << endl;	
				
		}
		
		arch <<";" <<endl<<endl;
		
		arch << "end;";
		arch.close();
	}
}

//
void init_valla(list<valla> & listavalla)
{
	valla va;
	
	va.inicio = 0 ;
	va.fin  = 480;
	listavalla.push_back(va);
	listavalla.push_back(va);
	va.inicio = 0 ;
	va.fin  = 50;
	listavalla.push_back(va);
	va.inicio = 0 ;
	va.fin  = 480;
	listavalla.push_back(va);
	listavalla.push_back(va);
	listavalla.push_back(va);
	listavalla.push_back(va);
	va.inicio = 0 ;
	va.fin  = 50;
	listavalla.push_back(va);
	va.inicio = 0 ;
	va.fin  = 150;
	listavalla.push_back(va);
	va.inicio = 0 ;
	va.fin  = 480;
	listavalla.push_back(va);
	
}

//
void test_create_data_model()
{
	cout << "Create Data Model" <<endl;
	int numV=8;
	int numVehi = 3;
	int x1 = 2;
	int mtto[x1];mtto[0]=5;mtto[1]=1;
	list<valla> listavalla;
	init_valla(listavalla);
	list<int> listatiempo;
	listatiempo.push_back(15);listatiempo.push_back(50);
	listatiempo.push_back(80);listatiempo.push_back(70);
	listatiempo.push_back(60);listatiempo.push_back(100);
	listatiempo.push_back(30);listatiempo.push_back(160);
	listatiempo.push_back(60);listatiempo.push_back(15);
	list<int> listavehiculos;
	listavehiculos.push_back(1000);
	listavehiculos.push_back(0);
	listavehiculos.push_back(0);
	
	int numMat = 10;
	int **mat;
	mat = new int * [numMat];
	for(int i = 0; i <numMat; i++)
		mat[i] = new int[numMat];
	
	create_data(numV,numVehi,x1,mtto,listavalla,listatiempo,listavehiculos,numMat,mat);
}

//
void read_matrix_distance()
{
	ifstream arch;
	arch.open("matrixdistance_test.txt");
	if(!arch)
	{
		cout<< "Error" <<endl;
	}
	else
	{
		int num_vallas;
		arch >> num_vallas;
		cout << "Numero de vallas " << num_vallas << endl;
		
		string codes[num_vallas];
		
		for(int i = 0 ; i < num_vallas; i++)
		{
			arch >> codes[i];
			cout << codes[i] << endl;
		}
		
		int matriz[num_vallas][num_vallas];
		for(int i = 0 ; i < num_vallas; i++)
		{
			for(int j = 0 ; j < num_vallas; j++)
			{
				arch >> matriz[i][j];
				cout << matriz[i][j] << " " ;
			}
			cout << endl;
		}
		
		arch.close();
	}
	
}

int read_matrix_distance_getNUMVALLAS()
{
	int num_vallas = 0;
	ifstream arch;
	arch.open("matrixdistance_test.txt");
	if(!arch)
	{
		cout<< "Error" <<endl;
	}
	else
	{
		
		arch >> num_vallas;
		cout << "Numero de vallas " << num_vallas << endl;
		
		arch.close();
	}
	
	return num_vallas;
	
}

void read_matrix_distance_getLISTCODES(list<string> & codes)
{
	ifstream arch;
	arch.open("matrixdistance_test.txt");
	if(!arch)
	{
		cout<< "Error" <<endl;
	}
	else
	{
		int num_vallas;
		arch >> num_vallas;

		string code;
		
		for(int i = 0 ; i < num_vallas; i++)
		{
			arch >> code;
			codes.push_back(code);
		}
		
		arch.close();
	}
	
}


void read_matrix_distance_getALLVALUES(int & num_vallas,list<string> & codes,int ** & matriz)
{
	ifstream arch;
	arch.open("matrixdistance_test.txt");
	if(!arch)
	{
		cout<< "Error" <<endl;
	}
	else
	{
		arch >> num_vallas;
		string code;
		
		for(int i = 0 ; i < num_vallas; i++)
		{
			arch >> code;
			codes.push_back(code);
		}
		
		matriz = new int * [num_vallas];
		for(int i = 0; i <num_vallas; i++)
			matriz[i] = new int[num_vallas];
		
		for(int i = 0 ; i < num_vallas; i++)
		{
			for(int j = 0 ; j < num_vallas; j++)
			{
				arch >> matriz[i][j];
			}
		}
		arch.close();
	}
}

void insert_new_pendiente()
{

	pendiente pe;

	cout << "CODIGO_VALLA: " ; cin >> pe.codigo_valla ;
	cout << "CODIGO_ACTIVIDAD: " ; cin >>  pe.codigo_actividad ;
	cout << "FECHA (YYYY-MM-DD): " ; cin >>  pe.fecha ;
	pe.estado = "Pendiente" ;
	actividad ac;
	getDataTableDataActividades(pe.codigo_actividad, &ac);
	pe.prioridad = ac.prioridad;
	pe.tiempo = ac.tiempo;
	insert_value_pendiente(pe);
	cout << "ID: " << pe.id << endl;
	cout << "CODIGO_VALLA: " << pe.codigo_valla << endl;
	cout << "CODIGO_ACTIVIDAD: " << pe.codigo_actividad << endl;
	cout << "PRIORIDAD (INT): " << pe.prioridad << endl;
	cout << "TIEMPO: (INT): " << pe.tiempo << endl;
	cout << "FECHA: " << pe.fecha << endl;
	cout << "ESTADO: " << pe.estado << endl;
	
	//verificar si la valla ya esta en el sistema para agregarla
	list<string>  codes;
	int num_vallas;
	bool esta = false;
	int ** matriz;
	read_matrix_distance_getALLVALUES(num_vallas,codes,matriz);
	for (std::list<string>::iterator it=codes.begin(); it != codes.end(); ++it)
	{
		if(*it == pe.codigo_valla)
		{
			esta = true;
		}
	}
	//ampliamos la matriz de distancias
	if(!esta)
	{
		valla va;
		va.codigo = pe.codigo_valla;
		writeNewValla(va);
		Py_SetProgramName("menuManager");
		Py_Initialize();
		PyRun_SimpleString("execfile(\"test.py\")");
		Py_Finalize();
	}
}

void listar_pendientes_nuevo()
{
	list<pendiente> lista_pendientes;
	string estado = "Pendiente";
	pendiente pe;
	getDataTableDataPendientes_estado_only(estado,pe,lista_pendientes);
	lista_pendientes.sort(myfunction);
	for (std::list<pendiente>::iterator it=lista_pendientes.begin(); it != lista_pendientes.end(); ++it)
	{
		pendiente pe;
		pe = *it;
		cout << "ID: " << pe.id << " ";
		cout << "CODIGO_VALLA: " << pe.codigo_valla << " ";
		cout << "CODIGO_ACTIVIDAD: " << pe.codigo_actividad << " ";
		cout << "PRIORIDAD: " << pe.prioridad << " ";
		cout << "TIEMPO: " << pe.tiempo << " ";
		cout << "FECHA: " << pe.fecha << " ";
		cout << "ESTADO: " << pe.estado << endl << endl;
		
	}
}

void fill_lista_pendientes(list<pendiente> & lista_pendientes)
{
	string estado = "Pendiente";
	pendiente pe;
	getDataTableDataPendientes_estado_only(estado,pe,lista_pendientes);
	lista_pendientes.sort(myfunction);
}

void fill_lista_pendientes_instalation(list<pendiente> & lista_pendientes)
{
	string estado = "Pendiente";
	pendiente pe;
	getDataTableDataPendientes_estado_only(estado,pe,lista_pendientes);
	
	list<pendiente> lista_instalation;
	
	for (std::list<pendiente>::iterator it=lista_pendientes.begin(); it != lista_pendientes.end(); ++it)
	{
		pe = *it;
		actividad ac;
		getDataTableDataActividades(pe.codigo_actividad, &ac);
		if (ac.instalacion == 1)
		{
			lista_instalation.push_back(pe);
		}
	}
	lista_pendientes=lista_instalation;
	lista_pendientes.sort(myfunction);
}

void get_only_instalation_pendientes_list(list<valla> & lista_vallas, list<int> & lista_tiempo)
{
	list<pendiente> lista_pendientes;
	string estado = "Pendiente";
	pendiente pe;
	getDataTableDataPendientes_estado_only(estado,pe,lista_pendientes);
	lista_pendientes.sort(myfunction);
	
	cout << "ESTOY EN LA FUNCION" << endl;
	
	for (std::list<pendiente>::iterator it=lista_pendientes.begin(); it != lista_pendientes.end(); ++it)
	{
		pendiente pe;
		pe = *it;
		valla va;
		actividad ac;
		int tiempo = pe.tiempo;
			
		getDataTableDataActividades(pe.codigo_actividad, &ac);
		getDataTableDataVallas(pe.codigo_valla, &va);
		
		bool insertar = true;
		std::list<int>::iterator it3=lista_tiempo.begin();
		for (std::list<valla>::iterator it2=lista_vallas.begin(); it2 != lista_vallas.end(); ++it2)
		{
			if(it2->codigo == va.codigo)
			{
				insertar = false;
			} 
			
			if(ac.instalacion == 0)
			{
				insertar = false;
			}
			
			
				
		}
		
		time_t now = time(0);
		tm tm_struct = *localtime(&now);
		double seconds;
		double valor = 432000;

		strptime(pe.fecha.c_str(), "%Y-%m-%d", &tm_struct);
		seconds = difftime(now,mktime(&tm_struct));
		
		if(ac.instalacion == 1 and seconds < valor)
		{
			cout << "AQUI BANDERA 3" << endl;
			insertar = false;
		}
		
		if(insertar)
		{
			cout << "ESTOY INSERTANDO: " << va.codigo << endl;
			lista_tiempo.push_back(tiempo);
			lista_vallas.push_back(va);
		}
	}	
}

void get_only_instalation_pendientes_list_general(list<valla> & lista_vallas, list<int> & lista_tiempo,list<pendiente> & lista_pendientes)
{
	
	/*string estado = "Pendiente";
	pendiente pe;
	getDataTableDataPendientes_estado_only(estado,pe,lista_pendientes);
	lista_pendientes.sort(myfunction);*/
	for (std::list<pendiente>::iterator it=lista_pendientes.begin(); it != lista_pendientes.end(); ++it)
	{
		pendiente pe;
		pe = *it;
		valla va;
		actividad ac;
		int tiempo = pe.tiempo;
			
		getDataTableDataActividades(pe.codigo_actividad, &ac);
		getDataTableDataVallas(pe.codigo_valla, &va);
		
		bool insertar = true;
		std::list<int>::iterator it3=lista_tiempo.begin();
		for (std::list<valla>::iterator it2=lista_vallas.begin(); it2 != lista_vallas.end(); ++it2)
		{
			if(it2->codigo == va.codigo)
			{
				insertar = false;
				*it3 += ac.tiempo;
			}
			
			++it3;
		}
		if(insertar)
		{
			lista_tiempo.push_back(tiempo);
			lista_vallas.push_back(va);
		}
	}
}

//obtener lista de vallas a usar Modelo 1
void obtener_lista_vallas_a_usar(list<valla> & lista_vallas, list<int> & lista_tiempo)
{
	get_only_instalation_pendientes_list(lista_vallas, lista_tiempo);
	//get deposito
	valla va;
	va.codigo = "Deposito";
	getDataTableDataVallas(va.codigo, &va);
	lista_vallas.push_back(va);
	lista_vallas.push_front(va);
	
	lista_tiempo.push_back(15);
	lista_tiempo.push_front(15);
}

//obtener lista de vallas a usar Modelo General
void obtener_lista_vallas_a_usar_modeloGeneral(list<valla> & lista_vallas, list<int> & lista_tiempo,list<pendiente> & lista_pendientes)
{
	get_only_instalation_pendientes_list_general(lista_vallas, lista_tiempo, lista_pendientes);
	//get deposito
	valla va;
	va.codigo = "Deposito";
	getDataTableDataVallas(va.codigo, &va);
	lista_vallas.push_back(va);
	lista_vallas.push_front(va);
	
	lista_tiempo.push_back(15);
	lista_tiempo.push_front(15);
}

void matriz_de_distancia_vallas(list<valla> lista_vallas, int ** & newmatriz)
{
	list<string>  codes;
	int num_vallas;
	int ** matriz;
	
	read_matrix_distance_getALLVALUES(num_vallas,codes,matriz);
	
	newmatriz = new int * [lista_vallas.size()];
	for(int i = 0; i < lista_vallas.size(); i++)
		newmatriz[i] = new int[lista_vallas.size()];

	cout << "NUMERO DE VALLAS: " << lista_vallas.size() << endl;

	int i=0,j=0,y=0,z=0;
	
	i=0;
	for (std::list<valla>::iterator it=lista_vallas.begin(); it != lista_vallas.end(); ++it)
	{
		j=0;
		for (std::list<valla>::iterator it2=lista_vallas.begin(); it2 != lista_vallas.end(); ++it2)
		{
			y=0;
			for (std::list<string>::iterator it3=codes.begin(); it3 != codes.end(); ++it3)
			{
				z=0;
				for (std::list<string>::iterator it4=codes.begin(); it4 != codes.end(); ++it4)
				{
					if((it->codigo == *it3) and (it2->codigo == *it4))
					{
						
						newmatriz[i][j] = matriz[y][z]; 
					}
					z++;
				}
				y++;
			}
			j++;
		}
		i++;
	}

    /*for(i = 0 ; i < num_vallas; i++)
		{
			for(j = 0 ; j < num_vallas; j++)
			{
				cout << matriz[i][j] << " - ";
			}
			cout << endl;
		}*/
	for(i = 0 ; i < lista_vallas.size(); i++)
		{
			for(j = 0 ; j < lista_vallas.size(); j++)
			{
				cout << newmatriz[i][j] << " - ";
			}
			cout << endl;
		}

}

//probar obtener matriz de distancia
void probar_obtener_matriz_de_distancia()
{
	list<valla> lista_vallas;
	list<int> lista_tiempo;
	
	
	obtener_lista_vallas_a_usar(lista_vallas, lista_tiempo);
	int ** newmatriz;
	
		
	matriz_de_distancia_vallas(lista_vallas, newmatriz);
	for(int i = 0 ; i < lista_vallas.size(); i++)
	{
		for(int j = 0 ; j < lista_vallas.size(); j++)
		{
			cout << newmatriz[i][j] << " ";
		}
		cout << endl;
	}
}


void create_data_modelo1(int numV,int numVehi,list<valla> & listavalla,list<int> & listatiempo, int numMat, int ** mat)
{
	ofstream arch;
	arch.open("Modelo1.dat");
	if(!arch)
	{
		cout<< "Error" <<endl;
	}
	else
	{
		//print line data
		arch << "data;" << endl << endl;
		//print num vallas
		arch << "#Vallas" << endl;
		arch << "param n:="<<numV<<";" << endl << endl;
		//print num vehiculos
		arch << "#Vehiculos" << endl;
		arch << "param z:="<<numVehi<<";" << endl << endl;
		//print Minumos maximos por jornada laboral
		arch << "#Minumos maximos por jornada laboral del personal subcontratado" << endl;
		arch << "param Jornada := "<<480<<";" << endl << endl;
				
		//print Intervalos de las Ventanas de Tiempo: [e, l]
		arch << "#Intervalos de las Ventanas de Tiempo: [e, l]" << endl;
		arch << "param:"<<"     "<<"e"<<"     "<<"l:="<<endl;
		int w = 0;
		for (std::list<valla>::iterator it=listavalla.begin(); it != listavalla.end(); ++it)
		{
			arch << w << "     "<< it->inicio << "       " << it->fin << endl;
			w++;
		}
		arch <<";" <<endl<<endl;
		
		//print Tiempo de servicio ui
		arch << "#u : Tiempo de servicio" << endl;
		arch << "param:"<<"      "<<"u:="<<endl;
		w = 0;
		for (std::list<int>::iterator it=listatiempo.begin(); it != listatiempo.end(); ++it)
		{
			arch << w << "     "<< *it << endl;
			w++;
		}

		arch <<";" <<endl<<endl;
		
		
		//print #M es una constante aleatoriamente grande
		arch << "#M es una constante aleatoriamente grande" << endl;
		arch << "param M:="<<500000<<";" << endl << endl;
		
		//print #Tiempo de viaje desde i hasta j
		arch << "#Tiempo de viaje desde i hasta j" << endl;
		arch << "param t:   ";
		for(int i = 0; i < numMat; i++)
		{
			arch << i << " " ;
		}
		arch <<":="<<endl;
		for(int i = 0; i < numMat; i++)
		{
			arch << "         " << i << " ";
			for(int j = 0; j < numMat; j++)
			{
				arch << mat[i][j] << " ";
			}
			arch << endl;	
				
		}
		
		arch <<";" <<endl<<endl;
		
		arch << "end;";
		arch.close();
	}
}


int test_model1()
{
  glp_prob *mip;
  glp_tran *tran;
  
  glp_iocp *parm = new glp_iocp;
  glp_init_iocp(parm);
  parm->gmi_cuts = GLP_ON;
  parm->clq_cuts = GLP_ON;
  parm->cov_cuts = GLP_ON;
  parm->mir_cuts = GLP_ON;
  parm->presolve = GLP_ON;
  parm->binarize = GLP_ON;
  int ret;
  int sol = -1;
  mip = glp_create_prob();
  tran = glp_mpl_alloc_wksp();
  ret = glp_mpl_read_model(tran, "Modelo1.mod", 1);
  if (ret != 0)
  { fprintf(stderr, "Error on translating model\n");
  }
  ret = glp_mpl_read_data(tran, "Modelo1.dat");
  if (ret != 0)
  { fprintf(stderr, "Error on translating data\n");
  }
  ret = glp_mpl_generate(tran, NULL);
  if (ret != 0)
  { fprintf(stderr, "Error on generating model\n");
  }
  glp_mpl_build_prob(tran, mip);
  sol = glp_intopt(mip, parm);
  sol = glp_mip_status(mip);
  ret = glp_print_mip(mip, "resultado.txt");
  if (ret != 0)
  { fprintf(stderr, "Error on generating output\n");
  }
  
  glp_mpl_free_wksp(tran);
  glp_delete_prob(mip);
  
  return sol;
}


int test_model_general()
{
  glp_prob *mip;
  glp_tran *tran;
  
  glp_iocp *parm = new glp_iocp;
  glp_init_iocp(parm);
  parm->gmi_cuts = GLP_ON;
  parm->clq_cuts = GLP_ON;
  parm->cov_cuts = GLP_ON;
  parm->mir_cuts = GLP_ON;
  parm->presolve = GLP_ON;
  parm->binarize = GLP_ON;
  int ret;
  int sol = -1;
  mip = glp_create_prob();
  tran = glp_mpl_alloc_wksp();
  ret = glp_mpl_read_model(tran, "Modelo.mod", 1);
  if (ret != 0)
  { fprintf(stderr, "Error on translating model\n");
  }
  ret = glp_mpl_read_data(tran, "modelo.dat");
  if (ret != 0)
  { fprintf(stderr, "Error on translating data\n");
  }
  ret = glp_mpl_generate(tran, NULL);
  if (ret != 0)
  { fprintf(stderr, "Error on generating model\n");
  }
  glp_mpl_build_prob(tran, mip);
  sol = glp_intopt(mip, parm);
  sol = glp_mip_status(mip);
  
  cout << "NUMERO DE COLUMNAS " << glp_get_num_cols(mip) << endl;
  for (int i = 0; i < glp_get_num_cols(mip); ++i)
  {
  	if (glp_mip_col_val(mip,i+1) == 1)
  	{
  		cout << "NAME: " << glp_get_col_name(mip,i+1) << " VALUE: " << glp_mip_col_val(mip,i+1) <<endl;
  	}
  }

	ofstream arch;
	arch.open("valores.txt");
	if(!arch)
	{
		cout<< "Error" <<endl;
	}
	else
	{
		for (int i = 0; i < glp_get_num_cols(mip); ++i)
		{
			if (glp_mip_col_val(mip,i+1) == 1)
		  	{
		  		arch << glp_get_col_name(mip,i+1) << endl;
		  	}
		}
		arch.close();
	}

  //ret = glp_mpl_postsolve(tran, mip, GLP_MIP);
  //if (ret != 0)
  //fprintf(stderr, "Error on postsolving model\n");
  
  ret = glp_print_mip(mip, "resultado.txt");
  
  if (ret != 0)
  { fprintf(stderr, "Error on generating output\n");
  }
  
  glp_mpl_free_wksp(tran);
  glp_delete_prob(mip);
  
  return sol;
}

int test_create_data_model1(bool propio)
{
	list<valla> lista_vallas;
	list<int> lista_tiempo;
	obtener_lista_vallas_a_usar(lista_vallas, lista_tiempo);
	int ** newmatriz;
	matriz_de_distancia_vallas(lista_vallas, newmatriz);
	
	
	int numV=lista_vallas.size()-2;
	int numVehi = 0;
	int numero = 0;

	int ret = 0;
	
	do{
		numVehi = numVehi+1;
		create_data_modelo1(numV,numVehi,lista_vallas,lista_tiempo,lista_vallas.size(),newmatriz);
		ret  = test_model1();
	}while(ret != 5);
	
	system("clear");
	cout << "Se sugiere subcontratar --> " << numVehi  << " <-- vehiculos" << endl<<endl;
	
	cout << "Cuantos vehiculos se van a subcontratar?: ";
	cin >> numero;
	cout << endl;
	
	if(propio)
	{
		numVehi = numero +1;
	}
	else
	{
		numVehi = numero;
	}
	return numVehi;
}

int test_modelo_original(bool propio,list<pendiente> & lista_pendientes)
{
	
	//obtengo los pendientes
	if(propio)
	{
		fill_lista_pendientes(lista_pendientes);
	}
	else
	{
		fill_lista_pendientes_instalation(lista_pendientes);
	}	

	int ret = 0;
	
	int numVehi = test_create_data_model1(propio);

	if (lista_pendientes.size() != 0)
	{
		
		do
		{
			list<valla>  lista_vallas;
			list<int>  lista_tiempo;
			obtener_lista_vallas_a_usar_modeloGeneral(lista_vallas, lista_tiempo, lista_pendientes);
			int numV=lista_vallas.size()-2;

			if (propio)
			{
				if (numVehi == 0)
				{
					numVehi = 1;
				}
			}
			else
			{
				if (numVehi == 0 )
				{
					cout << "ERROR: No hay vehiculos disponibles para la planificacion" << endl;
					return -1;
				}
			}
			
			//Construccion de p
			list<int> listavehiculos;
			if (propio)
			{
				listavehiculos.push_back(1);
				for (int i = 0; i < numVehi-1; ++i)
				{
					listavehiculos.push_back(0);
				}
			}
			else
			{
				for (int i = 0; i < numVehi; ++i)
				{
					listavehiculos.push_back(0);
				}
			}

			//Construccion de numMat
			int numMat = lista_vallas.size();
			
			//Construccion de matriz de distancias (mat)
			int ** mat;
			matriz_de_distancia_vallas(lista_vallas, mat);
			
			//Construccion de NC
			int * NC;
			int bandera = 0;
			
			list<valla> lista_auxiliar;		
			
			for (std::list<valla>::iterator it=lista_vallas.begin(); it != lista_vallas.end(); ++it)
			{	
				valla va;
				va = *it;
						
				for (std::list<pendiente>::iterator it2=lista_pendientes.begin(); it2 != lista_pendientes.end(); ++it2)
				{
					pendiente pe;
					pe = *it2;
					actividad ac;
					if(va.codigo == pe.codigo_valla){
						getDataTableDataActividades(pe.codigo_actividad, &ac);
						
						time_t now = time(0);
						tm tm_struct = *localtime(&now);
						double seconds;
						double valor = 432000;

						strptime(pe.fecha.c_str(), "%Y-%m-%d", &tm_struct);
						seconds = difftime(now,mktime(&tm_struct));

						if (ac.instalacion == 1 and seconds < valor)
						{
							lista_auxiliar.push_back(va);
						}
						
						if (ac.instalacion == 0)
						{
							lista_auxiliar.push_back(va);
						}
					}
				}
			}
			
			lista_auxiliar.unique();
			
			int x1=0;
			
			for (std::list<valla>::iterator it=lista_auxiliar.begin(); it != lista_auxiliar.end(); ++it)
			{
				valla va;
				va = *it;
				x1++;
			}
			
			if (x1>0)
			{
				NC = new int [x1];
				int x3 = 0;
				int x2 = 0;
				
				for (std::list<valla>::iterator it=lista_auxiliar.begin(); it != lista_auxiliar.end(); ++it)
				{	
					valla va;
					va = *it;
					x3 = 0;
					for (std::list<valla>::iterator it2=lista_vallas.begin(); it2 != lista_vallas.end(); ++it2)
					{
						valla va1;
						va1 = *it2;
						
						if(va.codigo == va1.codigo)
						{
							NC[x2] = x3;
							x2++;
						}
					x3++;
					}
				}
			}	
			
			//Creacion del archivo de DATA y corrida del modelo
			create_data(numV,numVehi,x1,NC,lista_vallas,lista_tiempo,listavehiculos, numMat, mat);
			ret = test_model_general();

			if (ret != 5)
			{
				lista_pendientes.pop_back();
			}
			else
			{
				//cout << "SOLUCION Encontrada" << endl;
				return 0;
			}

		}while((lista_pendientes.size() != 0));
	}
	else
	{
		cout << "ERROR: No hay pendientes por planificar" << endl;
		return -1;
	}

	return 1;

	
	
}

void modelo_general_correrlo()
{		
	list<pendiente> lista_pendientes;
	bool propio = true;
	string ca;
	
	do
	{
		cout << "El vehiculo propio esta disponible (SI=S,NO=N): "; cin >> ca;
	}while(ca != "S" and ca != "s" and ca != "N" and ca != "n");
	
	if (ca == "N" or ca == "n")
	{
		propio = false;
	}
	
	int value = test_modelo_original(propio,lista_pendientes);
	
	if (value == -1)
	{
		cout << "ERROR EN LA CONSTRUCCION DE LA DATA" << endl;
	}
	else
	{
		if (value == 1)
		{
			cout << "ERROR EN EL MODELO: no se encuentra solucion factible" << endl;
		}
		else
		{
			cout << "VALUE " << value << endl;
			cout << "SOLUCION Encontrada" << endl;
			
			//Cambio en el estado de las actividades ruteadas a realizandose
			for (std::list<pendiente>::iterator it2=lista_pendientes.begin(); it2 != lista_pendientes.end(); ++it2)
			{
				cout << it2->codigo_actividad << endl;
				pendiente pe = *it2;
				updateDataTableDataPendientes_realizandose(pe.id, pe);
			}
			
			//Construccion de la Orden de Carretera
					
			ifstream arch;
			arch.open("valores.txt");
			if (!arch)
			{
				cout << "Error al leer el modelo" << endl;
			}
			else
			{
				list<string> valores;
				string data;
				while(getline(arch,data))
				{
					valores.push_back(data);
				}
				arch.close();
				
				int Matriz[valores.size()][3];
				int xcont = 1;
				int f=0;
					
				for (std::list<string>::iterator it2=valores.begin(); it2 != valores.end(); ++it2)
				{
					int first,second,third;
					string value;
					string primero,segundo,tercero;
						
					value = *it2;
	
					std::size_t foundpa = value.find("[");
					std::size_t foundcoma = value.find(",");
					std::size_t found2coma = value.find(",",foundcoma+1);
					std::size_t found2pa = value.find("]",found2coma+1);
				
					primero = value.substr(foundpa+1,foundcoma-foundpa-1);
					segundo = value.substr(foundcoma+1,found2coma-foundcoma-1);
					tercero = value.substr(found2coma+1,found2pa-found2coma-1);
						
					first = atoi(primero.c_str());
					second = atoi(segundo.c_str());
					third = atoi(tercero.c_str());		
							
					Matriz[f][0]=first;
					Matriz[f][1]=second;
					Matriz[f][2]=third;
					f++;
						
					xcont++;
				}
				
				
				int mayor=0;
									
				for(int i=0; i<valores.size(); i++)
				{
					for(int j=0; j<valores.size(); j++)
					{
						if(Matriz[i][2]<Matriz[j][2])
						{
							mayor=Matriz[i][2];
							Matriz[i][2]=Matriz[j][2];
							Matriz[j][2]=mayor;
							
							mayor=Matriz[i][1];
							Matriz[i][1]=Matriz[j][1];
							Matriz[j][1]=mayor;
								
							mayor=Matriz[i][0];
							Matriz[i][0]=Matriz[j][0];
							Matriz[j][0]=mayor;
						}
					}
				}
					
				
				std::list<int> listaux;
				for(int i=0; i<valores.size(); i++)
				{
					listaux.push_back(Matriz[i][2]);
				}
				
				listaux.unique();
				int numVehi = listaux.size();
				//cout << "NUMERO DE VEHICULOS: " << numVehi << endl;
				
				std::list<valla>  lista_vallas;
				std::list<int>  lista_tiempo;
				
				obtener_lista_vallas_a_usar_modeloGeneral(lista_vallas, lista_tiempo, lista_pendientes);
					
				ofstream reporte;
				reporte.open("OC.txt");
				if (!reporte)
				{
					cout <<"ERROR: no se ha creado el archivo de la Orden de Carretera" << endl;
				}
				else
				{
				
				time_t now = time(0);
				tm * timeinfo = localtime(&now);
				
				list<string> wday_name;
				wday_name.push_back("Domingo");
				wday_name.push_back("Lunes");
				wday_name.push_back("Martes");
				wday_name.push_back("Miercoles");
				wday_name.push_back("Jueves");
				wday_name.push_back("Viernes");
				wday_name.push_back("Sabado");
  
				list<string> mon_name;
				mon_name.push_back("Enero");
				mon_name.push_back("Febrero");
				mon_name.push_back("Marzo");
				mon_name.push_back("Abril");
				mon_name.push_back("Mayo");
				mon_name.push_back("Junio");
				mon_name.push_back("Julio");
				mon_name.push_back("Agosto");
				mon_name.push_back("Semtiembre");
				mon_name.push_back("Octubre");
				mon_name.push_back("Noviembre");
				mon_name.push_back("Diciembre");
  
				string result;
				
				std::list<string>::iterator it = wday_name.begin();
				advance(it,timeinfo->tm_wday);
				result += *it;
				result += ", ";
				
				int day = timeinfo->tm_mday;
				stringstream dayc;
				dayc << day;
				result += dayc.str();
				result += " de ";
				
				std::list<string>::iterator it1 = mon_name.begin();
				advance(it1,timeinfo->tm_wday);
				result += *it1;
				result += " de ";
				
				int year = 1900 + timeinfo->tm_year;
				stringstream yearc;
				yearc << year;
				result += yearc.str();
				result += "   ";
				
				reporte<<"Fecha de planificacion: "<< result <<endl;
				
				reporte << "Hora: "<< timeinfo->tm_hour << ":" << timeinfo->tm_min << endl << endl;
				
				
				int car = 1;
				
				while (car <= numVehi){
				
				string ruta = "https://www.google.co.ve/maps/dir/";
				
				std::list<int> lista;
				
				for(int i=0; i<valores.size(); i++)
				{				
					if(Matriz[i][2]==car)
					{
					lista.push_back(Matriz[i][0]);
					}
				}
				
				lista.sort();
				
				int cont = 1;
				
				
				for(std::list<int>::iterator it=lista.begin(); it != lista.end(); ++it)
				{
					int numero = *it;
					
					if(numero == 0){
						reporte <<"**             Vehiculo "<< car <<"            **"<<endl;
						//reporte <<"** Salida del Deposito **"<<endl;
						valla v1;
						v1.codigo = "Deposito";
						getDataTableDataVallas(v1.codigo, &v1);
						ruta = ruta + v1.latitud + ","  + v1.longitud + "/";
					}
					else
					{
										
					
					actividad ac1;
					
					std::list<valla>::iterator it2=lista_vallas.begin();
					std::advance(it2, numero);
					//cout << "Codigo de Valla: " << it2->codigo << endl;
									
					string actividades;
					for (std::list<pendiente>::iterator it=lista_pendientes.begin(); it != lista_pendientes.end(); ++it)
					{
					pendiente pe = *it;
					
					
					if (pe.codigo_valla == it2->codigo)
					{
						getDataTableDataActividades(pe.codigo_actividad, &ac1);
						actividades += ac1.descripcion +",";
					}
					}
					reporte << endl << "--> Orden de Visita: " << cont - 1 << endl
					<< "Codigo de Valla: " << it2->codigo << endl
					<< "Direccion: " << it2->direccion << endl
					<< "Visual: " << it2->visual << endl
					<<"Tipo: " << it2->tipo << endl
					<<"Actividades a Realizar: " << actividades << endl;		
					
					ruta = ruta + it2->latitud + ","  + it2->longitud + "/";
					
					}
					
					
					
					cont++;
					
				}	
						
						valla v1;
						v1.codigo = "Deposito";
						getDataTableDataVallas(v1.codigo, &v1);
						ruta = ruta + v1.latitud + ","  + v1.longitud;

					reporte << endl << "Ruta: "<< ruta << endl << endl;
				car++;
				}			
					
					reporte.close();		

				//Uso para pruebas
				for (std::list<pendiente>::iterator it2=lista_pendientes.begin(); it2 != lista_pendientes.end(); ++it2)
				{
				pendiente pe = *it2;
				updateDataTableDataPendientes_pendiente(pe.id, pe);
				}

			}
		}
	}
}

}


#endif
