/* * OOC.H - Object Oriented C Framework
 * Created by Ahmet Eymen - 2026
 * Inspired by C# discipline and C performance.
 * * This framework implements Classes, Inheritance, VTables, 
 * and Destructors in pure C.
 *
 * Copyright (c) 2026 Ahmet Eymen
 * This file is part of OOC Framework.
 * Licensed under the MIT License.
 */

#ifndef OOC_H
#define OOC_H

#include <stdio.h>
#include <stdlib.h>

// --- MACRO ENGINE ---

// Defines a new class and its Virtual Table (VTable)
#define class(name) \
    typedef struct name name; \
    typedef struct name##_vtable name##_vtable; \
    struct name##_vtable; \
    struct name { name##_vtable *vptr;

// Closes the class structure and starts the VTable definition
#define end_class(name) }; \
    struct name##_vtable

// Implementation for Inheritance (Memory Alignment)
#define extends(base_type) base_type base

// Method definition for VTable
#define method(res, type, name, ...) res (*name)(type* this, ##__VA_ARGS__)

// Method implementation wrapper - Automatically injects 'this' pointer
#define def_method(res, type, name, ...) \
    res type##_##name(type* this, ##__VA_ARGS__)

// --- OBJECT MANAGEMENT ---

// C# style object creation (Allocates memory + Calls constructor)
#define new(type, ...) type##_ctor((type*)malloc(sizeof(type)), ##__VA_ARGS__)

// C# style method call: obj->Method(args)
#define invoke(obj, func, ...) obj->vptr->func(obj, ##__VA_ARGS__)

// Calls base class method (C# base.Method() equivalent)
#define base_call(base_type, obj, func, ...) \
    ((base_type##_vtable*)base_type##_get_vtable())->func((base_type*)obj, ##__VA_ARGS__)

// Destroys object and triggers the custom destructor (dtor)
#define clear_ram(obj) \
    if(obj->vptr->dtor) obj->vptr->dtor(obj); \
    free(obj);

#endif
