#include "ArbolB.h"
int compara(string c,string cadena){

	unsigned int temp = c.length() ;
	unsigned int temp2 = cadena.length() ;

	unsigned int limite;
		
	if( temp > temp2)
		limite = temp2;
	else
		limite = temp;

	for(unsigned int i=0;i < limite ;i++){

		if ( c[i] > cadena[i] )
			return 1;
		
		else if( c[i] < cadena[i] )
			return -1;
	}
	if ( temp > temp2 )
			return 1;
		
	else if( temp < temp2 )
			return -1;
	else
		return 0;
	
}
bool nodoB::nodoLleno(int nEle){
	return (clavesUsadas==nEle);
}

bool nodoB::nodoVacio(int nEle){
	return (clavesUsadas<nEle/2);
}

void nodoB::escribeNodo(){
	cout<<page<<"\t";
	for(int i=0;i<clavesUsadas;i++)
		cout<<claves[i].registro<<"|"<<claves[i].valor<<"  ";
	cout<<"\t\t";
	for(int j=0;j<clavesUsadas+1;j++)
		if((hijos[j]))
			cout<<(hijos[j])->page<<"  ";
	cout<<"\n";	
}

bool ArbolB::encontrarNodo(nodoB *Act,bClaves &cl, int *pos){
	(*pos)=0;
	int t;
	//while((*pos)<Act->clavesUsadas && Act->claves[(*pos)]<cl)
	while((*pos)<Act->clavesUsadas && ( t= compara(Act->claves[*pos].valor,cl.valor) )<0)
		(*pos)++;
	
	return t==0;
}
bClaves* ArbolB::busca(nodoB* nodo,bClaves &cadena){
	if(nodo){
		int i=nodo->clavesUsadas/2,n,m=0;
		while(0<=i && i< nodo->clavesUsadas){

			if(!(n=compara(nodo->claves[i].valor,cadena.valor)))
				return &nodo->claves[i];
			if(!(n+m))break;
			m=n;
			i=i-n;
		}
		if(m>0)i++;
		return busca(nodo->hijos[i],cadena);
	}
	return 0;
}
nodoB* ArbolB::encontrar(bClaves &cl,int *pos,nodoB *Nodo,bool r){
	if(r) Nodo=raiz;
	if(!Nodo)
		return 0;
	else{
		int fl;
		fl=encontrarNodo(Nodo,cl,pos);
		if (fl)
			return Nodo;
		else
			return encontrar(cl,pos,Nodo->hijos[*pos],false);
	}

}
void ArbolB::insertar(bClaves &cl){
	int up;
	bClaves clMedian;
	nodoB *pnew,*nd;
	push(raiz,cl,&up,&clMedian,&nd);
	if(up){
		pnew=new nodoB(orden);
		pnew->clavesUsadas=1;
		pnew->claves[0]=clMedian;
		pnew->hijos[0]=raiz;
		pnew->hijos[1]=nd;
		pnew->page = cont;
		cont++;
		raiz=pnew;
		
		pnew=0;
		
	}
}

void ArbolB::push(nodoB *Act,bClaves &cl,int* Up,bClaves * clMedian,nodoB ** newnode){
	
	int k;
	if(!Act){
		(*Up)=1;
		(*clMedian)=cl;
		(*newnode)=0;
	}
	else{
		int fl;
		fl=encontrarNodo(Act,cl,&k);
		/*if(fl){
			//Act->claves[k].ingresar(cl,cl.inicio->posInicial,cl.inicio->largoCadena);
			cout<<"Duplicada\n";
			(*Up)=0;
			return;
		}*/
		push(Act->hijos[k],cl,Up,clMedian,newnode);

		if(*Up){
			if(Act->nodoLleno(orden-1))
				dividirNodo(Act,*clMedian,*newnode,k,clMedian,newnode);
			else{
				(*Up)=0;
				putLeaf(Act,*clMedian,*newnode,k);
			}
		}
	}
}

void ArbolB::putLeaf(nodoB *Act,bClaves cl,nodoB* rd,int k){
	int i;
	for(i=Act->clavesUsadas-1;i>=k;i--){		
		Act->claves[i+1]=Act->claves[i];
		Act->hijos[i+2]=Act->hijos[i+1];
	}
	Act->claves[k]=cl;		
	Act->hijos[i+2]=rd;
	Act->clavesUsadas++;
}

void ArbolB::dividirNodo(nodoB *Act,bClaves &cl,nodoB *rd,int k,bClaves *clMedian,nodoB **newnode){
	int i,posMdna;
	posMdna=(k<=orden/2)?orden/2:orden/2+1;	

	(*newnode)=new nodoB(orden);		

	for(i=posMdna;i<orden-1;i++){
		(*newnode)->claves[i-posMdna]=Act->claves[i];
		(*newnode)->hijos[i-posMdna+1]=Act->hijos[i+1];
	}
	(*newnode)->clavesUsadas=(orden-1)-posMdna; 
	Act->clavesUsadas=posMdna;

	if(k<=orden/2)   
		putLeaf(Act,cl,rd,k);
	else		
		putLeaf(*newnode,cl,rd,k-posMdna);

	(*clMedian)=Act->claves[Act->clavesUsadas-1];    
	(*newnode)->hijos[0]=Act->hijos[Act->clavesUsadas]; 
	Act->clavesUsadas--;
	(*newnode)->page = cont;
	cont++;
	
}

void ArbolB::mostrarArbol(nodoB *Act,bool r){
	int i;
	if(r){
		Act=raiz;
		cout<<"Page\tKeys Nodo\t\t Pag Ramas\n";
	}	
	if(!Act)return;
	Act->escribeNodo();
	for(i=0;i<=Act->clavesUsadas;i++)
		mostrarArbol(Act->hijos[i],false);
	
}
void ArbolB::eliminarArbol(nodoB* nodo){
	if(nodo){
	if(*nodo->hijos)
		for(int i=0;i<=nodo->clavesUsadas;i++)
			eliminarArbol(nodo->hijos[i]);
	
	delete nodo;
	nodo=0;
	}
	return;

}