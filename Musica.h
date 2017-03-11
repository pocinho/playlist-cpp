/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#ifndef PLAYLIST_CPP_MUSICA_H_
#define PLAYLIST_CPP_MUSICA_H_

#pragma once

#include <string>

class Musica
{
public:
	Musica() = delete;
	Musica(std::string titulo, std::string autor, std::string estilo, int ano, double duracao, std::string ficheiro);
	virtual ~Musica();

	std::string GetTitulo();
	std::string GetAutor();
	std::string GetEstilo();
	int GetAno();
	double GetDuracao();
	std::string GetFicheiro();

private:
	std::string titulo_;
	std::string autor_;
	std::string estilo_;
	int ano_;
	double duracao_;
	std::string ficheiro_;
};

#endif // !PLAYLIST_CPP_MUSICA_H_