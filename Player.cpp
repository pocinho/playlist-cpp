/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Musica.h"
#include "Player.h"
#include "Playlist.h"

using namespace std;

typedef std::vector<int>::size_type VecInt;

Player::Player()
{
}

Player::~Player()
{
}

void Player::AdicionarPlaylist(std::string nome)
{
	lista_.push_back(Playlist(nome));
}

void Player::AdicionarMusica(VecInt playlist, Musica musica)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Nao e possivel encontrar a playlist " << playlist << ".\n";
	}
	else
	{
		lista_[pos].Adicionar(musica);
	}
}

void Player::RemoverPlaylist(VecInt posicao)
{
	VecInt pos = posicao - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Nao e possivel encontrar a playlist " << posicao << ".\n";
	}
	else
	{
		lista_.erase(lista_.begin() + pos);
	}
}

void Player::RemoverMusica(VecInt playlist, VecInt musica)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Nao e possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(musica))
	{
		cout << "Nao e possivel encontrar a musica " << musica << " na playlist " << playlist << ".\n";
	}
	else
	{
		lista_[playlist].Remover(musica);
	}
}

void Player::AlocarMusica(VecInt playlist_origem, VecInt musica, VecInt playlist_destino)
{
	VecInt pos_origem = playlist_origem - 1;
	VecInt pos_destino = playlist_destino - 1;
	if (pos_origem < 0 || pos_origem >= lista_.size())
	{
		cout << "Nao e possivel encontrar a playlist " << playlist_origem << ".\n";
	}
	else if (pos_origem < 0 || pos_origem >= lista_.size())
	{
		cout << "Nao e possivel encontrar a playlist " << playlist_origem << ".\n"; 
	}
	else if (!lista_[pos_origem].HasObject(musica))
	{
		cout << "Nao e possivel encontrar a musica " << musica << " na playlist " << playlist_origem << ".\n";
	}
	else
	{
		lista_[pos_destino].Adicionar(lista_[pos_origem].GetMusica(musica));
		lista_[pos_origem].Remover(musica);
	}
}

void Player::ReordenarPlaylist(VecInt playlist, VecInt musica_origem, VecInt musica_destino)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Nao e possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(musica_origem))
	{
		cout << "Nao e possivel encontrar a musica " << musica_origem << " na playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(musica_destino))
	{
		cout << "Nao e possivel encontrar a musica " << musica_destino << " na playlist " << playlist << ".\n";
	}
	else
	{
		lista_[pos].Reordenar(musica_origem, musica_destino);
	}
}

std::string Player::ListarPlaylists()
{
	stringstream lista;
	lista << "\nPlaylists disponiveis:\n\n";
	for (VecInt i = 0; i < lista_.size(); ++i)
	{
		lista << (i + 1) << ". " << lista_[i].GetNome() << "\n";
	}
	return lista.str();
}

std::string Player::ListarMusicas(VecInt playlist)
{
	stringstream lista;
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		lista << "Nao e possivel encontrar a playlist " << playlist << ".\n";
	}
	else
	{
		lista << lista_[pos].Listar();
	}
	return lista.str();
}

std::string Player::ConsultarPlaylist(VecInt posicao)
{
	stringstream consulta;
	VecInt pos = posicao - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		consulta << "Nao e possivel encontrar a playlist " << posicao << ".\n";
	}
	else
	{
		consulta << "\n(" << posicao << ") Playlist " << lista_[pos].GetNome() << "\n\n";
		consulta << lista_[pos].Listar();
		consulta << "\nTotal Musicas: " << lista_[pos].GetTotalMusicas() << "\n";
		consulta << "Capacidade: " << lista_[pos].GetCapacidade() << "\n";
	}
	return consulta.str();
}

std::string Player::ConsultarMusica(VecInt playlist, VecInt musica)
{
	stringstream consulta;
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		consulta << "Nao e possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(musica))
	{
		consulta << "Nao e possivel encontrar a musica " << musica << " na playlist " << playlist << ".\n";
	}
	else
	{
		consulta << "\n(" << playlist << ") Playlist " << lista_[pos].GetNome() << "\n\n";
		consulta << lista_[pos].Consultar(musica);
	}
	return consulta.str();
}

void Player::AlterarPlaylist(VecInt playlist, std::string nome)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Nao e possivel encontrar a playlist " << playlist << ".\n";
	}
	else
	{
		lista_[pos].SetNome(nome);
	}
}

void Player::AlterarMusica(VecInt playlist, VecInt posicao, Musica musica)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Nao e possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(posicao))
	{
		cout << "Nao e possivel encontrar a musica " << posicao << " na playlist " << playlist << ".\n";
	}
	else
	{
		lista_[pos].AlterarMusica(posicao, musica);
	}
}
