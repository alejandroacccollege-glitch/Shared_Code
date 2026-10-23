.data

Vector_1: .word 1, 2, 3, 4, 5, 6, 7, 8, 9
# int Vector_1[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
Vector_2: .word -1, 2, -3, 4, -5, 6, -7, 8, -9
# int Vector_2[9] = { -1,2,-3,4,-5,6,-7,8,-9 };
i: .word 0 # int i = 0; 
resultado: .word 0 # int resultado = 0;
# Todo esto se almacena en la RAM

.text

main:
    addi sp, sp, -16 # Se reserva espacio en la pila 
    sw   ra, 12(sp) # Se almacena "ra" en la pila para
    # no perderla

    addi s0, zero, 0 # Se mantiene en "s0" el valor de "i"
    # para poder operar con él dentro de las operativas del
    # procesador
    addi s1, zero, 0 # Se mantiene en "s1" el valor del acumulador
    # del resultado dentro de las operativas del procesador


for:
    addi t0, zero, 9 # Guarda en "t0" el límite del ciclo
    bge  s0, t0, end_for # Se evalua si "i" es mayor o 
    # igual a "9"

    slli t1, s0, 2 # Multiplica el índice por "4" para moverse
    # por el arreglo que es de enteros que valen "4" bytes cada
    # uno

    # Se carga la parte alta de la dirección de memoria de Vector_1 en el registro temporal
    lui  t2, %hi(Vector_1)
    # Se suma la parte baja para completar la dirección base absoluta de Vector_1
    addi t2, t2, %lo(Vector_1)
    
    add  t2, t2, t1  # A lo anterior se le suma el desplazamiento
    # en "t1"
    lw   a0, 0(t2) # Lee el elemento, haciendo que sea el primer
    # argumento de la función

    # Se carga la parte alta de la dirección de memoria de Vector_2 en el registro temporal
    lui  t3, %hi(Vector_2)
    # Se suma la parte baja para completar la dirección base absoluta de Vector_2
    addi t3, t3, %lo(Vector_2)
    
    add  t3, t3, t1 # A lo anterior se le suma el desplazamiento
    # en "t1"
    lw   a1, 0(t3) # Lee el elemento, haciendo que sea el segundo
    # argumento de la función

    # Se calcula la dirección relativa alta (PC-relative) para el salto a la subrutina
    auipc ra, %pcrel_hi(ProductFunction)
    # Se salta a la función guardando la dirección de retorno en "ra" y resolviendo el desplazamiento bajo
    jalr  ra, ra, %pcrel_lo(ProductFunction) # Salta a la función que se encarga
    # de la multiplicación guardando el retorno en "ra"

    add  s1, s1, a0 # Se suma el valor devuelto en "a0"
    # al registro acumulado
    addi s0, s0, 1 # Incrementa el contador del índice "i" en "1"
    
    jal  zero, for # Realiza un salto al inicio del ciclo para
    # volver a evaluar la siguiente iteración

end_for:
    # Se carga la parte alta de la dirección de memoria de la variable global "i"
    lui  t0, %hi(i)
    # Se completa la dirección sumando la parte baja para obtener la referencia en RAM
    addi t0, t0, %lo(i) # Se obtiene la dirección de memoria de la variable global "i"
    sw   s0, 0(t0) # Se escribe su valor final desde "s0"

    # Se carga la parte alta de la dirección de memoria de la variable global "resultado"
    lui  t0, %hi(resultado)
    # Se completa la dirección sumando la parte baja para obtener la referencia en RAM
    addi t0, t0, %lo(resultado) # Se obtiene la dirección de memoria de la variable 
    # global "resultado"
    sw   s1, 0(t0) # Se escribe su valor final desde "s1"

    lw   ra, 12(sp) # Se recupera el "ra" original del main
    addi sp, sp, 16 # Se libera el espacio de la pila

    addi a0, zero, 0 # Esto sería el "return 0;" del main
    jalr zero, 0(ra) # Se salta de regreso usando el registro de retorno
    # ignorando la generación de un nuevo punto de retorno


ProductFunction:
    mul  a0, a0, a1 # "a0" = "a0" * "a1"
    jalr zero, 0(ra) # Se realiza el retorno de la función
    # posterior al punto donde fue llamada