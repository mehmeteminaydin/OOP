#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    int list_size = this->vertexList.size();
    for(int i = 0; i < list_size; i++){
        if (this->vertexList[i].name == vertexName){
            throw DuplicateVertexNameException();
            return;
        }
    }
    // if there is no dublicate, we can add the vertex
    GraphVertex new_vertex = GraphVertex();
    new_vertex.name = vertexName;
    new_vertex.edgeCount = 0;
    vertexList.push_back(new_vertex);
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    // check dublicate name
    if(fromVertexName == toVertexName){
        return false;
    }
    // check both of them exist
    bool exists1 = false;
    bool exists2 = false;
    int list_size = this->vertexList.size();
    int id_0;
    int id_1;
    for(int i = 0; i < list_size; i++){
        if (this->vertexList[i].name == fromVertexName){
            exists1 = true;
            id_0 = i;
        }
        else if(this->vertexList[i].name == toVertexName){
            exists2 = true;
            id_1 = i;
        }
    }
    // if any of them does not exists, then return false;
    if(!(exists1 && exists2)){
        throw VertexNotFoundException();
        return false;
    }
    // check if edge already exists
    for(int i = 0; i < edgeList.size(); i++){
        if(edgeList[i].vertexId0 == id_0 && edgeList[i].vertexId1 == id_1){
            return false;
        }
        if(edgeList[i].vertexId0 == id_1 && edgeList[i].vertexId1 == id_0){
            return false;
        }
    }
    GraphEdge new_edge = GraphEdge();
    new_edge.masked = false;
    new_edge.weight = weight;
    for(int i = 0; i < list_size; i++){
        if(this->vertexList[i].name == fromVertexName){
            new_edge.vertexId0 = i;
            // check if it exceeds the limit
            if(vertexList[i].edgeCount == MAX_EDGE_PER_VERTEX){
                throw TooManyEdgeOnVertexExecption();
                return false;
            }
            vertexList[i].edgeCount++;
        }
        if(this->vertexList[i].name == toVertexName){
            new_edge.vertexId1 = i;
            // check if it exceeds the limit
            if(vertexList[i].edgeCount == MAX_EDGE_PER_VERTEX){
                throw TooManyEdgeOnVertexExecption();
                return false;
            }
            vertexList[i].edgeCount++;
        }
    }

    edgeList.push_back(new_edge);
    vertexList[new_edge.vertexId0].edgeIds[vertexList[new_edge.vertexId0].edgeCount-1] = edgeList.size()-1;
    vertexList[new_edge.vertexId1].edgeIds[vertexList[new_edge.vertexId1].edgeCount-1] = edgeList.size()-1;
    return true;
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    // check both of them exist
    bool exists1 = false;
    bool exists2 = false;
    int list_size = this->vertexList.size();
    int id_0;
    int id_1;
    for(int i = 0; i < list_size; i++){
        if (this->vertexList[i].name == from){
            exists1 = true;
            id_0 = i;
        }
        else if(this->vertexList[i].name == to){
            exists2 = true;
            id_1 = i;
        }
    }
    // if any of them does not exists, then return false;
    if(!(exists1 && exists2)){
        throw VertexNotFoundException();
        return false;
    }
    // Find id of from and to with the help of helper function
    int from_id;
    int to_id;
    from_id = getId(from);
    to_id = getId(to);
    int vertex_number = vertexList.size();
    // define min heap;
    std::priority_queue<DistanceVertexIdPair> pqueue;
    // define flag array to know vertices are marked or not
    std::vector<bool> flag(vertex_number, false);
    std::vector<int> previous(vertex_number, -1);
    std::vector<DistanceVertexIdPair> distance;
    
    for(int i = 0; i < vertex_number; i++){
        DistanceVertexIdPair temp_pair(i, LARGE_NUMBER);
        if (i == from_id){
            temp_pair.currentWeight = 0;
        }
        distance.push_back(temp_pair);
    }
    pqueue.push(distance[from_id]);
    int temp_id;
    GraphEdge temp_edge;
    DistanceVertexIdPair prev_vertex(-1, -1);
    
    while(!(pqueue.empty())){
        prev_vertex.vId = pqueue.top().vId ;
        prev_vertex.currentWeight = pqueue.top().currentWeight ;
        flag[prev_vertex.vId] = true ;
        pqueue.pop() ;
        
        for(int i = 0; i < vertexList[prev_vertex.vId].edgeCount; i++){
            temp_edge = edgeList[vertexList[prev_vertex.vId].edgeIds[i]];
            // chech whether edge is masked or not, if so, continue;
            if (temp_edge.masked == true){
                continue;
            }
            else{
                if(temp_edge.vertexId0 == prev_vertex.vId)
                {
                    // keep id as temporary variable to ease coding further
                    temp_id = temp_edge.vertexId1;
                    if(flag[temp_id] == true){
                        continue;
                    }
                    else if ((temp_edge.weight + prev_vertex.currentWeight) < distance[temp_id].currentWeight){
                        distance[temp_id].currentWeight = temp_edge.weight + prev_vertex.currentWeight ;
                        previous[temp_id] = prev_vertex.vId;
                    }
                }
                else if(temp_edge.vertexId1 == prev_vertex.vId){
                    temp_id = temp_edge.vertexId0;
                    // check whether this vertex is marked or not
                    if(flag[temp_id] == true){
                        continue;
                    }
                    else if((temp_edge.weight + prev_vertex.currentWeight) < distance[temp_id].currentWeight){
                        distance[temp_id].currentWeight = temp_edge.weight + prev_vertex.currentWeight;
                        previous[temp_id] = prev_vertex.vId;
                    }
                }
            }
            // add the vertex to the priority queue
            pqueue.push(distance[temp_id]);
        }
        
    }
    if (previous[to_id] != -1)
    {
        // to find the path, we need a temporary array
        std::vector<int> temp_arr;
        temp_arr.push_back(to_id);
        for (int i = 1; i < vertex_number; i++){
            if(previous[temp_arr[temp_arr.size()-1]] == -1){
                break;
            }
            else{
                temp_arr.push_back(previous[temp_arr[temp_arr.size()-1]]);
            }
        }
        if(temp_arr[temp_arr.size()-1] == from_id){
            for(int i = temp_arr.size() - 1; i >= 0; i--){
                orderedVertexIdList.push_back(temp_arr[i]);
            }
            // clear all the temporary data and return true
            flag.clear();
            temp_arr.clear();
            distance.clear();
            previous.clear();
            return true;
        }
        // clear all the temporary data and return false if there is no path
        flag.clear();
        temp_arr.clear();
        distance.clear();
        previous.clear();
        if(orderedVertexIdList.empty()){
            return false;
        }
    }
    // clear all the temporary data
    flag.clear() ;
    distance.clear() ;
    previous.clear() ;
    return false ;
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    /*
    Unmask all the edges
• Find the shortest path normally
• Add the found path to the orderedVertexIdList
• Refer to it as the last found path
• Until numberOfShortestPaths is reached
– Mask the highest weighted edge on the last found path
– Run shortest path on the graph
– If any other shortest path could not be found; terminate.
– Add the found path to the orderedVertexIdList
– Refer the found path as last found path.
• Unmask all the edges
    */
    // check vertices exist
    bool v1 = false;
    bool v2 = false;
    for(int k = 0; k < vertexList.size(); k++){
        if(k == getId(from)){
            v1 = true;
        }
        if(k == getId(to)){
            v2 = true;
        }
    }
    // otherwise return -1;
    if(!(v1 && v2)){
        throw VertexNotFoundException();
        return -1;
    }
    this->UnMaskAllEdges();
    std::vector<int> last_path;
    bool done;
    done = this->ShortestPath(last_path,from,to);
    if(done){
        orderedVertexIdList.push_back(last_path);
    }
    else{
        return 0;
    }
    int id_0;
    int id_1;
    // to keep max weighted edge, we need an array,
    int max_edge[2];

    // temp weight variable
    int temp_weight;
    while(orderedVertexIdList.size()!= numberOfShortestPaths){
        temp_weight = 0;
        for(int i = 0; i < last_path.size()-1; i++){
            id_0 = last_path[i];
            id_1 = last_path[i+1];
            // find max weighted edge
            for(int j = 0; j < edgeList.size(); j++){
                if(edgeList[j].vertexId0 == id_0 && edgeList[j].vertexId1 == id_1){
                    if(edgeList[j].weight > temp_weight){
                        temp_weight = edgeList[j].weight;
                        max_edge[0] = id_0;
                        max_edge[1] = id_1;
                    }
                }
                else if(edgeList[j].vertexId0 == id_1 && edgeList[j].vertexId1 == id_0){
                    if(edgeList[j].weight > temp_weight){
                        temp_weight = edgeList[j].weight;
                        max_edge[0] = id_1;
                        max_edge[1] = id_0;
                    }
                }
            }
        }
        // mask found edge
        for(int j = 0; j < edgeList.size(); j++){
            if(edgeList[j].vertexId0 == max_edge[0] && edgeList[j].vertexId1 == max_edge[1]){
                edgeList[j].masked = true;
            }
            else if(edgeList[j].vertexId0 == max_edge[1] && edgeList[j].vertexId1 == max_edge[0]){
                edgeList[j].masked = true;
            }
        }
        last_path.clear();
        done = this->ShortestPath(last_path,from,to);
        if(done){
            orderedVertexIdList.push_back(last_path);
        }
        else{
            return orderedVertexIdList.size();
        }
    }
    this->UnMaskAllEdges();
    return orderedVertexIdList.size();
}

