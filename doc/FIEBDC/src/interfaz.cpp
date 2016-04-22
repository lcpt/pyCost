#include <windows.h>
#include <string.h>
#include "Base.h"

/////////////////////////////////////////////////////////////////////////////
// FUNCIONES REFERENTES AL PARAM�TRICO GLOBAL

// Lectura del param�trico global
HANDLE APIENTRY
BdcGloLee (VOID)
{
	return BdcLee ("######$");
}

// Obtenci�n de sus par�metros
LONG APIENTRY
BdcGloParNumero (
HANDLE	h )
{
	return BdcParNumero (h);
}

LONG APIENTRY
BdcGloOpcNumero (
HANDLE	h,
LONG	par )
{
	return BdcOpcNumero (h, par);
}

LPCSTR APIENTRY
BdcGloParRotulo (
HANDLE	h,
LONG	par )
{
	return BdcParRotulo (h, par);
}

LPCSTR APIENTRY
BdcGloOpcRotulo (
HANDLE	h,
LONG	par,
LONG	opc )
{
	return BdcOpcRotulo (h, par, opc);
}

BOOL APIENTRY
BdcGloCierra (
HANDLE	h)
{
	return BdcCierra (h);
}

////////////////////////////////////////////////////////////////////////////
//	FUNCIONES REFERENTES AL RESTO DE PARAM�TRICOS

// Lectura de una familia
HANDLE APIENTRY
BdcLee (
LPCSTR cod) {
	int		i;

	Cfiebdc *Cpar = new Cfiebdc();
	for (i=0;;i++) {
		Cpar->inicializa(BORRA);
		if (!((precios [i])(*Cpar, BUSCA)) )
			break;
		if (strcmp (Cpar->lee_codigo(), cod) == 0) {
			(precios [i])(*Cpar, LEE);
			Cpar->funcion = precios[i];
			return (HANDLE)Cpar;
		}
	}
	BdcCierra ( (HANDLE)Cpar );
	return (HANDLE) 0; // El precio no existe
}

// Obtenci�n de sus par�metros
LONG APIENTRY
BdcParNumero (
HANDLE	h )
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return Cpar->lee_num_par();
}

LONG APIENTRY
BdcOpcNumero (
HANDLE	h,
LONG	par)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return Cpar->lee_num_opc (par);
}

LPCSTR APIENTRY
BdcParRotulo (
HANDLE	h,
LONG	par)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return (LPCSTR)Cpar->lee_rot_par(par);
}

LPCSTR APIENTRY
BdcOpcRotulo (
HANDLE	h,
LONG	par,
LONG	opc)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return (LPCSTR)Cpar->lee_rot_opc (par, opc);
}

// Obtenci�n de las opciones en funci�n del c�digo
BOOL APIENTRY
BdcOpciones (
HANDLE	h,
LPCSTR	sub,
LPLONG	opcl )
{
	int len;

	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;

	if (!opcl)
		return FALSE;

	len = strlen(sub);
	if (len <= 0)
		return FALSE; // No existe subc�digo

	return Cpar->lee_opciones((char *)sub, opcl);
}

// Asignaci�n de opciones de los par�metros y c�lculo del derivado
BOOL APIENTRY 
BdcCalcula (
HANDLE	h,
LPLONG	opcl,
LONG	gloparnum,
LPLONG	gloopcl )
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	if (Cpar->lee_estado() == ST_VACIO) {
		Cpar->estado(ST_ERROR);
		return FALSE;
	}
	Cpar->opciones (opcl);
	Cpar->opciones_glo (gloparnum, gloopcl);
	return (Cpar->funcion) (*Cpar, CALCULA);
}


// Liberaci�n de memoria
BOOL APIENTRY
BdcCierra (
HANDLE	h)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	Cpar->inicializa (BORRA);
	Cpar->Cfiebdc::~Cfiebdc();
	return TRUE;
}

// Obtenci�n del derivado param�trico
LONG APIENTRY
BdcDesNumero (
HANDLE	h )
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return Cpar->lee_num_des();
}

LPCSTR APIENTRY
BdcDesCodigo (
HANDLE	h,
LONG	des )
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return (LPCSTR)Cpar->lee_cod_des (des);
}

double APIENTRY
BdcRendimiento (
HANDLE	h,
LONG	des)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return Cpar->lee_ren_des(des);
}

double APIENTRY
BdcPrecio (
HANDLE	h)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return Cpar->lee_precio();
}

LPCSTR APIENTRY
BdcCodigo (
HANDLE	h)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return (LPCSTR)Cpar->lee_codigo();
}

LPCSTR APIENTRY
BdcResumen (
HANDLE	h)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return (LPCSTR)Cpar->lee_resumen();
}

LPCSTR APIENTRY
BdcTexto (
HANDLE	h)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return (LPCSTR)Cpar->lee_texto();
}

LPCSTR APIENTRY
BdcPliego (
HANDLE	h)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return (LPCSTR)Cpar->lee_pliego();
}

LPCSTR APIENTRY
BdcError (
HANDLE	h)
{
	Cfiebdc	*Cpar;
	Cpar = (Cfiebdc *)h;
	return (LPCSTR)Cpar->lee_error();
}
