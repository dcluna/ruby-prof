/* Copyright (C) 2005-2011 Shugo Maeda <shugo@ruby-lang.org> and Charlie Savage <cfis@savagexi.com>
   Please see the LICENSE file for copyright and distribution information */

#ifndef __RP_CALL_INFO_H__
#define __RP_CALL_INFO_H__

#include "rp_measurement.h"
#include "rp_method_info.h"

extern VALUE cCallInfo;

/* Callers and callee information for a method. */
typedef struct prof_call_info_t {
    prof_method_t *target; /* Use target instead of method to avoid conflict with Ruby method */
    struct prof_call_info_t *parent;
    st_table *call_infos;
    int called;
    prof_measure_t total_time;
    prof_measure_t self_time;
    prof_measure_t wait_time;
    int line;
    VALUE object;
    VALUE children;
} prof_call_info_t;

/* Array of call_info objects */
typedef struct prof_call_infos_t {
    prof_call_info_t **start;
    prof_call_info_t **end;
    prof_call_info_t **ptr;
    VALUE object;
} prof_call_infos_t;


void rp_init_call_info(void);
prof_call_infos_t* prof_call_infos_create();
void prof_call_infos_free(prof_call_infos_t *call_infos);
void prof_add_call_info(prof_call_infos_t *call_infos, prof_call_info_t *call_info);
VALUE prof_call_infos_wrap(prof_call_infos_t *call_infos);
prof_call_info_t * prof_call_info_create(prof_method_t* method, prof_call_info_t* parent);
prof_call_info_t * call_info_table_lookup(st_table *table, const prof_method_key_t *key);
size_t call_info_table_insert(st_table *table, const prof_method_key_t *key, prof_call_info_t *val);

#endif //__RP_CALL_INFO_H__
