# -*- coding: utf-8 -*-
#UnitPrice.py


from pycost.utils import measurable as ms
from pycost.prices import elementary_price_container
from pycost.prices import component_list

class UnitPrice(ms.Measurable):

    def __init__(self, cod="", desc="", ud="", ld= None):
        super(UnitPrice,self).__init__(cod,desc,ud,ld)
        self.components= component_list.ComponentList()
    def Tipo(self):
        return self.mat;    #XXX provisional.

    def Precio(self):
        return self.components.Precio()

    def AsignaFactor(self, f):
        self.components.AsignaFactor(f)

    def Append(self,e, f, r):
        tmp= BC3Component(e,f,r)
        self.components.append(tmp)
        return tmp

    def LeeBC3Fase1(self,r):
        '''Lee la unidad a falta de la descomposición.'''
        super(UnitPrice,self).LeeBC3(r)

    def LeeBC3Fase2(self, r, bp):
        error = False
        if r.Datos().desc.size():
            tmp = ObtienePunteros(r.Datos().desc,bp,error)
            if not error:
                components= tmp
            else:
                lmsg.error("Error al leer descomposición de la unidad: " + Codigo() + '\n')

        else:
            components= GetSindesco(r.Datos().Precio(),bp)
        return error

    def GetSindesco(self, rendimiento, bp):
        '''Para unidades de obra sin descomposición de las que
           sólo se conoce el precio.'''
        retval= ComponentList()
        be= bp["elementos"]
        ent= be.Busca("SINDESCO")
        retval.append(BC3Component(ent,1.0,rendimiento))
        return retval

    @staticmethod
    def ObtienePunteros(self, descBC3, bp, error):
        '''Obtiene los punteros a los precios de la descomposición.'''
        retval= ComponentList()
        be= bp["elementos"]
        bd= bp["ud_obra"]
        ent= None
        for i in descBC3:
            ent= be.Busca((i).codigo)
            if not ent:
                ent= bd.Busca((i).codigo)
            if not ent:
                if(verborrea>6): #Puede no ser un error.
                    lmsg.error("UnitPrice.ObtienePunteros; No se encontró la componente: " + (i).codigo + '\n')
                error= True
                continue

            else:
                retval.append(BC3Component(ent,(i).factor,(i).rendimiento))
                error= False


        return retval



    def WriteSpre(self, os):
        os.write(Codigo() + '|'
           + Unidad() + '|'
           + Titulo() + '|')
        components.WriteSpre(os)


    def WriteBC3(self, os):
        Measurable.WriteBC3(os)
        components.WriteBC3(Codigo(),os)


    def SimulaDescomp(self,otra):
        '''Toma la descomposición de otra unidad de obra.
           sin alterar el precio de ésta.'''
        objetivo= self.Precio()
        components= copia(otra.components)
        return components.FuerzaPrecio(objetivo)


    def ImprLtxJustPre(self, os):
        os.write("\\begin{tabular}{l r l p{4cm} r r}" + '\n')
        #Cabecera
        os.write(ascii2latex(Codigo()) + " & "
           + ascii2latex(Unidad()) + " & "
           + ltx_multicolumn(ltx_datos_multicolumn("4","p{7cm}",ascii2latex(self.getLongDescription()))) + ltx_fin_reg + '\n')
        os.write("Código & Rdto. & Ud. & Descripción & Unit. & Total"
           + ltx_fin_reg + '\n' + ltx_hline + '\n')
        #Descomposición
        components.ImprLtxJustPre(os,True); #XXX Here cumulated percentages.
        os.write("\\end{tabular}" + '\n')

    def ImprLtxCP1(self, os):
        os.write(ascii2latex(Codigo()) + " & "
           + ascii2latex(Unidad()) + " & "
           + ascii2latex(self.getLongDescription()) + " & ")
        components.ImprLtxCP1(os,True,False); #XXX Aqui género.
        os.write("\\\\" + '\n')

    def ImprLtxCP2(self, os):
        os.write("\\begin{tabular}{l r p{5.5cm} r}" + '\n')
        #Cabecera
        os.write("Código & Ud. & Descripción & Importe"
           + ltx_fin_reg + '\n' + ltx_hline + '\n')
        os.write(ascii2latex(Codigo()) + " & "
           + ascii2latex(Unidad()) + " & "
           + ascii2latex(self.getLongDescription()) + " & " + ltx_fin_reg + '\n' + ltx_fin_reg + '\n')
        #Descomposición
        components.ImprLtxCP2(os,True); #XXX Here cumulated percentages.
        os.write("\\end{tabular}" + '\n')

    def WriteHCalc(self, os):
        os.write(Codigo() + tab
           + ascii2latex(Unidad()) + tab
           + '"' + ascii2latex(self.getLongDescription()) + '"' + tab
           + '"' + StrPrecioEnLetra(True) + '"' + tab
           + StrPrecio() + '\n')


