# Milk Collection Problem With Blending

Este es un programa en C++ que resuelve el problema de recolección de leche con mezcla. El programa toma una instancia de entrada que contiene información sobre los camiones disponibles, los tipos de leche y los nodos, y luego utiliza un enfoque voraz para asignar una ruta a los camiones.

## Requisitos

- Compilador de C++ compatible con C++11 o superior.
- Un archivo de instancia de entrada que siga el formato especificado (ver sección de Formato de Instancia de Entrada).

## Uso

Para compilar y ejecutar el programa, sigue estos pasos:

1. Abre una terminal en la ubicación del archivo fuente.

2. Utiliza el siguiente comando para compilar el programa:

    make

3. Para ejecutar el programa, Escribe lo siguiente en la línea de comandos
    
    ./Nombre_del_programa Ruta_de_instancias Numero_de_iteraciones
   
- Ejemplo
   
    ./MCPwB instances/a44.txt 1000

## Output

El output tiene el siguiente formato:
	
	Archivo: "Ruta de la instancia"
	
	Solución inicial:

	Ganancia_Final	Costo_Total	Ganancia_Total

	Ruta_Camión_1	Costo_Ruta_1	Volumen_de_Leche_Ruta_1 Tipo_de_Leche_Ruta_1
	Ruta_Camión_2	Costo_Ruta_2	Volumen_de_Leche_Ruta_2 Tipo_de_Leche_Ruta_2
	Ruta_Camión_3	Costo_Ruta_3	Volumen_de_Leche_Ruta_3 Tipo_de_Leche_Ruta_3

	Solución después de Hill-Climbing:

	Ganancia_Final	Costo_Total	Ganancia_Total

	Ruta_Camión_1	Costo_Ruta_1	Volumen_de_Leche_Ruta_1 Tipo_de_Leche_Ruta_1
	Ruta_Camión_2	Costo_Ruta_2	Volumen_de_Leche_Ruta_2 Tipo_de_Leche_Ruta_2
	Ruta_Camión_3	Costo_Ruta_3	Volumen_de_Leche_Ruta_3 Tipo_de_Leche_Ruta_3

	Tiempo total de ejecución: Tiempo[s]

Ejemplo:
	
	Archivo: instances/eil76.txt

	Solución inicial:

	90094.6    2265.38    92360

	1-67-10-22-34-25-31-46-49-76-7-28-55-13-40-58-61-37-19-52-4-64-43-70-16-73-1   669.767   42900 C
	1-41-68-5-29-65-47-11-32-59-35-53-17-2-44-62-8-20-38-26-23-14-71-56-74-50-1   755.806   46800 A
	1-12-15-33-3-57-39-60-54-51-21-6-18-48-63-27-45-9-42-30-75-69-36-66-24-72-1   839.804   46700 B

	Solución después de Hill-Climbing:

	91410.5    949.52    92360

	1-76-46-28-55-58-16-61-37-70-22-49-31-7-52-4-34-64-43-25-19-10-40-73-67-13-1   325.689   42900 C
	1-5-68-41-26-56-32-11-59-8-20-47-35-53-14-38-71-62-29-23-65-44-2-74-50-17-1   322.587   46800 A
	1-3-63-75-48-72-21-6-30-9-36-54-15-60-12-66-39-27-18-33-51-45-24-57-42-69-1   301.245   46700 B

	Tiempo total de ejecución: 2.418063[s]


En caso de mezcla, el outputPasaría a ser el siguiente:

	Archivo: "Ruta de la instancia"
	
	Solución inicial:

	Ganancia_Final	Costo_Total	Ganancia_Total

	Ruta_Camión_1	Costo_Ruta_1	Volumen_de_Leche_Ruta_1 Tipo_de_Leche_Ruta_1
	Ruta_Camión_2	Costo_Ruta_2	Volumen_de_Leche_Ruta_2 Tipo_de_Leche_Ruta_2
	Ruta_Camión_3	Costo_Ruta_3	Volumen_de_Leche_Ruta_3 Tipo_de_Leche_Ruta_3

	Solución después de Hill-Climbing:

	Ganancia_Final	Costo_Total	Ganancia_Total

	Ruta_Camión_1	Costo_Ruta_1	Volumen_de_Leche_Ruta_1 Tipo_de_Leche_Ruta_1
	Ruta_Camión_2	Costo_Ruta_2	Volumen_de_Leche_Ruta_2 Tipo_de_Leche_Ruta_2
	Ruta_Camión_3	Costo_Ruta_3	Volumen_de_Leche_Ruta_3 Tipo_de_Leche_Ruta_3

	Solución final después de la mezcla:

	Ganancia_Final	Costo_Total	Ganancia_Total

	Ruta_Camión_1	Costo_Ruta_1	Volumen_de_Leche_Ruta_1 Tipo_de_Leche_Ruta_1
	Ruta_Camión_2	Costo_Ruta_2	Volumen_de_Leche_Ruta_2 Tipo_de_Leche_Ruta_2
	Ruta_Camión_3	Costo_Ruta_3	Volumen_de_Leche_Ruta_3 Tipo_de_Leche_Ruta_3

	Tiempo total de ejecución: Tiempo[s]

Ejemplo:
	
	Archivo: instances/a44.txt

	Solución inicial:

	37865.1    2314.95    40180

	1-17-26-38-32-5-20-44-11-29-35-14-41-8-23-2-1   930.737   24400 A
	1-28-31-7-37-43-34-4-12-13-19-27-40-16-42-10-25-22-1   806.645   17600 C
	1-3-15-24-9-18-36-21-30-6-33-39-1   577.566   15000 B

	Solución después de Hill-Climbing:

	38959.4    1220.56    40180

	1-23-14-44-26-41-2-17-38-11-35-5-20-29-8-32-1   408.39   24400 A
	1-42-10-37-7-4-13-40-31-19-12-43-22-28-16-25-34-27-1   410.319   17600 C
	1-15-39-30-24-36-21-18-33-6-9-3-1   401.852   15000 B

	Solución final después de la mezcla:

	38659.4    1220.56    39880

	1-23-14-44-26-41-2-17-38-11-35-5-20-29-8-32-1   408.39   23400 A
	1-42-10-37-7-4-13-40-31-19-12-43-22-28-16-25-34-27-1   410.319   17600 C
	1-15-39-30-24-36-21-18-33-6-9-3-1   401.852   16000 B

	Tiempo total de ejecución: 0.039217[s]
