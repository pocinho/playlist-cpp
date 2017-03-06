/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
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

#endif // !PLAYLIST_CPP_MAIN_H_