#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
    // TODO
    Graph new_graph(mapFilePath);
    this->map = new_graph;
    this->potentialPathCount = potentialPathCount;
    this->inJourney = false;
    int hashSize = map.TotalVertexCount() * potentialPathCount;
    KeyedHashTable new_hash_table(hashSize);
    this->cachedPaths = new_hash_table;

}

void METUMaps::SetDestination(const std::string& name)
{
    // TODO
    if(this->inJourney){
        PrintUnableToChangeDestination();
        return;
    }
    this->destination = name;
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    // TODO
    if(this->inJourney){
        PrintUnableToChangeStartingLoc();
        return;
    }
    this->startingLoc = name;
}

void METUMaps::StartJourney()
{
    // TODO
    PrintCalculatingRoutes(startingLoc,destination);
    if(this->inJourney){
        PrintAlreadyInJourney();
        return;
    }
    bool v1 = false;
    bool v2 = false;
    int start_id;
    int end_id;
    // check if locations exist or not
    for(int i = 0; i < map.TotalVertexCount(); i++){
        if(map.VertexName(i) == startingLoc){
            v1 = true;
            start_id = i;
        }
        if(map.VertexName(i) == destination){
            v2 = true;
            end_id = i;
        }
    }
    if(!(v1 && v2)){
        this->PrintLocationNotFound();
        return;
    }
    inJourney = true;
    std::vector<std::vector<int> > paths;
    map.MultipleShortPaths(paths,startingLoc,destination, potentialPathCount);
    // set currentRoute to first found path
    currentRoute = paths[0];
    // set currentLoc to startingLoc
    currentLoc = startingLoc;
    // caching goes here;
    std::vector<int> path;
    std::string key;
    for(int i = 0; i < paths.size(); i++){
        path = paths[i];
        if(path.size()>2){
            int temp_size = path.size();
            for(int j = 0; j<temp_size-2; j++){
                //std::cout<< map.VertexName(path[0]) <<std::endl;
                key = GenerateKey(map.VertexName(path[0]),destination);
                cachedPaths.Insert(key,path);
                // remove first element after caching
                path.erase(path.begin());
            }
            // we left with a path with 2 elements
            key = GenerateKey(map.VertexName(path[0]),destination);
            cachedPaths.Insert(key,path);
        }
        // path like A->C
        else{
            key = GenerateKey(map.VertexName(path[0]),destination);
            cachedPaths.Insert(key,path);
        }
    }
    paths.clear();
    path.clear();
}

void METUMaps::EndJourney()
{
    // TODO
    if(!(this->inJourney)){
        this->PrintJourneyIsAlreadFinished();
        return;
    }
    cachedPaths.ClearTable();
    destination.clear();
    startingLoc.clear();
    currentLoc.clear();
    currentRoute.clear();
    inJourney = false;
}

void METUMaps::UpdateLocation(const std::string& name)
{
    // TODO
    if(!this->inJourney){
        PrintNotInJourney();
        return;
    }
    if(name == destination){
        PrintJourneyCompleted();
        return;
    }
    bool v1 = false;
    int start_id;
    int end_id;
    // check if locations exist or not
    for(int i = 0; i < map.TotalVertexCount(); i++){
        if(map.VertexName(i) == name){
            v1 = true;
            start_id = i;
        }
        if(map.VertexName(i) == destination){
            end_id = i;
        }
    }
    if(!v1){
        this->PrintLocationNotFound();
        return;
    }
    currentLoc = name;
    std::vector<std::vector<int> > paths;
    std::vector<int> path;
    std::string key;
    key = GenerateKey(name,destination);
    bool found;
    found = cachedPaths.Find(path,key);
    if(found){
        PrintCachedLocationFound(name,destination);
        currentRoute = path;
        return;
    }
    else{
        PrintCalculatingRoutes(name,destination);
        map.MultipleShortPaths(paths,name,destination, potentialPathCount);
        // set currentRoute to first found path
        currentRoute = paths[0];
        // caching goes here;
        for(int i = 0; i < paths.size(); i++){
            path = paths[i];
            if(path.size()>2){
                int temp_size = path.size();
                for(int j = 0; j<temp_size-2; j++){
                    key = GenerateKey(map.VertexName(path[0]),destination);
                    cachedPaths.Insert(key,path);
                    // remove first element after caching
                    path.erase(path.begin());
                }
                // we left with a path with 2 elements
                key = GenerateKey(map.VertexName(path[0]),destination);
                cachedPaths.Insert(key,path);
            }
            // path like A->C
            else{
                key = GenerateKey(map.VertexName(path[0]),destination);
                cachedPaths.Insert(key,path);
            }
        }
    }
    paths.clear();
    path.clear();
    key.clear();
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}