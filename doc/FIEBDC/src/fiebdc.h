/*	FORMATO DE INTERCAMBIO EST�NDAR DE PARAM�TRICOS EN DLL	*/

#ifdef BASE

/****************************************************************************/
/*	PARTE DEL ARCHIVO NECESARIA PARA LOS DESARROLLADORES DE BASE DE PRECIOS	*/
/****************************************************************************/

/*	FUNCIONES REFERENTES AL PARAM�TRICO GLOBAL	*****************************/
/*	Accesibles en cualquier momento	*/
/*	Lectura del param�trico global */
HANDLE	APIENTRY BdcGloLee			(VOID);

/*	Accesibles despu�s de BdcGloLee	*/
/*	Obtenci�n de sus par�metros */
LONG	APIENTRY BdcGloParNumero 	(HANDLE h);
LONG	APIENTRY BdcGloOpcNumero 	(HANDLE h, LONG par);
LPCSTR	APIENTRY BdcGloParRotulo 	(HANDLE h, LONG par);
LPCSTR	APIENTRY BdcGloOpcRotulo 	(HANDLE h, LONG par, LONG opc);
/*	Cerrar y liberar memoria */
BOOL	APIENTRY BdcGloCierra		(HANDLE h);

/*	FUNCIONES REFERENTES AL RESTO DE PARAM�TRICOS	*************************/
/*	Accesibles en cualquier momento	*/
/*	Lectura de una familia */
HANDLE	APIENTRY BdcLee				(LPCSTR cod);

/*	Accesibles despu�s de BdcLee	*/
/*	Obtenci�n de sus par�metros */
LONG	APIENTRY BdcParNumero 		(HANDLE h);
LONG	APIENTRY BdcOpcNumero 		(HANDLE h, LONG par);
LPCSTR	APIENTRY BdcParRotulo 		(HANDLE h, LONG par);
LPCSTR	APIENTRY BdcOpcRotulo 		(HANDLE h, LONG par, LONG opc);
/*	Obtenci�n de las opciones en funci�n del c�digo */
BOOL	APIENTRY BdcOpciones		(HANDLE h, LPCSTR sub, LPLONG opcl);
/*	Asignaci�n de opciones de los par�metros y c�lculo del derivado */
BOOL	APIENTRY BdcCalcula			(HANDLE h, LPLONG opcl, LONG gloparnum, LPLONG gloopcl);
/*	Liberaci�n de memoria */
BOOL	APIENTRY BdcCierra			(HANDLE h);

/*	Accesibles despu�s de BdcCalcula	*/
/*	Obtenci�n del derivado param�trico */
LONG	APIENTRY BdcDesNumero		(HANDLE h);
LPCSTR	APIENTRY BdcDesCodigo		(HANDLE h, LONG des);
double	APIENTRY BdcRendimiento		(HANDLE h, LONG des);
double	APIENTRY BdcPrecio			(HANDLE h);
LPCSTR	APIENTRY BdcCodigo			(HANDLE h);
LPCSTR	APIENTRY BdcResumen			(HANDLE h);
LPCSTR	APIENTRY BdcTexto			(HANDLE h);
LPCSTR	APIENTRY BdcPliego			(HANDLE h);
/*	Mensajes de error */
LPCSTR	APIENTRY BdcError			(HANDLE h);


#else  /* BASE no definido */
/****************************************************************************/
/*	PARTE DEL ARCHIVO NECESARIA PARA LOS DESARROLLADORES DE PROGRAMAS		*/
/****************************************************************************/

/*	FUNCIONES REFERENTES AL PARAM�TRICO GLOBAL	*****************************/
typedef HANDLE	(APIENTRY * BDCGLOLEE)		(VOID);
typedef LONG	(APIENTRY * BDCGLOPARNUMERO)(HANDLE h);
typedef LONG	(APIENTRY * BDCGLOOPCNUMERO)(HANDLE h, LONG par);
typedef LPCSTR	(APIENTRY * BDCGLOPARROTULO)(HANDLE h, LONG par);
typedef LPCSTR	(APIENTRY * BDCGLOOPCROTULO)(HANDLE h, LONG par, LONG opc);
typedef BOOL	(APIENTRY * BDCGLOCIERRA)	(HANDLE h);

/*	FUNCIONES REFERENTES AL RESTO DE PARAM�TRICOS	*************************/
typedef HANDLE	(APIENTRY * BDCLEE)			(LPCSTR cod);
typedef LONG	(APIENTRY * BDCPARNUMERO)	(HANDLE h);
typedef LONG	(APIENTRY * BDCOPCNUMERO)	(HANDLE h, LONG par);
typedef LPCSTR	(APIENTRY * BDCPARROTULO)	(HANDLE h, LONG par);
typedef LPCSTR	(APIENTRY * BDCOPCROTULO)	(HANDLE h, LONG par, LONG opc);
typedef BOOL	(APIENTRY * BDCOPCIONES)	(HANDLE h, LPCSTR sub, LPLONG opcl);
typedef BOOL	(APIENTRY * BDCCALCULA)		(HANDLE h, LPLONG opcl, LONG gloparnum, LPLONG gloopcl);
typedef BOOL	(APIENTRY * BDCCIERRA)		(HANDLE h);
typedef LONG	(APIENTRY * BDCDESNUMERO)	(HANDLE h);
typedef LPCSTR	(APIENTRY * BDCDESCODIGO)	(HANDLE h, LONG des);
typedef double	(APIENTRY * BDCRENDIMIENTO)	(HANDLE h, LONG des);
typedef double	(APIENTRY * BDCPRECIO)		(HANDLE h);
typedef LPCSTR	(APIENTRY * BDCCODIGO)		(HANDLE h);
typedef LPCSTR	(APIENTRY * BDCRESUMEN)		(HANDLE h);
typedef LPCSTR	(APIENTRY * BDCTEXTO)		(HANDLE h);
typedef LPCSTR	(APIENTRY * BDCPLIEGO)		(HANDLE h);
typedef LPCSTR	(APIENTRY * BDCERROR)		(HANDLE h);

#endif /* de ifdef #BASE */
