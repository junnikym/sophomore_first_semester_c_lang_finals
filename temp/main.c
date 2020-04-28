#include "object.h"

void print_dyn_arr_force ( DYN_ARR* a ) {
	int i = 0;
	FORCE* result = (FORCE*)a->items;

	printf("\tforce [size : %d] : ----------\n", a->size);
	for (i = 0; i <= dyn_arr_size(a); i++) {
        printf("\t%d : (%f, %f) (%p) \n", i, result[i].force_vec.x, result[i].force_vec.y, &result[i]);
	}

    printf("\n");
}

void print_dyn_arr_ent_f ( DYN_ARR* a ) {
	int i = 0;
	ENTITY* ent = (ENTITY*)a->items;

	for(i = 0; i <= dyn_arr_size(a); i++) {
		printf("entity [%d] : --------------------\n", i);
		print_dyn_arr_force( ent[i].forces );
		printf("\n");
	}
}

int main() {
	int i = 0;
	DYN_ARR v;
	OBJECT* obj_converter = NULL;

	dyn_arr_init(&v, sizeof(OBJECT));
	printf("init_complate \n");

	dyn_arr_push_back(&v, NULL, copy_obj);
	dyn_arr_push_back(&v, NULL, copy_obj);
	dyn_arr_push_back(&v, NULL, copy_obj);
	dyn_arr_push_back(&v, NULL, copy_obj);
	printf("pushed_elems \n");

	printf("entity DYN_ARR size : %d \n ", v.size);

	//print_dyn_arr_ent_f(&v);

	//----- release memeory ---------------
	obj_converter = (OBJECT*)v.items;
	for( i = 0; i < v.capacity; i++) {
		release_obj( &obj_converter[i] );
	}
	obj_converter = NULL;

	dyn_arr_release( &v );

	return 0;
}