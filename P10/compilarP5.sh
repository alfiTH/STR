if [ -z $1 ]; then echo "Debe incluirse la ruta del fichero ClasesPosix.cpp"
else
	if [ ! -d $1 ]; then echo "la ruta al fichero ClasesPosix.cpp es errónea"
	else g++ -I$1 p5.cpp $1/ClasesPosix.cpp $1/Identificador.cpp funciones_time.cpp -o p5 -lpthread -lrt -I./
	fi
fi
