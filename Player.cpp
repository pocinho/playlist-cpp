/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <shlwapi.h>

#include <SQLiteCpp/SQLiteCpp.h>

#include "Musica.h"
#include "Player.h"
#include "Playlist.h"

using namespace std;

typedef std::vector<int>::size_type VecInt;

Player::Player() : db_name_("Playlist.db"), db_(db_name_.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
	InicializarDB();
}

Player::~Player()
{
}

void Player::InicializarDB()
{
	try
	{
		if (!db_.tableExists("playlists"))
		{
			db_.exec("CREATE TABLE playlists (id INTEGER PRIMARY KEY, nome CHAR(50), posicao INTEGER)");
		}
		else
		{
			SQLite::Statement query(db_, "SELECT nome FROM playlists ORDER BY posicao");
			while (query.executeStep())
			{
				const std::string nome = query.getColumn(0);
				lista_.push_back(Playlist(nome));
			}
		}

		if (!db_.tableExists("musicas"))
		{
			db_.exec("CREATE TABLE musicas (id INTEGER PRIMARY KEY, titulo CHAR(50), autor CHAR(50), estilo CHAR(50), ano INTEGER, duracao REAL, ficheiro CHAR(200), playlist INTEGER, posicao INTEGER)");
		}
		else
		{
			SQLite::Statement query(db_, "SELECT titulo, autor, estilo, ano, duracao, ficheiro, playlist FROM musicas ORDER BY posicao");
			while (query.executeStep())
			{
				const std::string titulo   = query.getColumn(0);
				const std::string autor    = query.getColumn(1);
				const std::string estilo   = query.getColumn(2);
				const int         ano      = query.getColumn(3);
				const double      duracao  = query.getColumn(4);
				const std::string ficheiro = query.getColumn(5);
				const int         playlist = query.getColumn(6);
				lista_[playlist - 1].Adicionar(Musica(titulo, autor, estilo, ano, duracao, ficheiro));
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Erro ao inicializar base de dados: " << e.what() << std::endl;
	}

	std::cout << "Base de dados inicializada.\n";
}

void Player::AdicionarPlaylist(std::string nome)
{
	try
	{
		const int posicao = lista_.size() + 1;
		stringstream query;
		query << "INSERT INTO playlists VALUES (NULL, \"" << nome << "\", \"" << posicao << "\")";
		db_.exec(query.str());
	}
	catch (std::exception& e)
	{
		std::cout << "Erro ao guardar playlist na base de dados: " << e.what() << std::endl;
	}
	lista_.push_back(Playlist(nome));
}

void Player::AdicionarMusica(VecInt playlist, Musica musica)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Não é possivel encontrar a playlist " << playlist << ".\n";
	}
	else
	{
		try
		{
			int posicao = lista_[pos].GetTotalMusicas() + 1;
			stringstream query;
			query << "INSERT INTO musicas VALUES (NULL, \"";
			query << musica.GetTitulo();
			query << "\", \"";
			query << musica.GetAutor();
			query << "\", \"";
			query << musica.GetEstilo();
			query << "\", \"";
			query << musica.GetAno();
			query << "\", \"";
			query << musica.GetDuracao();
			query << "\", \"";
			query << musica.GetFicheiro();
			query << "\", \"";
			query << playlist;
			query << "\", \"";
			query << posicao;
			query << "\")";
			db_.exec(query.str().c_str());
		}
		catch (std::exception& e)
		{
			std::cout << "Erro ao guardar musica na base de dados: " << e.what() << std::endl;
		}
		lista_[pos].Adicionar(musica);
	}
}

void Player::RemoverPlaylist(VecInt posicao)
{
	VecInt pos = posicao - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Não é possivel encontrar a playlist " << posicao << ".\n";
	}
	else
	{
		try
		{
			stringstream query1;
			query1 << "DELETE FROM musicas WHERE playlist = " << posicao;
			db_.exec(query1.str());

			stringstream query2;
			query2 << "DELETE FROM playlists WHERE posicao = " << posicao;
			db_.exec(query2.str());
		}
		catch (std::exception& e)
		{
			std::cout << "Erro ao eliminar playlist na base de dados: " << e.what() << std::endl;
		}
		lista_.erase(lista_.begin() + pos);
	}
}

