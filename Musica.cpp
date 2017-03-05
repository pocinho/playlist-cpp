/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#include <string>
#include "Musica.h"

using namespace std;

Musica::Musica(std::string titulo, std::string autor, std::string estilo, int ano, double duracao) :
	titulo_(titulo), autor_(autor), estilo_(estilo), ano_(ano), duracao_(duracao)
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
