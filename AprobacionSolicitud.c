/***Librerias***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define N 100
typedef struct
{
    int nroSolicitud;
    char cedulA[11];
    int montoA;
} aprobacion;
typedef struct
{
    int numeroS;
    char fechaS[11];
    char cedulaS[11];
    int codigoS;
    char fechaIS[11];
    char fechaRS[11];
    int montS;
    char estatuS;
} solicitud;

int leerSolicitudes(solicitud *datos, int *dim);
int leerConfig(int *divisasU,unsigned long *divisas);
void Limpiador(char *cadena);
void aprobarSolicitud(solicitud *datos,int dim,unsigned long divisas,int divisasU);
int verificarSolicitud(unsigned long *limite,int monto);
void guardarAprobacion(unsigned long montoI, unsigned long montoF,aprobacion *vector,int dimv);
void GuardarSolicitud(solicitud *datos, int *dim);
void fecha(char *cad);
void guardarConfig(int divisasU,unsigned long divisas);
int main()
{
    int divisasU,dim;
    unsigned long divisas;
    solicitud datos[N];
    leerConfig(&divisasU,&divisas);
    leerSolicitudes(datos,&dim);
    aprobarSolicitud(datos,dim,divisas,divisasU);
    GuardarSolicitud(datos,&dim);
    return 0;
}
/*Lee el pote the divisas*/
int leerConfig(int *divisasU,unsigned long *divisas)
{
    FILE *entrada;
    entrada=fopen("config.dat","r");
    if(entrada==NULL)
    {
        printf("\n\tERROR, EL ARCHIVO Config.dat NO EXISTE\n\n");
        return EXIT_FAILURE;
    }
    else
    {
        fscanf(entrada,"%d \n",divisasU);
        fscanf(entrada,"%lu",divisas);
        return EXIT_SUCCESS;
    }
    return 0;
}
int leerSolicitudes(solicitud *datos, int *dim)
{

    FILE *entrada;
    int i;

    entrada=(fopen("solicitudes.dat","r"));
    if(entrada==NULL)
    {
        return 1;
    }
    else
    {
        i=0;
        while(!feof(entrada))
        {
            fscanf(entrada,"%d ",&datos[i].numeroS);
            fscanf(entrada,"%10[-0-9] ",datos[i].fechaS);
            Limpiador(datos[i].fechaS);
            fscanf(entrada,"%10[-VE0-9] ",datos[i].cedulaS);
            Limpiador(datos[i].cedulaS);
            fscanf(entrada,"%d ",&datos[i].codigoS);
            fscanf(entrada,"%10[-0-9] ",datos[i].fechaIS);
            Limpiador(datos[i].fechaIS);
            fscanf(entrada,"%10[-0-9] ",datos[i].fechaRS);
            Limpiador(datos[i].fechaRS);
            fscanf(entrada,"%d ",&datos[i].montS);
            fscanf(entrada,"%c\n",&datos[i].estatuS);
            i++;
        }
        *dim=i;
        fclose(entrada);
        return 0;
    }
}
/*Aprobar solicitudes*/
void aprobarSolicitud(solicitud *datos,int dim,unsigned long divisas,int divisasU)
{
    int i=0,j=0,band=0;
    unsigned long limite=divisas;
    aprobacion vector[N];
    while(band==0 && i<dim)
    {
        if(datos[i].estatuS=='P')
        {
            if(verificarSolicitud(&limite,datos[i].montS))
            {
                datos[i].estatuS='A';
                vector[j].nroSolicitud=datos[i].numeroS;
                strcpy(vector[j].cedulA,datos[i].cedulaS);
                vector[j].montoA=datos[i].montS;
                j++;
            }
            else
                band=1;
        }
        i++;
    }
    if(band==0 && i>0)
        printf("\n\tTodas las solicitudes han sido aprobadas correctamente\n\n");
    if(band==1)
        printf("\n\tYa no hay divisas disponibles en el pote\n\n");
    guardarAprobacion(divisas,limite,vector,j);
    guardarConfig(divisasU,limite);
}
/*Actualiza el monto y verifica que el monto sea menor al limite*/
int verificarSolicitud(unsigned long *limite,int monto)
{

    if(monto<=*limite)
    {
        *limite=*limite-monto;
        return 1;
    }
    else
        return 0;
}
/*Guarda la informacion en un archivo*/
void guardarAprobacion(unsigned long montoI, unsigned long montoF,aprobacion *vector,int dimv)
{
    FILE *salida;
    char fech[11];
    int i;
    salida=fopen("aprobacion.dat","a");
    if(salida==NULL)
        printf("\n\tERROR,No se pudo abrir APROBACION.DAT\n");
    else
    {
        fecha(fech);
        fprintf(salida,"Fecha Actual=\t%s\n",fech);
        fprintf(salida,"Monto Inicial=\t%lu\n",montoI);
        fprintf(salida,"Monto Final=\t%lu\n\n",montoF);
        for(i=0; i<dimv; i++)
        {
            if(i==0)
                fprintf(salida,"Nro Solicitud\tCedula\tMonto\n\n");
            fprintf(salida,"%d",vector[i].nroSolicitud);
            fprintf(salida,"%19s\t",vector[i].cedulA);
            fprintf(salida,"%2d\n",vector[i].montoA);
        }
    }
}
/*Guarda las Solicitudes*/
void GuardarSolicitud(solicitud *datos, int *dimS)
{
    int i;
    FILE *salida;

    salida=(fopen("solicitudes.dat","w"));
    for(i=0; i<*dimS; i++)
    {
        fprintf(salida,"%d",datos[i].numeroS);
        fprintf(salida," %s",datos[i].fechaS);
        fprintf(salida," %s",datos[i].cedulaS);
        fprintf(salida," %d",datos[i].codigoS);
        fprintf(salida," %s",datos[i].fechaIS);
        fprintf(salida," %s",datos[i].fechaRS);
        fprintf(salida," %d",datos[i].montS);
        fprintf(salida," %c\n",datos[i].estatuS);
    }
    fclose(salida);
    leerSolicitudes(datos,dimS);
}
void fecha(char *cad)
{
    time_t tiempo;
    struct tm *tmPtr;

    tiempo=time(NULL);
    tmPtr=localtime(&tiempo);
    strftime(cad,80,"%d-%m-%Y",tmPtr);
}
/*Limpia espacios de la cadena*/
void Limpiador(char *cadena)
{
    int lng,i=0,j=0,k;
    char cad[40];

    while (cadena[i]==' ')
        i++;
    lng=strlen(cadena);
    while (cadena[lng-j-1]==' ')
        j++;
    for (k=i; k<lng-j; k++)
        cad[k-i]=cadena[k];
    cad[k-i]='\0';
    strcpy(cadena,cad);
}
void guardarConfig(int divisasU,unsigned long divisas)
{
    FILE *salida;
    salida=fopen("config.dat","w");
    fprintf(salida,"%d\n",divisasU);
    fprintf(salida,"%lu\n",divisas);
    fclose(salida);
}
