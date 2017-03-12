/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#define NOMINMAX
#include <Windows.h>

#include <SQLiteCpp/SQLiteCpp.h>

#include "Main.h"
#include "Musica.h"
#include "Player.h"
#include "Playlist.h"

using namespace std;
using namespace SQLite;

typedef std::vector<int>::size_type VecInt;

int main()
{
	string db_name = "Playlist.db";
	Player MusicPlayer;
	int opcao = 0;

	// Configurar a consola para aceitar caracteres latinos / europa ocidental:
	SetConsoleOutputCP(1252);

	cout << "SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")" << endl;
	cout << "SQliteC++ version " << SQLITECPP_VERSION << endl;

	////////////////////////////////////////////////////////////////////////////
	// Simple batch queries example :
	try
	{
		// Open a database file in create/write mode
		SQLite::Database db(db_name.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";

		// Create a new table with an explicit "id" column aliasing the underlying rowid
		db.exec("DROP TABLE IF EXISTS test");
		db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

		// first row
		int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
		std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

		// second row
		nb = db.exec("INSERT INTO test VALUES (NULL, \"second\")");
		std::cout << "INSERT INTO test VALUES (NULL, \"second\")\", returned " << nb << std::endl;

		// update the second row
		nb = db.exec("UPDATE test SET value=\"second-updated\" WHERE id='2'");
		std::cout << "UPDATE test SET value=\"second-updated\" WHERE id='2', returned " << nb << std::endl;

		// Check the results : expect two row of result
		SQLite::Statement   query(db, "SELECT * FROM test");
		std::cout << "SELECT * FROM test :\n";
		while (query.executeStep())
		{
			std::cout << "row (" << query.getColumn(0) << ", \"" << query.getColumn(1) << "\")\n";
		}

		db.exec("DROP TABLE test");
	}
	catch (std::exception& e)
	{
		std::cout << "SQLite exception: " << e.what() << std::endl;
		return EXIT_FAILURE; // unexpected error : exit the example program
	}
#ifdef _DEBUG
	remove(db_name.c_str());
#endif
	std::cout << "Tudo bem até agora.\n";

	do
	{
		Menu();
		cin >> opcao;
		cin.ignore();

		switch (opcao)
		{
		case 1:
			CriarPlaylist(MusicPlayer);
			break;
		case 2:
			CriarMusica(MusicPlayer);
			break;
		case 3:
			RemoverPlaylist(MusicPlayer);
			break;
		case 4:
			RemoverMusica(MusicPlayer);
			break;
		case 5:
			ListarPlaylists(MusicPlayer);
			break;
		case 6:
			ConsultarPlaylist(MusicPlayer);
			break;
		case 7:
			ConsultarMusica(MusicPlayer);
			break;
		case 8:
			AlterarPlaylist(MusicPlayer);
			break;
		case 9:
			AlterarMusica(MusicPlayer);
			break;
		case 10:
			ReordenarPlaylist(MusicPlayer);
			break;
		case 11:
			AlocarMusica(MusicPlayer);
			break;
		case 12:
			TocarMusica(MusicPlayer);
			break;
#ifdef _DEBUG
		case 13:
			GerarDadosTeste(MusicPlayer);
			break;
#endif
		case 0:
			cout << "Adeus, volte sempre!\n";
			break;
		default:
			cout << "Opção inválida.\n";
			break;
		}

	} while (opcao != 0);

	return 0;
}

void Menu()
{
	cout << "Opcoes disponiveis:\n";
	cout << " (1) Criar playlist\n";
	cout << " (2) Criar musica\n";
	cout << " (3) Remover playlist\n";
	cout << " (4) Remover musica de uma playlist\n";
	cout << " (5) Ver todas as playlists\n";
	cout << " (6) Consultar detalhes de playlist\n";
	cout << " (7) Consultar detalhes de musica\n";
	cout << " (8) Alterar uma playlist\n";
	cout << " (9) Alterar uma musica\n";
	cout << "(10) Reordenar playlist\n";
	cout << "(11) Alocar musica a outra playlist\n";
	cout << "(12) Tocar musica\n";
#ifdef _DEBUG
	cout << "(13) Gerar dados de teste\n";
#endif
	cout << " (0) Sair\n";
	cout << "Introduza uma opção: \n";
}

void CriarPlaylist(Player& player)
{
	string nome;
	cout << "Introduza o nome da playlist:\n";
	getline(cin, nome);
	player.AdicionarPlaylist(nome);
	Pausa();
}

