#ProtoPartida.cxx

#include "ProtoPartida.h"
#include "Obra.h"

#not  @brief Imprime la cabecera para la partida.
def ImprLtxCabecera(self, &os, &totalr, ancho):
    os << ascii2latex(CodigoUdObra()) << ltx_ampsnd
       << totalr << ' ' << ascii2latex(UnidadMedida()) << ltx_ampsnd
       << ltx_multicolumn(ltx_datos_multicolumn("4",ancho,ascii2latex(TextoLUdObra())))


#not  @brief Imprime la partida.
def ImprCompLtxMed(self, &os, &otra):
     linea_en_blanco = ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_fin_reg
    os << linea_en_blanco << std.endl
     totalr_otra = otra.TotalR().EnHumano()
    otra.ImprLtxCabecera(os,totalr_otra,"p{4.5cm}|")
    os << ltx_ampsnd
     totalr_esta = TotalR().EnHumano()
    ImprLtxCabecera(os,totalr_esta,"p{4.5cm}")
    os << ltx_fin_reg << std.endl
    ImprLtxLeyenda(os)
    os << ltx_ampsnd
    ImprLtxLeyenda(os)
    os << ltx_fin_reg << std.endl
       << ltx_hline << std.endl
    Meds().ImprCompLtx(os,otra.Meds())
    ImprLtxPie(os,totalr_otra)
    os << ltx_ampsnd
    ImprLtxPie(os,totalr_esta)
    os << ltx_fin_reg << std.endl
    os << ltx_hline << std.endl
    os << linea_en_blanco << std.endl


#not  @brief Imprime la partida.
def ImprCompLtxMed(self, &os):
     linea_en_blanco = ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_fin_reg
     media_linea_en_blanco = ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
            ltx_ampsnd+ltx_ampsnd+ltx_ampsnd
    os << linea_en_blanco << std.endl
    os << media_linea_en_blanco
     totalr = TotalR().EnHumano()
    ImprLtxCabecera(os,totalr,"p{4.5cm}")
    os << ltx_fin_reg << std.endl
    #ImprLtxLeyenda(os)
    #os << ltx_ampsnd
    os << media_linea_en_blanco
    ImprLtxLeyenda(os)
    os << ltx_fin_reg << std.endl
       << ltx_hline << std.endl
    Meds().ImprCompLtx(os)
    os << media_linea_en_blanco
    ImprLtxPie(os,totalr)
    os << ltx_fin_reg << std.endl
    os << ltx_hline << std.endl
    os << linea_en_blanco << std.endl


def ImprLtxCabeceraPre(self, &os, &totalr, ancho):
    os << ascii2latex(CodigoUdObra()) << ltx_ampsnd
       << totalr + " " + ascii2latex(UnidadMedida()) << ltx_ampsnd
       << ltx_multicolumn(ltx_datos_multicolumn("1",ancho,ascii2latex(TextoLUdObra())))

def ImprCompLtxPre(self, &os, &otra):
     linea_en_blanco = ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_fin_reg
    os << linea_en_blanco << std.endl
     totalr_otra = otra.TotalR().EnHumano()
    otra.ImprLtxCabeceraPre(os,totalr_otra,"p{2.5cm}")
    os << ltx_ampsnd
       << otra.StrPrecioLtxUd() << ltx_ampsnd
       << otra.StrPrecioLtx() << ltx_ampsnd
     totalr_esta = TotalR().EnHumano()
    ImprLtxCabeceraPre(os,totalr_esta,"p{2.5cm}")
    os << ltx_ampsnd
       << StrPrecioLtxUd() << ltx_ampsnd
       << StrPrecioLtx() << ltx_fin_reg << std.endl
    os << linea_en_blanco << std.endl

def ImprCompLtxPre(self, &os):
     linea_en_blanco = ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+
                                       ltx_ampsnd+ltx_ampsnd+ltx_fin_reg
     media_linea_en_blanco = ltx_ampsnd+ltx_ampsnd+
            ltx_ampsnd+ltx_ampsnd+ltx_ampsnd
    os << linea_en_blanco << std.endl
    os << media_linea_en_blanco
     totalr_med = TotalR().EnHumano()
    ImprLtxCabeceraPre(os,totalr_med,"p{2.5cm}")
    os << ltx_ampsnd
       << StrPrecioLtxUd() << ltx_ampsnd
       << StrPrecioLtx() << ltx_fin_reg << std.endl
    os << linea_en_blanco << std.endl

def ImprLtxPre(self, &os):
     linea_en_blanco = ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_fin_reg
     totalr_med = TotalR().EnHumano()
    ImprLtxCabeceraPre(os,totalr_med,"p{5cm}")
    os << ltx_ampsnd
       << StrPrecioLtxUd() << ltx_ampsnd
       << StrPrecioLtx() << ltx_fin_reg << std.endl
    os << linea_en_blanco << std.endl

#HCalc
def EscribeHCalcMed(self, &os):
    os << CodigoUdObra() << tab
       << en_humano(Total(),3) << tab << ascii2latex(UnidadMedida()) << tab
       << '"' << ascii2latex(TextoLUdObra()) << '"' << std.endl
       << "Texto" << tab
       << "Unidades" << tab
       << "Largo" << tab
       << "Ancho" << tab
       << "Alto" << tab
       << "Parcial" << std.endl
    Meds().EscribeHCalc(os)

def EscribeHCalcPre(self, &os):
    os << CodigoUdObra() << tab
       << Total() << tab << UnidadMedida() << tab << TextoLUdObra() << tab
       << StrPrecioUd() << tab
       << Precio() << std.endl


def EscribeBC3RegM(self, &os, &cap_padre, &pos):
    os << "~M|" << cap_padre << '\\' << CodigoUdObra() << '|'
       << pos << '|'
       << Total() << '|'


def EscribeBC3(self, &os, &cap_padre, &pos):
    EscribeBC3RegM(os,cap_padre,pos)
    Meds().EscribeBC3(os)
    os << '|' << endl_msdos


def ImprLtxLeyenda(self, &os):
    os << "Texto" << ltx_ampsnd
       << "Unidades" << ltx_ampsnd
       << "Largo" << ltx_ampsnd
       << "Ancho" << ltx_ampsnd
       << "Alto" << ltx_ampsnd
       << "Parcial"


def ImprLtxPie(self, &os, &totalr):
    os << ltx_multicolumn(ltx_datos_multicolumn("5","r","Suma "+ ltx_ldots)) << ltx_ampsnd
       << ltx_textbf(totalr)


def ImprLtxMed(self, &os):
     linea_en_blanco = ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_ampsnd+ltx_fin_reg
    os << linea_en_blanco << std.endl
     totalr = TotalR().EnHumano()
    ImprLtxCabecera(os,totalr,"p{6cm}")
    os << ltx_fin_reg << std.endl
    ImprLtxLeyenda(os)
    os << ltx_fin_reg << std.endl
       << ltx_hline << std.endl
    Meds().ImprLtx(os)
    ImprLtxPie(os,totalr)
    os << ltx_fin_reg << std.endl
    os << ltx_hline << std.endl
    os << linea_en_blanco << std.endl


