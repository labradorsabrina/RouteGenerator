/*                           NODOS Y ARCOS                           */
param n, integer, >=1;              /*Cantidad de vallas*/

set I:={1..n};                      /*Conjunto de Vallas*/
set IT:={0} union I;                /*Conjunto de nodos directos*/
set IR:=I union {n+1};              /*Conjunto de nodos inversos*/
set IC:={0} union (I union {n+1});  /*Conjunto de todos los nodos*/

param t{i in IC,j in IC};           /*Tiempo de traslado entre i y j*/
param u{i in IC};                   /*Tiempo de servicio que requiere la valla i*/
param e{i in IC}, integer;          /*Inicio de la ventana de tiempo de servicio de la valla i*/
param l{i in IC}, integer <=480;    /*Fin de la ventana de tiempo de servicio de valla i*/
param Jornada, >0;                  /*Tiempo maximo de jornada laboral para el personal*/
param M;                            /*Constante arbitraria grande*/


/*                           VEHICULOS                           */
param z,integer, >=1;               /*Numero de vehiculos*/
set V:={1..z};              /*Conjunto de vehiculos disponibles para la planificacion*/


/*                           VARIABLES                           */
/*X es una variable binaria que toma el valor de 1 si el vehiculo k viaja directamente del nodo i al nodo j y 0 de lo contrario*/
var X{i in IC,j in IC,k in V},binary;
var T{i in IC, k in V}, >=0;#tiempo de empezar a servir al cliente j


/*                           FUNCION OBJETIVO                           */
minimize Z: sum{i in IT,j in IR,k in V}((t[i,j]+u[j])*X[i,j,k]);
/*El modelo tiene como objetivo principal minimizar el costo total de viaje para la planificacion diaria de actividades operativas*/


/*                           RESTRICCIONES                           */
/*Todos los vehiculos deben salir del deposito*/
s.t.salida{k in V}:sum{j in IT}X[0,j,k]=1;

/*Todos los vehiculos regresan al deposito*/
s.t.llegada{k in V}:sum{i in IT}X[0,i,k]=sum{j in IT}X[j,n+1,k];

/*Cada valla debe visitarse solo una vez*/
s.t.nodos1{j in I}:sum{i in IT, k in V}(X[i,j,k])=1;

/*Visitar y dejar a un cliente con el mismo vehiculo*/
s.t.nodos2{j in IC, k in V: (j != 0 and j!=n+1)}:sum{i in IC: i!=j}(X[i,j,k])=sum{ii in IC: ii != j}(X[j,ii,k]);

/*Asegura que no se visiten arcos con tiempos iguales a 0*/
s.t.bucle{i in IT, j in IC}: if t[i,j]=0 then sum{k in V}X[i,j,k]=0;

/*Asegura que se cumpla la jornada laboral para personal subcontratados*/
s.t.jornada1{k in V}: sum{i in IC, j in IC}((u[i]+t[i,j])*X[i,j,k])<=Jornada;

/*Restricciones para asegurar las ventanas de tiempo*/
s.t.h1{i in IT,j in IT,k in V}:(T[i,k]+u[i]+t[i,j]-T[j,k])<=M*(1-X[i,j,k]);
s.t.h2{i in IC, k in V}:e[i]<=T[i,k];
s.t.h3{i in IC, k in V}:T[i,k]+u[i]<=l[i];


s.t.correccion{i in IR, k in V : (i!=0)}: X[i,0,k]=0;

solve;

for{k in V} {
	printf"\n";
	printf("      Ruta       Vehiculo \n");
	printf"\n";
		for{i in IT}{
			for{j in IR}{
				for {0..0: X[i,j,k]=1}  {
				printf"      %1s  %2s   %10s   %10% \n", i, j, k;
				printf"\n";
				}
			}
		}
		printf"\n";
}

for{k in V}{
printf"Tiempo de recorrido del Vehiculo %1s:",k;
printf"  %1s\n", sum{i in IC, j in IC}((u[i]+t[i,j])*X[i,j,k]);
				printf"\n";
}

data;

#Vallas
param n:=8;

#Vehiculos
param z:=2;

#Minumos maximos por jornada laboral del personal subcontratado
param Jornada := 480;

#Intervalos de las Ventanas de Tiempo: [e, l]
param:         e          l:=
0              0          480# Deposito  
1              0          480
2              0          450
3              0          480
4              0          480
5              0          480
6              0          480
7              0          450
8              0          150
9              0          480;# Deposito 

#u : Tiempo de servicio
param: u:= 
0      15
1      50
2      80
3      70
4      60
5      100
6      30
7      160
8      60
9      15;

#M es una constante aleatoriamente grande
param M:=500000;
 
#Tiempo de viaje desde i hasta j
param t:    0    1    2    3    4    5    6    7    8   9:=
		 0   0   13   14   16   14   16   15   15   15   0
         1  13    0   13   15   10   14   13   11   12  13
         2  18   14    0   14   10   14   13   11   12  18
         3  18   14   15    0   10   14   13   11   12  18
         4  18   14   15   14    0   13   13   11   11  18
         5  14   10   11   10   11    0   10   12   12  14
         6  15   11   12   11   12   11    0   13   13  15
         7  10   16   17   16   16   15   15    0   13  10
         8  22   18   19   18   19   18   17   17    0  22
		 9   0   13   14   16   14   16   15   15   15   0;


end;
