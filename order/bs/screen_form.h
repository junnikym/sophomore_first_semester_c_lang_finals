#ifndef SCREEN_FORM_H
#define SCREEN_FORM_H

typedef enum __SCREEN_ITEM_FLAGS__ {
	/* ... 추가 */
} SCREEN_ITME_FLAGS;

typedef struct _SCREEN_ITEM_ {
	/* ... 추가 */
} SCREEN_ITEM;

typedef struct _SCREEN_FORM_ {
	/* ... 추가 */
} SCREEN_FORM;

void append_screen_item ( SCREEN_FORM* target_form, SCREEN_ITEM append_item );

void load_screen_item ( const SCREEN_FORM* form );

#endif