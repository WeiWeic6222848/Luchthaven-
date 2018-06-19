//
// Created by c6222 on 2018/3/8.
//

#include "Airportsim.h"
#include "DesignByContract.h"
#include "AirportUtils.h"
#include "Runway.h"
#include "Taxipoint.h"
#include "Gate.h"

Airportsim::Airportsim(const string& filename) {
    _InitCheck=this;
    addSourcefile(filename);
    ENSURE(ProperInitialized(),"This airportsim object failed to initialize properly");
}


/**
 * @param value a string of only digits
 * @return the int value of that string, logically
 */

void Airportsim::removeAirport(Airport* airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling removeairport");
    Airport* todelete=NULL;
    for (unsigned int i = 0; i < Airports.size(); ++i) {
        if (airport==Airports[i]){
            todelete=airport;
            Airports.erase(Airports.begin()+i);
            break;
        }
    }
    if(todelete){
        delete (todelete);
    }
    ENSURE(find(Airports.begin(),Airports.end(),airport)==Airports.end(),"removeairport postcondition failed");
}


void Airportsim::addSourcefile(const string &filename) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling addsourcefile");
    REQUIRE(fileExist(filename),"Giving filename must exist when calling addsourcefile");
    /*TiXmlDocument XMLfile;
    int errors=0;
    int aprroaching=0;
    XMLfile.LoadFile(filename.c_str());
    Airport* airport;
    if(XMLfile.Error()){
        cerr<<"this xml contains syntax error, trying to read as much as possible"<<endl;
    }
        TiXmlElement *Root = XMLfile.RootElement();
        if (Root) {
            TiXmlElement *airportelement=Root->FirstChildElement("AIRPORT");
            if (airportelement->FirstChildElement("name")&&airportelement->FirstChildElement("iata")&&airportelement->FirstChildElement("callsign")&&airportelement->FirstChildElement("gates")){
                try{
                    string name=airportelement->FirstChildElement("name")->GetText();
                    string iata=airportelement->FirstChildElement("iata")->GetText();
                    string callsign=airportelement->FirstChildElement("callsign")->GetText();
                    int gates;
                    try{gates=stoi(airportelement->FirstChildElement("gates")->GetText());}
                    catch(...){
                        cerr<< "Airport with name "+name+" has a number of gate which isn't a integer"<<endl;
                        return;
                    }
                    int passenger=0;
                    if (airportelement->FirstChildElement("passenger")) {
                        try {
                            passenger = stoi(airportelement->FirstChildElement("passenger")->GetText());
                        } catch (...) {
                            cerr << "Airport with name " + name + " has a passenger attribute which isn't a interger" << endl;
                            return;
                        }
                    }
                    airport=new Airport(name,iata,callsign,gates,passenger);
                    Airports.push_back(airport);
                }
                catch(...){
                    cerr<<"there's a syntax error at airport element";
                    return;
                }
            }
            else{
                cerr<<"airport doesn't have the required attributes";
                return;
            }

            for (TiXmlElement* childelement=Root->FirstChildElement();childelement!= NULL;childelement=childelement->NextSiblingElement()){ string Elementname=childelement->Value();
                if(Elementname=="AIRPORT"){}
                else if (Elementname=="RUNWAY"&&childelement->FirstChildElement("name")&&childelement->FirstChildElement("airport")){
                    string name=childelement->FirstChildElement("name")->GetText();
                    string airportname=childelement->FirstChildElement("airport")->GetText();
                    bool airportfound=false;
                    for (unsigned int i = 0; i < Airports.size(); ++i) {
                        if(Airports[i]->getIata()==airportname){
                            Runway* runway=new Runway(name,Airports[i]);
                            Airports[i]->addRunway(runway);
                            airportfound=true;
                        }
                    }
                    if(!(airportfound)){
                        cerr<<"cannot find airpont: "<<airportname<<" for the runway with name:"<<name<<endl;
                        cerr<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                        errors++;
                        break;
                    }
                }
                else if (Elementname=="AIRPLANE"&&childelement->FirstChildElement("number")&&childelement->FirstChildElement("callsign")&&childelement->FirstChildElement("model")&&childelement->FirstChildElement("status")){
                    string number=childelement->FirstChildElement("number")->GetText();
                    string callsign=childelement->FirstChildElement("callsign")->GetText();
                    string model=childelement->FirstChildElement("model")->GetText();
                    string status=childelement->FirstChildElement("status")->GetText();
                    if(status!="Approaching"&&status!="Stand at gate"){
                        cerr<<"Airplane status of " + number+" is not correct"<<endl;
                        cerr<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                        errors++;
                        break;
                    }
                    int passengercapacity=10;
                    if(childelement->FirstChildElement("passengercapacity")){
                        try {
                            passengercapacity = stoi(childelement->FirstChildElement("passengercapacity")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a passengercapacity attribute which isn't a interger"<<endl;
                            errors++;
                            continue;
                        }
                    }
                    int passenger=passengercapacity;

                    if(childelement->FirstChildElement("passenger")){
                        try {
                            passenger = stoi(childelement->FirstChildElement("passenger")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a passenger attribute which isn't a interger"<<endl;
                            errors++;
                            continue;
                        }
                    }

                    int fuel=100;
                    if(childelement->FirstChildElement("fuel")){
                        try {
                            fuel = stoi(childelement->FirstChildElement("fuel")->GetText());
                        }catch (...){
                            cerr<<"Airplane with number "+number+" has a fuel attribute which isn't a interger"<<endl;
                            errors++;
                            continue;
                        }
                    }
                    Airplane* a=new Airplane(status,passenger,fuel,number,callsign,model,passengercapacity);
                    Airplanes.push_back(a);

                    if (status=="standing at gate"){
                        int gateforairplane=airport->findFreeGates();
                        passenger=0;
                        if(gateforairplane==-1){
                            cerr<<airport->getName()<<" has more airplanes at gates than it's gate"<<endl;
                            cerr<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                            break;
                        }
                        else{
                            airport->parkAirplane(gateforairplane,a);
                        }
                    }
                    else{
                        if(aprroaching==0){
                            aprroaching++;
                        }
                        else{
                            cerr<<airport->getName()<<" has more than one airplane approaching"<<endl;
                            cerr<<airport->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
                            break;
                        }
                    }
                    airport->addAirplane(a);
                }
                else{
                    cerr<<"element "+ Elementname+" is not recongized by the airsim system, skipping"<<endl;
                    errors++;
                    continue;
                }
            }
        }
    if(errors==0){
        cout<<filename +" read no error"<<endl;
    }else{
        cout<<filename +" read with " <<errors<< " errors"<<endl;
    }
    for (unsigned int j = 0; j < Airports.size(); ++j) {
        if (Airports[j]->getRunways().empty()) {
            cerr<<Airports[j]->getName()<<" has no runway or a wrong amount of runway."<<endl;
            cerr<<Airports[j]->getName()<<" got removed from airportslist beacause of inconsistency"<<endl;
            removeAirport(Airports[j]);
        }
    }
    return;*/
    ofstream a;
    AirportsimImporter::importAirportsim(filename.c_str(),a,*this);
    cout<<a;
}

