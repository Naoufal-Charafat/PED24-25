#Copyright® Joaquin 2015-2016  

TESTSPORO=11
TESTSVECTOR=9
TESTSTLISTA=15
nombreBase="tad"
extension=".cpp"
zero="0"

echo "Autocorrector Cuadernillo 1 PED"
echo "1. Test TPoro"
echo "2. Test TVectorPoro"
echo "3. Test TListaPoro"
echo "4. Todos"
echo 'Opcion: '
read Opcion
if ! test -d ./salidaObtenida/ ; then
	mkdir salidaObtenida
fi
if (( $Opcion == 1 || $Opcion == 4 )); then
	
	echo "//////////////////////////////////////////////////////////////////"
	echo "///////////////////////Pruebas TPoro//////////////////////////////"
	if test -d ./salidaObtenida/tporo ; then
		rm -R ./salidaObtenida/tporo
	fi
	mkdir salidaObtenida/tporo	
	cp src/tporo/*.cpp src/
	for (( i = 1; i <= $TESTSPORO; i++ )); do
		
		if (($i >= 10)); then
			nombre=$nombreBase$i$extension 
		else
			nombre=$nombreBase$zero$i$extension 
		fi
		echo $nombre
		mv src/$nombre src/tad.cpp
		make > basura.txt
		./tad > ./salidaObtenida/tporo/$i.txt
		diff -b ./salidaObtenida/tporo/$i.txt salidas/tporo/$nombre.sal
		mv src/tad.cpp src/$nombre
		rm ./tad
		rm ./basura.txt
		
	done
	rm src/*.cpp
fi
if (( $Opcion == 2 || $Opcion == 4 )); then

	echo "//////////////////////////////////////////////////////////////////"
	echo "//////////////////////Pruebas TVectorPoro/////////////////////////"
	if test -d ./salidaObtenida/tvectorporo ; then
		rm -R ./salidaObtenida/tvectorporo
	fi
	mkdir salidaObtenida/tvectorporo	
	cp src/tvectorporo/*.cpp src/
	for (( i = 1; i <= $TESTSVECTOR; i++ )); do
		
		if (($i >= 10)); then
			nombre=$nombreBase$i$extension 
		else
			nombre=$nombreBase$zero$i$extension 
		fi
		echo $nombre
		mv src/$nombre src/tad.cpp
		make > basura.txt
		./tad > ./salidaObtenida/tvectorporo/$i.txt
		diff -b ./salidaObtenida/tvectorporo/$i.txt salidas/tvectorporo/$nombre.sal
		mv src/tad.cpp src/$nombre
		rm ./tad
		rm ./basura.txt
		
	done
	rm src/*.cpp
fi
if (( $Opcion == 3 || $Opcion == 4 )); then
	echo "//////////////////////////////////////////////////////////////////"
	echo "///////////////////////Pruebas TListaPoro/////////////////////////"
	if test -d ./salidaObtenida/tlistaporo ; then
		rm -R ./salidaObtenida/tlistaporo
	fi
	mkdir salidaObtenida/tlistaporo
	cp src/tlistaporo/*.cpp src/
	for (( i = 1; i <= $TESTSTLISTA; i++ )); do
		
		if (($i >= 10)); then
			nombre=$nombreBase$i$extension 
		else
			nombre=$nombreBase$zero$i$extension 
		fi
		echo $nombre
		mv src/$nombre src/tad.cpp
		make > basura.txt
		./tad > ./salidaObtenida/tlistaporo/$i.txt
		diff -b ./salidaObtenida/tlistaporo/$i.txt salidas/tlistaporo/$nombre.sal
		mv src/tad.cpp src/$nombre
		rm ./tad
		rm ./basura.txt
		
	done
	rm src/*.cpp
fi