# Teoría de filtros digitales

Este tutorial resume los conceptos clave de filtros analógicos y digitales, apoyándose en los ejemplos y la estructura del repositorio `DSP_SIMULIDE_ARDUINO`.

El repositorio contiene:
- ejemplos de filtros digitales en Arduino (`arduino_codes/`)
- diseños basados en ecuaciones en diferencias y transferencias discretas
- simulaciones en SimulIDE (`circuito_simulide/`)
- librerías y ejemplos de implementación FIR/IIR (`arduino_codes/librerias/isbFilters`)

## 1. Filtros analógicos de primer orden

Los filtros analógicos de primer orden son los más sencillos y se usan como referencia para entender el comportamiento básico de los sistemas lineales.

### 1.1 Filtro RC pasa-bajo

Un filtro RC pasa-bajo típico consta de una resistencia serie y un condensador a masa. Su función de transferencia en el dominio de Laplace es:

H(s) = 1 / (1 + sRC)

Donde:
- `R` es la resistencia
- `C` es la capacitancia
- `s` es la variable de Laplace

La frecuencia de corte se define como:

f_c = 1 / (2πRC)

A frecuencias bajas, la ganancia se aproxima a 1. A frecuencias altas, la ganancia cae con una pendiente de -20 dB/década.

### 1.2 Filtro RC pasa-alto

Un filtro RC pasa-alto es similar, pero el condensador está en serie con la entrada y la resistencia a masa. Su función de transferencia es:

H(s) = sRC / (1 + sRC)

Este filtro atenúa señales de baja frecuencia y deja pasar las altas.

### 1.3 Resumen del orden 1

- respuesta en magnitud con pendiente -20 dB/década
- fase aproximada a 0° en bajas frecuencias y -90° en altas frecuencias (pasa-bajo)
- implementaciones simples en hardware analógico con RC

## 2. De analógico a digital

En el dominio digital, las señales se representan mediante muestras equiespaciadas en el tiempo. La transformada z es la herramienta equivalente a la transformada de Laplace para sistemas discretos.

### 2.1 Variable `z` y el plano Z

En el análisis discreto, la variable `z` se relaciona con el retraso por una muestra:

z^{-1} representa un retraso de una muestra.

La estabilidad de un filtro digital se evalúa en el plano Z:
- un filtro es estable si todos sus polos están dentro del círculo unitario (`|z| < 1`)
- los ceros afectan la respuesta en frecuencia pero no la estabilidad directa

## 3. Filtros digitales IIR (Infinite Impulse Response)

Los filtros IIR tienen una respuesta impulsional infinita porque su salida depende de valores pasados de la salida.

### 3.1 Ecuación en diferencias general

Un filtro IIR clásico se describe por la ecuación en diferencias:

y[n] = b0 x[n] + b1 x[n-1] + ... + bM x[n-M]
      - a1 y[n-1] - a2 y[n-2] - ... - aN y[n-N]

Donde:
- `x[n]` es la entrada en la muestra `n`
- `y[n]` es la salida en la muestra `n`
- `bi` son los coeficientes de feedforward
- `ai` son los coeficientes de feedback

### 3.2 Transferencia en z

La función de transferencia del filtro IIR es:

H(z) = (b0 + b1 z^{-1} + ... + bM z^{-M}) / (1 + a1 z^{-1} + ... + aN z^{-N})

Este polinomio en numerador y denominador define ceros y polos.

### 3.3 Ejemplo de implementación Arduino

En el repositorio hay varios ejemplos IIR en `arduino_codes/` y en la librería `isbFilters`, donde un filtro IIR se implementa con bucles que calculan la ecuación en diferencias en cada muestra.

Un ejemplo típico de código Arduino es:

    y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] - a1*y[n-1] - a2*y[n-2];

Este enfoque es eficiente y directo para filtros IIR de bajo orden.

## 4. Filtros digitales FIR (Finite Impulse Response)

Los filtros FIR tienen una respuesta impulsional finita porque la salida depende solo de las muestras actuales y pasadas de la entrada.

### 4.1 Ecuación en diferencias FIR

La forma general de un filtro FIR es:

y[n] = b0 x[n] + b1 x[n-1] + ... + bM x[n-M]

