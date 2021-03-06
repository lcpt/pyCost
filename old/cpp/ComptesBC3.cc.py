#ComptesBC3.cxx

#include "ComptesBC3.h"
#include "just_pre/ListaRegJustPre.h"
#include "just_pre/ListaJustPre.h"


#not  @brief Asigna el valor f a los factores de toda la descomposición.
def AsignaFactor(self, &f):
    for(dq_comp_bc3.iterator i=begin(); i!=end(); i++)
        (*i).Factor()= f

def EscribeSpre(self, &os):
    if(size()<1) return
    dq_comp_bc3.const_iterator i
    for(i=begin(); i!=end(); i++) (*i).EscribeSpre(os)
    os << '|' << endl_msdos

def EscribeBC3(self, &cod, &os):
    if(size()<1) return
    os << "~D" << '|'
       << cod << '|'
    dq_comp_bc3.const_iterator i
    for(i=begin(); i!=end(); i++) (*i).EscribeBC3(os)
    os << '|' << endl_msdos


def PrecioR(self, void):
    ListaJustPre lista(GetListaJustPre(True));#XXX Aqui porcentajes acumulados.
    return ppl_precio(double(lista.TotalRnd()))


#not  @brief Suma de los precios de un tipo (mdo, maq, mat,...)
def Precio(self, tipo):
    dq_comp_bc3.const_iterator i
    ppl_precio3 ptipo(0.0); #Precio total.
    for(i=begin(); i!=end(); i++) #Elementos normales.
        if (*i).Tipo()==tipo and not (*i).EsPorcentaje():
            ptipo+= (*i).PrecioR()
    return ptipo

#not  @brief Calcula los porcentajes sobre un tipo.
def PrecioSobre(self, tipo, &sobre):
    dq_comp_bc3.const_iterator i
    ppl_precio3 ptipo(0.0); #Precio total.
    for(i=begin(); i!=end(); i++) #Porcentajes.
        if (*i).Tipo()==tipo and (*i).EsPorcentaje():
            ptipo+= (*i).PrecioSobre(sobre)
    return ptipo

long double ComptesBC3.SumaPorcentajes(tipo_concepto tipo)
    dq_comp_bc3.const_iterator i
    long double porc(0.0); #Porcentaje total.
    for(i=begin(); i!=end(); i++) #Porcentajes.
        if (*i).Tipo()==tipo and (*i).EsPorcentaje():
            porc+= (*i).Producto()
    return porc


long double ComptesBC3.CalculaLambda( long double &objetivo)
    long sum_porc = SumaPorcentajes(sin_clasif)
    long sum_pi = Precio(mdo)+Precio(maq)
    long pmat = Precio(mat)
    long numerador = objetivo/(1.0+sum_porc)-pmat
    return (numerador/sum_pi)


long double ComptesBC3.FuerzaPrecio( long double &objetivo)
     long lambda = CalculaLambda(objetivo)
    dq_comp_bc3.iterator i
    for(i=begin(); i!=end(); i++) #Porcentajes.
        if (*i).Tipo()!=mat and not (*i).EsPorcentaje():
            (*i).Rendimiento()*=lambda
    if lambda<0.0:
        std.cerr << "lambda = " << lambda << " negativo" << std.endl

    return lambda

def GetElementosTipo(self, &tipo):
    ListaRegJustPre lista(tipo)
    for(const_iterator i=begin(); i!=end(); i++)
        if (*i).Tipo()==tipo and not (*i).EsPorcentaje():
            lista.push_back((*i).GetRegJustPre(0.0))
    return lista

def GetPorcentajesTipo(self, &tipo):
    ListaRegJustPre lista(tipo)
    for(const_iterator i=begin(); i!=end(); i++)
        if (*i).Tipo()==tipo and (*i).EsPorcentaje():
            lista.push_back((*i).GetRegJustPre(0.0))
    return lista


def GetListaJustPre(self, &pa):
    return ListaJustPre(pa,GetElementosTipo(mdo),GetElementosTipo(mat),GetElementosTipo(maq),GetElementosTipo(sin_clasif),GetPorcentajesTipo(sin_clasif))


def ImprLtxJustPre(self, &os, &pa):
    ListaJustPre lista(GetListaJustPre(pa))
    lista.ImprLtxJustPre(os)

def ImprLtxCP2(self, &os, &pa):
    ListaJustPre lista(GetListaJustPre(pa))
    lista.ImprLtxCP2(os)

def ImprLtxCP1(self, &os, &pa, &genero):
    ListaJustPre lista(GetListaJustPre(pa))
    lista.ImprLtxCP1(os,genero)


