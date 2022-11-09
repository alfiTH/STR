#rm *.o
#rm p1
if [ -f p1.o ]; then rm p1.o; fi
if [ -f pila_acotada.o ]; then rm pila_acotada.o; fi
if [ -f p1.ali ]; then rm p1.ali; fi
if [ -f pila_acotada.ali ]; then rm pila_acotada.ali; fi
if [ -f p1 ]; then rm p1; fi
gnatmake p1.adb -o p1