void Player::RemoverMusica(VecInt playlist, VecInt posicao)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Não é possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(posicao))
	{
		cout << "Não é possivel encontrar a musica " << posicao << " na playlist " << playlist << ".\n";
	}
	else
	{
		try
		{
			stringstream query;
			query << "DELETE FROM musicas WHERE playlist = " << playlist;
			db_.exec(query.str());
		}
		catch (std::exception& e)
		{
			std::cout << "Erro ao eliminar musica na base de dados: " << e.what() << std::endl;
		}

		lista_[playlist].Remover(posicao);

		int posicao_musica = 0;
		for (auto& musica : lista_[playlist].GetLista())
		{
			posicao_musica += 1;
			try
			{
				stringstream query;
				query << "INSERT INTO musicas VALUES (NULL, \"";
				query << musica.GetTitulo();
				query << "\", \"";
				query << musica.GetAutor();
				query << "\", \"";
				query << musica.GetEstilo();
				query << "\", \"";
				query << musica.GetAno();
				query << "\", \"";
				query << musica.GetDuracao();
				query << "\", \"";
				query << musica.GetFicheiro();
				query << "\", \"";
				query << playlist;
				query << "\", \"";
				query << posicao_musica;
				query << "\")";
				db_.exec(query.str());
			}
			catch (std::exception& e)
			{
				std::cout << "Erro ao reordenar musica na base de dados: " << e.what() << std::endl;
			}
		}
	}
}

void Player::AlocarMusica(VecInt playlist_origem, VecInt musica, VecInt playlist_destino)
{
	VecInt pos_origem = playlist_origem - 1;
	VecInt pos_destino = playlist_destino - 1;
	if (pos_origem < 0 || pos_origem >= lista_.size())
	{
		cout << "Não é possivel encontrar a playlist " << playlist_origem << ".\n";
	}
	else if (pos_origem < 0 || pos_origem >= lista_.size())
	{
		cout << "Não é possivel encontrar a playlist " << playlist_origem << ".\n"; 
	}
	else if (!lista_[pos_origem].HasObject(musica))
	{
		cout << "Não é possivel encontrar a musica " << musica << " na playlist " << playlist_origem << ".\n";
	}
	else
	{
		try
		{
			stringstream query1;
			query1 << "DELETE FROM musicas WHERE playlist = " << playlist_origem;
			db_.exec(query1.str());

			stringstream query2;
			query2 << "DELETE FROM musicas WHERE playlist = " << playlist_destino;
			db_.exec(query2.str());
		}
		catch (std::exception& e)
		{
			std::cout << "Erro ao eliminar musica na base de dados: " << e.what() << std::endl;
		}

		lista_[pos_destino].Adicionar(lista_[pos_origem].GetMusica(musica));
		lista_[pos_origem].Remover(musica);

		int posicao_musica = 0;
		for (auto& musica : lista_[playlist_origem].GetLista())
		{
			posicao_musica += 1;
			try
			{
				stringstream query;
				query << "INSERT INTO musicas VALUES (NULL, \"";
				query << musica.GetTitulo();
				query << "\", \"";
				query << musica.GetAutor();
				query << "\", \"";
				query << musica.GetEstilo();
				query << "\", \"";
				query << musica.GetAno();
				query << "\", \"";
				query << musica.GetDuracao();
				query << "\", \"";
				query << musica.GetFicheiro();
				query << "\", \"";
				query << playlist_origem;
				query << "\", \"";
				query << posicao_musica;
				query << "\")";
				db_.exec(query.str());
			}
			catch (std::exception& e)
			{
				std::cout << "Erro ao reordenar musica na base de dados: " << e.what() << std::endl;
			}
		}

		posicao_musica = 0;
		for (auto& musica : lista_[playlist_destino].GetLista())
		{
			posicao_musica += 1;
			try
			{
				stringstream query;
				query << "INSERT INTO musicas VALUES (NULL, \"";
				query << musica.GetTitulo();
				query << "\", \"";
				query << musica.GetAutor();
				query << "\", \"";
				query << musica.GetEstilo();
				query << "\", \"";
				query << musica.GetAno();
				query << "\", \"";
				query << musica.GetDuracao();
				query << "\", \"";
				query << musica.GetFicheiro();
				query << "\", \"";
				query << playlist_destino;
				query << "\", \"";
				query << posicao_musica;
				query << "\")";
				db_.exec(query.str());
			}
			catch (std::exception& e)
			{
				std::cout << "Erro ao reordenar musica na base de dados: " << e.what() << std::endl;
			}
		}
	}
}

