.text

main: 
    addi a0, zero, 6 # m = 6
    addi a1, zero, 6 # n = 6

    jal ra, Potencia #Salta a la etiqueta Potencia
    jalr zero, ra, 0 

Potencia:
    addi t0, zero, 1 # Constante para comparar "n"
    bge a1, t0, else # Hace la comparación
    # n >= 1 para que salte al else si se cumple

if:
    addi a0, zero, 1 # Asigna 1 al requistro de retorno 
    jalr zero, ra, 0 # Se regresa a la dirección de 
    # memoria almacenada en "ra", siendo las instrucciones
    # de Potencia
else:
    addi sp, sp, -16 # Se reserva espacio en la pila para
    # guardar variables y direcciones de retorno locales
    sw ra, 12(sp) # Se guarda en la pila el registro de 
    # retorno "ra", para que no se pierda cuando se haga
    # la llamada recursiva
    sw a0, 8(sp) # Guarda en la pila el valor actual de "m"
    # para usarlo después en la multiplicación
    addi a1, a1, -1 # Decrementa "n" en 1
    jal ra, Potencia # Se llama a la función potencia
    # nuevamente (llamada recursiva)
    lw t1, 8(sp) # Se recupera el valor original de "m"
    # y se carga a un registro temporal
    mul a0, t1, a0 # Se multiplica el valor de "m" que
    # está en el temporal "t1" por el resultado acumulado
    # que se tiene  en "a0"
    lw ra, 12(sp) # Restaura el registro de retorno "ra"
    # original desde la pila
    addi sp, sp, 16 # Se libera el espacio que se había
    # reservado en la pila
    jalr zero, ra, 0 # Retorna al nivel anterior de la
    # función hasta que llega al caso basa y hasta 
    # entonces regresa al main