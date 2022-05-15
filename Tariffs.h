#ifndef TARIIFS_H
#define TARIIFS_H
/**
 * @brief Ez a fájl tartalmazza a tarifákat tartalmazó Tariffs osztály deklarációit
 * 
 */


class Tariffs{
    public:
        static double residental_16; /**< Lakossági | 16A */
        static double residental_32; /**< Lakossági | 32A */
        static double corporate_2ph_32; /**< Vállalati | 2 fázis | 32A */
        static double corporate_2ph_63; /**< Vállalati | 2 fázis | 63A */
        static double corporate_2ph_128; /**< Vállalati | 2 fázis | 128A */
        static double corporate_3ph_32; /**< Vállalati | 3 fázis | 32A */
        static double corporate_3ph_63; /**< Vállalati | 3 fázis | 63A */
        static double corporate_3ph_128;/**< Vállalati | 2 fázis | 128A */
        static double usage_fee;
};
#endif
