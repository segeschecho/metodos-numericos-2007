# ConvencionesDeEstilo #
Guía de estilo para el código fuente
### Guía de estilo para código fuente ###
## Por qué? ##

Cuando se programa en equipo es importante mantener un estilo coherente. Esto hace que el código sea más fácil de leer y por lo tanto simplifica encontrar bugs. Además, da una mejor presentación al trabajo.
## Ideas importantes ##

Para trabajar en equipo hay que hacer que la vida del otro sea lo más fácil posible. Para esto, es buena idea considerar al menos las siguiente ideas:
Los nombres de variables tienen que ser descriptivos. No llamar "i" a una variable si hace algo más que contar un bucle. Pero hay que conservar el sentido común: unaMuyLindaVariableTemporalQueNecesitoEnEstaFuncion no es un buen nombre de variable.
Los comentarios tienen que ser cortos, concisos y aparecer cuando son necesarios (si y solo si). Tienen que respetar el estilo descripto abajo. Es buena idea acompañar a cada método con una comentario antes de su implementación explicando qué hace. Si es un algoritmo no trivial se puede incorporar un segundo comentario explicando la idea que sigue el algoritmo antes de su código. Solo cuando realmente se esté haciendo magia negra es bueno poner comentarios espolvoreados en el código (y es dudoso que hacer esa magia negra fuera buena idea en primer lugar!).
En general si la performance no es crítica es mejor implementar un algoritmo fácil de leer y entender que algo super veloz y críptico.
## TODOs y FIXMEs ##

Cuando algo no está implementado aún o tiene que ser mejorado, o tiene un bug conocido, usar estas etiquetas con libertad para indicarlo en el código, acompañados de una breve explicación. Estos se revisan antes de dar por completado el código. Mejor que sobren y no falten, es mucho peor olvidarse de hacer algo que perder 5 minutos recorriendo código fuente con un buscador de texto.

Ejemplos:
// FIXME: muy lento, implementar sin recursión
int fibo(int n) {
(...)

// TODO: implementar tests para este método
void Clasecita::Metodo() {
(...)
## Leyes ##

Estas son las guías que debe seguir el código fuente:
Usar CamelCase para nombres de variables y métodos (Ejemplo: nombreDeVariable)
Usar UpperCamelCase para nombres de clases (Ejemplo: NombreDeClase)
Indentar con 4 espacios únicamente, nunca tabs
Dejar espacios entre los símbolos (a excepción de los paréntesis)
Ejemplo:
```
if(a==b){ // incorrecto
if(a == b) { // correcto
a=3/2+h; // incorrecto
a = 3 / 2 + h; // correcto
```
Las llaves se abren en la misma línea de la sentencia de control, y se cierran en una nueva línea.
Ejemplo:
```
if(a == b) {
    // codigo
}
NO hacer esto bajo ningún concepto so pena de ofender a los dioses: 
if(a == b)
    {
    // codigo
    }
```
Los elses y elseifs van en líneas nuevas (no en la misma línea que la llave que se cierra)
NO PASARÁS de 100 caracteres por línea bajo ningún concepto, y en lo posible siempre usar menos de 80 a menos que haya una muy buena razón para usar los 20 restantes.
Los comentarios se hacen con "// " (no olvidar el espacio al final), al nivel de indentación que corresponde al bloque en el que estamos. No usar comentarios multilínea (/**codigo**/) a menos que sea para comentar un bloque de código que por alguna razón no se usa pero tenga que permanecer en el archivo para discusión futura. Muy importante: no usar caracteres especiales en los comentarios (acentos, eñes, etc). Esto trae problemas al compartir el código ya que las IDEs caprichosas pueden cambiar los encodings y esto genera cambios innecesarios en el repositorio. Recordar las clases de lengua de la primaria no está de más tampoco.
Ejemplo:
```
Buen comentario:
// Esta funcion cuenta los miembros del equipo.
Mal comentario:
//cuantos miembros en el equipo
```
Usar "p->a" siempre en lugar de "(**p).a"
Los operadores** y & cuando acompañan a declaraciones de tipo, deben ir pegados al nombre del tipo, no al de la variable.
Ejemplo:
```
int* p; // correcto
int *p; // incorrecto
TipoPesado& t; // correcto
TipoPesado &t; // incorrecto
```
## LATEX ##

Las reglas para LATEX se derivan de las de C++. Se indenta con 4 espacios, de forma coherente. Se deben usar espacios para separar los diferentes bloques de parámetros de los comandos (que van entre llaves), y también puede ser buena idea ir a la línea entre los parámetros por claridad. Estas reglas no se aplican a las librerías proporcionadas por la cátedra ya que en principio no hay que tocarlas, pero sí hay que seguirlas en los archivos propios.
Ejemplo:
```
% incorrecto
\comando{parametro1}{parametro2}
% correcto
\comando {parametro1} {parametro2}
\comando {parametro1}
         {parametro2}
```
# Uso del repositorio #

Siempre que se hagan cambios, indicar lo que se hizo en el mensaje que acompaña al commit. Si se tienen que cambiar varias cosas significantes, es mejor separarlo en varias revisiones en lugar de meter muchos cambios grandes en un solo commit. En caso de querer revertir algo, es más complicado si el paso de una revisión a otra es muy grande.

Por último, la máxima del desarrollo compartido (para imprimir y llevar en la billetera): NUNCA JAMÁS COMMITEARÁS CÓDIGO QUE NO COMPILE, NI ARCHIVOS DE TU IDE NI NADA QUE NO SEA ESTRICTAMENTE PARTE DEL SAGRADO CÓDIGO.

La segunda máxima del desarrollo compartido es: LA CONSISTENCIA ES MI RAZÓN DE VIVIR Y NUNCA POR MÍ SERÁ VIOLADA Qué significa esto? Que si se va a hacer algún cambio de estilo o de convención de uso o de aridades de funciones, es imperativo que se actualicen todas las referencias. Si una función que usaba array ahora usa secuencia, hay que cambiar todas las llamadas (o en su defecto indicarlo con un TODO). Esto es vital para mantener el código ordenado: nunca tiene que quedar en el el HEAD una versión inconsistente.

Eso es todo, espero que les haya gustado (y que le den algo de bola ya que están).