//CodigosObra.h

#ifndef CODIGOSOBRA_H
#define CODIGOSOBRA_H

#include "Codigos.h"

class CodigosObra
{
    Codigos caps; //capitulos.
    Codigos elementos;
    Codigos mediciones;
    Codigos udsobr;
    Codigos resto;
    static std::set<std::string> codigos_capitulos;
    void Trocea(const int &verborrea);
public:
    CodigosObra(void) {}
    bool ExisteConcepto(const std::string &cod) const;
    std::string StrTablaConcepto(const std::string &cod) const;
    Codigos::const_iterator BuscaConcepto(const std::string &cod) const;

    const Codigos &GetDatosElementos(void) const;
    const Codigos &GetDatosUnidades(void) const;
    const Codigos GetDatosObra(void) const;
    const Codigos &GetDatosCaps(void) const;
    const std::set<std::string> &GetCodigosCapitulos(void) const;

    Codigos::reg_capitulo GetDatosCapitulo(const Codigos::mapa::const_iterator &i) const;
    Codigos FiltraPrecios(const regBC3_d &descomp,const Codigos &precios) const;
    Codigos FiltraElementales(const regBC3_d &descomp) const;
    Codigos FiltraDescompuestos(const regBC3_d &descomp) const;

    const Codigos &GetDatosMeds(void) const;
    void BorraElementales(const Codigos &els);
    void BorraDescompuestos(const Codigos &uds);
    void LeeBC3(std::istream &is,const int &verborrea= 0);

    friend std::ostream &operator<<(std::ostream &os,const CodigosObra &co);
};

#endif
