#InformeMediciones.cxx

#include "InformeMediciones.h"
#include "InformeUdObra.h"

def Inserta(self, &iu):
    i = find(iu.Unidad())
    if i!=end():
        (*i).second+= iu.Medicion()
    else:
        (*self)[iu.Unidad()]= iu.Medicion()

def Merge(self, &otro):
    for(i = otro.begin(); i!= otro.end(); i++)
        Inserta(InformeUdObra((*i).first,(*i).second))

def ImprLtx(self, &os):
    if(size()<1) return
    os << "\\begin{longtable}{|l|p{4cm}|r|r|}" << std.endl
       << "\\hline" << std.endl
       << "Código & Descripción & Medición & Precio \\\\"
       << "\\hline" << std.endl
       << "\\endhead" << std.endl
       << "\\hline" << std.endl
       << "\\multicolumn{" << 4 << "}{|r|}{../..}\\\\\\hline" << std.endl
       << "\\endfoot" << std.endl
       << "\\hline" << std.endl
       << "\\endlastfoot" << std.endl
    for(i = begin(); i!= end(); i++)
        InformeUdObra iu((*i).first,(*i).second)
        iu.ImprLtx(os)
        os <<  "\\\\" << std.endl

    os << "\\end{longtable}" << std.endl

