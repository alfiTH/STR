if [ -z $1 ]; then echo "Debe incluirse la ruta a la carpeta que contenga los ficheros ClasesPosix.h/.cpp e Identificador.h/.cpp"
else
	if [ ! -d $1 ]; then echo "la ruta a la carpeta que contenga los ficheros ClasesPosix.h/.cpp e Identificador.h/.cpp es errónea"
	else g++ -I$1 p1.cpp pila_acotada.cpp $1/ClasesPosix.cpp $1/Identificador.cpp -o p1 -lpthread
	fi
fi