void Player::ReordenarPlaylist(VecInt playlist, VecInt musica_origem, VecInt musica_destino)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Não é possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(musica_origem))
	{
		cout << "Não é possivel encontrar a musica " << musica_origem << " na playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(musica_destino))
	{
		cout << "Não é possivel encontrar a musica " << musica_destino << " na playlist " << playlist << ".\n";
	}
	else
	{
		try
		{
			stringstream query;
			query << "DELETE FROM musicas WHERE playlist = " << playlist;
			db_.exec(query.str());
		}
		catch (std::exception& e)
		{
			std::cout << "Erro ao eliminar musica na base de dados: " << e.what() << std::endl;
		}

		lista_[pos].Reordenar(musica_origem, musica_destino);

		int posicao_musica = 0;
		for (auto& musica : lista_[playlist].GetLista())
		{
			posicao_musica += 1;
			try
			{
				stringstream query;
				query << "INSERT INTO musicas VALUES (NULL, \"";
				query << musica.GetTitulo();
				query << "\", \"";
				query << musica.GetAutor();
				query << "\", \"";
				query << musica.GetEstilo();
				query << "\", \"";
				query << musica.GetAno();
				query << "\", \"";
				query << musica.GetDuracao();
				query << "\", \"";
				query << musica.GetFicheiro();
				query << "\", \"";
				query << playlist;
				query << "\", \"";
				query << posicao_musica;
				query << "\")";
				db_.exec(query.str());
			}
			catch (std::exception& e)
			{
				std::cout << "Erro ao reordenar musica na base de dados: " << e.what() << std::endl;
			}
		}
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
		lista << "Não é possivel encontrar a playlist " << playlist << ".\n";
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
		consulta << "Não é possivel encontrar a playlist " << posicao << ".\n";
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
		consulta << "Não é possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(musica))
	{
		consulta << "Não é possivel encontrar a musica " << musica << " na playlist " << playlist << ".\n";
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
		cout << "Não é possivel encontrar a playlist " << playlist << ".\n";
	}
	else
	{
		try
		{
			stringstream query;
			query << "UPDATE playlists SET nome = " << nome << " WHERE posicao = " << playlist;
			db_.exec(query.str());
		}
		catch (std::exception& e)
		{
			std::cout << "Erro ao renomear playlist na base de dados: " << e.what() << std::endl;
		}

		lista_[pos].SetNome(nome);
	}
}

void Player::AlterarMusica(VecInt playlist, VecInt posicao, Musica musica)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Não é possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(posicao))
	{
		cout << "Não é possivel encontrar a musica " << posicao << " na playlist " << playlist << ".\n";
	}
	else
	{
		try
		{
			stringstream query;
			query << "UPDATE musicas SET titulo = ";
			query << musica.GetTitulo();
			query << ", autor = ";
			query << musica.GetAutor();
			query << ", estilo = ";
			query << musica.GetEstilo();
			query << ", ano = ";
			query << musica.GetAno();
			query << ", duracao = ";
			query << musica.GetDuracao();
			query << ", ficheiro = ";
			query << musica.GetFicheiro();
			query << " WHERE playlist = ";
			query << playlist;
			query << " AND posicao = ";
			query << posicao;
			db_.exec(query.str());
		}
		catch (std::exception& e)
		{
			std::cout << "Erro ao actualizar musica na base de dados: " << e.what() << std::endl;
		}
		lista_[pos].AlterarMusica(posicao, musica);
	}
}

void Player::TocarMusica(std::vector<int>::size_type playlist, std::vector<int>::size_type posicao)
{
	VecInt pos = playlist - 1;
	if (pos < 0 || pos >= lista_.size())
	{
		cout << "Não é possivel encontrar a playlist " << playlist << ".\n";
	}
	else if (!lista_[pos].HasObject(posicao))
	{
		cout << "Não é possivel encontrar a musica " << posicao << " na playlist " << playlist << ".\n";
	}
	else
	{
		string file = lista_[pos].GetFicheiro(posicao);
#ifdef UNICODE
		wstring file_ws(file.begin(), file.end());
		ShellExecute(NULL, L"open", file_ws.c_str(), NULL, NULL, SW_SHOW);
#else
		ShellExecute(NULL, L"open", file.c_str(), NULL, NULL, SW_SHOW);
#endif
	}
}
