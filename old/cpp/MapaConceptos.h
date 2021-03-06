//MapaConceptos.h

#ifndef MAPACONCEPTOS_H
#define MAPACONCEPTOS_H

#include <map>
#include "EntPpl.h"

template<class T>
class MapaClaves: public std::map<std::string,T *>
{
};

template<class T>
class MapaConceptos: public std::map<std::string,T>, public EntPpl
{
public:
    typedef std::map<std::string,T> map_ccpto;
    typedef MapaClaves<T> map_claves;

    typedef typename map_ccpto::iterator iterator;
    typedef typename map_ccpto::const_iterator const_iterator;
    typedef typename MapaClaves<T>::iterator claves_iterator;
    typedef typename MapaClaves<T>::const_iterator claves_const_iterator;
private:
    static map_claves claves;
protected:
    virtual void err_no_encontrado(const std::string &cod) const;
public:

    void Agrega(const T &u)
    {
        claves[u.Codigo()]= &((*this)[u.Codigo()]= u);
    }
    T *Busca(const std::string &cod);
    const T *Busca(const std::string &cod) const;
    void EscribeBC3(std::ostream &os) const;
    void Escribe(std::ostream &os) const;
    virtual ~MapaConceptos(void) {}
};

template<class T>
MapaClaves<T> MapaConceptos<T>::claves;

template<class T>
void MapaConceptos<T>::err_no_encontrado(const std::string &cod) const
{
    std::cerr << "Concepto: " << cod
              << " no encontrado" << std::endl;
}
template<class T>
T *MapaConceptos<T>::Busca(const std::string &cod)
{
    claves_iterator i= claves.find(cod);
    if(i==claves.end())
    {
        //err_no_encontrado(cod);
        return NULL;
    }
    return ((*i).second);
}
template<class T>
const T *MapaConceptos<T>::Busca(const std::string &cod) const
{
    claves_const_iterator i= claves.find(cod);
    if(i==claves.end())
    {
        //err_no_encontrado(cod);
        return NULL;
    }
    return ((*i).second);
}
template<class T>
void MapaConceptos<T>::EscribeBC3(std::ostream &os) const
{
    const_iterator j= MapaConceptos<T>::begin();
    for(; j!=MapaConceptos<T>::end(); j++)
        (*j).second.EscribeBC3(os);
}
template<class T>
void MapaConceptos<T>::Escribe(std::ostream &os) const
{
    const_iterator i;
    for(i= MapaConceptos<T>::begin(); i!=MapaConceptos<T>::end(); i++)
        (*i).second.Escribe(os);
}
#endif
