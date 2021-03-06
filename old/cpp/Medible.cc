//Medible.cxx

#include "Medible.h"

//! @brief Constructor.
Medible::Medible(const std::string &cod,const std::string &tit,const std::string &ud)
    : EntBC3(cod,tit), unidad(ud), txt_largo("") {}

const std::string &Medible::TextoLargo(void) const
{
    return txt_largo;
}

std::string &Medible::TextoLargo(void)
{
    return txt_largo;
}

const std::string &Medible::Unidad(void) const
{
    return unidad;
}

void Medible::EscribeBC3(std::ostream &os) const
{
    EscribeConceptoBC3(os);
    if(TextoLargo().length()>0)
        os << "~T|" << Codigo() << '|' << latin1TOpc850ML(TextoLargo()) << '|' << endl_msdos;
}