Airport* Airportsim::findAirport(const string &iata) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findairport");
    for (unsigned int j = 0; j < Airports.size(); ++j) {
        if(Airports[j]->getIata()==iata){
            return Airports[j];
        }
    }
    cerr<<"no airport found with iata "+iata;
    return NULL;
}

Airplane *Airportsim::findAirplane(const string &number) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findairplane");
    for (unsigned int j = 0; j < Airplanes.size(); ++j) {
        if(Airplanes[j]->getNumber()==number){
            return Airplanes[j];
        }
    }
    cerr<<"no airplane found with number "+number;
    return NULL;
}

Runway *Airportsim::findRunway(const string &number, const string &iata) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling findrunway");
    Airport* air=findAirport(iata);
    if (air==NULL){
        cerr<<"cannot find the giving airport with iata "+iata;
        return NULL;
    }
    return air->findRunway(number);
}


const vector<Airport*> &Airportsim::getAirports() const {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling getAirports");
    return Airports;
}

const vector<Airplane*> &Airportsim::getAirplanes() const {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling getAirplanes");
    return Allplanes;
}

bool Airportsim::ProperInitialized() const{
    return _InitCheck==this;
}

Airportsim::Airportsim(int argc, const char **argv) {
    _InitCheck=this;
    for (int i = 1; i < argc; ++i) {
        addSourcefile(argv[i]);
    };
    ENSURE(ProperInitialized(),"Airportsim object failed to initialize properly");
}

Airportsim::~Airportsim() {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling Destructor");
    for (unsigned int i = 0; i < Airports.size(); ++i) {
        delete Airports[i];
    }
    for (unsigned int j = 0; j < Airplanes.size(); ++j) {
        delete Airplanes[j];
    }
}

void Airportsim::addAirport(Airport *airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling addAirport");
    Airports.push_back(airport);
    ENSURE(findAirport(airport->getIata())!=NULL,"addAirport postcondition failed");
}

void Airportsim::addAirplane(Airplane *airplane) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling addAirplane");
    Airplanes.push_back(airplane);
    Allplanes.push_back(airplane);
    ENSURE(find(Airplanes.begin(),Airplanes.end(),airplane)!=Airplanes.end()&&find(Allplanes.begin(),Allplanes.end(),airplane)!=Allplanes.end(),"addAirplane postcondition failed");
}

Airportsim::Airportsim() {
    _InitCheck=this;
    ENSURE(ProperInitialized(),"this object failed to initialize properly");
}



 //future functions
