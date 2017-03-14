/*
 *  File:       Playlist\Musica.h
 *
 *  Abstract:   Header file for the class Musica.
 *
 *  Created:    2017-03-05 by Paulo Pocinho
 *
 *  Updated:    2017-03-13 by Paulo Pocinho
 *
 *  LICENSE:    Copyright (c) 2017 Paulo Pocinho
 *              See accompanying file LICENSE.txt
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