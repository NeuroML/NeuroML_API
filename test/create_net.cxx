// Copyright 2017 University College London.
// See Licence.txt for details.

// Test building a NeuroML2 network from scratch

#include <iostream>
#include <fstream>
#include <memory>

#include "neuroml.hxx"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Specify the name of the file to save to:" << std::endl;
        std::cerr << "    " << argv[0] << " <file.nml>" << std::endl;
        return 1;
    }

    try
    {
        neuroml2::NeuroMLDocument* nmlDoc = new neuroml2::NeuroMLDocument("TestIzhNet");
        
        const neuroml2::Izhikevich2007Cell* izhCell = new neuroml2::Izhikevich2007Cell("RS","100 pF","-60mV","0.7 nS_per_mV",
                "-60 mV","-40 mV","35 mV","0.03 per_ms","-2 nS","-50 mV","100 pA");
        
        nmlDoc->izhikevich2007Cell().push_back(*izhCell);
        
        neuroml2::Network* net = new neuroml2::Network("Network0");
        
        
        neuroml2::Population* pop = new neuroml2::Population("Pop0",izhCell->id());
        pop->size(5);
        //pop->type("populationList");
        
        net->population().push_back(*pop);
        
        nmlDoc->network().push_back(*net);
        
        std::cout << "Saving to file: " << argv[1] << std::endl;
        nmlDoc->writeToFile(argv[1]);
        
    }
    catch (const xml_schema::exception& e)
    {
        std::cerr << "XSD error:" << std::endl << e << std::endl;
        return 1;
    }
    return 0;
}
