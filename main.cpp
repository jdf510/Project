#include "projheader.h"

int main()
{
    vector<string> training; //contains all the training games
    vector<string> test1; //contains test set 1
    vector<string> test2; //contains test set 2

ifstream fin("training.txt");
    cout << "Loading training games..." << endl;
    if(fin.fail())
        {
            cerr << "Error reading training games" << endl;
        }
    else
        {
            string temp;
            while(fin >> temp)
                {
                    training.push_back(temp);
                }
        }
fin.close();

ifstream fin2("test1.txt");
    cout << "Loading test set 1..." << endl;
    if(fin2.fail())
        {
            cerr << "Error reading test1" << endl;
        }
    else
        {
            string temp;
            while(fin2 >> temp)
                {
                    test1.push_back(temp);
                }
        }
fin2.close();

ifstream fin3("test2.txt");
    cout << "Loading test set 2..." << endl;
    if(fin3.fail())
        {
            cerr << "Error reading test2" << endl;
        }
    else
        {
            string temp;
            while(fin3 >> temp)
                {
                    test2.push_back(temp);
                }
        }
fin3.close();

    cout << "Loaded " << training.size() /4 << " training games." << endl;
    cout << "Test set 1 contains " << test1.size() /4 << " games." << endl;
    cout << "Test set 2 contains " << test2.size() /4<< " games." << endl;

    cout << "\nFinding players..." << endl;

    vector<Player> players = populatePlayers(training); //fill a vector with unique players from the training set

    cout << players.size() << " unique players found." << endl;

    cout << "\nRanking players..." << endl;

    play(players,training,53871); //plays first 53,871 games only, the rest overlap with the test sets so are not played

    cout << "\nFinding Glicko ratings..." << endl;

    GlickoUpdate(players,training,11,95); //plays first 95 months (53871 games) only, with c = 11

    //Players are ranked according to their Glicko ratings
    cout << "\nRank#\tPlayer stats" << endl;

    for(int i=0; i < 20; i++)
        {
            cout << i+1 << "\t" << players[i] << endl;
        }

/*
    cout << "\nEvaluating predictive power..." << endl;

//  this finds RMSE of all systems on both test sets
    cout << "\nSystem\tRMSE#1\tRMSE#2" << endl;
    cout << "Glicko\t" << RMSE(players,test1,"Glicko") <<"\t"<< RMSE(players,test2,"Glicko") << endl;
    cout << "EloL\t" << RMSE(players,test1,"EloL") <<"\t"<< RMSE(players,test2,"EloL") << endl;
    cout << "EloG\t" << RMSE(players,test1,"EloG") <<"\t"<< RMSE(players,test2,"EloG") << endl;
    cout << "wWins\t" << RMSE(players,test1,"WhiteWins") <<"\t"<< RMSE(players,test2,"WhiteWins") << endl;
    cout << "bWins\t" << RMSE(players,test1,"BlackWins") <<"\t"<< RMSE(players,test2,"BlackWins") << endl;
    cout << "AllDraw\t" << RMSE(players,test1,"Draw") <<"\t"<< RMSE(players,test2,"Draw") << endl;

//  this finds Binomial devience of all systems on both test sets
    cout << "\nSystem\tBD#1\tBD#2" << endl;
    cout << "Glicko\t" << BD(players,test1,"Glicko") <<"\t"<< BD(players,test2,"Glicko") << endl;
    cout << "EloL\t" << BD(players,test1,"EloL") <<"\t"<< BD(players,test2,"EloL") << endl;
    cout << "EloG\t" << BD(players,test1,"EloG") <<"\t"<< BD(players,test2,"EloG") << endl;
    cout << "wWins\t" << BD(players,test1,"WhiteWins") <<"\t"<< BD(players,test2,"WhiteWins") << endl;
    cout << "bWins\t" << BD(players,test1,"BlackWins") <<"\t"<< BD(players,test2,"BlackWins") << endl;
    cout << "AllDraw\t" << BD(players,test1,"Draw") <<"\t"<< BD(players,test2,"Draw") << endl;

    winproportion(training);
*/



    //cout << "\nStarting kfactor optimisation..." << endl;
    //kfactortest(players,training,test1);

    //cout << "\nStarting c optimisation..." << endl;
    //ctest(players,training,test1);


    string key;
    cout << "\n\nEnter any char to end: " << endl;
    cin >> key;

    return 0;
}
