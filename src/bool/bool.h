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
typedef unsigned char tabBool;
bool get_tabBool(const tabBool tab, const int position);
tabBool set_tabBool(tabBool tab, const int position, const bool value);
#endif // !TAB_BOOL_INCLUDED
#endif // TAB_BOOL

#ifdef LONG_TAB_BOOL
#ifndef LONG_TAB_BOOL_INCLUDED
#define LONG_TAB_BOOL_INCLUDED
typedef unsigned int long_tabBool;
bool get_long_tabBool(const long_tabBool tab, const int position);
long_tabBool set_long_tabBool(long_tabBool tab, const int position, const bool value);
#endif // !LONG_TAB_BOOL_INCLUDED
#endif // LONG_TAB_BOOL



