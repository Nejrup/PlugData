/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <z_libpd.h>

void libpd_multi_init(void);
void libpd_init_else(void);
void libpd_init_cyclone(void);
void libpd_init_pdlua(const char *datadir, char *vers, int vers_len);

typedef void (*t_libpd_multi_banghook)(void* ptr, char const* recv);
typedef void (*t_libpd_multi_floathook)(void* ptr, char const* recv, float f);
typedef void (*t_libpd_multi_symbolhook)(void* ptr, char const* recv, char const* s);
typedef void (*t_libpd_multi_listhook)(void* ptr, char const* recv, int argc, t_atom* argv);
typedef void (*t_libpd_multi_messagehook)(void* ptr, char const* recv, char const* msg, int argc, t_atom* argv);

void* libpd_multi_receiver_new(void* ptr, char const* s,
    t_libpd_multi_banghook hook_bang,
    t_libpd_multi_floathook hook_float,
    t_libpd_multi_symbolhook hook_symbol,
    t_libpd_multi_listhook hook_list,
    t_libpd_multi_messagehook hook_message);

typedef void (*t_libpd_multi_noteonhook)(void* ptr, int channel, int pitch, int velocity);
typedef void (*t_libpd_multi_controlchangehook)(void* ptr, int channel, int controller, int value);
typedef void (*t_libpd_multi_programchangehook)(void* ptr, int channel, int value);
typedef void (*t_libpd_multi_pitchbendhook)(void* ptr, int channel, int value);
typedef void (*t_libpd_multi_aftertouchhook)(void* ptr, int channel, int value);
typedef void (*t_libpd_multi_polyaftertouchhook)(void* ptr, int channel, int pitch, int value);
typedef void (*t_libpd_multi_midibytehook)(void* ptr, int port, int byte);

void* libpd_multi_midi_new(void* ptr,
    t_libpd_multi_noteonhook hook_noteon,
    t_libpd_multi_controlchangehook hook_controlchange,
    t_libpd_multi_programchangehook hook_programchange,
    t_libpd_multi_pitchbendhook hook_pitchbend,
    t_libpd_multi_aftertouchhook hook_aftertouch,
    t_libpd_multi_polyaftertouchhook hook_polyaftertouch,
    t_libpd_multi_midibytehook hook_midibyte);

typedef void (*t_libpd_multi_printhook)(void* ptr, char const* recv);

void* libpd_multi_print_new(void* ptr, t_libpd_multi_printhook hook_print);


struct t_namelist;

int parse_startup_arguments(char const** args, size_t argc, t_namelist** sys_openlist, t_namelist** sys_messagelist);

#ifdef __cplusplus
}
#endif
