-- Añadir el paquete  de interrupciones de ADA

-- Añadir el paquete  de nombres de interrupciones de ADA


-- Inicio del paquete controlador

   -- Crear un objeto protegido de nombre ControladorSigInt (no pondremos el type, ya que queremos creal el objeto específico y no un tipo)

      -- Definir un procedimiento Interrupcion sin parámetros

      -- Definir una entrada Wait sin parámetros

      -- Incluir el pragma Interrupt_Handler con Interrupcion como parámetro (indica que Interrupcion será un manejador de interrupción)

      -- Incluir el pragma Attach_Handler con Interrupcion y Sigint como parámetros (indicará que Interrupcion manejará la señal Sigint)

      -- Incluir el pragma Unreserve_All_Interrupts sin parámetros (necesario para que se puedan manejar las interrupciones)

   -- Zona privada del objeto

      -- Definir un atributo booleano e inicializarlo a falso para indicar si se ha producido la ocurrencia de la señal o no

   -- Fin del objeto ControladorSigInt

-- Fin del paquete controlador
