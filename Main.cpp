/*
 * AUTOR: Paulo Pocinho
 * DESDE: 05-03-2017
 */

#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include "Main.h"


using namespace std;

int main()
{
	Player player;

	int opcao = 0;

	do
	{
		escreve_menu();
		cin >> opcao;
		cin.ignore();

		switch (opcao)
		{
		case 1:
			CriarPlaylist(player);
			break;
		case 2:
			CriarMusica(player);
			break;
		case 3:
			RemoverPlaylist(player);
			break;
		case 4:
			RemoverMusica(player);
			break;
		case 5:
			ListarPlaylists(player);
			break;
		case 6:
			ConsultarPlaylist(player);
			break;
		case 7:
			ConsultarMusica(player);
			break;
		case 8:
			AlterarPlaylist(player);
			break;
		case 9:
			AlterarMusica(player);
			break;
		case 10:
			ReordenarPlaylist(player);
			break;
		case 11:
			AlocarMusica(player);
			break;
		case 12:
			GerarDadosTeste(player);
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

void escreve_menu()
{
	cout << "Opções disponiveis:\n";
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
	cout << "(12) Gerar dados de teste\n";
	cout << " (0) Sair\n";
	cout << "Introduza uma opcao: \n";
}

void CriarPlaylist(Player& player)
{
	string nome = "";
	cout << "Introduza o nome da playlist:\n";
	getline(cin, nome);
	player.AdicionarPlaylist(nome);
	pausa();
}

void CriarMusica(Player& player)
{
	int playlist;
	string titulo;
	string autor;
	string estilo;
	int ano;
	double duracao;
	cout << "Introduza a playlist onde quer adicionar a musica:\n";
	cin >> playlist;
	cin.ignore();
	cout << "Introduza o titulo da musica:\n";
	getline(cin, titulo);
	cout << "Introduza o autor da musica " << titulo << ":\n";
	getline(cin, autor);	
	cout << "Introduza o estilo da musica " << titulo << ":\n";
	getline(cin, estilo);
	cout << "Introduza o ano da musica " << titulo << ":\n";
	cin >> ano;
	cin.ignore();
	cout << "Introduza a duracao da musica " << titulo << ":\n";
	cin >> duracao;
	cin.ignore();
	player.AdicionarMusica(playlist, Musica(titulo, autor, estilo, ano, duracao));
	pausa();
}

void RemoverPlaylist(Player & player)
{
	int playlist;
	cout << "introduza o numero da playlist que quer remover:\n";
	cin >> playlist;
	cin.ignore();
	player.RemoverPlaylist(playlist);
	pausa();
}

void RemoverMusica(Player & player)
{
	int playlist;
	int musica;
	cout << "Introduza o numero da playlist:\n";
	cin >> playlist;
	cin.ignore();
	cout << "Introduza o numero da musica:\n";
	cin >> musica;
	cin.ignore();
	player.RemoverMusica(playlist, musica);
	pausa();
}

void ListarPlaylists(Player & player)
{
	cout << player.ListarPlaylists();
	pausa();
}

void ConsultarPlaylist(Player & player)
{
	int posicao;
	cout << "Introduza o numero da playlist:\n";
	cin >> posicao;
	cin.ignore();
	cout << player.ConsultarPlaylist(posicao);
	pausa();
}

void ConsultarMusica(Player & player)
{
	int playlist;
	int musica;
	cout << "Introduza o numero da playlist:\n";
	cin >> playlist;
	cin.ignore();
	cout << "Introduza o numero da musica:\n";
	cin >> musica;
	cin.ignore();
	cout << player.ConsultarMusica(playlist, musica);
	pausa();
}

void AlterarPlaylist(Player & player)
{
	int playlist;
	std::string nome;
	cout << "Introduza o numero da playlist:\n";
	cin >> playlist;
	cin.ignore();
	cout << "Introduza o novo nome da playlist:\n";
	getline(cin, nome);
	player.AlterarPlaylist(playlist, nome);
	pausa();
}

void AlterarMusica(Player & player)
{
	int playlist;
	int musica;
	string titulo;
	string autor;
	string estilo;
	int ano;
	double duracao;
	cout << "Introduza o numero da playlist:\n";
	cin >> playlist;
	cin.ignore();
	cout << "Introduza o numero da musica a alterar:\n";
	cin >> musica;
	cin.ignore();
	cout << "Introduza o titulo da musica:\n";
	getline(cin, titulo);
	cout << "Introduza o autor da musica " << titulo << ":\n";
	getline(cin, autor);
	cout << "Introduza o estilo da musica " << titulo << ":\n";
	getline(cin, estilo);
	cout << "Introduza o ano da musica " << titulo << ":\n";
	cin >> ano;
	cin.ignore();
	cout << "Introduza a duracao da musica " << titulo << ":\n";
	cin >> duracao;
	cin.ignore();
	player.AlterarMusica(playlist, musica, Musica(titulo, autor, estilo, ano, duracao));
	pausa();
}

void ReordenarPlaylist(Player & player)
{
	int playlist;
	int musica_origem;
	int musica_destino;
	cout << "Introduza o numero da playlist:\n";
	cin >> playlist;
	cin.ignore();
	cout << "Introduza o numero da musica origem:\n";
	cin >> musica_origem;
	cin.ignore();
	cout << "Introduza o numero da musica destino:\n";
	cin >> musica_destino;
	cin.ignore();
	player.ReordenarPlaylist(playlist, musica_origem, musica_destino);
	pausa();
}

void AlocarMusica(Player & player)
{
	int playlist_origem;
	int musica;
	int playlist_destino;
	cout << "Introduza o numero da playlist origem:\n";
	cin >> playlist_origem;
	cin.ignore();
	cout << "Introduza o numero da musica origem:\n";
	cin >> musica;
	cin.ignore();
	cout << "Introduza o numero da playlist destino:\n";
	cin >> playlist_destino;
	cin.ignore();
	player.AlocarMusica(playlist_origem, musica, playlist_destino);
	pausa();
}

void pausa()
{
	cout << "\nPrima ENTER para continuar.\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void GerarDadosTeste(Player& player)
{
	for (int i = 0; i < 7; ++i)
	{
		stringstream nome;
		nome << "Teste " << i;
		player.AdicionarPlaylist(nome.str());
		for (int m = 0; m < 10; ++m)
		{
			stringstream titulo;
			titulo << "Titulo " << i << " - " << m;
			stringstream autor;
			autor << "Autor " << i << " - " << m;
			stringstream estilo;
			estilo << "Estilo " << i << " - " << m;
			int ano = 2017;
			double duracao = 3.33;
			player.AdicionarMusica(i, Musica(titulo.str(), autor.str(), estilo.str(), ano, duracao));
		}
	}
	cout << "Dados de teste introduzidos.\n";
	pausa();
}
