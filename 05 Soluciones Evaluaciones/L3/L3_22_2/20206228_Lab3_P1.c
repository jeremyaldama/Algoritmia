//T�cnica aplicada: Divide y Vencer�s
#include <stdio.h>
#define MAX_DIAS 30

int calcularDiasConsec(int*pesos, int*dias, int menorPeso,
										int left, int right){
	int i, contadorDiasConsec=0;
	//recorremos el arreglo de pesos, el cual tiene 30 dias
	int j=1;//ac� empieza el indice del arreglo dias
	for (i=0; i<MAX_DIAS; i++){
		if (pesos[i]==menorPeso){
			contadorDiasConsec++;
			dias[j] = i+1;//guardamos los d�as que tiene ese peso
						  //sumamos +1 para que se guarde el dia tal cual
						  //y no el �ndice
			j++;//actualizamos al sig d�a 
			if (pesos[i+1]!=menorPeso) break;
		}
	}
	//en el 1er indice guardamos la cantidad de d�as consecutivos
	dias[0] = contadorDiasConsec;
	return contadorDiasConsec;											
}

int hallarDiasConsecutivos(int*pesos, int*dias, int menorPeso,
							int left, int right){
	if (left==right) return 0;
	
	int mid = (left+right)/2;
	
	int diasConsecIzq, diasConsecDer, diasConsecBloq;
	
	diasConsecIzq = hallarDiasConsecutivos(pesos, dias, menorPeso,
										   left, mid);
	diasConsecDer = hallarDiasConsecutivos(pesos, dias, menorPeso,
										   mid+1, right);
	diasConsecBloq = calcularDiasConsec(pesos, dias, menorPeso,
										left, right);
	
	if (diasConsecIzq>diasConsecDer && diasConsecIzq>diasConsecBloq)
		return diasConsecIzq;
	else if (diasConsecDer>diasConsecIzq && diasConsecDer>diasConsecBloq)
		return diasConsecDer;
	return diasConsecBloq;
}

int hallarRangoDiasConMenorPeso(int *pesos, int left, int right){
	if (left==right) return pesos[left];
	
	int mid = (left+right)/2;
	
	int minLeft, minRight, minBlock;
	
	minLeft = hallarRangoDiasConMenorPeso(pesos, left, mid);
 	minRight = hallarRangoDiasConMenorPeso(pesos, mid+1, right);
	
	if (minLeft<minRight) return minLeft;
	return minRight;
}

int main(){
	int pesos[] = {98, 95, 92, 89, 91, 92, 89, 89, 92, 93, 94, 92, 91,
				  90, 88, 88, 88, 89, 90, 91, 88, 88, 90, 90, 92, 89,
				  90, 88, 90, 91};
	//hallamos el menor peso de todos los d�as con T(n) = O(logn)
	int menorPeso = hallarRangoDiasConMenorPeso(pesos, 0, MAX_DIAS-1);
	
	printf("El menor peso fue de %d. El rango de dias en que lo obtuvo",
			menorPeso);
			
	//en la posicion 0, se guardar� la cantidad de dias consecutivos
	//con el menor peso; y en el resto, los dias con el menor peso,
	//o sea el �ndice del arreglo pesos[] 
	int dias[MAX_DIAS+1];
	hallarDiasConsecutivos(pesos, dias, menorPeso, 0, MAX_DIAS);
	int primerDia, ultimoDia;
	primerDia = dias[1];
	ultimoDia = dias[1]+dias[0]-1;//el ultimo dia es igual al 1er dia m�s
								//la cantidad de d�as tuvo ese peso menos el
								//primer d�a
	printf(" fue del %d al %d", primerDia, ultimoDia);
	return 0;
}
