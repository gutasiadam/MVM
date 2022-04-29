#ifndef TARIIFS_H
#define TARIIFS_H
/**
 * \file Tariffs.h
 *
 * Ez a fájl tartalmazza a Tariffs osztály deklarációját és inline függvényeit.
 */


class Tariffs{
    private:
        static double VAT;
        static double residental;
        static double corporate;
        static double usage_fee;
    public:
        Tariffs();

        double getVAT();
        double getResidental();
        double getCorporate();
        double get_usage_fee();
};
#endif