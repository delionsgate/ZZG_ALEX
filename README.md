# ZZG_ALEX
ALEX (Analizador Léxico)

UNIVERSIDAD NACIONAL AUTÓNOMA DE MÉXICO
Compiladores  -  Grupo 03
Semestre 2023-1
Profesora: M.C. Laura Sandoval Montaño

Por: Zuriel Zárate García

Objetivo: Elaborar un analizador léxico en lex/flex
          que reconozca los componentes léxicos
          pertenecientes a las clases descritas.

ALEX es un analizador léxico diseñado para el lenguaje definido en la clase
de la profesora M.C. Laura Sandoval Montaño. Para más detalles, vea el documento
de descripción: DescripProgAnalizadorLex23-1.pdf


#INSTALACIÓN (LINUX)
1.- Descargue el archivo .zip

2.- Descomprima el archivo descargado, de preferencia, en una carpeta llamada ALEX
    (sólo para ubicarlo mejor).

3.- Abra una terminal nueva (ctrl+t)

4.- Sitúese en la ruta de ALEX: $cd PATH_A_ALEX/ALEX

5.- Compile el programa:
    $flex zzg_alex.l
    $gcc lex.yy.c -lfl tablas.c -o ALEX.out

6.- Ejecute el programa pasando como parametro un archivo de prueba
    con código fuente en el lenguaje definido (En el zip se incluye uno):
    $./ALEX.out prueba.txt
    
7.- Habrá una pausa para que pueda observar el trabajo del analizador.
    Para continuar con la impresión de las tablas finales, presione 'Enter' :)

8.- Revise el archivo 'salida.txt'. Ahí estarán los tokens generados y las tablas llenas.
