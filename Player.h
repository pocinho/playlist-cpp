/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#ifndef PLAYLIST_CPP_PLAYER_H_
#define PLAYLIST_CPP_PLAYER_H_

#pragma once

#include <string>
#include <vector>

#include <SQLiteCpp/SQLiteCpp.h>

#include "Musica.h"
#include "Playlist.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void InicializarDB();
	void AdicionarPlaylist(std::string nome);
	void AdicionarMusica(std::vector<int>::size_type playlist, Musica musica);
	void RemoverPlaylist(std::vector<int>::size_type posicao);
	void RemoverMusica(std::vector<int>::size_type playlist, std::vector<int>::size_type musica);
	void AlocarMusica(std::vector<int>::size_type playlist_origem, std::vector<int>::size_type musica, std::vector<int>::size_type playlist_destino);
	void ReordenarPlaylist(std::vector<int>::size_type playlist, std::vector<int>::size_type musica_origem, std::vector<int>::size_type musica_destino);
	std::string ListarPlaylists();
	std::string ListarMusicas(std::vector<int>::size_type playlist);
	std::string ConsultarPlaylist(std::vector<int>::size_type posicao);
	std::string ConsultarMusica(std::vector<int>::size_type playlist, std::vector<int>::size_type musica);
	void AlterarPlaylist(std::vector<int>::size_type playlist, std::string nome);
	void AlterarMusica(std::vector<int>::size_type playlist, std::vector<int>::size_type posicao, Musica musica);
	void TocarMusica(std::vector<int>::size_type playlist, std::vector<int>::size_type posicao);

private:
	std::vector<Playlist> lista_;
	std::string db_name_;
	SQLite::Database db_;
};

#endif // !PLAYLIST_CPP_PLAYER_H_