int Graph::getId(const std::string& vertexName)const{
    for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i].name == vertexName){
            return i;
        }
    }
    return -1;
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    int id_0;
    int id_1;
    for(int i = 0; i < vertexNames.size(); i++){
        id_0 = this->getId(vertexNames[i].s0);
        id_1 = this->getId(vertexNames[i].s1);
        if(id_0 == -1 || id_1 == -1){
            throw VertexNotFoundException();
            continue;
        }
        else{
            for(int j =0; j<this->edgeList.size(); j++){
                if(edgeList[j].vertexId0 == id_0 && edgeList[j].vertexId1 == id_1){
                    edgeList[j].masked = true;
                }
                if(edgeList[j].vertexId0 == id_1 && edgeList[j].vertexId1 == id_0){
                    edgeList[j].masked = true;
                }
            }
        }
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    int id_0;
    int id_1;
    for(int i = 0; i < vertexNames.size(); i++){
        id_0 = this->getId(vertexNames[i].s0);
        id_1 = this->getId(vertexNames[i].s1);
        if(id_0 == -1 || id_1 == -1){
            throw VertexNotFoundException();
            continue;
        }
        else{
            for(int j =0; j<this->edgeList.size(); j++){
                if(edgeList[j].vertexId0 == id_0 && edgeList[j].vertexId1 == id_1){
                    edgeList[j].masked = false;
                }
                if(edgeList[j].vertexId0 == id_1 && edgeList[j].vertexId1 == id_0){
                    edgeList[j].masked = false;
                }
            }
        }
    }
}

