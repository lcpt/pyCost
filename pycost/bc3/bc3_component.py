#BC3Component.py

from pycost.bc3 import fr_entity
from pycost.bc3 import bc3_entity
from pycost.prices.price_justification import PriceJustificationRecord as pjr
from pycost.utils import basic_types


class BC3Component(fr_entity.EntFR):
    '''Component of a price decomposition.'''

    def __init__(self, e= None, fr= fr_entity.EntFR()):
        super(BC3Component,self).__init__(fr.factor,fr.productionRate)
        self.ent= e

    def getPrice(self):
        return self.ent.getPrice()*getProduct()

    def getRoundedPrice(self):
        retval= self.ent.getRoundedPrice()
        retval*= self.getRoundedProduct()
        return retval

    def getLtxPriceString(self):
        return basic_types.human_readable(getRoundedPrice())


    def PrecioSobre(self, sobre):
        '''For percentages.'''
        d= basic_types.ppl_price(sobre)
        d*= getProduct()
        return d

    def StrPrecioSobreLtx(self, sobre):
        '''For percentages.'''
        return basic_types.human_readable(PrecioSobre(sobre))


    def getType(self):
        return self.ent.getType()


    def CodigoEntidad(self):
        return self.ent.Codigo()


    def isPercentage(self):
        return self.ent.isPercentage()


    def WriteSpre(self, os):
        if not ((CodigoEntidad()).find('%')):
            os.write(0 + '|' + self.CodigoEntidad() + '|')
        super(BC3Component,self).WriteSpre(os)

    def WriteBC3(self, os):
        os.write(self.ent.CodigoBC3() + '\\')
        super(BC3Component,self).WriteBC3(os)

    def Entidad(self):
        if self.ent:
            return self.ent
        else:
            lmsg.error("La componente no se refiere a ninguna entidad" + '\n')
            exit(1)

    def getPriceJustificationRecord(self, over):
        if self.isPercentage():
            return pjr.PriceJustificationRecord(CodigoEntidad(),self.getRoundedProduct(),self.ent.Unidad(),self.ent.getTitle(),True,self.getRoundedPercentage(),over)
        else:
            return pjr.PriceJustificationRecord(self.ent.Codigo(),self.getRoundedProduct(),self.ent.Unidad(),self.ent.getTitle(),False,self.ent.getRoundedPrice(),0.0)


    def ImprLtxJustPre(self, os, over):
        r= self.getPriceJustificationRecord(over)
        r.ImprLtxJustPre(os)
        return r.getTotal()


    def writePriceTableTwoIntoLatexDocument(self, doc, over):
        r= self.getPriceJustificationRecord(over)
        r.writePriceTableTwoIntoLatexDocument(doc)
        return r.getTotal()


