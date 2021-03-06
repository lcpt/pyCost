//Obra.h

#ifndef OBRA_H
#define OBRA_H

#include "Capitulo.h"
#include "Porcentajes.h"

class CodigoObra;
class Codigos;

class Obra: public Capitulo
{
private:
    Porcentajes porcentajes;

    inline virtual std::string getClassName(void) const
    {
        return "Obra";
    }
public:
    Obra(const std::string &cod="ObraSinCod",const std::string &tit="ObraSinTit");
    virtual std::string CodigoBC3(void) const;

    void AgregaCapitulo(const std::string &cap_padre,const Capitulo &cap);
    void AgregaPartida(const std::string &cap_padre,const Partida &m);

    void LeeBC3DatosObra(const Codigos &obra);
    void EscribeSpre(void) const
    {
        precios.EscribeSpre();
        std::cerr << "Exportación de capítulos no implementada." << std::endl;
    }
    void EscribeBC3(std::ostream &os,const std::string pos="") const;
    void LeeMedicSpre(std::istream &is);
    void LeeSpre(std::istream &is);
    Capitulo *BuscaCapituloMedicion(regBC3_ruta &ruta);
    void LeeBC3Mediciones(const CodigosObra &co);
    void LeeBC3(std::istream &is);

    void ImprLtxPresEjecMat(std::ostream &os) const;
    void ImprLtxPresContrata(std::ostream &os) const;
    void ImprLtxPresGen(std::ostream &os) const;
    void ImprLtxMed(std::ostream &os) const;
    void ImprCompLtxMed(const Obra &otra,std::ostream &os) const;
    void ImprLtxCP1(std::ostream &os) const;
    void ImprLtxCP2(std::ostream &os) const;
    void ImprLtxJustPre(std::ostream &os) const;
    void ImprLtxCP(std::ostream &os) const;
    void ImprLtxPreParc(std::ostream &os) const;
    void ImprCompLtxPreParc(const Obra &otra,std::ostream &os) const;
    void ImprLtxResumen(std::ostream &os) const;
    void ImprCompLtx(const Obra &otra,std::ostream &os) const;
    void ImprLtx(std::ostream &os) const;
    void ImprLtxInformeObra(std::ostream &os) const;

    void EscribeHCalc(std::ostream &os) const;
    void SimulaDescomp(const std::string &origen, const std::string &destino);
};
#endif
