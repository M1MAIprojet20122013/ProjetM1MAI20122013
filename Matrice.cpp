#include "Matrice.hpp"

#include <iostream>

Matrice::Matrice(uint r_count, uint c_count) : row_count(r_count), col_count(c_count), mat_core(new double[c_count*r_count])
{
}


Matrice::Matrice(uint r_count, uint c_count, double default_init) :  row_count(r_count), col_count(c_count), mat_core(new double[c_count*r_count])
{
	for (uint i=0;i<col_count*row_count;++i)
	{
		this->mat_core[i] = default_init;
	}

}

Matrice::~Matrice()
{
	delete[] this->mat_core;
}

uint Matrice::get_row_count() const
{
	return this->row_count;
}

uint Matrice::get_col_count() const
{
	return this->col_count;
}

void Matrice::swap_rows(uint i, uint j)
{
	double temp;
	for (uint k=0;k<this->col_count;++k)
	{
		temp = this->mat_core[i*this->col_count + k];
		this->mat_core[i*this->col_count + k] = this->mat_core[j*this->col_count + k];
		this->mat_core[j*this->col_count + k] = temp;
	}
}

double& Matrice::operator()(uint i, uint j)
{
	return this->mat_core[i*this->col_count + j];
}

double Matrice::operator()(uint i, uint j) const
{
	return this->mat_core[i*this->col_count + j];
}

Matrice operator+(Matrice& A, Matrice& B)
{
	Matrice C(A.row_count, A.col_count);
	for (uint i=0;i<A.row_count*A.col_count;++i)
	{
		C.mat_core[i] = A.mat_core[i] + B.mat_core[i];
	}
	return C;
}

std::vector<double> operator*(const Matrice& A, const double* x)
{
	std::vector<double> b(A.get_col_count(), 0);
	for (uint i=0;i<A.get_row_count();++i)
	{
		for (uint j=0;j<A.get_col_count();++j)
		{
			b[i] += A(i,j)*x[j];
		}
	}
	return b;
}

int rsl_gauss_jordan (
/* resolution d'un systeme de N equations a N inconnues */
/* methode de Gauss-Jordan */
/* pivotement force */
   int               N, /* nombre d'inconnues du systeme d'equations */
   Matrice&          A, /* matrice des coeff. du systeme */
   double*           B, /* second membre du systeme */
   int*          ORDRE, /* second membre du systeme */
   const double    EPS, /* petit parametre (valeur consideree 0) */
   double*           X  /* solution du systeme */
)
{
 int    i,j,mi,mj,mo,p;
 double ma,l,piv,pivo;

 /* initialisation de la table ordre */
 for (i=0; i<N; i++) ORDRE[i] = i;

 /* pour chaque pivo */
 for (p=0; p<N; p++) {

   /* recherche du meilleur pivot */
   mi = p;
   mj = p;
   pivo = A(p,p);

   for (i=p; i<N; i++) {
     for (j=p; j<N; j++) {
       piv = A(i,j);
       if (fabs(piv) > fabs(pivo)) {mi=i; mj=j; pivo=piv;}
     }
   }

   /*rsl_aff_matrice("Avant permutation ",N,A);*/
 
   /* permutation des lignes */
   ma    = B[p];
   B[p]  = B[mi];
   B[mi] = ma;
   for (j=p; j<N; j++) {
     ma       = A(p,j);
     A(p,j)  = A(mi,j);
     A(mi,j) = ma;
   }
   /* permutation des inconnues */
   mo        = ORDRE[p];
   ORDRE[p]  = ORDRE[mj];
   ORDRE[mj] = mo;
   /* permutation des colonnes */
   for (i=0; i<N; i++) {
     ma       = A(i,p);
     A(i,p)  = A(i,mj);
     A(i,mj) = ma;
   }
   
   /*rsl_aff_matrice("Apres permutation ",N,A);*/

   /* diagonalisation */
   pivo = A(p,p);
   if ( fabs(pivo) < EPS ) goto ERREUR2;
   
   for (j=p; j<N; j++) A(p,j) = A(p,j)/pivo;
   B[p] = B[p] / pivo;
   for (i=0; i<N; i++) {
    if (i != p) {
      l = A(i,p);
      for (j=p; j<N; j++) A(i,j) = A(i,j) - l * A(p,j);
      B[i] = B[i] - l * B[p];
    }
   }
   
 }

 /* ordonnancement de la solution */
 for (i=0; i<N; i++) X[ORDRE[i]] = B[i];

 /* sortie sans erreurs */
 return 0;

ERREUR2:;
printf("rsl_gauss_jordan: Pivo trop petit: PIVO = %25.17e\n",fabs(pivo));
printf("rsl_gauss_jordan:                       <  %#+-12.5e\n",EPS);
return p+1;

} /*rsl_gauss_jordan*/
