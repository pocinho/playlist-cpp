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
	lista_.reserve(5);
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
	stringstream lista_ss;
	for (std::vector<int>::size_type i = 0; i < lista_.size(); ++i)
	{
		lista_ss << i << ". " << lista_[i].GetTitulo() << "\n";
	}
	string lista = lista_ss.str();
	return lista;
}

std::string Playlist::Consultar(int posicao)
{
	stringstream consulta_ss;
	consulta_ss << posicao << ". Titulo: " << lista_[posicao].GetTitulo() << "\n";
	consulta_ss << "Autor: " << lista_[posicao].GetAutor() << "\n";
	consulta_ss << "Estilo: " << lista_[posicao].GetEstilo() << "\n";
	consulta_ss << "Ano: " << lista_[posicao].GetAno() << "\n";
	consulta_ss << "Duração: " << lista_[posicao].GetDuracao() << "\n";
	string consulta = consulta_ss.str();
	return consulta;
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
