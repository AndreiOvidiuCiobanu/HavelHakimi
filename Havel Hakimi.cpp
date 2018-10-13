#include<iostream>
#include<vector>
#include<fstream>
#include<list>
#include<algorithm>
using namespace std;

/**
Idee - la un pas unim varful de grad maxim cu urmatoarele in ordine descrescatoare a gradelor

Pentru a reordona secventa la fiecare pas -este suficient sa inversam vectorul de grade intre pozitiile intre care s-a stricat ordinea
Spre exemplu, pentru secventa
5 4 4 3 3 3 3 3 2 1 1, dupa un pas, obtinem secventa
0 3 3 2 2 2 3 3 2 1 1- reordonam intre pozitiile 4 si 8 <=> inversam/oglindim aceasta parte din vector
**/

struct varf{
	int grad;
	int eticheta;
};

int comp(struct varf v1, struct varf v2){
	return v1.grad>v2.grad;
}

void afisare(int i,int n, varf* s){
	for(int j=i;j<=n;j++)
		cout<<s[j].grad<<"/"<<s[j].eticheta<<" ";
	cout<<endl;
}

int main()
{
    varf *s;/// secventa citita
    vector<pair<int,int> >E;/// lista de muchii
    int n, x,y,poz1,poz2, i,j,v,poz;

    ifstream fin("date.in");
    fin>>n;
    int sum=0;
    s=new varf[n+1];
    for(i=1;i<=n;i++){/// citim secventa si asociem etichete
		fin>>x;
        varf v={x,i}; ///pereche grad,eticheta
        s[i]=v;
        sum=sum+x;
    }
    fin.close();

    if(sum%2==1)
    {cout<<"Secventa nu este grafica"; return 0;}

    sort(s+1,s+n+1,comp);///sortarea initiala a vectorului de perechi
    if(s[1].grad>=n)
    {cout<<"Secventa nu este grafica"; return 0;}

    i=1;
    while(s[i].grad>0)///cat timp cel mai mare grad e mai mare ca 0, inseamna ca nu am secventa nula, deci tb sa continui
    {
        afisare(i,n,s);
		varf v=s[i]; ///v - va fi nodul curent ce trebuie saturat

        for(j=1;j<=v.grad;j++) ///parcurg cele mai mari v.grad noduri = urmatoarele v.grad noduri din secventa
        {
            s[i+j].grad--; /// le decrementez gradul
            if(s[i+j].grad<0)  {cout<<"Secventa nu este grafica"; return 0;}///verific daca se genereaza ceva negativ
            ///- conditie de orprire
            E.push_back(make_pair( v.eticheta,s[i+j].eticheta));///adaug muchie de la varful corespunzator lui
            ///v la cel corespunzator lui s[i+j] la lista de muchii
        }

        int k=i+v.grad;///ultimul varf caruia i-am scazut gradul


        if(k+1<=n && s[k].grad<s[k+1].grad) {
                /**
            secventa nu ramane sortata <=>s[k].grad =s[k+1].grad-1
        	in acest caz exista o subsecventa care trebuie inversata pentru a reordona vectorul,
        	avand la inceput elementele egale cu s[k].grad si urmata de  elemente egale cu s[k+1].grad
            determinam pozitiile  poz1 si poz2 de inceput si sfarsit ale acestei secvente
            **/
			int poz1=k-1; ///mergem la stanga cat timp gradele sunt egale cu s[k].grad
            while(poz1>1 && s[k].grad==s[poz1].grad)
                poz1--;
            poz1++;

            int poz2=k+2; ///mergem la dreapta cat timp gradele sunt egale cu s[k+1].grad
			while(poz2<=n && s[k+1].grad==s[poz2].grad)
                    poz2++;



            reverse( s+poz1,s+poz2);

   		}
        ///afisare(i,n,s);
	    s[i].grad=0;
        i++;
    }
    afisare(i,n,s);
    cout<<"Secventa este grafica!\n Muchiile sunt:\n";
    for(int i=0;i<E.size();i++) {///afisare cu fr
    	pair<int,int> p=E[i];
        cout<<p.first<<'-'<<p.second<<endl;
    }
    return 0;
}
