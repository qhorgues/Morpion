#include <stdio.h>
#include "bool.h"
#include <math.h>
typedef uint_fast8_t tabBool;
typedef uint_fast32_t long_tabBool;

int_fast32_t powi(const int_fast32_t value, int_fast32_t power)
{
    if (power >= 0)
    {
        if (power == 0)
        {
            return 1;
        }
        int_fast32_t curentValue = value;
        while (power > 1)
        {
            curentValue *= value;
            power--;
        }
        return curentValue;
    }
    return -1;
}

/**
 * \brief Obtenir un element du tableau de booleen
 * 
 * \param tab Le tableau de booleen
 * \param position La position dans le tableau
 * \return true ou false
 */
bool get_tabBool(const tabBool tab, const int_fast32_t position)
{
    if ((tab & powi(2, position)) != 0)
    {
        return true;
    }
    return false;
}

/**
 * \brief Changer un element du tableau de booleen
 * 
 * \param tab Le tableau de booleen
 * \param position La position dans le tableau
 * \param value la nouvelle valeur du booleen
 * \return Le tableau modifie
 */
tabBool set_tabBool(tabBool tab, const int_fast32_t position, const bool value)
{
    if (get_tabBool(tab, position) == value)
    {
        return tab;
    }

    if (value)
    {
        tab += powi(2, position);
    }
    else
    {
        tab -= powi(2, position);
    }
    return tab;
}

int_fast32_t long_powi(const int_fast32_t value, int_fast32_t power)
{
    if (power >= 0)
    {
        if (power == 0)
        {
            return 1;
        }
        int_fast32_t curentValue = value;
        while (power > 1)
        {
            curentValue *= value;
            power--;
        }
        return value;
    }
    return -1;
}

bool get_long_tabBool(const long_tabBool tab, const int_fast32_t position)
{
    if ((tab & long_powi(2, position)) != 0)
    {
        return true;
    }
    return false;
}

long_tabBool set_long_tabBool(long_tabBool tab, const int_fast32_t position, const bool value)
{
    if (get_tabBool(tab, position) == value)
    {
        return tab;
    }

    if (value)
    {
        tab += long_powi(2, position);
    }
    else
    {
        tab -= long_powi(2, position);
    }
    return tab;
}