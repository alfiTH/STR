with GNAT.IO; use GNAT.IO;
-- Añadir el paquete controlador


procedure p2_2 is
   procedure senial_capturada(capturadas: Natural; max_capturas: Positive) is begin
      Put_line("Se han capturado" & integer'image(capturadas) & " señales SIGINT de" & integer'image(max_capturas));
   end senial_capturada;

   -- Definir el tipo tarea EsperarCtrlC con un parámetro de tipo positive (tiene que ser mayor que 0) para indicar el número de señales esperadas

   -- Implementación el cuerpo del tipo tarea EsperarCtrlC
   -- Zona de declaración

      -- Declarar una variable de tipo Natural (puede contener valores mayores o iguales que 0) para contar el número de ocurrencias de la señal SIGINT e inicializarla a 0

   -- Zona de código

      -- Mientras no se hayan recibido las señales esperadas

         -- Invocar a la entrada Wait de ControladorSigInt para esperar a que se pulse Ctrl+C

         -- Incrementar las señales recibidas

         -- Mostrar el mensaje "Se han capturado xxxx señales SIGINT de yyyy" siendo xxxx el número de señales capturadas e yyyy el número de señales esperadas (usar el procedimiento
         -- senial_capturada)

      -- Fin mientras

   -- Fin del cuerpo del tipo tarea EsperarCtrlC

   -- Crear una tarea de tipo EsperarCtrlC pasando por parámetros el número de señales SIGINT que debe recibir

begin
   null;
end p2_2;
