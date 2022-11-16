--Inicio el paquete paquetebarrera
package paquetebarrera is
   -- Definir el tipo Barrera_t privado y limitado (type NombreTipo is limited private) para poder usarlo fuera del paquete. Recibir� un par�metro de tipo positive
   -- (al ser de tipo positive, debe ser un valor mayor que 0) con el n�mero de tareas que bloquear� (10 por defecto)
   type Barrera_t(limitBarrel: positive :=10 ) is limited private;
   -- Definir el procedimiento SincronizarEnBarrera con un par�metro de entrada salida de tipo Barrera_t
   procedure SincronizarEnBarrera (Barrel: in out Barrera_t );
   -- Definir el procedimiento ResetearBarrera con dos par�metros, uno de entrada salida de tipo Barrera_t y otro de entrada de tipo Positive para cambiar
   -- el l�mite de la barrera
   procedure ResetearBarrera (Barrel: in out Barrera_t; limitBarrel: positive );
-- Definir la regi�n privada del paquete
   private
   -- Definir el objeto protegido Barrera_t. Debe coincidir con la definici�n privada del comienzo del paquete
      protected type Barrera_t(limitBarrel: positive:=10) is 
         -- Definir el procedimiento Sincronizar sin par�metros
         procedure Sincronizar;
         -- Definir la entrada Wait sin par�metros
         entry Wait;
         -- Definir el procedimiento Resetear con un par�metro de tipo positive
         procedure Resetear (limitBarrel: positive );
      -- Definir la regi�n privada del objeto protegido
      private
         -- Definir una variable de tipo natural (al ser de tipo natural, no puede tener valores negativos) para llevar la cuenta de las tereas que tienen que llegar a la barrera
         cout:natural := 0;
         -- Definir una variable de tipo positive para almacenar el n�mero de tareas que se vab a bloquear en la tarea. Inicializarlo con el par�metro de creaci�n del objeto protegido
         maxBarrel:positive := limitBarrel;
         -- Definir una variable de tipo booleano para indicar que las tareas pueden pasar o no e inicializarla a falso
         breakBarrel :boolean := false;
      -- Fin del objeto protegido Barrera_t
   end Barrera_t;
--Fin del paquete paquetebarrera
end paquetebarrera;