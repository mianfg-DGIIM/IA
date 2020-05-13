`IA` **Inteligencia Artificial** - Prácticas

# Práctica 1. Agentes Conversacionales

> Alumno: Miguel Ángel Fernández Gutiérrez
>
> 3º Doble Grado en Ingeniería Informática y Matemáticas, 2019/2020
> Inteligencia Artificial - DECSAI UGR



A continuación, le envío pruebas de la ejecución del agente. Las conversaciones que figuran a continuación son resultado de "copiar y pegar" la salida de la ejecución de `run.sh`.

### Consideraciones relevantes

* La fecha de "hoy" para el agente es el **martes, 18 de febrero de 2020**.
* En diferentes conversaciones (separadas por cuadros de texto diferentes), el número y localización de las citas ocupadas puede variar (las he modificado para tener más variedad en el _output_). Sin embargo, en una misma conversación no se ha modificado el archivo `eventos.txt` más allá de cómo lo modifique el propio agente.



## Nivel 0

En el propio archivo de reglas `nivel0.aiml` aparecen comentadas las preguntas a las que puede responder.



## Nivel 1

```
Human: Me gustaría concertar una cita para el 18 de febrero a las 20:00
Robot: Perfecto, queda marcada la cita de las 20:00 para el 18 febrero 20. ¿Desea pedir alguna otra cita?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```

```
Human: Me gustaría concertar una cita para el 18 de febrero de 2020 a las 20:00
Robot: La hora que ha introducido no se encuentra disponible, ¿desea pedir otra cita?
Human: Sí
Robot: ¿Para cuándo quiere la cita?
Human: Para el 19 de febrero
Robot: ¡Tenemos citas disponibles para el 19 febrero 20! ¿Desea la cita por la mañana, por la tarde o le da igual?
Human: Me gustaría por la mañana
Robot: Pues tengo los siguientes huecos libres para el 19 febrero 20 por la mañana: 08:00 09:00 10:00 11:00 12:00. ¿Quiere alguno en concreto?
Human: Sí a las 09:00
Robot: Perfecto, queda marcada la cita de las 09:00 para el 19 febrero 20. ¿Quiere alguna otra cita más?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```

```
Human: Me gustaría concertar una cita para el 17 de febrero
Robot: Lo siento, no hay citas para ese día, ¿desea ver la disponibilidad para algún otro?
Human: Si
Robot: Genial, especifique cuándo quiere otra cita.
Human: El 19 de febrero
Robot: ¡Tenemos citas disponibles para el 19 febrero 20! ¿Desea la cita por la mañana, por la tarde o le da igual?
Human: Me da igual
Robot: El próximo hueco libre es a las 08:00, ¿lo desea?
Human: No
Robot: El siguiente hueco libre es a las 10:00, ¿lo desea?
Human: No
Robot: El siguiente hueco libre es a las 11:00, ¿lo desea?
Human: No
Robot: El siguiente hueco libre es a las 17:00, ¿lo desea?
Human: No
Robot: El siguiente hueco libre es a las 18:00, ¿lo desea?
Human: No
Robot: El siguiente hueco libre es a las 19:00, ¿lo desea?
Human: No
Robot: El siguiente hueco libre es a las 20:00, ¿lo desea?
Human: No
Robot: No hay mas huecos libres, ¿desea otro día?
Human: Sí
Robot: Genial, especifique cuándo quiere otra cita.
Human: El 20 de febrero
Robot: ¡Tenemos citas disponibles para el 20 febrero 20! ¿Desea la cita por la mañana, por la tarde o le da igual?
Human: Me da absolutamente igual la verdad
Robot: El próximo hueco libre es a las 08:00, ¿lo desea?
Human: Si
Robot: Perfecto, queda marcada la cita de las 08:00 para el 20 febrero 20. ¿Quiere alguna otra cita más?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```

```
Human: Quiero una cita para el 2 de marzo
Robot: ¡Tenemos citas disponibles para el 2 marzo 20! ¿Desea la cita por la mañana, por la tarde o le da igual?
Human: Espera que me aclare
Robot: Por favor, especifique si desea la cita por la mañana, por la tarde o le da igual. Si no quiere una cita para el 2 marzo 20, díganoslo.
Human: No quiero una cita para ese día
Robot: No hay problema, ¿desea una cita para otro día?
Human: Sí
Robot: Genial, especifique cuándo quiere otra cita.
Human: 3 marzo 20
Robot: ¡Tenemos citas disponibles para el 3 marzo 20! ¿Desea la cita por la mañana, por la tarde o le da igual?
Human: Me da igual
Robot: El próximo hueco libre es a las 09:00, ¿lo desea?
Human: Pff
Robot: Perdona, no te he entendido, ¿desea o no el hueco de las 09:00?
Human: Sí
Robot: Perfecto, queda marcada la cita de las 09:00 para el 3 marzo 20. ¿Quiere alguna otra cita más?
Human: Sí
Robot: ¿Para cuándo quiere la cita?
Human: Para el 6 de marzo
Robot: ¡Tenemos citas disponibles para el 6 marzo 20! ¿Desea la cita por la mañana, por la tarde o le da igual?
Human: Por la tarde
Robot: Pues tengo los siguientes huecos libres para el 6 marzo 20 por la tarde: 13:00 14:00 15:00 16:00 17:00 18:00 19:00 20:00. ¿Quiere alguno en concreto?
Human: 19:00
Robot: Perfecto, queda marcada la cita de las 19:00 para el 6 marzo 20. ¿Quiere alguna otra cita más?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```



