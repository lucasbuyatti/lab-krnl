# Configuración de Visual Studio 2022 (Comodidad)
Configurar Proyecto de Inicio >> Selección Actual

# Conocimiento Adquirido
Windbg
Display Bytes EPROCESS PTR + PEB OFFSET

db FFFF838E28C840C0+0x550
| Dirección de Memoria | Contenido en Bytes | Contenido interpretado (hexadecimal a decimal, decimal a ASCII) |
|-----------------------|---------------------|----------------------------------------------------------------|
| ffff838e28c84610     | 00 f0 59 26 f9 00 00 00-b0 3c f3 25 8e 83 ff ff | ..Y&.....<.%.... |
| ffff838e28c84620     | 00 00 00 00 00 00 00 00-c0 3c 0d 27 8e 83 ff ff | .........<.'.... |
| ffff838e28c84630     | 80 f7 55 d6 84 99 ff ff-00 00 00 00 00 00 00 00 | ..U............. |
| ffff838e28c84640     | 00 00 00 00 00 00 00 00-af be 13 cc 84 99 ff ff | ................ |
| ffff838e28c84650     | 90 67 af 2c 8e 83 ff ff-00 00 00 00 00 00 00 00 | .g.,............ |
| ffff838e28c84660     | a0 96 ba 2a 8e 83 ff ff-4e 6f 74 65 70 61 64 2e | ...*....Notepad. |
| ffff838e28c84670     | 65 78 65 00 00 00 00 02-00 00 00 00 00 00 00 00 | exe............. |
| ffff838e28c84680     | 50 aa a9 25 8e 83 ff ff-88 70 00 2a 8e 83 ff ff | P..%.....p.*.... |
