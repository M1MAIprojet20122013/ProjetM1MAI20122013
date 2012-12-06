#ifndef CONDITION_H
#define CONDITION_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct s_Condition Condition;

typedef enum {NEUMANN, DIRICHLET} Condition_type;

// Pour l'instant, on ne considère pas les conditions de Dirichlet de type $\phi = a$.
struct s_Condition
{
	Condition_type type;
	double value;
}; 

#ifdef __cplusplus
}
#endif

#endif
