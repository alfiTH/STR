if [ -f p2_2.o ]; then rm p2_2.o; fi
if [ -f controlador.o ]; then rm controlador.o; fi
if [ -f p2_2 ]; then rm p2_2; fi
if [ -f controlador.ali ]; then rm controlador.ali; fi
if [ -f p2_2 ]; then rm p2_2; fi
gnatmake p2_2.adb -o p2_2