/**
 * Start of a driver file to test connectedcities.cpp
 * CS 210 Fall 2022
 * @author Mitchell Shapiro <mshapiro6805@sdsu.edu>
 * @date Nov 2022
 *
 * Additional testing for connectedcities.cpp
 *
 * I, Kyle Phillips, promise that this exam submission is my own work. I recognize that should this not be the case;
 * I will be subject to plagiarism penalties as outlined in the course syllabus
 * CS 210 Fall 2022
 * @author Kyle Phillips <kphillips4637@sdsu.edu> <825638314>
 * @date Nov 2022
 */
#include "connectedcities.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MOST CASES ARE
 * HIDDEN ON GRADESCOPE.
 */
/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void asserts(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
// If you do comment this out, ignore the
// "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}
//TODO
int main(int argc, char **argv) {

    // Begin Testing
    // A few sample testing code are provided below

    /* Construct a graph for testing
        *    SD ---> DL <--------
        *    ^                   |
        *    |                   |
        *    OD <--- JL <--------|--
        *                        |  |
        *    BV <---             |  |
        *    --->  LA ---> BU    |  |
        *          ^             |  |
        *          |             |  |
        *  SJ ---> SK ---> IV ---|  |
        *                           |
        *  <---------------         |
        *  SF ---> HT ---> NH ------|
        * */
    vector<string> cities_1 {"SD", "LA", "SK", "IV", "JL", "SF",
                             "DL", "HT", "OD", "NH", "BV", "SJ", "BU"};
    vector<pair<string, string>> trainRoutes;
    trainRoutes.emplace_back("JL", "OD");
    trainRoutes.emplace_back("OD", "SD");
    trainRoutes.emplace_back("SD", "DL");
    trainRoutes.emplace_back("BV", "LA");
    trainRoutes.emplace_back("LA", "BV");
    trainRoutes.emplace_back("LA", "BU");
    trainRoutes.emplace_back("SK", "IV");
    trainRoutes.emplace_back("SK", "LA");
    trainRoutes.emplace_back("SJ", "SK");
    trainRoutes.emplace_back("IV", "DL");

    trainRoutes.emplace_back("SF", "HT");
    trainRoutes.emplace_back("HT", "NH");
    trainRoutes.emplace_back("NH", "SF");
    trainRoutes.emplace_back("NH", "JL");

    vector<CityNode> cities =
            ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_1,
                                                                             trainRoutes);

    //cities returned from the above call are sorted according to
    //the ascending order of the city names and
    //the descending order of the size of reachableCities starting from those cities

    for(int d=0; d<cities.size();d++){
        cout << cities.at(d).getCity() << "   ";
        for(int r = 0; r<cities.at(d).getReachableCities().size();r++){
            cout<<cities.at(d).getReachableCities().at(r);
        }
        cout << endl;
    }

            asserts(cities.at(0).getCity() == "HT", "First city should be HT");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(cities.at(0).getReachableCities().size() == 7, "Train starting "
                                                           "from city HT can reach 7 cities");

    asserts(cities.at(1).getCity() == "NH", "Second city should be NH");
    //Reachable cities from NH are [NH, SF, HT, JL, OD, SD, DL]
    asserts(cities.at(1).getReachableCities().size() == 7, "Train starting "
                                                           "from city NH can reach 7 cities");

    asserts(cities.at(2).getCity() == "SF", "Third city should be SF");
    //Reachable cities from SF are [SF, HT, NH, JL, OD, SD, DL]
    asserts(cities.at(2).getReachableCities().size() == 7, "Train starting "
                                                           "from city SF can reach 7 cities");

    asserts(cities.at(3).getCity() == "SJ", "Fourth city should be SJ");
    //Reachable cities from SJ are [SJ, SK, IV, DL, LA, BV, BU]
    asserts(cities.at(3).getReachableCities().size() == 7, "Train starting "
                                                           "from city SJ can reach 7 cities");
    asserts(cities.at(4).getCity() == "SK", "Fifth city should be SK");
    //Reachable cities from SK are [SK, IV, DL, LA, BV, BU]
    asserts(cities.at(4).getReachableCities().size() == 6, "Train starting "
                                                           "from city SK can reach 6 cities");

    asserts(cities.at(5).getCity() == "JL", "Sixth city should be JL");
    //Reachable cities from JL are [JL, OD, SD, DL]
    asserts(cities.at(5).getReachableCities().size() == 4, "Train starting "
                                                           "from city JL can reach 4 cities");

    asserts(cities.at(6).getCity() == "BV", "Seventh city should be BV");
    //Reachable cities from BV are [BV, LA, BU]
    asserts(cities.at(6).getReachableCities().size() == 3, "Train starting "
                                                           "from city BV can reach 3 cities");

    asserts(cities.at(7).getCity() == "LA", "Eighth city should be LA");
    //Reachable cities from LA are [LA, BV, BU]
    asserts(cities.at(7).getReachableCities().size() == 3, "Train starting "
                                                           "from city LA can reach 3 cities");
    asserts(cities.at(8).getCity() == "OD", "Ninth city should be OD");
    //Reachable cities from OD are [OD, SD, DL]
    asserts(cities.at(8).getReachableCities().size() == 3, "Train starting "
                                                           "from city OD can reach 3 cities");
    asserts(cities.at(11).getCity() == "BU", "Twelfth city should be BU");
    //Reachable cities from BU are [BU]
    asserts(cities.at(11).getReachableCities().size() == 1, "Train starting "
                                                            "from city BU can reach 1 city");
    // IMPORTANT:
    // TODO: write your own testing code similar to above as part of the coding
    // required for assignment 4


    // IMPORTANT: You should construct at least one different city graph similar to the one above
    // Also make sure to construct graphs for testing the edge cases,
    // such as empty graph (NO node), one node graph, two nodes graph, etc.
    cout << endl << "All test cases passed for test for test 1!" << endl;

    vector<string> cities_2 {"SC", "VC", "LM", "TU", "OK", "RY", "FH", "LK", "AP"};


    vector<pair<string, string>> trainRoutesAgain;
    trainRoutesAgain.emplace_back("SC", "VC"); //SC->VC->RY->OK->AP->FH->LM->SC : 8
    trainRoutesAgain.emplace_back("SC", "AP");
    trainRoutesAgain.emplace_back("VC", "RY"); //VC->RY->OK->AP->FH->LM->SC : 7
    trainRoutesAgain.emplace_back("VC", "OK");
    trainRoutesAgain.emplace_back("VC", "LK");
    trainRoutesAgain.emplace_back("LM", "SC");
    trainRoutesAgain.emplace_back("TU", "FH");
    trainRoutesAgain.emplace_back("TU", "RY");
    trainRoutesAgain.emplace_back("OK", "AP");
    trainRoutesAgain.emplace_back("OK", "FH");

    trainRoutesAgain.emplace_back("RY", "VC");
    trainRoutesAgain.emplace_back("FH", "LM");
    trainRoutesAgain.emplace_back("LK", "TU");
    trainRoutesAgain.emplace_back("LK", "OK");
                                            //AP : 0

    vector<CityNode> citiesAgain =
            ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_2,
                                                                             trainRoutesAgain);

    for(int o=0; o<citiesAgain.size();o++){
        cout << citiesAgain.at(o).getCity() << "   ";
        for(int u = 0; u<citiesAgain.at(o).getReachableCities().size();u++){
            cout<<citiesAgain.at(o).getReachableCities().at(u);
        }
        cout << endl;
    }

    asserts(citiesAgain.at(0).getCity() == "FH", "First city should be FH");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(0).getReachableCities().size() == 9, "Train starting "
                                                           "from city FH can reach 9 cities");
    asserts(citiesAgain.at(1).getCity() == "LK", "Second city should be LK");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(1).getReachableCities().size() == 9, "Train starting "
                                                           "from city LK can reach 9 cities");
    asserts(citiesAgain.at(2).getCity() == "LM", "Third city should be LM");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(2).getReachableCities().size() == 9, "Train starting "
                                                           "from city LM can reach 9 cities");
    asserts(citiesAgain.at(3).getCity() == "OK", "Fourth city should be OK");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(3).getReachableCities().size() == 9, "Train starting "
                                                           "from city OK can reach 9 cities");
    asserts(citiesAgain.at(4).getCity() == "RY", "Fifth city should be RY");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(4).getReachableCities().size() == 9, "Train starting "
                                                           "from city RY can reach 9 cities");
    asserts(citiesAgain.at(5).getCity() == "SC", "Sixth city should be SC");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(5).getReachableCities().size() == 9, "Train starting "
                                                           "from city SC can reach 9 cities");
    asserts(citiesAgain.at(6).getCity() == "TU", "Seventh city should be TU");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(6).getReachableCities().size() == 9, "Train starting "
                                                           "from city TU can reach 9 cities");
    asserts(citiesAgain.at(7).getCity() == "VC", "Eighth city should be VC");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(7).getReachableCities().size() == 9, "Train starting "
                                                           "from city VC can reach 9 cities");
    asserts(citiesAgain.at(8).getCity() == "AP", "Ninth city should be AP");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(citiesAgain.at(8).getReachableCities().size() == 1, "Train starting "
                                                           "from city AP can reach 1 cities");


    cout << endl << "All test cases passed for test for test 2!" << endl;
    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}