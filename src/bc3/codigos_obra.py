# -*- coding: utf-8 -*-
#CodigosObra.py




import codes

class CodigosObra(object):
    def __init__(self):
        self.caps= Codigos() #capitulos.
        self.elementos= Codigos()
        self.mediciones= Codigos()
        self.udsobr= Codigos()
        self.resto= Codigos()
        self.containers= [self.caps,self.elementos,self.mediciones,self.udsobr,self.resto]
        self.codigos_capitulos= set()


    def GetDatosElementos(self):
        return elementos


    def GetDatosUnidades(self):
        return udsobr


    def GetDatosObra(self):
        return caps.GetObra()


    #not  @brief Devuelve los registros correspondientes a los capítulos
    #not  de la obra.
    def GetDatosCaps():
        return caps


    #not  @brief Devuelve los códigos de los capítulos de la obra.
    def GetCodigosCapitulos(self):
        return codigos_capitulos

    def ExisteConcepto(self, cod):
        '''Devuelve verdadero si existe el concepto 
           cuyo código se pasa como parámetro.'''
        retval= False
        for c in containers:
            if c.find(cod) != None:
              retval= True
              break
        return retval


    #not  @brief Devuelve una cadena de caracteres que identifica la
    #not  tabla en la que esta guardado el concepto.
    def StrTablaConcepto(self, cod):
        if caps.find(cod) != caps.end():
            return "capitulo"
        elif elementos.find(cod) != elementos.end():
            return "elementos"
        elif mediciones.find(cod) != mediciones.end():
            return "mediciones"
        elif udsobr.find(cod) != udsobr.end():
            return "descompuestos"
        elif resto.find(cod) != resto.end():
            return "resto"
        else:
            return "ninguna"


    #@ brief Devuelve un iterador al concepto cuyo código se pasa como parámetro.
    def BuscaConcepto(self, cod):
        retval= None
        for c in containers:
            tmp= c.find(cod)
            if(tmp):
                retval= tmp
                break
        return retval


    #@ brief Separa los registros según sean capítulos, mediciones, descompuestos, etc.
    def Trocea(self, verborrea):
        obra = resto.GetObra(); #Obtiene los registros que corresponden a la obra.
        caps.InsertaCods(obra)
        #resto.Borra(obra)
        caps+= resto.GetCapitulos()
        resto.Borra(caps)
        elementos= resto.GetElementos()
        resto.Borra(elementos)
        udsobr= resto.GetDescompuestos()
        resto.Borra(udsobr)
        if resto.size()>0:
            lmsg.error("Quedaron " + resto.size() + " conceptos sin importar" + '\n')
            if verborrea>4:
                lmsg.error(resto + '\n')


        codigos_capitulos= caps.GetCodigos()


    #@ brief Devuelve los datos del capítulo al que apunta el iterador.
    def GetDatosCapitulo(self, i):
        return caps.GetDatosCapitulo(i)


    #not  @brief Carga las líneas de BC3 "resto" y después llama a la rutina "Trocea"
    def LeeBC3(self, inputS, verborrea):
        reg = ""
        count = 0
        while(inputS):
            getline(inputS,reg,'~')
            count+= 1
            if verborrea>6:
                logging.info("Leyendo registro: " + count + '\n')
            reg= elimina_car(reg,char(13))
            reg= elimina_car(reg,'\n')
            if len(reg)>2:
                tipo = reg[0]
                if(tipo == 'M'): #Las mediciones las insertamos directamente.
                    mediciones.InsertaReg(reg,verborrea,count)
                else:
                    resto.InsertaReg(reg,verborrea,count)


        logging.info("  leídas " + mediciones.size() + " mediciones." + '\n')
        Trocea(verborrea)


    #not  @brief Devuelve los registros de la descomposicion que corresponden a
    #not  precios elementales.
    def FiltraElementales(self, descomp):
        return FiltraPrecios(descomp,elementos)


    #not  @brief Devuelve los registros de la descomposicion que corresponden a
    #not  precios descompuestos.
    def FiltraDescompuestos(self, descomp):
        return FiltraPrecios(descomp,udsobr)


    #not  @brief Devuelve los registros de la descomposicion que corresponden a los
    #not  precios que se pasan como parámetros.
    def FiltraPrecios(self, descomp, precios):
        retval= None
        for d in descomp:
            p = precios.find(d.codigo)
            if(p): #Encontró el precio
                retval[p.first]= p.second

        return retval


    #not  @brief Devuelve los registros correspondientes a mediciones.
    def GetDatosMeds(self):
        return mediciones


    def BorraElementales(self, els):
        elementos.Borra(els)


    def BorraDescompuestos(self, uds):
        udsobr.Borra(uds)


    def Print(os):
        os.write("Obra: " + '\n' + self.GetDatosObra() + '\n'
           + "Capítulos: " + '\n' + self.caps + '\n'
           + "Elementos:" + '\n' + '\n'
           + "Descompuestos:" + '\n' + self.udsobr + '\n'
           + "Mediciones:" + '\n' + self.mediciones + '\n'
           + "Quedan: " + '\n' + self.resto + '\n')
        return os
