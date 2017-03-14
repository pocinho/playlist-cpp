/*
 *  File:       Playlist\Playlist.cpp
 *
 *  Abstract:   Class Playlist stores and manages music objects.
 *
 *  Created:    2017-03-05 by Paulo Pocinho
 *
 *  Updated:    2017-03-13 by Paulo Pocinho
 *
 *  LICENSE:    Copyright (c) 2017 Paulo Pocinho
 *              See accompanying file LICENSE.txt
 */

#include <sstream>
#include <string>
#include <vector>

#include "Playlist.h"
#include "Musica.h"

using namespace std;

typedef std::vector<int>::size_type VecInt;

Playlist::Playlist(std::string nome) : nome_(nome)
{
}

Playlist::~Playlist()
{
}

void Playlist::Adicionar(Musica musica)
{
	lista_.push_back(musica);
}

void Playlist::Remover(VecInt posicao)
{
	VecInt pos = posicao - 1;
	lista_.erase(lista_.begin() + pos);
}

void Playlist::Reordenar(VecInt origem, VecInt destino)
{
	VecInt pos_origem = origem - 1;
	VecInt pos_destino = destino - 1;
	Musica musica = lista_[pos_origem];
	lista_[pos_origem] = lista_[pos_destino];
	lista_[pos_destino] = musica;
}

Musica Playlist::GetMusica(VecInt posicao)
{
	VecInt pos = posicao - 1;
	return lista_[pos];
}

string Playlist::Listar()
{
	stringstream lista;
	for (VecInt i = 0; i < lista_.size(); ++i)
	{
		lista << (i + 1) << ". " << lista_[i].GetTitulo() << "\n";
	}
	return lista.str();
}

string Playlist::Consultar(VecInt posicao)
{
	VecInt pos = posicao - 1;
	stringstream consulta;
	consulta << posicao << ". " << lista_[pos].GetTitulo() << "\n";
	consulta << "\nTitulo: " << lista_[pos].GetTitulo() << "\n";
	consulta << "Autor: " << lista_[pos].GetAutor() << "\n";
	consulta << "Estilo: " << lista_[pos].GetEstilo() << "\n";
	consulta << "Ano: " << lista_[pos].GetAno() << "\n";
	consulta << "Duracao: " << lista_[pos].GetDuracao() << "\n";
	consulta << "Ficheiro: " << lista_[pos].GetFicheiro() << "\n";
	return consulta.str();
}

string Playlist::GetNome()
{
	return nome_;
}

VecInt Playlist::GetTotalMusicas()
{
	return lista_.size();
}

VecInt Playlist::GetCapacidade()
{
	return lista_.capacity();
}

void Playlist::SetNome(std::string nome)
{
	nome_ = nome;
}

std::string Playlist::GetFicheiro(std::vector<int>::size_type posicao)
{
	VecInt pos = posicao - 1;
	return lista_[pos].GetFicheiro();
}

std::vector<Musica> Playlist::GetLista()
{
	return lista_;
}

void Playlist::AlterarMusica(VecInt posicao, Musica musica)
{
	VecInt pos = posicao - 1;
	lista_[pos] = musica;
}

bool Playlist::HasObject(VecInt musica)
{
	VecInt pos = musica - 1;
	if (pos >= 0 && pos < lista_.size())
		return true;
	return false;
}
