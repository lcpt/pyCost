//ProtoPartida.h
//Algo capaz de devolver mediciones de una unidad de obra.

#ifndef PROTOPARTIDA_H
#define PROTOPARTIDA_H

#include "InformeUdObra.h"
#include "Mediciones.h"
#include "Tipos.h"

class ProtoPartida : public EntPpl
{
    const Medible *ud;
    void EscribeBC3RegM(std::ostream &os,const std::string &cap_padre="",const std::string &pos="") const;
public:
    ProtoPartida(void):ud(NULL) {}
    ProtoPartida(const Medible &u):ud(&u) {}
    inline virtual ~ProtoPartida(void) {}
    virtual ProtoPartida *Copia(void) const= 0; //Constructor virtual.
    const std::string CodigoUdObra(void) const
    {
        return ud->Codigo();
    }
    const std::string UnidadMedida(void) const
    {
        return ud->Unidad();
    }
    const std::string TextoLUdObra(void) const
    {
        return ud->TextoLargo();
    }
    long double PrecioUd(void) const
    {
        return ud->Precio();
    }
    ppl_precio PrecioRUd(void) const
    {
        return ud->PrecioR();
    }
    virtual long double Total(void) const= 0;
    virtual ppl_dimension TotalR(void) const= 0;
    InformeUdObra Informe(void) const
    {
        return InformeUdObra(ud,Total());
    }
    std::string StrPrecioUd(void) const
    {
        return ud->StrPrecio();
    }
    std::string StrPrecioLtxUd(void) const
    {
        return ud->StrPrecioLtx();
    }
    long double Precio(void) const
    {
        return Total()*PrecioUd();
    }
    ppl_precio PrecioR(void) const
    {
        return ppl_precio(double(TotalR())*double(PrecioRUd()));
    }
    std::string StrPrecioLtx(void) const
    {
        return PrecioR().EnHumano();
    }
    virtual Mediciones Meds(void) const= 0;
    virtual void EscribeBC3(std::ostream &os,const std::string &cap_padre="",const std::string &pos="") const;
    //Latex.
    void ImprLtxCabecera(std::ostream &os,const std::string &totalr, const std::string ancho) const;
    static void ImprLtxLeyenda(std::ostream &os);
    static void ImprLtxPie(std::ostream &os,const std::string &totalr);
    void ImprCompLtxMed(std::ostream &os, const ProtoPartida &otra) const;
    void ImprCompLtxMed(std::ostream &os) const;
    void ImprLtxMed(std::ostream &os) const;
    void ImprLtxCabeceraPre(std::ostream &os,const std::string &totalr, const std::string ancho) const;
    void ImprCompLtxPre(std::ostream &os, const ProtoPartida &otra) const;
    void ImprCompLtxPre(std::ostream &os) const;
    void ImprLtxPre(std::ostream &os) const;
    void EscribeHCalcMed(std::ostream &os) const;
    void EscribeHCalcPre(std::ostream &os) const;
};

#endif
