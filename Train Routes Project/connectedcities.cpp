#include <map>
#include <algorithm>
#include "connectedcities.h"

/** Main function needed for connectedcities.h and driver to work.
* Finds reachable cities for each set of given cities and train routes. Then puts them in order based on size.
*
* I, Kyle Phillips, promise that this exam submission is my own work. I recognize that should this not be the case;
* I will be subject to plagiarism penalties as outlined in the course syllabus
* CS 210 Fall 2022
* @author Kyle Phillips <kphillips4637@sdsu.edu> <825638314>
* @date Nov 2022
*/

/**
 * <p>
 * Part A 
 * 
-----------------------------------------------------------------------------------
----
 * For each city in a city list, find the list of reachable cities starting from 
the city 
 * following the train routes, and sort the cities in the descending order based on
the 
 * number of their reachable cities.  
 * 
 * Required specifications - 
 *
 * Given a list of cities, and a list of one-way train routes from one city to 
another:
 *
 * 1) Create a graph with each node in the graph as an instance of the CityNode 
class,
 *    the graph can use any STL collection by your choice.
 *
 * 2) Populate the direct routes information to each CityNode's directRoutedCities 
collection.
 *    This is like an adjacency list graph representation.
 *
 * 3) For each city node in the graph, use Depth First Search algorithm to find all
reachable 
 *    cities starting from the city following the train routes and store those 
reachable cities to 
 *    the CityNode's reachableCities collection. 
 *
 *    IMPORTANT: The reachable cities must include the starting city itself.  
 *
 *    Note: The train route can go from the starting city and stop at several 
cities 
 *          before reaching the destination city, all cities including the starting
city and 
 *          the destination city along the path would be counted as reachable 
cities from 
 *          the city where the train starts.
 *
 * 4) Sort the cities in the descending order based on the number of their 
reachable cities,
 *    so that after sorting, starting from the first city in the sorted order, the 
train can 
 *    reach the greatest number of destination cities following the given one-way 
routes. 
 *
 * 5) You must use a RECURSIVE algorithm to implement the Depth First Search part 
to find
 *    all reachable cities from a starting city given the train routes, using an 
iterative 
 *    approach would result in a 30% penalty to your assignment 4 grade.  
 *
 * 6) You may add necessary helper functions as needed. Follow the comments for 
hints.
 * 
 * Assumptions - 
 * 1) Each city is represented by a unique two-letter code like "SD", "LA", 
 *    "SF", "SJ", "NY", etc.
 * 2) Each one-way train route is represented by a pair of city codes; for example,
 *    route {"SD", "LA"} means train can drive one-way from San Diego (SD) to 
 *    Los Angeles (LA). 
 *
 * <p>
 * Part B
 * 
-----------------------------------------------------------------------------------
----
 * Show the upper bound of the time complexity of this function would be O(c^2 + c 
* r) 
 * where:
 * c is the number of cities
 * r is the number of direct routes between cities
 * 
 * 
-----------------------------------------------------------------------------------
----
 * @param  cities  a list of cities with each city identified by a two letter code
 * @param  routes  pairs of one-way train routes with each one-way train route 
represented 
 *                 by a pair of city codes; for example, route {"SD", "LA"} means 
train 
 *                 can go one-way from San Diego (SD) to Los Angeles (LA).
 *
 *                 NOTE: examples of routes are { {"SD", "LA"},
 *                                                {"LA", "SJ"},
 *                                                {"SJ", "SF"}
 *                                              }   
 *                       refer to driver.cpp for more examples.  
 *
 * @return       A list of CityNode in the descending order based on the number of 
their 
 *               reachable cities following the train routes
 
* @see         
*/
vector<CityNode> ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(
        vector<string> cities,
        vector<pair<string, string>> trainRoutes) {

    if(cities.size() == 0){             /** checking if there were 0 cities inputted */
        return vector<CityNode>();
    }

    vector<CityNode> cityNodeList = vector<CityNode>();     /** creating a vector of CityNode objects to access the
 *                                                              functions in the .h file for each city */
    for(int k =0; k<cities.size(); k++){
    cityNodeList.emplace(cityNodeList.end(),CityNode(cities.at(k)));
    }

    for(int t =0; t<cities.size();t++){                   /** getting all of the adjacent cities lists for each city */
        for (int u = 0; u < trainRoutes.size(); u++) {
            if (cities.at(t) == trainRoutes.at(u).first) {
                cityNodeList.at(t).addADirectRoutedCity(trainRoutes.at(u).second);
            }
        }
    }

    for(int p =0; p<cityNodeList.size();p++){           /** getting all of the reachable cities for each city */
        bool T=true;
        vector<string> reachableCities = vector<string>();  /** using the boolean variable and some empty string vectors
 *                                                              to help with the recursive function */
        vector<string> visitedCities = vector<string>();
        vector<string> directCities = vector<string>();
        addReachableCities(cityNodeList.at(p).getCity(),reachableCities,visitedCities, T,
                           directCities,cityNodeList);

        cityNodeList.at(p).setReachableCities(reachableCities);
    }

    stable_sort(cityNodeList.begin(), cityNodeList.end(),   /** sorting my reachable cities list length and using  */
             [](const CityNode &a, const CityNode &b)->bool     /** alphabetical order as a tiebreaker */
        {
            if(a.getReachableCities().size() > b.getReachableCities().size()){
                return true;
            }
            if(a.getReachableCities().size() == b.getReachableCities().size()){
                if(int(a.getCity().at(0)) == int(b.getCity().at(0))){
                    if(int(a.getCity().at(0)) + int(a.getCity().at(1))
                    < int(b.getCity().at(0)) + int(b.getCity().at(1))){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                if (int(a.getCity().at(0)) < int(b.getCity().at(0))) {
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        });

    return cityNodeList;
}

void ConnectedCities::addReachableCities(string city, vector<string>& reachableCities,
                                         vector<string>& visitedCities,bool T,
                                         vector<string> directCities,
                                         vector<CityNode> cityNodeList){
    if(isInVector(visitedCities, city)== true){     /** one of my base cases: checking if we've already visited the
 *                                                   current city... if so, I will not let the recursion run again*/
        T=false;
    }
    else {
        visitedCities.push_back(city);
    }


    if (isInVector(reachableCities, city) == false) {   /** my other base case: checking if the city that we've
 *                      arrived at is already in the reachable cities vector... if it is not, we need to add it*/
        reachableCities.push_back(city);
    }
    for(int t=0; t<cityNodeList.size();t++){         /** this for loop searches the CityNode objects until it finds
 * the correct city. Once it does find the right city it will set directCities to that cities' adjacent cities*/
        if (cityNodeList.at(t).getCity() == city) {
        directCities = cityNodeList.at(t).getDirectRoutedCities();
        }
    }

    if(T== true){         /** checking if we should run recursion again */
        for (int i =0; i<directCities.size(); i++) {     /** if we can, run it for each adjacent city */
            addReachableCities(directCities.at(i), reachableCities, visitedCities, T,
                               directCities,cityNodeList);

        }
    }

}


bool ConnectedCities::isInVector(vector<string> vector, string city){   /** a simple helper function to find a string
 *                                                                          in a vector of strings */
    for(int r =0; r<vector.size();r++){
        if(vector.at(r) == city){
            return true;
        }
    }
    return false;
}