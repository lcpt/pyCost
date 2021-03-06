//ProtoPartida.cxx

#include "ProtoPartida.h"
#include "Obra.h"

//! @brief Imprime la cabecera para la partida.
void ProtoPartida::ImprLtxCabecera(std::ostream &os,const std::string &totalr, const std::string ancho) const
{
    os << ascii2latex(CodigoUdObra()) << ltx_ampsnd
       << totalr << ' ' << ascii2latex(UnidadMedida()) << ltx_ampsnd
       << ltx_multicolumn(ltx_datos_multicolumn("4",ancho,ascii2latex(TextoLUdObra())));
}

//! @brief Imprime la partida.
void ProtoPartida::ImprCompLtxMed(std::ostream &os, const ProtoPartida &otra) const
{
    const std::string linea_en_blanco= ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_fin_reg;
    os << linea_en_blanco << std::endl;
    const std::string totalr_otra= otra.TotalR().EnHumano();
    otra.ImprLtxCabecera(os,totalr_otra,"p{4.5cm}|");
    os << ltx_ampsnd;
    const std::string totalr_esta= TotalR().EnHumano();
    ImprLtxCabecera(os,totalr_esta,"p{4.5cm}");
    os << ltx_fin_reg << std::endl;
    ImprLtxLeyenda(os);
    os << ltx_ampsnd;
    ImprLtxLeyenda(os);
    os << ltx_fin_reg << std::endl
       << ltx_hline << std::endl;
    Meds().ImprCompLtx(os,otra.Meds());
    ImprLtxPie(os,totalr_otra);
    os << ltx_ampsnd;
    ImprLtxPie(os,totalr_esta);
    os << ltx_fin_reg << std::endl;
    os << ltx_hline << std::endl;
    os << linea_en_blanco << std::endl;
}

//! @brief Imprime la partida.
void ProtoPartida::ImprCompLtxMed(std::ostream &os) const
{
    const std::string linea_en_blanco= ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_fin_reg;
    const std::string media_linea_en_blanco= ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
            ltx_ampsnd+ltx_ampsnd+ltx_ampsnd;
    os << linea_en_blanco << std::endl;
    os << media_linea_en_blanco;
    const std::string totalr= TotalR().EnHumano();
    ImprLtxCabecera(os,totalr,"p{4.5cm}");
    os << ltx_fin_reg << std::endl;
    //ImprLtxLeyenda(os);
    //os << ltx_ampsnd;
    os << media_linea_en_blanco;
    ImprLtxLeyenda(os);
    os << ltx_fin_reg << std::endl
       << ltx_hline << std::endl;
    Meds().ImprCompLtx(os);
    os << media_linea_en_blanco;
    ImprLtxPie(os,totalr);
    os << ltx_fin_reg << std::endl;
    os << ltx_hline << std::endl;
    os << linea_en_blanco << std::endl;
}

