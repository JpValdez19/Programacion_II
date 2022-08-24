#include "io/io.h"
#include "string/string.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct Empresa
{
    int idEmpresa;
    String RazonSocial;
} Empresa;

typedef struct Departamento
{
    int idDepartamento;
    String nombre;
    String projecto;
} Departamento;

typedef struct Empleado
{
    int idEmpleado;
    String nombre;
    double sueldo;
} Empleado;

typedef struct Relacion
{
    int idRelación;
    Empresa empresa;
    Departamento departamento;
    Empleado empleado;
} Relacion;

int writeRelacion(Relacion relacion, FILE *stream)
{
    if (stream == 0)
        return -1;

    fprintf(stream, "%i\n"
                    "%i\n"
                    "%s\n"

                    "%i\n"
                    "%s\n"
                    "%s\n"

                    "%i\n"
                    "%s\n"
                    "%lf\n",

            relacion.idRelación,
            relacion.empresa.idEmpresa,
            relacion.empresa.RazonSocial.str,
            relacion.departamento.idDepartamento,
            relacion.departamento.nombre.str,
            relacion.departamento.projecto.str,
            relacion.empleado.idEmpleado,
            relacion.empleado.nombre.str,
            relacion.empleado.sueldo);

    return 1;
}

int inputRelacion(Relacion* relacion){
    input("idRelación: ", evaluarInt(stdin, &relacion->idRelación));
    input("idEmpresa: ", evaluarInt(stdin, &relacion->empresa.idEmpresa));
    input("RazonSocial: ", evaluarString(stdin, &relacion->empresa.RazonSocial));
    input("idDepartamento: ", evaluarInt(stdin, &relacion->departamento.idDepartamento));
    input("nombre: ", evaluarString(stdin, &relacion->departamento.nombre));
    input("projecto: ", evaluarString(stdin, &relacion->departamento.projecto));
    input("idEmpleado: ", evaluarInt(stdin, &relacion->empleado.idEmpleado));
    input("nombre: ", evaluarString(stdin, &relacion->empleado.nombre));
    input("sueldo: ", evaluarDouble(stdin, &relacion->empleado.sueldo));
}

int main(){
    // Sesiones
    int N = 0;
    input("Ingrese el numero de sesiones: ", evaluarInt(stdin, &N) );
    Relacion **dato = (Relacion**)malloc(N * sizeof(Relacion*));

    // Relaciones de cada sesion
    int M = 0;
    input("Ingrese el numero de relaciones: ", evaluarInt(stdin, &M) );
    for(int i = 0; i < N; i++){
        dato[i] = (Relacion*)malloc(M * sizeof(Relacion));
    }

    // Relacion Input
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            inputRelacion(&dato[i][j]);
        }
    }

    // Relacion Output
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            writeRelacion(dato[i][j], stdout);
        }
    }
    
    // Memory free
    {
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                free(dato[i][j].empleado.nombre.str);
                free(dato[i][j].departamento.nombre.str);
                free(dato[i][j].departamento.projecto.str);
                free(dato[i][j].empresa.RazonSocial.str);
            }
            free(dato[i]);
        }
        free(dato);
    }
    return 0;

}