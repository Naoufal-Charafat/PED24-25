# mio
for FILE in *PRUEBA/tad*.cpp ; do 
    echo "Evaluando $FILE"
    
    cp "$FILE" src/tad.cpp 
    rm -f ./tad
    make

    echo "---------- Salida de $FILE ----------"
    ./tad
    echo "-------------------------------------"
done
