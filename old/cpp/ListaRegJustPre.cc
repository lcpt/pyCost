//ListaRegJustPre.cc

#include "ListaRegJustPre.h"
#include "bibXCBasica/src/texto/latex.h"


void ListaRegJustPre::SetBase(const ppl_precio3 &b)
{
    if(size()<1) return;
    iterator i;
    for(i=begin(); i!=end(); i++)
        (*i).SetBase(b);
}
void ListaRegJustPre::SetBaseAcum(const ppl_precio3 &b)
{
    if(size()<1) return;
    ppl_precio3 base(b);
    iterator i;
    for(i=begin(); i!=end(); i++)
    {
        (*i).SetBase(base);
        base+= (*i).Total();
    }
}
void ListaRegJustPre::ImprLtxJust(std::ostream &os) const
{
    if(size()<1) return;
    const_iterator i;
    for(i=begin(); i!=end(); i++)
        (*i).ImprLtxJustPre(os);
    os << ltx_multicolumn(ltx_datos_multicolumn("4","r","Total "+StrTipo()))
       << " & & " << Total().EnHumano() << ltx_fin_reg << std::endl << ltx_fin_reg << std::endl;
}
void ListaRegJustPre::ImprLtxCP2(std::ostream &os) const
{
    ppl_precio3 total= Total();
    if(total>ppl_precio3(0.0))
        os << " & & " << StrTipo()
           << " & " << total.EnHumano() << ltx_fin_reg << std::endl;
}
void ListaRegJustPre::ImprLtxCP2Porc(std::ostream &os) const
{
    if(size()<1) return;
    const_iterator i;
    for(i=begin(); i!=end(); i++)
        (*i).ImprLtxCP2(os);
}
ppl_precio3 ListaRegJustPre::Total(void) const
{
    ppl_precio3 retval(0.0);
    for(const_iterator i=begin(); i!=end(); i++)
        retval+= (*i).Total();
    return retval;
}

