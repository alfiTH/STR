-- Inicio del cuerpo del paquete controlador
package body controlador is
   -- Implementaci�n del cuerpo del objeto protegido ControladorSigInt
   protected body ControladorSigInt is 
      -- Implementaci�n del procedimiento Interrupcion que lo �nico que hace es poner el atributo booleano a verdadero (este procedimiento se ejecutar� cuando ocurra la interrupci�n)
      procedure Interrupcion is
         
      begin
         senial := true;
      end Interrupcion;

      -- Implementaci�n de la entrada Wait que esperar� a que se produzca una ocurrencia (atributo booleano a verdadero) y lo �nico que hace es volver a ponerla a falso
      -- para que el objeto pueda volver a capturar se�ales
      entry Wait when senial is 
      begin
         senial:=false;
      end Wait;

   -- Fin del objeto protegido ControladorSigInt
   end ControladorSigInt;
-- Fin del cuerpo del paquete controlador
end controlador;