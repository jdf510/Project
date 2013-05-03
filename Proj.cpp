#include "projheader.h"
//Member functions

Player::Player(string a)
  {
	ID = a;
	gamesPlayed = 0;
	//Elo
	EloL = 1000;
	EloG = 1000;
	kFactor = 37;
    //Glicko
	t = 1;
    R = 1500;
    RD = 350;
    sumDelta = 0;
    sumDsqr = 0;
    RDupdate = true;
	}

Player::Player(string a,const double& b)
	{
	ID = a;
	gamesPlayed = 0;
	//Elo
	EloL = b;
	EloG = 1000;
	kFactor = 37;
    //Glicko
    t = 1;
    R = 1500;
    RD = 350;
    sumDelta = 0;
    sumDsqr = 0;
    RDupdate = true;
	}

Player::Player(string a,const double& b,const double& c)
	{
	ID = a;
	gamesPlayed = 0;
	//Elo
	EloL = 1000;
	EloG = 1000;
	kFactor = 37;
	//Glicko
    t = 1;
    R = b;
    RD = c;
    sumDelta = 0;
    sumDsqr = 0;
    RDupdate = true;
	}

double Player::getEloL() const
	{
	return EloL;
	}

double Player::getEloG() const
	{
	return EloG;
	}

double Player::getkFactor() const
	{
	return kFactor;
	}

double Player::getR() const
	{
	return R;
	}

double Player::getRD() const
	{
	return RD;
	}

double Player::getsumDelta() const
	{
	return sumDelta;
	}

double Player::getsumDsqr() const
	{
	return sumDsqr;
	}

bool Player::getRDupdate() const
	{
	return RDupdate;
	}

string Player::getID()
	{
	return ID;
	}

int Player::getgamesPlayed() const
	{
	return gamesPlayed;
	}

int Player::gett() const
    {
    return t;
    }

void Player::setEloL(const double& a)
	{
	EloL = a;
	}

void Player::setEloG(const double& a)
	{
	EloG = a;
	}

void Player::setR(const double& a)
	{
	R = a;
	}

void Player::setRD(const double& a)
	{
	RD = a;
	}

void Player::setsumDelta(const double& a)
	{
	sumDelta = a;
	}

void Player::setsumDsqr(const double& a)
	{
	sumDsqr = a;
	}

void Player::setRDupdate(const bool& a)
	{
	RDupdate = a;
	}

void Player::setkFactor(const double& a)
	{
	kFactor = a;
	}

void Player::setgamesPlayed(const int& a)
	{
	gamesPlayed = a;
	}

void Player::sett(const int& a)
	{
	t = a;
	}

ostream& operator<<(ostream& os, Player& P)
    {

     os << P.getID() << " E_L=("
        << floor(P.getEloL()) << ")E_G=("
        << floor(P.getEloG()) << ")G=("
        << floor(P.getR()) << ")RD=("
        << floor(P.getRD()) << ")["
        << P.getgamesPlayed() << "]{"
        << floor(P.getR() - P.getRD()) << "}";

    return os;
    }

bool operator==(Player P, Player Q)
	{
	if (P.getID() == Q.getID())
		return true;
	else
		return false;
	}

bool operator<(Player P, Player Q)
	{
	if (P.getR() - P.getRD() > Q.getR() - Q.getRD())
		return true;
	else
		return false;
	}

// function definitions

double EloLexpected(Player& A, Player& B)
    {
        double E_A = pow((1+pow(10,((B.getEloL()-A.getEloL())/400))),-1);

    return E_A;
    }

void EloLupdate(Player& A, Player& B, const double& r) // r is 1 if A wins, 0 if B wins and 0.5 if draw
    {
        if(r>1)
            {
                cout << "error with r" << endl;
            }

        double delta = (r-EloLexpected(A,B));

        A.setEloL(A.getEloL() + A.getkFactor() * delta);
        B.setEloL(B.getEloL() - B.getkFactor() * delta);
    }

double EloGexpected(Player& A, Player& B)
    {
        double E_A = phi((A.getEloG()-B.getEloG())/(sqrt(2)*200));

    return E_A;
    }

