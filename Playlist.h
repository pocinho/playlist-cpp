/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#ifndef PLAYLIST_CPP_PLAYLIST_H_
#define PLAYLIST_CPP_PLAYLIST_H_

#pragma once

#include <string>
#include <vector>
#include "Musica.h"

class Playlist
{
public:
	Playlist() = delete;
	Playlist(std::string nome);
	virtual ~Playlist();

	void Adicionar(Musica musica);
	void Remover(std::vector<int>::size_type posicao);
	void Reordenar(std::vector<int>::size_type origem, std::vector<int>::size_type destino);
	Musica GetMusica(std::vector<int>::size_type posicao);
	std::string Listar();
	std::string Consultar(std::vector<int>::size_type posicao);
	std::string GetNome();
	std::vector<int>::size_type GetTotalMusicas();
	std::vector<int>::size_type GetCapacidade();
	void SetNome(std::string nome);
	void AlterarMusica(std::vector<int>::size_type posicao, Musica musica);
	bool HasObject(std::vector<int>::size_type musica);
	std::string GetFicheiro(std::vector<int>::size_type posicao);
	std::vector<Musica> GetLista();

private:
	std::string nome_;
	std::vector<Musica> lista_;
};

#endif // !PLAYLIST_CPP_PLAYLIST_H_