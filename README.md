# Sobre el Proyecto

Este no es un proyecto terminado, sino un código de prueba desarrollado con fines de experimentación y aprendizaje. Está diseñado para explorar y entender conceptos de nivel de núcleo (kernel) y estructuras de procesos de Windows, además de trabajar un poco con ioctl para comunicar el espacio de usuario con el núcleo.

# Qué necesito saber?

- C/C++ [Modo Usuario](https://learn.microsoft.com/en-us/cpp/?view=msvc-170) [Modo kernel](https://learn.microsoft.com/en-us/windows-hardware/drivers/)
- Cómo funciona la memoria
- [Estructuras de Procesos de Windows](https://www.vergiliusproject.com/)

# Documentación

**En esta documentación, nos centraremos en el **WDM_BASE**. El propósito principal de este proyecto es proporcionar información crítica sobre un proceso específico, interactuando con los miembros de la estructura `EPROCESS`. La función clave en el proyecto es **ProcessInfoByName**, ubicada en **process.c**.**

Esta función es responsable de recuperar información sobre un proceso haciendo referencia a su estructura `EPROCESS`, que está cargada en el núcleo. El primer paso es iterar sobre los procesos utilizando el miembro `ActiveProcessLinks`, lo que permite acceder a la lista de procesos activos.

Una vez que la función encuentra el proceso objetivo, interactúa con otros miembros de la estructura, como el `PEB` (Process Environment Block), para obtener datos adicionales que no están disponibles directamente en el `EPROCESS`. Este proceso proporciona información detallada sobre el proceso objetivo, como su `UniqueProcessId`, el nombre del archivo de imagen y la dirección base de la imagen.

```mermaid
graph TD;
    A["Inicio"] --> B["Obtener EPROCESS del Proceso Actual"]
    B --> C["Acceder a la Lista de Procesos (aplList)"]
    C --> D["Iterar sobre la Lista de Procesos"]
    D --> D1["Convertir LIST_ENTRY a PEPROCESS (entry - 0x1d8)"]
    D1 --> E["Obtener Nombre de Imagen del Proceso (GetImageFileName)"]
    E --> F{"¿El Nombre Coincide?"}
    F -- No --> G["Liberar Memoria de Nombre de Imagen (ExFreePool)"]
    G --> H["Mover al Siguiente Proceso"]
    H --> I1{"¿Es Entrada Válida?"}
    I1 -- Sí --> D
    I1 -- No --> K["Terminar"]
    F -- Sí --> J["Obtener Unique Process ID (GetUniqueProcessId)"]
    J --> L["Obtener Dirección Base de la Imagen (GetImageBaseAddress)"]
    L --> M["Guardar Información del Proceso"]
    M --> K
    K --> N["Fin"]

    subgraph "Funciones Auxiliares"
        F1["GetUniqueProcessId"]
        F2["GetImageFileName"]
        F3["GetImageBaseAddress"]
    end

    D1 --> F2
    J --> F1
    L --> F3