void EloGupdate(Player& A, Player& B, const double& r) // r is 1 if A wins, 0 if B wins and 0.5 if draw
    {
        if(r>1)
            {
                cout << "error with r" << endl;
            }

        double delta = (r-EloGexpected(A,B));

        A.setEloG(A.getEloG() + A.getkFactor() * delta);
        B.setEloG(B.getEloG() - B.getkFactor() * delta);
    }

vector<Player> populatePlayers(vector<string> fullData)
    {

    vector<Player> players;

    string nul;
    for(int i=3; i < fullData.size(); i += 4) // removes results so we're just left with ununique players
        {
            fullData[i] = nul;
        }
    for(int i=0; i < fullData.size(); i += 4) // removes months so we're just left with ununique players
        {
            fullData[i] = nul;
        }

    for(int i=0; i < fullData.size(); i++)
        {
            if(fullData[i] == nul)
            fullData.erase(fullData.begin()+i);
        }
    cout << "Sorting players..."  << endl;
    sort(fullData.begin(), fullData.end());
    fullData.erase(unique(fullData.begin(), fullData.end()), fullData.end());
    cout << "Populating player vector..." << endl;
    for(int i=0; i < fullData.size(); i++)
        {
            Player P = fullData[i];
            players.push_back(P);
        }

    return players;
    }

void play(vector<Player>& players,vector<string> dataList, int n)
    {
    int a,b = 0;

    if(4*n > dataList.size() || n == 0)
        {
            n = (dataList.size() / 4);
        }

    for(int i=1; i < 4*n; i += 4)
        {
            a, b = 0;
            for(int j=0; j < players.size(); j++) //finds player A in the players vector
                {

                    if(dataList[i] == players[j].getID())
                        {
                            a = j;
                            break;
                        }

                }

            for(int k=0; k < players.size(); k++) //finds player B in the players vector
                {
                    if(dataList[i+1] == players[k].getID())
                        {
                            b = k;
                            break;
                        }
                }
/*
 //to find a players convergence
        if(players[a].getID() == "5342")
            {
                cout << players[a].getgamesPlayed() << "," << players[a].getEloL() << endl;
            }

        if(players[b].getID() == "5342")
            {
                cout << players[b].getgamesPlayed() << "," << players[b].getEloL() << endl;
            }
*/

        players[a].setgamesPlayed(players[a].getgamesPlayed() + 1);
        players[b].setgamesPlayed(players[b].getgamesPlayed() + 1);
        EloLupdate(players[a],players[b],s2d(dataList[i+2]));
        EloGupdate(players[a],players[b],s2d(dataList[i+2]));
        }

    sort(players.begin(), players.end());

    }

double RMSE(vector<Player> players, vector<string> dataList, string s)
    {
    double RMSE;
    double e; //expected results given two players
    double sum = 0; //sum of the differences squared
    int a,b,games = 0; // tracks number of games tested

    for(int i=1; i < dataList.size(); i += 4)
        {
        a, b = 0;

            for(int j=0; j < players.size(); j++) //finds player A in the players vector
                {
                    if(dataList[i] == players[j].getID())
                        {
                            a = j;
                            break;
                        }
                }

            for(int k=0; k < players.size(); k++) //finds player B in the players vector
                {
                    if(dataList[i+1] == players[k].getID())
                        {
                            b = k;
                            break;
                        }
                }

            if(s == "EloL")
                {
                    e = EloLexpected(players[a],players[b]);
                }
            if(s == "EloG")
                {
                    e = EloGexpected(players[a],players[b]);
                }
            if(s == "Glicko")
                {
                    e = Glickoexpected(players[a],players[b]);
                }
            if(s == "WhiteWins")
                {
                    e = 1;
                }
            if(s == "BlackWins")
                {
                    e = 0;
                }
            if(s == "Draw")
                {
                    e = 0.5;
                }
        if(players[a].getgamesPlayed() >= 10 && players[b].getgamesPlayed() >= 10) // only use players who're rated in at least 10 games
            {
                sum += pow(s2d(dataList[i+2]) - e,2);
                games++;
            }
        }

    RMSE = sqrt(sum/games);

    return RMSE;
    }

