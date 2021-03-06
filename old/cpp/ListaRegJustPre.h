//ListaRegJustPre.hxx

#ifndef LISTAREGJUSTPRE_HXX
#define LISTAREGJUSTPRE_HXX

#include "RegJustPre.h"
#include <deque>
#include "../EntBC3.h"

class ListaRegJustPre: public std::deque<RegJustPre>, public EntCmd
{
    tipo_concepto tipo;
public:
    ListaRegJustPre(const tipo_concepto &tp)
        : tipo(tp) {}
    void SetBase(const ppl_precio3 &b);
    void SetBaseAcum(const ppl_precio3 &b);
    ppl_precio3 Total(void) const;
    std::string StrTipo(void) const
    {
        switch(tipo)
        {
        case mdo:
            return "mano de obra";
        case mat:
            return "materiales";
        case maq:
            return "maquinaria";
        default:
            return "porcentajes";
        }
    }
    void ImprLtxJust(std::ostream &os) const;
    void ImprLtxCP2(std::ostream &os) const;
    void ImprLtxCP2Porc(std::ostream &os) const;
};

#endif
