with GNAT.IO; use GNAT.IO;
-- A�adir el paquete controlador


procedure p2_2 is
   procedure senial_capturada(capturadas: Natural; max_capturas: Positive) is begin
      Put_line("Se han capturado" & integer'image(capturadas) & " se�ales SIGINT de" & integer'image(max_capturas));
   end senial_capturada;

   -- Definir el tipo tarea EsperarCtrlC con un par�metro de tipo positive (tiene que ser mayor que 0) para indicar el n�mero de se�ales esperadas

   -- Implementaci�n el cuerpo del tipo tarea EsperarCtrlC
   -- Zona de declaraci�n

      -- Declarar una variable de tipo Natural (puede contener valores mayores o iguales que 0) para contar el n�mero de ocurrencias de la se�al SIGINT e inicializarla a 0

   -- Zona de c�digo

      -- Mientras no se hayan recibido las se�ales esperadas

         -- Invocar a la entrada Wait de ControladorSigInt para esperar a que se pulse Ctrl+C

         -- Incrementar las se�ales recibidas

         -- Mostrar el mensaje "Se han capturado xxxx se�ales SIGINT de yyyy" siendo xxxx el n�mero de se�ales capturadas e yyyy el n�mero de se�ales esperadas (usar el procedimiento
         -- senial_capturada)

      -- Fin mientras

   -- Fin del cuerpo del tipo tarea EsperarCtrlC

   -- Crear una tarea de tipo EsperarCtrlC pasando por par�metros el n�mero de se�ales SIGINT que debe recibir

begin
   null;
end p2_2;
