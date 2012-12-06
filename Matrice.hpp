#ifndef MATRICE_HPP
#define MATRICE_HPP

// STL includes
#include <iostream>
#include <cmath>
#include <vector>
// other includes
#include "commun.h"

class Matrice
{
friend Matrice operator+(Matrice& A, Matrice& B);
friend std::vector<double> operator*(const Matrice& A, const double* x);

public:
	Matrice(uint r_count=1, uint c_count=1);
	Matrice(uint r_count, uint c_count, double default_init);
	~Matrice();
	uint get_row_count() const;
	uint get_col_count() const;
	void swap_rows(uint i, uint j);
	double& operator()(uint i, uint j); // i = ligne, j = colone
	double operator()(uint i, uint j) const;
private:
	uint row_count;
	uint col_count;
	double* mat_core;
};

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
);

#endif
