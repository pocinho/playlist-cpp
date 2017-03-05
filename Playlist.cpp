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
	vector<int>::size_type pos = posicao - 1;
	lista_.erase(lista_.begin() + pos);
}

void Playlist::Reordenar(int origem, int destino)
{
	vector<int>::size_type pos_origem = origem - 1;
	vector<int>::size_type pos_destino = destino - 1;
	Musica musica = lista_[pos_origem];
	lista_[pos_origem] = lista_[pos_destino];
	lista_[pos_destino] = musica;
}

Musica Playlist::GetMusica(int posicao)
{
	vector<int>::size_type pos = posicao - 1;
	return lista_[pos];
}

std::string Playlist::Listar()
{
	stringstream lista;
	for (std::vector<int>::size_type i = 0; i < lista_.size(); ++i)
	{
		lista << (i + 1) << ". " << lista_[i].GetTitulo() << "\n";
	}
	return lista.str();
}

std::string Playlist::Consultar(int posicao)
{
	vector<int>::size_type pos = posicao - 1;
	stringstream consulta;
	consulta << posicao << ". " << lista_[pos].GetTitulo() << "\n";
	consulta << "\nTitulo: " << lista_[pos].GetTitulo() << "\n";
	consulta << "Autor: " << lista_[pos].GetAutor() << "\n";
	consulta << "Estilo: " << lista_[pos].GetEstilo() << "\n";
	consulta << "Ano: " << lista_[pos].GetAno() << "\n";
	consulta << "Duração: " << lista_[pos].GetDuracao() << "\n";
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
	vector<int>::size_type pos = posicao - 1;
	lista_[pos] = musica;
}

bool Playlist::HasObject(int musica)
{
	vector<int>::size_type pos = musica - 1;
	if (pos >= 0 && pos < lista_.size())
		return true;
	return false;
}
