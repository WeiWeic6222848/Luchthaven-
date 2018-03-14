//
// Created by c6222 on 2018/3/8.
//

#include <iostream>
#include "LuchthavenXML.h"

LuchthavenXML::LuchthavenXML(const string& filename) {
    TiXmlDocument XMLfile(filename.c_str());
    if (XMLfile.LoadFile()) {
        TiXmlElement *Root = XMLfile.RootElement();
        if (Root) {
            for (TiXmlElement* childelement=Root->FirstChildElement();childelement!= nullptr;childelement=childelement->NextSiblingElement()){
                string Elementname=childelement->Value();
                if (Elementname=="AIRPORT"){
                    string name=childelement->FirstChildElement("name")->GetText();
                    string iata=childelement->FirstChildElement("iata")->GetText();
                    string callsign=childelement->FirstChildElement("callsign")->GetText();
                    int gates=stoi(childelement->FirstChildElement("gates")->GetText());
                    int passenger=0;
                    if (childelement->FirstChildElement("passenger")){
                        int passenger=stoi(childelement->FirstChildElement("passenger")->GetText());
                    }
                    cout<<name<<iata<<callsign<<gates<<passenger<<endl;
                    Airport tempair(name,iata,callsign,gates,passenger);
                    Airports.push_back(tempair);
                }
                else if (Elementname=="RUNWAY"){
                    string name=childelement->FirstChildElement("name")->GetText();
                    string airport=childelement->FirstChildElement("airport")->GetText();
                    cout<<name<<airport;
                    for (Airport air:Airports) {
                        if(air.getIata()==airport){
                            Runway* runway=new Runway(name);
                            air.addrunway(runway);
                        }
                    }
                }
                else if (Elementname=="AIRPLANE"){
                    //do somehing with airplane
                }
            }
        }
    }
}
