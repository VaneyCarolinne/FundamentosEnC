/*Librerias*/
#include <stdio.h>
#include <stdlib.h>
/*Definicion de constantes*/
#define N 100
/*Prototipos*/
int leerArreglos(int a[N],int b[N], int *m, int *n);
void mostrar(int a[N],int b[N], int m, int n);
void ordenar(int *c[N],int dim);
void intercambiar(int *v1,int *v2);
void mostrarC(int *c, int dim);
/*Programa Principal*/
int main(){

	int i,j,k,n,m,dim,pos; 
	int c[N],a[N],b[N];

	if(!leerArreglos(a,b,&m,&n)){
		mostrar(a,b,m,n);
		for(i=0;i<=m;i++){
		  c[i]=a[i];			
		}
		for(j=0;j<=n;j++){
		   c[i-1]=b[j];
		   i++;	
		}
		dim=i-2;
		for(k=0;k<dim;k++){
			
		}
		mostrarC(c,dim);

	}/*FSiGRANDE*/
	
	return 0;
}

/*lee los datos del archivo*/
int leerArreglos(int a[N],int b[N], int *m, int *n)
{

    FILE *entrada;
    int i,j;
    char cad;

    entrada=(fopen("arreglos.dat","r"));
    if(entrada==NULL)
    {
	printf("\n\tEl Archivo arreglos.dat NO EXISTE!\t\n");
        return EXIT_FAILURE;
    }
    else
    {
        i=0;
        while(cad!='\n')
        {
            fscanf(entrada,"%d%c",&a[i],&cad);
	    i++;
	}
	*m=i;
	j=0;
        while(!feof(entrada)){
            fscanf(entrada,"%d%c",&b[j],&cad);
	    j++;
	}
	*n=j-1;
        fclose(entrada);
        return EXIT_SUCCESS;
    }
}
/*Muestra los dos arreglos A y B por pantalla*/
void mostrar(int a[N],int b[N], int m, int n)
{
    int i;
	/*Muestra arreglo a*/
     printf("Arreglo A: ");
    for(i=0; i<=m-1; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    printf("Arreglo B: ");
	/*muestra arreglo b*/
    for(i=0; i<=n-1; i++)
    {
        printf("%d ",b[i]);
    }
    printf("\n");
}
/*Ordena El arreglo final C*/
void ordenar(int *c[N],int dim)
{

    int i,j;
    for(i=0; i<=dim; i++)
    {
        for(j=i+1; j<=dim-1; j++)
        {
            if(c[i]>c[j])
            {
                intercambiar(c[i],c[j]);
            }/*fsi*/
        }/*fforpequeño*/
    }/*fforgrande*/
}
/*Intercambia numeros para ordenar el vector resultante*/
void intercambiar(int *v1,int *v2)
{
    int temp;
	
	temp=*v1;
	*v1=*v2;
	*v2=temp;
}
/*Muestra el vector C por pantalla*/
void mostrarC(int *c, int dim)
{
    int i;

    printf("Arreglo C: ");
    for(i=0; i<=dim-1; i++)
    {
        printf("%d ",c[i]);
    }
    printf("\n");
}
