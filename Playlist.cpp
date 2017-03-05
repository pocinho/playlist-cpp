/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#include <sstream>
#include <string>
#include <vector>
#include "Playlist.h"
#include "Musica.h"

using namespace std;

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

void Playlist::Remover(int posicao)
{
	lista_.erase(lista_.begin() + posicao);
}

void Playlist::Reordenar(int origem, int destino)
{
	Musica musica = lista_[origem];
	lista_[origem] = lista_[destino];
	lista_[destino] = musica;
}

Musica Playlist::GetMusica(int posicao)
{
	return lista_[posicao];
}

std::string Playlist::Listar()
{
	stringstream lista;
	for (std::vector<int>::size_type i = 0; i < lista_.size(); ++i)
	{
		lista << i << ". " << lista_[i].GetTitulo() << "\n";
	}
	return lista.str();
}

std::string Playlist::Consultar(int posicao)
{
	stringstream consulta;
	consulta << posicao << ". " << lista_[posicao].GetTitulo() << "\n";
	consulta << "\nTitulo: " << lista_[posicao].GetTitulo() << "\n";
	consulta << "Autor: " << lista_[posicao].GetAutor() << "\n";
	consulta << "Estilo: " << lista_[posicao].GetEstilo() << "\n";
	consulta << "Ano: " << lista_[posicao].GetAno() << "\n";
	consulta << "Duração: " << lista_[posicao].GetDuracao() << "\n";
	return consulta.str();
}

std::string Playlist::GetNome()
{
	return nome_;
}

std::vector<int>::size_type Playlist::GetTotalMusicas()
{
	return lista_.size();
}

std::vector<int>::size_type Playlist::GetCapacidade()
{
	return lista_.capacity();
}

void Playlist::SetNome(std::string nome)
{
	nome_ = nome;
}

void Playlist::AlterarMusica(int posicao, Musica musica)
{
	lista_[posicao] = musica;
}