No hay coeficientes `a` de feedback.

### 4.2 Propiedades de los FIR

- siempre son inherentemente estables
- pueden diseñarse con fase lineal exacta
- su orden determina la longitud del retardo y la precisión de la respuesta

### 4.3 Implementación en Arduino

Los ejemplos en `arduino_codes/` y en `arduino_codes/librerias/isbFilters` muestran cómo usar una tabla de coeficientes `b[]` y un historial de muestras para calcular la salida.

## 5. Diagrama de Bode

El diagrama de Bode muestra:
- magnitud en dB frente a frecuencia
- fase en grados frente a frecuencia

Para filtros digitales, la frecuencia se normaliza respecto a la frecuencia de muestreo `f_s`.

### 5.1 Magnitud

La ganancia en magnitud se obtiene de `|H(e^{jω})|`, donde `ω` es la frecuencia normalizada en radianes por muestra.

En un filtro pasa-bajo digital, la magnitud es alta en bajas frecuencias y baja en altas frecuencias. En un pasa-alto, es al revés.

### 5.2 Fase

La fase se deriva del argumento de `H(e^{jω})`.
- los filtros FIR simétricos pueden tener fase lineal
- los filtros IIR suelen tener fase no lineal, con mayor distorsión de fase cercana a la frecuencia de corte

## 6. Estabilidad en el plano Z

La estabilidad de un filtro digital se analiza mediante los polos de su función de transferencia.

### 6.1 Región de estabilidad

Para un sistema causal y estable, todos los polos deben estar dentro del círculo unitario:

|z_polo| < 1

Si un polo cae sobre o fuera del círculo unitario, el filtro puede oscilar o diverger.

### 6.2 Polos y ceros

- ceros (`H(z)=0`) definen frecuencias atenuadas
- polos (`denominador=0`) definen frecuencias reforzadas y afectan la estabilidad

Un filtro IIR con polos cerca del círculo unitario ofrece mayor selectividad y mayor Q, pero también mayor riesgo de inestabilidad.

## 7. Relación entre filtros analógicos y digitales

Un filtro analógico de primer orden puede discretizarse mediante técnicas como:
- aproximación bilineal
- método de la transformación impulsional en respuesta

En este repositorio, los ejemplos digitales se diseñan directamente en el dominio discreto y se implementan en Arduino mediante código y filtros por ecuaciones en diferencias.

## 8. Aplicaciones prácticas en el repositorio

### 8.1 Simulación en SimulIDE

Los archivos `circuito_simulide/*.sim1` contienen circuitos para probar filtros digitales y analógicos en un entorno de simulación.

### 8.2 Códigos de Arduino

- `arduino_codes/filtro_pasa_bajo_20hz.ino`: ejemplo de filtro digital en Arduino
- `arduino_codes/filtro_pasa_pajo_50hz.ino`: otro filtro digital implementado en código
- `arduino_codes/filtro_pasa_pajo_iir_biquad/`: implementación IIR de segundo orden

### 8.3 Librería `isbFilters`

La carpeta `arduino_codes/librerias/isbFilters` contiene ejemplos, definiciones y una estructura de filtros que permiten experimentar con FIR/IIR y biquad.

## 9. Consejos prácticos

- use coeficientes calibrados para la frecuencia de muestreo específica
- en Arduino, calcule las operaciones de filtro de forma eficiente para cumplir con los límites de tiempo real
- valide la estabilidad verificando que los polos de filtros IIR queden dentro del círculo unitario
- compare la respuesta en magnitud y fase con diagramas de Bode para entender el comportamiento

## 10. Resumen

- Los filtros analógicos de primer orden RC permiten entender la respuesta básica en magnitud y fase.
- Los filtros digitales FIR son siempre estables y pueden tener fase lineal, mientras que los IIR son más eficientes pero requieren cuidado con la estabilidad.
- La ecuación en diferencias es la base de la implementación digital en Arduino.
- El diagrama de Bode y el plano Z son herramientas fundamentales para analizar la respuesta en frecuencia y estabilidad.

Este tutorial está pensado para usar el repositorio como guía práctica: diseñar, codificar y simular filtros en Arduino y SimulIDE.
