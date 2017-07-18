from datetime import datetime
import time

import googlemaps
import responses
import sqlite3

def testGoogle():
	key = "AIzaSyD15v_vQF-9bRWppqpMPcDKlXHhsqEifLw"
	client = googlemaps.Client(key)

	responses.add(responses.GET, 'https://maps.googleapis.com/maps/api/distancematrix/json', body='{"status":"OK","rows":[]}', status=200, content_type='application/json')

	origins = [[10.49206, -66.78868]]
	destinations = [(10.49573, -66.77852), (10.49586, -66.77996)]

	matrix = client.distance_matrix(origins, destinations)

	print matrix

	status = matrix['status']

	#print status


	rows = matrix['rows']

	#print rows

	origin_addresses = matrix['origin_addresses']

	#print origin_addresses

	destination_addresses = matrix['destination_addresses']

	#print destination_addresses

	for x in rows:
		#print x
		elements = x['elements']
		for z in elements:
			status = z['status']
			duration = z['duration']
			distance = z['distance']
			print "status = ",status
			print "duration = ",duration['value']/60
			print "distance = ",distance['value']/1000
			print z


def getNewValla():
	data = ""
	with open('newvalla.txt', 'r') as f:
		data = f.readline().rstrip('\n')
	f.close()
	return data

def writeNewMatrixDistance(num , codes, distance):
	f = open('matrixdistance_test.txt','w')
	f.write(str(num) + "\n" )
	for x in codes:
		f.write( x + " "  )
	f.write("\n")
	for x in distance:
		for y in x:
			f.write( str(y) + " " )
		f.write("\n")
	f.close()

def readMatrixDistanceNUM():
	f = open('matrixdistance_test.txt', 'r')
	num = int(f.readline())
	codes = f.readline().split(' ')
	f.close()
	return num

def readMatrixDistanceCODES():
	f = open('matrixdistance_test.txt', 'r')
	num = int(f.readline())
	codes = f.readline().split(' ')
	f.close()
	return codes

def getCodes(newcode):
	codes = []
	codes = readMatrixDistanceCODES()
	num = readMatrixDistanceNUM()
	codes[num] = newcode
	return codes
	
def getLongitudLatitud(codigo):
	latitud = ""
	longitud = ""
	conn = sqlite3.connect('tesisData.db')
	cursor = conn.execute('''SELECT codigo, longitud , latitud FROM VALLAS WHERE codigo = ?''',(codigo,))
	for row in cursor:
		longitud = row[1]
		latitud = row[2]
	conn.close()
	return (latitud,longitud)

def getLongitudLatitudLIST(codigo):
	latitud = ""
	longitud = ""
	conn = sqlite3.connect('tesisData.db')
	cursor = conn.execute('''SELECT codigo, longitud , latitud FROM VALLAS WHERE codigo = ?''',(codigo,))
	for row in cursor:
		longitud = row[1]
		latitud = row[2]
	conn.close()
	return [latitud,longitud]
	
def getDistances(num, codes, newcode):
	distance = []
	key = "AIzaSyD15v_vQF-9bRWppqpMPcDKlXHhsqEifLw"
	client = googlemaps.Client(key)
	responses.add(responses.GET, 'https://maps.googleapis.com/maps/api/distancematrix/json', body='{"status":"OK","rows":[]}', status=200, content_type='application/json')
	
	for y in range(num):
		origins = [["a","a"]]
		origins[0] = getLongitudLatitudLIST(codes[y])
		print origins
		destinations = []
		for x in range(num):
			destinations.append(getLongitudLatitud(codes[x]))
		print destinations
		
		matrix = client.distance_matrix(origins, destinations)
		rows = matrix['rows']
		subdistance = []
		for x in rows:
			elements = x['elements']
			for z in elements:
				duration = z['duration']
				subdistance.append(duration['value']/60)
				print "duration = ",duration['value']/60
		distance.append(subdistance)
	#distance = [[0,1,1],[1,0,1],[1,1,0]]
	return distance

def main():
	print "Hola"


if __name__ == "__main__":
	main()
	print getNewValla()
	num = 2
	codes = ['Deposito','6772P']
	distance = [[0,1,1],[1,0,1],[1,1,0]]
	#writeNewMatrixDistance(num, codes, distance)
	numero = readMatrixDistanceNUM()
	codigos = getCodes(getNewValla())
	distance = getDistances(numero+1,codigos, getNewValla())

	print numero
	print codigos
	for x in range(numero+1):
		print codigos[x]
	
	print distance
	
	writeNewMatrixDistance(numero+1, codigos, distance)


