#ifndef SCREEN_COMMON_H
#define SCREEN_COMMON_H

#include "../opengl/control.h"

#include "press_any_key.h"

static void (*current_screen)( ) = NULL;

void init_screen();							// ȭ�� �ʱ�ȭ

void transe_screen (int screen_code );		// ��ũ�� �ڵ�� ���� ȭ�� ��ȯ

void run_current_screen();					// ȭ�� ����

#endif
