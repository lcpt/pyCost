//CompBC3.h

#ifndef COMPBC3_H
#define COMPBC3_H

#include "EntFR.h"
#include "EntBC3.h"

class RegJustPre;

//! Componente de una descomposición
class CompBC3: public EntFR
{
private:
    EntBC3 const *ent; //Entidad a la que se refiere.
    const EntBC3 &Entidad(void) const;
public:
    CompBC3(void);
    CompBC3(const EntBC3 &e,const EntFR &fr);
    CompBC3(const EntBC3 &e,const float &f,const float &r);
    long double Precio(void) const;
    virtual ppl_precio3 PrecioR(void) const;
    std::string StrPrecioLtx(void) const;
    ppl_precio3 PrecioSobre(const ppl_precio3 &sobre) const;
    std::string StrPrecioSobreLtx(const ppl_precio3 &sobre) const;
    virtual tipo_concepto Tipo(void) const;
    const std::string &CodigoEntidad(void) const;
    bool EsPorcentaje(void) const;
    void EscribeSpre(std::ostream &os) const;
    void EscribeBC3(std::ostream &os) const;
    RegJustPre GetRegJustPre(const ppl_precio3 &sobre= 0.0) const;
    ppl_precio3 ImprLtxJustPre(std::ostream &os,const ppl_precio3 &sobre= 0.0) const;
    ppl_precio3 ImprLtxCP2(std::ostream &os,const ppl_precio3 &sobre= 0.0) const;
};

#endif
