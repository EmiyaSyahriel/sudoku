#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "sudoku.h"

void splsh_start();
void board_start();
void mmenu_start();
void gmend_start();

void splsh_update(double time);
void board_update(double time);
void mmenu_update(double time);
void gmend_update(double time);

void splsh_end();
void board_end();
void mmenu_end();
void gmend_end();

void splsh_kdn(int key);
void board_kdn(int key);
void mmenu_kdn(int key);
void gmend_kdn(int key);

#endif