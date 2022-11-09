--Inicio del cuerpo del paquete pila_acotada
package body pila_acotada is
   -- Definir el cuerpo del objeto protegido PilaAcotada
   protected body PilaAcotada is
      -- A�adir la cabecera de la entrada PilaAniadir (debe ser igual que en el fichero .ads)
      entry PilaAniadir(Item: in integer)
         -- A�adir la condici�n de acceso a la entrada (Pila no llena) de la forma "when Condici�n is", siendo Condici�n la condici�n que se debe cumplir para entrar en la entrada
         when Cima < Tamanio_Pila is
         -- Comienzo del c�digo de la entrada PilaAniadir
         begin
         -- Incrementar Cima
         Cima:= Cima + 1;
         -- A�adir Item a la posici�n Cima de Pila
         Pila(Cima):=Item;
         -- Fin de la entrada PilaAniadir
         end PilaAniadir;

      -- A�adir la cabecera de la entrada PilaSacar (debe ser igual que en el fichero .ads)
      entry PilaSacar(Item: out integer)
      -- A�adir la condici�n de acceso a la entrada (Pila no vac�a) de la forma "when Condici�n is", siendo Condici�n la condici�n que se debe cumplir para entrar en la entrada
      when Cima > 0 is
      -- Comienzo del c�digo de la entrada PilaSacar
      begin
         -- Guardar en Item el contenido de la posici�n Cima de Pila
         Item:=Pila(Cima);
         -- Decrementar Cima
         Cima:=Cima-1;
      -- Fin de la entrada PilaSacar
      end PilaSacar;
   -- Fin del cuerpo del del objeto protegido PilaAcotada
   end PilaAcotada;
--Fin del paquete pila_acotada
end pila_acotada;

