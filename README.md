# Mensajes

Este proyecto es gestor de una base de datos de personas comprendido por un servidor que accede a la informacion y clientes que pueden consultarlo. Es el segundo trabajo práctico de la materia 75.59 Técnicas de programación concurrente I de la FIUBA

Para mas información, puede revisar el [informe](https://docs.google.com/document/d/1Om4c_uCetOpWceyFtwdVO_XExd2GVdmHKO6OYZDSJv0 "Informe")

## Diagrama de procesos

El siguiente diagrama de procesos modela los diferentes procesos que se ejecutan dentro del sistema así como también las técnicas de comunicación y sincronización que utilizan entre ellos

![Diagrama de procesos](https://github.com/FedericoAmura/ConcurrentesI2018C1Conculandia/blob/master/diagramaProcesos.png "Diagrama de procesos")

## Diagrama de clases

Se adjunta un diagrama de clases de la aplicación, en ella se modelan las clases y sus distintas relaciones. Puede verse tambien [online](https://www.lucidchart.com/invitations/accept/5e77560c-b42e-41a0-93a9-eecb19302ab6 "Diagrama de clases")

![Diagrama de clases](https://github.com/FedericoAmura/ConcurrentesI2018C1Conculandia/blob/master/diagramaClases.jpeg "Diagrama de clases")

## Instalación
Para la instalación de este proyecto debe contar con cmake y las herramientas de compilación para C++11

Primero debe copiar el repositorio en el directorio destino

````bash
$ git clone https://github.com/FedericoAmura/ConcurrentesI2018C1Conculandia.git
````

Luego debe ejecutar cmake y posteriormente make para compilar los archivos fuente
````bash
$ cmake
$ make
````

Una vez terminado, ya podrá pasar a la sección de ejecución

## Ejecución
Para correr el programa debe primero ejecutar el servidor
```bash
$ ./servidor
```

Luego ejecutara tantos clientes como desee
```bash
$ ./cliente
```

Una vez dentro del cliente, un menú interactivo lo llevará para poder realizar las consultas deseadas