void CriarMusica(Player& player)
{
	VecInt playlist;
	string titulo;
	string autor;
	string estilo;
	int ano;
	double duracao;
	string ficheiro;

	for (;;)
	{
		cout << "Introduza o numero da playlist onde quer adicionar a musica:\n";
		if (cin >> playlist)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << "Introduza o titulo da musica:\n";
	getline(cin, titulo);
	cout << "Introduza o autor da musica " << titulo << ":\n";
	getline(cin, autor);
	cout << "Introduza o estilo da musica " << titulo << ":\n";
	getline(cin, estilo);
	for (;;)
	{
		cout << "Introduza o ano da musica " << titulo << ":\n";
		if (cin >> ano)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza a duracao da musica " << titulo << ":\n";
		if (cin >> duracao)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero real positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << "Introduza a localização do ficheiro da musica " << titulo << ":\n";
	getline(cin, ficheiro);
	player.AdicionarMusica(playlist, Musica(titulo, autor, estilo, ano, duracao, ficheiro));
	Pausa();
}

void RemoverPlaylist(Player & player)
{
	VecInt playlist;
	for (;;)
	{
		cout << "Introduza o numero da playlist que quer remover:\n";
		if (cin >> playlist)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	player.RemoverPlaylist(playlist);
	Pausa();
}

void RemoverMusica(Player & player)
{
	VecInt playlist;
	VecInt musica;
	for (;;)
	{
		cout << "Introduza o numero da playlist:\n";
		if (cin >> playlist)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza o numero da musica:\n";
		if (cin >> musica)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	player.RemoverMusica(playlist, musica);
	Pausa();
}

void ListarPlaylists(Player & player)
{
	cout << player.ListarPlaylists();
	Pausa();
}

void ConsultarPlaylist(Player & player)
{
	VecInt posicao;
	for (;;)
	{
		cout << "Introduza o numero da playlist:\n";
		if (cin >> posicao)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << player.ConsultarPlaylist(posicao);
	Pausa();
}

void ConsultarMusica(Player & player)
{
	VecInt playlist;
	VecInt musica;
	for (;;)
	{
		cout << "Introduza o numero da playlist:\n";
		if (cin >> playlist)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza o numero da musica:\n";
		if (cin >> musica)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << player.ConsultarMusica(playlist, musica);
	Pausa();
}

void AlterarPlaylist(Player & player)
{
	VecInt playlist;
	string nome;
	for (;;)
	{
		cout << "Introduza o numero da playlist:\n";
		if (cin >> playlist)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << "Introduza o novo nome da playlist:\n";
	getline(cin, nome);
	player.AlterarPlaylist(playlist, nome);
	Pausa();
}

void AlterarMusica(Player & player)
{
	VecInt playlist;
	VecInt musica;
	string titulo;
	string autor;
	string estilo;
	int ano;
	double duracao;
	string ficheiro;
	for (;;)
	{
		cout << "Introduza o numero da playlist:\n";
		if (cin >> playlist)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza o numero da musica a alterar:\n";
		if (cin >> musica)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << "Introduza o titulo da musica:\n";
	getline(cin, titulo);
	cout << "Introduza o autor da musica " << titulo << ":\n";
	getline(cin, autor);
	cout << "Introduza o estilo da musica " << titulo << ":\n";
	getline(cin, estilo);
	for (;;)
	{
		cout << "Introduza o ano da musica " << titulo << ":\n";
		if (cin >> ano)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza a duracao da musica " << titulo << ":\n";
		if (cin >> duracao)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero real positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << "Introduza a localização do ficheiro da musica " << titulo << ":\n";
	getline(cin, ficheiro);
	player.AlterarMusica(playlist, musica, Musica(titulo, autor, estilo, ano, duracao, ficheiro));
	Pausa();
}

void ReordenarPlaylist(Player & player)
{
	VecInt playlist;
	VecInt musica_origem;
	VecInt musica_destino;
	for (;;)
	{
		cout << "Introduza o numero da playlist:\n";
		if (cin >> playlist)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza o numero da musica origem:\n";
		if (cin >> musica_origem)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza o numero da musica destino:\n";
		if (cin >> musica_destino)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	player.ReordenarPlaylist(playlist, musica_origem, musica_destino);
	Pausa();
}

void AlocarMusica(Player & player)
{
	VecInt playlist_origem;
	VecInt musica;
	VecInt playlist_destino;
	for (;;)
	{
		cout << "Introduza o numero da playlist origem:\n";
		if (cin >> playlist_origem)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza o numero da musica origem:\n";
		if (cin >> musica)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza o numero da playlist destino:\n";
		if (cin >> playlist_destino)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	player.AlocarMusica(playlist_origem, musica, playlist_destino);
	Pausa();
}

void Pausa()
{
	cout << "\nPrima ENTER para continuar.\n";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#ifdef _DEBUG
void GerarDadosTeste(Player& player)
{
	for (int i = 1; i < 7; ++i)
	{
		stringstream nome;
		nome << "Teste " << i;
		player.AdicionarPlaylist(nome.str());
		for (int m = 1; m < 10; ++m)
		{
			stringstream titulo;
			titulo << "Titulo " << i << " - " << m;
			stringstream autor;
			autor << "Autor " << i << " - " << m;
			stringstream estilo;
			estilo << "Estilo " << i << " - " << m;
			int ano = 2017;
			double duracao = 3.33;
			string ficheiro = "";
			player.AdicionarMusica(i, Musica(titulo.str(), autor.str(), estilo.str(), ano, duracao, ficheiro));
		}
	}
	cout << "Dados de teste introduzidos.\n";
	Pausa();
}
#endif // _DEBUG

void TocarMusica(Player & player)
{
	VecInt playlist;
	VecInt posicao;
	for (;;)
	{
		cout << "Introduza o numero da playlist:\n";
		if (cin >> playlist)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	for (;;)
	{
		cout << "Introduza o numero da musica que quer tocar:\n";
		if (cin >> posicao)
		{
			break;
		}
		else
		{
			cout << "Por favor, introduza um numero inteiro positivo válido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	player.TocarMusica(playlist, posicao);
	Pausa();
}