double BD(vector<Player> players, vector<string> dataList, string s)
    {
    double BD;
    double e; //expected results given two players
    double sum = 0; //sum of the differences squared
    int a,b,games = 0; // tracks number of games tested

    for(int i=1; i < dataList.size(); i += 4)
        {
        a, b = 0;

            for(int j=0; j < players.size(); j++) //finds player A in the players vector
                {
                    if(dataList[i] == players[j].getID())
                        {
                            a = j;
                            break;
                        }
                }

            for(int k=0; k < players.size(); k++) //finds player B in the players vector
                {
                    if(dataList[i+1] == players[k].getID())
                        {
                            b = k;
                            break;
                        }
                }

            if(s == "EloL")
                {
                    e = EloLexpected(players[a],players[b]);
                }
            if(s == "EloG")
                {
                    e = EloGexpected(players[a],players[b]);
                }
            if(s == "Glicko")
                {
                    e = Glickoexpected(players[a],players[b]);
                }
            if(s == "WhiteWins")
                {
                    e = 0.99; // log10(1) is undefined so use 0.99
                }
            if(s == "BlackWins")
                {
                    e = 0.01;
                }
            if(s == "Draw")
                {
                    e = 0.5;
                }
        if(players[a].getgamesPlayed() >= 10 && players[b].getgamesPlayed() >= 10)
            {
                sum += -1*(s2d(dataList[i+2])*log10(e) + (1-s2d(dataList[i+2]))*log10(1-e));
                games++;
            }
        }

    BD = sum/games;

    return BD;
    }

double phi(double x) //credit to http://www.johndcook.com/cpp_phi.html Used for Elo_g
{
    // constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;

    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x)/sqrt(2.0);

    // A&S formula 7.1.26
    double t = 1.0/(1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

    return 0.5*(1.0 + sign*y);
}

 double s2d( const string& s ) // credit to http://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c
 {
   istringstream i(s);
   double x;

   if (!(i >> x))
     return 0;

   return x;
 }

void winproportion(vector<string> fullData)
    {
    double blackwins,whitewins,draws, results = 0;

    for(int i=3; i < fullData.size(); i += 4) // considers results only
        {
            if(s2d(fullData[i]) == 0)
                {
                    blackwins++;
                }

            if(s2d(fullData[i]) == 1)
                {
                    whitewins++;
                }

            if(s2d(fullData[i]) == 0.5)
                {
                    draws++;
                }
            results++;
        }

    double pw = (whitewins/results)*100;
    double pb = (blackwins/results)*100;
    double pd = (draws/results)*100;
    cout << "\nWhite wins: " << pw << "%" << endl;
    cout << "Black wins: " << pb << "%" << endl;
    cout << "Draws:      " << pd << "%" << endl;
    }

void clearPlayers(vector<Player>& players)
    {
        for(int i=0; i < players.size(); i++)
            {
                players[i].setEloG(1000);
                players[i].setEloL(1000);
                players[i].setkFactor(37);
                players[i].setgamesPlayed(0);
                players[i].sett(1);
                players[i].setR(1500);
                players[i].setRD(350);
            }
    }

