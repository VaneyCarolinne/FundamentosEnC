/***Librerias***/
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/***Definicion de constantes***/
#define N 100
#define D 500
#define S 99999999
/***registros y arreglos de registros***/

typedef struct
{
    char nombres[D];
    int montos[4];
} destinos;
typedef struct
{
    char cedulaD[11];
    char fechaID[11];
    int montoED;
    int viajoD;
} declaracion;
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
typedef struct
{
    char cedula[11];
    char nombres[31];
    int estatus;
    char apellidos[31];
    char correo[41];
    int pregunta;
    char descripcionP[41];
    int monto;
    char respuesta[41];
    char fecha[11];
} registro;
/***Prototipos***/
int menuP();
void registrarse(registro *usuarios, int *dimU,int divisasU);
void fecha(char *cad);
void escVector(registro *usuarios,int dim);
int valida_NombreApellido(char *cad);
int validarcedu(char *cad);
int validar_DescripcionRespuesta(char *cad);
int BuscandoArroba(char *cad);
int validarcorreo(char *cad);
int BuscandoPunto(char *cad);
int BuscandoUsuario(registro *v,int dim,char *cedula);
void ordenarRegistro(registro *v, int dim);
void intercambiar(registro *v1, registro *v2);
int menu_principal();
void pulse_intro();
int leerArchivo(registro *v,int *dim);
void Limpiador(char *cadena);
void LeeNombre(char *name);
void leeApellido(char *lastname);
void leecorreo(char *email);
void leerDescripcion(char *des);
void leerespuesta(char *answer);
int AsignarEstatus(int monto);
void leeyvalidaMonto(int *monto,int limite);
void leecedula(char *cedula);
int leerSolicitudes(solicitud *solicitud, int *dim);
int leerDeclaracion(declaracion *declaracion, int *dim);
/*AGREGADO POR DEY*/
void usuarioRegistrado(registro *usuarios, int n,solicitud *datos,int dimS,destinos *codigos, int dimD,declaracion *campos,int *dimC,unsigned long *divisas);
void hacerpregunta(int opcion);
void impEstatus(char letra);
int listaSolicitud(solicitud *datos,int ns, registro *usuario,int pos);
int menuInterno();
int crearSolicitud(solicitud *datos,int *dimS,registro *usuarios,int pos,destinos *codigos, int dimD);
void validaFecha(char *fecha);
int leediamesanyo(int *dd,int *mm, int *aa);
void convertirFecha(int dd, int mm, int aa, char *fecha);
int comparaFecha(int dd1, int mm1, int aa1,int dd2, int mm2, int aa2);
int diferenciaFechas(int dd1,int mm1,int aa1,int dd2,int mm2,int aa2);
void separaFecha(char *Fecha,int *ddn,int *mmn,int *aan);
int pedirDatos(registro *vector,int pos);
void mostrar(registro *usuarios, int dim);
int buscaSolicitud(solicitud *datos, int dimS, char *fecha, char *cedula);
int leerDestinos(destinos *codigos, int *dimD);
void imprimirDestinos(destinos *codigos, int dim1);
void montoAutorizado(destinos *codigos, int opc, int dias, int *monto,int montoU);
void modificarSolicitud(solicitud *datos,int dimS,registro *usuario, int pos,destinos *codigos,int dimD);
void GuardarSolicitud(solicitud *datos, int *dim);
void cerrarSolicitud(solicitud *datos,int dimS, declaracion *campos, int *dimC,registro *usuarios,int pos,unsigned long *divisas);
int leerConfig(int *divisasU,unsigned long *divisas);
void guardarConfig(int divisasU,unsigned long *divisas);
void guardarDeclaracion(declaracion *campos,int dimC);
void limpiar_buffer();
/*Agregado por Vaney*/
void EstadoCuenta(registro *usuarios, solicitud *solicitudes, declaracion *declaraciones, int dim,int dimS,int dimD);
void solicitud_divisas(registro *usuarios,solicitud *solicitudes,int dim,int dimS);
void leerMesyAno(int *mes, int *ano);
void separaFecha(char *fecha,int *dian,int *mesn,int *anyo);/**/
int diferenciaFechas(int dd1,int mm1,int aa1,int dd2,int mm2,int aa2);/**/
void ordenarfecha(solicitud *v,int dim);
void intercambiarS(solicitud *v1,solicitud *v2);
void Igualdad(solicitud *solicitudes,int dimS);
int DestinoSolicitado(solicitud *solicitudes,int dimS);
void TotalDestinosDias(solicitud *solicitudes,int dimS);
int BuscandoUsuarioS(solicitud *vector, int n,char *cedula);
void ordenarC(solicitud *v,int dim);
int miniMenu();
/***Programa Principal***/
int main()
{
    /*Declaración de variables*/
    int i,opcion,dimU,dimS,dimD,dimC;
    registro usuarios[N];
    solicitud datos[N];
    destinos codigos[N];
    declaracion campos[N];
    int divisasU;
    unsigned long divisas;
    registro user[N];
    solicitud solicitudes[N];
    declaracion declaraciones[N];
    int n,nS,nD,opcionL;

    if(!leerConfig(&divisasU,&divisas) && !leerDestinos(codigos,&dimD))
    {
        leerArchivo(usuarios,&dimU);
        ordenarRegistro(usuarios,dimU);
        leerSolicitudes(datos,&dimS);
        leerDeclaracion(campos,&dimC);
        i=dimU;
        do
        {
            opcion=menu_principal();
            switch(opcion)
            {
            case 1:/*1.REGISTRARSE*/
                registrarse(usuarios,&dimU,divisasU);
                ordenarRegistro(usuarios,dimU);
                pulse_intro();
                break;
            case 2:/*2.USUARIOS REGISTRADO*/
                usuarioRegistrado(usuarios,dimU,datos,dimS,codigos,dimD,campos,&dimC,&divisas);
                guardarConfig(divisasU,&divisas);
                break;
            case 3:/*3.LISTADOS*/
                if(leerArchivo(user,&n))
                {
                    escVector(usuarios,dimU);
                }
                leerArchivo(user,&n);
                leerSolicitudes(solicitudes,&nS);
                leerDeclaracion(declaraciones,&nD);
                do
                {
                    opcionL=miniMenu();
                    switch(opcionL)
                    {
                    case 1:
                        EstadoCuenta(user,solicitudes,declaraciones,n,nS,nD);
                        pulse_intro();
                        break;
                    case 2:
                        solicitud_divisas(user,solicitudes,n,nS);
                        pulse_intro();
                        break;
                    }/*FinSeleccion*/
                }
                while(opcionL!=0);
                break;
            }/*FSeleccionPrincipal*/
        }
        while(opcion!=0);
        if(i<=dimU)
            escVector(usuarios,dimU);
    }
    return 0;
}
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
/*Muestra el menu principal del programa*/
int menu_principal()
{

    int opc;
    system("clear");
    printf("\n\t***Bienvenido al Menu Principal***\n");
    printf("\n\tSeleccionar una de las siguientes opciones: \n");
    do
    {
        printf("\n\t1.REGISTRARSE\n");
        printf("\t2.USUARIOS REGISTRADOS\n");
        printf("\t3.LISTADOS\n");
        printf("\t0.SALIR\n");
        printf("\tIndique su opción: ");
        scanf("%d",&opc);
        printf("\n");
        if(opc<0||opc>3)
        {
            system("clear");
            printf("\n\tOpción Invalida!! por favor seleccione una de las opciones en el rango de [0..3]\n");
        }
    }
    while(opc<0||opc>3);

    return(opc);
}
/*Pulse intro para continuar*/
void pulse_intro()
{
    printf("\n\tPulse <INTRO> para continuar...");
    getchar();
    getchar();
    system("clear");
}
/*Menu de pregunta alternativa*/
int menuP()
{
    int opc;
    do
    {
        printf("\n");
        printf("\tPregunta de seguridad, seleccionar una de las siguientes opciones:\n");
        printf("\t1.Cuál es el nombre de su mascota?\n");
        printf("\t2.Cuál es el nombre de su primera escuela?\n");
        printf("\t3.Cuál es el nombre de su héroe favorito?\n");
        printf("\t4.Cuál es tu pasatiempo favorito?\n");
        printf("\t5.Cuál es el apellido de tu padre?\n");
        printf("\t6.Cuál fue la marca de tu primera bicicleta?\n");
        printf("\t7.Cuál es el nombre de tu equipo favorito?\n");
        printf("\t8.Otro(Escriba la pregunta alternativa)\n");
        printf("\tIndique su opción: ");
        scanf("%d",&opc);
        getchar();
        if(opc<=0||opc>8)
        {
            system("clear");
            printf("\n\tOpción Invalida por favor ingrese una opción en el rango de [1..8]\n");
        }
    }
    while(opc<=0||opc>8);
    return(opc);
}
/*Fecha obtenida del sistema*/
void fecha(char *cad)
{

    time_t tiempo;
    struct tm *tmPtr;

    tiempo=time(NULL);
    tmPtr=localtime(&tiempo);
    strftime(cad,80,"%d-%m-%Y",tmPtr);
}
/*Escribe los datos ingresados en un archivo*/
void escVector(registro *usuario, int dimU)
{

    FILE *usuarios;
    int i;
    usuarios=(fopen("usuarios.dat","w"));
    if(usuarios==NULL)
    {
        printf("\nERROR! al abrir el archivo usuarios.dat\n");
    }
    else
    {
        for(i=0; i<=dimU-1; i++)
        {
            fprintf(usuarios,"%s ",usuario[i].cedula);
            fprintf(usuarios,"%s ",usuario[i].nombres);
            fprintf(usuarios,"%d ",usuario[i].estatus);
            fprintf(usuarios,"%s ",usuario[i].apellidos);
            fprintf(usuarios,"%s ",usuario[i].fecha);
            fprintf(usuarios,"%s ",usuario[i].correo);
            fprintf(usuarios,"%d ",usuario[i].pregunta);
            if(usuario[i].pregunta==8)
                fprintf(usuarios,"%s ",usuario[i].descripcionP);
            else
                fprintf(usuarios,"# ");
            fprintf(usuarios,"%d ",usuario[i].monto);
            fprintf(usuarios,"%s\n",usuario[i].respuesta);
        }
        fclose(usuarios);
    }
}
/*Validando correo electronico*/
int validarcorreo(char *cad)
{

    int i,longitud,arroba,punto,band,aux;

    band=0;
    longitud=strlen(cad);
    arroba=BuscandoArroba(cad);
    aux=0;
    punto=BuscandoPunto(cad);
    if(punto==-1)
    {
        return(-1);
    }
    if(arroba==0)
    {
        return(-1);
    }
    if(arroba!=-1)
    {
        for(i=0; i<arroba; i++)
        {
            if(!isalnum(cad[i])&&!(cad[i]=='.'||cad[i]=='-'||cad[i]=='_')&&aux==0)
            {
                band=-1;/*es otra cosa*/
                aux=1;
            }
            else
            {
                if(aux==0)
                {
                    band=0;
                }
            }/*fsi*/
        }/*ffor*/
        punto=BuscandoPunto(cad);
        if(cad[arroba+1]=='.'&&aux==0)
        {
            band=-1;
            aux=1;
        }
        else
        {
            if(aux==0)
            {
                band=0;
            }
        }

        for(i=arroba+1; i<punto; i++)
        {
            if(!isalpha(cad[i]))
            {
                return(-1);
                band=-1;/*es otra cosa*/
            }/*fsi*/
        }/*ffor*/
        for(i=punto+1; i<longitud; i++)
        {
            if(!isalpha(cad[i]))
            {
                return(-1);/*es otra cosa*/
            }
        }/*ffor*/
        if(punto==longitud-1)
        {
            return(-1);
        }

    }
    else
    {
        band=-1;
    }/*fsigrande*/
    return(band);
}
/*Buscando arroba:*/
int BuscandoArroba(char *cad)
{

    int i,longitud,band,pos,aux;

    aux=0;
    band=0;
    longitud=strlen(cad);

    for(i=0; i<longitud; i++)
    {
        if(cad[i]=='@'&&aux==0)
        {
            pos=i;/*posicion donde esta el arroba*/
            aux=1;
        }
        else
        {
            band++;
        }
    }
    if(band>=longitud&&aux==0)
    {
        pos=-1;/*no hay arrobas en la cadena*/
        aux=1;
    }
    return(pos);
}
/*Buscando un punto en lugar que debe ir:*/
int BuscandoPunto(char *cad)
{

    int i,longitud,j,aux,pos;

    aux=0;
    longitud=strlen(cad);
    j=BuscandoArroba(cad);

    for(i=j; i<longitud; i++)
    {
        if(cad[i]=='.'&&aux==0)
        {
            pos=i;/*posicion donde esta el punto*/
            aux=1;
        }
    }

    if(aux==0)
    {
        pos=-1;/*no hay puntos en la cadena*/
    }
    return(pos);
}
/*Valida nombres y apellidos*/
int valida_NombreApellido(char *cad)
{

    int i,longitud,band,aux;

    aux=0;
    longitud=strlen(cad);

    for(i=0; i<longitud; i++)
    {

        if(!isalpha(cad[i])&&!(cad[i]==' '))
        {
            band=1; /*es otra cosa*/
            aux=1;
        }
        else
        {
            if(aux!=1)
            {
                band=0;
            }
        }
    }
    return(band);
}
/*Valida Cedula*/
int validarcedu(char *cad)
{

    int i, longitud,band,aux;
    aux=0;
    longitud=strlen(cad);

    if((cad[0]=='V'||cad[0]=='E')&&(cad[1]=='-'))
    {
        band=0;
        aux=1;
    }
    else
    {
        if(aux!=1)
        {
            band=1; /*es otra cosa*/
        }
    }
    if(band==0)
    {
        for(i=2; i<longitud; i++)
        {
            if(!isdigit(cad[i]))
            {
                band=1;/*es otra cosa*/
                aux=1;
            }
        }
        if(aux!=1)
        {
            band=0;
        }
    }
    return(band);
}

