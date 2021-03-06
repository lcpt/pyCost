//InformeMediciones.h

#ifndef INFORME_MEDICIONES_H
#define INFORME_MEDICIONES_H

#include "Medible.h"
#include <map>

class InformeUdObra;

class InformeMediciones: public std::map<Medible const *,long double>
{
public:
    void Inserta(const InformeUdObra &iu);
    void Merge(const InformeMediciones &otro);
    void ImprLtx(std::ostream &os) const;
};

#endif
