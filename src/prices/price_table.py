# -*- coding: utf-8 -*-
#CuaPre.py




import elementary_price_container
import unit_price_table
import codigos_obra

class CuaPre(EntPyCost):
    def __init__(self):
        self.elementos= Elementos() #Precios elementales.
        self.unidades= Descompuestos() #Unidades de obra.

    def Elementales(self):
        return self.elementos

    def UdsObra(self):
        return self.unidades

    def TieneElementales(self):
        return (self.elementos.size()>0)

    def NumDescompuestos(self):
        return self.unidades.size()

    def TieneDescompuestos(self):
        return (self.unidades.size()>0)

    def AgregaComponente(self, cod_ud, cod_el, r, f= 1.0):
        self.unidades.AgregaComponente(elementos,cod_ud,cod_el,r,f)


    def LeeBC3Elementales(self, elem):
        self.elementos.LeeBC3(elem)

    def LeeBC3DescompFase1(self, descomp):
        self.unidades.LeeBC3Fase1(descomp)

    def LeeBC3DescompFase2(self, descomp):
        bp= Buscadores()
        b_elem = elementos.GetBuscador()
        bp["elementos"]= b_elem
        b_desc = unidades.GetBuscador()
        bp["ud_obra"]= b_desc
        return unidades.LeeBC3Fase2(descomp,bp)

    def BuscaUdObra(self, cod):
        return self.unidades.Busca(cod)

    def BuscaElemento(self, cod):
        return self.elementos.Busca(cod)

    def BuscaPrecio(self, cod):
        retval= BuscaUdObra(cod)
        if not retval:
            retval= BuscaElemento(cod)
        return retval


    def WriteSpre(self):
        self.elementos.WriteSpre()
        ofs_des= std.ofstream("DES001.std",std.ios.out)
        self.unidades.WriteSpre(ofs_des)
        ofs_des.close()

    def WriteBC3(self, os):
        elementos.WriteBC3(os)
        unidades.WriteBC3(os)

    def LeeSpre(self, iS):
        self.elementos.LeeSpre(iS)
        Str=''
        getline(iS,Str,'\n')
        if(Str.find("[DES]")<len(Str)):
            self.unidades.LeeSpre(iS,elementos)


    #not  @brief Write los precios elementales.
    def ImprLtxElementales(self, os):
        self.elementos.ImprLtx(os)


    #not  @brief Write la justificación de precios.
    def ImprLtxJustPre(self, os):
        self.unidades.ImprLtxJustPre(os)


    #not  @brief Write el cuadro de precios número 1.
    def ImprLtxCP1(self, os):
        self.unidades.ImprLtxCP1(os)

    #not  @brief Write el cuadro de precios número 2.
    def ImprLtxCP2(self, os):
        self.unidades.ImprLtxCP2(os)

    #not  @brief Write los cuadros de precios números 1 y 2.
    def ImprLtxCP(self, os):
        ImprLtxCP1(os)
        ImprLtxCP2(os)


    def WriteHCalc(self, os):
        elementos.WriteHCalc(os)
        self.unidades.WriteHCalc(os)


    def SimulaDescomp(self, origen, destino):
        self.unidades.SimulaDescomp(origen,destino)
