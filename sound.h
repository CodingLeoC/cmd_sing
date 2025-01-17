#pragma once

#include "types.h"

bool vsk_sound_init(void);
void vsk_sound_exit(void);
bool vsk_sound_is_playing(void);
bool vsk_sound_wait(VskDword milliseconds);
void vsk_sound_stop(void);
void vsk_sound_beep(int i);
bool vsk_sound_is_beeping(void);
const char *vsk_get_openal_error(int error);
void vsk_print_openal_error(int error);

enum VSK_SOUND_ERR
{
    VSK_SOUND_ERR_SUCCESS = 0,
    VSK_SOUND_ERR_ILLEGAL,
    VSK_SOUND_ERR_IO_ERROR,
};

VSK_SOUND_ERR vsk_sound_cmd_sing(const char *str);
VSK_SOUND_ERR vsk_sound_cmd_sing(const wchar_t *str);
VSK_SOUND_ERR vsk_sound_cmd_sing_save(const char *str, const wchar_t *filename);
VSK_SOUND_ERR vsk_sound_cmd_sing_save(const wchar_t *wstr, const wchar_t *filename);
bool vsk_sound_voice_reg(int addr, int data);
