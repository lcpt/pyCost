//CuaPre.cxx

#include "CuaPre.h"
#include "CodigosObra.h"

Descompuestos::set_pendientes CuaPre::LeeBC3DescompFase2(const Codigos &descomp)
{
    Buscadores bp;
    BuscadorElementos b_elem= elementos.GetBuscador();
    bp["elementos"]= &b_elem;
    BuscadorDescompuestos b_desc= unidades.GetBuscador();
    bp["ud_obra"]= &b_desc;
    return unidades.LeeBC3Fase2(descomp,bp);
}
const UdObra *CuaPre::BuscaUdObra(const std::string &cod) const
{
    return unidades.Busca(cod);
}
const Elemento *CuaPre::BuscaElemento(const std::string &cod) const
{
    return elementos.Busca(cod);
}
const Medible *CuaPre::BuscaPrecio(const std::string &cod) const
{
    const Medible *retval= BuscaUdObra(cod);
    if(!retval)
        retval= BuscaElemento(cod);
    return retval;
}

void CuaPre::EscribeSpre(void) const
{
    elementos.EscribeSpre();
    std::ofstream ofs_des("DES001.std",std::ios::out);
    unidades.EscribeSpre(ofs_des);
    ofs_des.close();
}
void CuaPre::EscribeBC3(std::ostream &os) const
{
    elementos.EscribeBC3(os);
    unidades.EscribeBC3(os);
}
void CuaPre::LeeSpre(std::istream &is)
{
    elementos.LeeSpre(is);
    std::string str;
    getline(is,str,'\n');
    if(str.find("[DES]")<str.length()) unidades.LeeSpre(is,elementos);
}

//! @brief Escribe los precios elementales.
void CuaPre::ImprLtxElementales(std::ostream &os) const
{
    elementos.ImprLtx(os);
}

//! @brief Escribe la justificación de precios.
void CuaPre::ImprLtxJustPre(std::ostream &os) const
{
    unidades.ImprLtxJustPre(os);
}

//! @brief Escribe el cuadro de precios número 1.
void CuaPre::ImprLtxCP1(std::ostream &os) const
{
    unidades.ImprLtxCP1(os);
}
//! @brief Escribe el cuadro de precios número 2.
void CuaPre::ImprLtxCP2(std::ostream &os) const
{
    unidades.ImprLtxCP2(os);
}
//! @brief Escribe los cuadros de precios números 1 y 2.
void CuaPre::ImprLtxCP(std::ostream &os) const
{
    ImprLtxCP1(os);
    ImprLtxCP2(os);
}

void CuaPre::EscribeHCalc(std::ostream &os) const
{
    elementos.EscribeHCalc(os);
    unidades.EscribeHCalc(os);
}

void CuaPre::SimulaDescomp(const std::string &origen, const std::string &destino)
{
    unidades.SimulaDescomp(origen,destino);
}
