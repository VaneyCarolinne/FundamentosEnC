#include <stdio.h>
#define N 100
void leerdimension(int *kk);
void mostrarM(int Matriz[N][N], int kk);
void llenarM(int Matriz[N][N], int kk);
void InicializarM(int Matriz[N][N], int kk);
int main(){

	int  k;
	/*definicion de matriz*/
	int matriz[N][N];

		leerdimension(&k);
		InicializarM(matriz,k);
		llenarM(matriz,k);
		mostrarM(matriz,k);

	return 0;

}

void leerdimension(int *kk){

	do{
		printf("\nIngrece k?\n");
		scanf("%d",&*kk);
		if((*kk<2)||(*kk>9)){
			printf("\nIngrece un K en el rango de (2..9)\n");
		}
	}while((*kk<2)||(*kk>9));


}

void mostrarM(int Matriz[N][N], int kk){

	int i,j;

	 for(i=0;i<kk;i++){
                      for(j=0;j<kk;j++){
                          printf("%d  ",Matriz[i][j]);
                      }
                        printf("\n");
                 }


}

void llenarM(int Matriz[N][N], int kk){

	int i,j,aux,kk266666;
	kk2=kk;
	aux=1;
	i=0;
	j=0;
	Matriz[i][j]=kk;
	


	while(i!=kk-1&&j!=kk-1){
		/*Cuando se mueve a un lado*/

			if(aux==1){
				j++;
				kk2++;
				if(kk2==10){
					kk2=0;
				}
				Matriz[i][j]=kk2;
				kk2++;
				if(kk2==10){
					kk2=0;
				}
				if(i==kk-1){
					aux=4;
					}
					aux=2;

			}
			/*cuando baja en diagonal*/
			while(aux==2){
				j--;
				i++;
				Matriz[i][j]=kk2;
				kk2++;
				if(kk2==10){
					kk2=0;
				}
				if(j==0||i==kk-1){
					aux=3;
					}
				if(j==0&&i==kk-1){
						aux=1;
						kk2--;
					}	
				}
			
		/*Cuando baja solo*/
				if((j==0)||(j==kk-1)){
					i++;
					Matriz[i][j]=kk2;
					kk2++;
					if(kk2==10){
					  kk2=0;
				    }
					  aux=4;
			     }
		/*Cuando sube en diagonal*/
				while(aux==4){
					i--;
					j++;
					Matriz[i][j]=kk2;
					kk2++;
					if(kk2==10){
				    	kk2=0;
			     	}
					if(i==0||i==kk-1){
						aux=1;
						kk2--;
						}
					}
				
	}//fmientras
}

/*Inicializa la matriz en 0*/

void InicializarM(int Matriz[N][N], int kk){

	int i,j;
		for(i=0;i<kk;i++){
			for(j=0;j<kk;j++){
				Matriz[i][j]=0;
			}

		}
}
