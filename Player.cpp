/*
* AUTOR: Paulo Pocinho
* DESDE: 05-03-2017
*/

#include <sstream>
#include <string>
#include <vector>
#include "Musica.h"
#include "Player.h"
#include "Playlist.h"

using namespace std;

Player::Player()
{
	lista_.reserve(5);
}


Player::~Player()
{
}

void Player::AdicionarPlaylist(std::string nome)
{
	lista_.push_back(Playlist(nome));
}

void Player::AdicionarMusica(int playlist, Musica musica)
{
	lista_[playlist].Adicionar(musica);
}

void Player::RemoverPlaylist(int posicao)
{
	lista_.erase(lista_.begin() + posicao);
}

void Player::RemoverMusica(int playlist, int musica)
{
	lista_[playlist].Remover(musica);
}

void Player::AlocarMusica(int playlist_origem, int musica, int playlist_destino)
{
	lista_[playlist_destino].Adicionar(lista_[playlist_origem].GetMusica(musica));
	lista_[playlist_origem].Remover(musica);
}

void Player::ReordenarPlaylist(int playlist, int musica_origem, int musica_destino)
{
	lista_[playlist].Reordenar(musica_origem, musica_destino);
}

std::string Player::ListarPlaylists()
{
	stringstream lista_ss;
	lista_ss << "\nPlaylists Disponiveis:\n";
	for (std::vector<int>::size_type i = 0; i < lista_.size(); ++i)
	{
		lista_ss << i << ". " << lista_[i].GetNome() << "\n";
	}
	string lista = lista_ss.str();
	return lista;
}

std::string Player::ListarMusicas(int playlist)
{
	return lista_[playlist].Listar();
}

std::string Player::ConsultarPlaylist(int posicao)
{
	stringstream consulta_ss;
	consulta_ss << posicao << ". Playlist " << lista_[posicao].GetNome() << "\n";
	consulta_ss << lista_[posicao].Listar();
	consulta_ss << "Total Musicas: " << lista_[posicao].GetTotalMusicas() << "\n";
	consulta_ss << "Capacidade: " << lista_[posicao].GetCapacidade() << "\n";
	string consulta = consulta_ss.str();
	return consulta;
}

std::string Player::ConsultarMusica(int playlist, int musica)
{
	return lista_[playlist].Consultar(musica);
}

void Player::AlterarPlaylist(int playlist, std::string nome)
{
	lista_[playlist].SetNome(nome);
}

void Player::AlterarMusica(int playlist, int posicao, Musica musica)
{
	lista_[playlist].AlterarMusica(posicao, musica);
}