void kfactortest(vector<Player> players, vector<string> training, vector<string> test1)
    {
    vector<double> errorEloLs;
    vector<double> errorEloGs;

    for(double i=0; i <= 100; i++)
        {
            clearPlayers(players);

            for(int j=0; j < players.size(); j++)
                {
                    players[j].setkFactor(i);
                }

            play(players,training,53871);

            errorEloGs.push_back(i);
            errorEloGs.push_back(RMSE(players,test1,"EloG"));
            errorEloGs.push_back(BD(players,test1,"EloG"));

            errorEloLs.push_back(i);
            errorEloLs.push_back(RMSE(players,test1,"EloL"));
            errorEloLs.push_back(BD(players,test1,"EloL"));

            cout << i << "% complete" << endl;
        }

ofstream fout("ErrorsG.csv");
    if(fout.fail())
        {
            cerr << "Error writing G" << endl;
        }
    else
        {
        fout << "G k factor" << "," << "RMSE" << "," << "BD" << endl;
        for(int i=0; i < errorEloGs.size(); i+=3)
            {
                fout << errorEloGs[i] << "," << errorEloGs[i+1] << "," << errorEloGs[i+2] << endl;
            }
        }
fout.close();

ofstream fout2("ErrorsL.csv");
    if(fout2.fail())
        {
            cerr << "Error writing L" << endl;
        }
    else
        {
        fout2 << "L k factor" << "," << "RMSE" << "," << "BD" << endl;
        for(int i=0; i < errorEloLs.size(); i+=3)
            {
                fout2 << errorEloLs[i] << "," << errorEloLs[i+1] << "," << errorEloLs[i+2] << endl;
            }
        }
fout2.close();

        cout << "kfactor test complete. Please find ErrorL.csv and ErrorG.csv" << endl;

    }

double g(Player& P)
    {
        double q = 0.0057565;
        double pi = 3.141592;
        double p = 3*pow(q,2)*pow(P.getRD(),2)/pow(pi,2);
        double g = pow(sqrt(1+p),-1);

    return g;
    }

double Glickoexpected(Player& P, Player& Q)
    {
        double e = pow(1+pow(10,-1*g(Q)*(P.getR()- Q.getR())/400),-1);

    return e;
    }

double dsqr(Player& P)
    {
        double q = 0.0057565;
        double dsqr = pow(pow(q,2)*P.getsumDsqr(),-1);

    return dsqr;
    }