/*Valida descripcion y respuesta*/
int validar_DescripcionRespuesta(char *cad)
{

    int i, longitud;
    int band, aux;

    longitud=strlen(cad);

    for(i=0; i<longitud; i++)
    {
        if(!isalnum(cad[i])&&!(cad[i]==' '))
        {
            band=1;/*es otra cosa*/
            aux=1;/*entro*/
        }
        else
        {
            if(aux!=1)
            {
                band=0;
            }
        }
    }
    return(band);
}
/*Buscando usuario en el vector*/
int BuscandoUsuario(registro *v, int dim, char *cedula)
{

    int centro, inf, sup;

    inf=0;
    sup=dim;

    while(inf<=sup)
    {
        centro=(sup+inf)/2;
        if(strcmp(v[centro].cedula,cedula)==0)
        {
            return(centro);
        }
        else
        {
            if(strcmp(cedula,v[centro].cedula)<0)
            {
                sup=centro-1;
            }
            else
            {
                inf=centro+1;
            }
        }
    }/*fmientras*/
    return(-1);

}
/*Ordenar un vector por cedula de identidad*/
void ordenarRegistro(registro *v,int dim)
{

    int i,j;
    for(i=0; i<=dim; i++)
    {
        for(j=i+1; j<=dim-1; j++)
        {
            if(strcmp(v[i].cedula,v[j].cedula)>0)
            {
                intercambiar(&v[i],&v[j]);
            }/*fsi*/
        }/*fforpequeño*/
    }/*fforgrande*/
}
void intercambiar(registro *v1,registro *v2)
{

    registro temp;

    strcpy(temp.cedula,v1->cedula);
    strcpy(v1->cedula,v2->cedula);
    strcpy(v2->cedula,temp.cedula);

    strcpy(temp.nombres,v1->nombres);
    strcpy(v1->nombres,v2->nombres);
    strcpy(v2->nombres,temp.nombres);

    temp.estatus=v1->estatus;
    v1->estatus=v2->estatus;
    v2->estatus=temp.estatus;

    strcpy(temp.apellidos,v1->apellidos);
    strcpy(v1->apellidos,v2->apellidos);
    strcpy(v2->apellidos,temp.apellidos);

    strcpy(temp.fecha,v1->fecha);
    strcpy(v1->fecha,v2->fecha);
    strcpy(v2->fecha,temp.fecha);

    strcpy(temp.correo,v1->correo);
    strcpy(v1->correo,v2->correo);
    strcpy(v2->correo,temp.correo);

    temp.pregunta=v1->pregunta;
    v1->pregunta=v2->pregunta;
    v2->pregunta=temp.pregunta;

    strcpy(temp.descripcionP,v1->descripcionP);
    strcpy(v1->descripcionP,v2->descripcionP);
    strcpy(v2->descripcionP,temp.descripcionP);

    temp.monto=v1->monto;
    v1->monto=v2->monto;
    v2->monto=temp.monto;

    strcpy(temp.respuesta,v1->respuesta);
    strcpy(v1->respuesta,v2->respuesta);
    strcpy(v2->respuesta,temp.respuesta);
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
/*lee los datos del archivo*/
int leerArchivo(registro *usuario, int *dim)
{

    FILE *entrada;
    int i;

    entrada=(fopen("usuarios.dat","r"));
    if(entrada==NULL)
    {
        return 1;
    }
    else
    {
        i=0;
        while(!feof(entrada))
        {
            fscanf(entrada,"%10[-VE0-9] ",usuario[i].cedula);
            fscanf(entrada,"%30[a-zA-Z ] ",usuario[i].nombres);
            Limpiador(usuario[i].nombres);
            fscanf(entrada,"%d",&usuario[i].estatus);
            fscanf(entrada,"%30[a-zA-Z ] ",usuario[i].apellidos);
            Limpiador(usuario[i].apellidos);
            fscanf(entrada,"%10[0-9-] ",usuario[i].fecha);
            fscanf(entrada,"%40s ",usuario[i].correo);
            fscanf(entrada,"%d ",&usuario[i].pregunta);
            fscanf(entrada,"%40[^-0-9] ",usuario[i].descripcionP);
            Limpiador(usuario[i].descripcionP);
            fscanf(entrada,"%d ",&usuario[i].monto);
            fscanf(entrada,"%40[^\n]\n",usuario[i].respuesta);
            Limpiador(usuario[i].respuesta);
            i++;
        }
        *dim=i;
        fclose(entrada);
        return 0;
    }
}
/*Para el registro*/
/*Leyendo nombre*/
void LeeNombre(char *name)
{

    int band;
    band=0;
    do
    {
        printf("\n\tNombres: ");
        scanf(" %30[^\n]s",name);
        Limpiador(name);
        band=valida_NombreApellido(name);
        if(band==1)
        {
            printf("\n\tNOMBRE INVALIDO!!\n");
        }
    }
    while(band==1);
}
/*leyendo apellido*/
void leeApellido(char *lastname)
{

    int band;
    band=0;
    do
    {
        printf("\n\tApellidos: ");
        scanf(" %30[^\n]s",lastname);
        Limpiador(lastname);
        band=valida_NombreApellido(lastname);
        if(band==1)
        {
            printf("\n\tAPELLIDO INVALIDO!!\n");
        }
    }
    while(band==1);
}
/*lee correo*/
void leecorreo(char *email)
{

    int band;

    do
    {
        printf("\n\tCorreo electronico: ");
        scanf(" %40[^\n]s",email);
        Limpiador(email);
        band=validarcorreo(email);
        if(band==-1)
        {
            printf("\n\tCORREO INVALIDO!!\n");
        }
    }
    while(band==-1);
}

/*Lee respuesta secreta*/
void leerespuesta(char *answer)
{

    int band;

    do
    {
        printf("\n\tRespuesta secreta(Solo se permiten letras y números): ");
        scanf(" %40[^\n]s",answer);
        Limpiador(answer);
        band=validar_DescripcionRespuesta(answer);
        if(band==1)
        {
            printf("\n\tIngrese solo caracteres validos POR FAVOR\n");
        }
    }
    while(band==1);
}

/*lee y valida la descripcion en caso de q' la opcion sea 8*/
void leerDescripcion(char *des)
{

    int band;

    do
    {
        printf("\n\tEscriba la pregunta alternativa(Solo se permiten letras y números): ");
        scanf("%40[^\n]s",des);
        Limpiador(des);
        band=validar_DescripcionRespuesta(des);
        if(band==1)
        {
            printf("\n\tIngrese solo caracteres validos POR FAVOR\n");
        }
    }
    while(band==1);
}

/*Asigna monto*/
void leeyvalidaMonto(int *monto,int limite)
{
    *monto=limite;
}
/*Asignando estatus*/
int AsignarEstatus(int monto)
{

    int estatus;

    if(monto>0)
    {
        estatus=1;/*solvente*/
    }
    if(monto<0)
    {
        estatus=2;/*moroso*/
    }
    return(estatus);
}
/*Lee cedula*/
void leecedula(char *cedula)
{

    int band;

    do
    {
        printf("\n\tCedula de Identidad: ");
        scanf(" %10[^\n]s",cedula);
        Limpiador(cedula);
        band=validarcedu(cedula);
        if(band==1)
        {
            printf("\n\tCEDULA INVALIDAD!!\n");
        }
    }
    while(band==1);
}
/*registro de datos*/
void registrarse(registro *usuarios, int *n, int divisasU)
{

    int i=0;
    char caracter[3]="#\0";
    char cedula[11];
    int clave;

    i=*n;
    if(*n<=N)
    {
        printf("\tIngrese los siguientes datos:\n");
        leecedula(cedula);
        clave=BuscandoUsuario(usuarios,*n,cedula);
        /*Sino existe se registra el nuevo usuario*/
        if(clave==-1) /*ingresando datos*/
        {
            strcpy(usuarios[i].cedula,cedula);
            /*Ingresa los datos faltantes:*/
            LeeNombre(usuarios[i].nombres);
            leeApellido(usuarios[i].apellidos);
            leecorreo(usuarios[i].correo);
            usuarios[i].pregunta=menuP();
            if(usuarios[i].pregunta==8)
            {
                leerDescripcion(usuarios[i].descripcionP);
            }
            else
            {
                strcpy(usuarios[i].descripcionP,caracter);
            }
            Limpiador(usuarios[i].descripcionP);
            leerespuesta(usuarios[i].respuesta);
            leeyvalidaMonto(&usuarios[i].monto,divisasU);
            usuarios[i].estatus=AsignarEstatus(usuarios[i].monto);
            fecha(usuarios[i].fecha);
            Limpiador(usuarios[i].fecha);
            *n=i+1;
            printf("\n\tUsuario Registrado %d con EXITO!!\n",i+1);
        }
        else /*el usuario está en memoria*/
            printf("\n\tEsté Usuario ya está registrado\n");
        /*fsiLecturadeDatos*/
    }/*fsiGRANDE*/
}
/*PARTE DEY*/
/*usuario registrado*/
/***Modificado***/
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
            datos[i].estatuS=toupper(datos[i].estatuS);
            i++;
        }
        *dim=i;
        fclose(entrada);
        return 0;
    }
}
/***Modificado***/
int leerDeclaracion(declaracion *campos, int *dim)
{

    FILE *entrada;
    int i;

    entrada=(fopen("declaracion.dat","r"));
    if(entrada==NULL)
    {
        return 1;
    }
    else
    {

        i=0;
        while(!feof(entrada))
        {
            fscanf(entrada,"%10[-VE0-9]",campos[i].cedulaD);
            Limpiador(campos[i].cedulaD);
            fscanf(entrada," %10[-0-9]",campos[i].fechaID);
            Limpiador(campos[i].fechaID);
            fscanf(entrada,"%d",&campos[i].montoED);
            fscanf(entrada,"%d\n",&campos[i].viajoD);
            i++;
        }
        *dim=i;
        fclose(entrada);
        return 0;
    }

}
void usuarioRegistrado(registro *usuarios, int dimU, solicitud *datos,int dimS, destinos *codigos, int dimD,declaracion *campos, int *dimC,unsigned long *divisas)
{
    char cedula[11],ultimaS;
    int pos,opc;

    leecedula(cedula);
    if(BuscandoUsuario(usuarios,dimU,cedula)==-1)/*Buscando la posicion del usuario*/
    {
        printf("\tUSUARIO NO REGISTRADO\n");
        pulse_intro();
    }
    else
    {
        pos=BuscandoUsuario(usuarios,dimU,cedula);
        if(pedirDatos(usuarios,pos))
        {
            do
            {
                ultimaS=listaSolicitud(datos,dimS,usuarios,pos);
                opc=menuInterno();
                switch(opc)
                {
                case 1:
                    if((usuarios[pos].estatus==1) && (ultimaS=='C'|| ultimaS==' ') && (usuarios[pos].monto>0))
                    {
                        crearSolicitud(datos,&dimS,usuarios, pos,codigos,dimD);
                    }
                    else
                    {
                        printf("\tNo posee los requisitos necesarios para crear una solicitud\n\n");
                        pulse_intro();
                    }
                    break;
                case 2:
                    if((usuarios[pos].estatus==1) && ultimaS=='P'&& (usuarios[pos].monto>0))
                    {
                        modificarSolicitud(datos,dimS,usuarios,pos,codigos,dimD);
                    }
                    else
                    {
                        printf("\tNo posee los requisitos necesarios para modificar una solicitud\n\n");
                        pulse_intro();
                    }
                    break;
                case 3:
                    if(ultimaS!=' ')
                        cerrarSolicitud(datos,dimS,campos,dimC,usuarios,pos,divisas);
                    else
                        printf("\n\tUsted no posee solicitudes\n\n"),pulse_intro();
                    break;
                case 4:
                    system("clear");
                    break;
                default:
                {
                    printf("\tERROR, Opcion incorrecta ingrese una opcion del menu\n\n");
                    pulse_intro();
                }
                }
            }
            while(opc!=4);
        }
    }
}
int pedirDatos(registro *vector,int pos)
{
    char correo[41], resp[41];
    leecorreo(correo);
    if(strcmp(correo,vector[pos].correo)!=0)
    {
        printf("\n\tCORREO INCORRECTO\n\n");
        pulse_intro();
    }
    else
    {
        printf("\n");
        hacerpregunta(vector[pos].pregunta);
        if(vector[pos].pregunta==8)
        {
            printf("(%s)?: ",vector[pos].descripcionP);
        }
        scanf("%s",resp);
        printf("\n");
        if(strcmp(resp,vector[pos].respuesta)!=0)
        {
            printf("\n\tRESPUESTA INCORRECTA\n\n");
            pulse_intro();
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
/*hacer pregunta*/
void hacerpregunta(int opc)
{
    switch(opc)
    {
    case 1:
        printf("\tCual es el nombre de su mascota?: ");
        break;
    case 2:
        printf("\tCual es el nombre de su primera escuela?: ");
        break;
    case 3:
        printf("\tCual es el nombre de su heroe favorito?: ");
        break;
    case 4:
        printf("\tCual es tu pasatiempo favorito?: ");
        break;
    case 5:
        printf("\tCual es el apellido de tu padre?: ");
        break;
    case 6:
        printf("\tCual fue la marca de tu primera bicicleta?: ");
        break;
    case 7:
        printf("\tCual es el nombre de tu equipo favorito?: ");
        break;
    case 8:
        printf("\tOtro ");
        break;
    }
}
int listaSolicitud(solicitud *datos, int ns, registro *usuario,int pos)
{

    int band,i;
    char ultima;
    system("clear");
    band=0, ultima=' ';
    printf("\tCedula: %s\tNombres: %s\tApellidos: %s\n",usuario[pos].cedula,usuario[pos].nombres,usuario[pos].apellidos);
    for(i=0; i<=ns; i++)
    {
        if(strcmp(datos[i].cedulaS,usuario[pos].cedula)==0)
        {
            if(band==0)
            {
                printf("\tNumero de Solicitud   Fecha de solicitud   Estatus\t\tMonto Autorizado\n");
                band=1;
            }
            printf("\t%d%39s   ",datos[i].numeroS,datos[i].fechaS);
            impEstatus(datos[i].estatuS);
            printf("\t%24d\n",datos[i].montS);
            ultima=datos[i].estatuS;
            printf("\tultimaS:(%c)\n",ultima);
        }
    }
    if(band==0)
        printf("\tUsted no tiene solicitudes anteriores\n");
    printf("\n");
    return ultima;
}
void impEstatus(char letra)
{
	letra=toupper(letra);
    if(letra=='P')
        printf("Procesada");
    else if(letra=='A')
        printf("Aprobada");
    else if(letra=='C')
        printf("Cerrada");
}
/*Procedimiento Menu*/
int menuInterno()
{
    int opc;
    printf("\t1. Crear una nueva solicitud.\n");
    printf("\t2. Modificar una solicitud.\n");
    printf("\t3. Cerrar solicitud.\n");
    printf("\t4. Retornar al inicio.\n");
    printf("\tIndique su opcion: \t");
    scanf("%d",&opc);
    printf("\n");
    return(opc);
}
/*Crear Solicitud*/
int crearSolicitud(solicitud *datos,int *dimS,registro *usuarios,int pos, destinos *codigos, int dimD)
{
    char fechaIda[11], fechaRegreso[11],fechaSolicitud[11],resp='\0';
    int ddI,mmI,aaI,ddS,mmS,aaS,ddR,mmR,aaR,dias,opc,monto,i=0;

    system("clear");
    if(*dimS<=S)
    {
        fecha(fechaSolicitud);
        separaFecha(fechaSolicitud,&ddS,&mmS,&aaS);
        printf("\tIngrese la siguiente informacion:\n\n");
        do
        {
            printf("\tFecha de ida del viaje:\n");
            validaFecha(fechaIda);
            separaFecha(fechaIda,&ddI,&mmI,&aaI);
            dias=diferenciaFechas(ddS,mmS,aaS,ddI,mmI,aaI);
            if(dias<=14 || dias>=30)
            {
                printf("\tLa fecha de ida debe ser posterior a la fecha actual \n\ten un minimo de 15 dias y en un maximo de 30 dias\n");
                printf("\tFecha actual= %s\n",fechaSolicitud);
            }
        }
        while(dias<=14 || dias>=30);
        do
        {
            printf("\tFecha de Regreso del viaje:\n");
            validaFecha(fechaRegreso);
            separaFecha(fechaRegreso,&ddR,&mmR,&aaR);
            if(comparaFecha(ddI,mmI,aaI,ddR,mmR,aaR)==1)
            {
                printf("\tLa fecha de Regreso debe ser posterio o igual a la fecha de ida\n");
                printf("\tFecha de Ida= %.2d-%.2d-%d\n",ddI,mmI,aaI);
            }
        }
        while(comparaFecha(ddI,mmI,aaI,ddR,mmR,aaR)==1);
        dias=diferenciaFechas(ddI,mmI,aaI,ddR,mmR,aaR);
        printf("diferencia de dias= %d\n",dias);
        do
        {
            system("clear");
            printf("\tIngrese el codigo de destino de la siguiente lista\n\n");
            imprimirDestinos(codigos,dimD);
            printf("\n\tIndique su Opcion: "),scanf("%d",&opc);
        }
        while(opc<1||opc>dimD);
        montoAutorizado(codigos,opc,dias,&monto,usuarios[pos].monto);
        do
        {
            printf("\tIngrese 'G' para guardar o 'S' para salir y no guardar: \n\tIndique su opcion: ");
            scanf("%*c%c",&resp);
            resp=toupper(resp);
            if(resp!='G' && resp!='S')
                printf("\tSolo puede ingresar 'G' o 'S'\n");
        }
        while(resp!='G' && resp!='S');
        if(resp=='G')
        {
            i=*dimS;
            datos[i].numeroS=i+1;
            strcpy(datos[i].fechaS,fechaSolicitud);
            strcpy(datos[i].cedulaS,usuarios[pos].cedula);
            datos[i].codigoS=opc;
            strcpy(datos[i].fechaIS,fechaIda);
            strcpy(datos[i].fechaRS,fechaRegreso);
            datos[i].montS=monto;
            datos[i].estatuS='P';
            *dimS=i+1;
            GuardarSolicitud(datos,dimS);
        }
    }
    else
        printf("\n\tEl numero de solicitudes llego a su limite\n\n");
    pulse_intro();

    return 0;
}
void validaFecha(char *fecha)
{
    int dd,mm,aa,band=0;
    do
    {
        band=leediamesanyo(&dd,&mm,&aa);
    }
    while(!band);
    convertirFecha(dd,mm,aa,fecha);
}
/*lee y valida la lectura de enteros dias, mes y año*/
int leediamesanyo(int *dd,int *mm, int *aa)
{
    int bisiesto=0, valida=0;
    do
    {
        printf("\tNro. Dia: ");							/*Lee y valida numero de dia mayor que 0 y menor que 32*/
        scanf("%d",dd);
    }
    while(*dd<=0|| *dd>=32);
    do
    {
        printf("\tNro. Mes: ");							/*Lee y valida numero de mes mayor que 0 y menor que 12*/
        scanf("%d",mm);
    }
    while(*mm<=0|| *mm>=13);
    do
    {
        printf("\tNro. Año: ");								/*Lee y valida numero de año mayor que 2000*/
        scanf("%d",aa);
        if(*aa<2014)
            printf("\tIngrese un año posterior al año actual\n\n");
    }
    while(*aa<2014);
    if((*aa%4==0 && *aa%100!=0) || (*aa%400==0))		/*se verifica si el año es bisiesto*/
        bisiesto = 1;
    if(*mm==1 || *mm==3 || *mm==5 || *mm==7 || *mm==8 || *mm==10 || *mm==12)
        valida=1;
    else 												/*Validando si la fecha es valida*/
    {
        if(*mm==2 && *dd<30 && bisiesto)
            valida=1;
        else if(*mm==2 && *dd<29 && !bisiesto)
            valida=1;
        else if(*mm!=2 && *dd<31)
            valida=1;
        else
            printf("\n\tFecha no valida\n"),valida=0;
    }
    return valida;
}
/*Convierte una secuencia de enteros dia mes y año en una cadena dia-mes-año*/
void convertirFecha(int dd, int mm, int aa, char *fecha)
{
    char barra[1],ddc[3],mmc[3],aac[5];
    sprintf(ddc,"%.2d",dd);
    sprintf(mmc,"%.2d",mm);
    sprintf(aac,"%d",aa);	/*se convierte numeros enteros en cadenas*/
    strcpy(fecha,ddc);
    strcpy(barra,"-");		/*se copia el dia en la cadena fecha*/
    strcat(fecha,barra);
    strcpy(fecha,fecha);	/*se concatena la fecha con la barra y se copia sobre fecha*/
    strcat(fecha,mmc);
    strcat(fecha,barra);	/*se concatena la fecha con el mes y la barra*/
    strcpy(fecha,fecha);
    strcat(fecha,aac);		/*se copia fecha sobre fecha y se concatena con el año*/
}
/* Función comparaFecha, devuelve:
   -1 si fecha1 < fecha2,0 si fecha1 = fecha2,1 si fecha1 > fecha2 */
int comparaFecha(int dd1, int mm1, int aa1,int dd2, int mm2, int aa2)
{
    int val;

    if(aa1<aa2)						/*Si el año de fecha1 es menor que fecha2*/
        val=-1;
    else if(aa1>aa2)				/*si el año de fecha1 es menor*/
        val=1;
    else
    {
        if(mm1<mm2)					/*si el mes de fecha1 es mayor*/
            val=-1;
        else if (mm1>mm2)			/*si el mes de fecha 1 es menor*/
            val=1;
        else
        {
            if(dd1<dd2)				/*si el dia de fecha 1 es mayor*/
                val=-1;
            else if(dd1>dd2)		/*si el dia de fecha 1 es menor*/
                val=1;
            else 					/*entonces las fechas son iguales*/
                val=0;
        }
    }
    return val;
}
/*Devuelve el numero de dias que hay de una fecha a otra*/
int diferenciaFechas(int dd1,int mm1,int aa1,int dd2,int mm2,int aa2)
{
    int cont=0,bisiesto,ultdia;

    if((aa1%4==0 && aa1%100!=0) || (aa1%400==0))			/*verifica si el año es biciesto*/
        bisiesto=1;
    switch(mm1) 											/*seleccion para saber el ultimo dia del mes1*/
    {
    case 2:
        if(bisiesto==1)
            ultdia=29;
        else
            ultdia=28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        ultdia=30;
        break;
    default:
        ultdia=31;
    }/*Fin Seleccion*/
    while(aa1<aa2 || ((aa1==aa2)&&(mm1<mm2)) || ((aa1==aa2)&&(mm1==mm2)&& (dd1<dd2))) /*mientras*/
    {
        if(dd1==ultdia)					/*si el dia es igual que el ultimo dia del mes*/
        {
            dd1=0,mm1++;				/*se reinicia el dia en 0 y a mes se le suma 1*/
            switch(mm1) 				/*se vuelve a calcular el ultimo dia del mes*/
            {
            case 2:
                if(bisiesto==1)
                    ultdia=29;
                else
                    ultdia=28;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                ultdia=30;
                break;
            default:
                ultdia=31;
            }/*Fin Seleccion*/
        }/*Fin si*/
        if(mm1>12)						/*si el mes es mayor que 12*/
        {
            mm1=1;
            aa1++;				/*se reinicia el mes en 1 y al año se le suma 1*/
            if((aa1%4==0 && aa1%100!=0) || (aa1%400==0))
                bisiesto=1;					/*se vuelve a calcular si el año es bisiesto*/
        }/*Fin Si*/
        dd1++;
        cont++;
    }/*Fin del Mientras*/

    return (cont); /*se retorna la cantidad de dias entre la fecha1 y la fecha2*/
}
void separaFecha(char *fecha,int *dian,int *mesn,int *anyo)
{
    char dia[3]="\0",mes[3]="\0",any[5]="\0",barra[2]="-\0";
    strncpy(dia,fecha,2);							/*copiando sobre dia los primeros 2 caracteres*/
    *dian=atoi(dia);									/*transformando la cadena dia en entero*/
    strncat(mes,strpbrk(fecha,barra),3);			/*copiando sobre mes los primeros 3 caracteres desde barra*/
    *mesn=abs(atoi(mes));							/*tranformando la cadena mes en un entero con valor absoluto para eliminar la barra*/
    strcpy(any,strrchr(fecha,'-'));				/*copiando en año la fecha hasta '-' buscando desde el final*/
    *anyo=abs(atoi(any));								/*tranformando la cadena año en un entero con valor absoluto para eliminar la barra*/
}
int buscaSolicitud(solicitud *datos, int dim, char *fecha, char *cedula)
{
    int i;
    for(i=0; i<=dim; i++)
    {
        if (strcmp(fecha,datos[i].fechaIS)==0 && strcmp(datos[i].cedulaS,cedula)==0)
        {
            system("clear");
            printf("\tDATOS DE SOLICITUD\n\n");
            printf("\tN° de Solicitud = \t%d\n",datos[i].numeroS);
            printf("\tFecha de Solicitud = \t%s\n",datos[i].fechaS);
            printf("\tCodigo del Destino = \t%d\n",datos[i].codigoS);
            printf("\tFecha de Ida = \t\t%s\n",datos[i].fechaIS);
            printf("\tFecha de Regreso = \t%s\n",datos[i].fechaRS);
            printf("\tMonto Autorizado = \t%d\n\tEstatus = \t\t",datos[i].montS);
            impEstatus(datos[i].estatuS);
            printf("\n\n");
            return i;
        }
    }
    return -1;
}
int leerDestinos(destinos *codigos, int *dimD)
{
    int i=0,j;
    FILE *entrada;
    entrada=fopen("destinos.dat","r");
    if(entrada==NULL)
    {
        printf("\tERROR. destinos.dat no existe\n");
        return EXIT_FAILURE;
    }
    else
    {
        while(!feof(entrada))
        {
            fscanf(entrada,"\t%d\n",&i);
            fscanf(entrada,"%[^0-9\n]",codigos[i-1].nombres);
            for(j=0; j<3; j++)
            {
                fscanf(entrada,"%*d %d\n",&codigos[i-1].montos[j]);
            }
        }
        *dimD=i;
        return EXIT_SUCCESS;
    }
}
void imprimirDestinos(destinos *codigos, int dimD)
{
    int i;
    for(i=0; i<dimD; i++)
    {
        printf("\tOpcion %d.\n",i+1);
        printf("\t%s\n",codigos[i].nombres);
    }
}
void montoAutorizado(destinos *codigos, int opc,int dias, int *monto,int montoU)
{
    int num;
    switch(dias)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        num=codigos[opc-1].montos[0];
        printf("\tDestino[%d]\tMonto Registrado por viaje =%d\n",opc,num);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        num=codigos[opc-1].montos[1];
        printf("\tDestino[%d]\tMonto Registrado por viaje =%d\n",opc,num);
        break;
    default:
        num=codigos[opc-1].montos[2];
        printf("\tDestino[%d]\tMonto Registrado por viaje =%d\n",opc,num);
    }
    if(montoU>=num)
    {
        *monto=num;
        printf("\tMonto Aprobado=%d\n",*monto);
    }
    else
    {
        *monto=montoU;
        printf("\tMonto Aprobado=%d\n",*monto);
    }
}
void modificarSolicitud(solicitud *datos, int dimS,registro *usuarios, int pos, destinos *codigos,int dimD)
{
    int posS,ddI,mmI,aaI,ddS,mmS,aaS,ddR,mmR,aaR,dias,opc,monto;
    char fechaIda[11],fechaRegreso[11],fechaActual[11],resp='\0';

    printf("\tFecha de ida del viaje:\n"),validaFecha(fechaIda);
    posS=buscaSolicitud(datos,dimS,fechaIda,usuarios[pos].cedula);
    if(posS!=-1)
    {
        fecha(fechaActual);
        separaFecha(fechaActual,&ddS,&mmS,&aaS);
        printf("\tModificando solicitud: pos=%d\n\n",posS);
        do
        {
            printf("\tFecha de ida del viaje:\n");
            validaFecha(fechaIda);
            separaFecha(fechaIda,&ddI,&mmI,&aaI);
            dias=diferenciaFechas(ddS,mmS,aaS,ddI,mmI,aaI);
            if(dias<=14 || dias>=30)
            {
                printf("\tLa fecha de ida debe ser posterior a la fecha actual \n\ten un minimo de 15 dias y en un maximo de 30 dias\n");
                printf("\tFecha actual= %s\n",fechaActual);
            }
        }
        while(dias<=14 || dias>=30);
        do
        {
            printf("\tFecha de Regreso del viaje:\n");
            validaFecha(fechaRegreso);
            separaFecha(fechaRegreso,&ddR,&mmR,&aaR);
            if(comparaFecha(ddI,mmI,aaI,ddR,mmR,aaR)==1)
            {
                printf("\tLa fecha de Regreso debe ser posterio o igual a la fecha de ida\n"),printf("\tFecha de Ida= %.2d-%.2d-%d\n",ddI,mmI,aaI);
            }
        }
        while(comparaFecha(ddI,mmI,aaI,ddR,mmR,aaR)==1);
        dias=diferenciaFechas(ddI,mmI,aaI,ddR,mmR,aaR);
        printf("diferencia de dias= %d\n",dias);
        do
        {
            system("clear");
            printf("\tIngrese el codigo de destino de la siguiente lista\n\n");
            imprimirDestinos(codigos,dimD);
            printf("\tIndique su opcion: ");
            scanf("%d",&opc);
        }
        while(opc<1||opc>dimD);
        montoAutorizado(codigos,opc,dias,&monto,usuarios[pos].monto);
        do
        {
            printf("\tIngrese 'G' para guardar o 'S' para salir y no guardar: \n\tIndique su opcion: ");
            scanf("%*c%c",&resp);
            resp=toupper(resp);
            if(resp!='G' && resp!='S')
                printf("\tSolo puede ingresar 'G' o 'S'\n");
        }
        while(resp!='G' && resp!='S');
        if(resp=='G')
        {
            datos[posS].codigoS=opc;
            strcpy(datos[posS].fechaIS,fechaIda);
            strcpy(datos[posS].fechaRS,fechaRegreso);
            datos[posS].montS=monto;
            GuardarSolicitud(datos,&dimS);
        }
    }
    else
    {
        printf("\n\tSolicitud no registrada! \n\n");
        pulse_intro();
    }
}
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
void cerrarSolicitud(solicitud *datos,int dimS, declaracion *campos, int *dimC,registro *usuarios,int pos, unsigned long *divisas)
{
    int posS,i,dias,dd1,mm1,aa1,dd2,mm2,aa2,viajo,montoo,band=0;
    char fechaIda[11],fechaSolicitud[11];
    printf("\tFecha de ida del viaje: \n");
    validaFecha(fechaIda);

    posS=buscaSolicitud(datos,dimS,fechaIda,usuarios[pos].cedula);
    separaFecha(fechaIda,&dd1,&mm1,&aa1);
    fecha(fechaSolicitud);
    separaFecha(fechaSolicitud,&dd2,&mm2,&aa2);
	if(posS!=-1)
	{

	switch(datos[posS].estatuS)
	{
		case 'P':
        printf("\n\t\"SOLICITUD AUN POR APROBAR\"\n\n");
		break;
		case 'C':
			for(i=0; i<=*dimC; i++)
			{
				if(strcmp(campos[i].cedulaD,datos[posS].cedulaS)==0)
				{
					if(band==0)
						printf("\tDATOS DE CIERRE DE SOLICITUD\n\n");
						printf("\tFecha de Ida: \t\t%s\n",campos[i].fechaID);
						printf("\tMonto Ejecutado: \t%d\n",campos[i].montoED);
						printf("\tViajo?: \t\t");
					if(campos[i].viajoD==1)
						printf("Si.\n\n");
					else
						printf("No.\n\n");
					band=1;
				}
			}
			if(band==0)
				printf("\tPor Alguna Razon Usted no esta en declaracion.dat!\n\n");
			break;
		case 'A':
			dias=diferenciaFechas(dd1,mm1,aa1,dd2,mm2,aa2);
			if(dias>45)
			{
				printf("\n\t\"PERIODO DE CIERRE FINALIZADO, DIRIJASE AL ENTE ADMINISTRADOR\"\n\n");
				usuarios[pos].estatus=2;
			}
			else
			{
				do
				{
					printf("\n\tViajo? 0:No / 1:Si : ");
					scanf("%d",&viajo);
						if(viajo!=0&&viajo!=1)
							printf("\tIngrese solo 0 ó 1\n");
				}
				while(viajo!=0&&viajo!=1);
				i=*dimC;
				if(viajo==0)
				{
					campos[i].montoED=0;
					campos[i].viajoD=0;
					*divisas=*divisas+datos[posS].montS;
				}
				else
				{
					do
					{
						printf("\tIngrese el monto ejecutado: ");
						scanf("%d",&montoo);
						if(montoo<0)
							printf("\n\tEl monto no puede ser negativo!!\n\n");
					}
					while(montoo<0);
					if(montoo>datos[posS].montS)
					{
						printf("\t\"ACUDIR AL BANCO PARA CANCELAR SOBREGIRO\"\n\n");
						usuarios[pos].estatus=2;
					}
					else
					{
						*divisas=*divisas+(datos[posS].montS-montoo);
					}
					campos[i].montoED=montoo;
					campos[i].viajoD=1;
				}
					strcpy(campos[i].cedulaD,datos[posS].cedulaS);
					strcpy(campos[i].fechaID,datos[posS].fechaIS);
					usuarios[pos].monto=usuarios[pos].monto-campos[i].montoED;
					*dimC=i+1;
					guardarDeclaracion(campos,*dimC);
			}
			printf("\n\tSolicitud cerrada correctamente!\n\n");
			datos[posS].estatuS='C';
			GuardarSolicitud(datos,&dimS);
			break;
	}
	}else
		printf("\n\tSolicitud no Registrada!\n\n");
    pulse_intro();
}
void guardarConfig(int divisasU,unsigned long *divisas)
{
    FILE *salida;
    salida=fopen("config.dat","w");
    fprintf(salida,"%d\n",divisasU);
    fprintf(salida,"%lu\n",*divisas);
    fclose(salida);
}
void limpiar_buffer()
{
    while(getchar()!='\n');
}
void guardarDeclaracion(declaracion *campos,int dimC)
{
    FILE *salida;
    int i;
    salida=fopen("declaracion.dat","w");
    for(i=0; i<=dimC-1; i++)
    {
        fprintf(salida,"%s ",campos[i].cedulaD);
        fprintf(salida,"%s ",campos[i].fechaID);
        fprintf(salida,"%d ",campos[i].montoED);
        fprintf(salida,"%d\n",campos[i].viajoD);
    }
    fclose(salida);
}
/***LISTADOS AGREGADO POR VANEY***/
/*Listado del Estado de cuenta del viajero*/
void EstadoCuenta(registro *usuarios, solicitud *solicitudes, declaracion *declaraciones, int dim,int dimS,int dimD)
{

    char cedula[11];
    int pos,i,j,MontoUtilizar,totalS,totalV,totalMUsado,totalMUsar,clave,aux;

    leecedula(cedula);/*Para emitir el listado debe ingresarse la cedula del usuario*/
    pos=BuscandoUsuario(usuarios,dim,cedula);
    clave=BuscandoUsuarioS(solicitudes,dimS,cedula);
    if(pos!=-1&&clave!=-1)
    {
        printf("\n\t\t\t\t\t\t\t\t\t\tESTADO DE CUENTA\n\n");
        printf("\t\t\t\tNombre: %s\tApellido: %s\tCÉDULA: %s\tFECHA DE EMISIÓN: %s\tESTATUS: %d\n\n\n",usuarios[pos].nombres,usuarios[pos].apellidos,usuarios[pos].cedula,usuarios[pos].fecha,usuarios[pos].estatus);
        printf(" No.Solicitud");
        printf("       Fecha Solicitud");
        printf("       Estatus        Ida           Vuelta");
        printf("       Monto autorizado");
        printf("       Monto usado");
        printf("       Monto por utilizar");
        printf("       Destino");
        printf("       ¿Viajó?\n");
        totalS=0;
        totalV=0;
        totalMUsado=0;
        totalMUsar=0;
        aux=1;
        for(i=0; i<=dimS-1; i++)
        {
            if(strcmp(cedula,solicitudes[i].cedulaS)==0)
            {
                printf(" %7.d              %s             %c        %s     %s       %7.d          ",solicitudes[i].numeroS,solicitudes[i].fechaS,solicitudes[i].estatuS,solicitudes[i].fechaIS,solicitudes[i].fechaRS,solicitudes[i].montS);
                totalS++;
                for(j=0; j<=dimD-1; j++)
                {
                    if(strcmp(cedula,declaraciones[j].cedulaD)==0)
                    {
                        printf("%11.d",declaraciones[j].montoED);
                        totalMUsado=totalMUsado+declaraciones[j].montoED;
                        MontoUtilizar=solicitudes[i].montS-declaraciones[j].montoED;
                        if(MontoUtilizar==0)
                        {
                            printf("     %16.1d     ",0);
                        }
                        else
                        {
                            printf("     %16.d     ",MontoUtilizar);
                        }
                        totalMUsar=totalMUsar+MontoUtilizar;
                        printf("    %10.d  ",solicitudes[i].codigoS);
                        printf("      %6.d\n",declaraciones[j].viajoD);
                        if(declaraciones[j].viajoD==1)
                        {
                            totalV++;
                        }
                        aux=0;
                    }
                }
                if(aux==1)
                {
                    printf("%11.1d",0);
                    printf("    %16d      ",solicitudes[i].montS);
                    printf("    %10.d  ",solicitudes[i].codigoS);
                    printf("      %6.1d\n",0);
                }
            }
        }
        printf("\n\n\t\tTotal Solicitudes         %d\n",totalS);
        printf("\t\tTotal viajes realizados   %d\n",totalV);
        printf("\t\tTotal monto usado         %d\n",totalMUsado);
        if(totalMUsar==0)
        {
            printf("\t\tTotal monto por usar      0\n\n");
        }
        else
        {
            printf("\t\tTotal monto por usar      %d\n\n",totalMUsar);
        }
    }
    else
    {
	if(pos!=-1&&clave==-1){
		printf("\n\t\t\t\t\t\t\t\t\t\tESTADO DE CUENTA\n\n");
        	printf("\t\t\t\tNombre: %s\tApellido: %s\tCÉDULA: %s\tFECHA DE EMISIÓN: %s\tESTATUS: %d\n\n\n",usuarios[pos].nombres,usuarios[pos].apellidos,usuarios[pos].cedula,usuarios[pos].fecha,usuarios[pos].estatus);
		printf("\n\t\t\t\t\t\t\t\t\t\tREGISTRADO SIN SOLICITUDES\n\n");
	}
    	else
    	{
        	printf("\n\t\tEste Usuario NO se encuentra en nuestra base de datos\n");
    	}
    }/*fsiGRANDE*/
}
/*Listado de solicitudes por mes*/
void solicitud_divisas(registro *usuarios,solicitud *solicitudes,int dim,int dimS)
{

    int mes,ano,diaS,meS,anoS,i,diaI,mesI,anoI,diaR,mesR,anoR,numeroDias,pos;
    int totalS,totalDestino,aux;

    leerMesyAno(&mes,&ano);
    printf("\n\t\t\t\t\t\t\t\t\tSOLICITUD DE DIVISAS\n\n");
    printf("\n\t\t\t\tMES: %d        AÑO: %d\n\n",mes,ano);
    printf("\nFecha Solicitud      Nro Solic      Cédula         Nombre       Apellido         Destino       F. Ida        F.Regreso         Monto autorizado       No. Días de viaje\n");
    totalS=0;
    for(i=0; i<=dimS-1; i++)
    {
        separaFecha(solicitudes[i].fechaS,&diaS,&meS,&anoS);
        if(ano==anoS&&mes==meS)
        {
            ordenarfecha(solicitudes,dimS);
            pos=BuscandoUsuario(usuarios,dim,solicitudes[i].cedulaS);
            separaFecha(solicitudes[i].fechaIS,&diaI,&mesI,&anoI);
            separaFecha(solicitudes[i].fechaRS,&diaR,&mesR,&anoR);
            numeroDias=diferenciaFechas(diaI,mesI,anoI,diaR,mesR,anoR);
            if(pos!=-1)
            {
                printf("\n  %s            %d        %-10.10s %15s %15s %9.d        %s      %s             %4.d                %6.d\n",solicitudes[i].fechaS,solicitudes[i].numeroS,solicitudes[i].cedulaS,usuarios[pos].nombres,usuarios[pos].apellidos,solicitudes[i].codigoS,solicitudes[i].fechaIS,solicitudes[i].fechaRS,solicitudes[i].montS,numeroDias);
                totalS++;
            }
            else
            {
                printf("\neste usuario no se encuentra en usuarios.dat\n");
            }

        }
        else
        {
            aux=0;
        }

    }
    if(aux!=0)
    {
        printf("\n\t\tTotal Solicitudes                                      %d",totalS);
        totalDestino=DestinoSolicitado(solicitudes,dimS);
        if(totalDestino==0)
        {
            Igualdad(solicitudes,dimS);
        }
        else
        {
            printf("\n\t\tDestino más solicitado                                 %d\n",totalDestino);
        }
        TotalDestinosDias(solicitudes,dimS);
        printf("\n");
    }
    else
    {
        system("clear");
        printf("\n\n\n\n\n\t\t\t\tLo Sentimos no hubo solicitud de divisas en esta fecha:%.2d/%d\n\n\n\n\n",mes,ano);
    }

}
/*Leer fecha*/
void leerMesyAno(int *mes, int *ano)
{

    int m,a;
    do
    {
        printf("\n\t\t\tIngrese mes: ");
        scanf("%d",&m);
        printf("\n\t\t\tIngrese año: ");
        scanf("%d",&a);
        printf("\n");
        if(m>12||m<=0||a<=0)
        {
            printf("\n\t\t\tFECHA INVALIDA!!!\n");
        }
    }
    while(m>12||m<=0||a<=0);
    *mes=m;
    *ano=a;
}
/*Ordenar vector de solicitudes por fecha*/
void ordenarfecha(solicitud *v,int dim)
{

    int i,j;

    for(i=1; i<=dim-1; i++)
    {

        for(j=0; j<=dim-2; j++)
        {
            if(strcmp(v[j].fechaS,v[j+1].fechaS)>0)
            {
                intercambiarS(&v[j],&v[j+1]);
            }/*fsi*/
        }/*fforpequeño*/
    }/*fforgrande*/
}
/*Intercambia posiciones segun el orden para solicitudes.dat*/
void intercambiarS(solicitud *v1,solicitud *v2)
{

    solicitud temp;

    temp.numeroS=v1->numeroS;
    v1->numeroS=v2->numeroS;
    v2->numeroS=temp.numeroS;

    strcpy(temp.fechaS,v1->fechaS);
    strcpy(v1->fechaS,v2->fechaS);
    strcpy(v2->fechaS,temp.fechaS);

    strcpy(temp.cedulaS,v1->cedulaS);
    strcpy(v1->cedulaS,v2->cedulaS);
    strcpy(v2->cedulaS,temp.cedulaS);

    temp.codigoS=v1->codigoS;
    v1->codigoS=v2->codigoS;
    v2->codigoS=temp.codigoS;

    strcpy(temp.fechaIS,v1->fechaIS);
    strcpy(v1->fechaIS,v2->fechaIS);
    strcpy(v2->fechaIS,temp.fechaIS);

    strcpy(temp.fechaRS,v1->fechaRS);
    strcpy(v1->fechaRS,v2->fechaRS);
    strcpy(v2->fechaRS,temp.fechaRS);

    temp.montS=v1->montS;
    v1->montS=v2->montS;
    v2->montS=temp.montS;

    strcpy(&temp.estatuS,&v1->estatuS);
    strcpy(&v1->estatuS,&v2->estatuS);
    strcpy(&v2->estatuS,&temp.estatuS);

}
/*Genera el destino más solicitado*/
int DestinoSolicitado(solicitud *solicitudes,int dimS)
{

    int cont1,cont2,cont3,cont4,cont5,DestinoS;
    int i;
    cont1=0;
    cont2=0;
    cont3=0;
    cont4=0;
    cont5=0;
    DestinoS=0;
    for(i=0; i<=dimS-1; i++)
    {
        if(solicitudes[i].codigoS==1)
        {
            cont1++;
        }
        if(solicitudes[i].codigoS==2)
        {
            cont2++;
        }
        if(solicitudes[i].codigoS==3)
        {
            cont3++;
        }
        if(solicitudes[i].codigoS==4)
        {
            cont4++;
        }
        if(solicitudes[i].codigoS==5)
        {
            cont5++;
        }
    }
    if(cont1>cont2&&cont1>cont3&&cont1>cont4&&cont1>cont5)
    {
        DestinoS=1;
    }
    else
    {
        if(cont2>cont1&&cont2>cont3&&cont2>cont4&&cont2>cont5)
        {
            DestinoS=2;
        }
        else
        {
            if(cont3>cont1&&cont3>cont2&&cont3>cont4&&cont3>cont5)
            {
                DestinoS=3;
            }
            else
            {
                if(cont4>cont1&&cont4>cont2&&cont4>cont3&&cont4>cont5)
                {
                    DestinoS=4;
                }
                else
                {
                    if(cont5>cont1&&cont5>cont2&&cont5>cont3&&cont5>cont4)
                    {
                        DestinoS=5;
                    }
                }
            }
        }
    }
    return(DestinoS);
}
/*En caso de que todos los destinos sean iguales*/
void Igualdad(solicitud *solicitudes,int dimS)
{

    int cont1,cont2,cont3,cont4,cont5;
    int aux,i;

    cont1=0;
    cont2=0;
    cont3=0;
    cont4=0;
    cont5=0;
    aux=-1;
    for(i=0; i<=dimS-1; i++)
    {
        if(solicitudes[i].codigoS==1)
        {
            cont1++;
        }
        if(solicitudes[i].codigoS==2)
        {
            cont2++;
        }
        if(solicitudes[i].codigoS==3)
        {
            cont3++;
        }
        if(solicitudes[i].codigoS==4)
        {
            cont4++;
        }
        if(solicitudes[i].codigoS==5)
        {
            cont5++;
        }
    }
    printf("\n\t\tDestino más solicitado                                 ");
    if(cont1==cont2&&cont1==cont3&&cont1==cont4&&cont1==cont5)
    {
        printf("1, 2, 3, 4 y 5\n");
    }
    else /*Permutaciones de 4*/
        if(cont1==cont2&&cont1==cont3&&cont1==cont4)
        {
            printf("1, 2, 3 y 4\n");
        }
        else if(cont1==cont4&&cont1==cont2&&cont1==cont5)
        {
            printf("1, 2, 4 y 5\n");
        }

        else if(cont1==cont2&&cont1==cont3&&cont1==cont5)
        {
            printf("1, 2, 3 y 5\n");
        }
        else if(cont1==cont3&&cont1==cont4&&cont1==cont5)
        {
            printf("1, 3, 4 y 5\n");
        }
        else if(cont2==cont3&&cont2==cont4&&cont2==cont5)
        {
            printf("2, 3, 4 y 5\n");
        }
        else /*Permutaciones de 3*/
            if(cont1==cont2&&cont1==cont3)
            {
                printf("1, 2 y 3\n");
            }
            else if(cont2==cont3&&cont2==cont4)
            {
                printf("2, 3 y 4\n");
            }
            else if(cont3==cont4&&cont3==cont5)
            {
                printf("3, 4 y 5\n");
            }
            else if(cont2==cont5&&cont2==cont4)
            {
                printf("2, 4 y 5\n");
            }
            else if(cont5==cont3&&cont5==cont1)
            {
                printf("1, 3 y 5\n");
            }
            else if(cont5==cont2&&cont5==cont1)
            {
                printf("1, 2 y 5\n");
            }
            else if(cont4==cont1&&cont4==cont2)
            {
                printf("1, 2 y 4\n");
            }
            else if(cont1==cont3&&cont1==cont4)
            {
                printf("1, 3 y 4\n");
            }
            else if(cont1==cont4&&cont1==cont5)
            {
                printf("1, 4 y 5\n");
            }
            else if(cont3==cont2&&cont3==cont5)
            {
                printf("2, 3 y 5\n");

            }
            else /*Permutaciones de 2*/
                if(aux!=1)
                {
                    aux=0;
                }
    if(cont1==cont2&&aux==0)
    {
        printf("1 y 2\n");
        aux=1;
    }
    if(cont1==cont3&&aux==0)
    {
        printf("1 y 3\n");
        aux=1;
    }
    if(cont1==cont4&&aux==0)
    {
        printf("1 y 4\n");
        aux=1;
    }
    if(cont1==cont5&&aux==0)
    {
        printf("1 y 5\n");
        aux=1;
    }
    if(cont2==cont3&&aux==0)
    {
        printf("2 y 3\n");
        aux=1;
    }
    if(cont2==cont4&&aux==0)
    {
        printf("2 y 4\n");
        aux=1;
    }
    if(cont2==cont5&&aux==0)
    {
        printf("2 y 5\n");
        aux=1;
    }
    if(cont3==cont4&&aux==0)
    {
        printf("3 y 4\n");
        aux=1;
    }
    if(cont3==cont5&&aux==0)
    {
        printf("3 y 5\n");
        aux=1;
    }
    if(cont4==cont5&&aux==0)
    {
        printf("4 y 5\n");
        aux=1;
    }
}
/*Determina el numero de dias por destino*/
void TotalDestinosDias(solicitud *solicitudes,int dimS)
{

    int i, cont1,cont2,cont3,cont4,cont5;

    cont1=0;
    cont2=0;
    cont3=0;
    cont4=0;
    cont5=0;
    for(i=0; i<=dimS-1; i++)
    {
        if(solicitudes[i].codigoS==1)
        {
            cont1++;
        }
        if(solicitudes[i].codigoS==2)
        {
            cont2++;
        }
        if(solicitudes[i].codigoS==3)
        {
            cont3++;
        }
        if(solicitudes[i].codigoS==4)
        {
            cont4++;
        }
        if(solicitudes[i].codigoS==5)
        {
            cont5++;
        }
    }
    printf("\t\tTotal de días por cada destino solicitado      ");
    printf("        Destino       Días\n");
    if(cont1>0)
    {
        printf("	                                                               1          %4.d\n",cont1);
    }
    if(cont2>0)
    {
        printf("	                                                               2          %4.d\n",cont2);
    }
    if(cont3>0)
    {
        printf("                                                                       3          %4.d\n",cont3);
    }
    if(cont4>0)
    {
        printf("                                                                       4          %4.d\n",cont4);
    }
    if(cont5>0)
    {
        printf("                                                                       5          %4.d\n",cont5);
    }
}
/*Buscando usuario en el archivo en solicitudes.dat*/
int BuscandoUsuarioS(solicitud *vector, int n,char *cedula)
{

    int centro,inf,sup;

    ordenarC(vector,n);
    inf=0;
    sup=n-1;
    while(inf<=sup)
    {
        centro=(sup+inf)/2;
        if(strcmp(vector[centro].cedulaS,cedula)==0)
        {
            return(centro);
        }
        else
        {
            if(strcmp(cedula,vector[centro].cedulaS)<0)
            {
                sup=centro-1;
            }
            else
            {
                inf=centro+1;
            }
        }
    }/*fmientras*/
    return(-1);
}

/*Ordenar un vector por cedula de identidad*/
void ordenarC(solicitud *v,int dim)
{

    int i,j;

    for(i=1; i<=dim-1; i++)
    {
        for(j=0; j<=dim-2; j++)
        {
            if(strcmp(v[j].cedulaS,v[j+1].cedulaS)>0)
            {
                intercambiarS(&v[j],&v[j+1]);
            }/*fsi*/
        }/*fforpequeño*/
    }/*fforgrande*/
}
/*Mini menu para el listado*/
int miniMenu()
{

    int resp;

    do
    {
        printf("\n\n\t\tBienvenido a los Listados del sistema de Asignación de divisas a viajeros\n");
        printf("\n\t\tSeleccionar una de las siguientes opciones:\n");
        printf("\t\t1.ESTADO DE CUENTA\n");
        printf("\t\t2.SOLICITUD DE DIVISAS\n");
        printf("\t\t0.SALIR\n");
        printf("\t\tIndique su opción: ");
        scanf("%d",&resp);
        printf("\n");
        if(resp<0||resp>2)
        {
            system("clear");
            printf("\n\t\tOpción Invalida\n");
        }
    }
    while(resp<0||resp>2);
    return(resp);
}

