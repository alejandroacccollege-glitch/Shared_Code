#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float v1, v2, v3;
} Vec3;

typedef struct
{
    Vec3 position;   // x, y, z
    Vec3 color;      // red, green, blue
    Vec3 dimensions; // width, height, depth
} Box;
//Ejercicio 1
void createBoxes(Box ***boxesArray, int N)
{                                                    // Es un arreglo por referencia
    Box **array = (Box **) malloc(N * sizeof(Box *)); // Se modifica el arreglo directamente pasado por referencia
    // Ahora hay que llenar el arreglo ,
    // Cada ejemplar de los atributos Box almanecaran posicion. 0 0 0
    // Dimensiones
    //
    int i;
    for (i = 0; i < N; i++)
    {
        // Como entramos en los datos ?
        // Y una vez entrando en los datos como nos movemos?
        *(array + i) = (Box *)calloc(N, sizeof(Box));
        (*(array + i))->dimensions.v1 = 1.0;
        // Como nota se usa un . ya que usar flecha seria en el primero que es un apuntador
        (*(array + i))->dimensions.v2 = 1.0;
        (*(array + i))->dimensions.v3 = 1.0;
    }
    *boxesArray = array;
}
// El parametro a devolver si usa tres asteriscos?
Vec3 ***createCube(int size)
{
    int cols, depth, data; // Filas , columnas y profundidad
    Vec3 ***rows = (Vec3 ***) malloc(size * sizeof(Vec3 **));
    // En este caso deberian de ser tres asteriscos
    // Iterar en el primer bloque creado coon cube

    for (cols = 0; cols < size; cols++)
    {
        // hago la nueva dimension y agrego memoria a caada bloque creado
        *(rows + cols) = (Vec3 **) malloc(size * sizeof(Vec3 *));
        // Volvemos a iterar y en los nuevos le vamos agregar los nuevos bloques , que estaran adentro
        // Dentro de los bloques que estan adetro de los bloques que estaban adentro del bloque rows
        for (depth = 0; depth < size; depth++)
        {
            *((*(rows + cols)) + depth) = (Vec3 *)malloc(size * sizeof(Vec3));
            for (data = 0; data < size; data++)
            {
                (*(*(*(rows + cols) + depth) + data)).v1 = (float)cols;
                (*(*(*(rows + cols) + depth) + data)).v2 = (float)depth;
                (*(*(*(rows + cols) + depth) + data)).v3 = (float)data;
            }
        }
    }
    return rows; // Técnicamente este es un cubo que está guardado en rows
}
// Ejercicio tres , metodo que libera memoria del arreglo tridimensional
// Que va a devolver?
// Que va a recibir?
void freeCube(Vec3 ***cube, int size)
{
    // Deeriamos de liberar cada bloque , desde el bloque que se encuentra en la profundidad , luego el bloque tenga las columnsa
    // y por ultimo el bloque que guarda las filas
    // van a ser tres iteraciones
    int cols, depth;

    for (cols = 0; cols < size; cols++)
    { // Entra en el segundo iterador que son las direcciones que
        // Se guardaron en cada bloque de rows , y entramos a los bloques de cols con una tercera iteración
        for (depth = 0; depth < size; depth++)
        {
            // Liberamos cada boque se encuentra en la profunidad
            free(*(*(cube + cols) + depth));
        }
        free(*(cube + cols));
    }
    free(cube);
}

int main()
{
    Box **boxes = NULL;
    int N = 3;
    createBoxes(&boxes, N);

    int i;
    for (i = 0; i < N; i++)
    {
        printf("Box %d:\n", i);
        printf("  Posicion:    <%.1f, %.1f, %.1f>\n", (*(boxes + i))->position.v1, (*(boxes + i))->position.v2, (*(boxes + i))->position.v3);
        printf("  Color:       <%.1f, %.1f, %.1f>\n", (*(boxes + i))->color.v1, (*(boxes + i))->color.v2, (*(boxes + i))->color.v3);
        printf("  Dimensiones: <%.1f, %.1f, %.1f>\n", (*(boxes + i))->dimensions.v1, (*(boxes + i))->dimensions.v2, (*(boxes + i))->dimensions.v3);
    }

    Vec3 ***cube = createCube(3);

    int layer, row, col;
    int size = 3; // O el tamaño que le hayas asignado al cubo

    for (layer = 0; layer < size; layer++)
    {
        for (row = 0; row < size; row++)
        {
            for (col = 0; col < size; col++)
            {
                printf("Cube[%d][%d][%d] = <%.1f, %.1f, %.1f>\n",
                       layer, row, col,
                       (*(*(*(cube + layer) + row) + col)).v1,
                       (*(*(*(cube + layer) + row) + col)).v2,
                       (*(*(*(cube + layer) + row) + col)).v3);
            }
        }
    }

    freeCube(cube, 3);
    cube = NULL;

    if (cube == NULL)
    {
        printf("Comprobacion: El cubo apunta a NULL, memoria totalmente limpia.\n");
    }

    return 0;
}