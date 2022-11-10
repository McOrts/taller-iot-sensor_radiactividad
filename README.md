# <img src="./img/LogoTelegramGroup.png" width="50"/> Taller sensor IoT de radiactividad
Taller IoT para construir un medidor Geiger conectado. Basado en el ESP8266, MQTT, Node-RED e integrado en la red GMC

## Componentes que vamos a utilizar
**Hardware**
- 1 x [WEMOS D1 Mini Pro 16 MBytes con antena externa](https://www.aliexpress.com/item/32801063577.html)
<img src="./img/WemosD1MiniPro.png" width="250" align="right" />

La placa de prototipo Wemos D1 Mini es microcontrolador muy versatil y de tamaño reducido.
  - Permite ser programado directamente desde el IDE de Arduino.
  - Ofrece pines de voltajes de salida de 3,2V y 5V.
<br>
  - Tiene conectividad Wi-Fi con todo el estak de TCP/IP.
<br>
  - Incluye el chip CP2104 USB-TO-UART IC
<br>
  - El microcontrolador incorporado es el ESP-8266EX
<br>
    _  * Con un voltaje de funcionamiento: 3,3 V (chip) 5 V (placa)
<br>
    _  * Tiene 11 pines de E/S digitales: de los cuales 2 son serie y otros 2 para I2C
<br>
    _  * Pines de entrada analógica: 1 (entrada máxima: 3,2 V)
<br>
    _  * 16M bytes(128M bit) Flash
<br>

- [Contador Geiger radiación Beta Gamma ensamblado] (https://es.aliexpress.com/item/1005004074447194.html)
<img src="./img/RadiationD_v1_1_CAJOE.png" width="700" align="right" />


## Software
### 1. Instalación del IDE de Arduino (Ver 2.0.1)
Puedes descargar la última versión del IDE de Arduino desde [este sitio web](https://www.arduino.cc/en/software) si aún no la tienes.

Los sistemas Mac y Windows tienen opciones de instalación típicas. Los usuarios de Linux pueden beneficiarse de [esta información adicional](https://docs.arduino.cc/software/ide-v1/tutorials/Linux) en el sitio web de Arduino.

### 2. Añadir la placa ESP en el manager
Una vez que se haya instalado el IDE de Arduino, ábralo y haga clic en preferencias .
<img src="./img/ESPPreferencesIDE.png" width="800"/> 

Tendremos que agregar esta  URL em la caja de texto de "Additional board manager URLs":
```
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```
Si ya hay URL registradas se puede hacer clic en el ícono pequeño a la derecha del cuadro de texto para registrar varias URL's.

### 3. Añadir las placas ESP para el configurador
Ahora podemos agregar los tableros ESP haciendo clic en la opción herramientas > tablero > administrador de tableros… en el menú.
<img src="./img/ESPBoardsIDE.png" width="300"/> 

Busca el paquete ESP8266 e instálalo. Una vez que se haya instalado, puedes cerrar el administrador de placas.

### 4. Elige la placa y el puerto
A continuación, debemos seleccionar la placa Wemos D1 Mini PRO del menú de herramientas. Tendremos que seleccionar **LOLIN (WEMOS) D1 mini PRO** de los dispositivos ESP recién agregados.
<img src="./img/WEMOSD1PROSettingIDE.png" width="700"/> 

Puede suceder que la aplicación encuentre dependencias u otras librerias desactializadas. Aparecería un mensaje como este que deberás aceptar.
<img src="./img/ESPWemosIDE.png" width="500"/> 

Finalmente, debemos elegir el puerto correcto en el menú de herramientas . En Mac/Linux esto aparecerá como algo así como **dev/cu.usbserial-xxxx** y en Windows será **COMX\**.
<img src="./img/WEMOSD1PROSettingIDE_Port.png" width="700"/> 

### 5. _Testing Point_
En este punto vamos a chequear todo cargando un _sketch_ que hará que la luz azul de la placa parpadee.
Este programa lo podrás encontrar en la ruta de ejemplos:
<img src="./img/IDE_WEMOS_test_blink.png" width="700"/> 

Con todo lo anterior configurado ahora solo tendrás que dar al botón de cargar (_upload_) y al cabo de un rato, el firmaware nuevo se cargará en la placa empezando a parpadear el LED y con estos mensajes de salida en la aplicación:
<img src="./img/IDE_WEMOS_test_blink_output.png" width="700"/> 

### 6. Añadir la librería de MQTT
Nuestro sensor va a utilizar colas MQTT para publicar sus lecturas y recbir comandos. Esta es la razón por la que hay la llamada a esta librería: 
#include <PubSubClient.h>

Por lo tanto hay se buscarla e instalarla con todas sus dependencias:
<img src="./img/ArduinoLibMQTT.png" width="700"/> 