void Graph::UnMaskAllEdges()
{
    for(int i = 0; i < edgeList.size(); i++){
        edgeList[i].masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name)
{
    if(getId(name) == -1){
        throw VertexNotFoundException();
        return;
    }
    for(int i = 0; i < vertexList[getId(name)].edgeCount; i++){
        edgeList[vertexList[getId(name)].edgeIds[i]].masked = true;
    }
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    if(getId(name) == -1){
        throw VertexNotFoundException();
        return;
    }
    for(int i = 0; i < vertexList[getId(name)].edgeCount; i++){
        edgeList[vertexList[getId(name)].edgeIds[i]].masked = false;
    }
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    int id_0 = getId(vName0);
    int id_1 = getId(vName1);
    if(id_0 == -1 || id_1 == -1){
        throw VertexNotFoundException();
        return;
    }
    for(int i = 0; i < edgeList.size(); i++){
        if(edgeList[i].vertexId0 == id_0 && edgeList[i].vertexId1 == id_1){
            edgeList[i].weight = newWeight;
            return;
        }
        if(edgeList[i].vertexId0 == id_1 && edgeList[i].vertexId1 == id_0){
            edgeList[i].weight = newWeight;
            return;
        }
    }
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    for(int i = 0; i < edgeList.size(); i++){
        if(edgeList[i].vertexId0 == vId0 && edgeList[i].vertexId1 == vId1){
            edgeList[i].weight = newWeight;
            return;
        }
        if(edgeList[i].vertexId0 == vId1 && edgeList[i].vertexId1 == vId0){
            edgeList[i].weight = newWeight;
            return;
        }
    }
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    return vertexList[vertexId].name;
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    int id_0;
    int id_1;
    int sum = 0;
    bool flag;
    bool v1 = false;
    bool v2 = false;
    for(int i = 0; i < orderedVertexIdList.size()-1; i++){
        id_0 = orderedVertexIdList[i];
        id_1 = orderedVertexIdList[i+1];
        // check vertices are equal to each other
        if(id_0 == id_1){
            return -1;
        }
        // check vertices exist
        for(int k = 0; k < vertexList.size(); k++){
            if(k == id_0){
                v1 = true;
            }
            if(k == id_1){
                v2 = true;
            }
        }
        // otherwise return -1;
        if(!(v1 && v2)){
            throw VertexNotFoundException();
            return -1;
        }
        flag = false;
        for(int j = 0; j < edgeList.size(); j++){
            if(edgeList[j].vertexId0 == id_0 && edgeList[j].vertexId1 == id_1){
                sum += edgeList[j].weight;
                flag = true;
            }
            else if(edgeList[j].vertexId0 == id_1 && edgeList[j].vertexId1 == id_0){
                sum += edgeList[j].weight;
                flag = true;
            }
        }
        if(!flag){
            return -1;
        }
    }
    return sum;
}