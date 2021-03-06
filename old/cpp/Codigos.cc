//Codigos.cxx

#include "Codigos.h"
#include "boost/lexical_cast.hpp"

void Codigos::InsertaCods(const Codigos &cods)
{
    mapa::const_iterator i= cods.begin();
    for(; i!=cods.end(); i++)
        (*this)[(*i).first]= (*i).second;
}


//! @brief Devuelve los subcapítulos del capitulo que se pasa como parámetro.
Codigos Codigos::GetSubCaps(const RegBC3 &ppal) const
{
    Codigos retval;
    regBC3_d desc= ppal.GetDesc(); //Obtiene la descomposición
    for(regBC3_d::const_iterator i=desc.begin(); i!=desc.end(); i++)
    {
        std::string cod= (*i).codigo;
        if(es_codigo_capitulo(cod)) //Es un capítulo.
        {
            mapa::const_iterator j= BuscaCapitulo(cod);
            if(j!=end())
                retval[(*j).first]= (*j).second;
            else
                std::cerr << "Codigos::GetSubCaps; No se encontró el subcapítulo: " << cod << std::endl;
        }
        //else //partidas del capítulo
        //std::cerr << "subcapítulo raro: " << cod << std::endl;
    }
    return retval;
}
Codigos Codigos::GetSubCapitulos(const Codigos &cods) const
{
    Codigos retval;
    mapa::const_iterator i= cods.begin();
    for(; i!=cods.end(); i++)
        retval.InsertaCods(GetSubCaps((*i).second));
    return retval;
}
Codigos Codigos::GetSubElementos(const RegBC3 &ppal,const Codigos &elementos) const
//Devuelve los precios elementales del capitulo que se pasa como parámetro.
{
    Codigos retval;
    regBC3_d desc= ppal.GetDesc(); //Obtiene la descomposición
    for(regBC3_d::const_iterator i=desc.begin(); i!=desc.end(); i++)
    {
        std::string cod= (*i).codigo;
        if(!es_codigo_capitulo(cod)) //No es un capítulo.
        {
            mapa::const_iterator j= elementos.find(cod);
            if(j!=end())
                retval[(*j).first]= (*j).second;
        }
    }
    return retval;
}
Codigos Codigos::GetSubDescompuestos(const RegBC3 &ppal,const Codigos &descompuestos) const
//Devuelve los descompuestos del capitulo que se pasa como parámetro.
{
    Codigos retval;
    regBC3_d desc= ppal.GetDesc(); //Obtiene la descomposición
    for(regBC3_d::const_iterator i=desc.begin(); i!=desc.end(); i++)
    {
        std::string cod= (*i).codigo;
        if(!es_codigo_capitulo(cod)) //No es un capítulo.
        {
            mapa::const_iterator j= descompuestos.find(cod);
            if(j!=end())
                retval[(*j).first]= (*j).second;
        }
    }
    return retval;
}

void Codigos::InsertaReg(const std::string &str_reg,const int &verborrea,const int &cont_mediciones)
{
    StrTok strtk(str_reg);
    char tipo= (strtk.get_token('|'))[0];
    std::string cod= strtk.get_token('|');
    cod= q_car_d(cod,'\\'); //Quitamos la barra si está al final.

    if(tipo=='V' || tipo=='K' || tipo=='L' ||
            tipo=='A' || tipo=='G' || tipo=='E')
    {
        if(verborrea > 0)
            std::clog << "Se ignora el registro de tipo " << tipo << ".\n";
        return;
    }
    if(cod.length()<1) return;
    const std::string resto= strtk.resto();
    mapa::iterator i= find(cod);
    if(i==end())
    {
        i= find(cod+'#');
        if(i==end()) //El registro no es de capítulo.
        {
            i= find(cod+"##");
            if(i==end()) //El registro tampoco es de obra luego es nuevo.
            {
                if(tipo == 'M') //El registro corresponde a una medición.
                {
                    if(has_char(cod,'\\')) //A veces el registro ~M es de la forma: ~M|13.3.1#\01.009|1....
                        cod= copia_desde(cod,'\\'); //aquí le quitamod la parte 13.3.1#\ al código.
                    cod= boost::lexical_cast<std::string>(cont_mediciones) + '@' + cod;
                }
                (*this)[cod]= RegBC3(); //Lo damos de alta.
                i= find(cod);
            }
        }
    }
    switch(tipo)
    {
    case 'C':
        (*i).second.c= pc8TOlatin1(resto);
        break;
    case 'D':
        if(resto.length()<2)
        {
            if(verborrea>4) //No tiene porqué ser un error.
                std::cerr << "Descomposición vacía en concepto: \'" << cod
                          << "\' se ignora la descomposición." << std::endl;
        }
        else
            (*i).second.d= resto;
        break;
    case 'T':
        (*i).second.t= pc8TOlatin1(resto);
        break;
    case 'M':
        (*i).second.m= pc8TOlatin1(resto);
        break;
    case 'Y':
        (*i).second.y= resto;
        break;
    default:
        std::cerr << "Registro de tipo: " << tipo << " desconocido." << std::endl;
        break;
    }
}

//! @brief Devuelve el registro que corresponde a la obra.
Codigos Codigos::GetObra(void) const
{
    Codigos retval;
    mapa::const_iterator i= begin();
    for(; i!=end(); i++)
        if(EsObra(i))
            retval[(*i).first]= (*i).second;
    if(!retval.size())
        std::cerr << "No se encontró el capítulo raíz." << std::endl;
    return retval;
}

