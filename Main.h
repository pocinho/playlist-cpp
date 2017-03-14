/*
 *  File:       Playlist\Main.h
 *
 *  Abstract:   Header file for the main program entry.
 *
 *  Created:    2017-03-05 by Paulo Pocinho
 *
 *  Updated:    2017-03-13 by Paulo Pocinho
 *
 *  LICENSE:    Copyright (c) 2017 Paulo Pocinho
 *              See accompanying file LICENSE.txt
 */

#ifndef PLAYLIST_CPP_MAIN_H_
#define	PLAYLIST_CPP_MAIN_H_

#pragma once

#include "Player.h"

void Menu();
void CriarPlaylist(Player& player);
void CriarMusica(Player& player);
void RemoverPlaylist(Player& player);
void RemoverMusica(Player& player);
void ListarPlaylists(Player& player);
void ConsultarPlaylist(Player& player);
void ConsultarMusica(Player& player);
void AlterarPlaylist(Player& player);
void AlterarMusica(Player& player);
void ReordenarPlaylist(Player& player);
void AlocarMusica(Player& player);
void Pausa();
void GerarDadosTeste(Player& player);
void TocarMusica(Player& player);

#endif // !PLAYLIST_CPP_MAIN_H_