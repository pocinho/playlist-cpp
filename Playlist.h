/*
* AUTOR: Paulo Pocinho
* DESDE: 05-03-2017
*/

#pragma once

#include <vector>
#include "Musica.h"

class Playlist
{
public:
	Playlist() = delete;
	Playlist(std::string nome);
	virtual ~Playlist();

	void Adicionar(Musica musica);
	void Remover(int posicao);
	void Reordenar(int origem, int destino);
	Musica GetMusica(int posicao);
	std::string Listar();
	std::string Consultar(int posicao);
	std::string GetNome();
	std::vector<int>::size_type GetTotalMusicas();
	std::vector<int>::size_type GetCapacidade();
	void SetNome(std::string nome);
	void AlterarMusica(int posicao, Musica musica);

private:
	std::string nome_;
	std::vector<Musica> lista_;
};

