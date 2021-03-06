//ListaJustPre.hxx

#ifndef LISTAJUSTPRE_HXX
#define LISTAJUSTPRE_HXX

#include "ListaRegJustPre.h"
#include "../Tipos.h"

class ListaJustPre: public EntCmd
{
    bool porcentajes_acumulados;
    ListaRegJustPre mano_de_obra;
    ListaRegJustPre materiales;
    ListaRegJustPre maquinaria;
    ListaRegJustPre otros;
    ListaRegJustPre porcentajes;
public:
    ListaJustPre(const bool &pa,const ListaRegJustPre &mano, const ListaRegJustPre &mater, const ListaRegJustPre &maqui, const ListaRegJustPre &otr, const ListaRegJustPre &porc);
    ppl_precio3 Base(void) const;
    ppl_precio3 Total(void) const;
    ppl_precio3 Redondeo(void) const;
    ppl_precio3 TotalRnd(void) const;
    ppl_precio2 TotalCP1(void) const;
    std::string StrPrecioLtx(void) const;
    std::string StrPrecioEnLetra(const bool &genero) const;
    size_t size(void) const;
    void ImprLtxJustPre(std::ostream &os) const;
    void ImprLtxCP1(std::ostream &os,const bool &genero) const;
    void ImprLtxCP2(std::ostream &os) const;
};

#endif
