-- A�adir el paquete  de interrupciones de ADA
with Ada.Interrupts; use Ada.Interrupts;
with Ada.Interrupts.Names; use Ada.Interrupts.Names;
-- A�adir el paquete  de nombres de interrupciones de ADA


-- Inicio del paquete controlador
package controlador is 
   -- Crear un objeto protegido de nombre ControladorSigInt (no pondremos el type, ya que queremos creal el objeto espec�fico y no un tipo)
   protected ControladorSigInt is 
      -- Definir un procedimiento Interrupcion sin par�metros
      procedure Interrupcion;
      -- Definir una entrada Wait sin par�metros
      entry Wait;
      -- Incluir el pragma Interrupt_Handler con Interrupcion como par�metro (indica que Interrupcion ser� un manejador de interrupci�n)
      pragma Interrupt_Handler(Interrupcion);
      -- Incluir el pragma Attach_Handler con Interrupcion y Sigint como par�metros (indicar� que Interrupcion manejar� la se�al Sigint)
      pragma Attach_Handler(Interrupcion, SIGINT);
      -- Incluir el pragma Unreserve_All_Interrupts sin par�metros (necesario para que se puedan manejar las interrupciones)
      pragma Unreserve_All_Interrupts;
   -- Zona privada del objeto
   private
      -- Definir un atributo booleano e inicializarlo a falso para indicar si se ha producido la ocurrencia de la se�al o no
      senial : boolean := false;
   -- Fin del objeto ControladorSigInt
   end ControladorSigInt;
-- Fin del paquete controlador
end controlador;
