/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "Main.h"
#include "Musica.h"
#include "Player.h"
#include "Playlist.h"

using namespace std;

typedef std::vector<int>::size_type VecInt;

int main()
{
	Player MusicPlayer;

	int opcao = 0;

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
		case 13:
			GerarDadosTeste(MusicPlayer);
			break;
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
	cout << "(13) Gerar dados de teste\n";
	cout << " (0) Sair\n";
	cout << "Introduza uma opcao: \n";
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero real positivo valido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << "Introduza a localizacao do ficheiro da musica " << titulo << ":\n";
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero real positivo valido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	cout << "Introduza a localizacao do ficheiro da musica " << titulo << ":\n";
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
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
			cout << "Por favor, introduza um numero inteiro positivo valido." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.ignore();
	player.TocarMusica(playlist, posicao);
	Pausa();
}
