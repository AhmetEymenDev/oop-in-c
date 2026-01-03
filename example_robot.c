/* 
 * Copyright (c) 2026 Ahmet Eymen
 * This file is part of OOC Framework.
 * Licensed under the MIT License.
 */
#include "ooc.h"

// --- STEP 1: CLASS DEFINATIONS ---
// Base Class: Entity
// Every object in our engine starts here.
class(Entity)
    int id;
end_class(Entity) {
    method(void, Entity, dtor);          // Destructor
    method(void, Entity, Update);        // Virtual Method
};

// Derived Class: Robot
// Robot inherits from Entity (Inheritance)
class(Robot)
    extends(Entity);
    int battery_level;
end_class(Robot) {
    method(void, Robot, dtor);
    method(void, Robot, Update); // Overriding base method
};


// --- STEP 2: FORWARD DECLARATIONS ---
void Entity_dtor(Entity* this);
void Entity_Update(Entity* this);
void Robot_dtor(Robot* this);
void Robot_Update(Robot* this);


// STEP 3: VTABLE FUNCTIONS
void* Entity_get_vtable() {
    static Entity_vtable vt = {
        .dtor = Entity_dtor, .Update = Entity_Update
    }; // VTable storage
    return &vt;
}


// --- STEP 4: CONSTRUCTORS ---
// Entity Constructor
Entity* Entity_ctor(Entity* this, int id) {
    static Entity_vtable vt = { .dtor = Entity_dtor, .Update = Entity_Update };
    this->vptr = &vt;
    this->id = id;
    return this;
}


// Robot Constructor
Robot* Robot_ctor(Robot* this, int id, int battery) {
    static Robot_vtable vt = { .dtor = Robot_dtor, .Update = Robot_Update };
    this->vptr = &vt;
    this->base.id = id;
    this->battery_level = battery;
    return this;
}


// --- STEP 5: METHOD DEFINATIONS ---
// Entity Class Methods
def_method(void, Entity, Update) {
    printf("[Entity %d] Logic updating...\n", this->id);
}

def_method(void, Entity, dtor) {
    printf("[Entity %d] Memory released.\n", this->id);
}

// Robot Class Methods
def_method(void, Robot, Update) {
    // Calling base method (C# base.Update())
    base_call(Entity, this, Update); 
    printf("[Robot] Battery: %d%% - Scanning environment...\n", this->battery_level);
}

def_method(void, Robot, dtor) {
    printf("[Robot] Battery system safely shutdown.\n");
    base_call(Entity, this, dtor); // Clean up base parts
}


// --- STEP 6: MAIN ENGINE LOOP ---
int main() {
    // Creating a Robot using our 'new' macro
    Robot* myRobot = new(Robot, 101, 85);

    printf("--- RUNNING LOGIC ---\n");
    invoke(myRobot, Update); // Method invocation with injected 'this'

    printf("--- CLEANUP ---\n");
    clear_ram(myRobot); // Safe memory management

    return 0;
}