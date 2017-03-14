/*
 *  File:       Playlist\Musica.cpp
 *
 *  Abstract:   Class Musica stores music information.
 *
 *  Created:    2017-03-05 by Paulo Pocinho
 *
 *  Updated:    2017-03-13 by Paulo Pocinho
 *
 *  LICENSE:    Copyright (c) 2017 Paulo Pocinho
 *              See accompanying file LICENSE.txt
 */

#include <string>

#include "Musica.h"

using namespace std;

Musica::Musica(std::string titulo, std::string autor, std::string estilo, int ano, double duracao, std::string ficheiro) :
	titulo_(titulo), autor_(autor), estilo_(estilo), ano_(ano), duracao_(duracao), ficheiro_(ficheiro)
{
}

Musica::~Musica()
{
}

std::string Musica::GetTitulo()
{
	return titulo_;
}

std::string Musica::GetAutor()
{
	return autor_;
}

std::string Musica::GetEstilo()
{
	return estilo_;
}

int Musica::GetAno()
{
	return ano_;
}

double Musica::GetDuracao()
{
	return duracao_;
}

std::string Musica::GetFicheiro()
{
	return ficheiro_;
}