## Nivel 2

```
Human: Hola, me gustaría una cita para mañana por la mañana
Robot: Pues tengo los siguientes huecos libres para el 19 febrero 20 por la mañana: 08:00 10:00 11:00 12:00. ¿Quiere alguno en concreto?
Human: Sí el de las 12:00
Robot: Perfecto, queda marcada la cita de las 12:00 para el 19 febrero 20. ¿Quiere alguna otra cita más?
Human: No gracias
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```

```
Human: Hola, quisiera una cita para pasado maniana      
Robot: ¡Tenemos citas disponibles para el 20 febrero 20! ¿Desea la cita por la mañana, por la tarde o le da igual?
Human: Me da igual
Robot: El próximo hueco libre es a las 10:00, ¿lo desea?
Human: Si
Robot: Perfecto, queda marcada la cita de las 10:00 para el 20 febrero 20. ¿Quiere alguna otra cita más?
Human: No hasta luego
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```

```
Human: Buenas quisiera una cita para el próximo lunes a las 19:00
Robot: Perfecto, queda marcada la cita de las 19:00 para el 24 febrero 20. ¿Desea pedir alguna otra cita?
Human: Sí
Robot: ¿Para cuándo quiere la cita?
Human: Para el siguiente martes por la tarde
Robot: Pues tengo los siguientes huecos libres para el 25 febrero 20 por la tarde: 13:00 14:00 15:00 16:00 17:00 18:00 19:00 20:00. ¿Quiere alguno en concreto?
Human: No
Robot: Sin problema, ¿desea pedir alguna otra cita?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```



## Nivel 3

###### Alternativa 1

El usuario tiene claro qué día proponer (volvemos a los niveles 1 y 2)

```
Human: Hola buenas
Robot: Hola, buenas, ¿qué desea?
Human: Quiero una cita
Robot: ¿Para cuándo quiere la cita?
Human: Para el próximo lunes por la tarde
Robot: Pues tengo los siguientes huecos libres para el 24 febrero 20 por la tarde: 13:00 14:00 16:00 17:00 18:00 20:00. ¿Quiere alguno en concreto?
Human: Sí
Robot: Por favor, especifique qué hueco quiere para el día 24 febrero 20, o díganos si no desea concertar una cita para ese día.
Human: No quiero una cita en verdad
Robot: Sin problema, ¿desea pedir alguna otra cita?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```



###### Alternativa 2

El usuario no lo tiene claro

```
Human: Buenas
Robot: Hola, buenas, ¿qué desea?
Human: Quiero una cita
Robot: ¿Para cuándo quiere la cita?
Human: La verdad es que no lo tengo muy claro
Robot: ¡No se preocupe! Le guiaré en la búsqueda de su cita. ¿Quiere comprobar si hay citas libres para esta semana?
Human: No
Robot: No hay problema, ¿consulto la semana siguiente, del 24 febrero 20 al 28 febrero 20?
Human: Sí
Robot: No tenemos citas para la semana del 24 febrero 20 al 28 febrero 20. ¿Quiere que consulte la agenda para la semana siguiente, del 2 Marzo 2020 al 6 Marzo 2020?
Human: Sí
Robot: ¡Tenemos citas disponibles para la semana del 2 Marzo 2020 al 6 Marzo 2020! ¿Quiere la cita por la mañana, por la tarde o le da igual?
Human: Quiero por la mañana gracias
Robot: La semana del 2 Marzo 2020 al 6 Marzo 2020 tengo libres por la mañana los siguientes días: 2 Marzo 2020  3 Marzo 2020  4 Marzo 2020  5 Marzo 2020  6 Marzo 2020. ¿Cuándo quiere la cita?
Human: No me viene bien ninguno
Robot: No hay problema, ¿quiere cita para la semana siguiente, del 9 Marzo 2020 al 13 Marzo 2020?
Human: Sí
Robot: ¡Tenemos citas disponibles para la semana del 9 Marzo 2020 al 13 Marzo 2020! ¿Quiere la cita por la mañana, por la tarde o le da igual?
Human: Por la tarde
Robot: La semana del 9 Marzo 2020 al 13 Marzo 2020 tengo libres por la tarde los siguientes días: 9 Marzo 2020  10 Marzo 2020  11 Marzo 2020  12 Marzo 2020  13 Marzo 2020. ¿Cuándo quiere la cita?
Human: La quiero el martes de esa semana
Robot: Pues tengo los siguientes huecos libres para el 10 Marzo 20 por la tarde: 13:00 14:00 15:00 16:00 17:00 18:00 19:00 20:00. ¿Quiere alguno en concreto?
Human: Sí el de las 16:00
Robot: Perfecto, queda marcada la cita de las 16:00 para el 10 Marzo 20. ¿Quiere alguna otra cita más?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```

