#define BASE
#include "Fiebdc.h"

#define PAR		par.parametro
#define PRE		par.precio
#define DES		par.descompuesto
#define RES		par.resumen
#define TEX		par.texto
#define PLI		par.pliego
#define ROT		par.lee_rotulo
#define ERR		par.error
#define COD		par.codigo
#define SIN		par.sinonimo

#define INI(Op)	par.inicializa(Op)

#define ROTA	ROT(0)
#define ROTB	ROT(1)
#define ROTC	ROT(2)
#define ROTD	ROT(3)

#define A		par.lee_opcion(0)
#define B		par.lee_opcion(1)
#define C		par.lee_opcion(2)
#define D		par.lee_opcion(4)

// Valores de status
#define ST_ERROR	-1
#define	ST_VACIO	0
#define	ST_FAMILIA	1
#define ST_DERIVADO	2

#define BORRA		0
#define LEE			1
#define CALCULA		2
#define	BUSCA		3

#define MAX_PARAM	12		// M�ximo n�mero de par�netros
#define MAX_TXT		30000	// Longitud m�xima de los textos

class Cfiebdc;

typedef short (*PRECIO)(Cfiebdc &, short operacion);

extern PRECIO	precios[];

class Cfiebdc {
private:
	long	parnum;					// N� de par�metros
	long	opcnum[MAX_PARAM];		// N� de opciones por par�metro
	char	*parrot[MAX_PARAM];		// Texto de los r�tulos de cada par�metro
	char	**opcrot[MAX_PARAM];	// Texto de las opciones de cada par�metro

	long	opc[MAX_PARAM];			// Valores de cada par�metro
	long	opcgnum;				// N�mero de opciones globales
	long	*opcg;					// Valores de cada opci�n global

	char	*err;					// Texto de error
	double	pre;					// Precio unitario (precio simple)
	long	desnum;					// N� de descompuestos
	char	**descod;				// C�digos de cada precio de la descomposici�n
	double	*desren;				// Rendimiento de cada precio de la descomposici�n
	char	*res, *tex, *pli;		// Texto resumido, Completo y Pliego
	char	*codfam;				// C�digo del precio (familia)
	char	*subcod;				// Parte variable del c�digo autom�tica
	char	*codder;				// C�digo completo del derivado
	BOOL	status;

	long	sinnum;					// N� de sin�nimos
	char	**codsin[2];			// Textos [0] subc�digosautom�ticos [1] sin�nimos
public:
	//PRECIO	funcion;										// Puntero a la funci�n del precio
	short	(*funcion)		(Cfiebdc &par,short operacion);	// Puntero a la funci�n del precio
	BOOL	parametro		(char *Rot, ...);				// Crea un par�metro
	BOOL	precio			(double Pre);					// Fija el precio unitario
	BOOL	descompuesto	(double Ren, char *cod, ...);	// Crea un elemento de la descomposici�n
	BOOL	resumen			(char *Res, ...);				// Fija el texto resumido
	BOOL	texto			(char *Tex, ...);				// Fija el texto de descripci�n
	BOOL	pliego			(char *Pli, ...);				// Fija el texto del pliego
	BOOL	error			(char *Err, ...);				// Fija el texto de error
	BOOL	codigo			(char *Cod, ...);				// Fija el c�digo (familia o el derivado)
	void	estado			(BOOL Status) {status = Status; };
	BOOL	subcodigo		(void);							// Calcula el subc�digo
	BOOL	opciones		(long *Opc);					// Fija los valores de los par�metros
	BOOL	opciones_glo	(long OpcGNum, long *OpcG);	// Fija los valores de los par�metros globales
	BOOL	sinonimo		(char *Subcod, char *Codsin);	// Fija el sin�nimo se Subcod

	long	lee_num_par		(void) { return parnum; };
	long	lee_num_des		(void) { return desnum; };
	long	lee_num_opc		(long id_par) { return opcnum[id_par];};
	char	*lee_rot_par	(long id_par);
	char	*lee_rot_opc	(long id_par, long id_opc);
	char	*lee_cod_des	(long id_des);
	double	lee_ren_des		(long id_des);
	double	lee_precio		(void) { return pre; };
	char	*lee_codigo		(void);
	char	*lee_resumen	(void);
	char	*lee_texto		(void);
	char	*lee_pliego		(void);
	char	*lee_error		(void);
	
	long	lee_opcion		(long Par);						// Devuelve la opci�n fijada en el par�metro Par
	char	*lee_rotulo		(long Par);						// Devuelve el r�tulo de la opci�n fijada en el par�metro Par
	BOOL	lee_opciones	(char *Cod, long *Opc);			// Devuelve las opciones de un c�digo
	BOOL	lee_estado		(void) { return status; };

	int		inicializa		(short operacion);
	Cfiebdc ();
	~Cfiebdc ();
};

