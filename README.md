# <img src="./img/LogoTelegramGroup.png" width="50"/> Taller sensor IoT de radiactividad
Taller IoT para construir un medidor Geiger conectado. Basado en el ESP8266, MQTT, Node-RED e integrado en la red GMC

## Componentes que vamos a utilizar
**Hardware**
- [WEMOS D1 Mini Pro 16 MBytes con antena externa](https://s.click.aliexpress.com/e/kMC1v8nW) ×	1	 
<img src="./img/WemosD1MiniPro.png" width="250" align="right" />
La placa de prototipo Wemos D1 Mini es microcontrolador muy versatil y de tamaño reducido.
  - Permite ser programado directamente desde el IDE de Arduino.
  - Ofrece pines de voltajes de salida de 3,2V y 5V.
  - Tiene conectividad Wi-Fi con todo el estak de TCP/IP.
  - Incluye el chip CP2104 USB-TO-UART IC
  - El microcontrolador incorporado es el ESP-8266EX
    - Con un voltaje de funcionamiento: 3,3 V (chip) 5 V (placa)
    - Tiene 11 pines de E/S digitales: de los cuales 2 son serie y otros 2 para I2C
    - Pines de entrada analógica: 1 (entrada máxima: 3,2 V)
    - 16M bytes(128M bit) Flash


- https://es.aliexpress.com/item/1005004074447194.html

## Software
### Instalación del IDE de Arduino.
Puedes descargar la última versión del IDE de Arduino desde [este sitio web](https://www.arduino.cc/en/software) si aún no la tienes.

Los sistemas Mac y Windows tienen opciones de instalación típicas. Los usuarios de Linux pueden beneficiarse de [esta información adicional](https://docs.arduino.cc/software/ide-v1/tutorials/Linux) en el sitio web de Arduino.

### Añadir la placa ESP en el manager
Una vez que se haya instalado el IDE de Arduino, ábralo y haga clic en preferencias .
<img src="./img/ESPPreferencesIDE.png" width="500"/> 

Tendremos que agregar esta  URL em la caja de texto de "Additional board manager URLs":
```
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
Si ya hay URL registradas se puede hacer clic en el ícono pequeño a la derecha del cuadro de texto para registrar varias URL's.

### Añadir las placas ESP para el configurador
Ahora podemos agregar los tableros ESP haciendo clic en la opción herramientas > tablero > administrador de tableros… en el menú.
<img src="./img/ESPBoardsIDE.png" width="500"/> 

Busqua el paquete ESP8266 e instálalo. Una vez que se haya instalado, puedes cerrar el administrador de placas.

### Elige la placa y el puerto
A continuación, debemos seleccionar la placa Wemos D1 Mini PRO del menú de herramientas. Tendremos que seleccionar **LOLIN (WEMOS) D1 mini PRO** de los dispositivos ESP recién agregados.

<img src="./img/WEMOSD1PROSettingIDE.png" width="500"/> 

Finalmente, debemos elegir el puerto correcto en el menú de herramientas . En Mac/Linux esto aparecerá como algo así como **dev/cu.usbserial-xxxx** y en Windows será **COMX\**.
