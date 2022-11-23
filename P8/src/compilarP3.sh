if [ -f p3.o ]; then rm p3.o; fi
if [ -f controlador.o ]; then rm controlador.o; fi
if [ -f p3 ]; then rm p3; fi
if [ -f controlador.ali ]; then rm controlador.ali; fi
if [ -f p3 ]; then rm p3; fi
gnatmake p3.adb -o p3