void Airportsim::Simulate() {
     REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling Simulate");
     ofstream file;
     for (unsigned int k = 0; k < Airports.size(); ++k) {
         string filename="../output/floormap_state_airport["+Airports[k]->getIata()+"].txt";
         file.open(filename.c_str(),ios::out);
         file.close();
     }
     for (unsigned int k = 0; k < Airports.size(); ++k) {
         string filename="../output/"+Airports[k]->getIata()+"_Tower.txt";
         file.open(filename.c_str(),ios::out);
         file.close();
     }

     for (unsigned int l = 0; l < Airplanes.size(); ++l) {
         string filename="../output/"+Airplanes[l]->getCallsign()+".txt";
         file.open(filename.c_str(),ios::out);
         file.close();
     }
     vector<int> airplanestoremove;
     bool  alreadypushed=false;
     int chillingcounter=0;

     //int toweraction=0;
     while (!Airplanes.empty()){
         airplanestoremove.clear();
         Airplane::Airplaneallowedstatus status;

         for (unsigned int j = 0; j < Airplanes.size(); ++j) {
             alreadypushed=false;
             chillingcounter=0;
             do{
                 status=Airplanes[j]->getStatus();
                 chillingcounter++;
                 if(status==Airplane::Approaching||status==Airplane::Landed){
                     landingstep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status==Airplane::Standing_at_gate){
                     airplaneAtGatestep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status==Airplane::Taxiing_to_gate){
                     taxiingToGatestep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status==Airplane::Leaving){
                     leavingstep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status==Airplane::Taxiing_to_runway){
                     taxiingToRunwaystep(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status==Airplane::Emergency){
                     emergencyLanding(*Airplanes[j],*Airplanes[j]->getDestination());
                 }
                 else if(status==Airplane::jobsdone&&!alreadypushed){
                     airplanestoremove.push_back(j);
                     alreadypushed=true;
                 }
             }while(Airplanes[j]->isDoingNothing()&&chillingcounter<3);
             Airplanes[j]->timeRuns();
         }
         for (unsigned int k = 0; k < Airports.size(); ++k) {
             chillingcounter=0;
             do{
                 Airports[k]->getTower().sendSignal();
                 chillingcounter++;
             }while(Airports[k]->getTower().isDoingNothing()&&chillingcounter<3);

             Airports[k]->getTower().timeRuns();

         }

         generateFloorPlan(*getAirports()[0]);
         createVisual(*getAirports()[0]);
         timespec tim, tim2;
         tim.tv_nsec=500000000L;
         tim.tv_sec=0;
         nanosleep(&tim,&tim2);
         for (unsigned int i = 0; i < airplanestoremove.size(); ++i) {
             AirplanesFlying.push_back((Airplanes.begin() + airplanestoremove[i] - i).operator*());
             Airplanes.erase(Airplanes.begin() + airplanestoremove[i] - i);
         }
         for (unsigned int i=0;i<getAirplanes().size();i++){
             Airplane* plane=getAirplanes()[i];
             plane->fuelReduction();
         }

         currentTime=currentTime++;
     }

}


void Airportsim::landingstep(Airplane &approaching, Airport &airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling landingstep");
    REQUIRE(approaching.ProperInitialized(),"Airplane wasn't initialized when calling landingstep");
    REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling landingstep");
    REQUIRE(approaching.getStatus()==Airplane::Approaching||approaching.getStatus()==Airplane::Landed,"Airplane must has the status of Approaching when calling landingstep");

    ofstream outputfile;

    string filename="../output/"+approaching.getCallsign()+".txt";

    outputfile.open(filename.c_str(),ios::app);

    if (approaching.getHeight()>5000&&approaching.getPermission()==Airplane::fiveThousandPermission){//getting permission
        approaching.fall();
        if(approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" descended to "<<approaching.getHeight()<<" ft."<<endl;
        }
    }

    else if(approaching.getHeight()>3000&&approaching.getPermission()==Airplane::threeThousandPermission){
        approaching.fall();
        if(approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" descended to "<<approaching.getHeight()<<" ft."<<endl;
        }
    }

    else if(approaching.getHeight()>=1000&&approaching.getPermission()==Airplane::LandingPermission){
        //on getting permission landing, a runway will be on use
        approaching.fall();
        if(approaching.getHeight()!=0&&approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" descended to "<<approaching.getHeight()<<" ft."<<endl;
        }
    }



    else if (approaching.getHeight()==0&&approaching.getStatus()!=Airplane::Landed){
        if(approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" is landing at "<<airport.getName()<<" on runway "<<approaching.getDestinateRunway()->getName()<<endl;
        }
        approaching.landing();
        if(approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" has landed at "<<airport.getName()<<" on runway "<<approaching.getDestinateRunway()->getName()<<endl;
            approaching.setLocation(approaching.getDestinateRunway());
            approaching.getDestinateRunway()->setPlaneAtEnd(&approaching);
        }
        //ask permission
    }
    else if(approaching.getStatus()==Airplane::Landed){
        if (approaching.getPermission()!=Airplane::TaxiingPermission){
            approaching.sendSignalTaxiingtoGate();
        }
        if(approaching.getPermission()==Airplane::TaxiingPermission){
            outputfile<<approaching.getCallsign()<<" is taxiing to Gates "<<endl;
            approaching.getDestinateRunway()->setCurrentairplane(NULL);
            approaching.setStatus(Airplane::Taxiing_to_gate);
        };
    }
    else if (approaching.getHeight()==10000&&approaching.getPermission()!=Airplane::tenThousandPermission){
        if(approaching.isDoingNothing()){
            outputfile<<approaching.getCallsign()<<" is approaching "<<airport.getName()<<" at 10000 ft."<<endl;
        }
        approaching.sendSignalApproaching();
        //initial contact;
    }
}
void Airportsim::emergencyLanding(Airplane& airplane,Airport& airport){
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling emergencyLanding");
    REQUIRE(airplane.ProperInitialized(),"Airplane wasn't initialized when calling emergencyLanding");
    REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling emergencyLanding");
    REQUIRE(airplane.getStatus()==Airplane::Emergency,"Airplane must has the status of Emergency when calling emergencyLanding");

    ofstream outputfile;
    string filename="../output/"+airport.getCallsign()+".txt";
    outputfile.open(filename.c_str(),ios::app);

    if(airplane.getDestinateRunway()!=NULL){
        if(airplane.getHeight()==0){
            if(airplane.getLocation()==airplane.getDestinateRunway()){
                airplane.progressCheck();
            }
            else{
                airplane.landing();
                if(airplane.isDoingNothing()){
                    airplane.setLocation(airplane.getDestinateRunway());
                }
            }
        }
        else{
            airplane.fall();
            if(airplane.isDoingNothing()){
                outputfile<<airplane.getCallsign()<<" descended to "<<airplane.getHeight()<<" ft."<<endl;
            }
        }
    }
    else{
        if(airplane.getHeight()==0){
            airplane.setStatus(Airplane::jobsdone);
            return;
        }
        else{
            airplane.fall();
        }
    }
}
void Airportsim::airplaneAtGatestep(Airplane &plane, Airport &airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling airplaneAtGatestep");
    REQUIRE(plane.ProperInitialized(),"Airplane wasn't initialized when calling airplaneAtGatestep");
    REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling airplaneAtGatestep");
    REQUIRE(plane.getStatus()==Airplane::Standing_at_gate,"Airplane must has the status of Standing at gate when calling airplaneAtGate");
    ofstream outputfile;
    string filename="../output/"+plane.getCallsign()+".txt";
    outputfile.open(filename.data(),ios::app);
    if(plane.getStatus()==Airplane::Standing_at_gate){
        if(plane.getCheckProcedure()==Airplane::Just_landed){
            plane.progressCheck();
            if(plane.isDoingNothing()){
                airport.addPassenger(plane.getPassenger());
                outputfile<<plane.getPassenger()<<" passengers exited "<<plane.getCallsign()<<" at gate "<<airport.getGateFromAirplane(&plane)->getName()<<" of "<<airport.getName()<<endl;
                plane.setPassenger(0);
            }
        }

        else if(plane.getCheckProcedure()==Airplane::Technical_control){
            plane.progressCheck();
            if(plane.isDoingNothing()){
                outputfile<<plane.getCallsign()<<" has been checked for technical malfunctions"<<endl;
            }
        }
        else if(plane.getCheckProcedure()==Airplane::Refueling){
            plane.progressCheck();
            if(plane.isDoingNothing()) {
                outputfile << plane.getCallsign() << " has been refueled" << endl;
            }
        }
        else if(plane.getCheckProcedure()==Airplane::Boarding){
            plane.progressCheck();
            if(plane.isDoingNothing()) {
                plane.setPassenger(plane.getPassengerCapacity());
                outputfile<<plane.getPassenger()<<" passengers boarded "<<plane.getCallsign()<<" at gate "<<airport.getGateFromAirplane(&plane)->getName()<<" of "<<airport.getName()<<endl;
            }
        }
        else if(plane.getCheckProcedure()==Airplane::Ready_to_leave){
            //ask permission to leave gate;
            Gate* gate=airport.getGateFromAirplane(&plane);
            if(plane.getPermission()!=Airplane::IFR_clearancyPermission&&plane.getPermission()!=Airplane::Push_backPermission&&plane.getPermission()!=Airplane::TaxiingPermission){
                plane.sendSignalIFR();
            }
            else if(plane.getPermission()!=Airplane::Push_backPermission&&plane.getPermission()!=Airplane::TaxiingPermission){
                plane.sendSignalPushBack();
            }
            else if(gate->getCurrentPlane()==&plane&&plane.getPermission()==Airplane::Push_backPermission){
                    if(plane.pushBack()){
                        //leave gate at first time, will get a runway assigned if succes, if not then wait one more round.
                        gate->setPlaneNearGate(&plane);
                        gate->setCurrentPlane(NULL);
                    }//care, maybe syntax problems. idk?
                }
            else if(plane.getPermission()!=Airplane::TaxiingPermission){
                plane.sendSignalTaxiingtoRunway();
            }
            else if(plane.getPermission()==Airplane::TaxiingPermission){
                plane.resetCheckProcedure();
                //ask permission, if there is a runway available just go there.
                plane.setStatus(Airplane::Taxiing_to_runway);
                gate->setPlaneNearGate(NULL);
                outputfile<<plane.getCallsign()<<" is standing at Gate "<<gate->getName()<<endl;
                outputfile<<plane.getCallsign()<<" is taxiing to runway "<<plane.getDestinateRunway()->getName()<<endl;//add here
            }
        }
    }
}

void Airportsim::taxiingToGatestep(Airplane &taxiingplane, Airport &airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling taxiingToGatestep");
    REQUIRE(taxiingplane.ProperInitialized(),"Airplane wasn't initialized when calling taxiingToGatestep");
    REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling taxiingToGatestep");
    REQUIRE(taxiingplane.getStatus()==Airplane::Taxiing_to_gate,"Airplane must has the status of Taxiing to gate when calling taxiingToGatestep");
        ofstream outputfile;
        string filename="../output/"+taxiingplane.getCallsign()+".txt";
        outputfile.open(filename.c_str(),ios::app);
        vector<Location*> instruction=taxiingplane.getInstruction();

        if(taxiingplane.getLocation()->isGate()){
            //only a gate location will be giving under this condition
            for (unsigned int i = 0; i < airport.getGates().size(); ++i) {
                if(airport.getGates()[i]->getName()==taxiingplane.getLocation()->getName()){
                    airport.getGates()[i]->setCurrentPlane(&taxiingplane);
                    break;
                }
            }
            outputfile<<taxiingplane.getCallsign()<<" is standing at Gate "<<taxiingplane.getLocation()->getName()<<endl;
            vector<Location*> empty;
            taxiingplane.setInstruction(empty);
            taxiingplane.setStatus(Airplane::Standing_at_gate);
        }
        else if(taxiingplane.getLocation()==taxiingplane.getDestinateRunway()){
            //first set after landing will be immidiate;
            taxiingplane.setLocation((find(instruction.begin(),instruction.end(),taxiingplane.getLocation())+1).operator*());
            if(taxiingplane.getLocation()->isTaxipoint()){
                taxiingplane.taxiing();
                taxiingplane.getLocation()->setOnuse(true);
                airport.findTaxipoint(taxiingplane.getLocation()->getName())->addPlanesWaiting(&taxiingplane);
            }
            taxiingplane.getDestinateRunway()->setPlaneAtEnd(NULL);
            taxiingplane.setDestinateRunway(NULL);
        }
        else if(!taxiingplane.getLocation()->isRunway()&&taxiingplane.getLocation()->isTaxipoint()){
            if(taxiingplane.taxiing()){
                taxiingplane.setLocation((find(instruction.begin(),instruction.end(),taxiingplane.getLocation())+1).operator*());
            }
        }
        else if(taxiingplane.getLocation()->isRunway()&&taxiingplane.getPermission()!=Airplane::Cleared_to_crossPermission){
            taxiingplane.sendSignalCrossingRunway();
        }
        else if(taxiingplane.getPermission()==Airplane::Cleared_to_crossPermission&&taxiingplane.getLocation()->isRunway()){
            if(taxiingplane.crossingRunway()){
                taxiingplane.setLocation((find(instruction.begin(),instruction.end(),taxiingplane.getLocation())+1).operator*());
                if(taxiingplane.getLocation()->isTaxipoint()){
                    taxiingplane.taxiing();
                    taxiingplane.getLocation()->setOnuse(true);
                    airport.findTaxipoint(taxiingplane.getLocation()->getName())->addPlanesWaiting(&taxiingplane);
                }
            }
        }
    //if(taxiingplane.getLocation()==taxiingplane.getInstruction()[taxiingplane.getInstruction().size()-1]){
        //hold short
        //}


}

void Airportsim::taxiingToRunwaystep(Airplane &taxiingplane, Airport &airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling taxiingToRunwaystep");
    REQUIRE(taxiingplane.ProperInitialized(),"Airplane wasn't initialized when calling taxiingToRunwaystep");
    REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling taxiingToRunwaystep");
    REQUIRE(taxiingplane.getStatus()==Airplane::Taxiing_to_runway,"Airplane must has the status of Taxiing to runway when calling taxiingToRunwaystep");
        ofstream outputfile;
        string filename = "../output/" + taxiingplane.getCallsign() + ".txt";
        outputfile.open(filename.c_str(), ios::app);
        Runway *destination = taxiingplane.getDestinateRunway();
        vector<Location *> instruction = taxiingplane.getInstruction();

        if (taxiingplane.getLocation() == destination && (taxiingplane.getPermission()==Airplane::LineupPermission||taxiingplane.getPermission()==Airplane::FlyPermission)) {
            if(taxiingplane.liningUp()){
                /*
                destination->setPlaneAtbegin(&taxiingplane);
                if(taxiingplane.getPermission()=="Fly"){
                    destination->setCurrentairplane(&taxiingplane);
                }
                 */
                taxiingplane.setStatus(Airplane::Leaving);
            }
        }
        else if (taxiingplane.getLocation() == destination&&!(taxiingplane.getPermission()==Airplane::LineupPermission||taxiingplane.getPermission()==Airplane::FlyPermission)) {
            taxiingplane.sendSignalAtRunway();
        }
        else if(taxiingplane.getLocation()->isGate()){
            taxiingplane.setLocation((find(instruction.begin(), instruction.end(), taxiingplane.getLocation()) + 1).operator*());
            if(taxiingplane.getLocation()->isTaxipoint()){
                taxiingplane.taxiing();
                taxiingplane.getLocation()->setOnuse(true);
                airport.findTaxipoint(taxiingplane.getLocation()->getName())->addPlanesWaiting(&taxiingplane);
            }
        }
        else if(taxiingplane.getLocation()->isTaxipoint()){
            if(taxiingplane.taxiing()){
                taxiingplane.setLocation((find(instruction.begin(), instruction.end(), taxiingplane.getLocation()) + 1).operator*());
            }
        }
        else if (taxiingplane.getLocation()->isRunway()&&taxiingplane.getPermission()!=Airplane::Cleared_to_crossPermission){
            taxiingplane.sendSignalCrossingRunway();
        }
        else if(taxiingplane.getLocation()->isRunway()&&taxiingplane.getPermission()==Airplane::Cleared_to_crossPermission){
            if(taxiingplane.crossingRunway()){
                taxiingplane.setLocation((find(instruction.begin(), instruction.end(), taxiingplane.getLocation()) + 1).operator*());
                if(taxiingplane.getLocation()->isTaxipoint()){
                    taxiingplane.taxiing();
                    taxiingplane.getLocation()->setOnuse(true);
                    airport.findTaxipoint(taxiingplane.getLocation()->getName())->addPlanesWaiting(&taxiingplane);
                }
            }
        }
}

void Airportsim::leavingstep(Airplane &leaving, Airport &airport) {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling leavingstep");
    REQUIRE(leaving.ProperInitialized(),"Airplane wasn't initialized when calling leavingstep");
    REQUIRE(airport.ProperInitialized(),"Airport wasn't initialized when calling leavingstep");
    REQUIRE(leaving.getStatus()==Airplane::Leaving,"Airplane must has the status of Leaving when calling leavingstep");
    ofstream outputfile;
    string filename="../output/"+leaving.getCallsign()+".txt";
    outputfile.open(filename.c_str(),ios::app);
    //ask leaving permission

    if(leaving.getHeight()==0&&leaving.getPermission()==Airplane::FlyPermission&&leaving.getDestinateRunway()==NULL){
        leaving.rise();
    }
    else if(leaving.getHeight()==0&&leaving.getPermission()==Airplane::FlyPermission){
        if(leaving.isDoingNothing()){
            outputfile<<leaving.getCallsign()<<" is taking off at "<<airport.getName()<<" on runway "<<leaving.getDestinateRunway()->getName()<<endl;

            if(leaving.getDestinateRunway()->getPlaneAtbegin()==&leaving){
                leaving.getDestinateRunway()->setPlaneAtbegin(NULL);
            }
        }
        if(leaving.takeOff()){
            leaving.getDestinateRunway()->planeLeaved();
            leaving.getDestinateRunway()->setCurrentairplane(NULL);
            leaving.setDestinateRunway(NULL);
            airport.getTower().getFile()<<"airplane "<<leaving.getCallsign()<< " left"<<currentTime<<endl;
        }
        //test purpose
    }
    else if(leaving.getHeight()>5000&&leaving.getPermission()==Airplane::FlyPermission){
        outputfile<<leaving.getCallsign()<<" has left "<<airport.getName()<<endl;
        leaving.setPermission(Airplane::empty);
        leaving.setStatus(Airplane::jobsdone);
    }
    else if(leaving.getHeight()>=1000&&leaving.getPermission()==Airplane::FlyPermission){
        //don't need permission anymore once it has rised;
        if(leaving.isDoingNothing()){
            outputfile<<leaving.getCallsign()<<" ascended to "<<leaving.getHeight()<<" ft."<<endl;
        }
        leaving.rise();
    }
    else if (leaving.getHeight()==0&&leaving.getPermission()!=Airplane::FlyPermission){
        //await for signal;
    }
}

const Time &Airportsim::getCurrentTime() const {
    REQUIRE(ProperInitialized(), "airportsim wasn't initialized when calling getCurrentTime");
    return currentTime;
}

void Airportsim::setCurrentTime(const Time &currentTime) {
    REQUIRE(ProperInitialized(), "airportsim wasn't initialized when calling setCurrentTime");
    Airportsim::currentTime = currentTime;
    ENSURE(getCurrentTime()==currentTime,"setCurrenTime postcondition failed");
}

void Airportsim::generateFloorPlan(Airport &vlieghaven) {
    REQUIRE(vlieghaven.ProperInitialized(), "airport wasn't initialized when calling generateFloorPlan");
    ofstream outputfile;
    string filename = "../output/floormap_state_airport[" + vlieghaven.getIata() + "]"+".txt";
    outputfile.open(filename.c_str(), ios::app);
    outputfile<<getCurrentTime()<<endl;
    for (unsigned int i = 0; i < vlieghaven.getRunways().size(); i++) {
        Runway *runway = vlieghaven.getRunways()[vlieghaven.getRunways().size() - 1 - i];
        outputfile << runway->getName() << " | ";
        if (runway->isOnuse()) {
            if(runway->getPlaneAtbegin()!=NULL){
                outputfile << "V=========" << endl;
            }
            else if(runway->getPlaneAtEnd()!=NULL){
                outputfile << "=========V" << endl;
            }
            else{
                outputfile << "====V=====" << endl;
            }
        } else {
            outputfile << "==========" << endl;
        }
        outputfile << "TP" << runway->getTaxipoint()->getName()[0] << " | ";
        if(runway->getTaxipoint()->isOnuse()){
            for(unsigned int j=0;j<runway->getTaxipoint()->getPlanesWaiting().size();j++){
                outputfile<<"V";
            }
        }
        outputfile << endl;
    }
    outputfile << "Gates [";
    for (unsigned int i = 0; i < vlieghaven.getGates().size(); i++) {
        Gate *gate = vlieghaven.getGates()[i];
        if (gate->isOnuse()) {
            outputfile << "V";
        } else {
            outputfile << " ";
        }
    }
    outputfile << "]" << endl;
    outputfile.close();
    ENSURE(fileExist(filename.c_str()), "generateFloorPlan postcondition failed");
}
void Airportsim::writeIni(Airport &airport) {
    REQUIRE(airport.ProperInitialized(), "airport wasn't initialized when calling writeIni");
    int amountFigs=42;
    ofstream outputfile;
    string filename = "../output/settings_2D_[" + airport.getIata() + "]"+".ini";
    outputfile.open(filename.c_str(), ios::out);
    outputfile<<"[General]\n"<<"type = \"LightedZBuffering\"\n"<<"size = 1024\n"<<"backgroundcolor = (0, 1, 0)\n";
    int amountFigures=airport.getRunways().size()*amountFigs;
    for(unsigned int i=0;i<airport.getRunways().size();i++){
        if(airport.getRunways()[i]->isOnuse()){
            amountFigures+=6;
        }
        if(airport.getRunways()[i]->getTaxipoint()->isOnuse()){
            amountFigures+=6*airport.getRunways()[i]->getTaxipoint()->getPlanesWaiting().size();
        }
        if(airport.getRunways()[i]->isCrossing()){
            amountFigures+=6;
        }
    }
    amountFigures+=airport.getGates().size();
    for(unsigned int i=0;i<airport.getGates().size();i++){
        if(airport.getGates()[i]->getCurrentPlane()!=NULL){
            amountFigures+=6;
        }
        if(airport.getGates()[i]->getPlaneNearGate()!=NULL){
            amountFigures+=6;
        }
    }
    outputfile<<"nrLights = 1\n";
    outputfile<<"nrFigures = "<<amountFigures<<"\n"<<"eye = (0, 0, 10000)\n\n";
    outputfile<<"[Light0]\n"
            "infinity = TRUE\n"
            "direction = (1, 1, 1)\n"
            "ambientLight = (1, 1, 1)\n"
            "diffuseLight = (1, 1, 1)\n\n";
    amountFigs=0;
    for(unsigned int i=0;i<airport.getRunways().size();i++){
        for(int j=0;j<7;j++){
            outputfile<<"[Figure"<<amountFigs+j<<"]\n"
                    "type = \"Cube\"\n"
                    "scale = 120\n"
                    "rotateX = 0\n"
                    "rotateY = 0\n"
                    "rotateZ = 0\n"
                    "center = ("<<i*720<<", "<<-720+240*j<<", 0)\n"
                              "color = (0.501, 0.501, 0.501)\n"
                              "ambientReflection = (0.501, 0.501, 0.501)\n"
                              "diffuseReflection = (0.501, 0.501, 0.501)\n"
                              "\n";
        }
        outputfile<<"[Figure"<<7+amountFigs<<"]\n"
                "type = \"Cube\"\n"
                "scale = 120\n"
                "rotateX = -15\n"
                "rotateY = -15\n"
                "rotateZ = 45\n"
                "center = ("<<360+i*720<<", 0, 0)\n"
                          "color = (0.3, 0.3, 0.3)\n"
                          "ambientReflection = (0.3, 0.3, 0.3)\n"
                          "diffuseReflection = (0.3, 0.3, 0.3)\n\n";
        for(unsigned int j=0;j<17;j++){
            outputfile<<"[Figure"<<8+2*j+amountFigs<<"]\n"
                    "type = \"Cube\"\n"
                    "scale = 12\n"
                    "rotateX = 0\n"
                    "rotateY = 0\n"
                    "rotateZ = 0\n"
                    "center = ("<<720*i<<", "<<-780+96*j<<", 120)\n"
                              "color = (1.0, 1.0, 1.0)\n"
                              "ambientReflection = (1.0, 1.0, 1.0)\n"
                              "diffuseReflection = (1.0, 1.0, 1.0)\n"
                              "\n"
                              "\n"
                              "[Figure"<<9+j*2+amountFigs<<"]\n"
                              "type = \"Cube\"\n"
                              "scale = 12\n"
                              "rotateX = 0\n"
                              "rotateY = 0\n"
                              "rotateZ = 0\n"
                              "center = ("<<720*i<<", "<<-756+96*j<<", 120)\n"
                              "color = (1.0, 1.0, 1.0)\n"
                              "ambientReflection = (1.0, 1.0, 1.0)\n"
                              "diffuseReflection = (1.0, 1.0, 1.0)\n"
                              "\n";
        }
        if(airport.getRunways()[i]->isOnuse()){
            int horizontalMovement=0;
            if(airport.getRunways()[i]->getPlaneAtbegin()!=NULL){
                horizontalMovement-=720;
            }
            else if(airport.getRunways()[i]->getPlaneAtEnd()!=NULL){
                horizontalMovement+=720;
            }
            double scaleFactor=0.5;
            int zval=200;
            outputfile<<"[Figure"<<42+amountFigs<<"]\n"
                    "type = \"Cylinder\"\n"
                    "height = 7\n"
                    "n = 40\n"
                    "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 90\n"
                              "rotateY = 0\n"
                              "rotateZ = 45\n"
                              "center = ("<<720*(airport.getRunways().size()-1-i)+0*scaleFactor<<", "<<(0)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<43+amountFigs<<"]\n"
                              "type = \"Cone\"\n"
                              "height = 1.5\n"
                              "n = 40\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 270\n"
                              "rotateY = 0\n"
                              "rotateZ = 45\n"
                              "center = ("<<720*(airport.getRunways().size()-1-i)+0*scaleFactor<<", "<<0*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<44+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 45\n"
                              "rotateY = 0\n"
                              "rotateZ = -10\n"
                              "center = ("<<(50)*scaleFactor+720*(airport.getRunways().size()-1-i)<<", "<<(-180)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<45+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<40*scaleFactor<<"\n"
                              "rotateX = 50\n"
                              "rotateY = 0\n"
                              "rotateZ = -68\n"
                              "center = ("<<(75)*scaleFactor+720*(airport.getRunways().size()-1-i)<<", "<<(-249)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<46+amountFigs<<"]\n"
                              "type = \"Cube\"\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 0\n"
                              "rotateY = 0\n"
                              "rotateZ = 79\n"
                              "center = ("<<(28)*scaleFactor+720*(airport.getRunways().size()-1-i)<<", "<<(-302)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<47+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<40*scaleFactor<<"\n"
                              "rotateX = 50\n"
                              "rotateY = 0\n"
                              "rotateZ = 112\n"
                              "center = ("<<(220)*scaleFactor+720*(airport.getRunways().size()-1-i)<<", "<<(-330)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n\n";
            amountFigs+=6;
        }
        if(airport.getRunways()[i]->isCrossing()){
            int horizontalMovement=0;
            double scaleFactor=0.5;
            int zval=200;
            outputfile<<"[Figure"<<42+amountFigs<<"]\n"
                    "type = \"Cylinder\"\n"
                    "height = 7\n"
                    "n = 40\n"
                    "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 90\n"
                              "rotateY = 0\n"
                              "rotateZ = 45\n"
                              "center = ("<<720*(airport.getRunways().size()-1-i)+0*scaleFactor<<", "<<(0)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<43+amountFigs<<"]\n"
                              "type = \"Cone\"\n"
                              "height = 1.5\n"
                              "n = 40\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 270\n"
                              "rotateY = 0\n"
                              "rotateZ = 45\n"
                              "center = ("<<720*(airport.getRunways().size()-1-i)+0*scaleFactor<<", "<<0*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<44+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 45\n"
                              "rotateY = 0\n"
                              "rotateZ = -10\n"
                              "center = ("<<(50)*scaleFactor+720*(airport.getRunways().size()-1-i)<<", "<<(-180)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<45+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<40*scaleFactor<<"\n"
                              "rotateX = 50\n"
                              "rotateY = 0\n"
                              "rotateZ = -68\n"
                              "center = ("<<(75)*scaleFactor+720*(airport.getRunways().size()-1-i)<<", "<<(-249)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<46+amountFigs<<"]\n"
                              "type = \"Cube\"\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 0\n"
                              "rotateY = 0\n"
                              "rotateZ = 79\n"
                              "center = ("<<(28)*scaleFactor+720*(airport.getRunways().size()-1-i)<<", "<<(-302)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<47+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<40*scaleFactor<<"\n"
                              "rotateX = 50\n"
                              "rotateY = 0\n"
                              "rotateZ = 112\n"
                              "center = ("<<(220)*scaleFactor+720*(airport.getRunways().size()-1-i)<<", "<<(-330)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n\n";
            amountFigs+=6;

        }
        if(airport.getRunways()[i]->getTaxipoint()->isOnuse()){
            for (unsigned int j = 0; j <airport.getRunways()[i]->getTaxipoint()->getPlanesWaiting().size() ; ++j) {
                int horizontalMovement=0+j*240;
                double scaleFactor=0.5;
                int zval=200;
                outputfile<<"[Figure"<<42+amountFigs<<"]\n"
                        "type = \"Cylinder\"\n"
                        "height = 7\n"
                        "n = 40\n"
                        "scale = "<<60*scaleFactor<<"\n"
                                  "rotateX = 90\n"
                                  "rotateY = 0\n"
                                  "rotateZ = 45\n"
                                  "center = ("<<720*(airport.getRunways().size()-1-i)+360+0*scaleFactor<<", "<<(0)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                                  "color = (1, 1, 1)\n"
                                  "ambientReflection = (1, 1, 1)\n"
                                  "diffuseReflection = (0, 0, 0)\n"
                                  "\n"
                                  "[Figure"<<43+amountFigs<<"]\n"
                                  "type = \"Cone\"\n"
                                  "height = 1.5\n"
                                  "n = 40\n"
                                  "scale = "<<60*scaleFactor<<"\n"
                                  "rotateX = 270\n"
                                  "rotateY = 0\n"
                                  "rotateZ = 45\n"
                                  "center = ("<<720*(airport.getRunways().size()-1-i)+360+0*scaleFactor<<", "<<0*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                                  "color = (1, 1, 1)\n"
                                  "ambientReflection = (1, 1, 1)\n"
                                  "diffuseReflection = (0, 0, 0)\n"
                                  "\n"
                                  "[Figure"<<44+amountFigs<<"]\n"
                                  "type = \"Tetrahedron\"\n"
                                  "scale = "<<60*scaleFactor<<"\n"
                                  "rotateX = 45\n"
                                  "rotateY = 0\n"
                                  "rotateZ = -10\n"
                                  "center = ("<<(50)*scaleFactor+720*(airport.getRunways().size()-1-i)+360<<", "<<(-180)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                                  "color = (1, 1, 1)\n"
                                  "ambientReflection = (1, 1, 1)\n"
                                  "diffuseReflection = (0, 0, 0)\n"
                                  "\n"
                                  "[Figure"<<45+amountFigs<<"]\n"
                                  "type = \"Tetrahedron\"\n"
                                  "scale = "<<40*scaleFactor<<"\n"
                                  "rotateX = 50\n"
                                  "rotateY = 0\n"
                                  "rotateZ = -68\n"
                                  "center = ("<<(75)*scaleFactor+720*(airport.getRunways().size()-1-i)+360<<", "<<(-249)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                                  "color = (1, 1, 1)\n"
                                  "ambientReflection = (1, 1, 1)\n"
                                  "diffuseReflection = (0, 0, 0)\n"
                                  "\n"
                                  "[Figure"<<46+amountFigs<<"]\n"
                                  "type = \"Cube\"\n"
                                  "scale = "<<60*scaleFactor<<"\n"
                                  "rotateX = 0\n"
                                  "rotateY = 0\n"
                                  "rotateZ = 79\n"
                                  "center = ("<<(28)*scaleFactor+720*(airport.getRunways().size()-1-i)+360<<", "<<(-302)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                                  "color = (1, 1, 1)\n"
                                  "ambientReflection = (1, 1, 1)\n"
                                  "diffuseReflection = (0, 0, 0)\n"
                                  "\n"
                                  "[Figure"<<47+amountFigs<<"]\n"
                                  "type = \"Tetrahedron\"\n"
                                  "scale = "<<40*scaleFactor<<"\n"
                                  "rotateX = 50\n"
                                  "rotateY = 0\n"
                                  "rotateZ = 112\n"
                                  "center = ("<<(220)*scaleFactor+720*(airport.getRunways().size()-1-i)+360<<", "<<(-330)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                                  "color = (1, 1, 1)\n"
                                  "ambientReflection = (1, 1, 1)\n"
                                  "diffuseReflection = (0, 0, 0)\n\n";
                amountFigs+=6;
            }

        }
        amountFigs+=42;
    }
    int begingates=ceil(airport.getGates().size()/2)*(-240);
    for(unsigned int i=0;i<airport.getGates().size();i++){
        outputfile<<"[Figure"<<amountFigs<<"]\n"
                "type = \"Cube\"\n"
                "scale = 120\n"
                "rotateX = 0\n"
                "rotateY = 0\n"
                "rotateZ = 0\n"
                "center = ("<<airport.getRunways().size()*720<<", "<<begingates+240*i<<", 0)\n"
                          "color = (0.02745098, 0.968627451, 0.843137255)\n"
                          "ambientReflection = (0.02745098, 0.968627451, 0.843137255)\n"
                          "diffuseReflection = (0.02745098, 0.968627451, 0.843137255)\n"
                          "\n";
        amountFigs++;
        if(airport.getGates()[i]->getCurrentPlane()!=NULL){
            int horizontalMovement=begingates+240*i;
            double scaleFactor=0.5;
            int zval=200;
            outputfile<<"[Figure"<<amountFigs<<"]\n"
                    "type = \"Cylinder\"\n"
                    "height = 7\n"
                    "n = 40\n"
                    "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 90\n"
                              "rotateY = 0\n"
                              "rotateZ = 45\n"
                              "center = ("<<720*airport.getRunways().size()+0*scaleFactor<<", "<<(0)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<1+amountFigs<<"]\n"
                              "type = \"Cone\"\n"
                              "height = 1.5\n"
                              "n = 40\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 270\n"
                              "rotateY = 0\n"
                              "rotateZ = 45\n"
                              "center = ("<<720*airport.getRunways().size()+0*scaleFactor<<", "<<0*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<2+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 45\n"
                              "rotateY = 0\n"
                              "rotateZ = -10\n"
                              "center = ("<<(50)*scaleFactor+720*airport.getRunways().size()<<", "<<(-180)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<3+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<40*scaleFactor<<"\n"
                              "rotateX = 50\n"
                              "rotateY = 0\n"
                              "rotateZ = -68\n"
                              "center = ("<<(75)*scaleFactor+720*airport.getRunways().size()<<", "<<(-249)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<4+amountFigs<<"]\n"
                              "type = \"Cube\"\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 0\n"
                              "rotateY = 0\n"
                              "rotateZ = 79\n"
                              "center = ("<<(28)*scaleFactor+720*airport.getRunways().size()<<", "<<(-302)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<5+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<40*scaleFactor<<"\n"
                              "rotateX = 50\n"
                              "rotateY = 0\n"
                              "rotateZ = 112\n"
                              "center = ("<<(220)*scaleFactor+720*airport.getRunways().size()<<", "<<(-330)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n\n";
            amountFigs+=6;
        }
        if(airport.getGates()[i]->getPlaneNearGate()!=NULL){
            int horizontalMovement=begingates+240*i;
            double scaleFactor=0.5;
            int zval=200;
            outputfile<<"[Figure"<<amountFigs<<"]\n"
                    "type = \"Cylinder\"\n"
                    "height = 7\n"
                    "n = 40\n"
                    "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 90\n"
                              "rotateY = 0\n"
                              "rotateZ = 45\n"
                              "center = ("<<720*airport.getRunways().size()+0*scaleFactor-200<<", "<<(0)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<1+amountFigs<<"]\n"
                              "type = \"Cone\"\n"
                              "height = 1.5\n"
                              "n = 40\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 270\n"
                              "rotateY = 0\n"
                              "rotateZ = 45\n"
                              "center = ("<<720*airport.getRunways().size()+0*scaleFactor-200<<", "<<0*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<2+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 45\n"
                              "rotateY = 0\n"
                              "rotateZ = -10\n"
                              "center = ("<<(50)*scaleFactor+720*airport.getRunways().size()-200<<", "<<(-180)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<3+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<40*scaleFactor<<"\n"
                              "rotateX = 50\n"
                              "rotateY = 0\n"
                              "rotateZ = -68\n"
                              "center = ("<<(75)*scaleFactor+720*airport.getRunways().size()-200<<", "<<(-249)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<4+amountFigs<<"]\n"
                              "type = \"Cube\"\n"
                              "scale = "<<60*scaleFactor<<"\n"
                              "rotateX = 0\n"
                              "rotateY = 0\n"
                              "rotateZ = 79\n"
                              "center = ("<<(28)*scaleFactor+720*airport.getRunways().size()-200<<", "<<(-302)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n"
                              "\n"
                              "[Figure"<<5+amountFigs<<"]\n"
                              "type = \"Tetrahedron\"\n"
                              "scale = "<<40*scaleFactor<<"\n"
                              "rotateX = 50\n"
                              "rotateY = 0\n"
                              "rotateZ = 112\n"
                              "center = ("<<(220)*scaleFactor+720*airport.getRunways().size()-200<<", "<<(-330)*scaleFactor+horizontalMovement<<", "<<zval<<")\n"
                              "color = (1, 1, 1)\n"
                              "ambientReflection = (1, 1, 1)\n"
                              "diffuseReflection = (0, 0, 0)\n\n";
            amountFigs+=6;
        }
    }
    ENSURE(fileExist(filename.c_str()), "writeIni postcondition failed");
}
void Airportsim::createVisual(Airport &airport) {
    REQUIRE(airport.ProperInitialized(), "airport wasn't initialized when calling createVisual");
    writeIni(airport);
    string filename = "../Engine/./engine ../output/settings_2D_[" + airport.getIata() + "]"+".ini";
    system(filename.c_str());
}

void Airportsim::simulate_Onetime() {
    REQUIRE(ProperInitialized(),"Airportsim object wasn't initialized when calling simulate_Onetime");
    vector<int> airplanestoremove;
    bool  alreadypushed=false;
    int chillingcounter=0;
    Airplane::Airplaneallowedstatus status;

    for (unsigned int j = 0; j < Airplanes.size(); ++j) {
        alreadypushed=false;
        chillingcounter=0;
        do{
            status=Airplanes[j]->getStatus();
            chillingcounter++;
            if(status==Airplane::Approaching||status==Airplane::Landed){
                landingstep(*Airplanes[j],*Airplanes[j]->getDestination());
            }
            else if(status==Airplane::Standing_at_gate){
                airplaneAtGatestep(*Airplanes[j],*Airplanes[j]->getDestination());
            }
            else if(status==Airplane::Taxiing_to_gate){
                taxiingToGatestep(*Airplanes[j],*Airplanes[j]->getDestination());
            }
            else if(status==Airplane::Leaving){
                leavingstep(*Airplanes[j],*Airplanes[j]->getDestination());
            }
            else if(status==Airplane::Taxiing_to_runway){
                taxiingToRunwaystep(*Airplanes[j],*Airplanes[j]->getDestination());
            }
            else if(status==Airplane::jobsdone&&!alreadypushed){
                airplanestoremove.push_back(j);
                alreadypushed=true;
            }
        }while(Airplanes[j]->isDoingNothing()&&chillingcounter<3);
        Airplanes[j]->timeRuns();
    }
    for (unsigned int k = 0; k < Airports.size(); ++k) {
        chillingcounter=0;
        do{
            Airports[k]->getTower().sendSignal();
            chillingcounter++;
        }while(Airports[k]->getTower().isDoingNothing()&&chillingcounter<3);

        Airports[k]->getTower().timeRuns();

    }

    //generateFloorPlan(*getAirports()[0]);
    //createVisual(*getAirports()[0]);
    //timespec tim, tim2;
    //tim.tv_nsec=500000000L;
    //tim.tv_sec=0;
    //nanosleep(&tim,&tim2);
    for (unsigned int i = 0; i < airplanestoremove.size(); ++i) {
        AirplanesFlying.push_back((Airplanes.begin() + airplanestoremove[i] - i).operator*());
        Airplanes.erase(Airplanes.begin() + airplanestoremove[i] - i);
    }
    currentTime=currentTime++;
}



