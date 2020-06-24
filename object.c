#include "object.h"


void copy_box ( BOX* lhs, BOX* rhs ) {
	*(BOX*)lhs = *(BOX*)rhs;
}

void copy_circle ( CIRCLE* lhs, CIRCLE* rhs ) {
	*(CIRCLE*)lhs = *(CIRCLE*)rhs;
}

// ------------------------------------------------------- //
// ----- object functions	------------------------------

void init_obj ( OBJECT* obj ) {
	dyn_arr_init( &(obj->entities), sizeof(ENTITY) );
	obj->center = NULL;

	dyn_arr_init ( &(obj->collision_box), sizeof ( BOX ) );
	dyn_arr_init ( &(obj->collision_circle), sizeof ( CIRCLE ) );

	obj->collision_indicator = 0;
	
	obj->head_for = V2_ZERO;
} 

void copy_obj( void* lhs, const void* rhs) {
	if(rhs == NULL) 
		init_obj( (OBJECT*)lhs );
	else
		*(OBJECT*)lhs = *(OBJECT*)rhs;
}

void release_obj ( OBJECT* obj ) {
	int i = 0;
	ENTITY* ent_converter = (ENTITY*)(obj->entities.items);

	for( i = 0; i <= obj->entities.size; i++) {
		release_ent( &ent_converter[i] );
	}

	dyn_arr_release ( &(obj->collision_box) );
	dyn_arr_release ( &(obj->collision_circle) );

	dyn_arr_release( &obj->entities );

	obj->center = NULL;
}

void draw_obj(OBJECT* obj, int fixed) {
	int i = 0;
	ENTITY* ent = NULL;
	VEC2 temp_pos = V2_ZERO;

	if (obj->center == NULL) {
		for (i = 0; i <= obj->entities.size; i++) 
			draw_ent(dyn_arr_get(&obj->entities, i));
		
		return;
	}

	for (i = 0; i <= obj->entities.size; i++) {
		ent = dyn_arr_get(&obj->entities, i);

		if (ent == obj->center) {
			if (fixed == 0)
				draw_ent(ent);
			else
				fixed_draw_ent(ent);
		}
		else {
			temp_pos = ent->position;
			vec2_add_assn(&ent->position, &(obj->center->position));

			if (fixed == 0)
				draw_ent(ent);
			else
				fixed_draw_ent(ent);

			ent->position = temp_pos;
		}
	}
}

void adapt_each_f_obj (void* elem, int i, void* msger) {
	MOMENTUM ent_momentum = pass_by_f_ent ( elem );
	
	((OBJECT*)msger)->center->angle += ent_momentum.angle;
	
	vec2_add_assn (
		&((OBJECT*)msger)->center->position,
		&(ent_momentum.vector)
	);
	
	((OBJECT*)msger)->head_for = ent_momentum.vector;
}

void update_obj ( OBJECT* obj ) {
	MOMENTUM_PTR info_msger = {
		&(obj->center->position),
		&(obj->center->angle)
	};
	
	dyn_arr_foreach(&obj->entities, obj, adapt_each_f_obj);

	draw_obj(obj, 0);
}

// -- setting function

void* set_center_obj ( OBJECT* obj, int index ) {
	if (obj->center != NULL) {
		// !TODO : detech_center_obj();
	}
	void* a = dyn_arr_get(&obj->entities, index);
	
	return (obj->center = a);
}

void detech_center_obj ( OBJECT* obj ) {
	
}

// -- collision function

int obj_is_collision ( OBJECT* lhs, OBJECT* rhs ) {
	int indicator = 0;
	int lhs_i = 0, rhs_i = 0;
	BOX lhs_box = {V2_ZERO, V2_ZERO}, rhs_box = {V2_ZERO, V2_ZERO};
	CIRCLE lhs_circle = {V2_ZERO, 0.0}, rhs_circle = {V2_ZERO, 0.0};
	
	if(lhs == NULL || rhs == NULL )	return -1;
	
	if(	( lhs->collision_box.size == -1 && lhs->collision_circle.size == -1 ) ||
		( rhs->collision_box.size == -1 && rhs->collision_circle.size == -1 ) ) {
		return -1;
	}
	
	for( lhs_i = 0; lhs_i <= lhs->collision_box.size; lhs_i++ ) {
		lhs_box = *(BOX*)dyn_arr_get( &(lhs->collision_box), lhs_i );
		vec2_add_assn ( &lhs_box.position, &lhs->center->position );
		
		// ( Box and Box )
		for( rhs_i = 0; rhs_i <= rhs->collision_box.size; rhs_i++ ) {
			rhs_box = *(BOX*)dyn_arr_get( &(rhs->collision_box), rhs_i );
			vec2_add_assn ( &rhs_box.position, &rhs->center->position );
			
			indicator |= collision_detection_obb (
				&lhs_box.position,
				&lhs_box.size,
				&lhs->center->angle,
				&rhs_box.position,
				&rhs_box.size,
				&rhs->center->angle
			);
		}
		
		// ( Box and Circle )
		/*
		for( rhs_i = 0; rhs_i <= rhs->collision_circle.size; rhs_i++ ) {
			rhs_circle = *(CIRCLE*)dyn_arr_get( &(rhs->collision_circle), rhs_i );
			vec2_add_assn ( &rhs_circle.position, &rhs->center->position );
			
			
		}
		*/
	}
	
	
	return indicator;
}