void GlickoUpdate(vector<Player>& players, vector<string> training, int c, int RP)
    {

    vector<string> month; //Contains the games for a given month

    for(int m=1; m <= RP; m++) //Considers the data month by month
    {

        for(int i=0; i < training.size(); i+=4)
            {
                if(s2d(training[i]) == m)
                    {
                        month.push_back(training[i]);
                        month.push_back(training[i+1]);
                        month.push_back(training[i+2]);
                        month.push_back(training[i+3]);
                    }
            }

        int a,b = 0;

        for(int i=0; i < month.size(); i += 4)
            {
                a, b = 0;

                for(int j=0; j < players.size(); j++) //finds player A in the players vector
                    {
                        if(month[i+1] == players[j].getID())
                            {
                                a = j;
                                break;
                            }
                    }

                for(int k=0; k < players.size(); k++) //finds player B in the players vector
                    {
                        if(month[i+2] == players[k].getID())
                            {
                                b = k;
                                break;
                            }
                    }

            if(players[a].getRDupdate() == true) // Determine RD at the onset of the rating peroid
                {
                    players[a].setRD(sqrt(pow(players[a].getRD(),2)+pow(c,2)*(players[a].gett())));

                    if(players[a].getRD() > 350)
                        {
                            players[a].setRD(350);
                        }
                    players[a].setRDupdate(false);
                }

            if(players[b].getRDupdate() == true)
                {
                    players[b].setRD(sqrt(pow(players[b].getRD(),2)+pow(c,2)*(players[b].gett())));

                    if(players[b].getRD() > 350)
                        {
                            players[b].setRD(350);
                        }
                    players[b].setRDupdate(false);
                }

            if(s2d(month[i+3]) == 1)
                {
                    //player 1 won
                    players[a].setsumDelta(players[a].getsumDelta() + g(players[b])*(1-Glickoexpected(players[a],players[b])));
                    players[a].setsumDsqr(players[a].getsumDsqr() + pow(g(players[b]),2)*Glickoexpected(players[a],players[b])*(1-Glickoexpected(players[a],players[b])));
                    players[b].setsumDelta(players[b].getsumDelta() + g(players[a])*(0-Glickoexpected(players[b],players[a])));
                    players[b].setsumDsqr(players[b].getsumDsqr() + pow(g(players[a]),2)*Glickoexpected(players[b],players[a])*(1-Glickoexpected(players[b],players[a])));

                }
            if(s2d(month[i+3]) == 0)
                {
                    //player 2 won
                    players[a].setsumDelta(players[a].getsumDelta() + g(players[b])*(0-Glickoexpected(players[a],players[b])));
                    players[a].setsumDsqr(players[a].getsumDsqr() + pow(g(players[b]),2)*Glickoexpected(players[a],players[b])*(1-Glickoexpected(players[a],players[b])));
                    players[b].setsumDelta(players[b].getsumDelta() + g(players[a])*(1-Glickoexpected(players[b],players[a])));
                    players[b].setsumDsqr(players[b].getsumDsqr() + pow(g(players[a]),2)*Glickoexpected(players[b],players[a])*(1-Glickoexpected(players[b],players[a])));

                }
            if(s2d(month[i+3]) == 0.5)
                {
                    //draw
                    players[a].setsumDelta(players[a].getsumDelta() + g(players[b])*(0.5-Glickoexpected(players[a],players[b])));
                    players[a].setsumDsqr(players[a].getsumDsqr() + pow(g(players[b]),2)*Glickoexpected(players[a],players[b])*(1-Glickoexpected(players[a],players[b])));
                    players[b].setsumDelta(players[b].getsumDelta() + g(players[a])*(0.5-Glickoexpected(players[b],players[a])));
                    players[b].setsumDsqr(players[b].getsumDsqr() + pow(g(players[a]),2)*Glickoexpected(players[b],players[a])*(1-Glickoexpected(players[b],players[a])));
                }

            players[a].setgamesPlayed(players[a].getgamesPlayed() + 1);
            players[b].setgamesPlayed(players[b].getgamesPlayed() + 1);

            }

        for(int t=0; t < players.size(); t++)
            {
                if(players[t].getgamesPlayed() > 0)
                    {
                        players[t].sett(players[t].gett() + 1);
                    }
            }

        for(int p =0; p < players.size(); p++)
            {
                if(players[p].getsumDelta() != 0 || players[p].getsumDsqr() != 0) // Finds players who played in this rating peroid
                    {
                        double q = 0.0057565;
                        double d = dsqr(players[p]);
                        double coff = q/((1/pow(players[p].getRD(),2))+(1/d));

                        //update R and RD
                        players[p].setR(players[p].getR() + players[p].getsumDelta()*coff);
                        players[p].setRD(sqrt(1/((1/pow(players[p].getRD(),2))+(1/d))));

                        //reset values
                        players[p].setRDupdate(true);
                        players[p].setsumDelta(0);
                        players[p].setsumDsqr(0);
                        players[p].sett(1);
                    }
            }

/*
 //to find a players convergence
    for(int o=0; o < players.size(); o++)
    {

        if(players[o].getID() == "1286")
            {
                cout << players[o].getgamesPlayed() << "," << players[o].getR() - players[o].getRD() << endl;
            }
    }
*/
        month.clear();
    }

    sort(players.begin(), players.end());
    }

void ctest(vector<Player> players, vector<string> training, vector<string> test1)
    {

    vector<double> errorGlicko;

    for(double i=0; i <= 40; i++)
        {
            clearPlayers(players);

            GlickoUpdate(players,training,i,95);

            errorGlicko.push_back(i);
            errorGlicko.push_back(RMSE(players,test1,"Glicko"));
            errorGlicko.push_back(BD(players,test1,"Glicko"));

            cout << i << "/40" << endl;
        }

ofstream fout3("Glicko.csv");
    if(fout3.fail())
        {
            cerr << "Error writing Glicko" << endl;
        }
    else
        {
        fout3 << "c" << "," << "RMSE" << "," << "BD" << endl;
        for(int i=0; i < errorGlicko.size(); i+=3)
            {
                fout3 << errorGlicko[i] << "," << errorGlicko[i+1] << "," << errorGlicko[i+2] << endl;
            }
        }
fout3.close();

        cout << "c test complete. Please find Glicko.csv" << endl;

    }
