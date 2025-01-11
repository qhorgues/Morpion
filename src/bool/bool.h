#ifndef BOOL_H_INCLUDED
#define BOOL_H_INCLUDED

typedef _Bool bool;
enum bool
{
    false,
    true
};

#endif // !BOOL_H_INCLUDED

#ifdef TAB_BOOL
#ifndef TAB_BOOL_INCLUDED
#define TAB_BOOL_INCLUDED
typedef uint8_t tabBool;
bool get_tabBool(const tabBool tab, const int position);
tabBool set_tabBool(tabBool tab, const int position, const bool value);
#endif // !TAB_BOOL_INCLUDED
#endif // TAB_BOOL