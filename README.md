##Integrantes:

  - Mateo Carvajal Muñoz.
  - Julian Andres Rodriguez.

##Descripcion del programa:

   - El programa fue desarrollado en c++, el cual se comunica con el programa [Sysctrl](https://github.com/agomezl/Sysctrl.git "Sysctrl"), basicamente tiene 3 clases:
     - input.h es un struct que define los metodos del programa.
     - input.cpp esta clase define como se leera los documentos en el formato YAML.
     - practica.cpp es la clase que realiza todo el procedimiento de leer el documento
       y llamar al programa sysctrl para que analice los datos.
       

##Como usar el programa:

Primero para poder usar el programa es necesario intregrar una variable 
de ambiente que permita al programa poder comunicarse con el programa 
externo "Sysctrl", para ello debe escribir en consola: 

```
  - PAHT=$PATH:/home/"Usuario de maquina"/"Ruta donde esta el ejecutable de sysctrl"
```

Una vez agregada la variable de entorno revisar de que esta si este funcionando,
para esto solo escribimos en la terminal "sysctrl" para lo cual debe aparecer lo
siguiente:

```
	Usage: sysctrl [-hvn] [-f File] <conf.yaml> 
  	-h       --help             print Help
  	-v       --version          print version
  	-f File  --file=File        use file as input commands
  	-n       --non-interactive  Non-interactive prompt (no readline suport)
```

Una vez funcionando el sysctrl procedemos a ir a la ruta de la carpeta del programa
por medio de la terminal. Esta carpeta debera contener lo siguiente: 
     
```
    .
	 └── st0257-practicasistemasoperativos
    	     ├── examples
    	     ├── makefile
    	     ├── README.md
    	     └── src
```

Cuando estemos parados dentro de la carpeta del proyecto "st0257-practicasistemasoperativos"
ingresaremos en consola el comando "make" para que nos cree el ejecutable del archivo.
Una vez compilado el programa, este debio haber creado una carpeta "bin" y dentro de esta 
el ejecutable llamado "autoTester". Para ejecutarlo escribimos el siguiente comando:

```
	- ./bin/autoTester examples/"nombre del archivo".yaml
```
   
Con esto correra los ejemplos que se dispongan y arrojara los resultados.