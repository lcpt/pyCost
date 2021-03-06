//ComptesBC3.cxx

#include "ComptesBC3.h"
#include "just_pre/ListaRegJustPre.h"
#include "just_pre/ListaJustPre.h"


//! @brief Asigna el valor f a los factores de toda la descomposición.
void ComptesBC3::AsignaFactor(const float &f)
{
    for(dq_comp_bc3::iterator i=begin(); i!=end(); i++)
        (*i).Factor()= f;
}
void ComptesBC3::EscribeSpre(std::ostream &os) const
{
    if(size()<1) return;
    dq_comp_bc3::const_iterator i;
    for(i=begin(); i!=end(); i++) (*i).EscribeSpre(os);
    os << '|' << endl_msdos;
}
void ComptesBC3::EscribeBC3(const std::string &cod,std::ostream &os) const
{
    if(size()<1) return;
    os << "~D" << '|'
       << cod << '|';
    dq_comp_bc3::const_iterator i;
    for(i=begin(); i!=end(); i++) (*i).EscribeBC3(os);
    os << '|' << endl_msdos;
}

ppl_precio ComptesBC3::PrecioR(void) const
{
    ListaJustPre lista(GetListaJustPre(true));//XXX Aqui porcentajes acumulados.
    return ppl_precio(double(lista.TotalRnd()));
}

//! @brief Suma de los precios de un tipo (mdo, maq, mat,...)
ppl_precio3 ComptesBC3::Precio(tipo_concepto tipo) const
{
    dq_comp_bc3::const_iterator i;
    ppl_precio3 ptipo(0.0); //Precio total.
    for(i=begin(); i!=end(); i++) //Elementos normales.
        if((*i).Tipo()==tipo && !(*i).EsPorcentaje())
            ptipo+= (*i).PrecioR();
    return ptipo;
}
//! @brief Calcula los porcentajes sobre un tipo.
ppl_precio3 ComptesBC3::PrecioSobre(tipo_concepto tipo,const ppl_precio3 &sobre) const
{
    dq_comp_bc3::const_iterator i;
    ppl_precio3 ptipo(0.0); //Precio total.
    for(i=begin(); i!=end(); i++) //Porcentajes.
        if((*i).Tipo()==tipo && (*i).EsPorcentaje())
            ptipo+= (*i).PrecioSobre(sobre);
    return ptipo;
}
long double ComptesBC3::SumaPorcentajes(tipo_concepto tipo) const
{
    dq_comp_bc3::const_iterator i;
    long double porc(0.0); //Porcentaje total.
    for(i=begin(); i!=end(); i++) //Porcentajes.
        if((*i).Tipo()==tipo && (*i).EsPorcentaje())
            porc+= (*i).Producto();
    return porc;
}

long double ComptesBC3::CalculaLambda(const long double &objetivo) const
{
    long double sum_porc= SumaPorcentajes(sin_clasif);
    long double sum_pi= Precio(mdo)+Precio(maq);
    long double pmat= Precio(mat);
    long double numerador= objetivo/(1.0+sum_porc)-pmat;
    return (numerador/sum_pi);
}

long double ComptesBC3::FuerzaPrecio(const long double &objetivo)
{
    const long double lambda= CalculaLambda(objetivo);
    dq_comp_bc3::iterator i;
    for(i=begin(); i!=end(); i++) //Porcentajes.
        if((*i).Tipo()!=mat && !(*i).EsPorcentaje())
            (*i).Rendimiento()*=lambda;
    if(lambda<0.0)
    {
        std::cerr << "Error lambda= " << lambda << " negativo" << std::endl;
    }
    return lambda;
}
ListaRegJustPre ComptesBC3::GetElementosTipo(const tipo_concepto &tipo) const
{
    ListaRegJustPre lista(tipo);
    for(const_iterator i=begin(); i!=end(); i++)
        if((*i).Tipo()==tipo && !(*i).EsPorcentaje())
            lista.push_back((*i).GetRegJustPre(0.0));
    return lista;
}
ListaRegJustPre ComptesBC3::GetPorcentajesTipo(const tipo_concepto &tipo) const
{
    ListaRegJustPre lista(tipo);
    for(const_iterator i=begin(); i!=end(); i++)
        if((*i).Tipo()==tipo && (*i).EsPorcentaje())
            lista.push_back((*i).GetRegJustPre(0.0));
    return lista;
}

ListaJustPre ComptesBC3::GetListaJustPre(const bool &pa) const
{
    return ListaJustPre(pa,GetElementosTipo(mdo),GetElementosTipo(mat),GetElementosTipo(maq),GetElementosTipo(sin_clasif),GetPorcentajesTipo(sin_clasif));
}

void ComptesBC3::ImprLtxJustPre(std::ostream &os,const bool &pa) const
{
    ListaJustPre lista(GetListaJustPre(pa));
    lista.ImprLtxJustPre(os);
}
void ComptesBC3::ImprLtxCP2(std::ostream &os,const bool &pa) const
{
    ListaJustPre lista(GetListaJustPre(pa));
    lista.ImprLtxCP2(os);
}
void ComptesBC3::ImprLtxCP1(std::ostream &os,const bool &pa,const bool &genero) const
{
    ListaJustPre lista(GetListaJustPre(pa));
    lista.ImprLtxCP1(os,genero);
}

