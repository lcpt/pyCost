//CodigosObra.cxx

#include "CodigosObra.h"

std::set<std::string> CodigosObra::codigos_capitulos;

const Codigos &CodigosObra::GetDatosElementos(void) const
{
    return elementos;
}

const Codigos &CodigosObra::GetDatosUnidades(void) const
{
    return udsobr;
}

const Codigos CodigosObra::GetDatosObra(void) const
{
    return caps.GetObra();
}

//! @brief Devuelve los registros correspondientes a los capítulos
//! de la obra.
const Codigos &CodigosObra::GetDatosCaps(void) const
{
    return caps;
}

//! @brief Devuelve los códigos de los capítulos de la obra.
const std::set<std::string> &CodigosObra::GetCodigosCapitulos(void) const
{
    return codigos_capitulos;
}

//! @brief Devuelve verdadero si existe el concepto cuyo código se pasa como parámetro.
bool CodigosObra::ExisteConcepto(const std::string &cod) const
{
    if(caps.find(cod) != caps.end())
        return true;
    else if(elementos.find(cod) != elementos.end())
        return true;
    else if(mediciones.find(cod) != mediciones.end())
        return true;
    else if(udsobr.find(cod) != udsobr.end())
        return true;
    else if(resto.find(cod) != resto.end())
        return true;
    else
        return false;
}

//! @brief Devuelve una cadena de caracteres que identifica la
//! tabla en la que esta guardado el concepto.
std::string CodigosObra::StrTablaConcepto(const std::string &cod) const
{
    if(caps.find(cod) != caps.end())
        return "capitulo";
    else if(elementos.find(cod) != elementos.end())
        return "elementos";
    else if(mediciones.find(cod) != mediciones.end())
        return "mediciones";
    else if(udsobr.find(cod) != udsobr.end())
        return "descompuestos";
    else if(resto.find(cod) != resto.end())
        return "resto";
    else
        return "ninguna";
}

//@ brief Devuelve un iterador al concepto cuyo código se pasa como parámetro.
Codigos::const_iterator CodigosObra::BuscaConcepto(const std::string &cod) const
{
    Codigos::const_iterator retval= caps.find(cod);
    if(retval != caps.end())
        return retval;
    else if((retval= elementos.find(cod)) != elementos.end())
        return retval;
    else if((retval= mediciones.find(cod)) != mediciones.end())
        return retval;
    else if((retval= udsobr.find(cod)) != udsobr.end())
        return retval;
    else return resto.find(cod);
}

//@ brief Separa los registros según sean capítulos, mediciones, precios descompuestos, etc.
void CodigosObra::Trocea(const int &verborrea)
{
    Codigos obra= resto.GetObra(); //Obtiene los registros que corresponden a la obra.
    caps.InsertaCods(obra);
    //resto.Borra(obra);
    caps+= resto.GetCapitulos();
    resto.Borra(caps);
    elementos= resto.GetElementos();
    resto.Borra(elementos);
    udsobr= resto.GetDescompuestos();
    resto.Borra(udsobr);
    if(resto.size()>0)
    {
        std::cerr << "Quedaron " << resto.size() << " conceptos sin importar" << std::endl;
        if(verborrea>4)
            std::cerr << resto << std::endl;
    }

    codigos_capitulos= caps.GetCodigos();
}

//@ brief Devuelve los datos del capítulo al que apunta el iterador.
Codigos::reg_capitulo CodigosObra::GetDatosCapitulo(const Codigos::mapa::const_iterator &i) const
{
    return caps.GetDatosCapitulo(i);
}

//! @brief Carga las líneas de BC3 "resto" y después llama a la rutina "Trocea"
void CodigosObra::LeeBC3(std::istream &is,const int &verborrea)
{
    std::string reg= "";
    int count= 0;
    while(!is.eof())
    {
        getline(is,reg,'~');
        count++;
        if(verborrea>6)
            std::clog << "Leyendo registro: " << count << std::endl;
        reg= elimina_car(reg,char(13));
        reg= elimina_car(reg,'\n');
        if(reg.length()>2)
        {
            const char tipo= reg[0];
            if(tipo == 'M') //Las mediciones las insertamos directamente.
                mediciones.InsertaReg(reg,verborrea,count);
            else
                resto.InsertaReg(reg,verborrea,count);
        }
    }
    std::clog << "  leídas " << mediciones.size() << " mediciones." << std::endl;
    Trocea(verborrea);
}

//! @brief Devuelve los registros de la descomposicion que corresponden a
//! precios elementales.
Codigos CodigosObra::FiltraElementales(const regBC3_d &descomp) const
{
    return FiltraPrecios(descomp,elementos);
}

//! @brief Devuelve los registros de la descomposicion que corresponden a
//! precios descompuestos.
Codigos CodigosObra::FiltraDescompuestos(const regBC3_d &descomp) const
{
    return FiltraPrecios(descomp,udsobr);
}

//! @brief Devuelve los registros de la descomposicion que corresponden a los
//! precios que se pasan como parámetros.
Codigos CodigosObra::FiltraPrecios(const regBC3_d &descomp,const Codigos &precios) const
{
    Codigos retval;
    for(size_t i= 0; i<descomp.size(); i++)
    {
        Codigos::const_iterator p= precios.find(descomp[i].codigo);
        if( (p!=precios.end()) ) //Encontró el precio
            retval[(*p).first]= (*p).second;
    }
    return retval;
}

//! @brief Devuelve los registros correspondientes a mediciones.
const Codigos &CodigosObra::GetDatosMeds(void) const
{
    return mediciones;
}

void CodigosObra::BorraElementales(const Codigos &els)
{
    elementos.Borra(els);
}

void CodigosObra::BorraDescompuestos(const Codigos &uds)
{
    udsobr.Borra(uds);
}

std::ostream &operator<<(std::ostream &os,const CodigosObra &co)
{
    os << "Obra: " << std::endl << co.GetDatosObra() << std::endl
       << "Capítulos: " << std::endl << co.caps << std::endl
       << "Elementos:" << std::endl << co.elementos << std::endl
       << "Descompuestos:" << std::endl << co.udsobr << std::endl
       << "Mediciones:" << std::endl << co.mediciones << std::endl
       << "Quedan: " << std::endl << co.resto << std::endl;
    return os;
}