```
Human: Hola
Robot: Hola, buenas, ¿qué desea?
Human: Una cita
Robot: ¿Para cuándo quiere la cita?
Human: No sé
Robot: ¡No se preocupe! Le guiaré en la búsqueda de su cita. ¿Quiere comprobar si hay citas libres para esta semana?
Human: Sí
Robot: ¡Tenemos citas disponibles para la semana del 18 febrero 20 al 21 febrero 20! ¿Quiere la cita por la mañana, por la tarde o le da igual?
Human: Me da igual
Robot: La semana del 18 febrero 20 al 21 febrero 20 tengo libres los siguientes días: 18 febrero 20  19 febrero 20  20 febrero 20  21 febrero 20. ¿Cuándo quiere la cita?
Human: No la quiero esos días
Robot: No hay problema, ¿quiere cita para la semana siguiente, del 24 febrero 20 al 28 febrero 20?
Human: Tengo libre la semana del 16 de marzo
Robot: ¡Tenemos citas disponibles para la semana del 16 marzo 2020 al 20 marzo 2020! ¿Quiere la cita por la mañana, por la tarde o le da igual?
Human: Me da igual
Robot: La semana del 16 marzo 2020 al 16 marzo 2020 tengo libres los siguientes días: 16 marzo 2020  17 marzo 2020  18 marzo 2020  19 marzo 2020  20 marzo 2020. ¿Cuándo quiere la cita?
Human: Pues quiero la cita para el jueves
Robot: ¡Tenemos citas disponibles para el 19 marzo 20! ¿Desea la cita por la mañana, por la tarde o le da igual?
Human: Me da igual 
Robot: El próximo hueco libre es a las 08:00, ¿lo desea?
Human: Sí
Robot: Perfecto, queda marcada la cita de las 08:00 para el 19 marzo 20. ¿Quiere alguna otra cita más?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```

```
Human: Hola buenas
Robot: Hola, buenas, ¿qué desea?
Human: Llamaba para concertar una cita
Robot: ¿Para cuándo quiere la cita?
Human: No lo tengo claro
Robot: ¡No se preocupe! Le guiaré en la búsqueda de su cita. ¿Quiere comprobar si hay citas libres para esta semana?
Human: Sí
Robot: ¡Tenemos citas disponibles para la semana del 18 febrero 20 al 21 febrero 20! ¿Quiere la cita por la mañana, por la tarde o le da igual?
Human: Me da igual
Robot: La semana del 18 febrero 20 al 21 febrero 20 tengo libres los siguientes días: 18 febrero 20  19 febrero 20  20 febrero 20  21 febrero 20. ¿Cuándo quiere la cita?
Human: La quiero el jueves por la mañana
Robot: Pues tengo los siguientes huecos libres para el 20 febrero 20 por la mañana: 12:00. ¿Quiere alguno en concreto?
Human: Ahora que lo pienso no
Robot: Sin problema, ¿desea pedir alguna otra cita?
Human: No
Robot: ¡Perfecto! ¡Nos vemos pronto! :)
```

```
Human: Quisiera una cita
Robot: ¿Para cuándo quiere la cita?
Human: No sé
Robot: ¡No se preocupe! Le guiaré en la búsqueda de su cita. ¿Quiere comprobar si hay citas libres para esta semana?
Human: Sí
Robot: ¡Tenemos citas disponibles para la semana del 18 febrero 20 al 21 febrero 20! ¿Quiere la cita por la mañana, por la tarde o le da igual?
Human: mañana
Robot: La semana del 18 febrero 20 al 21 febrero 20 tengo libres por la mañana los siguientes días: 18 febrero 20  19 febrero 20  20 febrero 20  21 febrero 20. ¿Cuándo quiere la cita?
Human: Quiero la cita para el lunes
Robot: Lo siento, no hay citas para ese intervalo de tiempo, ¿desea ver la disponibilidad para algún otro día?
Human: Sí
Robot: Genial, especifique cuándo quiere otra cita.
Human: No lo tengo claro
Robot: ¡No se preocupe! Le guiaré en la búsqueda de su cita. ¿Quiere comprobar si hay citas libres para esta semana?
```

En caso de que hoy sea fin de semana, no dirá si quiere comprobar citas para esta semana, sino para la que viene (en este caso, la fecha de "hoy" es **sábado, 28 de marzo de 2020**):

```
Human: Quiero concertar una cita
Robot: ¿Para cuándo quiere la cita?
Human: No tengo ni idea
Robot: ¡No se preocupe! Le guiaré en la búsqueda de su cita. ¿Quiere comprobar si hay citas libres para la semana que viene?
Human: Sí
Robot: ¡Tenemos citas disponibles para la semana del 30 marzo 20 al 3 Abril 20! ¿Quiere la cita por la mañana, por la tarde o le da igual?
```

