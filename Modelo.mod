/*                           NODOS Y ARCOS                           */
param n, integer, >=1;              /*Cantidad de vallas*/


set I:={1..n};                      /*Conjunto de Vallas*/
set IT:={0} union I;                /*Conjunto de nodos directos*/
set IR:=I union {n+1};              /*Conjunto de nodos inversos*/
set IC:={0} union (I union {n+1});  /*Conjunto de todos los nodos*/
set VNC;                            /*Conjunto de vallas que no pueden ser tratadas por los vehiculos subcontratados*/

param t{i in IC,j in IC};           /*Tiempo de traslado entre i y j*/
param u{i in IC};                   /*Tiempo de servicio que requiere la valla i*/
param e{i in IC}, integer;          /*Inicio de la ventana de tiempo de servicio de la valla i*/
param l{i in IC}, integer <=480;    /*Fin de la ventana de tiempo de servicio de valla i*/
param Jornada, >0;                  /*Tiempo maximo de jornada laboral para el personal*/
param M;                            /*Constante arbitraria grande*/

/*                           VEHICULOS                           */

param z,integer, >=1;               /*Numero de vehiculos*/
set V:={1..z};              /*Conjunto de vehiculos disponibles para la planificacion*/
set Vsub:={2..z};           /*Conjunto de vehiculos subcontratados*/
param p{k in V};            /*Inverso de la prioridad de asignacion vehicular*/

/*                           VARIABLES                           */

/*X es una variable binaria que toma el valor de 1 si el vehiculo k viaja directamente del nodo i al nodo j y 0 de lo contrario*/
var X{i in IC,j in IC,k in V},binary;
var T{i in IC, k in V}, >=0;#tiempo de empezar a servir al cliente j

/*                           FUNCION OBJETIVO                           */

minimize Z: sum{i in IT,j in IR,k in V}((t[i,j]+u[j])*X[i,j,k])+sum{i in IT, j in IC,k in V}(p[k]*X[i,j,k]);

/*El modelo tiene como objetivo principal minimizar el costo total de viaje para la planificacion diaria de actividades operativas*/

/*                           RESTRICCIONES                           */
/*Todos los vehiculos deben salir del deposito*/
s.t.salida{k in V}:sum{j in IT}X[0,j,k]=1;

/*Todos los vehiculos regresan al deposito*/
s.t.llegada{k in V}:sum{i in IT}X[0,i,k]=sum{j in IT}X[j,n+1,k];

/*Los vehiculos subcontratados solo pueden atender las instalaciones vencidas*/
s.t.contratos1{i in IR, j in IR}: if ((i in VNC) or (j in VNC)) then sum{k in Vsub}X[i,j,k]=0;

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
param n:=5;

#Vehiculos
param z:=3;

#Minumos maximos por jornada laboral del personal subcontratado
param Jornada := 480;

#Vallas de mantenimiento sin instalacion
set Mtto := ;

#Intervalos de las Ventanas de Tiempo: [e, l]
param:     e     l:=
0     0       480
1     0       480
2     0       480
3     0       480
4     0       480
5     0       480
6     0       480
;

#u : Tiempo de servicio
param:      u:=
0     15
1     153
2     153
3     153
4     153
5     153
6     15
;

#
param:      p:=
1     0
2     0
3     0
;

#M es una constante aleatoriamente grande
param M:=500000;

#Tiempo de viaje desde i hasta j
param t: 0 1 2 3 4 5 6 :=
         0 0 13 13 32 20 22 0 
         1 15 0 3 26 14 16 15 
         2 15 0 0 26 14 16 15 
         3 27 21 21 0 15 11 27 
         4 23 18 18 17 0 1 23 
         5 27 21 21 21 9 0 27 
         6 0 13 13 32 20 22 0 
;

end;
