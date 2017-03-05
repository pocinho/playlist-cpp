/*
* AUTOR: Paulo Pocinho
* DESDE: 05-03-2017
*/

#pragma once

#include "Musica.h"
#include "Player.h"
#include "Playlist.h"

void escreve_menu();
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
void pausa();
void GerarDadosTeste(Player& player);