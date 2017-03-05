/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#pragma once

#include "Musica.h"
#include "Playlist.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void AdicionarPlaylist(std::string nome);
	void AdicionarMusica(int playlist, Musica musica);
	void RemoverPlaylist(int posicao);
	void RemoverMusica(int playlist, int musica);
	void AlocarMusica(int playlist_origem, int musica, int playlist_destino);
	void ReordenarPlaylist(int playlist, int musica_origem, int musica_destino);
	std::string ListarPlaylists();
	std::string ListarMusicas(int playlist);
	std::string ConsultarPlaylist(int posicao);
	std::string ConsultarMusica(int playlist, int musica);
	void AlterarPlaylist(int playlist, std::string nome);
	void AlterarMusica(int playlist, int posicao, Musica musica);

private:
	std::vector<Playlist> lista_;
};

