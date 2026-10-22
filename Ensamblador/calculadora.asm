.text

main:
    addi sp, sp, -16 # Se reserva espacio en la pila
    sw   ra, 12(sp) # Se guarda en la pila la dirección de retorno

    addi s0, zero, 0 # selector = 0 
    addi s1, zero, 5 # a = 5      
    addi s2, zero, 3 # b = 3        
    addi s3, zero, 0 # c = 0

    # Aquí se hace la evaluación del switch
    addi t0, zero, 1 # t0 = 1
    beq  s0, t0, case_1 # Se compara "s0" con "t0" para saltar a la
    # etiqueta del caso 1

    addi t0, zero, 2 # t0 = 2
    beq  s0, t0, case_2 # Se compara "s0" con "t0" para saltar a la
    # etiqueta del caso 2

    addi t0, zero, 3 # t0 = 3
    beq  s0, t0, case_3 # Se compara "s0" con "t0" para saltar a la
    # etiqueta del caso 3

    jal  zero, case_default # si no se cumple alguno de los anteriores
    # se salta directamente al caso por defecto

case_1:
    addi a0, s1, 0 # Se guarda el valor de "a" en "a0"
    addi a1, s2, 0 # Se guarda el valor de "b" en "a1"
    # Esto con el fin de usarlos como parámetros para la función   
    jal  ra, suma # Se llama a la función (etiqueta) suma
    addi s3, a0, 0 # El resultado devuelto por "a0" se almmacena en 
    # la variable "c"    
    jal  zero, end_switch # Vendría siendo el equivalente al break
    # en "C"

case_2:
    addi a0, s1, 0 # Se guarda el valor de "a" en "a0"
    addi a1, s2, 0 # Se guarda el valor de "b" en "a1"
    # Esto con el fin de usarlos como parámetros para la función    
    jal  ra, resta # Se llama a la función (etiqueta) resta
    addi s3, a0, 0 # El resultado devuelto por "a0" se almmacena en 
    # la variable "c"     
    jal  zero, end_switch # Vendría siendo el equivalente al break
    # en "C"

case_3:
    addi a0, s1, 0 # Se guarda el valor de "a" en "a0" 
    addi a1, s2, 0 # Se guarda el valor de "b" en "a1"
    # Esto con el fin de usarlos como parámetros para la función 
    jal  ra, multiplica # Se llama a la función (etiqueta) multiplica
    addi s3, a0, 0 # El resultado devuelto por "a" se almmacena en 
    # la variable "c"   
    jal  zero, end_switch # Vendría siendo el equivalente al break
    # en "C"

case_default:
    addi a0, s1, 0 # Se guarda el valor de "a" en "a0"   
    addi a1, s2, 0 # Se guarda el valor de "b" en "a1"
    # Esto con el fin de usarlos como parámetros para la función     
    jal  ra, andBitwise # Se llama a la función (etiqueta) andBitwise
    addi s3, a0, 0 # El resultado devuelto por "a" se almmacena en 
    # la variable "c" 
    jal  zero, end_switch # Vendría siendo el equivalente al break
    # en "C"

end_switch:
    lw   ra, 12(sp) # Se recupera de la pila la dirección de retorno
    # original de la función main
    addi sp, sp, 16 # Se restaura el tamaño original de la pila

    addi a0, zero, 0 # Equivale al "return 0;" en "C"
    jalr zero, 0(ra) #Finaliza el programa al saltar a la 
    # dirección guardada en "ra"

# Implemantación de las funciones
suma:
    add  a0, a0, a1 # "a0" = "a0" + "a1"
    jalr zero, 0(ra) # Toma la dirección almacenada en "ra"
    # resgresando al punto donde fue invocada

resta:
    sub  a0, a0, a1 # "a0" = "a0" - "a1" 
    jalr zero, 0(ra) # Toma la dirección almacenada en "ra"
    # resgresando al punto donde fue invocada 

multiplica:
    mul  a0, a0, a1 # "a0" = "a0" * "a1"
    jalr zero, 0(ra) # Toma la dirección almacenada en "ra"
    # resgresando al punto donde fue invocada 

andBitwise:
    and  a0, a0, a1 # "a0" = "a0" | "a1"
    jalr zero, 0(ra) # Toma la dirección almacenada en "ra"
    # resgresando al punto donde fue invocada