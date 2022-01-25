#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger newPassenger(firstname, lastname);
    passengers.insert(newPassenger);
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger myPassenger(firstname, lastname);
    return &(passengers.search(myPassenger)->data);
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    /* TODO */
    Flight newFlight(flightCode,departureTime,arrivalTime,departureCity, arrivalCity,economyCapacity,businessCapacity);
    flights.insert(newFlight);
}
void AirlineReservationSystem::helperFlight(BSTNode<Flight> *root, std::vector<Flight *> &SearchedFlights, const std::string &departureCity, const std::string &arrivalCity){
    if (root == NULL){
        return;
    }
    else{
        if (((departureCity == (root->data).getDepartureCity()) && (arrivalCity == (root->data).getArrivalCity()))){
            SearchedFlights.push_back(&root->data);
        }
        helperFlight(root->left,SearchedFlights, departureCity,arrivalCity);
        helperFlight(root->right,SearchedFlights, departureCity,arrivalCity);
    }
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    /* TODO */
    BSTNode<Flight> * root;
    root = flights.getRoot();
    std::vector<Flight *> SearchedFlights;
    helperFlight(root, SearchedFlights, departureCity,arrivalCity);
    return SearchedFlights;

}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger * passeng;
    passeng = searchPassenger(firstname,lastname);
    if(passeng){
        Flight newFlight(flightCode,"departureTime","arrivalTime","departureCity", "arrivalCity",10,10);
        Flight * myFlight;
        myFlight = &flights.search(newFlight)->data;
        if(myFlight){
            Ticket newTicket(passeng, myFlight, ticketType);
            myFlight->addTicket(newTicket);
        }
    }
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger * passeng;
    passeng = searchPassenger(firstname,lastname);
    if(passeng){
        Flight newFlight(flightCode,"departureTime","arrivalTime","departureCity", "arrivalCity",10,10);
        Flight * myFlight;
        myFlight = &flights.search(newFlight)->data;
        if(myFlight){
            Ticket newTicket(passeng, myFlight, ticketType);
            this->freeTicketRequests.enqueue(newTicket);
        }
    }
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    /* TODO */
    Flight newFlight(flightCode,"departureTime","arrivalTime","departureCity", "arrivalCity",10,10);
    Flight * myFlight;
    int economyCapacity;
    int businessCapacity;
    std::string myFlightCode;
    TicketType type;
    myFlight = &flights.search(newFlight)->data;
    // to traverse through the queue, I will add terminator to the end.
    // and dequeue it after all process is done.
    Passenger terminatorPass("terminator","213_terminator_unique_string");
    Ticket terminator(&terminatorPass, myFlight, economy);
    this->freeTicketRequests.enqueue(terminator);

    if(myFlight){
        economyCapacity = myFlight->getEconomyCapacity();
        businessCapacity = myFlight->getBusinessCapacity();
        if(this->freeTicketRequests.isEmpty()){
            myFlight->setCompleted(true);
            return;
        }
        else{
            Ticket temp;
            while((this->freeTicketRequests.peek().getPassenger()->getLastname() != "213_terminator_unique_string")){
                type = this->freeTicketRequests.peek().getTicketType();
                myFlightCode = this->freeTicketRequests.peek().getFlight()->getFlightCode();
                if(myFlightCode == myFlight->getFlightCode()){
                    if(type == economy){
                        if(economyCapacity > 0){
                            myFlight->addTicket(this->freeTicketRequests.dequeue());
                        }
                        else{
                            temp = this->freeTicketRequests.dequeue();
                            this->freeTicketRequests.enqueue(temp);
                        }
                    }
                    else if(type == business){
                        if(businessCapacity > 0){
                            myFlight->addTicket(this->freeTicketRequests.dequeue());
                        }
                        else{
                            temp = this->freeTicketRequests.dequeue();
                            this->freeTicketRequests.enqueue(temp);
                        }
                    }
                }
                else{
                    temp = this->freeTicketRequests.dequeue();
                    this->freeTicketRequests.enqueue(temp);
                }
            }
            // after traversing all of the queue elements
            // I will dequeue the terminator
            this->freeTicketRequests.dequeue();
            // mark the flight as completed
            myFlight->setCompleted(true);
            return;
        }
    }
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
