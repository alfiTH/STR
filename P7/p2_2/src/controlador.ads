-- A�adir el paquete  de interrupciones de ADA

-- A�adir el paquete  de nombres de interrupciones de ADA


-- Inicio del paquete controlador

   -- Crear un objeto protegido de nombre ControladorSigInt (no pondremos el type, ya que queremos creal el objeto espec�fico y no un tipo)

      -- Definir un procedimiento Interrupcion sin par�metros

      -- Definir una entrada Wait sin par�metros

      -- Incluir el pragma Interrupt_Handler con Interrupcion como par�metro (indica que Interrupcion ser� un manejador de interrupci�n)

      -- Incluir el pragma Attach_Handler con Interrupcion y Sigint como par�metros (indicar� que Interrupcion manejar� la se�al Sigint)

      -- Incluir el pragma Unreserve_All_Interrupts sin par�metros (necesario para que se puedan manejar las interrupciones)

   -- Zona privada del objeto

      -- Definir un atributo booleano e inicializarlo a falso para indicar si se ha producido la ocurrencia de la se�al o no

   -- Fin del objeto ControladorSigInt

-- Fin del paquete controlador
