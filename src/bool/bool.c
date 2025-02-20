#include <stdio.h>
#include "bool.h"
#include <math.h>
#include <stdint.h>

typedef uint8_t tabBool;


/**
 * \brief Obtenir un element du tableau de booleen
 * 
 * \param tab Le tableau de booleen
 * \param position La position dans le tableau
 * \return true ou false
 */
bool get_tabBool(const tabBool tab, const int position)
{
    return (tab & (1 << position)) != 0;
}

/**
 * \brief Changer un element du tableau de booleen
 * 
 * \param tab Le tableau de booleen
 * \param position La position dans le tableau
 * \param value la nouvelle valeur du booleen
 * \return Le tableau modifie
 */
tabBool set_tabBool(tabBool tab, const int position, const bool value)
{
    tab ^= (tabBool)((get_tabBool(tab, position) ^ value) << position);
    return tab;
}