#ifndef PROJHEADER_H_INCLUDED
#define PROJHEADER_H_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sstream>

using namespace std;

class Player
  {
	private:
		string ID;
		int gamesPlayed;

        //Elo
		double EloL; // Logistic varient of Elo
		double EloG; // Gaussian varient of Elo
		double kFactor;

        //Glicko
		double R; // Glicko rating
		double RD; // Glicko rating deviation
		int t; // rating peroids since last active
		double sumDelta;
		double sumDsqr;
		bool RDupdate; // false if RD has been updated at the onset of the rating peroid

	public:
        //Constructors
		Player(string);
		Player(string, const double&);
		Player(string, const double&, const double&);

        string getID();
		int getgamesPlayed() const;
		void setgamesPlayed(const int&);

        //Elo
		double getEloL() const;
		double getEloG() const;
		double getkFactor() const;

		void setEloL(const double&);
		void setEloG(const double&);
		void setkFactor(const double&);

        //Glicko
		double getR() const;
		double getRD() const;
		double getsumDelta() const;
		double getsumDsqr() const;
		bool getRDupdate() const;
		int gett() const;

		void setR(const double&);
		void setRD(const double&);
		void setsumDelta(const double&);
		void setsumDsqr(const double&);
		void setRDupdate(const bool&);
		void sett(const int&);

	};

//overloaders
ostream& operator<<(ostream&, Player&);
bool operator==(Player, Player);
bool operator<(Player, Player); //for sort algorithm

//update functions
void play(vector<Player>&,vector<string>, int); // will play Elo games and update ratings
void EloLupdate(Player&, Player&, const double&);
void EloGupdate(Player&, Player&, const double&);
void GlickoUpdate(vector<Player>&,vector<string>, int, int);

//expected outcome functions
double EloLexpected(Player&, Player&);
double EloGexpected(Player&, Player&);
double Glickoexpected(Player&, Player&);

//other functions
vector<Player> populatePlayers(vector<string>);
double phi(double); // credit http://www.johndcook.com/cpp_phi.html
double s2d(const string&); // credit http://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c
void winproportion(vector<string>);
void clearPlayers(vector<Player>&);

//Glicko functions
double g(Player&);
double dsqr(Player&);

//optimisation tests
void ctest(vector<Player>, vector<string>, vector<string>);
void kfactortest(vector<Player>, vector<string>, vector<string>);

//Error tests
double RMSE(vector<Player>,vector<string>,string); //Root-mean squre error
double BD(vector<Player>,vector<string>,string); //Binomial devience

#endif // PROJHEADER_H_INCLUDED
