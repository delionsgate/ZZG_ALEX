# ZZG_AXIN
AXIN (Analizador Léxico-Sintáctico Descendente Recursivo)

UNIVERSIDAD NACIONAL AUTÓNOMA DE MÉXICO
Facultad de Ingeniería
Compiladores  -  Grupo 03
Semestre 2023-1
Profesora: M.C. Laura Sandoval Montaño

Por: Zuriel Zárate García

Descripción: Construcción de un analizador Léxico-Sintáctico Recursivo Descendente
             que revisa programas escritos en el lenguaje definido por la gramática
             del "Anexo A" del documento: "ProgAnalizadorSintactico2023-1.pdf".

ALEX es un analizador léxico diseñado para el lenguaje definido en la clase
de la profesora M.C. Laura Sandoval Montaño. Para más detalles, vea el documento
de descripción: DescripProgAnalizadorLex23-1.pdf


#INSTALACIÓN (LINUX)
1.- Descargue el archivo .zip

2.- Descomprima el archivo descargado, de preferencia, en una carpeta llamada AXIN
    (sólo para ubicarlo mejor).

3.- Abra una terminal nueva (ctrl+alt+t)

4.- Sitúese en la ruta de ALEX: $cd PATH_A_AXIN/AXIN

5.- Compile el programa (considere '$' como símbolo de la terminal):
    $flex zzg_axin.l
    $gcc lex.yy.c -lfl tablas.c -lm asin.c -o AXIN.out

6.- Ejecute el programa pasando como parametro un archivo de prueba
    con código fuente en el lenguaje definido (En el zip se incluye uno):
    $./AXIN.out pruebaAnalSint.txt
    
7.- Habrá una pausa para que pueda observar el trabajo del analizador.
    Para continuar con el análisis sintáctico y
    la impresión de las tablas finales, presione 'Enter'.

8.- Revise el archivo 'salida.txt'. Ahí estarán los tokens generados, 
    las tablas llenas y la cadena de átomos generada.
    
NOTA: Los errores sintácticos se despliegan en terminal (si es que hay),
      no se muestran en el archivo 'salida.txt'.