void ProtoPartida::ImprLtxCabeceraPre(std::ostream &os,const std::string &totalr, const std::string ancho) const
{
    os << ascii2latex(CodigoUdObra()) << ltx_ampsnd
       << totalr + " " + ascii2latex(UnidadMedida()) << ltx_ampsnd
       << ltx_multicolumn(ltx_datos_multicolumn("1",ancho,ascii2latex(TextoLUdObra())));
}
void ProtoPartida::ImprCompLtxPre(std::ostream &os, const ProtoPartida &otra) const
{
    const std::string linea_en_blanco= ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_fin_reg;
    os << linea_en_blanco << std::endl;
    const std::string totalr_otra= otra.TotalR().EnHumano();
    otra.ImprLtxCabeceraPre(os,totalr_otra,"p{2.5cm}");
    os << ltx_ampsnd
       << otra.StrPrecioLtxUd() << ltx_ampsnd
       << otra.StrPrecioLtx() << ltx_ampsnd;
    const std::string totalr_esta= TotalR().EnHumano();
    ImprLtxCabeceraPre(os,totalr_esta,"p{2.5cm}");
    os << ltx_ampsnd
       << StrPrecioLtxUd() << ltx_ampsnd
       << StrPrecioLtx() << ltx_fin_reg << std::endl;
    os << linea_en_blanco << std::endl;
}
void ProtoPartida::ImprCompLtxPre(std::ostream &os) const
{
    const std::string linea_en_blanco= ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_fin_reg;
    const std::string media_linea_en_blanco= ltx_ampsnd+ltx_ampsnd+
            ltx_ampsnd+ltx_ampsnd+ltx_ampsnd;
    os << linea_en_blanco << std::endl;
    os << media_linea_en_blanco;
    const std::string totalr_med= TotalR().EnHumano();
    ImprLtxCabeceraPre(os,totalr_med,"p{2.5cm}");
    os << ltx_ampsnd
       << StrPrecioLtxUd() << ltx_ampsnd
       << StrPrecioLtx() << ltx_fin_reg << std::endl;
    os << linea_en_blanco << std::endl;
}
void ProtoPartida::ImprLtxPre(std::ostream &os) const
{
    const std::string linea_en_blanco= ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_fin_reg;
    const std::string totalr_med= TotalR().EnHumano();
    ImprLtxCabeceraPre(os,totalr_med,"p{5cm}");
    os << ltx_ampsnd
       << StrPrecioLtxUd() << ltx_ampsnd
       << StrPrecioLtx() << ltx_fin_reg << std::endl;
    os << linea_en_blanco << std::endl;
}
//HCalc
void ProtoPartida::EscribeHCalcMed(std::ostream &os) const
{
    os << CodigoUdObra() << tab
       << en_humano(Total(),3) << tab << ascii2latex(UnidadMedida()) << tab
       << '"' << ascii2latex(TextoLUdObra()) << '"' << std::endl
       << "Texto" << tab
       << "Unidades" << tab
       << "Largo" << tab
       << "Ancho" << tab
       << "Alto" << tab
       << "Parcial" << std::endl;
    Meds().EscribeHCalc(os);
}
void ProtoPartida::EscribeHCalcPre(std::ostream &os) const
{
    os << CodigoUdObra() << tab
       << Total() << tab << UnidadMedida() << tab << TextoLUdObra() << tab
       << StrPrecioUd() << tab
       << Precio() << std::endl;
}

void ProtoPartida::EscribeBC3RegM(std::ostream &os,const std::string &cap_padre,const std::string &pos) const
{
    os << "~M|" << cap_padre << '\\' << CodigoUdObra() << '|'
       << pos << '|'
       << Total() << '|';
}

void ProtoPartida::EscribeBC3(std::ostream &os,const std::string &cap_padre,const std::string &pos) const
{
    EscribeBC3RegM(os,cap_padre,pos);
    Meds().EscribeBC3(os);
    os << '|' << endl_msdos;
}

void ProtoPartida::ImprLtxLeyenda(std::ostream &os)
{
    os << "Texto" << ltx_ampsnd
       << "Unidades" << ltx_ampsnd
       << "Largo" << ltx_ampsnd
       << "Ancho" << ltx_ampsnd
       << "Alto" << ltx_ampsnd
       << "Parcial";
}

void ProtoPartida::ImprLtxPie(std::ostream &os,const std::string &totalr)
{
    os << ltx_multicolumn(ltx_datos_multicolumn("5","r","Suma "+ ltx_ldots)) << ltx_ampsnd
       << ltx_textbf(totalr);
}

void ProtoPartida::ImprLtxMed(std::ostream &os) const
{
    const std::string linea_en_blanco= ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_fin_reg;
    os << linea_en_blanco << std::endl;
    const std::string totalr= TotalR().EnHumano();
    ImprLtxCabecera(os,totalr,"p{6cm}");
    os << ltx_fin_reg << std::endl;
    ImprLtxLeyenda(os);
    os << ltx_fin_reg << std::endl
       << ltx_hline << std::endl;
    Meds().ImprLtx(os);
    ImprLtxPie(os,totalr);
    os << ltx_fin_reg << std::endl;
    os << ltx_hline << std::endl;
    os << linea_en_blanco << std::endl;
}

