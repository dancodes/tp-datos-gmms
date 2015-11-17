# TP de 75.06 Datos en C++
*Por el lindo grupo de Team GMMS <3*

# ¿Dani, que mierda es cada clase?

Explicación (son solo 4!!!):

--

### Menu

Una "linda" interfaz que va a ser basicamente:

	Seleccione el archivo de entrenamiento [train.csv]: train.csv
	Seleccione el archivo de prueba [test.csv]: test.csv
	Seleccione el archivo de salida [submission.csv]: submission.csv

	Listo ahora hago todo yo.

### ContextoArchivos

Hace referencia a los archivos de train.csv y de test.csv, que se cargan desde el menu.

### DataFrame

Es un archivo csv convertido a un objeto listo para manipularse. Imaginense una matriz que le puedas decir "sacame esta columna", "dame los primeros 50 de tal y tal atributo", etc. Basicamente un contenedor.

### Clasificador

Clase abstracta a la cual le enchufas un DataFrame de entrada (el train.csv), le decis que prediga otro DataFrame, y te da uno final de salida (con las probabilidades)


### Te amo dani <3
