std::size_t timestamp_to_seconds(const char* timestamp)
{
    std::tm tm_struct;

    strptime(timestamp, "%F", &tm_struct);
    tm_struct.tm_isdst = 1;
    std::size_t t = std::mktime(&tm_struct);

    return t;
}


cout << "BANDERA DE TIEMPO: " << timestamp_to_seconds(pe.fecha.c_str()) << "    " << pe.fecha << endl;
						
						time_t now = time(0);
						tm tm_struct = *localtime(&now);
	
						double seconds;
						
	
						strptime(pe.fecha.c_str(), "%Y-%m-%d", &tm_struct);
						seconds = difftime(now,mktime(&tm_struct));
						
						cout << "BANDERA DE DIFERENCIA: " << seconds << endl;

						double valor = 432000;
						
						if(seconds > valor)
						{
							cout << "VENCIDA" << endl;
						}
		
		/*
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
		
		if(ac.instalacion == 0)
		{
				insertar = false;
		}
		
		if(insertar)
		{
			lista_tiempo.push_back(tiempo);
			lista_vallas.push_back(va);
		}
	
	}*/				
						
/*
void test_obtener_vallas_no_repetidas()
{
	list<valla> lista_vallas;
	list<int> lista_tiempo;
	
	get_only_instalation_pendientes_list(lista_vallas, lista_tiempo);
	
	for (std::list<valla>::iterator it2=lista_vallas.begin(); it2 != lista_vallas.end(); ++it2)
	{
		cout << it2->codigo << endl;
	}
}
*/
						
						/*
	string tiempoactual;
	
	int year = 1900+timeact->tm_year;
	int mont = timeact->tm_mon+1;
	int day = timeact->tm_mday;

	stringstream yearc; // stringstream used for the conversion
	yearc << year;//add the value of Number to the characters in the stream
	tiempoactual = yearc.str();//set Result to the content of the stream
	tiempoactual += "-";//set Result to the content of the stream
	
	stringstream montc; 
	montc << mont;//add the value of Number to the characters in the stream
	tiempoactual += montc.str();//set Result to the content of the stream
	tiempoactual += "-";//set Result to the content of the stream
	
	stringstream dayc;
	dayc << day;//add the value of Number to the characters in the stream
	tiempoactual += dayc.str();//set Result to the content of the stream
	
	cout << "BANDERA DE FECHA: " << tiempoactual <<endl;
	time_t now2 = time(0);
	tm * timepru = localtime(&now2);
	double seconds;
	
	timepru->tm_year = 2017 - 1900;
	timepru->tm_mon = 7 - 1;
	timepru->tm_mday = 1;
	
	seconds = difftime(now2,mktime(timepru));
	
	cout << "BANDERA DE DIFERENCIA: " << seconds <<endl;
	*/
	
	
					/*
					
					for(int i=0; i<valores.size(); i++)
					{
						int j=0;
						while(Matriz[j][2]==1){
								
							if(Matriz[i][0]=0)
							{
								v1.codigo = "Deposito";
								getDataTableDataVallas(v1.codigo, &v1);
							}
							
						}
					}
					
					/*ofstream reporte;
					reporte.open("OC.txt");
					if (!reporte)
					{
						cout <<"Error en la Orden de Carretera" << endl;
					}
					else
					{
				
				/*
				if (third == xcont)
							{
								valla v1,v2;
								actividad ac1,ac2;
								if (first == 0 or first == valores.size())
								{
									v1.codigo = "Deposito";
									getDataTableDataVallas(v1.codigo, &v1);
								}
								else
								{
									std::list<pendiente>::iterator it2=lista_pendientes.begin();
									std::advance(it2, first-1);
									v1.codigo = it2->codigo_valla;
									getDataTableDataVallas(v1.codigo, &v1);
									ac1.codigo = it2->codigo_actividad;
									getDataTableDataActividades(ac1.codigo, &ac1);
								}

								if (second == 0 or second == valores.size())
								{
									v2.codigo = "Deposito";
									getDataTableDataVallas(v2.codigo, &v2);
								}
								else
								{
									std::list<pendiente>::iterator it3=lista_pendientes.begin();
									std::advance(it3, second-1);
									v2.codigo = it3->codigo_valla;
									getDataTableDataVallas(v2.codigo, &v2);
									ac2.codigo = it3->codigo_actividad;
									getDataTableDataActividades(ac2.codigo, &ac2);
								}
								
								
								//cout << v1.codigo << "   " << v2.codigo << endl;
								string actividades;
								for (std::list<pendiente>::iterator it2=lista_pendientes.begin(); it2 != lista_pendientes.end(); ++it2)
								{
									pendiente pe = *it2;
									if (pe.codigo_valla == v1.codigo)
									{
										getDataTableDataActividades(pe.codigo_actividad, &ac1);
										actividades += ac1.descripcion +",";
									}
								}
								if  (v1.codigo != "Deposito")
								{
								reporte <<"Orden de Visita: "<< first << endl<< "Codigo de Valla: " << v1.codigo << endl<< "Direccion: " << v1.direccion << endl<< "Visual: " << v1.visual << endl<<"Tipo: " << v1.tipo << endl<<"Actividades a Realizar: " << actividades << endl;
								//reporte << second << " " << v2.codigo << " " << v2.direccion << " " << v2.visual << " " << v2.tipo << " " << ac2.descripcion << endl;
								//reporte << "--> Ubicacion: "<< "https://www.google.co.ve/maps/dir/"<< v1.latitud<<","<<v1.longitud<<"/"<< v2.latitud<<","<<v2.longitud << endl<<endl;
								}
								else
								{
								reporte <<"** Vehiculo "<< xcont <<"  **"<<endl;
								reporte <<"** Salida del Deposito **"<<endl;
								//reporte << second << " " << v2.codigo << " " << v2.direccion << " " << v2.visual << " " << v2.tipo << " " << ac2.descripcion << endl;
								//reporte << "--> Ubicacion: "<< "https://www.google.co.ve/maps/dir/"<< v1.latitud<<","<<v1.longitud<<"/"<< v2.latitud<<","<<v2.longitud << endl<<endl;
								}

								ruta = ruta + v1.latitud + ","  + v1.longitud + "/" + v2.latitud + "," + v2.longitud + "/";
							}
						
							
						//}

						//reporte << "--> Ruta: "<< ruta << endl << endl;
					
					reporte.close();*/
					
/*
void test_obtener_vallas_no_repetidas_para_usar()
{
	list<valla> lista_vallas;
	list<int> lista_tiempo;
	
	obtener_lista_vallas_a_usar(lista_vallas, lista_tiempo);
	
	for (std::list<valla>::iterator it2=lista_vallas.begin(); it2 != lista_vallas.end(); ++it2)
	{
		cout << it2->codigo << endl;
	}
	
	for (std::list<int>::iterator it2=lista_tiempo.begin(); it2 != lista_tiempo.end(); ++it2)
	{
		cout << *it2 << endl;
	}
}*/

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