//! @brief Devuelve un iterador al capítulo con el código que se pasa como parámetro.
Codigos::const_iterator Codigos::BuscaCapitulo(const std::string &cod) const
{
    const_iterator retval= find(cod); //Código
    if(retval==end())
        retval= find(cod+'#');
    return retval;
}

//! @brief Devuelve verdadero si el registro corresponde a una medición.
bool Codigos::EsMedicion(mapa::const_iterator &i)
{
    return ((*i).second.EsMedicion());
}

//! @brief Devuelve el tipo de concepto al que corresponde el registro.
TipoConcepto Codigos::GetTipoConcepto(mapa::const_iterator &i)
{
    if(EsObra(i))
        return obra;
    else if(EsElemento(i))
        return elemento;
    else if(EsMedicion(i))
        return medicion;
    else if(EsDescompuesto(i))
        return descompuesto;
    else if(EsCapitulo(i))
        return capitulo;
    else
    {
        std::cerr << "No se encontró el tipo del concepto: '" << (*i).first << "'\n";
        return sin_tipo;
    }
}

//! @brief Devuelve una cadena de caracteres que identifica el
//! tipo de concepto al que corresponde el registro.
std::string Codigos::StrTipoConcepto(mapa::const_iterator &i)
{
    const TipoConcepto tipo= GetTipoConcepto(i);
    switch(tipo)
    {
    case obra:
        return "obra";
    case elemento:
        return "elemento";
    case medicion:
        return "medicion";
    case descompuesto:
        return "descompuesto";
    case capitulo:
        return "capitulo";
    case sin_tipo :
    default:
        return "sin_tipo";
    }
}


//! @brief Extrae las entidades que corresponden a capitulos
Codigos Codigos::GetCapitulos(void) const
{
    Codigos retval;
    mapa::const_iterator i= begin();
    for(; i!=end(); i++)
        if(EsCapitulo(i))
            retval[(*i).first]= (*i).second;
    std::clog << "  leídos " << retval.size() << " capítulos." << std::endl;
    return retval;
}

//! @brief Devuelve los códigos de los objetos del contenedor
std::set<std::string> Codigos::GetCodigos(void) const
{
    std::set<std::string> retval;
    mapa::const_iterator i= begin();
    for(; i!=end(); i++)
        retval.insert((*i).first);
    return retval;
}

//! @brief Extrae las entidades que corresponden a elementos
Codigos Codigos::GetElementos(void) const
{
    Codigos retval;
    mapa::const_iterator i= begin();
    for(; i!=end(); i++)
        if(EsElemento(i))
            retval[(*i).first]= (*i).second;
    std::clog << "  leídos " << retval.size() << " precios elementales." << std::endl;
    return retval;
}

//! @brief Extrae las entidades que corresponden a mediciones
Codigos Codigos::GetMediciones(void) const
{
    Codigos retval;
    mapa::const_iterator i= begin();
    for(; i!=end(); i++)
        if(EsMedicion(i))
            retval[(*i).first]= (*i).second;
    std::clog << "  leídas " << retval.size() << " mediciones." << std::endl;
    return retval;
}

//! @brief Extrae las entidades que corresponden a descompuestos
Codigos Codigos::GetDescompuestos(void) const
{
    Codigos retval;
    mapa::const_iterator i= begin();
    for(; i!=end(); i++)
        if(EsDescompuesto(i))
            retval[(*i).first]= (*i).second;
    std::clog << " leídos " << retval.size() << " precios descompuestos." << std::endl;
    return retval;
}

//! @brief Borra los elementos de this que estan en cods.
void Codigos::Borra(const Codigos &cods)
{
    mapa::const_iterator i= cods.begin();
    for(; i!=cods.end(); i++)
    {
        mapa::iterator j= find((*i).first);
        if(j!=end()) erase(j);
    }
}

//! @brief Extrae las entidades que corresponden a unidades de obra
Codigos Codigos::GetUdsObra(const Codigos &udsobra) const
{
    Codigos retval;
    mapa::const_iterator i= udsobra.begin();
    for(; i!=udsobra.end(); i++)
    {
        StrTok str((*i).first);
        std::string scap= str.get_token('\\');
        std::string codud= str.resto();
        mapa::const_iterator j= find(codud);
        if(j!=end())
            retval[(*j).first]= (*j).second;
        else
            std::cerr << "GetUdsObra: No se encontro la unidad: \'" << codud
                      << "\' de la medición: " << scap << std::endl;
    }
    return retval;
}

Codigos::reg_elemento Codigos::GetDatosElemento(const mapa::const_iterator &i) const
{
    return reg_elemento((*i).first,(*i).second.GetDatosElemento());
}

Codigos::reg_udobra Codigos::GetDatosUdObra(const mapa::const_iterator &i) const
{
    return reg_udobra((*i).first,(*i).second.GetDatosUdObra());
}

Codigos::reg_capitulo Codigos::GetDatosCapitulo(const mapa::const_iterator &i) const
{
    return reg_capitulo((*i).first,(*i).second.GetDatosCapitulo());
}

Codigos::reg_medicion Codigos::GetDatosMedicion(const mapa::const_iterator &i) const
{
    return reg_medicion((*i).first,(*i).second.GetDatosMedicion());
}

std::ostream &operator<<(std::ostream &os,const Codigos &cds)
{
    Codigos::mapa::const_iterator i= cds.begin();
    for(; i!=cds.end(); i++)
        os << "Código: " << (*i).first << std::endl
           << (*i).second << std::endl;
    return os;
}
